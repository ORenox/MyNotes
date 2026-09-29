## ¿Qué problema resuelven las fixtures?

Supongamos que tenemos:

```python
def test_machine_name():
    machine = Machine.objects.create(
        name="CNC-001",
        model="Haas VF-2",
        location="Factory A",
    )

    assert machine.name == "CNC-001"
```

Y otro:

```python
def test_machine_location():
    machine = Machine.objects.create(
        name="CNC-001",
        model="Haas VF-2",
        location="Factory A",
    )

    assert machine.location == "Factory A"
```

Y otro:

```python
def test_machine_status():
    machine = Machine.objects.create(
        name="CNC-001",
        model="Haas VF-2",
        location="Factory A",
    )

    assert machine.status == Machine.Status.ACTIVE
```

**Estamos repitiendo datos.**

Las fixtures permiten preparar datos reutilizables:

```python
Fixture
   │
   ├── crea Machine
   ├── crea Sensor
   └── crea Measurement
          │
          ▼
       Tests
```

