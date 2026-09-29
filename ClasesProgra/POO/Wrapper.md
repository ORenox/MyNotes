Aquí está una de las partes más importantes.

Java tiene una **clase equivalente para cada tipo primitivo**.

| Primitivo | Wrapper     |
| --------- | ----------- |
| `byte`    | `Byte`      |
| `short`   | `Short`     |
| `int`     | `Integer`   |
| `long`    | `Long`      |
| `float`   | `Float`     |
| `double`  | `Double`    |
| `char`    | `Character` |
| `boolean` | `Boolean`   |
Por ejemplo:

```
int x = 10;
```

es un primitivo.

Mientras que:

```
Integer x = 10;
```

es un objeto de la clase `Integer`.

Y:

```
Object
   ↑
Number
   ↑
Integer
```

Por eso:
```
Integer x = 10;
```

sí puede considerarse un objeto.

# ¿Por qué existen los Wrapper?

Principalmente porque **hay situaciones en Java donde necesitas un objeto y no puedes utilizar directamente un primitivo**.

Un ejemplo muy importante son las colecciones.

Puedes hacer:

```java
List<Integer> numeros = new ArrayList<>();
```

pero no:

```java
List<int> numeros; // ❌
```

Las colecciones trabajan con tipos de referencia.

Por eso usamos:

```java
List<Integer>
```

en lugar de:

```java
List<int>
```

# Autoboxing

Ahora viene algo que hace que todo parezca más extraño.

Puedes hacer:

```java
Integer numero = 10;
```

Aunque `10` es un `int`.

Java automáticamente convierte:

```
int
 ↓
Integer
```

Esto se llama **autoboxing**.

Es como si Java hiciera:

```java
Integer numero = Integer.valueOf(10);
```

# Unboxing

También ocurre al revés.

```java
Integer numero = 10;

int x = numero;
```

Java convierte automáticamente:

```java
Integer
   ↓
  int
```

Esto se llama **unboxing**.

Conceptualmente:

```java
int x = numero.intValue();
```

# Entonces mira esta comparación

```java
int a = 10;
Integer b = 10;
```

Aunque parecen casi iguales:

```
a
│
└── 10
```

mientras:

```
b
│
▼
┌─────────────┐
│  Integer    │
│  value: 10  │
└─────────────┘
```

`a` es un valor primitivo.

`b` es una referencia a un objeto `Integer`.

# ¿Y `String`?

`String` no es un primitivo.

```java
String nombre = "Renato";
```

`String` es una **clase**.

Por lo tanto:

```java
Object
   ↑
 String
```

Puedes hacer:

```java
Object x = "Hola";
```

porque un `String` es un objeto.

Pero no:

```java
Object x = 10;
```

Bueno... **sí puedes** 😅

Y aquí aparece el autoboxing:

```java
Object x = 10;
```

Java transforma el `int` en `Integer`:

```java
10 (int)
   ↓ autoboxing
10 (Integer)
   ↓
Object
```

Conceptualmente:

```java
Object x = Integer.valueOf(10);
```

# La diferencia más importante

Cuando veas:

```
int edad = 25;
```

piensa:

> **Tengo un valor primitivo.**

Cuando veas:

```
Integer edad = 25;
```

piensa:

> **Tengo una referencia a un objeto `Integer`.**

Cuando veas:

```
Persona p = new Persona();
```

piensa:

> **Tengo una referencia a un objeto `Persona`.**

Cuando veas:

```
String nombre = "Renato";
```

piensa:

> **Tengo una referencia a un objeto `String`.**


----

una diferencia fundamental:

```
int x = null;       // ❌
Integer y = null;   // ✅
```

¿Por qué?

Porque `null` significa **"no hay objeto/referencia"**, y un `int` no es un objeto.

```
int
 │
 └── 10

Integer
 │
 ├── referencia → objeto
 │
 └── puede ser null
```

Esta distinción entre **valor primitivo** y **referencia a objeto** es una de las bases para entender bien Java.