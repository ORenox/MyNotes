#include <iostream>
#include <vector>

// Función para realizar el ordenamiento por selección
void selectionSort(std::vector<int>& arr) {
    int n = arr.size();

    // Bucle externo: mueve el límite de la sublista no ordenada uno por uno
    for (int i = 0; i < n - 1; i++) {
        // Suponemos que el primer elemento no ordenado es el mínimo
        int indiceMinimo = i;

        // Bucle interno: busca el elemento más pequeño en el resto del arreglo
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[indiceMinimo]) {
                indiceMinimo = j; // Actualiza el índice del nuevo mínimo encontrado
            }
        }

        // Si el mínimo encontrado no es el elemento inicial, se intercambian
        if (indiceMinimo != i) {
            std::swap(arr[i], arr[indiceMinimo]);
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
    std::vector<int> datos = {64, 25, 12, 22, 11};

    std::cout << "Arreglo original: ";
    imprimirArreglo(datos);

    selectionSort(datos);

    std::cout << "Arreglo ordenado: ";
    imprimirArreglo(datos);

    return 0;
}
