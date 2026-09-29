Un **entorno de desarrollo** es el conjunto de **herramientas, programas y configuraciones que utilizas para crear, probar y mantener software**.
[[PATH]]
Piensa en él como tu **taller de programación**. 🛠️

### Ejemplo sencillo

Si estás programando en Java, tu entorno de desarrollo podría ser:

```
┌─────────────────────────────────────┐
│       Entorno de desarrollo         │
│                                     │
│  JDK 21                             │
│    ↓                                │
│  IntelliJ IDEA                     │
│    ↓                                │
│  Maven / Gradle                    │
│    ↓                                │
│  Git                                │
│    ↓                                │
│  PostgreSQL                         │
│                                     │
└─────────────────────────────────────┘
```

Cada componente cumple una función:

- **JDK** → permite compilar y ejecutar Java.
- **IDE (IntelliJ, Eclipse, VS Code)** → editor con herramientas para programar.
- **Maven/Gradle** → administra dependencias y construye el proyecto.
- **Git** → controla las versiones del código.
- **PostgreSQL** → base de datos que puede utilizar tu aplicación.
- **Terminal** → permite ejecutar comandos y herramientas.

---

### ¿Y qué es un IDE?

Aquí suele aparecer la confusión:

**IDE ≠ entorno de desarrollo.**

Un **IDE (Integrated Development Environment)** es solamente **una parte del entorno de desarrollo**.

Por ejemplo:

```
Entorno de desarrollo
│
├── IDE
│   └── IntelliJ IDEA
│
├── Lenguaje
│   └── Java
│
├── JDK
│   └── JDK 21
│
├── Build tool
│   └── Gradle
│
├── Control de versiones
│   └── Git
│
└── Base de datos
    └── PostgreSQL
```

Por eso puedes tener un entorno de desarrollo aunque no uses un IDE.

Por ejemplo, podrías programar Java desde la terminal:

```
javac Main.java
java Main
```

Tu entorno sería:

```
Linux
 + JDK
 + terminal
 + editor Neovim
 + Git
```

y **seguirías teniendo un entorno de desarrollo**.

### ¿Y "entorno de desarrollo" vs "entorno de ejecución"?

También es importante distinguirlos:

```
DESARROLLO
    ↓
Escribes código
    ↓
Compilas
    ↓
Pruebas
    ↓
        PRODUCCIÓN
        ↓
    Ejecutas la aplicación
```

Por ejemplo, en Spring Boot podrías desarrollar con:

```
IntelliJ
Java 21
Gradle
PostgreSQL
Git
```

mientras que en producción podrías tener:

```
Linux
JRE/JDK
Spring Boot
PostgreSQL
Docker
```

En resumen:

> **Un entorno de desarrollo es todo el conjunto de herramientas y configuraciones que necesitas para desarrollar software.**

Y **un IDE es una herramienta dentro de ese entorno**, no el entorno completo.



