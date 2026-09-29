La partición EFI en un disco ==es un pequeño espacio reservado que contiene los archivos necesarios para arrancar el sistema operativo de la computadora==

**Función:** Almacena los cargadores de arranque, controladores y archivos de firmware que el sistema lee antes de iniciar Windows o Linux. 
**Tamaño:** Suele medir entre 100 MB y 300 MB
**Formato:** Utiliza obligatoriamente el sistema de archivos FAT32.
**Ubicación:** Se crea de forma automática en discos con formato GPT al instalar un sistema operativo moderno.
**Seguridad:** No tiene letra de unidad asignada por defecto para evitar que se borre por accidente, ya que eliminarla impediría que el equipo pueda encender