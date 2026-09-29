#include <iostream>
#include <vector>

// Función recursiva que realiza la búsqueda binaria
// Recibe el vector, los límites de búsqueda actual (low, high) y el objetivo
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

int main() {
    std::vector<int> datos = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int objetivo = 23;

    // La primera llamada empieza desde el índice 0 hasta el último elemento (size - 1)
    int resultado = binarySearchRecursive(datos, 0, datos.size() - 1, objetivo);

    if (resultado != -1) {
        std::cout << "Elemento encontrado en el indice: " << resultado << std::endl;
    } else {
        std::cout << "Elemento no encontrado en el arreglo." << std::endl;
    }

    return 0;
}
