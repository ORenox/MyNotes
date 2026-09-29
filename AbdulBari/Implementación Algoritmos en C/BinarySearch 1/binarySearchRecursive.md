```cpp
int binarySearchRecursive(const std::vector<int>& arr, int low, int high, int target) {
    // Caso Base 1: El espacio de búsqueda es inválido (el elemento no existe)
    if (low > high) {
        return -1;
    }

    // Cálculo del punto medio de manera segura (evitando desbordamiento)
    int mid = low + (high - low) / 2;

    // Caso Base 2: El elemento objetivo está en el medio
    if (arr[mid] == target) {
        return mid;
    }

    // Paso Recursivo 1: El del medio es menor, buscar en la mitad DERECHA
    if (arr[mid] < target) {
        return binarySearchRecursive(arr, mid + 1, high, target);
    }
    
    // Paso Recursivo 2: El del medio es mayor, buscar en la mitad IZQUIERDA
    else {
        return binarySearchRecursive(arr, low, mid - 1, target);
    }
}

```

El símbolo **`&`** en C++ se conoce como el operador de **referencia** (o dirección)

#### Pasar parámetros por referencia (Evitar copias en memoria)

Esta es la función más importante y es justo la que usamos en las funciones de Búsqueda Binaria que te mostré (`const std::vector<int>& arr`).

- **Sin `&` (Por copia):** Si pasas un vector gigante con 1 millón de datos a una función sin el `&`, C++ va a duplicar ese millón de datos en la memoria para que la función trabaje con una copia. Esto hace que tu programa sea extremadamente **lento e ineficiente**.
- **Con `&` (Por referencia):** En lugar de duplicar los datos, el `&` le dice a la función: _"No hagas una copia, trabaja directamente sobre el arreglo original usando su dirección"_.
- **El uso de `const`:** Poner `const` antes (`const std::vector<int>&`) es una medida de seguridad. Le dice a la función que puede leer los datos directamente para ahorrar memoria, pero tiene prohibido modificarlos.

---

#### Obtener la dirección de memoria de una variable

Si pones el `&` a la izquierda de una variable ya creada, sirve para averiguar en qué celda física de la memoria RAM de tu computadora está guardada esa información.

```cpp
int numero = 42;
// Imprime la dirección en formato hexadecimal (por ejemplo: 0x7ffd35b2a)
std::cout << &numero << std::endl; 
```

