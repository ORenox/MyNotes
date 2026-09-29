Fixtures y API Testing

# Nuestra primera fixture

En:

```
tests/test_machines.py
```

podemos hacer:

```python
import pytest

from apps.machines.models import Machine


@pytest.fixture
def machine():
    return Machine.objects.create(
        name="CNC-001",
        model="Haas VF-2",
        location="Factory A",
    )
```

Ahora podemos utilizarla:

```python
@pytest.mark.django_db
def test_machine_name(machine):

    assert machine.name == "CNC-001"
```

Y:

```python
@pytest.mark.django_db
def test_machine_status(machine):

    assert machine.status == Machine.Status.ACTIVE
```

Pytest ejecuta la fixture antes del test.

Conceptualmente:

```d
test_machine_name(machine)
          │
          ▼
    pytest busca
      fixture
          │
          ▼
      machine()
          │
          ▼
    crea Machine
          │
          ▼
       test
```



# ¿Podemos compartir fixtures?

Sí.

Y aquí aparece un archivo muy importante:

```python
tests/
├── conftest.py
├── test_machines.py
├── test_sensors.py
└── test_measurements.py
```

Creamos:

```python
tests/conftest.py
```

Ponemos:

```python
import pytest

from apps.machines.models import Machine


@pytest.fixture
def machine():

    return Machine.objects.create(
        name="CNC-001",
        model="Haas VF-2",
        location="Factory A",
    )
```

Ahora cualquier test dentro de `tests/` puede utilizar:

```
def test_machine_name(machine):
    ...
```

sin importar la fixture explícitamente.


# `conftest.py` es muy importante

Piensa en:

```
tests/conftest.py
```

como:

> Un lugar para fixtures compartidas por nuestros tests.

Por ejemplo:

```
conftest.py
│
├── machine
├── sensor
├── measurement
├── user
└── api_client
```

Entonces nuestros tests se vuelven mucho más limpios.

# Fixture de Sensor

Ahora agregamos:

```python
from apps.sensors.models import Sensor
```

y:

```python
@pytest.fixture
def sensor(machine):

    return Sensor.objects.create(
        machine=machine,
        name="Temperature Sensor",
        sensor_type="TEMPERATURE",
        unit="C",
    )
```

Fíjate en algo interesante:

```
def sensor(machine):
```

Nuestra fixture `sensor` depende de otra fixture:

```
sensor
  │
  ▼
machine
  │
  ▼
Machine.objects.create()
```

Pytest resuelve automáticamente esa dependencia.

# Fixture de Measurement

Podemos seguir:

```
from apps.measurements.models import Measurement
```

y:

```
@pytest.fixture
def measurement(sensor):

    return Measurement.objects.create(
        sensor=sensor,
        value=75.5,
        timestamp="2026-09-20T15:00:00Z",
    )
```

Ahora tenemos:

```
machine
   │
   ▼
sensor
   │
   ▼
measurement
```

Exactamente igual que nuestro modelo:

```
Machine
   │
   └── Sensor
          │
          └── Measurement
```

# Nuestro `conftest.py`

Podríamos terminar con:

```
import pytest

from apps.machines.models import Machine
from apps.sensors.models import Sensor
from apps.measurements.models import Measurement


@pytest.fixture
def machine():

    return Machine.objects.create(
        name="CNC-001",
        model="Haas VF-2",
        location="Factory A",
    )


@pytest.fixture
def sensor(machine):

    return Sensor.objects.create(
        machine=machine,
        name="Temperature Sensor",
        sensor_type="TEMPERATURE",
        unit="C",
    )


@pytest.fixture
def measurement(sensor):

    return Measurement.objects.create(
        sensor=sensor,
        value=75.5,
        timestamp="2026-09-20T15:00:00Z",
    )
```

# Ahora nuestros tests quedan mucho más limpios

### Machine

```
@pytest.mark.django_db
def test_machine_name(machine):

    assert machine.name == "CNC-001"
```

### Sensor

```
@pytest.mark.django_db
def test_sensor_machine(sensor, machine):

    assert sensor.machine == machine
```

### Measurement

```
@pytest.mark.django_db
def test_measurement_sensor(measurement, sensor):

    assert measurement.sensor == sensor
```

Observa que ya no tenemos que crear manualmente todos los objetos.
# Una fixture que vamos a necesitar: usuario

Como nuestra API utiliza JWT y permisos, necesitamos usuarios para los próximos tests.

En `conftest.py`:

```python
from django.contrib.auth.models import User
```

Y:

```
@pytest.fixture
def user():

    return User.objects.create_user(
        username="testuser",
        password="testpassword123",
    )
```

Y uno para staff:

```
@pytest.fixture
def staff_user():

    return User.objects.create_user(
        username="staffuser",
        password="staffpassword123",
        is_staff=True,
    )
```

Ahora tenemos:

```
user
  ↓
usuario normal

staff_user
  ↓
usuario staff
```

Esto será muy útil para probar:

```
GET
POST
PATCH
DELETE
```

con diferentes permisos.

# Fixture para `APIClient`

También podemos preparar nuestro cliente:

```python
from rest_framework.test import APIClient
```

y:

```python
@pytest.fixture
def api_client():

    return APIClient()
```

Entonces:

```python
@pytest.mark.django_db
def test_get_machines(api_client, machine):

    response = api_client.get("/api/machines/")

    assert response.status_code == 200
```

Mucho más limpio.

# Autenticarnos en tests

DRF nos permite hacer algo muy práctico:

```python
api_client.force_authenticate(user=user)
```

Por ejemplo:

```python
@pytest.mark.django_db
def test_authenticated_get_machines(
    api_client,
    user,
    machine,
):

    api_client.force_authenticate(user=user)

    response = api_client.get("/api/machines/")

    assert response.status_code == 200
```

Esto nos permite probar autenticación sin tener que obtener un JWT real en cada test.

# ¿Entonces no probaremos JWT?

Sí lo probaremos.

Pero hay dos tipos de tests:

### Tests de permisos/autenticación de endpoints

Podemos usar:

```
force_authenticate()
```

porque queremos probar:

> "¿Qué ocurre cuando este usuario autenticado llama al endpoint?"

### Tests del endpoint JWT

Ahí sí queremos probar:

```
username + password
        ↓
POST /api/token/
        ↓
access + refresh
```

Eso lo haremos específicamente.

# Nuestro primer test de permisos

Como creamos:

```d
IsAdminOrReadOnly
```

podemos probar:

### Usuario normal intentando POST

```python
@pytest.mark.django_db
def test_normal_user_cannot_create_machine(
    api_client,
    user,
):

    api_client.force_authenticate(user=user)

    response = api_client.post(
        "/api/machines/",
        {
            "name": "CNC-999",
            "model": "Test Model",
            "location": "Factory Test",
        },
        format="json",
    )

    assert response.status_code == 403
```

Esto es excelente porque estamos verificando una regla de seguridad real.