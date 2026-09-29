Serializers, ViewSets y Routers.

Hoy vamos a profundizar en **cómo DRF decide qué datos devolver**, y sobre todo en la diferencia entre:

- `queryset`
- `get_queryset()`
- `get_object()`
- `serializer`
- parámetros `?machine=...`
- filtros
- `404 Not Found`

La idea es que puedas mirar un `ViewSet` y entender exactamente qué está pasando.

---
## El flujo completo de una petición

Imagina:

```
GET /api/sensors/?machine=3
```

El flujo conceptual es:

```d
Cliente
   │
   │ GET /api/sensors/?machine=3
   ▼
URL Router
   │
   ▼
SensorViewSet
   │
   ▼
get_queryset()
   │
   ├── Sensor.objects.all()
   │
   └── .filter(machine_id=3)
   │
   ▼
QuerySet
   │
   ▼
Serializer
   │
   ▼
JSON
   │
   ▼
Cliente
```

Esto es fundamental para entender DRF.

# Serializer

Crea:

### `apps/sensors/serializers.py`

```
from rest_framework import serializers

from apps.sensors.models import Sensor


class SensorSerializer(serializers.ModelSerializer):

    class Meta:
        model = Sensor
        fields = [
            "id",
            "machine",
            "name",
            "sensor_type",
            "unit",
        ]
```

Aquí ocurre algo interesante.

Si tenemos:

```
Sensor
id = 1
machine = 3
name = "Temperature Sensor"
sensor_type = "TEMPERATURE"
unit = "°C"
```

El serializer puede producir:

```
{
    "id": 1,
    "machine": 3,
    "name": "Temperature Sensor",
    "sensor_type": "TEMPERATURE",
    "unit": "°C"
}
```

# Nuestro primer ViewSet

### `apps/sensors/views.py`

```python
from rest_framework import viewsets

from apps.sensors.models import Sensor
from apps.sensors.serializers import SensorSerializer


class SensorViewSet(viewsets.ModelViewSet):

    queryset = Sensor.objects.all()
    serializer_class = SensorSerializer
```

Esto ya nos proporciona:

```
GET     /api/sensors/
POST    /api/sensors/
GET     /api/sensors/1/
PUT     /api/sensors/1/
PATCH   /api/sensors/1/
DELETE  /api/sensors/1/
```


# ¿Qué significa realmente `queryset`?

Tenemos:

```python
queryset = Sensor.objects.all()
```

Piensa en esto como:

> "Este es el conjunto de sensores sobre el cual trabaja este ViewSet."

No significa:

> "Cada endpoint obligatoriamente devolverá todos los sensores."

DRF puede modificar ese QuerySet.

Por ejemplo:

```python
queryset = Sensor.objects.all()

queryset = queryset.filter(machine_id=3)
```

Resultado:

```
Todos los sensores
       │
       ▼
filter(machine_id=3)
       │
       ▼
Sensores de Machine 3
```

# `get_queryset()`

Aquí es donde empieza a ponerse interesante.

Podemos hacer:

```python
class SensorViewSet(viewsets.ModelViewSet):

    serializer_class = SensorSerializer

    def get_queryset(self):
        queryset = Sensor.objects.all()

        machine_id = self.request.query_params.get("machine")

        if machine_id:
            queryset = queryset.filter(machine_id=machine_id)

        return queryset
```

Ahora podemos hacer:

### Todos

```
GET /api/sensors/
```

Resultado:

```
[
    {
        "id": 1,
        "machine": 1,
        "name": "Temperature Sensor"
    },
    {
        "id": 2,
        "machine": 1,
        "name": "Pressure Sensor"
    },
    {
        "id": 3,
        "machine": 2,
        "name": "Temperature Sensor"
    }
]
```

Pero:

```
GET /api/sensors/?machine=1
```

produce solamente:

```
[
    {
        "id": 1,
        "machine": 1,
        "name": "Temperature Sensor"
    },
    {
        "id": 2,
        "machine": 1,
        "name": "Pressure Sensor"
    }
]
```

# ¿De dónde sale `self.request`?

Esta parte es muy importante.

DRF recibe:

```
GET /api/sensors/?machine=1
```

Y construye un objeto `request`.

Podemos acceder a los parámetros:

```python
self.request.query_params
```

Conceptualmente:

```d
request
│
├── method
│      GET
│
├── path
│      /api/sensors/
│
└── query_params
       │
       └── machine = 1
```

Entonces:

```python
self.request.query_params.get("machine")
```

devuelve:

```
"1"
```

**Ojo:** normalmente llega como string.

Por eso:

```python
machine_id = self.request.query_params.get("machine")
```

produce:

```
"1"
```

