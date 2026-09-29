# 📑 Apuntes: Complemento a 2 (2's Complement)

El **Complemento a 2** es el sistema matemático estándar que utilizan prácticamente todas las computadoras modernas para representar y realizar operaciones aritméticas con **números enteros negativos**.

A diferencia del Complemento a 1, este sistema **elimina el problema del doble cero** y permite que las operaciones de suma y resta se realicen utilizando el mismo circuito lógico en la CPU.

---

## ⚙️ Regla de Oro para Obtenerlo

Para transformar cualquier número positiva su equivalente neo gativo en Complemento a 2, se siguen dos pasos muy sencillos:
1.  **Paso 1:** Obtener el **Complemento a 1** (invertir todos los bits: `0` → `1` y `1` → `0`).
2.  **Paso 2:** **Sumarle un `1`** binario al resultado del Paso 1.

$\[\text{Complemento a 2} = (\text{Invertir Bits}) + 1\]$

---

## 🎯 Ejemplo Práctico: Representar el número `-5` en 8 bits (`int8_t`)

Vamos a convertir el número `+5` a `-5` usando un espacio de 8 bits.

### Paso 1: Escribir el número positivo (+5) en binario
*   `0000 0101`

### Paso 2: Invertir todos los bits (Complemento a 1)
*   `1111 1010`

### Paso 3: Sumar un `1` al resultado anterior
```text
  1111 1010  (Complemento a 1)
+ 0000 0001  (Sumar 1)
-----------
  1111 1011
```

> 💻 **Resultado:** El número `-5` expresado en Complemento a 2 de 8 bits es **`1111 1011`**.

---

## 💡 ¿Por qué es el Rey de la Computación? (Ventajas)

1.  **Soluciona el problema del "Doble Cero":**
    Si tomas el cero positivo `0000 0000`, inviertes sus bits (`1111 1111`) y le sumas `1`, el resultado genera un acarreo (*overflow*) que la CPU descarta, regresando exactamente a `0000 0000`. **¡Solo existe un cero único!**
2.  **Restas fáciles:** 
    Para restar $A - B$, la computadora simplemente transforma $B$ a negativo en Complemento a 2 y realiza una suma: $A + (-B)$. No necesita circuitos separados para restar.

---

## 🧠 Operación en C++

En la memoria de tu computadora, cuando declaras una variable con signo (como `int` o `int8_t`) y le asignas un valor negativo, **C++ ya la guarda automáticamente en Complemento a 2**. 

Si quieres calcularlo manualmente bit a bit usando operadores lógicos, la fórmula matemática exacta en código es `(~número) + 1`:

```cpp
#include <iostream>
#include <cstdint>
#include <bitset>

int main() {
    uint8_t positivo = 5;                        // En binario: 00000101
    uint8_t complemento2 = (~positivo) + 1;       // En binario: 11111011
    
    // Verificamos que el sistema guarda por defecto el -5 de forma idéntica
    int8_t nativoNegativo = -5;
    
    std::cout << "Original (+5):        " << std::bitset<8>(positivo) << "\n";
    std::cout << "Manual Complemento 2: " << std::bitset<8>(complemento2) << "\n";
    std::cout << "Nativo en C++ (-5):   " << std::bitset<8>(nativoNegativo) << "\n";
    
    return 0;
}
```
