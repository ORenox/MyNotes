Modelar la base de datos en `models.py`

Vamos a modelar:

```
Machine
   │
   ├──── Sensor
   │        │
   │        └──── Measurement
   │
   ├──── Alert
   │
   └──── Maintenance
```


# Primero: ¿qué es un Model en Django?

Un modelo Django es una **clase Python que representa una tabla de la base de datos**.

Por ejemplo:

```d
class Machine(models.Model):
    name = models.CharField(max_length=100)
```

Django interpreta esto como algo parecido a:

```d
CREATE TABLE machine (
    id BIGINT PRIMARY KEY,
    name VARCHAR(100) NOT NULL
);
```

Tú escribes Python.

Django genera el SQL.

PostgreSQL ejecuta ese SQL.

# Una decisión importante: cómo organizar las apps

En la sesión 1 hablamos de:

```
apps/
├── machines
├── sensors
├── measurements
├── alerts
└── maintenance
```

Vamos a mantener esa separación.

Cada app será responsable de una parte del dominio.

```
machines
    → Machine

sensors
    → Sensor

measurements
    → Measurement

alerts
    → Alert

maintenance
    → Maintenance
```

Esto nos ayudará muchísimo cuando hagamos tests y APIs.

# Crear las apps correctamente

Si todavía tienes las apps en la raíz del proyecto, podemos reorganizarlas.

La estructura final que queremos es:

```
industrial-monitoring/
│
├── apps/
│   ├── __init__.py
│   │
│   ├── machines/
│   ├── sensors/
│   ├── measurements/
│   ├── alerts/
│   └── maintenance/
│
├── config/
├── manage.py
├── requirements.txt
└── docker-compose.yml
```

Si todavía no las has creado, puedes hacerlo con:

```
python manage.py startapp machines apps/machines
python manage.py startapp sensors apps/sensors
python manage.py startapp measurements apps/measurements
python manage.py startapp alerts apps/alerts
python manage.py startapp maintenance apps/maintenance
```
[[startApp]]

# Registrar las apps

Ahora abre:

```
config/settings.py
```

Busca:

```
INSTALLED_APPS = [
    ...
]
```

Y agrega:

```
INSTALLED_APPS = [
    "django.contrib.admin",
    "django.contrib.auth",
    "django.contrib.contenttypes",
    "django.contrib.sessions",
    "django.contrib.messages",
    "django.contrib.staticfiles",

    "apps.machines",
    "apps.sensors",
    "apps.measurements",
    "apps.alerts",
    "apps.maintenance",
]
```

Esto le dice a Django:

> "Estas aplicaciones forman parte de mi proyecto."


# Nuestro primer modelo: Machine

Vamos a empezar por la tabla principal.

Abre:

```
apps/machines/models.py
```

Escribe:

```python
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

# ¿Dónde está `machine_id`?

Esta pregunta es importante.

En tu diagrama tienes:

```
machine_id SERIAL PK
```

Pero nosotros no escribimos:

```
machine_id = ...
```

Django automáticamente agrega un campo `id` como clave primaria si no defines uno.

Conceptualmente:

```
Machine
├── id           ← PK automática
├── name
├── model
├── location
└── status
```

En PostgreSQL tendremos una columna de identificación automática.

En versiones modernas de Django, el tipo exacto puede depender de la configuración del proyecto (`BigAutoField` por defecto en proyectos nuevos), así que no debemos asumir literalmente `SERIAL` solo porque tu diagrama lo muestra.

# Ahora Sensor
![[Pasted image 20260918135914.png|290]]

Abre:

```
apps/sensors/models.py
```

Escribe:

```python
from django.db import models

from apps.machines.models import Machine


class Sensor(models.Model):

    machine = models.ForeignKey(
        Machine,
        on_delete=models.CASCADE,
        related_name="sensors",
    )

    name = models.CharField(max_length=100)

    sensor_type = models.CharField(max_length=50)

    unit = models.CharField(max_length=20)

    def __str__(self):
        return self.name
```

### `related_name`

Tenemos:

```
related_name="sensors"
```

Esto nos permite hacer algo muy bonito con Django ORM.

Si tenemos:

```
machine = Machine.objects.get(id=1)
```

podemos obtener sus sensores:

```
machine.sensors.all()
```

Sin `related_name`, Django utilizaría un nombre inverso menos expresivo.

Esto será muy útil cuando hagamos nuestra API.

# Aquí aparece algo MUY importante: ForeignKey

Tu diagrama dice:

```
Machine
   │
   │ 1:N
   ▼
Sensor
```

Eso significa:

> Una máquina puede tener muchos sensores.

Por ejemplo:

```
CNC-001
 │
 ├── Temperature
 ├── Vibration
 ├── Pressure
 └── Current
