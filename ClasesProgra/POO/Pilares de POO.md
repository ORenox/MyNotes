![[Pasted image 20260825220528.png]]

# Abstracción
La mayoría de las veces, cuando creas un programa con POO, das forma a los objetos del programa con base a objetos del mundo real. Sin embargo, los objetos del programa no representan a los originales con una precisión del 100 % (y rara vez es necesario que lo hagan). En su lugar, tus objetos tan solo copian atributos y comportamientos de objetos reales en un contexto específico, ignorando el resto.

>La **abstracción** consiste en quedarnos con las características importantes de un objeto para el contexto de nuestro programa y **ignorar detalles que no necesitamos**.

Por ejemplo, si hacemos un programa para una veterinaria:

```
Animal
├── nombre
├── edad
└── emitirSonido()
```

No necesitamos representar absolutamente todo sobre un animal.

**En java**

```java
abstract class Animal {

    protected String nombre;
    protected int edad;

    public Animal(String nombre, int edad) {
        this.nombre = nombre;
        this.edad = edad;
    }

    public abstract void emitirSonido();
}
```

**En C++**

En C++ puedes hacer algo equivalente:

```C++
class Animal {

protected:
    std::string nombre;
    int edad;

public:
    Animal(std::string nombre, int edad)
        : nombre(nombre), edad(edad) {}

    virtual void emitirSonido() = 0;
};
```

---

# Encapsulación
Para arrancar el motor de un auto, tan solo debes girar una llave o pulsar un botón. No necesitas conectar cables bajo el capó, rotar el cigüeñal y los cilindros, e iniciar el ciclo de potencia del motor. Estos detalles se esconden bajo el capó del auto. Sólo tienes una interfaz simple: un interruptor de encendido, un volante y unos pedales. Esto ilustra el modo en que cada objeto cuenta con una interfaz: una parte pública de un objeto, abierta a interacciones con otros objetos.
La encapsulación es la capacidad que tiene un objeto de esconder partes de su estado y comportamiento de otros objetos, exponiendo únicamente una interfaz limitada al resto del
programa.
>Encapsular algo significa hacerlo privado y, por ello, accesible únicamente desde dentro de los métodos de su propia clase. Existe un modelo un poco menos restrictivo llamado protegido que hace que un miembro de una clase también esté disponible para las subclases.

>La **encapsulación** consiste en ocultar el estado interno del objeto y controlar cómo otros objetos pueden acceder a él.

imagina una cuenta bancaria.

No queremos permitir:

```
cuenta.saldo = -1000000
```

desde cualquier parte del programa.

Queremos controlar cómo se modifica.

### Java

```java
class Cuenta {

    private double saldo;

    public Cuenta(double saldoInicial) {
        saldo = saldoInicial;
    }

    public void depositar(double cantidad) {
        if (cantidad > 0) {
            saldo += cantidad;
        }
    }

    public double getSaldo() {
        return saldo;
    }
}
```

Ahora:

```java
Cuenta cuenta = new Cuenta(100);

cuenta.depositar(50);

System.out.println(cuenta.getSaldo());
```

Pero esto:

```java
cuenta.saldo = -500;
```

no funciona porque:

```java
private double saldo;
```

hace que `saldo` solamente pueda ser accedido directamente desde dentro de `Cuenta`.

**C++**
```C++
class Cuenta {

private:
    double saldo;

public:
    Cuenta(double saldoInicial) {
        saldo = saldoInicial;
    }

    void depositar(double cantidad) {
        if (cantidad > 0) {
            saldo += cantidad;
        }
    }

    double getSaldo() {
        return saldo;
    }
};
```

Uso:

```C++
Cuenta cuenta(100);

cuenta.depositar(50);

std::cout << cuenta.getSaldo();
```

Esto no está permitido:

```c++
cuenta.saldo = -500;
```

porque `saldo` es `private`.

---

# Herencia

La herencia es la capacidad de crear nuevas clases sobre otras existentes. La principal ventaja de la herencia es la reutilización de código. Si quieres crear una clase ligeramente diferente a una ya existente, no hay necesidad de duplicar el código.
En su lugar, extiendes la clase existente y colocas la funcionalidad adicional dentro de una subclase resultante que hereda los campos y métodos de la superclase.
> La consecuencia del uso de la herencia es que las subclases tienen la misma interfaz que su clase padre. 

