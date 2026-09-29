```cpp
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
    
```

- **Paso 1 (`a = a ^ b`)**: Ahora `a` guarda una mezcla de ambos (`5 ^ 3`).
- **Paso 2 (`b = a ^ b`)**: Sustituimos la nueva `a`. La operación se convierte en `(5 ^ 3) ^ 3`. Como `3 ^ 3 = 0`, nos queda `5 ^ 0 = 5`. **Ahora `b` vale 5** (el valor original de `a`).
- **Paso 3 (`a = a ^ b`)**: La operación se convierte en `(5 ^ 3) ^ 5`. Como `5 ^ 5 = 0`, nos queda `3 ^ 0 = 3`. **Ahora `a` vale 3** (el valor original de `b`).

Nota de advertencia en programación moderna

Aunque este algoritmo de tres líneas con `^` es una pieza de trivia de software muy famosa y elegante, **hoy en día no se recomienda usarlo en producción**

- **Legibilidad:** Es difícil de entender a simple vista para otros programadores.
- **Optimización:** Los compiladores modernos ya optimizan el uso de una variable temporal (como `int temp = a; a = b; b = temp;`) haciendo que sea igual o más rápido que usar XOR, sin arriesgarse a errores.