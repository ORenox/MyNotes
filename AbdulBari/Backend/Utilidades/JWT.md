Vamos a utilizar:

```python
python -m pip install djangorestframework-simplejwt
```

Después:

```python
python -m pip freeze > requirements.txt
```

Esto actualiza nuestro `requirements.txt`.


JWT significa:

**JSON Web Token**

Es una forma de representar la identidad/autorización del usuario mediante un token.

Por ejemplo, el cliente hace:

```
POST /api/token/
```

enviando:

```
{
    "username": "admin",
    "password": "password123"
}
```

El servidor verifica las credenciales y devuelve tokens.

Conceptualmente:

```
{
    "access": "eyJhbGciOiJIUzI1NiIs...",
    "refresh": "eyJhbGciOiJIUzI1NiIs..."
}
```

El cliente utiliza el `access token` para llamar a nuestra API:

```
GET /api/machines/
Authorization: Bearer eyJhbGciOiJIUzI1NiIs...
```

# JWT no es lo mismo que permisos

Esto es fundamental.

### Autenticación

Pregunta:

> **¿Quién eres?**

JWT responde a esto.

### Autorización

Pregunta:

> **¿Tienes permiso para hacer esto?**

Permissions responden a esto.

Por ejemplo:

```
Usuario autenticado
       │
       ▼
¿Puede eliminar una Machine?
       │
   ┌───┴───┐
   │       │
  Sí      No
   │       │
   ▼       ▼
 DELETE    403
```

