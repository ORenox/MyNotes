[[Git ignore]]
![[Pasted image 20260824222621.png]]
# Git

**Git es un sistema de control de versiones distribuido.**

Su función principal es registrar y administrar los cambios realizados en un proyecto a lo largo del tiempo.

Permite:

- Guardar un historial de cambios.
    
- Comparar diferentes versiones de un proyecto.
    
- Recuperar estados anteriores.
    
- Trabajar con diferentes ramas.
    
- Trabajar varias personas sobre un mismo proyecto.
    
- Sincronizar un repositorio local con un repositorio remoto.
    

> **Git ≠ GitHub**
> 
> - **Git** → herramienta de control de versiones.
>     
> - **GitHub** → plataforma que permite alojar repositorios Git y colaborar con otros usuarios.
>     

---

# Conceptos fundamentales

Una de las ideas más importantes de Git es entender el recorrido de los cambios:

```text
Working Tree
     │
     │ git add
     ▼
Staging Area
     │
     │ git commit
     ▼
Repository
```

## Working Tree / Working Directory

Es el estado de los archivos **con los que estás trabajando actualmente**.

Aquí realizamos modificaciones, creamos archivos, eliminamos archivos, etc.

Por ejemplo:

```text
bike-shop/
├── bike-shop.sh
└── README.md
```

Si modificamos `bike-shop.sh`, ese cambio inicialmente solamente existe en el **Working Tree**.

El directorio `.git/` contiene la información interna del repositorio y **no forma parte del Working Tree como un archivo normal del proyecto**.

---

## Staging Area / Index

Es una zona intermedia entre el **Working Tree** y el **Repository**.

Aquí seleccionamos qué cambios queremos incluir en el próximo commit.

Por ejemplo:

```bash
git add bike-shop.sh
```

Ahora los cambios de `bike-shop.sh` están preparados para el próximo commit.

Esto permite agrupar cambios relacionados en commits separados.

Por ejemplo, si modificamos:

```text
bike-shop.sh
README.md
database.sql
```

podemos hacer:

```bash
git add bike-shop.sh
git commit -m "Add bike validation"
```

y posteriormente:

```bash
git add README.md
git commit -m "Update documentation"
```

### ¿Por qué es importante?

Los commits deberían representar **cambios relacionados y coherentes**.

Esto facilita:

- entender el historial;
    
- revisar cambios;
    
- encontrar errores;
    
- revertir cambios específicos.
    

---

## Repository

Es donde Git almacena la información del historial del proyecto.

Los commits contienen snapshots del estado de los archivos en diferentes momentos.

```text
Commit A
   ↓
Commit B
   ↓
Commit C
   ↓
Commit D
```

Cada commit representa un estado registrado del proyecto.

El repositorio local se encuentra dentro del directorio:

```text
.git/
```

---

# Commit

Un **commit** es un registro de cambios en el historial del repositorio.

Para crear uno:

```bash
git add .
git commit -m "Add bike validation"
```

El proceso es:

```text
Modificar archivos
       ↓
   git add
       ↓
 Staging Area
       ↓
 git commit
       ↓
   Repository
```

Un buen mensaje de commit debe describir claramente qué cambio se realizó.

```bash
git commit -m "Add customer validation"
```

es preferible a:

```bash
git commit -m "changes"
```

---

# Commit ID / Hash

Cada commit tiene un identificador único llamado **hash**.

Por ejemplo:

```text
8a32f1c
```

El hash permite identificar un commit específico.

Un commit puede verse conceptualmente así:

```text
8a32f1c
│
├── Author
├── Date
├── Commit message
└── Snapshot
```

---

# HEAD

`HEAD` es una referencia que indica **dónde estamos actualmente dentro del historial de Git**.

Por ejemplo:

```text
A ---- B ---- C
             ↑
            HEAD
```

Si estamos trabajando en una rama llamada `main`, normalmente `HEAD` apunta al commit más reciente de esa rama.

---

# Comandos básicos

## Ver el directorio actual

```bash
pwd
```

Muestra el **current working directory**.

---

## Ver la versión de Git

```bash
git --version
```

Ejemplo:

```text
git version 2.x.x
```

---

## Inicializar un repositorio

```bash
git init
```

Convierte el directorio actual en un repositorio Git.

