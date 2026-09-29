```cpp
// Función que realiza el ordenamiento por inserción
// Recibe el vector por referencia con '&' para modificarlo directamente sin hacer copias
void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    
    // El ciclo empieza en 1 porque el primer elemento (índice 0) ya se considera "ordenado"
    for (int i = 1; i < n; i++) {
        int key = arr[i]; // El elemento actual que vamos a insertar en su lugar correcto
        int j = i - 1;

        // Mueve los elementos de arr[0..i-1] que son mayores que 'key'
        // una posición hacia adelante de su posición actual
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        
        // Coloca la 'key' en su posición correcta encontrada
        arr[j + 1] = key;
    }
}
```