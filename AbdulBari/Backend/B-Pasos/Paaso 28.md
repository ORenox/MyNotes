La idea no es simplemente "subir Django a internet". Queremos entender **cómo convertir lo que construimos en un proyecto presentable profesionalmente**.

La arquitectura final que buscamos será aproximadamente:

```
Industrial-Monitoring-API/
│
├── .github/
│   └── workflows/
│       └── ci.yml
│
├── apps/
│   ├── machines/
│   ├── sensors/
│   ├── measurements/
│   ├── alerts/
│   └── maintenance/
│
├── config/
│   ├── settings.py
│   └── urls.py
│
├── tests/
│
├── .dockerignore
├── .gitignore
├── .env.example
├── Dockerfile
├── docker-compose.yml
├── entrypoint.sh
├── manage.py
├── pytest.ini
├── README.md
└── requirements.txt
```

Y conceptualmente:

```
                    GitHub
                      │
                      │ deploy
                      ▼
              ┌───────────────┐
              │   Application │
              │    Django     │
              │      + DRF    │
              └───────┬───────┘
                      │
                      ▼
               ┌─────────────┐
               │ PostgreSQL  │
               └─────────────┘
```

## Primero: separar desarrollo de producción

Antes de desplegar, hay una diferencia fundamental que quiero que entiendas.

Actualmente tenemos cosas como:

```
DEBUG = True
```

y posiblemente:

```
ALLOWED_HOSTS = []
```

Eso está bien para desarrollo, pero **no debería ser nuestra configuración de producción**.

En producción queremos, como mínimo:

```
DEBUG = False
```

y hosts explícitamente permitidos.

Además, nuestro `SECRET_KEY` ya está correctamente externalizado mediante variables de entorno.

# Revisar `settings.py`

Abre:

```
config/settings.py
```

Busca:

```
DEBUG = True
```

Vamos a cambiarlo para que dependa de una variable de entorno:

```
DEBUG = os.getenv("DJANGO_DEBUG", "False") == "True"
```

Esto hace:

```
DJANGO_DEBUG=True
       ↓
DEBUG = True
```

y:

```
DJANGO_DEBUG=False
       ↓
DEBUG = False
```

### ¿Por qué es mejor?

Porque no queremos modificar código cada vez que pasamos de desarrollo a producción.

El código permanece igual:

```
Código Django
     │
     ├── desarrollo → variables de entorno
     │
     └── producción → variables de entorno
```

## `ALLOWED_HOSTS`

Busca:

```
ALLOWED_HOSTS = []
```

y cámbialo a:

```
ALLOWED_HOSTS = os.getenv(
    "DJANGO_ALLOWED_HOSTS",
    "localhost,127.0.0.1"
).split(",")
```

Así, localmente tendremos:

```
localhost
127.0.0.1
```

y posteriormente, cuando tengamos un dominio, podremos configurar:

```d
DJANGO_ALLOWED_HOSTS=localhost,127.0.0.1,mi-dominio.com
```

sin modificar el código.

## Actualizar `.env.example`

Actualmente tienes algo parecido a:

```
DJANGO_SECRET_KEY=

POSTGRES_DB=industrial_monitoring
POSTGRES_USER=django
POSTGRES_PASSWORD=
POSTGRES_HOST=localhost
POSTGRES_PORT=5433
```

Agrega:

```
DJANGO_DEBUG=False
DJANGO_ALLOWED_HOSTS=localhost,127.0.0.1
```

Por ejemplo:

```
DJANGO_SECRET_KEY=

DJANGO_DEBUG=False
DJANGO_ALLOWED_HOSTS=localhost,127.0.0.1

POSTGRES_DB=industrial_monitoring
POSTGRES_USER=django
POSTGRES_PASSWORD=
POSTGRES_HOST=localhost
POSTGRES_PORT=5433
```

Recuerda:

```
.env.example   → SÍ Git
.env           → NO Git
.env.docker    → NO Git
```


## Una observación importante

Tu `.env` real puede seguir teniendo:

```
POSTGRES_PORT=5433
```

porque ese es **tu entorno local**.

No estamos cambiando eso.

La configuración de GitHub Actions sigue siendo:

```
POSTGRES_PORT: 5432
```

Y Docker interno:

```
POSTGRES_PORT=5432
```

Esto es exactamente el tipo de separación que queremos conseguir en una aplicación profesional.

### Por qué `True` en tu `.env`?

Porque estás trabajando en desarrollo local:

