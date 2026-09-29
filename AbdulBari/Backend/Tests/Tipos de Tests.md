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