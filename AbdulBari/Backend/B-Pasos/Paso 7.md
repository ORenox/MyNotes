Validación y lógica de negocio con Django

En esta sesión vamos a dar el siguiente paso: **controlar qué datos puede recibir nuestra API**.

En un sistema industrial esto es especialmente importante.

Por ejemplo:

```
Temperatura = 75 °C   → válido
Temperatura = "hola"  → inválido
Valor = -999999       → posiblemente inválido
Machine inexistente   → inválido
Sensor inexistente    → inválido
```

# ¿Dónde debería estar la validación?

Esta es una pregunta muy importante de arquitectura.

Tenemos:

```
Model
Serializer
ViewSet
```

Cada uno tiene una responsabilidad diferente.

### Model

Representa la estructura y reglas relacionadas con la base de datos.

```
class Sensor(models.Model):
    ...
```

### Serializer

Valida los datos que llegan por la API.

```
JSON
 ↓
Serializer
 ↓
validación
 ↓
Model
```

### ViewSet

Se ocupa principalmente de la lógica HTTP y de coordinar la operación.

```
GET
POST
PUT
PATCH
DELETE
```

Por eso, muchas validaciones de entrada deben vivir en el **Serializer**.

# Ejemplo: nuestro Measurement

Tenemos:

```python
class Measurement(models.Model):
    sensor = models.ForeignKey(
        Sensor,
        on_delete=models.CASCADE,
        related_name="measurements",
    )
    value = models.FloatField()
    timestamp = models.DateTimeField()
```

Nuestro serializer probablemente es algo parecido a:

```python
from rest_framework import serializers

from apps.measurements.models import Measurement


class MeasurementSerializer(serializers.ModelSerializer):

    class Meta:
        model = Measurement
        fields = [
            "id",
            "sensor",
            "value",
            "timestamp",
        ]
```

Hasta ahora DRF nos permite enviar algo como:

```d
{
    "sensor": 1,
    "value": 75.5,
    "timestamp": "2026-09-20T10:00:00Z"
}
```

Pero ahora queremos controlar mejor los datos.

# Primera validación: `value`

Imagina que decidimos que una medición debe estar entre:

```
0
1000
```

Podemos validar en el serializer:

```python
class MeasurementSerializer(serializers.ModelSerializer):

    class Meta:
        model = Measurement
        fields = [
            "id",
            "sensor",
            "value",
            "timestamp",
        ]

    def validate_value(self, value):

        if value < 0:
            raise serializers.ValidationError(
                "Measurement value cannot be negative."
            )

        if value > 1000:
            raise serializers.ValidationError(
                "Measurement value cannot exceed 1000."
            )

        return value
```

Aquí aparece una convención importante:

```d
validate_<nombre_del_campo>
```

Por ejemplo:

```
validate_value()
```

valida:

```
value
```

# ¿Qué ocurre cuando llega un POST?

Supongamos:

```d
POST /api/measurements/
```

con:

```d
{
    "sensor": 1,
    "value": -50,
    "timestamp": "2026-09-20T10:00:00Z"
}
```

El flujo es:

```d
POST
 ↓
MeasurementViewSet
 ↓
MeasurementSerializer
 ↓
validate_value()
 ↓
value = -50
 ↓
❌ ValidationError
```

La API podría responder algo como:

```d
{
    "value": [
        "Measurement value cannot be negative."
    ]
}
```

Y devuelve un HTTP `400 Bad Request`.

Esto es exactamente lo que queremos.


# Validación del objeto completo

Ahora imagina una regla más compleja.

Por ejemplo:

> Una medición no debería tener un timestamp futuro.

Aquí ya no estamos validando solamente `value`.

Estamos comparando:

```d
value
+
timestamp
```

Para eso podemos utilizar:

```d
validate()
```

Ejemplo:

```d
from django.utils import timezone
from rest_framework import serializers


class MeasurementSerializer(serializers.ModelSerializer):

    class Meta:
        model = Measurement
        fields = [
            "id",
            "sensor",
            "value",
            "timestamp",
        ]

    def validate_value(self, value):

        if value < 0:
            raise serializers.ValidationError(
                "Measurement value cannot be negative."
            )

        if value > 1000:
            raise serializers.ValidationError(
                "Measurement value cannot exceed 1000."
            )

        return value

    def validate(self, data):

        if data["timestamp"] > timezone.now():
            raise serializers.ValidationError(
                "Measurement timestamp cannot be in the future."
            )

        return data
```

