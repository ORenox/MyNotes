Quiero que distingas estos conceptos.

### Unit test

Prueba una unidad pequeña y aislada.

Por ejemplo:

```
def test_basic_math():
    assert 2 + 2 == 4
```

O una función específica.

```
function
   ↓
test
```

---

### Integration test

Comprueba que varias partes funcionan juntas.

Nuestro:

```
client.get("/api/machines/")
```

hace:

```
URL
 ↓
View
 ↓
ORM
 ↓
Serializer
 ↓
Database
 ↓
Response
```

Eso es mucho más cercano al comportamiento real de nuestra aplicación.