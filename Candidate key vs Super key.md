**A Super Key can contain extra attributes not essential for unique identification, while a Candidate Key cannot.**

Una **Super Key** es cualquier conjunto de atributos que permite identificar de manera única una fila.

Una **Candidate Key** es una **Super Key mínima**: no puede tener atributos adicionales innecesarios.

Por ejemplo, imagina:

| id  | email                             | nombre |
| --- | --------------------------------- | ------ |
| 1   | [a@email.com](mailto:a@email.com) | Ana    |
| 2   | [b@email.com](mailto:b@email.com) | Luis   |
Podríamos tener:

```
{id}
```

como Super Key porque `id` identifica únicamente cada fila.

También:

```
{id, nombre}
```

es una Super Key, porque `id` ya identifica la fila y `nombre` es innecesario.

Pero:

```
{id, nombre}
```

**no es Candidate Key**, porque podemos eliminar `nombre` y seguir identificando únicamente la fila.

Por tanto:

```
Super Key
    ↓
puede tener atributos innecesarios

Candidate Key
    ↓
Super Key mínima
    ↓
sin atributos innecesarios
```

Se llaman así por la **idea que representa cada palabra**. Si entiendes el nombre, es mucho más fácil recordarlas.

### 1. Super Key → "Super"

Una **Super Key** es un conjunto de atributos que tiene la capacidad de **identificar de manera única** una fila.

"Super" porque puede ser **más grande de lo necesario**.

Por ejemplo, en:

|id|email|nombre|
|---|---|---|
|1|[a@mail.com](mailto:a@mail.com)|Ana|
|2|[b@mail.com](mailto:b@mail.com)|Luis|

Todas estas podrían ser Super Keys:

```
{id}
{email}
{id, nombre}
{id, email}
{id, email, nombre}
```

¿Por qué?

Porque todas permiten identificar una fila de forma única.

Pero algunas tienen información **extra**.

Por ejemplo:

```
{id, nombre}
```

`id` ya era suficiente. `nombre` sobra.

---

### 2. Candidate Key → "Candidate"

Ahora buscamos las **Super Keys mínimas**.

Tenemos:

```
{id}
{email}
{id, nombre}
{id, email}
```

Las que no tienen atributos innecesarios son:

```
{id}
{email}
```

Estas son **Candidate Keys**.

¿Por qué "Candidate"?

Porque son **candidatas a convertirse en la clave principal (`PRIMARY KEY`)**.

Por ejemplo, podríamos decidir:

```
CREATE TABLE users (
    id INT PRIMARY KEY,
    email VARCHAR(100) UNIQUE
);
```

Aquí elegimos `id` como la Primary Key.

Pero `email` era también una **Candidate Key**.

---

### La relación entre los nombres

Puedes imaginarlo así:

```
                 SUPER KEYS
        ┌───────────────────────────┐
        │ {id}                       │
        │ {email}                    │
        │ {id, nombre}               │
        │ {id, email}                │
        │ {id, email, nombre}        │
        └───────────────────────────┘
                  │
                  │ eliminar
                  │ atributos innecesarios
                  ▼
             CANDIDATE KEYS
        ┌────────────────────┐
        │ {id}               │
        │ {email}            │
        └────────────────────┘
                  │
                  │ elegir una
                  ▼
             PRIMARY KEY
                {id}
```

Así que puedes recordarlo como:

> **Super Key = cualquier combinación que identifica.**  
> **Candidate Key = las Super Keys mínimas que podrían ser elegidas.**  
> **Primary Key = la Candidate Key que finalmente elegimos.**