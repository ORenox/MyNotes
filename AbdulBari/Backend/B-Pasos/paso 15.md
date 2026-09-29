Test de JWT,

Ya probamos modelos, creación, validaciones, filtros y permisos. Ahora vamos a comprobar que el endpoint:

```
POST /api/token/
```

se comporte correctamente.


### Test con credenciales válidas

Crea `tests/test_authentication.py`:

```python
import pytest


@pytest.mark.django_db
def test_obtain_jwt_token(api_client, user):
    response = api_client.post(
        "/api/token/",
        {
            "username": "testuser",
            "password": "testpassword123",
        },
        format="json",
    )

    assert response.status_code == 200
    assert "access" in response.data
    assert "refresh" in response.data
```

Aquí estamos comprobando:

```
username + password
        │
        ▼
POST /api/token/
        │
        ▼
    credenciales
       válidas
        │
        ▼
      HTTP 200
        │
   ┌────┴────┐
   ▼         ▼
 access    refresh
```

La fixture `user` que ya creaste en `conftest.py` se encarga de crear:

```
username="testuser"
password="testpassword123"
```

### Test con contraseña incorrecta

Agrega:

```python
@pytest.mark.django_db
def test_obtain_jwt_token_with_invalid_password(api_client, user):
    response = api_client.post(
        "/api/token/",
        {
            "username": "testuser",
            "password": "wrong_password",
        },
        format="json",
    )

    assert response.status_code == 401
```

Estamos probando el caso negativo:

```
usuario correcto
       +
password incorrecto
       │
       ▼
    HTTP 401
```

### Test con usuario inexistente

```python
@pytest.mark.django_db
def test_obtain_jwt_token_with_unknown_user(api_client):
    response = api_client.post(
        "/api/token/",
        {
            "username": "does_not_exist",
            "password": "testpassword123",
        },
        format="json",
    )

    assert response.status_code == 401
```

Esto es importante porque no solamente debemos probar el camino exitoso.

Tenemos:

```
                 JWT
                  │
        ┌─────────┴─────────┐
        ▼                   ▼
   credenciales          credenciales
      válidas               inválidas
        │                   │
        ▼                   ▼
      200                  401
        │
   access + refresh
```

### 4. Ejecuta

```
pytest tests/test_authentication.py -v
```

Y luego:

```
pytest -v
```