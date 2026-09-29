# Instalar las herramientas

Ejecuta:

```python
python -m pip install pytest pytest-django
```

Después:

```python
python -m pip freeze > requirements.txt
```

Comprueba:

```python
pytest --version
```

Deberías obtener algo parecido a:

```
pytest 8.x.x
```