#include <iostream>
#include <vector>

// Función auxiliar para mezclar dos mitades ordenadas de un vector
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1; // Tamaño de la sublista izquierda
    int n2 = right - mid;    // Tamaño de la sublista derecha

    // Crear vectores temporales para almacenar las mitades
    std::vector<int> L(n1);
    std::vector<int> R(n2);

    // Copiar los datos a los vectores temporales L[] y R[]
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    // Índices iniciales para recorrer las sublistas y la lista principal
    int i = 0;    // Índice inicial de la primera mitad L
    int j = 0;    // Índice inicial de la segunda mitad R
    int k = left; // Índice inicial del vector mezclado principal

    // Mezclar los vectores temporales de regreso en arr[left..right] en orden
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copiar los elementos restantes de L[], si quedan algunos
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copiar los elementos restantes de R[], si quedan algunos
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Función principal de Merge Sort (Recursiva)
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        // Encuentra el punto medio de forma segura para evitar desbordamiento de enteros
        int mid = left + (right - left) / 2;

        // Ordena la primera y la segunda mitad recursivamente
        mergeSort(arr, left, mid);      // Mitad izquierda
        mergeSort(arr, mid + 1, right); // Mitad derecha

        // Mezcla las dos mitades ya ordenadas
        merge(arr, left, mid, right);
    }
}

int main() {
    std::vector<int> datos = {38, 27, 43, 3, 9, 82, 10};

    std::cout << "Arreglo original: ";
    for (int x : datos) std::cout << x << " ";
    std::cout << std::endl;

    // Llamada inicial desde el índice 0 hasta el último (size - 1)
    mergeSort(datos, 0, datos.size() - 1);

    std::cout << "Arreglo ordenado: ";
    for (int x : datos) std::cout << x << " ";
    std::cout << std::endl;

    return 0;
}