La diferencia conceptual es:

```
validate_value()
       ↓
valida UN campo


validate()
       ↓
valida varios campos juntos
```

# Esto es muy importante en nuestro proyecto

Nuestro sistema representa datos industriales.

Podríamos tener reglas como:

### Machine

```
name → obligatorio
model → obligatorio
status → ACTIVE / MAINTENANCE / OFFLINE
```

### Sensor

```
machine → debe existir
name → obligatorio
sensor_type → obligatorio
unit → obligatorio
```

### Measurement

```
sensor → debe existir
value → debe ser válido
timestamp → válido
```

### Alert

```
machine → debe existir
sensor → debe existir
value → válido
threshold → válido
severity → LOW / MEDIUM / HIGH
```

### Maintenance

```
machine → debe existir
scheduled_date → válida
completed → boolean
completed_date → coherente con completed
```

Esto empieza a convertirse en **lógica de negocio**.

# Ejemplo interesante: Maintenance

Tenemos:

```python
completed = models.BooleanField(default=False)
completed_date = models.DateField(
    null=True,
    blank=True,
)
```

Podemos establecer una regla:

> Si `completed=True`, debe existir `completed_date`.

Y:

> Si `completed=False`, no debería existir `completed_date`.

Eso requiere comparar dos campos.

Por tanto:

```python
def validate(self, data):

    completed = data.get("completed")
    completed_date = data.get("completed_date")

    if completed and not completed_date:
        raise serializers.ValidationError(
            "Completed maintenance must have a completed date."
        )

    if not completed and completed_date:
        raise serializers.ValidationError(
            "Incomplete maintenance cannot have a completed date."
        )

    return data
```

Esto es mucho más interesante que simplemente validar tipos.

# `required` vs `allow_null` vs `allow_blank`

Aquí hay tres conceptos que debes conocer.

### `required`

¿El cliente tiene que enviar el campo?

```
required=True
```

significa:

```
debes enviarlo
```

---

### `allow_null`

¿Puede ser `null`?

```
{
    "completed_date": null
}
```

Eso es diferente de no enviar el campo.

---

### `allow_blank`

Se utiliza principalmente con strings.

Por ejemplo:

```
{
    "description": ""
}
```

`allow_blank` determina si se permite un string vacío.

# Diferencia entre `null` y ausencia

Esto es importante para APIs.

### Campo ausente

```
{}
```

No enviamos el campo.

### Campo `null`

```
{
    "completed_date": null
}
```

Estamos diciendo explícitamente:

> El valor es nulo.

### String vacío

```
{
    "description": ""
}
```

Estamos diciendo:

> El valor es un string, pero está vacío.

Son tres situaciones diferentes.

# POST vs PATCH

Aquí empieza a tener sentido otra diferencia importante.

Tenemos:

```
POST /api/measurements/
```

para crear.

Y:

```
PATCH /api/measurements/1/
```

para modificar parcialmente.

Por ejemplo:

```
{
    "value": 85.3
}
```

Con PATCH no necesitamos enviar:

```
{
    "sensor": 1,
    "value": 85.3,
    "timestamp": "..."
}
```

porque estamos modificando solamente `value`.

DRF maneja esto mediante:

```
partial update
```

Esto será muy importante cuando empecemos a construir endpoints más reales.

# Una regla de oro

Quiero que empieces a pensar así:

```
ViewSet
   │
   ├── ¿Qué endpoint estoy ejecutando?
   │
   ├── ¿GET?
   ├── ¿POST?
   ├── ¿PATCH?
   └── ¿DELETE?
          │
          ▼
      Serializer
          │
          ├── ¿Los datos tienen el formato correcto?
          ├── ¿Los valores son válidos?
          └── ¿Las reglas de negocio se cumplen?
                    │
                    ▼
                  Model
                    │
                    ▼
               PostgreSQL
```

No queremos meter toda la lógica en `views.py`.
