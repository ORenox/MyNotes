

```
Sesión 2
Django ───────► PostgreSQL
                 │
              Docker
              (solo DB)


Sesión 10
┌─────────────────────────────────┐
│        Docker Compose           │
│                                 │
│  ┌─────────────┐ ┌───────────┐ │
│  │   Django    │ │ PostgreSQL│ │
│  │   API       │ │    DB     │ │
│  └─────────────┘ └───────────┘ │
│          │             │        │
│          └─────────────┘        │
└─────────────────────────────────┘
```

Al terminar podremos levantar todo con:

```
docker compose up
```

y tendremos:

```
Django API
    │
    ▼
PostgreSQL
```

sin necesitar ejecutar Django directamente desde tu máquina.

# Primero: entender qué tenemos actualmente

Ahora mismo tu `docker-compose.yml` probablemente tiene solamente PostgreSQL:

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

volumes:
  postgres_data:
```

Y Django se ejecuta fuera de Docker:

```d
Tu PC
│
├── Python
├── .venv
│
└── Django
       │
       │ localhost:5432
       ▼
┌─────────────────┐
│ Docker          │
│ PostgreSQL      │
└─────────────────┘
```

Ahora queremos:

```
Tu PC
│
└── Docker Compose
       │
       ├── django
       │      │
       │      ▼
       │   PostgreSQL
       │
       └── db
```

# ¿Por qué necesitamos un Dockerfile?

Docker Compose **orquesta contenedores**, pero necesitamos decirle cómo construir nuestro contenedor Django.

Para eso crearemos:

```
Dockerfile
```

El `Dockerfile` será algo parecido a una receta:

```
Dockerfile
     │
     ├── qué imagen usar
     ├── instalar dependencias
     ├── copiar proyecto
     └── ejecutar Django
```

Por ejemplo:

```
FROM python:3.13-slim
```

significa:

> "Quiero construir mi aplicación partiendo de una imagen que ya contiene Python."


# Crear `Dockerfile`

En la **raíz del proyecto**, al mismo nivel que `manage.py`:

```d
industrial-monitoring/
├── Dockerfile        ← nuevo
├── docker-compose.yml
├── manage.py
├── requirements.txt
├── .env
├── config/
├── apps/
└── tests/
```

Crea `Dockerfile`:

```d
FROM python:3.13-slim

WORKDIR /app

COPY requirements.txt .

RUN pip install --no-cache-dir -r requirements.txt

COPY . .

EXPOSE 8000

CMD ["python", "manage.py", "runserver", "0.0.0.0:8000"]
```

### ¿Qué hace cada línea?

```python
FROM python:3.13-slim
```

Imagen base.

```d
WORKDIR /app
```

Dentro del contenedor, `/app` será nuestro directorio de trabajo.

```d
COPY requirements.txt .
```

Copia las dependencias primero.

```d
RUN pip install --no-cache-dir -r requirements.txt
```

Instala Django, DRF, JWT, pytest, etc.

```d
COPY . .
```

Copia el proyecto.

```d
EXPOSE 8000
```

Documenta que la aplicación utiliza el puerto 8000.

```d
CMD [...]
```

Comando que se ejecutará cuando arranque el contenedor.

## Un detalle muy importante: `.dockerignore`

Tenemos `.gitignore`, pero **Docker tiene su propio sistema de exclusión**.

Creamos:

```d
.dockerignore
```

con:

```d
.venv/
__pycache__/
*.pyc
.git/
.gitignore
.env
.pytest_cache/
.coverage
htmlcov/
```

¿Por qué excluir `.env`?

Porque no queremos copiar secretos dentro de la imagen Docker.

La configuración seguirá llegando mediante variables de entorno.

# Construir la images


```python
docker build -t industrial-monitoring-api .
```