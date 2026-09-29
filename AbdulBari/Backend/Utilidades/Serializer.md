Este concepto es fundamental.

Django tiene objetos Python:

```
Machine(...)
```

Pero una API REST normalmente devuelve:

```
{
    "id": 1,
    "name": "CNC-001"
}
```

El **Serializer** convierte entre esos mundos:

```
Django Model
     ↕
Serializer
     ↕
JSON
```