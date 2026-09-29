![[Pasted image 20260904093104.png]]
![[Pasted image 20260904093142.png]]
![[Pasted image 20260904093210.png]]
![[Pasted image 20260904093222.png]]
## 1. Uno a uno (1:1)

Un registro de una tabla se relaciona con **un solo registro** de otra tabla.

### Ejemplo: Persona — Pasaporte

```
PERSONA  ────────  PASAPORTE
   1                  1
```

- Una persona tiene un pasaporte.
- Un pasaporte pertenece a una persona.

## 2. Uno a muchos (1:N)

Un registro puede relacionarse con **muchos registros** de otra entidad.

### Ejemplo: Cliente — Pedido

```
CLIENTE  ────────<  PEDIDO
    1                N
```

- Un cliente puede realizar muchos pedidos.
- Cada pedido pertenece a un solo cliente.

Por ejemplo:

```
Cliente: Renato
├── Pedido #001
├── Pedido #002
└── Pedido #003
```

# 4. Muchos a muchos (N:M)

Muchos registros de una entidad pueden relacionarse con muchos registros de otra.

### Ejemplo: Estudiante — Materia

```
ESTUDIANTE  >────<  MATERIA
     N             M
```

- Un estudiante puede cursar muchas materias.
- Una materia puede tener muchos estudiantes.

Por ejemplo:

```
Renato ─── Programación
       ├── Bases de Datos
       └── Matemáticas

Programación ─── Renato
              ├── María
              └── Juan
```