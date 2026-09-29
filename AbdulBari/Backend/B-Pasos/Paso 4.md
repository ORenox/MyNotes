**Django ORM + consultas + relaciones**.

Resumen
# Lo que acabas de aprender

Ya puedes hacer:
### Crear

```python
Machine.objects.create(...)
```

### Leer

```python
Machine.objects.all()
```

```python
Machine.objects.get(...)
```

```python
Machine.objects.filter(...)
```

### Actualizar

```python
machine.save()
```

### Eliminar

```python
machine.delete()
```

### Contar

```python
Machine.objects.count()
```

### Verificar existencia

```python
Machine.objects.filter(...).exists()
```

### Ordenar

```python
Machine.objects.order_by(...)
```

### Agregar

```python
Measurement.objects.aggregate(...)
```

### Atravesar relaciones

```python
Machine.objects.filter(
    sensors__measurements__value__gt=80
)
```

Eso ya es una base bastante sólida de Django ORM.


--- 


# Entrar al Django Shell

Vamos a trabajar directamente con el ORM.

```python
python manage.py shell
```

Verás algo parecido a:

```
Python ...
>>>
```

Este shell nos permite ejecutar Python utilizando todo el contexto de Django.

# Importar nuestros modelos

Vamos a importar todos:

```
from apps.machines.models import Machine
from apps.sensors.models import Sensor
from apps.measurements.models import Measurement
from apps.alerts.models import Alert
from apps.maintenance.models import Maintenance
```

Y también:

```
from django.contrib.auth.models import User
```

# Crear una Machine

Primero:

```
machine = Machine.objects.create(
    name="CNC-001",
    model="Haas VF-2",
    location="Production Area A",
)
```

Django devuelve algo como:

```
<Machine: CNC-001>
```

Acabas de hacer un `INSERT` en PostgreSQL.

Conceptualmente:

```
Machine.objects.create(...)
            ↓
         Django ORM
            ↓
        SQL INSERT
            ↓
       PostgreSQL
```

# Consultar todas las máquinas

```
Machine.objects.all()
```

Obtendrás:

```
<QuerySet [<Machine: CNC-001>]>
```

`QuerySet` es uno de los conceptos fundamentales de Django.

Puedes pensar en él como:

> Una colección de resultados que Django puede convertir en una consulta SQL.


# Crear más máquinas

Vamos a tener algunos datos para practicar.

```
Machine.objects.create(
    name="CNC-002",
    model="Haas VF-3",
    location="Production Area A",
)
```

```
Machine.objects.create(
    name="Robot-001",
    model="ABB IRB 120",
    location="Assembly Area",
)
```

Ahora:

```
Machine.objects.all()
```

Deberías tener tres máquinas.

# `get()`

Si queremos obtener una máquina específica:

```
machine = Machine.objects.get(name="CNC-001")
```

Ahora:

```
machine.name
```

Resultado:

```
'CNC-001'
```

Y:

```
machine.model
```

Resultado:

```
'Haas VF-2'
```

# Diferencia entre `get()` y `filter()`

Esto es importante.

### `get()`

```
Machine.objects.get(name="CNC-001")
```

Espera encontrar **exactamente un objeto**.

Si no existe:

```
Machine.DoesNotExist
```

Si encuentra varios:

```
Machine.MultipleObjectsReturned
```

---

### `filter()`

```
Machine.objects.filter(location="Production Area A")
```

Puede devolver:



```
<QuerySet [
    <Machine: CNC-001>,
    <Machine: CNC-002>
]>
```

Por eso:

```
get()
 ↓
un objeto

filter()
 ↓
QuerySet
```

# Filtrar por status

Recordemos nuestro modelo:

```python
class Status(models.TextChoices):
    ACTIVE = "ACTIVE"
    MAINTENANCE = "MAINTENANCE"
    OFFLINE = "OFFLINE"
```

Podemos hacer:

```python
Machine.objects.filter(status="ACTIVE")
```

