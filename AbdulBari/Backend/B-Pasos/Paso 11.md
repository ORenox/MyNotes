## Objetivo

Al terminar esta sesión tendremos:

```
                 Industrial Monitoring API
                          │
             ┌────────────┴────────────┐
             │                         │
        REST API                  OpenAPI Schema
             │                         │
             │                    /api/schema/
             │                         │
             │                         ▼
             │                    Swagger UI
             │                    /api/docs/
             │
             ├── Machines
             ├── Sensors
             ├── Measurements
             ├── Alerts
             └── Maintenance
```

## Instalar drf-spectacular

Si todavía no lo hiciste:

```python
python -m pip install drf-spectacular
```

y:

```python
python -m pip freeze > requirements.txt
```

## Agregarlo a `INSTALLED_APPS`

En:

```
config/settings.py
```

agrega:

```python
INSTALLED_APPS = [
    # Django
    "django.contrib.admin",
    "django.contrib.auth",
    "django.contrib.contenttypes",
    "django.contrib.sessions",
    "django.contrib.messages",
    "django.contrib.staticfiles",

    # Third party
    "rest_framework",
    "drf_spectacular",

    # Local
    "apps.machines",
    "apps.sensors",
    "apps.measurements",
    "apps.alerts",
    "apps.maintenance",
]
```

## Configurar DRF

Como ya tenemos JWT:

```python
REST_FRAMEWORK = {
    "DEFAULT_AUTHENTICATION_CLASSES": (
        "rest_framework_simplejwt.authentication.JWTAuthentication",
    ),

    "DEFAULT_SCHEMA_CLASS": (
        "drf_spectacular.openapi.AutoSchema"
    ),
}
```

Observa que **no estamos eliminando JWT**.

Estamos agregando:

```python
"DEFAULT_SCHEMA_CLASS": (
    "drf_spectacular.openapi.AutoSchema"
)
```


# Configuración de nuestra documentación

En `settings.py`:

```python
SPECTACULAR_SETTINGS = {
    "TITLE": "Industrial Monitoring API",
    "DESCRIPTION": (
        "REST API for monitoring industrial machines, "
        "sensors, measurements, alerts and maintenance."
    ),
    "VERSION": "1.0.0",
}
```

Por ahora no necesitamos meter más configuración.

# Crear el endpoint OpenAPI

En:

```
config/urls.py
```

importa:

```
from drf_spectacular.views import (
    SpectacularAPIView,
    SpectacularSwaggerView,
)
```

Y dentro de `urlpatterns`:

```
path(
    "api/schema/",
    SpectacularAPIView.as_view(),
    name="schema",
),

path(
    "api/docs/",
    SpectacularSwaggerView.as_view(
        url_name="schema"
    ),
    name="swagger-ui",
),
```

Entonces tendremos:

```
/api/schema/
/api/docs/
```

# Qué diferencia hay?

### `/api/schema/`

Es el documento OpenAPI.

```
/api/schema/
```

No está pensado principalmente para humanos.

Es información estructurada que describe nuestra API.

---

### `/api/docs/`

Es Swagger UI.

```
/api/docs/
```

Esta sí está diseñada para nosotros:

```
┌──────────────────────────────────────┐
│ Industrial Monitoring API            │
│ Version 1.0.0                        │
├──────────────────────────────────────┤
│ Machines                             │
│                                      │
│ GET    /api/machines/                │
│ POST   /api/machines/                │
│ GET    /api/machines/{id}/           │
│ PATCH  /api/machines/{id}/           │
│ DELETE /api/machines/{id}/           │
├──────────────────────────────────────┤
│ Sensors                              │
│ ...                                  │
└──────────────────────────────────────┘
```

# Arrancamos

Primero:

```python
python manage.py check
```

Después:

```python
python manage.py runserver
```

Y abre:

```
http://127.0.0.1:8000/api/docs/
```

# Lo que deberías ver

Swagger debería detectar automáticamente nuestros ViewSets.

Por ejemplo:

```
Machines
Sensors
Measurements
Alerts
Maintenance
```

Y dentro de cada uno:

```
GET
POST
PUT
PATCH
DELETE
```

dependiendo de cómo estén configurados nuestros ViewSets.

También debería detectar los schemas generados a partir de nuestros serializers.

# Algo interesante que ya tenemos

Fíjate en todo lo que Swagger puede obtener de nuestro código:

```python
class MeasurementSerializer(serializers.ModelSerializer):
```

↓

Swagger puede inferir:

```d
Measurement
├── id
├── sensor
├── value
└── timestamp
```

Y nuestro:

```python
class MeasurementViewSet(viewsets.ModelViewSet):
```

le permite conocer las operaciones disponibles.

Entonces:

```
Models
   ↓
Serializers
   ↓
ViewSets
   ↓
DRF
   ↓
drf-spectacular
   ↓
OpenAPI
   ↓
Swagger UI
```

Esto demuestra por qué fue importante construir la API de forma estructurada.

# JWT en Swagger

Ahora viene la parte importante.

Queremos que Swagger tenga un botón:

```
Authorize 🔒
```

para introducir nuestro JWT.

Para eso agregaremos una configuración de seguridad.

En `SPECTACULAR_SETTINGS`:

```
SPECTACULAR_SETTINGS = {
    "TITLE": "Industrial Monitoring API",
    "DESCRIPTION": (
        "REST API for monitoring industrial machines, "
        "sensors, measurements, alerts and maintenance."
    ),
    "VERSION": "1.0.0",

    "SERVE_INCLUDE_SCHEMA": False,
}
```

Y en nuestro caso, **drf-spectacular puede detectar la autenticación JWT a partir de la configuración de DRF/SimpleJWT**. Por eso primero prueba Swagger **sin agregar manualmente un `BearerAuth`**.

Esto es importante porque no queremos duplicar configuración innecesariamente.

# Comprueba el botón `Authorize`

Abre:

```
/api/docs/
```

Busca:

```
Authorize
```

Si aparece el esquema Bearer/JWT, podremos hacer:

```
POST /api/token/
```

obtener nuestro:

```
{
    "access": "...",
    "refresh": "..."
}
```

y utilizar el `access` token para autorizar Swagger.

Conceptualmente:

```
Swagger
   │
   ▼
POST /api/token/
   │
   ▼
JWT
   │
   ▼
Authorize 🔒
   │
   ▼
Bearer <access>
   │
   ▼
GET /api/machines/
   │
   ▼
200 OK
```