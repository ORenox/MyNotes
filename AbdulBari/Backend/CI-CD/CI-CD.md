GitHub Actions.

Cada vez que hagas:

```
git push
```

GitHub podría ejecutar:

```
git push
   ↓
GitHub Actions
   ↓
Install dependencies
   ↓
Run migrations
   ↓
Run pytest
   ↓
Build Docker image
   ↓
Quality Gate
```

Por ejemplo:

```
- name: Run tests
  run: pytest
```

Si falla un test:

```
❌ CI FAILED
```

Si todo funciona:

```
✅ CI PASSED
```

Esto conecta muy bien con lo que estabas estudiando de **CI execution y quality gates**.