```
.env
 │
 ├── DJANGO_DEBUG=True
 ├── POSTGRES_HOST=localhost
 └── POSTGRES_PORT=5433
```

Mientras que tu `.env.example` sirve como **plantilla para otros desarrolladores**:

```
DJANGO_SECRET_KEY=

DJANGO_DEBUG=False
DJANGO_ALLOWED_HOSTS=localhost,127.0.0.1

POSTGRES_DB=industrial_monitoring
POSTGRES_USER=django
POSTGRES_PASSWORD=
POSTGRES_HOST=localhost
POSTGRES_PORT=5433
```

Y producción podría tener:

```
DJANGO_DEBUG=False
DJANGO_ALLOWED_HOSTS=api.midominio.com
```

### GitHub Actions es independiente

Ahí podemos tener:

```
env:
  DJANGO_SECRET_KEY: test-secret-key
  DJANGO_DEBUG: "False"
  DJANGO_ALLOWED_HOSTS: localhost
  POSTGRES_DB: industrial_monitoring
  POSTGRES_USER: django
  POSTGRES_PASSWORD: django_password
  POSTGRES_HOST: localhost
  POSTGRES_PORT: 5432
```

No necesitas copiar tu `.env` a GitHub.

La idea profesional es:

```
                 MISMO CÓDIGO
                      │
        ┌─────────────┼─────────────┐
        ▼             ▼             ▼
     Local         CI/CD        Producción
        │             │             │
      .env       GitHub env      env/Secrets
        │             │             │
      5433          5432          5432*
```

* El puerto de producción dependerá de cómo despleguemos PostgreSQL.

## Revisar la configuración de producción

Antes de pensar en desplegar, vamos a hacer que Django pueda detectar problemas de configuración.

Django tiene un comando específico para esto:

```
python manage.py check --deploy
```

Ejecuta:

```
python manage.py check --deploy
```

Probablemente vas a recibir varios `WARNINGS`. **No te preocupes si aparecen**. Precisamente estamos usando este comando para descubrir qué nos falta para producción.

Podrías ver advertencias relacionadas con cosas como:

```
SecurityMiddleware
SECURE_HSTS_SECONDS
SECURE_SSL_REDIRECT
SESSION_COOKIE_SECURE
CSRF_COOKIE_SECURE
```

Eso es normal en este punto.


### ¿Por qué `check --deploy`?

Tenemos dos comandos diferentes:

```
python manage.py check
```

→ ¿La configuración de Django es válida?

Mientras que:

```
python manage.py check --deploy
```

→ ¿Hay problemas conocidos en la configuración para un entorno de producción?

Conceptualmente:

```
                    Django
                       │
             ┌─────────┴─────────┐
             ▼                   ▼
          check              check --deploy
             │                   │
       configuración        configuración
          válida             producción
```

## No vamos a activar todas las recomendaciones todavía

Esto es importante.

Si ejecutas:

```
python manage.py check --deploy
```

Django puede recomendar configuraciones de seguridad que **tienen sentido cuando realmente estamos detrás de HTTPS**, por ejemplo:

```
SECURE_SSL_REDIRECT = True
```

Pero todavía estamos trabajando localmente con:

```
http://localhost:8000
```

Si activamos ciertas opciones prematuramente, podemos romper nuestro entorno de desarrollo.

Por eso vamos a distinguir:

### Desarrollo

```
HTTP
localhost
DEBUG=True
```

### Producción

```
HTTPS
dominio real
DEBUG=False
secretos reales
cookies seguras
```

No queremos mezclar ambas configuraciones.### Desarrollo

```
HTTP
localhost
DEBUG=True
```

### Producción

```
HTTPS
dominio real
DEBUG=False
secretos reales
cookies seguras
```

No queremos mezclar ambas configuraciones.

# Preparar `README.md`

Esta es una parte **muy importante para tu portfolio**.

Tu código puede estar muy bien hecho, pero cuando alguien entra al repositorio necesita entender rápidamente:

1. ¿Qué es?
2. ¿Qué tecnologías utiliza?
3. ¿Cómo se ejecuta?
4. ¿Cómo se prueban los endpoints?
5. ¿Cómo se ejecutan los tests?
6. ¿Cómo funciona Docker?
7. ¿Qué hace CI?

La estructura que te recomiendo es:

```
README.md

# Industrial Monitoring API

## Description

## Architecture

## Technologies

## Features

## Project Structure

## Requirements

## Local Setup

## Docker

## API

## Authentication

## Testing

## CI/CD

## Environment Variables

## Future Improvements
```