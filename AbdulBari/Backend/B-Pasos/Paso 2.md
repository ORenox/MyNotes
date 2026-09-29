**PostgreSQL + Docker + conexión con Django**.

Hoy vamos a conseguir esto:

```
┌──────────────────────────┐
│        Django            │
│  Python + Django ORM     │
└────────────┬─────────────┘
             │
             │ psycopg
             ▼
┌──────────────────────────┐
│       PostgreSQL         │
│       Docker             │
│                          │
│   industrial_monitoring  │
└──────────────────────────┘
```

La idea importante de esta sesión es que **Django no reemplaza a PostgreSQL**.

Django se encarga de trabajar con la base de datos mediante el ORM; **PostgreSQL es quien realmente almacena los datos**.


# ¿Por qué Docker para PostgreSQL?

Podríamos instalar PostgreSQL directamente en tu computadora.

Pero para nuestro proyecto prefiero:

```
Docker
   ↓
PostgreSQL
```

¿Por qué?

Porque no necesitas instalar/configurar PostgreSQL directamente en tu sistema.

Además, posteriormente podremos tener:

```
Docker Compose
├── Django
├── PostgreSQL
└── otros servicios
```

Y cualquier persona que clone tu proyecto podrá levantar el entorno de forma reproducible.

Esto será especialmente útil cuando lleguemos a **CI/CD**.

# Comprobar Docker

Ejecuta:

```
docker --version
```

Y:

```
docker compose version
```

Deberías obtener algo parecido a:

```
Docker version ...
Docker Compose version ...
```

Si alguno de los comandos no funciona, **no continúes todavía**. Dime qué error aparece.

# Crear `docker-compose.yml`

En la raíz del proyecto:

```
industrial-monitoring/
├── config/
├── manage.py
├── requirements.txt
├── .gitignore
└── docker-compose.yml   ← nuevo
```

Crea:

```d
services:

  db:
    image: postgres:17
    container_name: industrial-monitoring-db
    restart: unless-stopped

    environment:
      POSTGRES_DB: industrial_monitoring
      POSTGRES_USER: django
      POSTGRES_PASSWORD: django_password

    ports:
      - "5432:5432"

    volumes:
      - postgres_data:/var/lib/postgresql/data


volumes:
  postgres_data:
```

Vamos a entenderlo antes de ejecutarlo.

## `services`

```
services:
```

Aquí definimos los servicios que forman nuestro sistema.

Por ahora solamente tenemos:

```
services
   │
   └── db
        │
        └── PostgreSQL
```

Más adelante agregaremos Django:

```
services
├── web
│   └── Django
│
└── db
    └── PostgreSQL
```

## La imagen de PostgreSQL

Tenemos:

```
image: postgres:17
```

Docker va a utilizar una imagen de PostgreSQL para crear nuestro contenedor.

Conceptualmente:

```
PostgreSQL image
       ↓
Docker container
       ↓
PostgreSQL funcionando
```

No tienes que instalar PostgreSQL manualmente.

## Variables de PostgreSQL

Tenemos:

```
environment:
  POSTGRES_DB: industrial_monitoring
  POSTGRES_USER: django
  POSTGRES_PASSWORD: django_password
```

Estamos diciéndole al contenedor:

```
Database:  industrial_monitoring
User:      django
Password:  django_password
```

Por ahora están escritas directamente para aprender.

**Más adelante las moveremos a `.env`**, porque no queremos contraseñas reales dentro de Git.

## `ports`

Tenemos:

```
ports:
  - "5432:5432"
```

Esto significa:

```
Tu computadora
localhost:5432
      │
      ▼
PostgreSQL container
      │
      └── 5432
```

El puerto estándar de PostgreSQL es:

```
5432
```

## Volumen

Esta parte es MUY importante:

```
volumes:
  - postgres_data:/var/lib/postgresql/data
```

PostgreSQL guarda sus datos dentro del contenedor.

Pero imagina:

```
Container
   ↓
lo eliminas
   ↓
¿qué pasa con la DB?
```

Si no usamos persistencia, podemos perder los datos.

El volumen:

```
postgres_data
```

permite que los datos sobrevivan aunque recreemos el contenedor.

Conceptualmente:

```
Docker Container
      │
      │
      ▼
PostgreSQL
      │
      ▼
postgres_data
      │
      ▼
Datos persistentes
```

# Levantar PostgreSQL

Ahora ejecuta:

```d
docker compose up -d
```

El `-d` significa que Docker se ejecutará en segundo plano.
[[conflicto de postgres puertos]]
![[Pasted image 20260918115940.png]]
Comprueba:

```d
docker compose ps
```

Deberías ver algo parecido a:

```
NAME                          STATUS
industrial-monitoring-db     Up
```



