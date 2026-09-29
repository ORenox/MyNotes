```cpp
int binarySearch(const std::vector<int>& arr, int target) {
	//inicializamos los punteros en 0 y en el final de la cadena
    int low = 0;
    int high = arr.size() - 1;

    // El ciclo continúa mientras el espacio de búsqueda sea válido
    while (low <= high) {
        // Se calcula el punto medio de esta manera para evitar el desbordamiento de enteros (overflow)
       
        int mid = low + (high - low) / 2;

        // Caso 1: El elemento objetivo está justo en el medio
        if (arr[mid] == target) {
            return mid; 
        }
        
        // Caso 2: El elemento del medio es menor que el objetivo,
        // por lo tanto, el objetivo está en la mitad derecha
        if (arr[mid] < target) {
            low = mid + 1;
        } 
        // Caso 3: El elemento del medio es mayor que el objetivo,
        // por lo tanto, el objetivo está en la mitad izquierda
        else {
            high = mid - 1;
        }
    }

    // Si salimos del ciclo, significa que el elemento no está en el arreglo
    return -1;
}

```

 El **desbordamiento de enteros** (u _integer overflow_ en inglés) ocurre cuando el resultado de una operación matemática da un número **más grande que el valor máximo** que la variable puede almacenar en la memoria de la computadora.
 
Imagina que una variable entera de tipo `int` en C++ se almacena usando **32 bits**. Esto significa que tiene un límite estricto de números que puede guardar:

- **Valor Máximo:** `2,147,483,647`
- **Valor Mínimo:** `-2,147,483,648`

Si intentas sumarle `1` al valor máximo, la computadora no tiene más espacio físico en sus bits para representar el siguiente número correcto (`2,147,483,648`). En su lugar, el bit de signo cambia y el valor **se desborda hacia el número más negativo posible**.

text

```
  2,147,483,647  (Límite máximo)
+             1  
-----------------
 -2,147,483,648  (¡Resultado incorrecto por desbordamiento!)
```

En el algoritmo de Búsqueda Binaria, necesitas calcular la posición del medio entre dos índices: `low` (el inicio) y `high` (el final).

- **La forma intuitiva pero peligrosa:** `int mid = (low + high) / 2;`
- **¿Qué pasa si el arreglo es gigante?** Si tu arreglo tiene miles de millones de elementos (por ejemplo, en bases de datos o Big Data), los índices `low` y `high` pueden ser números muy grandes. Si `low = 1,500,000,000` y `high = 1,500,000,000`, al sumarlos da `3,000,000,000`. Como ese número supera los `2,147,483,647`, la suma **se desborda y se vuelve negativa**, haciendo que tu programa intente buscar en un índice negativo y colapse de inmediato (_runtime error_).

- **La solución segura:** `int mid = low + (high - low) / 2;`  
    Al restar `high - low`, obtienes la distancia entre ambos puntos (que siempre será un número pequeño y seguro). Luego divides esa distancia entre 2 y se la sumas a `low`. Así, **nunca superas el límite de almacenamiento**.
