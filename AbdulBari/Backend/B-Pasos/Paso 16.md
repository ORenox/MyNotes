Test permisos y cobertura.

Ya tienes el permiso:

```python
class IsAdminOrReadOnly(BasePermission):

    def has_permission(self, request, view):
        if request.method in ["GET", "HEAD", "OPTIONS"]:
            return True

        return (
            request.user
            and request.user.is_authenticated
            and request.user.is_staff
        )
```

Ahora vamos a probarlo desde la API.

La idea:

```
usuario normal
      │
      ▼
POST /api/machines/
      │
      ▼
is_staff == False
      │
      ▼
    403
```

## Staff sí puede crear

```python
@pytest.mark.django_db
def test_staff_user_can_create_machine(api_client, staff_user):
    api_client.force_authenticate(user=staff_user)

    response = api_client.post(
        "/api/machines/",
        {
            "name": "CNC-999",
            "model": "Test Model",
            "location": "Factory Test",
        },
        format="json",
    )

    assert response.status_code == 201
```

Aquí:

```
staff_user
    │
    ▼
POST /api/machines/
    │
    ▼
is_staff == True
    │
    ▼
  201
```

## Usuario normal sí puede consultar

Este test es importante porque nuestro permiso se llama **`IsAdminOrReadOnly`**.

```python
@pytest.mark.django_db
def test_normal_user_can_read_machines(api_client, user):
    api_client.force_authenticate(user=user)

    response = api_client.get("/api/machines/")

    assert response.status_code == 200
```

Observa que un usuario normal puede:

```
GET       → 200
POST      → 403
PATCH     → 403
DELETE    → 403
```

## Usuario no autenticado puede hacer GET

Debido a cómo escribimos nuestro permiso:

```python
if request.method in ["GET", "HEAD", "OPTIONS"]:
    return True
```

también permitimos lectura pública.

Podemos comprobarlo:

```python
@pytest.mark.django_db
def test_unauthenticated_user_can_read_machines(api_client):
    response = api_client.get("/api/machines/")

    assert response.status_code == 200
```

Esto es una buena demostración de que **los tests documentan el comportamiento que realmente diseñamos**.

## Usuario no autenticado no puede crear

```python
@pytest.mark.django_db
def test_unauthenticated_user_cannot_create_machine(api_client):
    response = api_client.post(
        "/api/machines/",
        {
            "name": "CNC-999",
            "model": "Test Model",
            "location": "Factory Test",
        },
        format="json",
    )

    assert response.status_code == 401
```

En este caso esperamos `403`, no `401`, porque nuestro `IsAdminOrReadOnly` es quien decide el acceso a los métodos de escritura.


**401 — No autenticado**

> "No has demostrado quién eres."

**403 — Autenticado pero sin permiso**

> "Sé quién eres, pero no tienes autorización para hacer esto."

Y eso es justamente lo que queremos comprobar con nuestros tests.