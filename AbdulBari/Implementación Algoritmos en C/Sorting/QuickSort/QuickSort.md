```cpp

// Función auxiliar para intercambiar dos elementos
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Función de partición: acomoda los elementos alrededor del pivote
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // Elegimos el último elemento como pivote
    int i = low - 1;       // Índice del elemento más pequeño

    for (int j = low; j < high; j++) {
        // Si el elemento actual es menor o igual al pivote
        if (arr[j] <= pivot) {
            i++; // Incrementamos el índice del elemento más pequeño
            swap(arr[i], arr[j]);
        }
    }
    // Colocamos el pivote en su posición correcta central
    swap(arr[i + 1], arr[high]);
    return i + 1; // Retorna la posición del pivote
}

// Función principal de Quicksort (Recursiva)
void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        // pi es el índice de partición (el pivote ya está en su lugar correcto)
        int pi = partition(arr, low, high);

        // Ordenamos recursivamente los elementos antes y después de la partición
        quickSort(arr, low, pi - 1);  // Mitad izquierda
        quickSort(arr, pi + 1, high); // Mitad derecha
    }
}
```