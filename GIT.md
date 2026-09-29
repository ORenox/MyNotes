
Supongamos:

```
A --- B --- C
          ↑
         HEAD
```

y quieres volver a `B`.

## 1. Quiero simplemente ver/recuperar el estado de un commit anterior

Si quieres que tus archivos vuelvan temporalmente al estado de `B`:

```
git switch --detach B
```

Pero esto te deja en **detached HEAD**. No es normalmente lo que quieres si estás continuando el desarrollo.

---

## 2. Quiero que mi rama vuelva permanentemente a ese commit

Si quieres:

```
ANTES:

A --- B --- C
          ↑
         master

DESPUÉS:

A --- B
     ↑
   master
```

usa:

```
git reset --hard B
```

Por ejemplo, primero mira tus commits:

```
git log --oneline
```

Obtendrás algo como:

```
8f32abc Agrega menú
75a914a Crea estructura inicial
```

Entonces:

```
git reset --hard 75a914a
```

Ahora tu rama vuelve a ese commit.

### ⚠️ Cuidado con `--hard`

Esto elimina del working directory los cambios posteriores al commit.

Por ejemplo:

```
A --- B --- C
```

Si haces:

```
git reset --hard B
```

`C` deja de estar en la historia de tu rama.

---

## 3. Quiero deshacer un commit pero conservar el historial

Esta es una opción mucho más segura si el commit ya fue compartido/subido:

```
git revert C
```

Git crea un **nuevo commit** que deshace los cambios de `C`:

```
A --- B --- C --- D
              ↑
           revert C
```

No elimina `C`.

---

## 4. Quiero volver al commit anterior pero conservar mis archivos

Puedes usar:

```
git reset --soft B
```

La rama vuelve a `B`, pero los cambios de `C` quedan preparados en staging.

O:

```
git reset --mixed B
```

La rama vuelve a `B`, pero los cambios quedan en tu working directory **sin staging**.

La diferencia:

```
git reset --soft B
        ↓
cambios → staged

git reset --mixed B
        ↓
cambios → unstaged

git reset --hard B
        ↓
cambios → eliminados
```

---

### ¿Cuál deberías usar?

Si estás practicando Git y **todavía no has subido tus commits a GitHub**, probablemente lo que buscas sea:

```
git log --oneline
```

encuentras el commit:

```
8f32abc commit que no quiero
75a914a commit al que quiero volver
```

y:

```
git reset --hard 75a914a
```

Pero si **ya hiciste `git push`**, normalmente conviene usar `git revert` en lugar de reescribir la historia con `reset --hard`.