La **herencia** permite crear una clase a partir de otra.

Por ejemplo:

```
Animal
   │
   ├── Perro
   │
   └── Gato
```

`Perro` y `Gato` heredan características de `Animal`.

### Java

```java
class Animal {

    protected String nombre;

    public Animal(String nombre) {
        this.nombre = nombre;
    }

    public void dormir() {
        System.out.println(nombre + " está durmiendo");
    }
}
```

Ahora:

```java
class Perro extends Animal {

    public Perro(String nombre) {
        super(nombre);
    }

    public void ladrar() {
        System.out.println("Guau");
    }
}
```

`Perro` tiene:

```
Perro
 ├── nombre       ← heredado
 ├── dormir()     ← heredado
 └── ladrar()     ← propio
```

Puedes hacer:

```java
Perro perro = new Perro("Firulais");

perro.dormir();
perro.ladrar();
```

### C++

En C++:

```c++
class Animal {

protected:
    std::string nombre;

public:
    Animal(std::string nombre)
        : nombre(nombre) {}

    void dormir() {
        std::cout << nombre << " está durmiendo\n";
    }
};
```

Y:

```c++
class Perro : public Animal {

public:
    Perro(std::string nombre)
        : Animal(nombre) {}

    void ladrar() {
        std::cout << "Guau\n";
    }
};
```

---

# Polimorfismo

Veamos algunos ejemplos con animales. La mayoría de los Animal puede emitir sonidos. Podemos anticipar que todas las subclases necesitarán sobrescribir el método base emitirSonido para que cada subclase pueda emitir el sonido correcto; por lo tanto, podemos declararlo abstracto directamente. Esto nos permite omitir cualquier implementación por defecto del método en la superclase, pero fuerza a todas las subclases a establecer las suyas propias. Imagina que ponemos varios gatos y perros dentro de una gran bolsa. Después, con los ojos tapados, vamos sacando los animales de la bolsa, de uno en uno. Al sacar un animal, no sabemos con seguridad lo que es. Pero si lo abrazamos lo suficiente, el animal emitirá un sonido específico de alegría, dependiendo de su clase concreta.

>El polimorfismo es la capacidad que tiene un programa de detectar la verdadera clase de un objeto e invocar su implementación, incluso aunque su tipo real sea desconocido en el
contexto actual.

También puedes pensar en el polimorfismo como la capacidad de un objeto para “fingir” ser otra cosa, normalmente una clase que extiende o una interfaz que implementa. En nuestro ejemplo, los perros y gatos de la bolsa fingen ser animales genéricos.


La idea fundamental es:

> **Una referencia de un tipo general puede apuntar a un objeto de un tipo específico y ejecutar el comportamiento correspondiente al objeto real.**

Tenemos:

```
             Animal
             /    \
            /      \
        Perro      Gato
```

Ambos tienen:

```
emitirSonido()
```

pero cada uno lo implementa de manera diferente.

## Java

Primero:

```java
abstract class Animal {

    public abstract void emitirSonido();
}
```

Perro:

```java
class Perro extends Animal {

    @Override
    public void emitirSonido() {
        System.out.println("Guau");
    }
}
```

Gato:

```java
class Gato extends Animal {

    @Override
    public void emitirSonido() {
        System.out.println("Miau");
    }
}
```

Ahora viene lo interesante:

```java
Animal animal;
```

Podemos hacer:

```java
animal = new Perro();
animal.emitirSonido();
```

Resultado:

```
Guau
```

Y:

```java
animal = new Gato();
animal.emitirSonido();
```

Resultado:

```
Miau
```

La variable:

```java
Animal animal;
```

es de tipo `Animal`, pero el objeto real puede ser:

```
Perro
```

o:

```
Gato
```

Java determina qué implementación utilizar.

# Polimorfismo con varios objetos

Aquí se vuelve mucho más útil:

```java
Animal[] animales = {
    new Perro(),
    new Gato(),
    new Perro()
};

for (Animal animal : animales) {
    animal.emitirSonido();
}
```

Resultado:

```
Guau
Miau
Guau
```

El `for` no necesita saber si tiene un `Perro` o un `Gato`.

Simplemente dice:

```java
animal.emitirSonido();
```

Y cada objeto ejecuta **su propia implementación**.

Eso es polimorfismo.