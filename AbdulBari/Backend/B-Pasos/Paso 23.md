## El problema: el contenedor no es la base de datos

Tenemos:

```
Docker
│
├── web
│   └── Django
│
└── db
    └── PostgreSQL
```

Es tentador pensar:

> "Mi PostgreSQL está dentro del contenedor `db`."

Pero conceptualmente debemos separar:

```
Contenedor PostgreSQL
        │
        ▼
Proceso PostgreSQL

Volumen PostgreSQL
        │
        ▼
Datos reales
```

El contenedor puede desaparecer y podemos crear otro.

Los datos deberían sobrevivir.

# Nuestro volumen

En `docker-compose.yml` tenemos:

```d
volumes:
  postgres_data:
```

y:

```d
services:
  db:
    volumes:
      - postgres_data:/var/lib/postgresql/data
```

Esto significa:

```
                 Docker
                   │
        ┌──────────┴──────────┐
        │                     │
        ▼                     ▼
      db container       postgres_data
        │                     │
        │    mount            │
        └─────────────────────┘
              │
              ▼
      /var/lib/postgresql/data
```

PostgreSQL guarda sus datos en:

```d
/var/lib/postgresql/data
```

y nosotros estamos haciendo que ese directorio sea persistente mediante `postgres_data`.

# `docker compose down`

Supongamos que tienes datos:

```
Machine
CNC-001
CNC-002
```

Ahora ejecutas:

```
docker compose down
```

El contenedor desaparece:

```
db container
     ❌
```

pero el volumen permanece:

```
postgres_data
     ✅
```

Entonces haces:

```
docker compose up
```

Docker crea un nuevo contenedor:

```
nuevo db container
       │
       ▼
postgres_data existente
       │
       ▼
tus datos siguen ahí
```

**Esta es precisamente la ventaja del volumen.**

# Vamos a comprobarlo

Primero asegúrate de que Docker está funcionando:

```d
docker compose ps
```

Después entra al shell de Django:

```
docker compose exec web python manage.py shell
```

Crea una máquina:

```
from apps.machines.models import Machine

Machine.objects.create(
    name="PERSISTENCE-TEST",
    model="Docker Test",
    location="Factory Docker",
)
```

Comprueba:

```
Machine.objects.filter(
    name="PERSISTENCE-TEST"
).exists()
```

Debe devolver:

```
True
```

Sal:

```
exit()
```

# Ahora destruye los contenedores

```
docker compose down
```

Y vuelve a levantarlos:

```
docker compose up
```

Después:

```
docker compose exec web python manage.py shell
```

Y:

```
from apps.machines.models import Machine

Machine.objects.filter(
    name="PERSISTENCE-TEST"
).exists()
```

Debe seguir devolviendo:

```
True
```

Eso demuestra:

```
contenedor eliminado
       ↓
contenedor nuevo
       ↓
volumen conservado
       ↓
datos conservados
```

# ¿Qué pasa si elimino el volumen?

Aquí viene el comando peligroso:

```
docker compose down -v
```

La opción:

```
-v
```

significa que también queremos eliminar los volúmenes asociados.

Entonces:

```
docker compose down
       ↓
contenedores eliminados
volumen → conserva datos
```

pero:

```
docker compose down -v
       ↓
contenedores eliminados
volumen → eliminado
       ↓
datos PostgreSQL → perdidos
```

⚠️ **No ejecutes `docker compose down -v` en tu proyecto ahora**, porque perderíamos la base de datos actual.

# ¿Por qué esto importa en un proyecto real?

Porque normalmente queremos:

```
Código
   │
   ▼
Contenedor Django
   │
   │
   ▼
PostgreSQL
   │
   ▼
Volumen persistente
```

El contenedor puede ser reemplazado muchas veces:

```
db v1 ❌
   ↓
db v2 ❌
   ↓
db v3 ✅
```

pero:

```
postgres_data
      │
      ├── datos
      ├── tablas
      ├── registros
      └── migraciones
```

permanece.

# Pero hay una distinción fundamental

Un volumen **no es un backup**.

Esto:

```
postgres_data
```

te protege principalmente contra problemas como:

- recrear el contenedor;
- actualizar la imagen;
- detener/iniciar Docker;
- reemplazar el contenedor.

Pero si el volumen se corrompe, se elimina accidentalmente o falla el almacenamiento, puedes perder los datos.

En producción necesitamos además:

```
PostgreSQL
    │
    ├── volumen
    │
    └── backups
```

Los backups los veremos cuando lleguemos a despliegue.

# Con esto cerramos Docker Compose

Tu arquitectura ahora es:

```
                     Tu PC
                       │
                docker compose up
                       │
        ┌──────────────┴──────────────┐
        │                             │
        ▼                             ▼
   Django container            PostgreSQL container
        │                             │
        │                             ▼
        │                       postgres_data
        │
        ▼
     API :8000
```

Y tenemos:

- ✅ Dockerfile
- ✅ Docker image
- ✅ Docker Compose
- ✅ Django container
- ✅ PostgreSQL container
- ✅ comunicación entre servicios
- ✅ `.env.docker`
- ✅ `.dockerignore`
- ✅ PostgreSQL healthcheck
- ✅ `depends_on` con `service_healthy`
- ✅ migraciones automáticas
- ✅ volumen persistente
- ✅ tests ejecutables dentro del contenedor