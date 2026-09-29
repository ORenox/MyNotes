#docker
- **ps** :  ver contenedores activos
- **ps -a**: ver contenedores activados y desactivados
- **docker stats** : ver uso de espacio y recursos en tiempo real
- **docker system df** : ver el uso de espacio en el disco general de docker
---
- **rm <nombre_o_id>**: borrar contenedor detenido
- **rm -f <nombre_o_id>**: borrar contenedor incluso si no esta detenido
- **container prune**: borrar todos los contenedores detenido (-a : para forzar todo)
- **image prune -a**:El parámetro `-a` (all) le dice a Docker que borre **absolutamente todas** las imágenes que no estén siendo usadas por un contenedor actual, no solo las que no tienen nombre.
---
- **logs**: docker logs <nombre_o_id>
- **docker logs -f <nombre_o_id>**: Ver los logs en tiempo real (seguimiento)
- **`docker exec -it <nombre_o_id> sh` (o `bash`)**: Entrar a la terminal del contenedor
---
- **docker top <nombre_o_id>**: Inspeccionar toda la configuración (JSON)
---
- **docker pause <nombre_o_id>**: Pausar contenedor
- **docker unpause <nombre_o_id>**: Reanudar contenedor
- **docker restart <nombre_o_id>**: Reiniciar contenedor
---
- `docker compose up -d`: crear el contenedor
- docker compose down: dar de baja al contenedor


