#include <iostream>
#include <vector>
//El prefijo std:: representa el Standard Namespace (espacio de nombres estándar) en C++. 
// Debes usarlo para indicarle al compilador que los comandos, objetos o funciones que estás llamando 
// pertenecen a la biblioteca estándar de C++.
// Función que realiza la búsqueda binaria iterativa
// Recibe un vector ordenado por referencia constante y el elemento a buscar
int binarySearch(const std::vector<int>& arr, int target) {
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

int main() {
    // El arreglo DEBE estar ordenado para que la búsqueda binaria funcione
    std::vector<int> datos = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int objetivo = 2;

    int resultado = binarySearch(datos, objetivo);

    if (resultado != -1) {
        std::cout << "Elemento encontrado en el indice: " << resultado << std::endl;
    } else {
        std::cout << "Elemento no encontrado en el arreglo." << std::endl;
    }

    return 0;
}