# Ver los logs

Esto es muy útil para aprender a diagnosticar problemas.

Ejecuta:

```d
docker compose logs db
```

Si quieres seguir los logs en tiempo real:

```d
docker compose logs -f db
```

Para salir:

```
CTRL + C
```

Busca algo parecido a:

```
database system is ready to accept connections
```

Eso significa:

> PostgreSQL está funcionando y acepta conexiones.

# Instalar el driver de PostgreSQL

Hasta ahora tenemos:

```
Django
   │
   X
   │
PostgreSQL
```

Nos falta el adaptador que permite que Python/Django se comunique con PostgreSQL.

Vamos a utilizar **psycopg**.

Ejecuta:

```
python -m pip install "psycopg[binary]"
```

Después actualiza:

```
python -m pip freeze > requirements.txt
```

Ahora tu `requirements.txt` tendrá Django y psycopg, entre otras dependencias.

# Configurar Django

Abre:

```
config/settings.py
```

Busca:

```d
DATABASES = {
    "default": {
        "ENGINE": "django.db.backends.sqlite3",
        "NAME": BASE_DIR / "db.sqlite3",
    }
}
```

Eso es la configuración que Django trae por defecto.

Actualmente sería:

```
Django
  ↓
SQLite
```

Queremos:

```
Django
  ↓
PostgreSQL
```

Reemplázalo por:

```d
DATABASES = {
    "default": {
        "ENGINE": "django.db.backends.postgresql",
        "NAME": "industrial_monitoring",
        "USER": "django",
        "PASSWORD": "django_password",
        "HOST": "localhost",
        "PORT": "5432",
    }
}
```

---

```
"HOST": "localhost"
```

Como Django todavía está ejecutándose directamente en tu computadora:

```
Django
  ↓
localhost:5432
  ↓
Docker
  ↓
PostgreSQL
```

**Esto cambiará cuando metamos Django dentro de Docker.**

---

```
"PORT": "5432"
```

Puerto de PostgreSQL.

# Hacer la primera migración

Ahora viene una parte importante.

Ejecuta:

```
python manage.py migrate
```

Django debería mostrar algo parecido a:

```
Applying contenttypes.0001_initial... OK
Applying auth.0001_initial... OK
Applying admin.0001_initial... OK
Applying sessions.0001_initial... OK
...
```

¿Pero nosotros todavía no hemos creado ningún modelo?

Correcto.

Estas son tablas que Django necesita para funcionalidades propias como:
[[Conectarme a mi psql desde docker]]
![[Pasted image 20260918122150.png]]
- usuarios
- permisos
- sesiones
- administración

Por ejemplo:

```
PostgreSQL
│
├── auth_user
├── auth_group
├── django_admin_log
├── django_content_type
├── django_session
└── ...
```

**Todavía no aparecerán `machines`, `sensors`, `measurements`, etc.**

Eso lo haremos en la siguiente sesión.


# Verificar que realmente estamos usando PostgreSQL

Podemos preguntarle a Django:

```
python manage.py dbshell
```

Si todo está correctamente configurado, deberías entrar al cliente de PostgreSQL.

Podrías ver algo parecido a:

```
psql (...)
Type "help" for help.

industrial_monitoring=>
```

Ejecuta:

```
\dt
```

Deberías ver las tablas que Django creó.

Para salir:

```
\q
```

# Ahora una prueba muy importante

Detén temporalmente PostgreSQL:

```d
docker compose stop db
```

Ahora ejecuta:

```d
python manage.py migrate
```

Probablemente obtendrás un error de conexión.

¿Por qué?

Porque:

```
Django
  │
  ▼
localhost:5432
  │
  X
PostgreSQL apagado
```

Ahora vuelve a levantarlo:

```d
docker compose start db
```

Y:

```d
python manage.py migrate
```

Debería funcionar nuevamente.

Esto parece trivial, pero quiero que entiendas algo fundamental:

> **Django no contiene la base de datos. Django se conecta a un servidor de base de datos.**

# ¿Dónde está físicamente nuestra información?

Ahora tenemos tres cosas diferentes:

```
Python
│
├── Django
│
└── psycopg
        │
        ▼
     PostgreSQL
        │
        ▼
   Docker Container
        │
        ▼
   Docker Volume
```

Cada componente tiene una responsabilidad.

### Django

Maneja:

```
Models
ORM
Migrations
Views
URLs
API
Authentication
...
```

### psycopg

Permite que Python/Django hable con PostgreSQL.

### PostgreSQL

Maneja:

```
Tables
Rows
Indexes
Constraints
Transactions
Relationships
...
```

### Docker

Se encarga de empaquetar/ejecutar PostgreSQL de manera reproducible.