#include <iostream>
#include <vector>

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

// Función auxiliar para imprimir el vector
void imprimirVector(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << "\n";
}

int main() {
    std::vector<int> arr = {12, 11, 13, 5, 6, 7};
    
    std::cout << "Vector original: ";
    imprimirVector(arr);

    heapSort(arr);

    std::cout << "Vector ordenado: ";
    imprimirVector(arr);
    
    return 0;
}
