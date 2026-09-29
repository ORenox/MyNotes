**Django REST Framework (DRF)**.

# Instalar Django REST Framework

Activa tu entorno virtual:

```
.venv\Scripts\activate
```

o en Linux/macOS:

```
source .venv/bin/activate
```

Instala:

```python
python -m pip install djangorestframework
```

Actualiza:

```python
python -m pip freeze > requirements.txt
```

# Registrar DRF

Abre:

```
config/settings.py
```

En `INSTALLED_APPS` agrega:

```python
INSTALLED_APPS = [
    "django.contrib.admin",
    "django.contrib.auth",
    "django.contrib.contenttypes",
    "django.contrib.sessions",
    "django.contrib.messages",
    "django.contrib.staticfiles",

    "rest_framework",

    "apps.machines",
    "apps.sensors",
    "apps.measurements",
    "apps.alerts",
    "apps.maintenance",
]
```

La parte importante es:

```
"rest_framework",
```

# ==Nuestro primer Endpoint==

Vamos a empezar con algo sencillo:

```
GET /api/machines/
```

Queremos que responda:

```d
[
    {
        "id": 1,
        "name": "CNC-001",
        "model": "Haas VF-2",
        "location": "Production Area A",
        "status": "ACTIVE"
    }
]
```

Para conseguirlo necesitamos tres cosas:

```
Model
  ↓
Serializer
  ↓
View
  ↓
URL
```

## Crear nuestro primer Serializer

Abre:

```
apps/machines/
```

Crea:

```
serializers.py
```

Y escribe:

```python
from rest_framework import serializers

from apps.machines.models import Machine


class MachineSerializer(serializers.ModelSerializer):

    class Meta:
        model = Machine
        fields = [
            "id",
            "name",
            "model",
            "location",
            "status",
        ]
```

## ¿Qué significa `ModelSerializer`?

Podríamos escribir un serializer manualmente:

```python
class MachineSerializer(serializers.Serializer):
    ...
```

Pero como nuestro modelo ya existe:

```
class Machine(models.Model):
```

podemos aprovechar:

```python
serializers.ModelSerializer
```

DRF puede deducir automáticamente muchas cosas a partir de nuestro modelo.

Por ejemplo:

```python
name = models.CharField(...)
```

se transforma apropiadamente en un campo de serializer.

## Crear nuestra View

Abre:

```
apps/machines/views.py
```

Vamos a utilizar un `ViewSet`:

```python
from rest_framework import viewsets

from apps.machines.models import Machine
from apps.machines.serializers import MachineSerializer


class MachineViewSet(viewsets.ModelViewSet):

    queryset = Machine.objects.all()

    serializer_class = MachineSerializer
```

Aquí acabamos de conseguir bastante funcionalidad con muy poco código.

## ¿Qué nos da `ModelViewSet`?

Esta clase:

```python
viewsets.ModelViewSet
```

ya proporciona operaciones CRUD:

```
GET
POST
PUT
PATCH
DELETE
```

Conceptualmente:

```
MachineViewSet
      │
      ├── list()
      ├── retrieve()
      ├── create()
      ├── update()
      ├── partial_update()
      └── destroy()
```

No tenemos que escribir cada una manualmente.

## Crear las URLs

Ahora crea:

```
apps/machines/urls.py
```

Pon:

```python
from rest_framework.routers import DefaultRouter

from apps.machines.views import MachineViewSet


router = DefaultRouter()

router.register(
    "machines",
    MachineViewSet,
    basename="machine",
)

urlpatterns = router.urls
```

El `router` genera automáticamente las rutas.

## Conectar las URLs principales

Abre:

```
config/urls.py
```

Inicialmente tendrás algo parecido a:

```
from django.contrib import admin
from django.urls import path
```

Vamos a cambiarlo:

```
from django.contrib import admin
from django.urls import include, path


urlpatterns = [
    path("admin/", admin.site.urls),
    path(
        "api/",
        include("apps.machines.urls"),
    ),
]
```

Ahora tenemos:

```
/api/
   │
   └── machines/
```

## Arrancar Django

```
python manage.py runserver
```

Abre:

```
http://127.0.0.1:8000/api/machines/
```

Como DRF proporciona una interfaz navegable, deberías poder ver la respuesta desde el navegador.

Si ya tenías datos de `Machine`, aparecerán.

Por ejemplo:

```
[
    {
        "id": 1,
        "name": "CNC-001",
        "model": "Haas VF-2",
        "location": "Production Area A",
        "status": "MAINTENANCE"
    }
]
```

🎉 Acabas de crear tu primer endpoint REST.

## ¿Qué acaba de ocurrir?

Cuando haces:

```
GET /api/machines/
```

tenemos:

```
Browser / Postman
       │
       │ HTTP GET
       ▼
Django URL Router
       │
       ▼
MachineViewSet
       │
       ▼
Machine.objects.all()
       │
       ▼
PostgreSQL
       │
       ▼
Django Model
       │
       ▼
MachineSerializer
       │
       ▼
JSON
       │
       ▼
Cliente
```

Este flujo es **fundamental** para entender Django REST Framework.


# Probar POST

Ahora podemos crear una máquina mediante la API.

Puedes utilizar Postman, Insomnia o `curl`.

Por ejemplo:

```d
POST /api/machines/
Content-Type: application/json
```

Body:

```
{
    "name": "PLC-001",
    "model": "Siemens S7-1200",
    "location": "Control Room",
    "status": "ACTIVE"
}
```

