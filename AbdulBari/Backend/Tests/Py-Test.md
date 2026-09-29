# ¿Qué vamos a aprender?

Nuestra Sesión 9 tendrá cuatro partes:

### Parte A — Pytest básico

Aprender:

```
assert
fixtures
test functions
```

### Parte B — Tests de Django

Probar:

```
Models
ORM
validaciones
```

### Parte C — Tests de API

Probar:

```
GET
POST
PATCH
DELETE
```

### Parte D — Autenticación y permisos

Probar:

```
JWT
401 Unauthorized
403 Forbidden
```

Al terminar tendremos una estructura parecida a:

```
industrial-monitoring/
│
├── apps/
│   ├── machines/
│   ├── sensors/
│   ├── measurements/
│   ├── alerts/
│   └── maintenance/
│
├── tests/
│   ├── test_machines.py
│   ├── test_measurements.py
│   ├── test_authentication.py
│   └── test_permissions.py
│
├── pytest.ini
└── ...
```