```

Pero un sensor pertenece a una máquina.

Eso es exactamente:

```
machine = models.ForeignKey(...)
```



# Measurement
![[Pasted image 20260918140617.png]]

Ahora:

```
apps/measurements/models.py
```

Pon:

```python
from django.db import models

from apps.sensors.models import Sensor


class Measurement(models.Model):

    sensor = models.ForeignKey(
        Sensor,
        on_delete=models.CASCADE,
        related_name="measurements",
    )

    value = models.FloatField()

    timestamp = models.DateTimeField()

    def __str__(self):
        return f"{self.sensor.name}: {self.value}"
```

## Nuestra relación ahora es

```
Machine
   │
   │ 1:N
   ▼
Sensor
   │
   │ 1:N
   ▼
Measurement
```

Por ejemplo:

```
Machine: CNC-001

    Sensor: Motor Temperature

        Measurement
        72.5 °C
        2026-09-18 10:00

        Measurement
        73.1 °C
        2026-09-18 10:01

        
```

---

## ¿Por qué `FloatField`?

Tu diagrama tiene:

```
value float
```

Por eso usamos:

```
value = models.FloatField()
```

Pero hay una consideración interesante para un proyecto industrial real:

Si posteriormente almacenamos mediciones donde la precisión decimal sea crítica, podemos estudiar `DecimalField` en lugar de `FloatField`.

Para esta primera versión, `FloatField` está bien.

# Alert

![[Pasted image 20260918154532.png|488]]

Ahora:

```
apps/alerts/models.py
```

Pon:

```python
from django.db import models

from apps.machines.models import Machine
from apps.sensors.models import Sensor


class Alert(models.Model):

    class Severity(models.TextChoices):
        LOW = "LOW", "Low"
        MEDIUM = "MEDIUM", "Medium"
        HIGH = "HIGH", "High"

    machine = models.ForeignKey(
        Machine,
        on_delete=models.CASCADE,
        related_name="alerts",
    )

    sensor = models.ForeignKey(
        Sensor,
        on_delete=models.CASCADE,
        related_name="alerts",
    )

    value = models.FloatField()

    threshold = models.FloatField()

    severity = models.CharField(
        max_length=10,
        choices=Severity.choices,
    )

    resolved = models.BooleanField(default=False)

    created_at = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return f"{self.machine.name} - {self.severity}"
```

---

## ¿Por qué Alert tiene Machine Y Sensor?

Podríamos preguntarnos:

> Si `Sensor` ya pertenece a `Machine`, ¿para qué guardar `machine` otra vez?

Es una buena pregunta.

Tenemos:

```
Alert
├── machine
└── sensor
```

El sensor ya nos permite llegar a la máquina:

```
alert.sensor.machine
```

Por tanto, técnicamente podríamos modelar solamente:

```
sensor = models.ForeignKey(Sensor, ...)
```

y obtener la máquina mediante:

```
alert.sensor.machine
```

Pero conservar `machine` directamente en `Alert` puede ser útil para consultas, filtros y para representar explícitamente la máquina afectada.

**Sin embargo**, introduce una posibilidad de inconsistencia:

```
Alert.machine = CNC-001
Alert.sensor = sensor perteneciente a CNC-002
```

Eso sería incorrecto.

Por eso, para un diseño más normalizado, podemos considerar después si realmente necesitamos ambas relaciones.

Para nuestra primera versión, podemos mantener ambas y añadir validación para garantizar que sean consistentes.

Esto es un buen ejemplo de algo que aprenderemos durante el proyecto: **que un diagrama de base de datos no es simplemente dibujar tablas; también hay que pensar en las reglas de integridad.**

# Maintenance

Ahora corregimos la tabla de tu imagen.

Abre:

```
apps/maintenance/models.py
```

Pon:

```python
from django.contrib.auth.models import User
from django.db import models

from apps.machines.models import Machine


class Maintenance(models.Model):

    class MaintenanceType(models.TextChoices):
        PREVENTIVE = "PREVENTIVE", "Preventive"
        CORRECTIVE = "CORRECTIVE", "Corrective"

    machine = models.ForeignKey(
        Machine,
        on_delete=models.CASCADE,
        related_name="maintenance_records",
    )

    technician = models.ForeignKey(
        User,
        on_delete=models.SET_NULL,
        null=True,
        blank=True,
    )

    maintenance_type = models.CharField(
        max_length=20,
        choices=MaintenanceType.choices,
    )

    description = models.TextField()

    scheduled_date = models.DateField()

    completed = models.BooleanField(default=False)

    completed_date = models.DateField(
        null=True,
        blank=True,
    )

    def __str__(self):
        return f"{self.machine.name} - {self.maintenance_type}"
```

## ¿Por qué usamos `User`?

Django ya tiene un sistema de usuarios.

Por ejemplo:

```
User
├── username
├── password
├── email
├── first_name
└── last_name
```

En lugar de crear nosotros otra tabla:

```
technicians
```

podemos aprovechar el sistema de autenticación de Django.

Así:

```
User
   │
   │
   ▼
