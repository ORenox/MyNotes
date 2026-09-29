```cpp
    // Función para reestructurar el montículo (Heapify)
void heapify(std::vector<int>& arr, int n, int i) {
    int maximo = i;          // Inicializar el más grande como la raíz
    int izquierdo = 2 * i + 1; // Hijo izquierdo
    int derecho = 2 * i + 2;   // Hijo derecho

    // Si el hijo izquierdo es más grande que la raíz
    if (izquierdo < n && arr[izquierdo] > arr[maximo]) {
        maximo = izquierdo;
    }

    // Si el hijo derecho es más grande que el máximo actual
    if (derecho < n && arr[derecho] > arr[maximo]) {
        maximo = derecho;
    }

    // Si el máximo no es la raíz, se intercambian y se continúa aplicando heapify
    if (maximo != i) {
        std::swap(arr[i], arr[maximo]);
        
        // Afecta recursivamente al subárbol afectado
        heapify(arr, n, maximo);
    }
}

// Función principal de Heap Sort
void heapSort(std::vector<int>& arr) {
    int n = arr.size();

    // 1. Construir el Max-Heap (reorganizar el vector)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // 2. Extraer elementos uno a uno del montículo
    for (int i = n - 1; i > 0; i--) {
        // Mover la raíz actual (el más grande) al final del vector
        std::swap(arr[0], arr[i]);

        // Llamar a heapify en el montículo reducido
        heapify(arr, i, 0);
    }
}
```

### ¿Qué significa `int i = n / 2 - 1`?

Esta línea sirve para **encontrar el último nodo del árbol que tiene al menos un hijo** (también llamado el último nodo "padre").

En ciencias de la computación, un montículo se dibuja como un árbol, pero en memoria se guarda en un vector plano. Gracias a las matemáticas de los árboles binarios, si un vector tiene `n` elementos:

1. Las **hojas** (los nodos de hasta abajo que no tienen hijos) ocupan la segunda mitad del vector.
2. Los **padres** (los nodos que sí tienen hijos) ocupan la primera mitad.

El último nodo que no es una hoja se encuentra exactamente en la posición `(n / 2) - 1`.

🌲 Ejemplo visual con 6 elementos (`n = 6`)

Imagina que tenemos el vector `[12, 11, 13, 5, 6, 7]`. En forma de árbol se ve así:

text

```
       Índice 0: (12)           <-- Raíz (Padre de 11 y 13)
        /          \
  Índice 1: (11)   Índice 2: (13) <-- ¡Último nodo con hijos! (Padre de 7)
    /       \        /
Índice 3:(5) Índ.4:(6) Índ.5:(7)  <-- Hojas (No tienen hijos)
```

Usa el código con precaución.

Si calculamos `n / 2 - 1` con `n = 6`:  
$\(\text{Resultado}=(6/2)-1=3-1=\mathbf{2}\)$

El **índice 2** (que contiene al número `13`) es el **último nodo padre del árbol**. Los nodos en los índices 3, 4 y 5 son hojas sueltas.

¿Por qué el bucle `for` empieza ahí y va hacia atrás?

No tiene sentido aplicar `heapify` en las hojas (índices 3, 4 y 5) porque no tienen hijos con quienes compararse. Sería un desperdicio de tiempo.

Por eso, el algoritmo optimiza el proceso:

1. Empieza en el último padre (**índice 2**).
2. Avanza hacia atrás al siguiente padre (**índice 1**).
3. Termina en la raíz (**índice 0**).

Al recorrer los nodos de abajo hacia arriba construyendo el montículo, garantizas que cuando llegues a la raíz, todo el árbol cumpla perfectamente la propiedad de un Max-Heap.



1. La función `heapify` (Amontonar)

Es el motor del algoritmo. Se asegura de que un subárbol cumpla con la propiedad de **Max-Heap**: que el nodo padre sea siempre **mayor** que sus hijos.

- Recibe el tamaño del arreglo `n` y el índice del nodo actual `i`.
- Calcula las posiciones de sus hijos (`2*i + 1` y `2*i + 2`).
- Compara el padre con ambos hijos para encontrar el mayor de los tres.
- Si el padre no es el mayor, los intercambia. Como este cambio puede desordenar los niveles inferiores, la función se llama a sí misma recursivamente en el subárbol afectado.


### Paso 1 en `heapSort`: Construcción del Max-Heap

- El arreglo original está desordenado. El algoritmo empieza desde el último nodo que tiene hijos (`n / 2 - 1`) y va retrocediendo hasta la raíz (índice `0`).
- Llama a `heapify` para cada nodo. Al terminar este ciclo, **el número más grande de todos queda en la posición inicial (`arr[0]`)**.

![[Pasted image 20260916111031.png]]![[Pasted image 20260916111104.png]]
![[Pasted image 20260916111150.png]]