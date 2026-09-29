`.java` → `javac` → `.class` → `java`


Ese `.class` contiene **bytecode de Java**. No es exactamente un binario nativo como un ejecutable de C/C++; será ejecutado por la JVM.

`java` recibe el **nombre de la clase**, y busca su archivo `.class`.


```bash
javap -c HolaMundo
```
Eso es bastante interesante porque te permite ver el **bytecode que generó `javac`**.

```java
public class HolaMundo { public static void main(String[] args) throws InterruptedException { 
int x = 0; 
for (int i = 0; i <= 10; i++) { 
System.out.printf("El número es: %d%n", i + x); 
Thread.sleep(500); 
} 
} 
}
```

--- 
### Ejemplo con Herencia
