### Sí se sube

```
tests/
├── __init__.py
├── conftest.py
├── test_basic.py
├── test_machines.py
├── test_sensors.py
├── test_measurements.py
├── test_authentication.py
└── test_permissions.py
```

También:

```
pytest.ini
requirements.txt
```

### No se sube

```
.coverage
htmlcov/
```

Y ya tienes que evitar:

```
.env
.venv/
__pycache__/
```


Por eso nuestro `.gitignore` debería terminar incluyendo:

```
# Python
__pycache__/
*.py[cod]

# Virtual environment
.venv/

# Django
db.sqlite3
*.log

# Environment variables
.env

# IDE
.vscode/
.idea/

# OS
.DS_Store
Thumbs.db

# Coverage
.coverage
htmlcov/
```


Los `.pyc` son archivos compilados que Python genera automáticamente cuando ejecutas código `.py`.

Por ejemplo:

```
apps/machines/__pycache__/
├── __init__.cpython-314.pyc
└── models.cpython-314.pyc
```

No necesitas versionarlos porque Git debe guardar el **código fuente `.py`**, no esos archivos generados.

Tu `.gitignore` ya lo cubre con:

```
__pycache__/
*.py[cod]
```

La segunda línea incluye:

```
.pyc
.pyo
.pyd
```

Así que, por ejemplo:

```
models.py        → ✅ Git
models.pyc       → ❌ Git
__pycache__/     → ❌ Git
```