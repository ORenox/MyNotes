
```python
>>> machine.status = "hola"

# Si llamas a full_clean(), Django lanzará el error de validación
>>> machine.full_clean()
ValidationError: {'status': ["El valor 'hola' no es una opción válida."]}

# Si no capturaste el error y haces save(), se guardará directo en la BD
>>> machine.save() 
```
