Permisos

Ya tenemos:

```python
permission_classes = [IsAuthenticated]
```

Eso solamente dice:

> "Tienes que estar autenticado."

Ahora queremos controlar **qué puede hacer cada usuario**.

## Autenticación vs autorización

Ya tienes autenticación:

```d
¿Quién eres?
     ↓
JWT
     ↓
Usuario autenticado
```

Ahora autorización:

```d
¿Qué puedes hacer?
     ↓
Permissions
     ↓
¿Permitido?
```

Por ejemplo:

```
admin
 ├── GET machines       ✅
 ├── POST machines      ✅
 ├── PATCH machines     ✅
 └── DELETE machines    ✅

operador
 ├── GET machines       ✅
 ├── POST measurements  ✅
 ├── PATCH machines     ❌
 └── DELETE machines    ❌
```

# `IsAuthenticated`

Ya lo usamos:

```
from rest_framework.permissions import IsAuthenticated
```

y:

```
permission_classes = [IsAuthenticated]
```

Esto significa:

```
No autenticado → 401
Autenticado    → puede continuar
```

Pero todavía no distingue entre usuarios.

# `IsAdminUser`

DRF también proporciona:

```python
from rest_framework.permissions import IsAdminUser
```

Esto permite solamente usuarios considerados administradores.

Podríamos tener:

```python
class MachineViewSet(viewsets.ModelViewSet):

    queryset = Machine.objects.all()
    serializer_class = MachineSerializer
    permission_classes = [IsAdminUser]
```

Ahora:

```
Superuser/admin → permitido
Usuario normal  → 403
No autenticado  → 401
```

Pero probablemente **no queremos que toda nuestra API sea solamente para administradores**.

Necesitamos algo más flexible.

# Nuestro primer permiso personalizado

Vamos a crear:

```d
apps/
└── permissions.py
```

Pero aquí quiero que pensemos en la arquitectura.

Tenemos:

```
apps/
├── machines/
├── sensors/
├── measurements/
├── alerts/
├── maintenance/
└── permissions.py
```

Creamos:

```python
from rest_framework.permissions import BasePermission


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

La lógica es:

```
GET
 ↓
¿público?
 ↓
sí
```

Mientras que:

```
POST / PUT / PATCH / DELETE
          ↓
      ¿es staff?
       /     \
     sí       no
     ↓         ↓
 permitido    403
```


# ¿Por qué `GET` no necesita autenticación aquí?

Esto es una **decisión de diseño**, no una regla universal.

Podemos decidir que nuestro sistema permita consultar máquinas públicamente:

```
GET /api/machines/
```

pero que modificar máquinas requiera privilegios.

Entonces:

```
GET       → cualquiera
POST      → staff
PUT       → staff
PATCH     → staff
DELETE    → staff
```

En un sistema industrial real probablemente querríamos una política más restrictiva, pero para aprender permisos esta regla nos permite entender claramente la diferencia.

# Aplicarlo a Machine

En:

```
apps/machines/views.py
```

podríamos hacer:

```python
from rest_framework import viewsets

from apps.machines.models import Machine
from apps.machines.serializers import MachineSerializer
from apps.permissions import IsAdminOrReadOnly


class MachineViewSet(viewsets.ModelViewSet):

    queryset = Machine.objects.all()
    serializer_class = MachineSerializer
    permission_classes = [IsAdminOrReadOnly]
```

Ahora prueba en Postman.

### Sin autenticación

```
GET /api/machines/
```

debería permitirlo.

Pero:

```
POST /api/machines/
```

debería rechazarlo.

# ¿Y Measurements?

Aquí podríamos tomar otra decisión.

Las mediciones son datos que normalmente vienen de un dispositivo:

```
ESP32 / PLC / sensor
       ↓
POST /api/measurements/
```

Entonces eventualmente podríamos tener un usuario/cliente técnico que tenga permiso para crear mediciones pero no para borrar máquinas.

Esto nos lleva a una arquitectura más realista:

```
                    API
                     │
          ┌──────────┼──────────┐
          │          │          │
        Admin      Operator    Device
          │          │          │
          ▼          ▼          ▼
       Machines   Measurements Measurements
       Users      Alerts       POST only
```

Pero **no vamos a construir todavía un sistema complejo de roles**.

Primero quiero que entiendas el mecanismo de permisos de DRF.

# Una cosa muy importante: `is_staff` ≠ `is_superuser`

Django tiene varios conceptos.

Por ejemplo:

```
request.user.is_authenticated
```

significa:

> ¿El usuario está autenticado?

Mientras:

```
request.user.is_staff
```

significa:

> ¿El usuario tiene permiso para acceder a funcionalidades administrativas según esta bandera?

Y:

```
request.user.is_superuser
```

significa:

> ¿Es superusuario?

No son exactamente lo mismo.

Para nuestro primer permiso podemos utilizar `is_staff`.