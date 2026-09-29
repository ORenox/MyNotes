Hasta ahora hemos comprobado la API manualmente con Postman:

```
Postman
   ↓
HTTP Request
   ↓
Django REST Framework
   ↓
PostgreSQL
```

Ahora queremos que Python pueda comprobar automáticamente que nuestra API sigue funcionando:

```
Pytest
   ↓
Test
   ↓
API
   ↓
Resultado
   ↓
PASSED / FAILED
```

La diferencia es enorme:

```d
Manual:
"Yo probé POST /machines y funcionó."

Automatizado:
"Tenemos 30 tests que comprueban que POST /machines
sigue funcionando cada vez que modificamos el código."
```

# ¿Por qué Pytest y no solamente `unittest`?

Django incluye herramientas basadas en `unittest`, pero Pytest tiene una sintaxis muy cómoda y un ecosistema enorme.

Por ejemplo, un test sencillo:

```
def test_sum():
    assert 2 + 2 == 4
```

No necesitamos:

```
class TestSomething(unittest.TestCase):
    ...
```

Para nuestro proyecto vamos a utilizar:

```
pytest
+
pytest-django
```

`pytest-django` permite que Pytest trabaje correctamente con Django.

# Instalar las herramientas

Ejecuta:

```python
python -m pip install pytest pytest-django
```

Después:

```python
python -m pip freeze > requirements.txt
```

Comprueba:

```
pytest --version
```

Deberías obtener algo parecido a:

```
pytest 8.x.x
```

# Configurar Pytest para Django

En la raíz del proyecto:

```
industrial-monitoring/
```

crea:

```
pytest.ini
```

Es decir:

```
industrial-monitoring/
├── pytest.ini
├── manage.py
├── config/
└── apps/
```

Contenido:

```python
[pytest]
DJANGO_SETTINGS_MODULE = config.settings
python_files = tests.py test_*.py *_tests.py
```

Esto le dice a Pytest:

> "Este proyecto utiliza las settings de `config.settings`."


# Nuestro primer test

Vamos a empezar extremadamente sencillo.

Crea:

```
tests/
└── test_basic.py
```

Código:

```python
def test_basic_math():
    assert 2 + 2 == 4
```

Ahora ejecuta:

```
pytest
```

Deberías obtener algo parecido a:

```
1 passed
```

🎉

Acabas de ejecutar tu primer test automatizado.

# ¿Qué hace `assert`?

Esta línea:

```
assert 2 + 2 == 4
```

significa:

> Espero que esta condición sea verdadera.

Si:

```
2 + 2 == 4
```

es `True`:

```
PASSED
```

Si hacemos:

```
assert 2 + 2 == 5
```

entonces:

```
FAILED
```

Esto parece trivial, pero `assert` es uno de los elementos fundamentales de testing.

# Ahora probemos Django

Vamos a probar nuestro modelo `Machine`.

Crea:

```
tests/test_machines.py
```

Primero:

```python
import pytest

from apps.machines.models import Machine
```

Y:

```python
@pytest.mark.django_db
def test_create_machine():

    machine = Machine.objects.create(
        name="CNC-001",
        model="Haas VF-2",
        location="Factory A",
    )

    assert machine.name == "CNC-001"
    assert machine.model == "Haas VF-2"
    assert machine.location == "Factory A"
```

# ¿Qué significa `@pytest.mark.django_db`?

Esta línea:

```
@pytest.mark.django_db
```

le dice a `pytest-django`:

> Este test necesita acceder a la base de datos de Django.

Sin ella, si intentamos:

```
Machine.objects.create(...)
```

Pytest puede impedir el acceso a la BD.

Conceptualmente:

```
Test
 │
 ├── ¿Necesita DB?
 │       │
 │       └── Sí
 │
 ▼
@pytest.mark.django_db
 │
 ▼
Base de datos de testing
```

# Algo muy importante: no utiliza tu PostgreSQL de desarrollo de la misma manera

Cuando ejecutamos:

```
pytest
```

pytest-django crea/prepara una base de datos de testing.

Conceptualmente:

```
PostgreSQL desarrollo
industrial_monitoring
        │
        │
        ├── NO queremos destruirla
        │
        ▼
PostgreSQL test
test_...
```

