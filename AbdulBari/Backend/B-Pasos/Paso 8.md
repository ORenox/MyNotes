Relaciones entre recursos y Nested Serializers

![[Pasted image 20260920182226.png]]


Nuestro modelo tiene:

```
Machine
   │
   └── Sensor
          │
          └── Measurement
```

Es decir:

```
Machine 1
   │
   ├── Sensor 1
   │      ├── Measurement
   │      ├── Measurement
   │      └── Measurement
   │
   └── Sensor 2
          ├── Measurement
          └── Measurement
```

Esta sesión será sobre cómo representar esas relaciones correctamente en una API.

# Actualmente nuestra respuesta es limitada

Nuestro `MeasurementSerializer` devuelve algo parecido a:

```
{
    "id": 10,
    "sensor": 3,
    "value": 75.5,
    "timestamp": "2026-09-20T15:00:00Z"
}
```

El problema es que el cliente solamente recibe:

```
sensor = 3
```

Si quiere saber:

- qué sensor es,
- qué tipo de sensor es,
- a qué máquina pertenece,

tendría que hacer otra petición:

```
GET /api/sensors/3/
```

Y posiblemente después:

```
GET /api/machines/1/
```

Eso puede ser correcto, pero no siempre es conveniente.

# Primera solución: `PrimaryKeyRelatedField`

Podemos controlar cómo se representa una relación.

Por defecto:

```
sensor
```

se representa como:

```
"sensor": 3
```

Esto es útil para crear una medición:

```d
{
    "sensor": 3,
    "value": 75.5,
    "timestamp": "2026-09-20T15:00:00Z"
}
```

El cliente simplemente dice:

> Quiero crear una medición para el sensor 3.

Eso está muy bien para **escritura**.

# Pero queremos más información al leer

Podríamos querer:

```d
{
    "id": 10,
    "sensor": {
        "id": 3,
        "name": "Temperature Sensor",
        "sensor_type": "TEMPERATURE",
        "unit": "C"
    },
    "value": 75.5,
    "timestamp": "2026-09-20T15:00:00Z"
}
```

Ahora el cliente recibe información del sensor directamente.

Esto se llama un **nested serializer**.


# Crear `SensorSerializer`

Ya tenemos uno parecido:

```python
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

Ahora podemos utilizar ese serializer dentro del serializer de Measurement.

En:

```python
apps/measurements/serializers.py
```

importamos:

```python
from apps.sensors.serializers import SensorSerializer
```

Y:

```python
class MeasurementSerializer(serializers.ModelSerializer):

    sensor = SensorSerializer(read_only=True)

    class Meta:
        model = Measurement
        fields = [
            "id",
            "sensor",
            "value",
            "timestamp",
        ]
```

Ahora la respuesta GET cambia.

Antes:

```
{
    "id": 10,
    "sensor": 3,
    "value": 75.5
}
```

Ahora:

```d
{
    "id": 10,
    "sensor": {
        "id": 3,
        "machine": 1,
        "name": "Temperature Sensor",
        "sensor_type": "TEMPERATURE",
        "unit": "C"
    },
    "value": 75.5
}
```


# Pero aparece un problema

Tenemos:

```python
sensor = SensorSerializer(read_only=True)
```

`read_only=True` significa:

> Esta representación se utiliza para leer, pero no para recibir datos de entrada.

Entonces esto:

```d
{
    "sensor": {
        "id": 3,
        "name": "Temperature Sensor"
    }
}
```

no es la forma en que nuestro endpoint espera recibir el sensor.

Para crear una medición queremos seguir pudiendo enviar:

```d
{
    "sensor": 3,
    "value": 75.5,
    "timestamp": "2026-09-20T15:00:00Z"
}
```

Por eso, en APIs reales, muchas veces se separa la representación de **lectura** y **escritura**.

# Una solución profesional: dos campos

Podemos hacer:

```python
class MeasurementSerializer(serializers.ModelSerializer):

    sensor_detail = SensorSerializer(
        source="sensor",
        read_only=True,
    )

    class Meta:
        model = Measurement
        fields = [
            "id",
            "sensor",
            "sensor_detail",
            "value",
            "timestamp",
        ]