no:

```
1
```

Django puede manejar muchos filtros de FK con `"1"`, pero conceptualmente es importante entender que viene de HTTP como texto.

# Agreguemos filtro por tipo

Podemos hacer:

```python
class SensorViewSet(viewsets.ModelViewSet):

    serializer_class = SensorSerializer

    def get_queryset(self):
        queryset = Sensor.objects.all()

        machine_id = self.request.query_params.get("machine")
        sensor_type = self.request.query_params.get("type")

        if machine_id:
            queryset = queryset.filter(
                machine_id=machine_id
            )

        if sensor_type:
            queryset = queryset.filter(
                sensor_type=sensor_type
            )

        return queryset
```

Ahora tenemos:

```
GET /api/sensors/?machine=1
```

o:

```
GET /api/sensors/?type=TEMPERATURE
```

o ambos:

```
GET /api/sensors/?machine=1&type=TEMPERATURE
```

El último equivale conceptualmente a:

```
Sensor.objects.filter(
    machine_id=1,
    sensor_type="TEMPERATURE"
)
```

# Agreguemos búsqueda

Podemos usar:

```python
search = self.request.query_params.get("search")

if search:
    queryset = queryset.filter(
        name__icontains=search
    )
```

Entonces:

```
GET /api/sensors/?search=temp
```

puede encontrar:

```
Temperature Sensor
Temperature Probe
Temp Sensor
```

porque:

```
name__icontains="temp"
```

busca sin distinguir mayúsculas/minúsculas.

# get_queryset() vs get_object()

Esta diferencia quiero que la memorices.

### `get_queryset()`

Responde:

> **¿Cuál es el conjunto de objetos que puede manejar este endpoint?**

Ejemplo:

```
def get_queryset(self):
    return Sensor.objects.filter(
        sensor_type="TEMPERATURE"
    )
```

---

### `get_object()`

Responde:

> **¿Cuál objeto específico estamos buscando?**

Por ejemplo:

```
GET /api/sensors/5/
```

DRF busca el sensor específico.

# Ejemplo práctico

Supongamos:

```
Sensor 1 → Temperature
Sensor 2 → Pressure
Sensor 3 → Temperature
```

Si hacemos:

```
GET /api/sensors/
```

obtenemos:

```
1
2
3
```

Si hacemos:

```
GET /api/sensors/?type=TEMPERATURE
```

obtenemos:

```
1
3
```

Si hacemos:

```
GET /api/sensors/2/
```

obtenemos:

```
2
```

La diferencia es:

```
GET /sensors/
       │
       └── colección

GET /sensors/?type=...
       │
       └── colección filtrada

GET /sensors/2/
       │
       └── objeto específico
```

# ¿Por qué no hacer esto?

Evita algo como:

```python
def get_queryset(self):

    sensors = list(Sensor.objects.all())

    result = []

    for sensor in sensors:
        if sensor.machine_id == 3:
            result.append(sensor)

    return result
```

Aunque conceptualmente podría parecer funcionar, estás haciendo el trabajo en Python.

Es mucho mejor:

```python
return Sensor.objects.filter(
    machine_id=3
)
```

Porque el trabajo se realiza en la base de datos.

```
❌ Malo para grandes cantidades

PostgreSQL
    │
    │ todos los sensores
    ▼
Django
    │
    └── filtrar en Python


✅ Mejor

Django
    │
    │ SQL
    ▼
PostgreSQL
    │
    └── WHERE machine_id = 3
           │
           ▼
       solo resultados
```

Esto se vuelve **muy importante** cuando tengas miles o millones de mediciones industriales.

# Un concepto que debes empezar a reconocer: SQL

Cuando escribimos:

```
Sensor.objects.filter(
    machine_id=3
)
```

Django genera SQL aproximadamente equivalente a:

```
SELECT *
FROM sensors
WHERE machine_id = 3;
```

No necesitas escribir ese SQL manualmente.

Django ORM hace la traducción:

```
Python
  ↓
Django ORM
  ↓
SQL
  ↓
PostgreSQL
  ↓
Resultados
```

Puedes inspeccionarlo:

```python
queryset = Sensor.objects.filter(
    machine_id=3
)

print(queryset.query)
```

Esto es excelente para aprender backend.

# Ahora conectemos las URLs

### `apps/sensors/urls.py`

```python
from rest_framework.routers import DefaultRouter

from apps.sensors.views import SensorViewSet


router = DefaultRouter()

router.register(
    "sensors",
    SensorViewSet,
    basename="sensor",
)

urlpatterns = router.urls
```

Y en:

### `config/urls.py`

```python
from django.contrib import admin
from django.urls import include, path


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
]
```