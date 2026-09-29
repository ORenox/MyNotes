Tendríamos como mínimo dos containers:

```python
┌──────────────────────┐
│       Django         │
│      Container       │
└──────────┬───────────┘
           │
           │
┌──────────▼───────────┐
│     PostgreSQL       │
│      Container       │
└──────────────────────┘
```

`docker-compose.yml`:

```d
services:

  web:
    build: .
    ports:
      - "8000:8000"
    depends_on:
      - db

  db:
    image: postgres:17
    environment:
      POSTGRES_DB: industrial_db
      POSTGRES_USER: postgres
      POSTGRES_PASSWORD: postgres
```

Entonces:

```d
docker compose up
```

y tienes toda la aplicación levantada.