La respuesta debería ser:

```
{
    "id": 4,
    "name": "PLC-001",
    "model": "Siemens S7-1200",
    "location": "Control Room",
    "status": "ACTIVE"
}
```

Y esa información ahora existe en PostgreSQL.

# Probar GET de una máquina

Si tenemos:

```
id = 4
```

hacemos:

```
GET /api/machines/4/
```

Respuesta:

```
{
    "id": 4,
    "name": "PLC-001",
    "model": "Siemens S7-1200",
    "location": "Control Room",
    "status": "ACTIVE"
}
```

Esto se llama **retrieve**.

# PUT

Podemos reemplazar los datos:

```
PUT /api/machines/4/
```

```
{
    "name": "PLC-001",
    "model": "Siemens S7-1500",
    "location": "Control Room B",
    "status": "ACTIVE"
}
```

# PATCH

También podemos modificar solamente un campo:

```
PATCH /api/machines/4/
```

```
{
    "status": "MAINTENANCE"
}
```

Esto es muy útil porque no tenemos que enviar todo el objeto.

# DELETE

Finalmente:

```
DELETE /api/machines/4/
```

Esto eliminará la máquina.

⚠️ Para nuestro proyecto real, posteriormente tendremos que pensar cuidadosamente sobre eliminación de máquinas porque tenemos:

```
Machine
   │
   ├── Sensors
   ├── Measurements
   ├── Alerts
   └── Maintenance
```

y algunas relaciones utilizan:

```
on_delete=models.CASCADE
```

Por eso no quiero que implementemos una política de borrado definitiva sin analizar primero el historial industrial.

# Ver las rutas que generó el Router

Nuestro código:

```python

router.register(
    "machines",
    MachineViewSet,
    basename="machine",
)
```

genera conceptualmente:

|Método|URL|Acción|
|---|---|---|
|GET|`/api/machines/`|Listar|
|POST|`/api/machines/`|Crear|
|GET|`/api/machines/{id}/`|Obtener|
|PUT|`/api/machines/{id}/`|Reemplazar|
|PATCH|`/api/machines/{id}/`|Modificar|
|DELETE|`/api/machines/{id}/`|Eliminar|

Esto es CRUD REST.

# Nuestro primer API test manual

Ahora quiero que pienses como backend/SDET.

Tenemos:

```
POST /api/machines/
```

Podríamos definir:

### Request válido

```
{
    "name": "Robot-001",
    "model": "ABB IRB 120",
    "location": "Assembly Area",
    "status": "ACTIVE"
}
```

Esperamos:

```
HTTP 201 Created
```

---

### Request inválido

Por ejemplo:

```
{
    "name": "",
    "model": "ABB IRB 120"
}
```

Esperamos un error de validación.

DRF debería devolver un estado `400 Bad Request` cuando los datos no cumplan la validación correspondiente.

Esto será muy importante cuando lleguemos a **Pytest**.

# Una diferencia importante: Model vs Serializer

No los confundas.

### Model

Representa persistencia:

```
class Machine(models.Model):
    name = models.CharField(...)
```

Conceptualmente:

```
Python
 ↓
Database
```

---

### Serializer

Representa la entrada/salida de nuestra API:

```
class MachineSerializer(serializers.ModelSerializer):
```

Conceptualmente:

```
Python Model
     ↕
 JSON API
```

Entonces:

```
                 Django
                   │
        ┌──────────┴──────────┐
        ▼                     ▼
      Model               Serializer
        │                     │
        ▼                     ▼
   PostgreSQL              JSON API
```

# ¿Por qué no devolver directamente el Model?

Porque no queremos exponer necesariamente todos nuestros campos internos.

Imagina que `Machine` posteriormente tuviera:

```
internal_configuration
maintenance_cost
internal_notes
secret_identifier
```

No necesariamente queremos que:

```
GET /api/machines/
```

devuelva todo.

El serializer controla **qué entra y qué sale de la API**.

# Vamos a hacer una pequeña mejora

En nuestro serializer:

```python
fields = [
    "id",
    "name",
    "model",
    "location",
    "status",
]
```

Estamos diciendo explícitamente qué campos exponemos.

Eso es mejor que:

```python
fields = "__all__"
```

para una API que queremos mantener cuidadosamente.

# Documentar mentalmente nuestra arquitectura

A partir de ahora tu proyecto tiene:

```
                     HTTP
                      │
                      ▼
              ┌───────────────┐
              │      URL      │
              └───────┬───────┘
                      │
                      ▼
              ┌───────────────┐
              │     View      │
              └───────┬───────┘
                      │
                      ▼
              ┌───────────────┐
              │   Serializer  │
              └───────┬───────┘
                      │
                      ▼
              ┌───────────────┐
              │      ORM      │
              └───────┬───────┘
                      │
                      ▼
              ┌───────────────┐
              │  PostgreSQL   │
              └───────────────┘
```

Pero en una operación `GET`, el flujo de datos vuelve hacia arriba:

```
PostgreSQL
    ↓
ORM
    ↓
View
    ↓
Serializer
    ↓
JSON
    ↓
Cliente
```

# Challenge adicional

Una vez que tengas `/api/sensors/`, intenta hacer:

```
POST /api/sensors/
```

con:

```
{
    "machine": 1,
    "name": "Motor Current",
    "sensor_type": "CURRENT",
    "unit": "A"
}
```

Y después:

```
GET /api/sensors/
```

Deberías poder ver el sensor.