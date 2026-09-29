### 1. Comprueba si ya tienes una clave

```
ls ~/.ssh
```

Si ves algo como:

```
id_ed25519
id_ed25519.pub
```

probablemente ya tienes una.

Si no tienes, créala:

```
ssh-keygen -t ed25519 -C "tu_correo_de_github"
```

Puedes presionar Enter para aceptar las opciones predeterminadas.

### 1. Inicia el agente SSH en Fish

Ejecuta:

```
eval (ssh-agent -c)
```

Luego agrega tu clave:

```
ssh-add ~/.ssh/id_ed25519
```

Deberías obtener algo como:

```
Identity added: /home/reno/.ssh/id_ed25519
```

### 2. Agrega la clave pública a GitHub

Ya la mostraste correctamente con:

```
cat ~/.ssh/id_ed25519.pub
```

Copia **toda la línea** que comienza con:

```
ssh-ed25519 AAAA...
```

En GitHub ve a:

**Settings → SSH and GPG keys → New SSH key**

Ponle, por ejemplo:

```
Title: CachyOS
```

y pega la clave en **Key**.

### 3. Prueba la conexión

Después:

```
ssh -T git@github.com
```

La primera vez probablemente te preguntará:

```
Are you sure you want to continue connecting (yes/no/[fingerprint])?
```

Escribe:

```
yes
```

Si todo está correcto, deberías recibir:

```
Hi ORenoX! You've successfully authenticated, but GitHub does not provide shell access.
```

### 4. Cambia tu repositorio de HTTPS a SSH

Ahora mismo tu `origin` probablemente sigue siendo:

```
https://github.com/ORenox/bashScripting.git
```

Cámbialo:

```
git remote set-url origin git@github.com:ORenox/bashScripting.git
```

Comprueba:

```
git remote -v
```

Debe aparecer:

```
origin  git@github.com:ORenox/bashScripting.git (fetch)
origin  git@github.com:ORenox/bashScripting.git (push)
```

Finalmente:

```
git push -u origin main
```

### Una cosa importante

Veo que pusiste:

```
renato1234567r89@gmail.com
```

como comentario de la clave. **No es un problema**, pero asegúrate de que ese correo esté agregado/verificado en GitHub si quieres asociar correctamente la identidad de la clave/commits.

Y **no compartas nunca**:

```
~/.ssh/id_ed25519
```

Ese es tu archivo **privado**.

El que sí puedes compartir con GitHub es:

```
~/.ssh/id_ed25519.pub
```

### ¿Por qué antes no te pedía todo esto?

Probablemente antes tenías GitHub configurado de alguna forma que ya te autenticaba, o estabas usando un método distinto.

Ahora tu repositorio tiene un remoto **HTTPS**:

```
https://github.com/ORenox/bashScripting.git
```

Cuando haces:

```
git push
```

GitHub te pide autenticación. GitHub **ya no acepta la contraseña normal de tu cuenta** para operaciones Git por HTTPS.

Por eso te apareció:

```
Username for 'https://github.com':
Password for 'https://ORenoX@github.com':
```

Y falló.

---

# En tu caso

Tú hiciste:

```
GitHub
   │
   │ git clone
   ▼
Tu computadora
   │
   │ modificaste archivos
   ▼
git push
   │
   ▼
GitHub
```

El problema no fue el `clone`.

El `clone` funcionó porque **descargar un repositorio público no requiere autenticación**.

El problema apareció cuando quisiste hacer:

```
git push
```

porque eso **modifica tu repositorio en GitHub**, y GitHub necesita verificar que realmente eres tú.

---

# ¿Tengo que hacer todo esto cada vez?

**No.**

Una vez que configures SSH correctamente:

```
ssh-keygen
ssh-add
```

y agregues tu clave a GitHub, podrás trabajar normalmente.

Por ejemplo:

```
git clone git@github.com:ORenox/bashScripting.git

cd bashScripting

# modificas archivos

git add .
git commit -m "Add exercise"

git push
```

No tendrás que poner usuario y contraseña cada vez.

---

# ¿Y si quiero colaborar en el repositorio de otra persona?

Aquí hay dos situaciones.

## 1. Tienes permisos de escritura

Si el dueño del repositorio te agregó como colaborador:

```
Repositorio de otra persona
        │
        │ collaborator
        ▼
      Tú
```

Puedes clonarlo:

```
git clone git@github.com:usuario/proyecto.git
```

Crear una rama:

```
git switch -c mi-cambio
```

Modificar:

```
git add .
git commit -m "Mi cambio"
```

Subir:

```
git push -u origin mi-cambio
```

Y crear un **Pull Request**.

---

# 2. NO tienes permisos de escritura

Esta es la situación típica cuando quieres contribuir a un proyecto de otra persona.

Haces un **Fork**:

```
             Repositorio original
                     │
                     │ Fork
                     ▼
              Tu repositorio
                     │
                     │ clone
                     ▼
                Tu PC
                     │
                     │ push
                     ▼
              Tu repositorio
                     │
                     │ Pull Request
                     ▼
             Repositorio original
```

Por ejemplo:

```
git clone git@github.com:ORenox/proyecto.git
```

Trabajas en una rama:

```
git switch -c fix-error
```

Luego:

```
git add .
git commit -m "Fix error"
git push -u origin fix-error
```

Y desde GitHub haces:

**Pull Request → repositorio original**

---

## Lo importante que debes recordar

Hay tres cosas diferentes:

|Acción|¿Qué hace?|Autenticación|
|---|---|---|
|`git clone`|Descarga el repo|Puede no necesitarla|
|`git push`|Sube tus cambios|**Sí**|
|Pull Request|Propone integrar cambios|GitHub|

Y **SSH no es algo que tengas que repetir por cada repositorio**.

Una vez que tengas:

```
~/.ssh/id_ed25519
~/.ssh/id_ed25519.pub
```

asociada a tu cuenta de GitHub, puedes usar esa misma identidad para **todos tus repositorios de GitHub desde esa computadora**.

Ahora tienes:

```
https://github.com/ORenox/bashScripting.git
```

y quieres cambiarlo a:

```
git@github.com:ORenox/bashScripting.git
```

Haz:

```
git remote set-url origin git@github.com:ORenox/bashScripting.git
```

Comprueba:

```
git remote -v
```

Deberías ver:

```
origin  git@github.com:ORenox/bashScripting.git (fetch)
origin  git@github.com:ORenox/bashScripting.git (push)
```

Luego prueba:

```
git push -u origin main
```

Pero antes asegúrate de que SSH funciona:

```
ssh -T git@github.com
```

Si recibes:

```
Hi ORenoX! You've successfully authenticated, but GitHub does not provide shell access.
```

🎉 **Ya estás configurado.**

A partir de ahí, cuando clones repositorios tuyos, puedes directamente usar la URL SSH:

```
git clone git@github.com:ORenox/bashScripting.git
```

Y para otros repositorios donde tengas permisos:

```
git clone git@github.com:usuario/proyecto.git
```

No tienes que volver a configurar una clave SSH por cada repositorio.