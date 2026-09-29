Cuando haces:

```python
queryset = Machine.objects.filter(
    status=Machine.Status.ACTIVE
)
```

Django normalmente **no ejecuta inmediatamente la consulta**.

Los QuerySets tienen comportamiento de **evaluación perezosa (lazy evaluation)**.

Por ejemplo:

```
queryset = Machine.objects.filter(...)
```

no significa necesariamente:

```
ejecutar SQL inmediatamente
```

Cuando haces:

```
list(queryset)
```

o:

```
for machine in queryset:
    ...
```

o:

```
queryset.count()
```

Django necesita ejecutar una consulta.

Esto será importantísimo cuando lleguemos a **optimización de APIs**.