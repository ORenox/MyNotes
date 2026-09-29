```python
from rest_framework.routers import DefaultRouter
from apps.measurements.views import MeasurementViewSet

  

router = DefaultRouter()


router.register(

	"measurements",
	MeasurementViewSet,
	basename="measurement"
	
)

urlpatterns = router.urls

```

Este código sirve para **generar automáticamente todas las rutas URL (endpoints)** para un CRUD completo en tu API, utilizando Django REST Framework (DRF).

Las Importaciones

- `from rest_framework.routers import DefaultRouter`: Importa la herramienta de DRF encargada de mapear de forma automática la lógica de tus vistas (`ViewSets`) con las URLs estándar de una API REST.
- `from apps.measurements.views import MeasurementViewSet`: Importa tu clase de vistas para las mediciones. Un `ViewSet` es un controlador que ya incluye la lógica de las acciones comunes (como `list`, `create`, `retrieve`, `update`, `destroy`).
## Instanciación del Router


```python
router = DefaultRouter()
```


Crea una instancia del enrutador por defecto. Además de generar las URLs, `DefaultRouter` te regala automáticamente una **página de inicio para la API** (una interfaz web interactiva) donde puedes ver todos los endpoints disponibles cuando navegas a la raíz de tu API.

## Registro del ViewSet


```python

router.register(
    "measurements",
    MeasurementViewSet,
    basename="measurement"
)
```


Aquí le dices al enrutador qué quieres exponer:

- `"measurements"`: Es el **prefijo de la URL**. Significa que tus rutas empezarán con `/measurements/`.
- `MeasurementViewSet`: Es el conjunto de vistas que manejará las peticiones que lleguen a ese prefijo.
- `basename="measurement"`: Es el **nombre base** que usará Django para nombrar internamente las URLs (útil si después necesitas usar la función `reverse('measurement-list')` en tus pruebas o código).

## Generación de las URLs


```python

urlpatterns = router.urls
```


Esta línea extrae la lista de URLs generadas automáticamente y se las asigna a `urlpatterns` para que Django las reconozca.

---