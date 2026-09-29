Django por sí solo es un framework web.

DRF(Django Rest Framework) agrega herramientas para construir **APIs REST**.

Por ejemplo, nuestro cliente podría ser:

```
Frontend
Postman
Mobile App
ESP32
Otro backend
```

y comunicarse con Django mediante HTTP:

```
GET
POST
PUT
PATCH
DELETE
```

# Instalar Django REST Framework

Activa tu entorno virtual:

```
.venv\Scripts\activate
```

o en Linux/macOS:

```
source .venv/bin/activate
```

Instala:

```
python -m pip install djangorestframework
```

Actualiza:

```
python -m pip freeze > requirements.txt
```