Esto crea el directorio:

```text
.git/
```

---

# Configuración

## Ver la configuración

```bash
git config --list --show-origin
```

Muestra la configuración y el archivo desde el cual proviene cada configuración.

---

## Configurar nombre

```bash
git config --global user.name "Jane Doe"
```

---

## Configurar correo

```bash
git config --global user.email "janedoe@example.com"
```

Estas configuraciones se utilizan para identificar al autor de los commits.

---

## Configurar el editor

Por ejemplo, para utilizar VS Code:

```bash
git config --global core.editor "code --wait"
```

Git utilizará ese editor cuando necesite que escribamos información, como el mensaje de un commit.

---

# Estado del repositorio

## `git status`

```bash
git status
```

Muestra el estado actual del repositorio.

Permite saber, entre otras cosas:

- qué archivos fueron modificados;
    
- qué archivos son nuevos;
    
- qué cambios están en staging;
    
- en qué rama estamos.
    

Es uno de los comandos que más se utilizan durante el trabajo diario con Git.

---

# Historial

## `git log`

```bash
git log
```

Muestra el historial de commits.

Una versión resumida:

```bash
git log --oneline
```

También podemos mostrar estadísticas:

```bash
git log --oneline --stat
```

Ejemplo:

```text
8a32f1c Add bike validation
51d8ab2 Create bike shop script
```

---

## Mostrar un commit

```bash
git show HEAD~1
```

Muestra información sobre el commit anterior al commit actual.

Para mostrar solamente estadísticas:

```bash
git show --stat HEAD~1
```

### Referencias como `HEAD~1`

```text
HEAD       → commit actual
HEAD~1     → commit anterior
HEAD~2     → dos commits atrás
HEAD~3     → tres commits atrás
```

---

# Diferencias entre cambios

## `git diff`

Muestra las diferencias entre el **Working Tree** y el **Staging Area**.

```bash
git diff
```

Para un archivo específico:

```bash
git diff -- nombre_archivo
```

Por ejemplo:

```bash
git diff -- bike-shop.sh
```

---

## `git diff --cached`

Muestra los cambios que están en el **Staging Area**, pero que todavía no forman parte de un commit.

```bash
git diff --cached
```

También existe:

```bash
git diff --staged
```

Ambos hacen referencia a los cambios staged.

---

## `git diff HEAD`

Compara el estado actual de los archivos con el último commit.

```bash
git diff HEAD
```

Incluye:

- cambios que todavía están en el Working Tree;
    
- cambios que ya están en Staging.
    

Conceptualmente:

```text
             HEAD
              │
              ▼
         Last commit
              │
       ┌──────┴──────┐
       ▼             ▼
   Staging       Working Tree
```

---

## Comparar dos commits

```bash
git diff A B
```

Compara el estado de dos commits.

Por ejemplo:

```bash
git diff abc123 def456
```

También puedes utilizar referencias como:

```bash
git diff HEAD~2 HEAD
```

para comparar el estado de hace dos commits con el estado actual.

---

# Branches / Ramas

Una rama permite trabajar sobre una línea de desarrollo independiente.

Por ejemplo:

```text
A ---- B ---- C        main
           \
            D ---- E   feature
```

La rama `feature` puede utilizarse para desarrollar una nueva funcionalidad sin modificar directamente `main`.

---

## Ver las ramas

```bash
git branch
```

---

## Crear una rama

```bash
git branch <nombre_rama>
```

Por ejemplo:

```bash
git branch feature-login
```

Esto **crea la rama, pero no cambia a ella**.

---

## Crear y cambiar de rama

```bash
git switch -c <nombre_rama>
```

Por ejemplo:

```bash
git switch -c feature-login
```

Hace dos cosas:

1. Crea la rama.
    
2. Cambia a esa rama.
    

---

## Cambiar de rama

```bash
git switch <nombre_rama>
```

Por ejemplo:

```bash
git switch main
```

---

## Cambiar el nombre de una rama

Si estamos actualmente en la rama que queremos renombrar:

```bash
git branch -m <nuevo_nombre>
```

Por ejemplo:

```bash
git branch -m main
```

Si queremos especificar explícitamente la rama actual y el nuevo nombre:

```bash
git branch -m <nombre_actual> <nuevo_nombre>
```

Por ejemplo:

```bash
git branch -m master main
```

---

# Remotes

Un **remote** es una referencia a otro repositorio Git, normalmente un repositorio alojado en un servidor como GitHub.

Por ejemplo:

```text
Repositorio local
       │
       │
       ▼
     origin
       │
       ▼
GitHub repository
```

`origin` es simplemente el nombre convencional que Git asigna al remote principal cuando clonamos un repositorio.

---

## Ver los remotes

```bash
git remote -v
```

Muestra los remotes configurados y sus URLs.

Ejemplo:

```text
origin  https://github.com/user/project.git (fetch)
origin  https://github.com/user/project.git (push)
```

> `origin` no es un comando ni una palabra especial obligatoria. Es simplemente un **nombre para identificar un remote**.

---

# Comandos esenciales

```bash
git init

git status

git add <archivo>
git add .

git commit -m "mensaje"

git log
git log --oneline

git diff
git diff --cached
git diff HEAD

git branch
git branch <nombre>
git switch <rama>
git switch -c <nombre>

git merge <rama>

git remote -v

git push
git pull
```

---

# Flujo básico de trabajo

```text
                modificar archivos
                       │
                       ▼
                 Working Tree
                       │
                    git add
                       │
                       ▼
                 Staging Area
                       │
                   git commit
                       │
                       ▼
                   Repository
                       │
                    git push
                       │
                       ▼
                  GitHub/Remote
```

El flujo diario normalmente se parece a:

```bash
git status

# realizar cambios...

git diff

git add .

git diff --staged

git commit -m "Describe the changes"

git push
```

> Una buena práctica es revisar los cambios antes de crear el commit, especialmente utilizando `git diff` y `git diff --staged`.

### Estructura

```
project/
├── .git/
├── .gitignore
├── README.md
└── main.py
```

> **Importante:** `.gitignore` afecta a archivos que todavía no están siendo rastreados por Git. Si un archivo ya fue agregado al repositorio, añadirlo después a `.gitignore` no hace que Git deje de rastrearlo automáticamente.

---

## Patrones comunes

```
.env           # archivo específico
*.log          # cualquier archivo .log
node_modules/  # directorio
*.pyc          # archivos .pyc
```

|Patrón|Significado|
|---|---|
|`.env`|Ignora un archivo llamado `.env`|
|`*.log`|Ignora cualquier archivo que termine en `.log`|
|`node_modules/`|Ignora el directorio `node_modules`|
|`*.pyc`|Ignora cualquier archivo `.pyc`|

### `!` para crear excepciones

El carácter `!` permite indicar una excepción a una regla de ignorado.

```
*.log
!important.log
```

Significa:

```
Todos los .log       → ignorados
important.log        → NO ignorado
```

---

## Comprobar si un archivo está siendo ignorado

Puedes utilizar:

```
git check-ignore -v <archivo>
```

Ejemplo:

```
git check-ignore -v .env
```

La opción `-v` muestra **qué regla del `.gitignore` está provocando que el archivo sea ignorado**.

---

## Dejar de rastrear un archivo ignorado

Si agregaste un archivo por error y posteriormente lo colocaste en `.gitignore`, debes quitarlo del seguimiento de Git:

```
git rm --cached <archivo>
```

Ejemplo:

```
git rm --cached .env
```

Después:

```
git commit -m "Remove .env from tracking"
```

Para un directorio:

```
git rm -r --cached node_modules/
```

> Esto elimina el archivo o directorio del **índice de Git**, pero no necesariamente de tu computadora.

---

# Remotes

Un **remote** es una referencia a un repositorio remoto, normalmente alojado en servicios como GitHub, GitLab o Bitbucket.

## Ver remotes

### Solo nombres

```
git remote
```

Ejemplo:

```
origin
```

### Nombres + URLs

```
git remote -v
```

Ejemplo:

```
origin  https://github.com/user/project.git (fetch)
origin  https://github.com/user/project.git (push)
```

Normalmente:

```
origin
   ↓
Repositorio remoto
```

> `origin` es simplemente el nombre que Git asigna normalmente al repositorio remoto principal. No es obligatorio que se llame `origin`.

---

## Agregar un remote

