Django ORM nos permitiría trabajar con PostgreSQL mediante modelos:

```python
class Machine(models.Model):
    name = models.CharField(max_length=100)
    model = models.CharField(max_length=100)
    location = models.CharField(max_length=100)
    status = models.CharField(max_length=30)
```

Luego:

```python
python manage.py makemigrations
python manage.py migrate
```


## Tabla `Machine`

Tu diagrama tiene:

| Campo      | Django                 |
| ---------- | ---------------------- |
| machine_id | id automático          |
| name       | CharField              |
| model      | CharField              |
| location   | CharField              |
| status     | CharField con opciones |

```python
# apps/machines/models.py

from django.db import models

class Machine(models.Model):

    class Status(models.TextChoices):
        ACTIVE = "ACTIVE", "Active"
        MAINTENANCE = "MAINTENANCE", "Maintenance"
        OFFLINE = "OFFLINE", "Offline"

    name = models.CharField(max_length=100)
    model = models.CharField(max_length=100)
    location = models.CharField(max_length=100)

    status = models.CharField(
        max_length=20,
        choices=Status.choices,
        default=Status.ACTIVE,
    )

    def __str__(self):
        return self.name
```

### ¿Dónde está `machine_id`?

No lo escribes.

Django agrega automáticamente:

```
id BIGSERIAL PRIMARY KEY
```

equivalente a tu `machine_id serial`.


## Tabla `Sensor`

En tu diagrama:

- Un sensor pertenece a una máquina.
    
- Una máquina tiene muchos sensores.
    

Eso en Django es un `ForeignKey`.

```python
from django.db import models
from apps.machines.models import Machine

class Sensor(models.Model):

    machine = models.ForeignKey(
        Machine,
        on_delete=models.CASCADE,
        related_name="sensors"
    )

    name = models.CharField(max_length=100)

    sensor_type = models.CharField(max_length=50)

    unit = models.CharField(max_length=20)

    def __str__(self):
        return self.name
```

### Django crea esta relación

```
Machine (1)
     │
     │ ForeignKey
     ▼
Sensor (N)
```

En PostgreSQL aparecerá una columna:

```
machine_id INTEGER REFERENCES machine(id)
```

Sin escribir SQL.


## Measurements

Tu diagrama dice:

- Muchas mediciones pertenecen a un sensor.

En Django:

```python
from django.db import models
from apps.sensors.models import Sensor

class Measurement(models.Model):

    sensor = models.ForeignKey(
        Sensor,
        on_delete=models.CASCADE,
        related_name="measurements"
    )

    value = models.FloatField()

    timestamp = models.DateTimeField(auto_now_add=True)

    class Meta:
        ordering = ["-timestamp"]
```

### Aquí corrijo una cosa importante

En el diagrama tienes `date`.

Yo usaría:

```
DateTimeField
```

Porque las mediciones normalmente tienen fecha y hora.

Ejemplo:

|timestamp|
|---|
|2026-09-18 08:15:12|
|2026-09-18 08:20:12|


## Alerts

Aquí también hay relaciones.

En tu diagrama pusiste `machine_id` y `sensor_id` como `varchar`.

Yo los cambiaría a `ForeignKey`.

```python
from django.db import models
from apps.machines.models import Machine
from apps.sensors.models import Sensor

class Alert(models.Model):

    class Severity(models.TextChoices):
        LOW = "LOW"
        MEDIUM = "MEDIUM"
        HIGH = "HIGH"

    machine = models.ForeignKey(
        Machine,
        on_delete=models.CASCADE,
        related_name="alerts"
    )

    sensor = models.ForeignKey(
        Sensor,
        on_delete=models.CASCADE,
        related_name="alerts"
    )

    value = models.FloatField()

    threshold = models.FloatField()

    severity = models.CharField(
        max_length=10,
        choices=Severity.choices
    )

    resolved = models.BooleanField(default=False)

    created_at = models.DateTimeField(auto_now_add=True)
```

### ¿Por qué ForeignKey y no varchar?

Porque así PostgreSQL garantiza integridad.

No puedes crear una alerta para una máquina inexistente.

## Maintenance (Aquí sí hay un error en el diagrama)

Tu tabla `maintenance` parece una tabla de usuarios de un juego (`username`, `games`, `guesses`).

Para tu proyecto debería verse así.

```python
from django.db import models
from django.contrib.auth.models import User
from apps.machines.models import Machine

class Maintenance(models.Model):

    class MaintenanceType(models.TextChoices):
        PREVENTIVE = "PREVENTIVE"
        CORRECTIVE = "CORRECTIVE"

    machine = models.ForeignKey(
        Machine,
        on_delete=models.CASCADE,
        related_name="maintenance_records"
    )

    technician = models.ForeignKey(
        User,
        on_delete=models.SET_NULL,
        null=True
    )

    maintenance_type = models.CharField(
        max_length=20,
        choices=MaintenanceType.choices
    )

    description = models.TextField()

    scheduled_date = models.DateField()

    completed = models.BooleanField(default=False)

    completed_date = models.DateField(
        null=True,
        blank=True
    )
```

### Mucho más útil para un sistema industrial.