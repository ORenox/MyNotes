![[Pasted image 20260825184754.png]]

![[Pasted image 20260825184807.png]]

[[Pilares de POO]]
### Lenguajes con soporte para POO

| Lenguaje        | POO | Características                                  |
| --------------- | --- | ------------------------------------------------ |
| **Java**        | ✅   | Clases, herencia, interfaces, polimorfismo       |
| **C++**         | ✅   | Clases, herencia múltiple, polimorfismo          |
| **C#**          | ✅   | Clases, interfaces, herencia, polimorfismo       |
| **Python**      | ✅   | Clases, herencia múltiple, duck typing           |
| **Kotlin**      | ✅   | Clases, interfaces, herencia                     |
| **Swift**       | ✅   | Clases, structs, protocolos                      |
| **Ruby**        | ✅   | Todo gira alrededor de objetos                   |
| **PHP**         | ✅   | Clases, interfaces, traits                       |
| **TypeScript**  | ✅   | Clases, interfaces, herencia                     |
| **JavaScript**  | ✅   | Prototipos y `class`                             |
| **Dart**        | ✅   | Clases, interfaces implícitas, mixins            |
| **Scala**       | ✅   | POO + funcional                                  |
| **Objective-C** | ✅   | POO basada en Smalltalk                          |
| **Rust**        | ⚠️  | No POO clásica; structs + traits                 |
| **Go**          | ⚠️  | No clases/herencia clásica; structs + interfaces |
| **C**           | ❌*  | No tiene POO nativa                              |


## ¿Qué significa realmente "soportar POO"?

Normalmente hablamos de conceptos como:

### 1. Clases

```java
class Persona {
    String nombre;
}
```

### 2. Objetos

```java
Persona p = new Persona();
p.nombre = "Renato";
```

### 3. Encapsulamiento

```java
class Persona {
    private String nombre;

    public String getNombre() {
        return nombre;
    }
}
```

### 4. Herencia

```java
class Animal {
}

class Perro extends Animal {
}
```

### 5. Polimorfismo

```java
Animal animal = new Perro();
```

Estos conceptos aparecen de diferentes maneras dependiendo del lenguaje.


## Algo importante: POO ≠ lenguaje orientado exclusivamente a objetos

Por ejemplo, **Python** permite:

```
def suma(a, b):
    return a + b
```

Eso es programación procedural/imperativa.

Pero también puedes hacer:

```
class Persona:
    def __init__(self, nombre):
        self.nombre = nombre
```

Eso es POO.

Y puedes combinarlo con programación funcional:

```
numeros = [1, 2, 3, 4]

resultado = list(map(lambda x: x * 2, numeros))
```

Por eso es mejor pensar:

```
              Lenguajes
                  │
       ┌──────────┼──────────┐
       ↓          ↓          ↓
   Imperativo     POO    Funcional
       │          │          │
       └──────────┼──────────┘
                  ↓
             Python
             Java
             C++
             Kotlin
             ...
```

Muchos lenguajes modernos son **multiparadigma**.


### Curiosamente, JavaScript también es POO

Aunque funciona de manera diferente a Java:

```
class Persona {
    constructor(nombre) {
        this.nombre = nombre;
    }
}

const persona = new Persona("Renato");
```

JavaScript utiliza fundamentalmente un modelo de **objetos basado en prototipos**, aunque `class` proporciona una sintaxis de estilo clásico.


Eso se llama **sobrecarga de constructores** (_constructor overloading_).

Es un caso particular de **sobrecarga de métodos** (_method overloading_).

Por ejemplo, en Java:

```java
class Persona {

    String nombre;
    int edad;

    // Constructor 1
    Persona() {
        nombre = "Desconocido";
        edad = 0;
    }

    // Constructor 2
    Persona(String nombre) {
        this.nombre = nombre;
        edad = 0;
    }

    // Constructor 3
    Persona(String nombre, int edad) {
        this.nombre = nombre;
        this.edad = edad;
    }
}
```

Puedes crear objetos de diferentes maneras:

```
Persona p1 = new Persona();

Persona p2 = new Persona("Renato");

Persona p3 = new Persona("Renato", 25);
```

Java sabe cuál constructor utilizar según **la cantidad y tipos de argumentos**.