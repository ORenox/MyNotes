
## Haz el push

```
git push origin main
```

Esto enviará tu nuevo workflow:

```
.github/
└── workflows/
    └── ci.yml
```

a GitHub.

## Ve a GitHub → Actions

En tu repositorio:

```
GitHub
  └── Actions
```

Deberías encontrar algo como:

```
CI
```

y una ejecución asociada a tu `push`.

El flujo será:

```
push
 │
 ▼
GitHub Actions
 │
 ├── Checkout
 ├── Python 3.13
 ├── PostgreSQL 17
 ├── pip install
 ├── manage.py check
 ├── manage.py migrate
 └── pytest
```

## Entender el resultado

Si todo funciona:

```
✓ CI
  ✓ test
```

Pipeline verde.

Eso significa que GitHub pudo:

1. Obtener tu código.
2. Preparar Python.
3. Levantar PostgreSQL.
4. Instalar tus dependencias.
5. Ejecutar los checks de Django.
6. Ejecutar las migraciones.
7. Ejecutar tus tests.

Es una comprobación bastante buena de que el repositorio es reproducible.

# Algo que quiero que observes

Hay una diferencia interesante entre nuestros dos entornos:

### Local

```
Docker Compose
│
├── Django container
└── PostgreSQL container
```

### GitHub Actions

```
GitHub Actions
│
├── Ubuntu runner
│   └── Django + pytest
│
└── PostgreSQL service
```

No estamos ejecutando nuestro `docker-compose.yml` dentro del workflow todavía.

Y eso está bien.

Estamos aprendiendo primero **CI**, no intentando automatizar absolutamente todo de golpe.

# Nuestro pipeline actual

Conceptualmente tenemos:

```
                 Git
                  │
                  │ push
                  ▼
               GitHub
                  │
                  ▼
          ┌───────────────┐
          │ GitHub Actions│
          └───────┬───────┘
                  │
          ┌───────┴────────┐
          ▼                ▼
       Python           PostgreSQL
          │                │
          └───────┬────────┘
                  ▼
                pytest
                  │
             ┌────┴────┐
             ▼         ▼
           PASS       FAIL
```

Esto ya es un **pipeline CI funcional**.

### En Docker Compose

Tienes:

```
ports:
  - "5433:5432"
```

Esto significa:

```
TU PC                         CONTENEDOR
localhost:5433  ────────────> PostgreSQL:5432
```

Por tanto, **desde tu máquina**, Django debe usar:

```
POSTGRES_HOST=localhost
POSTGRES_PORT=5433
```

Eso está correcto.

### Pero dentro de Docker Compose es diferente

Tu servicio `web` se conecta al servicio `db` directamente por la red interna de Docker.

Por eso:

```
POSTGRES_HOST=db
POSTGRES_PORT=5432
```

es lo correcto para Django **dentro del contenedor**.

El `5433` solo es el puerto publicado hacia tu máquina.

```
                    Docker
┌─────────────────────────────────────────┐
│                                         │
│  web                                    │
│   │                                     │
│   │ db:5432                             │
│   ▼                                     │
│  PostgreSQL                             │
│   │                                     │
│   └──────────────► 5432                 │
│                                         │
└─────────────────────────────────────────┘
                    ▲
                    │
              localhost:5433
                    │
                 Tu PC
```

## Y aquí está el problema con GitHub Actions

En GitHub Actions tenemos:

```
services:
  postgres:
    ports:
      - 5432:5432
```

y Django corre **directamente en el runner**, no dentro de un contenedor.

Por tanto, debería conectarse a:

```
localhost:5432
```

No a `5433`.

Si en tu workflow tienes:

```
POSTGRES_PORT: 5433
```

entonces sí: **estaría mal para GitHub Actions**.

Pero el error que mostraste es todavía más interesante:

```
connection to server on socket "/var/run/postgresql/.s.PGSQL.5432"
```

Eso indica que Django está recibiendo un `HOST` vacío o no está leyendo `POSTGRES_HOST` como esperábamos.1

## Errores que cometí

Actualmente tienes:

```d
POSTGREES_HOST: localhost
POSGRES_PORT: 5432
```

Pero Django busca exactamente:

```d
os.getenv("POSTGRES_HOST")
os.getenv("POSTGRES_PORT")
```

Las variables de entorno deben coincidir **exactamente**.

### Corrige esto

Cambia:

```d
env:
  DJANGO_SECRET_KEY: test-secret-key
  POSTGRES_DB: industrial_monitoring
  POSTGRES_USER: django
  POSTGRES_PASSWORD: django_password
  POSTGREES_HOST: localhost
  POSGRES_PORT: 5432
```

por:

```d
env:
  DJANGO_SECRET_KEY: test-secret-key
  POSTGRES_DB: industrial_monitoring
  POSTGRES_USER: django
  POSTGRES_PASSWORD: django_password
  POSTGRES_HOST: localhost
  POSTGRES_PORT: 5432
```

Los dos errores eran:

```
POSTGREES_HOST ❌
POSTGRES_HOST  ✅

POSGRES_PORT   ❌
POSTGRES_PORT  ✅
```

Por eso tu prueba anterior devolvió:

```
POSTGRES_HOST= None
POSTGRES_PORT= None
```