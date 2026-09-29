#include <iostream>
#include <vector>

// Función para realizar el ordenamiento de burbuja
void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    bool intercambiado;

    // Bucle externo: controla cada pasada sobre el arreglo
    for (int i = 0; i < n - 1; i++) {
        intercambiado = false;

        // Bucle interno: compara elementos adyacentes
        // El "n - i - 1" evita revisar los elementos que ya están ordenados al final
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Intercambio de elementos usando std::swap
                std::swap(arr[j], arr[j + 1]);
                intercambiado = true; // Se registró un cambio
            }
        }

        // Si no hubo intercambios en toda la pasada, el arreglo ya está ordenado
        if (!intercambiado) {
            break;
        }
    }
}

// Función auxiliar para imprimir el arreglo
void imprimirArreglo(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> datos = {64, 34, 25, 12, 22, 11, 90};

    std::cout << "Arreglo original: ";
    imprimirArreglo(datos);

    bubbleSort(datos);

    std::cout << "Arreglo ordenado: ";
    imprimirArreglo(datos);

    return 0;
}