Esto es fundamental.

Tus tests no deberían borrar los datos reales que tienes para desarrollar.

# Ahora probemos nuestro modelo de forma más interesante

Podemos comprobar el comportamiento de `status`.

Nuestro modelo tiene:

```python
class Status(models.TextChoices):
    ACTIVE = "ACTIVE", "Active"
    MAINTENANCE = "MAINTENANCE", "Maintenance"
    OFFLINE = "OFFLINE", "Offline"
```

Y:

```python
status = models.CharField(
    max_length=20,
    choices=Status.choices,
    default=Status.ACTIVE,
)
```

Podemos probar el default:

```python
@pytest.mark.django_db
def test_machine_default_status():

    machine = Machine.objects.create(
        name="CNC-002",
        model="Haas VF-3",
        location="Factory B",
    )

    assert machine.status == Machine.Status.ACTIVE
```

Esto comprueba una regla importante de nuestro modelo.

# Probar relaciones

Ahora vamos a comprobar:

```
Machine
   │
   └── Sensor
```

Crea:

```
tests/test_sensors.py
```

```python
import pytest

from apps.machines.models import Machine
from apps.sensors.models import Sensor
```

Y:

```
@pytest.mark.django_db
def test_sensor_belongs_to_machine():

    machine = Machine.objects.create(
        name="CNC-003",
        model="Haas VF-4",
        location="Factory C",
    )

    sensor = Sensor.objects.create(
        machine=machine,
        name="Temperature Sensor",
        sensor_type="TEMPERATURE",
        unit="C",
    )

    assert sensor.machine == machine
```

Y podemos comprobar la relación inversa:

```
assert machine.sensors.count() == 1
```

Por tanto:

```
@pytest.mark.django_db
def test_sensor_belongs_to_machine():

    machine = Machine.objects.create(
        name="CNC-003",
        model="Haas VF-4",
        location="Factory C",
    )

    sensor = Sensor.objects.create(
        machine=machine,
        name="Temperature Sensor",
        sensor_type="TEMPERATURE",
        unit="C",
    )

    assert sensor.machine == machine
    assert machine.sensors.count() == 1
```


# Ahora viene algo mucho más interesante: API testing

Django REST Framework nos proporciona un cliente para probar nuestra API.

Con pytest podemos utilizar:

```python
APIClient
```

Importamos:

```python
from rest_framework.test import APIClient
```

Y podemos hacer:

```python
client = APIClient()
```

Conceptualmente:

```
pytest
  │
  ▼
APIClient
  │
  ▼
DRF
  │
  ▼
ViewSet
  │
  ▼
Serializer
  │
  ▼
Database
```

No necesitamos abrir Postman.

# Primer test de API

Crea:

```python
tests/test_machine_api.py
```

```python
import pytest

from rest_framework.test import APIClient

from apps.machines.models import Machine
```

Ahora:

```python
@pytest.mark.django_db
def test_get_machines():

    Machine.objects.create(
        name="CNC-001",
        model="Haas VF-2",
        location="Factory A",
    )

    client = APIClient()

    response = client.get("/api/machines/")

    assert response.status_code == 200
```

Ya estamos probando una petición HTTP real contra nuestra aplicación Django.

# También podemos comprobar los datos

Podemos hacer:

```python
assert len(response.data) == 1
```

y:

```python
assert response.data[0]["name"] == "CNC-001"
```

Por tanto:

```python
@pytest.mark.django_db
def test_get_machines():

    Machine.objects.create(
        name="CNC-001",
        model="Haas VF-2",
        location="Factory A",
    )

    client = APIClient()

    response = client.get("/api/machines/")

    assert response.status_code == 200
    assert len(response.data) == 1
    assert response.data[0]["name"] == "CNC-001"
```

# Este es el momento en que Testing empieza a ponerse interesante

Nuestro test está comprobando todo este flujo:

```
GET /api/machines/
       │
       ▼
       URL Router
       │
       ▼
MachineViewSet
       │
       ▼
Machine.objects.all()
       │
       ▼
MachineSerializer
       │
       ▼
JSON Response
       │
       ▼
assert
```

Eso es un **integration/API test**.

No estamos probando solamente una función aislada.

Estamos probando varias piezas trabajando juntas.

