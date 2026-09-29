**en Java, `Object` es la superclase raíz de todas las clases**.
[[Objetos y Clases]]
Por ejemplo:

```java
class Persona {
}
```

Java lo interpreta esencialmente como:

```java
class Persona extends Object {
}
```

Y si tienes:

```java
class Estudiante extends Persona {
}
```

la jerarquía sería:

```
Object
   ↑
Persona
   ↑
Estudiante
```

Por eso un `Estudiante` también puede usar métodos definidos en `Object`, como:

```
toString()
equals()
hashCode()
getClass()
```

### Pero ojo con los tipos primitivos

`Object` **no es el padre de los primitivos**:

```
int
double
boolean
char
```

Estos **no son objetos**.

Por eso existe algo como `Integer`:

```
int x = 10;          // primitivo
Integer y = 10;      // objeto
```

`Integer` sí pertenece a la jerarquía de `Object`:

```
Object
  ↑
Number
  ↑
Integer
```

Así que una forma más precisa de decirlo es:

> **`java.lang.Object` es la superclase raíz de todas las clases de Java.**

# ¿Por qué es importante?

Porque permite hacer algo muy poderoso:

```
Object x;
```

Una variable de tipo `Object` puede almacenar una referencia a prácticamente cualquier objeto:

```
Object a = new Persona();
Object b = "Hola";
Object c = new Integer(10);
Object d = new ArrayList<>();
```

Conceptualmente:

```
                 Object
                   ↑
        ┌──────────┼──────────┐
        │          │          │
     Persona     String    Integer
```

Por eso puedes hacer:

```
Object x = new Persona();
```

porque:

```
Persona IS-A Object
```

Es decir:

> Una `Persona` es un `Object`.


# Los métodos de `Object`

Aquí está una de las razones principales por las que `Object` es tan importante.

`Object` proporciona métodos que todos los objetos pueden utilizar.

Entre los más importantes:

```
toString()
equals()
hashCode()
getClass()
```

También existen métodos relacionados con concurrencia:

```
wait()
notify()
notifyAll()
```

y `clone()` bajo ciertas condiciones.