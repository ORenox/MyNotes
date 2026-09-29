### Ejercicio 1: primitivo vs objeto

Prueba esto:

```java
public class Main {

    public static void main(String[] args) {

        int a = 10;
        int b = a;

        Integer x = 10;
        Integer y = x;

        System.out.println(a == b);
        System.out.println(x == y);

        System.out.println(System.identityHashCode(x));
        System.out.println(System.identityHashCode(y));
    }
}
```

Primero piensa qué debería pasar antes de ejecutarlo.

---

### ¿Qué está pasando?

Con los primitivos:

```
int a = 10;
int b = a;
```

conceptualmente:

```
a ──→ 10

b ──→ 10
```

No hay un objeto compartido.

En cambio:

```
Integer x = 10;
Integer y = x;
```

conceptualmente:

```
x ─────┐
       ↓
     ┌──────────┐
     │ Integer  │
     │   10     │
     └──────────┘
       ↑
       │
y ─────┘
```

`x` y `y` contienen la misma referencia.

Por eso:

```
x == y
```

puede ser `true`.


## Ejercicio 2: haz que sea más evidente

Ahora crea tus propios objetos:

```
class Persona {

    String nombre;

    Persona(String nombre) {
        this.nombre = nombre;
    }
}
```

Y:

```java
public class Main {

    public static void main(String[] args) {

        Persona p1 = new Persona("Renato");
        Persona p2 = p1;

        System.out.println(p1 == p2);

        System.out.println(System.identityHashCode(p1));
        System.out.println(System.identityHashCode(p2));

        System.out.println(p1.getClass());
    }
}
```

Deberías obtener algo como:

```
true
12345678
12345678
class Persona
```

El mismo `identityHashCode` **no es una dirección de memoria**, pero sirve como una forma práctica de identificar el objeto durante este experimento.

## Ahora viene el experimento importante

Haz:

```
Persona p1 = new Persona("Renato");
Persona p2 = new Persona("Renato");

System.out.println(p1 == p2);
```

Obtendrás:

```
false
```

Aunque ambos tengan `"Renato"`:

```
p1 ─────→ ┌──────────────┐
          │ Persona      │
          │ Renato       │
          └──────────────┘


p2 ─────→ ┌──────────────┐
          │ Persona      │
          │ Renato       │
          └──────────────┘
```

Son **dos objetos diferentes**.

Mientras que:

```
Persona p1 = new Persona("Renato");
Persona p2 = p1;
```

es:

```
p1 ─────┐
        ↓
       ┌──────────────┐
       │ Persona      │
       │ Renato       │
       └──────────────┘
        ↑
        │
p2 ─────┘
```

---

### Y hay una herramienta MUY interesante

Puedes usar:

```
System.out.println(p1);
```

pero Java llama a `toString()`.

También puedes inspeccionar:

```
System.out.println(p1.getClass());
```

y:

```
System.out.println(p1.getClass().getSuperclass());
```

Por ejemplo:

```
class Persona
class java.lang.Object
```

Esto te permite experimentar directamente con la jerarquía:

```
Object
  ↑
Persona
```