Ahora mismo tenemos:

```
docker compose up
       │
       ├── db
       └── web
```

y `web` tiene:

```
depends_on:
  - db
```

El problema es que `depends_on` solamente controla **el orden de arranque**. PostgreSQL puede haber iniciado el contenedor pero todavía no estar listo para aceptar conexiones.

Queremos pasar de:

```
db inicia
   ↓
web inicia
   ↓
¿PostgreSQL está listo?
   └── quizá sí / quizá no
```

a:

```
db inicia
   ↓
healthcheck
   ↓
PostgreSQL READY
   ↓
web inicia
```

## Agregar `healthcheck` a PostgreSQL

En tu `docker-compose.yml`, modifica `db`:

```d
services:
  db:
    image: postgres:17
    container_name: industrial-monitoring-db
    restart: unless-stopped

    environment:
      POSTGRES_DB: ${POSTGRES_DB}
      POSTGRES_USER: ${POSTGRES_USER}
      POSTGRES_PASSWORD: ${POSTGRES_PASSWORD}

    ports:
      - "5432:5432"

    volumes:
      - postgres_data:/var/lib/postgresql/data

    healthcheck:
      test: ["CMD-SHELL", "pg_isready -U ${POSTGRES_USER} -d ${POSTGRES_DB}"]
      interval: 5s
      timeout: 5s
      retries: 5
```

### ¿Qué es `pg_isready`?

PostgreSQL trae una herramienta llamada:

```
pg_isready
```

que permite preguntar:

> "¿PostgreSQL está listo para aceptar conexiones?"

Por ejemplo:

```
pg_isready
     │
     ▼
PostgreSQL
     │
     ├── ready    → healthcheck OK
     │
     └── not ready
```

# Modificar `depends_on`

Ahora cambia:

```d
depends_on:
  - db
```

por:

```d
depends_on:
  db:
    condition: service_healthy
```

Entonces tu `web` queda:

```
  web:
    build: .
    container_name: industrial-monitoring-api
    restart: unless-stopped

    env_file:
      - .env.docker

    ports:
      - "8000:8000"

    depends_on:
      db:
        condition: service_healthy
```

La diferencia es importante:

### Antes

```
depends_on: db

"Arranca db primero."
```

### Ahora

```
condition: service_healthy

"Arranca web cuando db esté saludable."
```


# Tu `docker-compose.yml` completo

Deberías tener algo parecido a:

```d
services:
  db:
    image: postgres:17
    container_name: industrial-monitoring-db
    restart: unless-stopped

    environment:
      POSTGRES_DB: ${POSTGRES_DB}
      POSTGRES_USER: ${POSTGRES_USER}
      POSTGRES_PASSWORD: ${POSTGRES_PASSWORD}

    ports:
      - "5432:5432"

    volumes:
      - postgres_data:/var/lib/postgresql/data

    healthcheck:
      test: ["CMD-SHELL", "pg_isready -U ${POSTGRES_USER} -d ${POSTGRES_DB}"]
      interval: 5s
      timeout: 5s
      retries: 5

  web:
    build: .
    container_name: industrial-monitoring-api
    restart: unless-stopped

    env_file:
      - .env.docker

    ports:
      - "8000:8000"

    depends_on:
      db:
        condition: service_healthy

volumes:
  postgres_data:
```

# Probarlo

Primero:

```d
docker compose down
```

Luego:

```d
docker compose up --build
```

Y en otra terminal:

```d
docker compose ps
```

Ahora deberías ver algo parecido a:

```
NAME                         STATUS
industrial-monitoring-db     Up (healthy)
industrial-monitoring-api   Up
```

La palabra importante es:

```
(healthy)
```

# ¿Qué conseguimos?

Ahora Docker conoce una condición real de salud:

```
                    Docker Compose
                         │
              ┌──────────┴──────────┐
              ▼                     ▼
             db                    web
              │
        healthcheck
              │
       ┌──────┴──────┐
       ▼             ▼
   unhealthy       healthy
       │             │
       │             └──────────► web puede iniciar
       │
       └──────────────► web espera
```

Esto es mucho más robusto que simplemente asumir que porque el contenedor PostgreSQL está "Up", la base de datos ya está disponible.

## ¿Y las migraciones?

Aquí tenemos otro problema interesante.

Actualmente, después de levantar Docker, podríamos necesitar ejecutar manualmente:

```
docker compose exec web python manage.py migrate
```

Funciona, pero queremos automatizarlo.

El objetivo será conseguir:

```
docker compose up
       │
       ▼
PostgreSQL healthy
       │
       ▼
Django
       │
       ├── migrate
       │
       ▼
    servidor
```