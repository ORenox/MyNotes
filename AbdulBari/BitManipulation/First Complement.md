
El **Complemento a 1** es un sistema numérico binario que se utiliza principalmente para representar **números negativos**. 

La regla de oro para obtener el complemento a 1 de cualquier número es extremadamente sencilla: **invertir todos los bits** (cambiar los `0` por `1` y los `1` por `0`). Esto equivale a aplicar una operación lógica **NOT** bit a bit.

---

## ⚙️ Regla de Representación
En un espacio de bits fijo (por ejemplo, 8 bits):
*   El bit más a la izquierda (MSB) es el **bit de signo**.
    *   `0` = Número Positivo.
    *   `1` = Número Negativo.

---

## 🎯 Ejemplo Práctico: Representar el número `-5` en 8 bits (`int8_t`)

Para representar el número `-5`, primero debemos conocer su versión positiva y luego aplicar la inversión de bits.

### Paso 1: Escribir el número positivo (+5) en binario de 8 bits
El número 5 en binario puro es `101`. Completando los 8 bits con ceros a la izquierda nos queda:
*   **`+5` en binario:**  `0000 0101`

### Paso 2: Invertir todos los bits (Aplicar Complemento a 1)
Cambiamos cada `0` por un `1` y cada `1` por un `0`:

| Estado | Representación Binaria | Significado |
| :--- | :---: | :--- |
| **Original (+5)** | `0 0 0 0   0 1 0 1` | El primer bit `0` indica positivo. |
| **Invertido (-5)**| `1 1 1 1   1 0 1 0` | El primer bit `1` indica negativo. |

> 💻 **Resultado:** El número `-5` expresado en Complemento a 1 de 8 bits es **`11111010`**.

---

