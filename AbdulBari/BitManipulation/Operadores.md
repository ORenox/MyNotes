![[Pasted image 20260921233342.png]]


Operadores a Nivel de Bits (Bitwise Operators)

Los operadores de bits nos permiten modificar, encender, apagar o consultar bits individuales dentro de las variables. Trabajan directamente sobre la representación binaria en memoria, lo que los hace extremadamente rápidos.

---

## 🏎️ Los 6 Operadores Clásicos

A continuación se muestra el comportamiento de cada uno usando variables de 8 bits (`uint8_t`). Supongamos que:
*   `A = 5`  👉 `0000 0101`
*   `B = 6`  👉 `0000 0110`

### 1. AND Binario (`&`)
*   **Regla:** Da `1` únicamente si **ambos** bits comparados son `1`.
*   **Caso de uso:** Se usa como **máscara** para saber si un bit específico está encendido o para apagar bits.
*   **Ejemplo (`A & B`):**
    ```text
      0000 0101  (A)
    & 0000 0110  (B)
    -----------
      0000 0100  (Resultado = 4)
    ```

### 2. OR Binario (`|`)
*   **Regla:** Da `1` si **al menos uno** de los bits comparados es `1`.
*   **Caso de uso:** Se usa para **encender** bits específicos sin alterar los demás.
*   **Ejemplo (`A | B`):**
    ```text
      0000 0101  (A)
    | 0000 0110  (B)
    -----------
      0000 0111  (Resultado = 7)
    ```

### 3. XOR Binario (`^`) - OR Exclusivo
*   **Regla:** Da `1` si los bits comparados son **diferentes** (`0` y `1`). Da `0` si son iguales.
*   **Caso de uso:** Se usa para **alternar o invertir** (*toggle*) el estado de un bit o para encriptación simple.
*   **Ejemplo (`A ^ B`):**
    ```text
      0000 0101  (A)
    ^ 0000 0110  (B)
    -----------
      0000 0011  (Resultado = 3)
    ```

### 4. NOT Binario (`~`)
*   **Regla:** Invierte todos los bits de una variable (el Complemento a 1). Los `0` se vuelven `1` y viceversa.
*   **Ejemplo (`~A`):**
    ```text
    ~ 0000 0101  (A)
    -----------
      1111 1010  (Resultado = 250)
    ```

### 5. Desplazamiento Izquierda (`<<` - Left Shift)
*   **Regla:** Mueve todos los bits hacia la izquierda el número de posiciones indicado. Llena los espacios vacíos con `0`.
*   **Caso de uso matemático:** Multiplica el número por \(2^n\).
*   **Ejemplo (`A << 2`):**
    ```text
    0000 0101  (A antes: 5)
    0001 0100  (A después: 20 -> Equivale a 5 * 2²)
    ```

### 6. Desplazamiento Derecha (`>>` - Right Shift)
*   **Regla:** Mueve todos los bits hacia la derecha el número de posiciones indicado.
*   **Caso de uso matemático:** Divide el número entero entre \(2^n\) (truncando decimales).
*   **Ejemplo (`A >> 1`):**
    ```text
    0000 0101  (A antes: 5)
    0000 0010  (A después: 2 -> Equivale a 5 / 2¹)
    ```

---

### A. Asignaciones Compuestas (`&=`, `|=`, `^=`, `<<=`, `>>=`)
Igual que el operador `+=`, modifican directamente el valor de la variable original.
*   `opciones |= mascara;` es equivalente a `opciones = opciones | mascara;`

### B. Nuevas funciones nativas de C++20 (Librería `<bit>`)
Estas funciones se ejecutan directo en el hardware de la CPU a máxima velocidad:

1.  **`std::popcount(x)`**: Cuenta cuántos bits `1` hay encendidos en un número.
2.  **`std::has_single_bit(x)`**: Verifica si un número es potencia exacta de 2 (es decir, si tiene un solo bit encendido).
3.  **`std::bit_ceil(x)` / `std::bit_floor(x)`**: Encuentran la potencia de 2 más cercana hacia arriba o hacia abajo.
4.  **`std::countl_zero(x)` / `std::countr_zero(x)`**: Cuenta cuántos ceros seguidos hay a la izquierda (inicio) o a la derecha (final) del número.

---

## 🧠 Código Demostrativo Completo

```cpp
#include <iostream>
#include <cstdint>
#include <bitset>
#include <bit> // Requerido para C++20 (popcount, etc.)

int main() {
    uint8_t a = 5; // 00000101
    uint8_t b = 6; // 00000110

    std::cout << "AND (&):   " << std::bitset<8>(a & b) << "\n";
    std::cout << "OR (|):    " << std::bitset<8>(a | b) << "\n";
    std::cout << "XOR (^):   " << std::bitset<8>(a ^ b) << "\n";
    std::cout << "NOT (~):   " << std::bitset<8>(~a) << "\n";
    std::cout << "Shift L:   " << std::bitset<8>(a << 2) << "\n";
    
    // C++20 - Conteo de bits encendidos
    std::cout << "Bits encendidos en A: " << std::popcount(a) << "\n"; // Retorna 2

    return 0;
}
```
