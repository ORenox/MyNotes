
Actualmente tenemos algo parecido a esto en `settings.py`:

```d
"NAME": "industrial_monitoring",
"USER": "django",
"PASSWORD": "django_password",
"HOST": "localhost",
"PORT": "5432",
```

Para aprendizaje inicial estuvo bien.

**Pero antes de considerar el repositorio profesional y hacer el commit de esta configuración, vamos a mover las credenciales a variables de entorno.**

La arquitectura final será:

```
.env
 │
 ├── POSTGRES_DB
 ├── POSTGRES_USER
 ├── POSTGRES_PASSWORD
 └── ...
        │
        ▼
   Django settings
        │
        ▼
   PostgreSQL
```

Y:

```
.env
```

ya está en nuestro `.gitignore`.

- **Git local**: podemos hacer commits durante el desarrollo.
- **Repositorio remoto/GitHub**: antes de subirlo, debemos asegurarnos de que no haya secretos.

## Primero: dejemos el proyecto seguro

Antes del commit, vamos a sacar de `settings.py` cualquier secreto:

- `SECRET_KEY`
- contraseña de PostgreSQL
- cualquier API key futura
- tokens
- credenciales

Y mantener:

```
.env
```

Ya lo tenemos, así que perfecto.

La estructura debería quedar aproximadamente:

```d
industrial-monitoring/
│
├── .env                  # NO se sube
├── .gitignore
├── requirements.txt
├── docker-compose.yml
├── manage.py
│
├── config/
│   ├── settings.py
│   └── urls.py
│
└── apps/
    ├── machines/
    ├── sensors/
    ├── measurements/
    ├── alerts/
    └── maintenance/
```

# Vamos a usar `.env`

Instalamos:

```python
python -m pip install python-dotenv
```
**`python-dotenv` no crea ningún archivo automáticamente.** Es una librería que permite que Django lea variables desde un archivo que tú creas.

instalaste una librería dentro de tu entorno virtual:

```d
.venv/
└── ...
    └── dotenv
```

No esperes que aparezca un `.env` en tu proyecto.

Nosotros debemos crear ese archivo.

Después:

```python
python -m pip freeze > requirements.txt
```

En la raíz:

```python
.env
```

Por ejemplo:

```python
DJANGO_SECRET_KEY=tu-clave-secreta
POSTGRES_DB=industrial_monitoring
POSTGRES_USER=django
POSTGRES_PASSWORD=django_password
POSTGRES_HOST=localhost
POSTGRES_PORT=5432
```

**Ese archivo NO se sube a GitHub.**
## Crea `.env`

En la **raíz del proyecto**, al mismo nivel que `manage.py`:

```
industrial-monitoring/
│
├── .env                  ← crear
├── .env.example          ← crear
├── .gitignore
├── manage.py
├── requirements.txt
├── docker-compose.yml
│
├── config/
│   ├── settings.py
│   └── urls.py
│
└── apps/
    ├── machines/
    ├── sensors/
    ├── measurements/
    ├── alerts/
    └── maintenance/
```

### `.env`

Este contiene los **valores reales**:

```d
DJANGO_SECRET_KEY=tu-clave-secreta-real
POSTGRES_DB=industrial_monitoring
POSTGRES_USER=django
POSTGRES_PASSWORD=django_password
POSTGRES_HOST=localhost
POSTGRES_PORT=5432
```

⚠️ Este archivo **NO se sube a GitHub**.

Ya tenemos en `.gitignore`:

```
.env
```

Así que perfecto.

# `.env.example` sí se sube

Creamos:

```
.env.example
```

Pero sin secretos reales:

```
DJANGO_SECRET_KEY=
POSTGRES_DB=industrial_monitoring
POSTGRES_USER=django
POSTGRES_PASSWORD=
POSTGRES_HOST=localhost
POSTGRES_PORT=5432
```

Esto sirve para que otra persona pueda clonar el proyecto y entender qué variables necesita.

La diferencia es:

```
.env
   ↓
valores reales
   ↓
❌ NO GitHub


.env.example
   ↓
plantilla
   ↓
✅ GitHub
```

# Cambiar `settings.py`

En lugar de:

```
SECRET_KEY = "django-insecure-..."
```

utilizaremos:

```python
import os

from dotenv import load_dotenv

load_dotenv()

SECRET_KEY = os.getenv("DJANGO_SECRET_KEY")
```

Y PostgreSQL:

```python
DATABASES = {
    "default": {
        "ENGINE": "django.db.backends.postgresql",
        "NAME": os.getenv("POSTGRES_DB"),
        "USER": os.getenv("POSTGRES_USER"),
        "PASSWORD": os.getenv("POSTGRES_PASSWORD"),
        "HOST": os.getenv("POSTGRES_HOST"),
        "PORT": os.getenv("POSTGRES_PORT"),
    }
}
```

Ahora las credenciales ya no están escritas directamente en `settings.py`.

# Importante: Docker también necesita las variables

Aquí hay una pequeña mejora respecto a nuestro `docker-compose.yml` inicial.

En vez de:

```python
environment:
  POSTGRES_DB: industrial_monitoring
  POSTGRES_USER: django
  POSTGRES_PASSWORD: django_password
```

podemos hacer:

```d
environment:
  POSTGRES_DB: ${POSTGRES_DB}
  POSTGRES_USER: ${POSTGRES_USER}
  POSTGRES_PASSWORD: ${POSTGRES_PASSWORD}
```

Docker Compose leerá esas variables desde `.env`.

Así tenemos:

```
                    .env
                  /      \
                 /        \
                ▼          ▼
          Django settings  Docker Compose
                │              │
                ▼              ▼
              Django       PostgreSQL
```

Esto es mucho más cercano a cómo queremos manejar configuración real.


## Una cosa importante antes de continuar

No borres todavía tu configuración anterior de PostgreSQL.

Primero crea:

```
.env
.env.example
```

y configura `settings.py`.

Después ejecuta:

```python
python manage.py check
```

y:

```python
python manage.py migrate
```

Si ambos funcionan, sabremos que Django está leyendo correctamente las variables.

Después hacemos una comprobación de Git:

```python
git status
git status --ignored
```

y verificamos que `.env` esté siendo ignorado **antes de hacer nuestro commit**.

# Git ignore
**Antes de ejecutar `git commit`, mira la lista.**

No queremos ver:

```d
.env
.venv/
__pycache__/
*.pyc
```

# Nuestro primer commit importante

Una vez verificado:

```
git commit -m "feat: add JWT authentication"
```


# Proximos commits
Podemos mantener algo parecido a esto:

```
feat: add JWT authentication
feat: add API permissions
feat: add OpenAPI documentation
test: add API tests
chore: containerize application
ci: add GitHub Actions pipeline
chore: prepare production deployment
docs: improve project documentation
```