Como `ACTIVE` es el valor por defecto, nuestras máquinas nuevas deberían aparecer ahí.

También podemos utilizar la clase:

```
Machine.objects.filter(
    status=Machine.Status.ACTIVE
)
```

Prefiero esta segunda forma porque evita escribir strings arbitrarios.

# Filtrar por ubicación

```python
Machine.objects.filter(
    location="Production Area A"
)
```

También podemos usar:

```python
Machine.objects.filter(
    location__icontains="production"
)
```

Esto significa:

> Busca ubicaciones que contengan "production", sin importar mayúsculas/minúsculas.

# Algunos lookups importantes

Django tiene una sintaxis muy potente:

```python
field__lookup
```

Por ejemplo:

```python
name__exact
name__icontains
name__startswith
name__endswith
id__gt
id__gte
id__lt
id__lte
```

Ejemplo:

```python
Machine.objects.filter(
    name__startswith="CNC"
)
```

Devuelve las máquinas cuyo nombre comienza con `CNC`.

# Actualizar una máquina

Tenemos:

```
machine = Machine.objects.get(name="CNC-001")
```

Podemos modificar:

```python
machine.status = Machine.Status.MAINTENANCE
```

Y guardar:

```
machine.save()
```

Ahora:

```
machine.status
```

debería devolver:

```
'MAINTENANCE'
```

Para que Django verifique que el valor asignado es válido antes de guardarlo en la consola, debes llamar explícitamente al método **`full_clean()`** antes del `.save()`.

Mira este ejemplo en la consola de cómo se comporta:

python

```python
>>> machine.status = "hola"

# Si llamas a full_clean(), Django lanzará el error de validación
>>> machine.full_clean()
ValidationError: {'status': ["El valor 'hola' no es una opción válida."]}

# Si no capturaste el error y haces save(), se guardará directo en la BD
>>> machine.save() 
```

# Verificar el cambio

```PYTHON
Machine.objects.filter(
    status=Machine.Status.MAINTENANCE
)
```

Deberías encontrar `CNC-001`.

# Eliminar

También podemos:

```
machine.delete()
```

Pero **no hagas esto todavía** con `CNC-001`, porque la usaremos más adelante.

La operación sería:

```
object.delete()
      ↓
DELETE
      ↓
PostgreSQL
```

Y recuerda que en nuestro modelo tenemos relaciones `CASCADE`.

Si una máquina tiene sensores, eliminarla puede eliminar esos sensores y otros registros relacionados.

Por eso los `delete()` deben manejarse con cuidado en sistemas reales.

# Crear sensores

Ahora vamos a utilizar las relaciones.

Primero:

```python
machine = Machine.objects.get(name="CNC-001")
```

Creamos un sensor:

```python
temperature_sensor = Sensor.objects.create(
    machine=machine,
    name="Motor Temperature",
    sensor_type="TEMPERATURE",
    unit="°C",
)
```

Otro:

```
vibration_sensor = Sensor.objects.create(
    machine=machine,
    name="Motor Vibration",
    sensor_type="VIBRATION",
    unit="mm/s",
)
```

# Consultar sensores de una máquina

Gracias a:

```
related_name="sensors"
```

podemos hacer:

```
machine.sensors.all()
```

Obtendrás algo como:

```
<QuerySet [
    <Sensor: Motor Temperature>,
    <Sensor: Motor Vibration>
]>
```

Esto representa:

```
Machine
   │
   ├── Motor Temperature
   └── Motor Vibration
```

# Ir en la dirección contraria

Tenemos un sensor:

```
temperature_sensor
```

Podemos acceder a su máquina:

```
temperature_sensor.machine
```

Resultado:

```
<Machine: CNC-001>
```

Esto es muy importante:

```
machine
   │
   └── sensors

sensor
   │
   └── machine
```

Django maneja ambas direcciones de la relación.

# Crear Measurements

Ahora:

```
from django.utils import timezone
```