Maintenance
```

Y un mantenimiento puede registrar qué usuario/técnico lo realizó.

## ¿Por qué `SET_NULL`?

Tenemos:

```
on_delete=models.SET_NULL
```

y:

```
null=True
```

Esto significa:

> Si eliminamos el usuario, no queremos borrar el historial de mantenimiento.

Por ejemplo:

```
Maintenance #25
Machine: CNC-001
Technician: Juan
```

Si Juan deja de existir como usuario:

```
Maintenance #25
Machine: CNC-001
Technician: NULL
```

El registro histórico permanece.

Para registros históricos suele ser más apropiado que `CASCADE`.

### Ahora tenemos todos los modelos

Nuestra arquitectura lógica queda:

```
                    ┌──────────────┐
                    │    Machine   │
                    └──────┬───────┘
                           │
              ┌────────────┼────────────┐
              │            │            │
              ▼            ▼            ▼
           Sensor        Alert      Maintenance
              │
              │
              ▼
        Measurement
```

# Antes de crear las tablas: `makemigrations`

Ahora Django debe detectar nuestros modelos.

Ejecuta:

```python
python manage.py makemigrations
```

Deberías ver algo parecido a:

```bash
Migrations for 'machines':
  apps/machines/migrations/0001_initial.py
    + Create model Machine

Migrations for 'sensors':
  apps/sensors/migrations/0001_initial.py
    + Create model Sensor

Migrations for 'measurements':
  apps/measurements/migrations/0001_initial.py
    + Create model Measurement

Migrations for 'alerts':
  apps/alerts/migrations/0001_initial.py
    + Create model Alert

Migrations for 'maintenance':
  apps/maintenance/migrations/0001_initial.py
    + Create model Maintenance
```

## ¿Qué acaba de ocurrir?

Este es uno de los conceptos más importantes de Django:

```
models.py
    │
    │ makemigrations
    ▼
0001_initial.py
```

Django creó **archivos de migración**.

Pero atención:

### `makemigrations` NO modifica todavía PostgreSQL.

Solamente crea las instrucciones de migración.

# Ahora sí: `migrate`

Ejecuta:

```
python manage.py migrate
```

Ahora:

```
Migration
    ↓
SQL
    ↓
PostgreSQL
```

Y PostgreSQL creará nuestras tablas.

# Ver las migraciones

Puedes ejecutar:

```
python manage.py showmigrations
```

Deberías ver algo parecido:

```
machines
 [X] 0001_initial

sensors
 [X] 0001_initial

measurements
 [X] 0001_initial

alerts
 [X] 0001_initial

maintenance
 [X] 0001_initial
```

La `[X]` significa:

> Esta migración ya fue aplicada.


# Ver el SQL que Django generaría

Esta parte es excelente para entender la relación Django ↔ PostgreSQL.

Puedes ejecutar:

```
python manage.py sqlmigrate machines 0001
```

Django te mostrará el SQL correspondiente a esa migración.

No necesitas escribirlo tú.

Pero ahora puedes comparar:

```
Python
────────────────────
class Machine(models.Model):
    name = models.CharField(...)
```

con algo parecido a:

```
CREATE TABLE ...
```

Y empezarás a ver cómo el ORM traduce tus modelos Python a estructuras SQL.

# Una prueba real con Django ORM

Ahora quiero que hagamos algo que te ayudará a entender que **no necesitas escribir SQL para las operaciones normales**.

Ejecuta:

```
python manage.py shell
```

Y dentro:

```
from apps.machines.models import Machine
```

Crea una máquina:

```
machine = Machine.objects.create(
    name="CNC-001",
    model="Haas VF-2",
    location="Production Area A",
)
```

Ahora:

```
machine
```

Deberías obtener algo como:

```
<Machine: CNC-001>
```

Comprueba:

```
Machine.objects.all()
```

Y deberías ver:

```
<QuerySet [<Machine: CNC-001>]>
```

---

# Crear un sensor

Todavía dentro del shell:

```
from apps.sensors.models import Sensor
```

Luego:

```
sensor = Sensor.objects.create(
    machine=machine,
    name="Motor Temperature",
    sensor_type="TEMPERATURE",
    unit="°C",
)
```

Ahora:

```
machine.sensors.all()
```

Obtendrás:

```
<QuerySet [<Sensor: Motor Temperature>]>
```

Observa la magia del `related_name`:

```
machine.sensors.all()
```

Django sabe que esos sensores están relacionados con esa máquina.

# Crear una medición

Importa:

```
from apps.measurements.models import Measurement
```

Y:

```
from django.utils import timezone
```

Después:

```
measurement = Measurement.objects.create(
    sensor=sensor,
    value=72.5,
    timestamp=timezone.now(),
)
```

Ahora podemos hacer:

```
sensor.measurements.all()
```

Y tendremos nuestra medición.