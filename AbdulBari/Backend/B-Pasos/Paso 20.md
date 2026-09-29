Ahora viene el concepto clave de Docker Compose: **dentro de Docker, `localhost` cambia de significado**.

## Conectar Django con PostgreSQL dentro de Compose

Actualmente tu `settings.py` tiene:

```d
"HOST": os.getenv("POSTGRES_HOST"),
"PORT": os.getenv("POSTGRES_PORT"),
```

Y en tu `.env` tienes:

```d
POSTGRES_HOST=localhost
POSTGRES_PORT=5432
```

Eso funciona cuando Django corre directamente en tu máquina:

```
Tu PC
│
├── Django
│    │
│    └── localhost:5432
│              │
│              ▼
│        PostgreSQL Docker
```

Pero cuando **Django también esté dentro de Docker**, tendremos:

```
Docker
│
├── django
│
└── db
```

Desde el contenedor `django`, esto:

```
localhost
```

significa:

> **el propio contenedor Django**

No significa el contenedor PostgreSQL.

Por eso necesitamos utilizar el **nombre del servicio de Compose**:

```
db
```

La comunicación será:

```
django
  │
  │ PostgreSQL:5432
  ▼
 db
```


# Separar configuración local y Docker

Para no destruir tu configuración actual, vamos a utilizar dos archivos de entorno.

Tu `.env` puede quedar para ejecutar Django directamente desde tu máquina:

```d
DJANGO_SECRET_KEY=tu-clave-secreta-real

POSTGRES_DB=industrial_monitoring
POSTGRES_USER=django
POSTGRES_PASSWORD=django_password
POSTGRES_HOST=localhost
POSTGRES_PORT=5432
```

Y vamos a crear:

```d
.env.docker
```

con:

```d
DJANGO_SECRET_KEY=tu-clave-secreta-real

POSTGRES_DB=industrial_monitoring
POSTGRES_USER=django
POSTGRES_PASSWORD=django_password
POSTGRES_HOST=db
POSTGRES_PORT=5432
```

La diferencia importante es solamente:

```d
.env
       POSTGRES_HOST=localhost

.env.docker
       POSTGRES_HOST=db
```

Porque `db` es el nombre del servicio PostgreSQL en Compose.

### ⚠️ Pero `env_file` y `.env` tienen roles distintos

Docker Compose puede cargar variables de un archivo mediante:

```
env_file:
  - .env.docker
```

Mientras que `${POSTGRES_DB}` dentro de `docker-compose.yml` utiliza las variables que Compose tiene disponibles para interpolación.

Para evitar confusiones en esta primera versión, vamos a hacer que Compose pase explícitamente el archivo `.env.docker` al contenedor Django.

# Modificar `docker-compose.yml`

Ahora reemplaza tu `docker-compose.yml` por:

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

  web:
    build: .
    container_name: industrial-monitoring-api
    restart: unless-stopped
    env_file:
      - .env.docker
    ports:
      - "8000:8000"
    depends_on:
      - db

volumes:
  postgres_data:
```

Ahora tenemos dos servicios:

```
services
│
├── db
│   └── PostgreSQL
│
└── web
    └── Django
```

# ¿Qué hace `depends_on`?

Tenemos:

```
depends_on:
  - db
```

Esto indica que Compose debe iniciar el servicio `db` antes de iniciar `web`.

Pero hay una distinción importante:

> `depends_on` controla el **orden de inicio**, no garantiza que PostgreSQL ya esté completamente listo para aceptar conexiones.

Más adelante, si queremos hacerlo más robusto, podemos añadir un `healthcheck`.

Por ahora nos interesa entender la arquitectura.

# Agrega `.env.docker` al `.gitignore`

Como contiene la contraseña real:

```
.env
.env.docker
```

Y actualiza `.env.example` para documentar que Docker necesita:

```d
DJANGO_SECRET_KEY=

POSTGRES_DB=industrial_monitoring
POSTGRES_USER=django
POSTGRES_PASSWORD=
POSTGRES_HOST=db
POSTGRES_PORT=5432
```

No pongas la contraseña real en `.env.example`.

# Levantar los servicios

Primero detén cualquier contenedor anterior:

```d
docker compose down
```

Después:

```d
docker compose up --build
```

El `--build` es importante porque modificamos el `Dockerfile`.

Deberías terminar teniendo algo parecido a:

```d
industrial-monitoring-api
industrial-monitoring-db
```

Puedes comprobarlo desde otra terminal:

```d
docker compose ps
```

# Probar Django

Ahora abre:

```python
http://localhost:8000
```

Y también:

```d
http://localhost:8000/api/docs/
```

La diferencia conceptual es muy importante:

```
TU PC
│
│ localhost:8000
▼
┌──────────────────────── Docker ────────────────────────┐
│                                                        │
│   web                                                  │
│   Django                                               │
│     │                                                  │
│     │ db:5432                                          │
│     ▼                                                  │
│   db                                                   │
│   PostgreSQL                                           │
│                                                        │
└────────────────────────────────────────────────────────┘
```

Desde tu navegador:

```
localhost:8000
```

sí funciona porque estás entrando desde **tu máquina hacia el puerto publicado del contenedor**.

Pero desde Django:

```
POSTGRES_HOST=db
```

porque Django está hablando **desde un contenedor hacia otro contenedor**.

---

### Una última comprobación

Ejecuta:

```d
docker compose ps
```

y:

```d
docker compose logs web
```

Si Django arranca correctamente y puedes acceder a `/api/docs/`, tenemos la parte fundamental de la Sesión 10 funcionando.

Después hacemos el siguiente paso: **healthcheck de PostgreSQL + migraciones automáticas al levantar el contenedor**, que es donde empezamos a convertir esto en una configuración más profesional.