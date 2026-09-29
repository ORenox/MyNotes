**AWK** no es solo un comando, es un lenguaje de programación completo diseñado para procesar texto estructurado en filas y columnas. Su gran ventaja es que lee un archivo línea por línea de forma automática, por lo que no necesitas escribir bucles complejos.
**`awk`**: Es una base de datos miniatura para hacer reportes y cálculos en la terminal.

- **`grep` (Buscar):** Encuentra una aguja en un pajar. Te devuelve la línea entera donde está lo que buscas.
- **`sed` (Modificar):** Cambia la aguja por otra cosa, o elimina partes de la línea.
- **`awk` (Analizar):** Cuenta cuántas agujas hay, cuánto pesan las agujas de la segunda columna o calcula el promedio de su tamaño.
Imagina que tienes un archivo de registro (`servidor.log`) con este contenido:
```
2026-05-01 ERROR Conexión_fallida usuario_admin
2026-05-01 INFO  Inicio_sesión    usuario_invitado
2026-05-01 ERROR Contraseña_inval usuario_admin
````

- **Con `awk` (Procesas columnas):**  
    `awk '$3 == "ERROR" {print $4}' servidor.log`  
    _Resultado:_ Revisa si la columna 3 es "ERROR" y, si es así, te imprime **solo** el nombre del usuario (columna 4).
Cuando AWK lee una línea de texto, la divide automáticamente en **campos (columnas)** usando los espacios en blanco o tabulaciones como separadores.

- **`$0`**: Representa la línea completa.
- **`$1`**: La primera columna.
- **`$2`**: La segunda columna (y así sucesivamente).
- **`NF`**: (Number of Fields) Variable que contiene el número total de columnas de la línea actual. `$NF` imprime la última columna.
- **`NR`**: (Number of Records) Variable que indica el número de la línea actual (empieza en 1).

La sintaxis básica se compone de un patrón (una condición) y una acción entre llaves:

bash

```
awk 'patrón { acción }' archivo.txt
```

Usa el código con precaución.

- Si omites el **patrón**, la acción se aplica a **todas** las líneas.
- Si omites la **acción**, la acción por defecto es **imprimir** la línea completa.

---

Para los ejemplos, imagina que tienes un archivo llamado `usuarios.txt` con este contenido:

text

```
101 Carlos Administrador 2500
102 Ana Desarrollador 3000
103 Pedro Soporte 1800
104 Sofia Desarrollador 3100
```

Usa el código con precaución.

1. Imprimir columnas específicas

Muestra solo los nombres (columna 2) y sus salarios (columna 4).

bash

```
awk '{print $2, $4}' usuarios.txt
# Salida: Carlos 2500, Ana 3000...
```

2. Filtrar por texto (Patrón)

Muestra las líneas completas que contengan la palabra "Desarrollador".

bash

```
awk '/Desarrollador/' usuarios.txt
```

3. Filtrar por condiciones numéricas

Muestra el nombre de los usuarios que ganan más de 2000.

bash

```
awk '$4 > 2000 {print $2}' usuarios.txt
```

4. Cambiar el separador de columnas (`-F`)

Si tus datos están separados por comas (como un archivo CSV) o por dos puntos (como `/etc/passwd`), usa `-F`.

bash

```
awk -F':' '{print $1}' /etc/passwd
```

5. Imprimir con formato limpio (`printf`)

A diferencia de `print`, `printf` te da control total sobre el diseño y espaciado de la salida.

bash

```
awk '{printf "Empleado: %-10s | Sueldo: $%d\n", $2, $4}' usuarios.txt
```

Los bloques especiales: `BEGIN` y `END`

- **`BEGIN { ... }`**: Se ejecuta **antes** de empezar a leer el archivo (ideal para poner títulos).
- **`END { ... }`**: Se ejecuta **después** de procesar la última línea (ideal para mostrar totales o promedios).

**Ejemplo: Sumar una columna y calcular el promedio**

bash

```
awk '{suma += $4} END {print "Total de nómina:", suma, "| Promedio:", suma/NR}' usuarios.txt
```

