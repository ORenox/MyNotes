## Agregar PostgreSQL como servicio

En `.github/workflows/ci.yml`, dentro del job `test`, agrega `services:` antes de `steps:`:

```d
jobs:
  test:
    runs-on: ubuntu-latest

    services:
      postgres:
        image: postgres:17

        env:
          POSTGRES_DB: industrial_monitoring
          POSTGRES_USER: django
          POSTGRES_PASSWORD: django_password

        ports:
          - 5432:5432

        options: >-
          --health-cmd="pg_isready -U django -d industrial_monitoring"
          --health-interval=5s
          --health-timeout=5s
          --health-retries=5
```

Fíjate en que esto se parece muchísimo a nuestro `docker-compose.yml`.

En local tenemos:

```
Docker Compose
├── web
└── db → PostgreSQL
```

En CI tendremos:

```
GitHub Actions
├── Runner Ubuntu
│   └── Django + pytest
│
└── PostgreSQL service
```

Aquí Django no está dentro de un contenedor. Está directamente en el runner de GitHub.

Por eso:

```
POSTGRES_HOST: localhost
```

es correcto en este escenario.

## ¿Por qué ejecutar `migrate` si pytest crea su DB?

Buena distinción.

Con:

```
@pytest.mark.django_db
```

`pytest-django` gestiona una base de datos de testing para los tests que necesitan DB.

Entonces `migrate` no es estrictamente necesario **solo para que esos tests funcionen**.

Pero aquí también nos sirve como comprobación de CI:

```
¿El proyecto puede aplicar sus migraciones
desde cero sobre PostgreSQL?
              │
         ┌────┴────┐
         ▼         ▼
        Sí         No
         │          │
         ✓          ✗ CI falla
```

Eso es valioso en un backend.

## ¿Estamos exponiendo una contraseña?

Tenemos:

```
POSTGRES_PASSWORD: django_password
```

pero esto es una credencial **exclusiva del entorno efímero de testing**.

No estamos poniendo aquí:

```
❌ contraseña de producción
❌ contraseña personal
❌ SECRET_KEY real
❌ contenido de .env
```

El PostgreSQL que GitHub crea existe durante el job y después desaparece.

Para secretos reales usaríamos GitHub Secrets, algo que veremos después.


## ¿Qué va a pasar cuando hagamos push?

Ahora el flujo completo será:

```
Tu computadora
      │
   git push
      │
      ▼
    GitHub
      │
      ▼
GitHub Actions
      │
      ├── crea Ubuntu
      │
      ├── inicia PostgreSQL 17
      │
      ├── espera healthcheck
      │
      ├── checkout
      │
      ├── instala Python 3.13
      │
      ├── instala requirements.txt
      │
      ├── manage.py check
      │
      ├── manage.py migrate
      │
      └── pytest
             │
        ┌────┴────┐
        ▼         ▼
       PASS      FAIL
        ✓          ✗
```

Eso ya es **Continuous Integration**.

## Luego hacemos el commit

Si el staging está limpio:

```
git commit -m "chore: containerize application and add CI workflow"
```

Este mensaje tiene sentido porque estamos introduciendo dos bloques:

```
Docker
  +
GitHub Actions
```