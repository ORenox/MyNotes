Aquí vamos a conectar todo lo que ya construimos:

```
Git
 │
 ▼
GitHub
 │
 ▼
GitHub Actions
 │
 ├── instalar dependencias
 ├── levantar PostgreSQL
 ├── ejecutar migraciones
 ├── ejecutar pytest
 └── verificar que todo funciona
```

La idea principal es que **cada vez que hagas `push` o abras un Pull Request, GitHub pueda ejecutar automáticamente tus tests**.

# ¿Qué problema resuelve CI?

Actualmente tú haces:

```
pytest -v
```

y compruebas manualmente que todo funciona.

Pero imagina que mañana haces un cambio:

```
# models.py
```

y accidentalmente rompes algo.

Podrías hacer:

```
git add .
git commit
git push
```

sin darte cuenta.

CI busca evitar esto:

```
Tú haces push
      │
      ▼
GitHub Actions
      │
      ▼
¿Los tests pasan?
   │          │
  sí          no
   │          │
   ▼          ▼
  ✓           ✗
```

# GitHub Actions

GitHub Actions utiliza archivos YAML almacenados dentro de:

```
.github/workflows/
```

Así que nuestra estructura tendrá:

```d
industrial-monitoring/
├── .github/
│   └── workflows/
│       └── ci.yml
├── apps/
├── config/
├── tests/
├── Dockerfile
├── docker-compose.yml
└── manage.py
```

Crea las carpetas:

```d
mkdir -p .github/workflows
```

En Windows PowerShell:

```
mkdir .github/workflows
```

# Nuestro primer workflow

Crea:

```
.github/workflows/ci.yml
```

Y coloca:

```d
name: CI

on:
  push:
  pull_request:

jobs:
  test:
    runs-on: ubuntu-latest

    steps:
      - name: Checkout repository
        uses: actions/checkout@v4

      - name: Set up Python
        uses: actions/setup-python@v5
        with:
          python-version: "3.13"

      - name: Install dependencies
        run: |
          python -m pip install --upgrade pip
          pip install -r requirements.txt

      - name: Run Django checks
        env:
          DJANGO_SECRET_KEY: test-secret-key
          POSTGRES_DB: industrial_monitoring
          POSTGRES_USER: django
          POSTGRES_PASSWORD: django_password
          POSTGRES_HOST: localhost
          POSTGRES_PORT: 5432
        run: |
          python manage.py check

      - name: Run tests
        env:
          DJANGO_SECRET_KEY: test-secret-key
          POSTGRES_DB: industrial_monitoring
          POSTGRES_USER: django
          POSTGRES_PASSWORD: django_password
          POSTGRES_HOST: localhost
          POSTGRES_PORT: 5432
        run: |
          pytest -v
```

Ahora vamos a entenderlo antes de ejecutarlo.

# Checkout

```
- name: Checkout repository
  uses: actions/checkout@v4
```

Esto descarga nuestro repositorio dentro de la máquina de GitHub.

Sin esto, el runner no tendría:

```
manage.py
apps/
tests/
requirements.txt
```

# Instalar Python

```
- name: Set up Python
  uses: actions/setup-python@v5
  with:
    python-version: "3.13"
```

Le decimos:

> Necesito Python 3.13.

Es importante que CI utilice una versión compatible con nuestro proyecto.

# Instalar dependencias

```
- name: Install dependencies
  run: |
    python -m pip install --upgrade pip
    pip install -r requirements.txt
```

Esto reproduce aproximadamente lo que hacemos localmente:

```
pip install -r requirements.txt
```

Por eso `requirements.txt` es importante.

# Django necesita configuración

Aquí aparece algo que ya conocemos.

Nuestro `settings.py` utiliza:

```
os.getenv("DJANGO_SECRET_KEY")
os.getenv("POSTGRES_DB")
os.getenv("POSTGRES_USER")
...
```

GitHub no tiene nuestro `.env`.

Y **no debemos subir `.env` a GitHub**.

Por eso en CI proporcionamos variables específicamente para el workflow:

```
env:
  DJANGO_SECRET_KEY: test-secret-key
```

Estas son credenciales de **testing**, no tus credenciales reales.