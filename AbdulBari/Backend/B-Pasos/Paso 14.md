pruebas de filtros, JWT, permisos y cobertura.

Ya tenemos este endpoint:

```
GET /api/measurements/
```

y nuestro `MeasurementViewSet` permite:

```
? sensor=
? min_value=
? max_value=
```

Queremos comprobar que realmente funcionan.

### Agrega estos tests

En `tests/test_measurements.py`:

```python
@pytest.mark.django_db
def test_filter_measurements_by_sensor(
    api_client,
    sensor,
    measurement,
):
    response = api_client.get(
        f"/api/measurements/?sensor={sensor.id}"
    )

    assert response.status_code == 200
    assert len(response.data) == 1
    assert response.data[0]["sensor"] == sensor.id
```

Aquí estamos verificando:

```
GET /api/measurements/?sensor=1
                         │
                         ▼
                  sensor_id = 1
                         │
                         ▼
                solo mediciones
                de ese sensor
```

### Test de `min_value`

Necesitamos varias mediciones. Podemos crear una segunda directamente en el test:

```python
@pytest.mark.django_db
def test_filter_measurements_by_min_value(
    api_client,
    sensor,
    measurement,
):
    Measurement.objects.create(
        sensor=sensor,
        value=30,
        timestamp="2026-09-20T16:00:00Z",
    )

    response = api_client.get(
        "/api/measurements/?min_value=50"
    )

    assert response.status_code == 200
    assert len(response.data) == 1
    assert float(response.data[0]["value"]) >= 50
```

Pero necesitamos importar `Measurement` arriba:

```
from apps.measurements.models import Measurement
```

### Ejecuta los tests

```python
pytest tests/test_measurements.py -v
```

Y después todos los tests:

```
pytest -v
```

Si todo pasa, el siguiente bloque de la **Sesión 9** será:

```
Sesión 9
│
├── ✓ Fixtures
├── ✓ Tests de modelos
├── ✓ Tests de creación de Measurement
├── ✓ Tests de validación
├── → Tests de filtros       ← estamos aquí
├── Tests de JWT
├── Tests de permisos
└── pytest-cov
```

Haz estos tres tests de filtros y ejecuta `pytest -v`. Cuando los tengas, continuamos con **los tests de JWT**.