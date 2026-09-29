Crear el proyecto Django, entorno virtual, Git y Docker.

La meta de hoy será dejar esta estructura funcionando:

```
industrial-monitoring/
├── .venv/
├── config/
├── apps/
├── manage.py
├── .gitignore
├── requirements.txt
└── README.md
```

Y al terminar tendremos:

# Crear el entorno virtual

Esto es importante.

No queremos instalar Django directamente en todo tu sistema. Queremos que las dependencias pertenezcan exclusivamente a este proyecto.

```python
python -m venv .venv
```

Tendrás:

```
industrial-monitoring/
└── .venv/
```

# Activar el entorno virtual

#### Windows — PowerShell

```
.venv\Scripts\Activate.ps1
```

#### Windows — CMD

```
.venv\Scripts\activate
```

#### Linux / macOS

```python
source .venv/bin/activate
```

Si funcionó, deberías ver algo parecido a:

```
(.venv) C:\...\industrial-monitoring>
```

El `(.venv)` es importante: significa que estamos trabajando dentro del entorno virtual.


# Comprobar Python

Ejecuta:

```
python --version
```

Idealmente tendremos Python 3.12 o 3.13.

Después:

```
python -m pip --version
```

Esto comprueba que `pip` pertenece a nuestro entorno virtual.


# Instalar Django

Ahora sí:

```
python -m pip install django
```

Comprueba:

```
django-admin --version
```

Deberías obtener una versión de Django.


# Guardar las dependencias

Ahora ejecuta:

```python
python -m pip freeze > requirements.txt
```

Se creará:

```
industrial-monitoring/
├── .venv/
└── requirements.txt
```

El archivo permite que otra persona pueda instalar las mismas dependencias con:

```
pip install -r requirements.txt
```

Más adelante agregaremos DRF, pytest, PostgreSQL, etc.


# Crear el proyecto Django

Aquí hay un detalle importante de Django.

Vamos a llamar a nuestro proyecto interno:

```
config
```

Ejecuta:

```python
django-admin startproject config .
```

El `.` del final es importante.

La estructura será:

```
industrial-monitoring/
│
├── .venv/
│
├── config/
│   ├── __init__.py
│   ├── settings.py
│   ├── urls.py
│   ├── asgi.py
│   └── wsgi.py
│
├── manage.py
└── requirements.txt
```

### ¿Qué acaba de crear Django?

Esta parte es importante para aprender, no solamente para copiar comandos.

### `manage.py`

Es nuestra herramienta principal para administrar Django.

Por ejemplo:

```python
python manage.py runserver
```

```python
python manage.py makemigrations
```

```python
python manage.py migrate
```

```python
python manage.py createsuperuser
```

---

### `settings.py`

Aquí estará la configuración del proyecto:

```
Base de datos
Apps
Middleware
Secret key
Idioma
Zona horaria
Archivos estáticos
...
```

Más adelante configuraremos PostgreSQL aquí.

---

### `urls.py`

Aquí definiremos las rutas principales de nuestra aplicación.

Por ejemplo:

```
/api/machines/
/api/sensors/
/api/measurements/
/api/alerts/
/api/maintenance/
```

---

### `asgi.py` y `wsgi.py`

Son puntos de entrada para ejecutar Django mediante servidores compatibles con ASGI/WSGI.

Por ahora no necesitamos modificar ninguno.




# Crear nuestras aplicaciones

Ahora vamos a separar nuestro proyecto por dominios.

Primero:

```
mkdir apps
```

En Linux/macOS:

```
touch apps/__init__.py
```

En PowerShell:

```
New-Item apps\__init__.py -ItemType File
```

Después vamos a crear las aplicaciones.

```
python manage.py startapp machines
python manage.py startapp sensors
python manage.py startapp measurements
python manage.py startapp alerts
python manage.py startapp maintenance
```

Pero Django las habrá creado en la raíz. Queremos organizarlas dentro de `apps/`.

Por ahora, **no muevas nada todavía**.

Primero quiero que entiendas qué estamos haciendo.

Cada app representa un dominio:

```
machines
    ↓
Máquinas industriales

sensors
    ↓
Sensores

measurements
    ↓
Mediciones

alerts
    ↓
Alertas

maintenance
    ↓
Mantenimientos
```

# Git
Inicializamos el repositorio:

```
git init
```

Comprueba:

```
git status
```

Ahora necesitamos un `.gitignore`.

Crea:

```
.gitignore
```

Y coloca:

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
```

### ¿Por qué ignoramos `.venv/`?

Porque **no debemos subir el entorno virtual a Git**.

Otra persona podrá reconstruirlo usando:

```
pip install -r requirements.txt
```

# Primer arranque de Django

Ahora viene nuestra primera prueba.

Ejecuta:

```python
python manage.py runserver
```

Deberías ver algo parecido a:

```
Starting development server at http://127.0.0.1:8000/
```

Abre en el navegador:

```
http://127.0.0.1:8000/
```

Si aparece la página de bienvenida de Django:

# Primera comprobación

Antes de continuar, quiero que hagamos algo muy parecido a una prueba de ingeniería.

Ejecuta:

```python
python manage.py check
```

Django debería responder:

```
System check identified no issues (0 silenced).
```

Esto es importante porque posteriormente nuestro CI ejecutará comprobaciones y tests automáticamente.

# Primera versión de Git

Comprueba:

```
git status
```

Después:

```
git add .
```

Y:

```
git commit -m "chore: initialize Django project"
```

Ahora tenemos nuestro primer checkpoint:

```
v0
│
├── Python environment
├── Django
├── Project structure
├── Git
└── Django server
```