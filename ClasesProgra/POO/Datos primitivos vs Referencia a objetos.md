[[Wrapper]]
## En Java existen dos grandes categorías

```
                    TIPOS EN JAVA
                         │
             ┌───────────┴───────────┐
             │                       │
        PRIMITIVOS              REFERENCIA
                                  (objetos)
```

### Primitivos

Son los tipos básicos del lenguaje:

```
int
double
float
long
short
byte
char
boolean
```

```java
int edad = 25;
double precio = 19.99;
boolean activo = true;
char letra = 'A';
```

Un `int` **no es un objeto**.

# ¿Qué significa "no primitivo"?

Normalmente cuando escuchas **"no primitivo"**, se refiere a tipos de referencia.

Por ejemplo:

```java
String nombre = "Renato";
Persona persona = new Persona();
Integer numero = 10;
```

Estos son tipos de referencia.

La diferencia fundamental es que una variable de referencia **hace referencia a un objeto**.

Por ejemplo:

```
Persona persona = new Persona();
```

Conceptualmente:

```
persona
  │
  ▼
┌───────────────┐
│    Persona    │
│   objeto      │
└───────────────┘
```

Mientras que:

```
int edad = 25;
```

contiene directamente un valor primitivo.

```
edad
 │
 ▼
25
```

Aqui entra los wrappers
