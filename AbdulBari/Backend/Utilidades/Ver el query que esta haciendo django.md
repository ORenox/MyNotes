```python
queryset = Sensor.objects.filter(
    machine_id=3
)

print(queryset.query)
```
