#include <iostream>
#include <vector>
#include <algorithm>

void countingSort(std::vector<int>& arr) {
    if (arr.empty()) return;

    int n = arr.size();

    // 1. Encontrar el valor máximo en el vector para definir el tamaño del arreglo de conteo
    int maximo = *std::max_element(arr.begin(), arr.end());

    // 2. Crear el vector de conteo e inicializarlo en 0. Su tamaño debe ser (maximo + 1)
    std::vector<int> conteo(maximo + 1, 0);
    std::vector<int> resultado(n);

    // 3. Registrar la frecuencia/ocurrencia de cada número
    for (int i = 0; i < n; i++) {
        conteo[arr[i]]++;
    }

    // 4. Modificar 'conteo' para que almacene las posiciones acumuladas
    // Cada posición ahora te dice cuántos elementos son menores o iguales a ese índice
    for (int i = 1; i <= maximo; i++) {
        conteo[i] += conteo[i - 1];
    }

    // 5. Construir el vector de resultado recorriendo de atrás hacia adelante
    // Esto asegura que el algoritmo sea ESTABLE (mantiene el orden original de elementos iguales)
    for (int i = n - 1; i >= 0; i--) {
        int elementoActual = arr[i];
        int posicionCorrecta = conteo[elementoActual] - 1;
        resultado[posicionCorrecta] = elementoActual;
        conteo[elementoActual]--; // Reducir el conteo para el próximo elemento idéntico
    }

    // 6. Copiar los elementos ordenados de vuelta al vector original
    for (int i = 0; i < n; i++) {
        arr[i] = resultado[i];
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
    std::vector<int> arr = {4, 2, 2, 8, 3, 3, 1};
    
    std::cout << "Vector original: ";
    imprimirVector(arr);

    countingSort(arr);

    std::cout << "Vector ordenado: ";
    imprimirVector(arr);
    
    return 0;
}
