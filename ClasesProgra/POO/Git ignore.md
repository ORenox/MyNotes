
Un `.gitignore` sirve para decirle a Git **qué archivos o carpetas no debe rastrear**.

Por ejemplo, para un proyecto Java:

```
# Archivos compilados de Java
*.class

# Directorios de compilación
target/
out/

# Archivos de IntelliJ IDEA
.idea/
*.iml

# Archivos de VS Code
.vscode/

# Variables de entorno
.env

# Logs
*.log

# Archivos del sistema
.DS_Store
Thumbs.db
```

### Ejemplo de estructura

Supongamos que tienes:

```
mi-proyecto/
├── .git/
├── .gitignore
├── src/
│   └── Main.java
├── target/
│   ├── Main.class
│   └── ...
├── .idea/
├── .env
└── README.md
```

Con este `.gitignore`:

```
target/
.idea/
.env
*.class
```

Git **sí rastrearía**:

```
src/
README.md
.gitignore
```

Pero **ignoraría**:

```
target/
.idea/
.env
*.class
```


### 1. Sin símbolos: nombre exacto

```
.env
```

Significa: ignora archivos o directorios llamados `.env`.

Por ejemplo:

```
.env          ← ignorado
config/.env   ← también puede coincidir
```

---

### 2. `*`: comodín

El `*` significa **"cualquier cantidad de caracteres"**.

```
*.log
```

Significa:

> Ignora cualquier archivo que termine en `.log`.

Por ejemplo:

```
error.log       ← ignorado
server.log      ← ignorado
application.log ← ignorado
```

También:

```
*.class
```

ignora:

```
Main.class
User.class
Producto.class
```

---

### 3. `/` al final: directorio

```
target/
```

El `/` al final indica que estás hablando de un **directorio**.

Por ejemplo:

```
target/
├── Main.class
├── app.jar
└── ...
```

Todo lo que esté dentro de `target/` queda ignorado.

Lo mismo:

```
node_modules/
```

ignora el directorio `node_modules`.

---

### 4. ¿Por qué `target/` y no `target`?

Esta diferencia es importante.

```
target/
```

➡️ específicamente un **directorio** llamado `target`.

Mientras que:

```
target
```

➡️ puede coincidir con un archivo **o** un directorio llamado `target`.

Por eso normalmente se escribe:

```
target/
build/
node_modules/
```

cuando sabes que son carpetas.

---

### 5. Combinándolos

Puedes combinar los patrones.

```
*.log
```

Cualquier archivo `.log`.

```
logs/
```

La carpeta `logs` completa.

```
*.tmp
```

Cualquier archivo temporal `.tmp`.

```
temp*/
```

Directorios cuyo nombre comienza con `temp`.

Por ejemplo:

```
temp/
temp123/
temporary/
```

---

### Una forma fácil de recordarlo

|Patrón|Significado|
|---|---|
|`.env`|Nombre exacto|
|`*.log`|Cualquier cosa que termine en `.log`|
|`target/`|Directorio `target`|
|`build/`|Directorio `build`|
|`temp*`|Cualquier nombre que empiece por `temp`|
|`*.class`|Cualquier archivo que termine en `.class`|

Y hay otro símbolo muy importante: **`/` al principio**.

Por ejemplo:

```
/config.txt
```

significa:

> Ignora `config.txt` **solamente en la raíz del proyecto**.

Mientras:

```
config.txt
```

puede coincidir con `config.txt` en diferentes niveles del proyecto.

Si estás aprendiendo Git, entender bien `*`, `/`, `**`, `!` y los patrones de `.gitignore` te va a ahorrar bastantes problemas.


Aquí tienes una tabla resumen de los **patrones más importantes de `.gitignore`**:

|Patrón|Significado|Ejemplo|
|---|---|---|
|`archivo.txt`|Ignora un archivo/directorio con ese nombre|`config.json`|
|`*.log`|`*` representa cualquier cantidad de caracteres|`error.log`, `app.log`|
|`?`|Cualquier **un solo carácter**|`file?.txt` → `file1.txt`|
|`[abc]`|Uno de los caracteres indicados|`file[123].txt`|
|`[0-9]`|Cualquier carácter dentro del rango|`file[0-9].txt`|
|`carpeta/`|Ignora un directorio|`node_modules/`|
|`/archivo.txt`|Solo en la raíz del repositorio|`/config.txt`|
|`/carpeta/`|Solo esa carpeta en la raíz|`/build/`|
|`carpeta/archivo.txt`|Ruta específica|`config/database.txt`|
|`**/archivo.txt`|Archivo en cualquier nivel|`**/config.json`|
|`**/logs/`|Carpeta `logs` en cualquier nivel|`src/logs/`, `app/logs/`|
|`logs/**`|Todo lo que esté dentro de `logs`|`logs/app.log`|
|`*.class`|Todos los archivos con esa extensión|`Main.class`|
|`temp*`|Todo lo que empiece por `temp`|`temp/`, `temp123`|
|`*temp`|Todo lo que termine en `temp`|`mytemp`, `123temp`|
|`*temp*`|Cualquier nombre que contenga `temp`|`temp`, `mytemp123`|
|`!archivo.txt`|**Excepción**: deja de ignorar ese archivo|`!important.txt`|
|`!carpeta/archivo.txt`|Excepción para un archivo concreto|`!config/important.json`|
|`# comentario`|Comentario, Git lo ignora|`# Archivos temporales`|
|`\#archivo`|Escapa `#` para tratarlo como nombre|`\#archivo`|
|`\!archivo`|Escapa `!` para tratarlo como nombre|`\!archivo`|