```

Ahora podemos tener:

```python
{
    "id": 10,
    "sensor": 3,
    "sensor_detail": {
        "id": 3,
        "machine": 1,
        "name": "Temperature Sensor",
        "sensor_type": "TEMPERATURE",
        "unit": "C"
    },
    "value": 75.5,
    "timestamp": "2026-09-20T15:00:00Z"
}
```

Y para crear:

```d
{
    "sensor": 3,
    "value": 75.5,
    "timestamp": "2026-09-20T15:00:00Z"
}
```

Esto es bastante útil.

# Qué significa `source="sensor"`?

Tenemos:

```python
sensor_detail = SensorSerializer(
    source="sensor",
    read_only=True,
)
```

`source` le dice a DRF:

> El campo que estoy mostrando se obtiene realmente del atributo `sensor` del objeto Measurement.

Por eso:

```
sensor_detail
      │
      ▼
Measurement.sensor
      │
      ▼
SensorSerializer
```

# Ahora hagamos algo todavía más interesante

Podemos incluir la máquina.

Nuestro modelo es:

```
Measurement
     │
     ▼
Sensor
     │
     ▼
Machine
```

Y nuestro `SensorSerializer` actualmente tiene:

```
"machine"
```

Así que podemos terminar con:

```
{
    "id": 10,
    "sensor": 3,
    "sensor_detail": {
        "id": 3,
        "machine": 1,
        "name": "Temperature Sensor",
        "sensor_type": "TEMPERATURE",
        "unit": "C"
    },
    "value": 75.5
}
```

Ya podemos ver toda la cadena:

```
Measurement
    │
    └── Sensor 3
          │
          └── Machine 1
```

# Cuidado con un problema de rendimiento

Aquí aparece un concepto que será muy importante para nuestro proyecto.

Imagina que devolvemos:

```
1000 measurements
```

Y cada measurement necesita consultar su sensor.

Podríamos terminar haciendo muchas consultas a PostgreSQL.

Conceptualmente:

```
Measurement query
       ↓
1000 measurements
       ↓
consulta Sensor
consulta Sensor
consulta Sensor
consulta Sensor
...
```

Esto se conoce como el problema **N+1 queries**.

Y en un sistema industrial con millones de mediciones sería terrible.

# `select_related()`

Como:

```
Measurement → Sensor
```

es una relación `ForeignKey`, podemos utilizar:

```
select_related()
```

Nuestro ViewSet puede hacer:

```python
class MeasurementViewSet(viewsets.ModelViewSet):

    serializer_class = MeasurementSerializer

    def get_queryset(self):

        queryset = Measurement.objects.select_related(
            "sensor"
        )

        sensor_id = self.request.query_params.get("sensor")
        min_value = self.request.query_params.get("min_value")
        max_value = self.request.query_params.get("max_value")

        if sensor_id:
            queryset = queryset.filter(
                sensor_id=sensor_id
            )

        if min_value:
            queryset = queryset.filter(
                value__gte=min_value
            )

        if max_value:
            queryset = queryset.filter(
                value__lte=max_value
            )

        return queryset
```

Ahora Django puede obtener Measurement y Sensor mediante una consulta SQL con `JOIN`.

Conceptualmente:

```
❌ Sin select_related

Measurement
    ↓
Sensor
    ↓
Sensor
    ↓
Sensor
    ↓
...


✅ Con select_related

Measurement ─────┐
Sensor ──────────┤
                 ↓
            una consulta
```

# `select_related` vs `prefetch_related`

Por ahora memoriza esta regla:

### `select_related`

Para relaciones como:

```
ForeignKey
OneToOneField
```

Ejemplo:

```
Measurement.objects.select_related("sensor")
```

---

### `prefetch_related`

Para relaciones donde tenemos múltiples objetos relacionados.

Por ejemplo:

```
Machine
   │
   ├── Sensor
   ├── Sensor
   └── Sensor
```

Podemos hacer:

```
Machine.objects.prefetch_related("sensors")
```

Esto lo estudiaremos con más profundidad después.

