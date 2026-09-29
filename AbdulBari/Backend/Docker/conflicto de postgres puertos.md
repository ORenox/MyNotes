# Opción 1: Liberar el puerto 5432 (Recomendado)

Debes detener el servicio de PostgreSQL local que está consumiendo el puerto.

- **En Ubuntu/Debian:**
    
    bash
    
    ```
    sudo systemctl stop postgresql
    ```
    
    Usa el código con precaución.
    
- **En macOS (si lo instalaste con Homebrew):**
    
    bash
    
    ```
    brew services stop postgresql
    ```
    
    Usa el código con precaución.
    
- **En Windows (PowerShell como Administrador):**
    
    powershell
    
    ```
    Stop-Service -Name postgresql*
    ```
    
    Usa el código con precaución.
    

Una vez detenido, vuelve a ejecutar `docker compose up -d`.

# Opción 2: Cambiar el puerto en tu `docker-compose.yml`

Si necesitas mantener el PostgreSQL local activo, puedes mapear el contenedor a un puerto diferente de tu máquina (por ejemplo, el `5433`).

Modifica la sección de `ports` de tu servicio de base de datos en el archivo **`docker-compose.yml`**:

yaml

```d
services:
  db: # o industrial-monitoring-db
    image: postgres:17
    ports:
      - "5433:5432" # Cambia el primero (host), mantén el segundo (contenedor)
```


_Nota: Si cambias el puerto al `5433`, recuerda actualizar la variable de entorno `DATABASE_PORT` o `DB_PORT` en la configuración de tu proyecto de Django._