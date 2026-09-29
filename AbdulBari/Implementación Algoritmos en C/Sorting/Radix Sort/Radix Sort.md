```cpp
    // Función auxiliar: Un Counting Sort modificado para ordenar según un dígito específico (exp)
void countingSortPorDigito(std::vector<int>& arr, int exp) {
    int n = arr.size();
    std::vector<int> resultado(n);
    int conteo[10] = {0}; // Al ser dígitos del 0 al 9, el tamaño siempre es 10

    // 1. Almacenar el conteo de las ocurrencias de cada dígito
    for (int i = 0; i < n; i++) {
        int digito = (arr[i] / exp) % 10;
        conteo[digito]++;
    }

    // 2. Cambiar conteo[i] para que contenga la posición real de este dígito en el resultado
    for (int i = 1; i < 10; i++) {
        conteo[i] += conteo[i - 1];
    }

    // 3. Construir el vector de resultado recorriendo de atrás hacia adelante para mantener la estabilidad
    for (int i = n - 1; i >= 0; i--) {
        int digito = (arr[i] / exp) % 10;
        resultado[conteo[digito] - 1] = arr[i];
        conteo[digito]--;
    }

    // 4. Copiar los elementos ordenados de vuelta al vector original
    for (int i = 0; i < n; i++) {
        arr[i] = resultado[i];
    }
}

// Función principal de Radix Sort
void radixSort(std::vector<int>& arr) {
    if (arr.empty()) return;

    // 1. Encontrar el número máximo para saber cuántos dígitos tiene
    int maximo = *std::max_element(arr.begin(), arr.end());

    // 2. Hacer Counting Sort para cada dígito. 
    // 'exp' toma valores de 1 (unidades), 10 (decenas), 100 (centenas), etc.
    for (int exp = 1; maximo / exp > 0; exp *= 10) {
        countingSortPorDigito(arr, exp);
    }
}
```

![[Pasted image 20260916112716.png]]