Si tienes un repositorio local y quieres conectarlo con GitHub:

```
git remote add origin <URL>
```

Ejemplo:

```
git remote add origin https://github.com/user/project.git
```

Puedes comprobarlo con:

```
git remote -v
```

---

## Cambiar la URL de un remote

```
git remote set-url origin <NUEVA_URL>
```

Ejemplo:

```
git remote set-url origin https://github.com/user/new-project.git
```

---

## Eliminar un remote

```
git remote remove origin
```

Esto elimina la referencia al remote **en tu repositorio local**, pero no elimina el repositorio de GitHub.

---

# `push`

`git push` envía tus commits desde el repositorio local hacia un repositorio remoto.

```
git push
```

Visualmente:

```
Repositorio local
       │
       │ git push
       ▼
Repositorio remoto
     GitHub
```

## Primera vez

Cuando una rama local todavía no tiene una rama remota asociada:

```
git push -u origin main
```

También puedes escribir:

```
git push --set-upstream origin main
```

La opción `-u` (`--set-upstream`) establece la relación entre:

```
rama local:   main
      ↓
rama remota:  origin/main
```

Después de establecerla, normalmente basta con:

```
git push
```

---

# `fetch` vs `pull`

Ambos comandos obtienen información del repositorio remoto, pero no hacen exactamente lo mismo.

## `git fetch`

```
git fetch
```

Descarga los cambios y la información del repositorio remoto, pero **no integra esos cambios en tu rama actual**.

Por ejemplo:

```
GitHub
  │
  │ git fetch
  ▼
origin/main
  │
  X
  │
main
```

Tu rama `main` no cambia directamente.

Esto es útil cuando quieres **revisar primero qué cambios existen en el remoto** antes de integrarlos.

Puedes consultar, por ejemplo:

```
git log main..origin/main
```

---

## `git pull`

```
git pull
```

Normalmente realiza dos operaciones:

```
git fetch
   +
integración de cambios
```

Conceptualmente:

```
GitHub
  │
  │ fetch
  ▼
Información remota
  │
  │ integración
  ▼
Tu rama actual
```

La integración puede realizarse mediante `merge` o, dependiendo de las opciones y configuración, mediante `rebase`.

Por eso:

```
git fetch
```

te permite inspeccionar antes de integrar, mientras que:

```
git pull
```

normalmente descarga e integra los cambios en un solo paso.

---

# `clone`

`git clone` descarga un repositorio remoto a tu computadora y crea una copia de trabajo local.

```
git clone <URL>
```

Ejemplo:

```
git clone https://github.com/user/project.git
```

Esto normalmente crea un directorio:

```
project/
├── .git/
├── README.md
└── ...
```

Al clonar, Git normalmente configura automáticamente:

```
origin → URL del repositorio clonado
```

Puedes comprobarlo con:

```
git remote -v
```

---

# Flujo básico con GitHub

Un flujo típico para trabajar con un repositorio existente es:

```
git clone https://github.com/user/project.git
cd project
```

Realizas cambios y después:

```
git status
git add .
git commit -m "Describe your changes"
git push
```

Si otras personas hicieron cambios en el remoto:

```
git fetch
```

Puedes revisar qué cambió y posteriormente integrar los cambios.

O, si quieres descargar e integrar directamente:

```
git pull
```

---

# Concepto importante: local vs remoto

Una forma sencilla de visualizar Git es:

```
                 GitHub
             Repositorio remoto
                    ▲
                    │
                  push
                    │
                    │
              ┌───────────┐
              │   Local   │
              │ Repository│
              └───────────┘
                    │
              Working Tree
                    │
             tus archivos
```

Los comandos principales para mover información son:

```
clone
  ↓
Remoto → Local


fetch
  ↓
Remoto → Información remota local


pull
  ↓
Remoto → Local + integración


push
  ↓
Local → Remoto
```

La idea clave:

- **`clone`** → obtienes un repositorio por primera vez.
- **`fetch`** → actualizas la información sobre el remoto sin modificar directamente tu rama actual.
- **`pull`** → obtienes cambios y normalmente los integras.
- **`push`** → envías tus commits al remoto.
- **`remote`** → administras las conexiones con repositorios remotos.
- **`.gitignore`** → defines qué archivos Git debe ignorar.