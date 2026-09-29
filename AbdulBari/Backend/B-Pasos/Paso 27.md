
Ya tenemos la parte fundamental funcionando. Ahora vamos a mejorar la pipeline con **coverage** y una comprobación de que nuestro proyecto también puede construirse como imagen Docker.

## Integrar Coverage en CI

Ya instalaste `pytest-cov` y localmente puedes ejecutar:

```
pytest --cov=apps --cov-report=term-missing
```

Ahora queremos que **GitHub Actions haga lo mismo automáticamente**.

### 1. Modifica el último step

Actualmente tienes:

```
- name: Run tests
  run: |
    pytest -v
```

Cámbialo por:

```
- name: Run tests with coverage
  run: |
    pytest -v --cov=apps --cov-report=term-missing
```

La parte final de tu workflow quedaría:

```
- name: Run django checks
  run: |
    python manage.py check

- name: Run migrations
  run: python manage.py migrate

- name: Run tests with coverage
  run: |
    pytest -v --cov=apps --cov-report=term-missing
```

## Hacer que CI compruebe Docker

Esto es especialmente útil porque nuestro proyecto ya está dockerizado.

Actualmente CI comprueba:

```
Código Django
    ↓
Dependencias
    ↓
PostgreSQL
    ↓
Migrations
    ↓
Tests
```

Podemos añadir:

```
Código
   ↓
Docker build
   ↓
¿La imagen se puede construir?
```

Agrega al final de `steps`:

```
- name: Build Docker image
  run: docker build -t industrial-monitoring-api .
```

Tu workflow terminaría así:

```
- name: Run tests with coverage
  run: |
    pytest -v --cov=apps --cov-report=term-missing

- name: Build Docker image
  run: docker build -t industrial-monitoring-api .
```

### ¿Por qué esto es útil?

Imagina que mañana modificas:

```
COPY requirements.txt .
RUN pip install -r requirements.txt
```

y cometes un error.

Tus tests Python podrían seguir pasando, pero:

```
docker build .
```

podría fallar.

Con esta etapa, GitHub te lo detecta automáticamente.