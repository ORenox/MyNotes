Para evitar esto, en C++ se utiliza la librería `<cstdint>`, la cual define tipos de datos con el **número exacto de bits garantizado**:

- **`int8_t`** / **`uint8_t`** : Exactamente **8 bits** (con y sin signo).
- **`int16_t`** / **`uint16_t`** : Exactamente **16 bits**.
- **`int32_t`** / **`uint32_t`** : Exactamente **32 bits**.
- **`int64_t`** / **`uint64_t`** : Exactamente **64 bits**.

> 💡 **Regla de oro:** Cuando hagas máscaras de bits, encendidos (`|`), apagados (`&`) o desplazamientos (`<<`, `>>`), acostúmbrate a usar siempre los tipos con **`u`** al principio (como `uint32_t`). Los tipos **sin signo** evitan problemas extraños con el bit de signo (el bit más a la izquierda que define si el número es negativo).

Cuando estamos hablando de manipular bits, una consideración importante es su complemento:
### Complemento a 1 (1' Complement)
[[First Complement]]
### Complemento a 2 (2' Complement)
[[Second Complement]]

### Operadores

los operadores principales son AND, OR, XOR, SHIFT y NOT
[[Operadores]]
	