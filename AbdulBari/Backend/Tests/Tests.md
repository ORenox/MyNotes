Probaríamos cosas reales:

```d
Machine
 ├── create
 ├── retrieve
 ├── update
 └── delete

Sensor
 ├── create
 └── measurements

Authentication
 ├── login
 └── unauthorized request

Alerts
 └── temperature threshold
```

Por ejemplo:

```python
def test_create_machine():
    response = client.post(
        "/api/machines/",
        {
            "name": "CNC 01",
            "model": "VF-2",
            "location": "Area A"
        }
    )

    assert response.status_code == 201
```

Y ejecutar:

```python
pytest
```