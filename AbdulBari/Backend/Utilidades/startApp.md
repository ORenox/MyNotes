

- `migrations/` (Carpeta): Almacena el historial de cambios de tu base de datos.
    - `__init__.py`: Un archivo vacío que le dice a Python que esta carpeta es un paquete.
- `__init__.py`: Al igual que el anterior, indica que la aplicación en sí es un paquete de Python.
- `admin.py`: El archivo de configuración para **registrar tus modelos en el panel de administración** nativo de Django.
- `apps.py`: Contiene la **configuración principal de la aplicación** (como el nombre y el tipo de campo clave por defecto).
- `models.py`: El lugar donde **defines las tablas de tu base de datos** usando código Python (el ORM).
- `tests.py`: El archivo destinado a **escribir pruebas unitarias** para verificar que tu código funcione bien.
- `views.py`: El archivo donde **escribes la lógica que procesa las peticiones web** y devuelve las respuestas (HTML, JSON, etc.).

---

⚠️ **Nota importante sobre tu comando:**  
Al ejecutar `python manage.py startapp machines apps/machines`, Django creará la estructura dentro de `apps/machines`, pero **no creará automáticamente el archivo `urls.py`**. Si planeas que tus aplicaciones manejen sus propias rutas de navegación, tendrás que crear ese archivo a mano en cada carpeta.