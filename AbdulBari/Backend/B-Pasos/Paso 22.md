Pero todavía tenemos que ejecutar manualmente:

```d
docker compose exec web python manage.py migrate
```

Vamos a automatizarlo.

## Crear `entrypoint.sh`

En la raíz del proyecto, al mismo nivel que `Dockerfile`:

```d
industrial-monitoring/
├── Dockerfile
├── docker-compose.yml
├── entrypoint.sh       ← nuevo
├── manage.py
├── requirements.txt
└── ...
```

Crea `entrypoint.sh`:

```bash
#!/bin/sh

set -e

echo "Applying database migrations..."

python manage.py migrate

echo "Starting Django server..."

exec "$@"
```

### ¿Qué hace?

Primero:

```
python manage.py migrate
```

y después:

```
exec "$@"
```

ejecuta el comando que Docker le entregue.

Nuestro `Dockerfile` tiene:

```
CMD ["python", "manage.py", "runserver", "0.0.0.0:8000"]
```

Así que finalmente tendremos:

```
entrypoint.sh
     │
     ├── migrate
     │
     └── exec "$@"
              │
              ▼
     python manage.py runserver
```


# Modificar el Dockerfile

Ahora modifica:

```d
FROM python:3.13-slim

WORKDIR /app

COPY requirements.txt .

RUN pip install --no-cache-dir -r requirements.txt

COPY . .

EXPOSE 8000

CMD ["python", "manage.py", "runserver", "0.0.0.0:8000"]
```

para que quede:

```d
FROM python:3.13-slim

WORKDIR /app

COPY requirements.txt .

RUN pip install --no-cache-dir -r requirements.txt

COPY . .

RUN chmod +x entrypoint.sh

EXPOSE 8000

ENTRYPOINT ["./entrypoint.sh"]

CMD ["python", "manage.py", "runserver", "0.0.0.0:8000"]
```

Hay una diferencia importante entre:

```
ENTRYPOINT
```

y:

```
CMD
```

En nuestro caso:

```d
ENTRYPOINT
    │
    ▼
entrypoint.sh
    │
    ├── migrate
    │
    └── ejecuta CMD
             │
             ▼
        runserver
```

# ¿Por qué `exec "$@"`?

Esta línea:

```
exec "$@"
```

significa aproximadamente:

> "Reemplaza este proceso por el comando recibido."

En nuestro caso será:

```
python manage.py runserver 0.0.0.0:8000
```

Es una práctica habitual en entrypoints porque permite que el proceso principal de Django reciba correctamente señales del sistema, por ejemplo cuando Docker detiene el contenedor.

# Reconstruir la imagen

Como modificamos el `Dockerfile` y agregamos un archivo nuevo:

```
docker compose down
```

Después:

```
docker compose up --build
```

Ahora deberías ver en los logs algo parecido a:

```
Applying database migrations...
Operations to perform:
  Apply all migrations: ...
Running migrations:
  ...
Starting Django server...
```

Y luego:

```
Starting development server at http://0.0.0.0:8000/
```

# Comprobar que realmente funcionó

Puedes ejecutar:

```d
docker compose ps
```

y:

```d
docker compose logs web
```

También puedes comprobar las migraciones directamente dentro del contenedor:

```
docker compose exec web python manage.py showmigrations
```

Deberías ver las migraciones marcadas con:

```
[X]
```

## Algo importante para tu arquitectura

Ahora nuestro flujo es bastante más completo:

```
                 docker compose up
                        │
                        ▼
                 PostgreSQL inicia
                        │
                        ▼
                  healthcheck
                        │
                        ▼
                  DB healthy
                        │
                        ▼
                 Django inicia
                        │
                        ▼
              entrypoint.sh
                        │
                        ▼
              python manage.py migrate
                        │
                        ▼
             python manage.py runserver
                        │
                        ▼
                   API :8000
```

### Una precisión profesional

Estamos usando `runserver` porque **este proyecto está en etapa de desarrollo**. En producción no usaríamos `runserver`; normalmente utilizaríamos un servidor WSGI/ASGI como Gunicorn o Uvicorn según la aplicación.