Aquí aprenderías algo muy importante para backend.

Por ejemplo:

```python
class MachineSerializer(serializers.ModelSerializer):

    class Meta:
        model = Machine
        fields = "__all__"
```

Y una API:

```python
class MachineViewSet(viewsets.ModelViewSet):
    queryset = Machine.objects.all()
    serializer_class = MachineSerializer
```

Con un router:

```python
router.register(
    "machines",
    MachineViewSet
)
```

Obtienes:

```
GET     /api/machines/
POST    /api/machines/
GET     /api/machines/1/
PUT     /api/machines/1/
PATCH   /api/machines/1/
DELETE  /api/machines/1/
```