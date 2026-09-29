Estos algoritmos tienen una complejidad de **\(O(n \log n)\)** o mejor, lo que significa que pueden ordenar millones de datos en cuestión de milisegundos.

|Puesto|Algoritmo|Ventajas|Desventajas / Cuándo no usarlo|
|---|---|---|---|
|**1º**|**Quick Sort**|Es el **más rápido en la práctica** para casi cualquier uso general debido a cómo aprovecha la memoria caché de la computadora.|En su peor caso teórico puede volverse lento (\(O(n^2)\)), aunque en C++ moderno está muy optimizado para evitarlo.|
|**2º**|**Merge Sort**|Es **estable** (mantiene el orden de elementos iguales) y garantiza siempre la misma velocidad máxima (\(O(n \log n)\)) sin importar qué tan desordenado esté el vector.|Requiere **memoria extra** espacio duplicado) para fusionar los subarreglos.|
|**3º**|**Heap Sort**|Es genial porque es **"in-place"** (no usa memoria extra) y te garantiza siempre una velocidad excelente de \(O(n \log n)\) en el peor escenario.|En la práctica es un poco más lento que _Quick Sort_ debido a la forma en que salta en la memoria al buscar los nodos del árbol.|

---

🚀 Los Especialistas (Ultra rápidos, pero con condiciones)

Estos algoritmos no usan comparaciones. Pueden llegar a ser **más rápidos que los tres anteriores (velocidad lineal \(O(n)\))**, pero **solo funcionan bajo restricciones estrictas** (como trabajar exclusivamente con números enteros dentro de un rango controlado).

|Puesto|Algoritmo|Cuándo es el mejor|Restricción / Desventaja|
|---|---|---|---|
|**4º**|**Counting Sort**|El mejor si tienes millones de números pero el **valor máximo es pequeño** (por ejemplo, ordenar las edades de un país).|Si tienes un número muy grande (como el ID de un usuario), consumirá gigabytes de memoria innecesaria.|
|**5º**|**Radix Sort**|Excelente para ordenar números enteros largos, códigos numéricos o cadenas de texto de longitud fija dígito por dígito.|Depende completamente de otro algoritmo estable de soporte (como _Counting Sort_) y no sirve para datos decimales complejos de forma nativa.|

---

🐢 Los Lentos (Solo para propósitos educativos o listas muy pequeñas)

Tienen una complejidad de **\(O(n^2)\)**. Si intentas ordenar un millón de datos con ellos, tu programa podría quedarse congelado por minutos u horas.

| Puesto | Algoritmo          | Diagnóstico                                                                                                                                                                  | Único caso de uso útil                                                            |
| ------ | ------------------ | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------- |
| **6º** | **Insertion Sort** | Aunque es lento para listas grandes, es **extremadamente eficiente si la lista ya está casi ordenada** o si agregas elementos nuevos uno a uno a una lista que ya ordenaste. | Es pésimo si los datos están totalmente aleatorios o en orden inverso.            |
| **7º** | **Selection Sort** | Es ineficiente porque siempre revisa todo el arreglo buscando el mínimo, sin importar si ya estaba ordenado.                                                                 | Su única ventaja es que hace el número mínimo de intercambios en memoria físicos. |
| **8º** | **Bubble Sort**    | Es considerado **el algoritmo más ineficiente** de los clásicos. Realiza demasiadas operaciones de intercambio redundantes.                                                  | Solo sirve para aprender a programar en tus primeras clases de lógica.            |
