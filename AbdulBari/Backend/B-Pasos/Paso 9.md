Autenticación JWT y permisos.

Actualmente cualquiera que conozca nuestra API podría hacer:

```
POST /api/machines/
```

o:

```
DELETE /api/machines/1/
```

Eso **no es aceptable para una API real**.

Queremos pasar de:

```
Cliente
   │
   ▼
API
   │
   └── acceso libre
```

a:

```
Cliente
   │
   │ username + password
   ▼
Login
   │
   ▼
JWT Token
   │
   ▼
API
   │
   ├── autenticado?
   │       │
   │       ├── NO → 401
   │       │
   │       └── SÍ
   │
   ▼
Permisos
   │
   ├── permitido → 200/201/204
   │
   └── prohibido → 403
```

# Instalar Simple JWT

Vamos a utilizar:

```python
python -m pip install djangorestframework-simplejwt
```

Después:

```python
python -m pip freeze > requirements.txt
```

Esto actualiza nuestro `requirements.txt`.

# Configurar DRF

En:

```
config/settings.py
```

agrega:

```
REST_FRAMEWORK = {
    "DEFAULT_AUTHENTICATION_CLASSES": (
        "rest_framework_simplejwt.authentication.JWTAuthentication",
    ),
}
```

Ahora DRF sabe:

> Cuando llegue una petición, utiliza JWT para intentar identificar al usuario.


# Crear los endpoints JWT

En:

```
config/urls.py
```

agregamos:

```python
from rest_framework_simplejwt.views import (
    TokenObtainPairView,
    TokenRefreshView,
)
```

Y nuestras URLs:

```python
urlpatterns = [
    path("admin/", admin.site.urls),

    path(
        "api/",
        include("apps.machines.urls"),
    ),

    path(
        "api/",
        include("apps.sensors.urls"),
    ),

    path(
        "api/",
        include("apps.measurements.urls"),
    ),

    path(
        "api/token/",
        TokenObtainPairView.as_view(),
        name="token_obtain_pair",
    ),

    path(
        "api/token/refresh/",
        TokenRefreshView.as_view(),
        name="token_refresh",
    ),
]
```

# Crear un usuario
user=reno
email=renox164@gmail.com
password=123456789

Podemos utilizar el sistema de autenticación de Django.

Ejecuta:

```python
python manage.py createsuperuser
```

Django te preguntará:

```
Username:
Email:
Password:
Password (again):
```

Por ejemplo:

```
Username: admin
Email: admin@example.com
Password: ********
```

No necesitas crear un modelo `User` manualmente para esto.

Django ya proporciona:

```
User
├── username
├── password
├── email
├── is_staff
├── is_superuser
└── ...
```

# Obtener el JWT

Arranca Django:

```python
python manage.py runserver
```

En Postman:

```python
POST http://127.0.0.1:8000/api/token/
```

Body → raw → JSON:

```
{
    "username": "admin",
    "password": "TU_PASSWORD"
}
```

La respuesta será aproximadamente:

```
{
    "refresh": "eyJhbGciOiJIUzI1NiIs...",
    "access": "eyJhbGciOiJIUzI1NiIs..."
}
```

**No publiques esos tokens en GitHub ni los compartas.**

# ¿Para qué sirve `refresh`?

Tenemos dos tokens:

```
Access Token
Refresh Token
```

El `access` tiene una vida relativamente corta.

El `refresh` sirve para obtener otro `access` cuando este expire.

Por ejemplo:

```
Access
   │
   │ expira
   ▼
Refresh Token
   │
   ▼
Nuevo Access Token
```

Esto evita que el usuario tenga que introducir su contraseña constantemente.

# Proteger nuestra API

Ahora vamos a decirle a DRF:

> Solo usuarios autenticados pueden acceder.

En nuestro `MachineViewSet`:

```d
from rest_framework import viewsets
from rest_framework.permissions import IsAuthenticated

from apps.machines.models import Machine
from apps.machines.serializers import MachineSerializer


class MachineViewSet(viewsets.ModelViewSet):

    queryset = Machine.objects.all()
    serializer_class = MachineSerializer
    permission_classes = [IsAuthenticated]
```

Haz lo mismo inicialmente con:

```
SensorViewSet
MeasurementViewSet
AlertViewSet
MaintenanceViewSet
```


# ¿Qué ocurre ahora?

Si haces:

```d
GET /api/machines/
```

sin token:

```d
401 Unauthorized
```

Esto es correcto.

Ahora en Postman:

Authorization:

```
Type: Bearer Token
```

y colocas:

```
<tu access token>
```

Entonces:

```d
GET /api/machines/
Authorization: Bearer <token>
```

y deberías obtener:

```d
200 OK
```

# 401 vs 403

Esto debes aprenderlo muy bien.

### `401 Unauthorized`

Normalmente significa:

> No estás autenticado correctamente.

Ejemplos:

```
No token
Token inválido
Token expirado
```

---

### `403 Forbidden`

Significa:

> El servidor sabe quién eres, pero no tienes permiso para realizar esa acción.

Por ejemplo:

```
Usuario autenticado
       │
       ▼
DELETE /api/machines/1/
       │
       ▼
¿Tiene permiso?
       │
       └── NO
            │
            ▼
           403
```

Esta diferencia aparecerá muchísimo en entrevistas de backend/SDET.

# Primer objetivo de esta sesión

Por ahora **no vamos a crear permisos complejos**.

Primero quiero que consigamos esto:

```d
┌─────────────────────────────┐
│       POST /api/token/      │
│                             │
│ username + password         │
└──────────────┬──────────────┘
               │
               ▼
          JWT tokens
               │
               ▼
┌─────────────────────────────┐
│ GET /api/machines/          │
│                             │
│ Authorization: Bearer ...   │
└──────────────┬──────────────┘
               │
               ▼
          IsAuthenticated
               │
          ┌────┴────┐
          │         │
       token       no token
          │         │
          ▼         ▼
        200       401
```