Creamos algunas mediciones:

```
Measurement.objects.create(
    sensor=pressure_sensor,
    value=65.4,
    timestamp=timezone.now(),
)
```

Otra:

```
Measurement.objects.create(
    sensor=pressure_sensor,
    value=68.2,
    timestamp=timezone.now(),
)
```

Otra:

```
Measurement.objects.create(
    sensor=pressure_sensor,
    value=72.5,
    timestamp=timezone.now(),
)
```

# Consultar mediciones de un sensor

Gracias a:

```
related_name="measurements"
```

podemos:

```
temperature_sensor.measurements.all()
```

Y veremos las mediciones.

# Filtrar relaciones

Aquí empieza lo interesante.

Supongamos que queremos:

> Todas las mediciones del sensor de temperatura.

Podemos hacer:

```python
Measurement.objects.filter(
    sensor=temperature_sensor
)
```

Pero Django permite atravesar relaciones:

```python
Measurement.objects.filter(
    sensor__name="Motor Temperature"
)
```

Y aún más:

```python
Measurement.objects.filter(
    sensor__machine__name="CNC-001"
)
```

Observa:

```
Measurement
    ↓
sensor
    ↓
machine
    ↓
name
```

La sintaxis:

```
sensor__machine__name
```

representa justamente ese recorrido.
# Esto equivale conceptualmente a JOIN

En SQL tendrías que pensar en algo parecido a:

```sql
SELECT *
FROM measurements
JOIN sensors
  ON measurements.sensor_id = sensors.id
JOIN machines
  ON sensors.machine_id = machines.id
WHERE machines.name = 'CNC-001';
```

Con Django:

```
Measurement.objects.filter(
    sensor__machine__name="CNC-001"
)
```

Esto es una de las grandes ventajas del ORM.

# Ordenar resultados

Supongamos:

```python
Measurement.objects.all()
```

Podemos ordenar:

```python
Measurement.objects.order_by("value")
```

Ascendente.

Para descendente:

```python
Measurement.objects.order_by("-value")
```

El `-` significa descendente.

# Obtener las últimas mediciones

Podemos hacer:

```python
Measurement.objects.order_by("-timestamp")
```

Y limitar:

```python
Measurement.objects.order_by("-timestamp")[:10]
```

Esto significa:

> Dame las 10 mediciones más recientes.

Muy útil para nuestro futuro dashboard.

# `first()` y `last()`

También:

```
Measurement.objects.order_by("-timestamp").first()
```

Obtiene la medición más reciente.

Y:

```
Measurement.objects.order_by("timestamp").first()
```

obtiene la más antigua.

# Crear una alerta

Supongamos que el sensor alcanza:

```
87.5 °C
```

Creamos:

```
Alert.objects.create(
    machine=machine,
    sensor=pressure_sensor,
    value=87.5,
    threshold=80.0,
    severity=Alert.Severity.HIGH,
)
```

Ahora:

```
Alert.objects.all()
```

# Consultar alertas activas

Como tenemos:

```
resolved = models.BooleanField(default=False)
```

podemos:

```python
Alert.objects.filter(
    resolved=False
)
```

Eso sería:

> Alertas todavía no resueltas.

# Resolver una alerta

```python
alert = Alert.objects.first()
```

Luego:

```
alert.resolved = True
alert.save()
```

Y:

```
Alert.objects.filter(resolved=False)
```

ya no debería mostrar esa alerta.

# Crear un usuario

Django ya tiene el modelo `User`.

Podemos crear uno:

```python
user = User.objects.create_user(
    username="technician01",
    password="test_password_123",
)
```

**Nunca guardes contraseñas directamente en un campo normal.**

`create_user()` utiliza el mecanismo de hashing de Django.

# Crear un mantenimiento

Ahora:

```python
Maintenance.objects.create(
    machine=machine,
    technician=user,
    maintenance_type=Maintenance.MaintenanceType.PREVENTIVE,
    description="Routine motor inspection",
    scheduled_date="2026-10-01",
)
```

