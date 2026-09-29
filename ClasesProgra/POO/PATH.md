re

#Path
`PATH` es una **variable de entorno** que contiene una lista de carpetas donde el sistema debe buscar programas.
```bash
echo $PATH
```

![[Pasted image 20260825171623.png]]

```bash
which git

# readlink -f $(which java) para enlaces simbólicos como java
```

Cuando instalo un programa, el instalador modifica el PATH para evitar que tener que usar la ruta larga de un ejecutable
ej:
en lugar de llamar un comando git con:
```shell
/usr/bin/git init
```
solo usamos el nombre del comando a ejecutar:

```shell
git init
```

la shell encuentra el ejecutable automáticamente.

`PATH` contiene **directorios**, no los ejecutables.

----
Un comando útil para saber las versiones de un programa.

```
type -a git
```

Esto puede mostrarte **todas las versiones** que encuentra:

```
git is /usr/bin/git
git is /usr/local/bin/git

```

---

Supongamos que escribes:

```
git status
```

Tú ves:

```
git status
```

pero la shell tiene que descubrir **qué es `git`**.

Primero revisa si `git` es algo que ya conoce, por ejemplo:

- un alias
- una función
- un builtin de la shell
- un ejecutable

Puedes comprobarlo:

```
type git
```

Probablemente:

```bash
git is /usr/bin/git
```

Entonces la shell termina ejecutando:

```bash
/usr/bin/git status
```


# `PATH` es básicamente una lista de lugares donde buscar

Imagina:

```
echo $PATH
```

y obtienes:

```
/home/ren/.local/bin:/usr/local/bin:/usr/bin:/bin
```

La shell interpreta eso como:

```
1. /home/ren/.local/bin
2. /usr/local/bin
3. /usr/bin
4. /bin
```

Si escribes:

```
python
```

busca:

```
/home/ren/.local/bin/python
```

si no existe:

```
/usr/local/bin/python
```

si tampoco:

```
/usr/bin/python
```

etc.

Cuando encuentra uno, **deja de buscar**.

# Agregarlo a PATH

Puedes hacer temporalmente:

```
export PATH="$PATH:/home/ren/mycompiler/bin"
```

Ahora:

```
mycompiler
```

funcionará.

Pero hay una característica importante:

### Ese cambio es temporal.

Si cierras la terminal y abres otra, probablemente desaparezca.

# ¿Qué tiene que ver `bin` con todo esto?

Mira una instalación de Java:

```
jdk-21/
├── bin/
│   ├── java
│   ├── javac
│   ├── jar
│   └── javadoc
├── lib/
├── include/
└── ...
```

Cuando ejecutas:

```
java
```

realmente estás ejecutando algo parecido a:

```
/path/to/jdk-21/bin/java
```

Y cuando haces:

```
javac
```

es:

```
/path/to/jdk-21/bin/javac
```

Por eso muchas instrucciones de instalación de Java dicen que agregues:

```
/path/to/jdk-21/bin
```

a `PATH`.