Ahora tenemos:

```
User
  │
  │ technician
  ▼
Maintenance
  │
  │ machine
  ▼
Machine
```

# Consultar mantenimiento de una máquina

Gracias a:

```
related_name="maintenance_records"
```

podemos:

```python
machine.maintenance_records.all()
```

# `exists()`

A veces no necesitamos los objetos, solamente saber si existen.

Por ejemplo:

```
Machine.objects.filter(
    name="CNC-001"
).exists()
```

Resultado:

```
True
```

Esto es muy útil para validaciones.
# `count()`

¿Cuántas máquinas tenemos?

```
Machine.objects.count()
```

¿Cuántos sensores?

```
Sensor.objects.count()
```

¿Cuántas mediciones?

```
Measurement.objects.count()
```

# Agregaciones

Aquí entramos en algo más interesante.

Podemos calcular el promedio de temperatura:

```python
from django.db.models import Avg
```

Luego:

```
Measurement.objects.filter(
    sensor=pressure_sensor
).aggregate(
    Avg("value")
)
```

Obtendrás algo parecido a:

```
{'value__avg': 68.7}
```

# Máximo y mínimo

```python
from django.db.models import Max, Min
```

```python
Measurement.objects.filter(
    sensor=pressure_sensor
).aggregate(
    Max("value"),
    Min("value"),
)
```

Esto permite hacer cosas como:

```
Temperatura mínima: 65.4
Temperatura máxima: 87.5
Promedio:            72.8
```

sin tener que traer todos los registros a Python.

**Esto es importante:** dejamos que PostgreSQL haga el trabajo de agregación.
# `values()`

Podemos pedir solamente determinados campos:

```python
Machine.objects.values(
    "id",
    "name",
    "status",
)
```

Resultado:

```
[
    {
        "id": 1,
        "name": "CNC-001",
        "status": "MAINTENANCE",
    },
    ...
]
```

Esto será especialmente útil cuando construyamos APIs.

# `values_list()`

También:

```python
Machine.objects.values_list(
    "name",
    flat=True,
)
```

Resultado:

```
[
    "CNC-001",
    "CNC-002",
    "Robot-001",
]
```

# Una consulta más realista

Imagina que queremos:

> Las máquinas activas ubicadas en Production Area A.

Podemos hacer:

```python
Machine.objects.filter(
    status=Machine.Status.ACTIVE,
    location="Production Area A",
)
```

Django genera una consulta SQL equivalente conceptualmente a:

```
WHERE status = 'ACTIVE'
AND location = 'Production Area A'
```

# Consultar máquinas con sensores

Podemos atravesar relaciones.

Por ejemplo:

```python
Machine.objects.filter(
    sensors__sensor_type="TEMPERATURE"
).distinct()
```

Esto significa:

> Dame las máquinas que tienen al menos un sensor de temperatura.

El `distinct()` evita duplicados si una máquina tiene varios sensores que cumplen la condición.

# Una consulta muy interesante __gt

Podemos buscar:

> Máquinas que tengan mediciones superiores a 80.

```python
Machine.objects.filter(
    sensors__measurements__value__gt=80
).distinct()
```

Observa el recorrido:

```
Machine
   ↓
sensors
   ↓
measurements
   ↓
value
```

Y:

```
__gt
```

significa:

```
greater than
>
```

---

# IMPORTANTE
Prueba:

```python
queryset = Machine.objects.filter(
    status=Machine.Status.ACTIVE
)
```

Luego:

```python
print(queryset.query)
```

Django te mostrará el SQL que está generando.

Puede parecerse a:

```
SELECT ...
FROM "machines_machine"
WHERE "machines_machine"."status" = ACTIVE;
```

La idea importante es:

```
Machine.objects.filter(...)
           ↓
        QuerySet
           ↓
       SQL generado
           ↓
       PostgreSQL
```