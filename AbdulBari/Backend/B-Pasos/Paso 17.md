coverage con `pytest-cov`
## Instalar `pytest-cov`

Ejecuta:

```python
python -m pip install pytest-cov
```

Y actualiza:

```python
python -m pip freeze > requirements.txt
```

## Ejecutar coverage

Desde la raíz del proyecto:

```python
pytest --cov=apps --cov-report=term-missing
```

Esto hace dos cosas:

```
pytest
  │
  ├── ejecuta tus tests
  │
  └── mide qué código de apps/ fue ejecutado
```

`--cov-report=term-missing` además nos indica **qué líneas no fueron ejecutadas por ningún test**.

Podrías ver algo parecido a:

```
Name                              Stmts   Miss  Cover   Missing
----------------------------------------------------------------
apps/machines/models.py              15      2    87%   25-26
apps/machines/views.py               12      1    92%   18
apps/measurements/models.py          10      0   100%
apps/measurements/serializers.py    20      2    90%   31-32
----------------------------------------------------------------
TOTAL                                57      5    91%
```

Los números exactos dependerán de tus tests.

### ¿Qué significa?

Por ejemplo:

```
Cover = 90%
```

significa aproximadamente que el 90% de las líneas consideradas fueron ejecutadas durante los tests.

Pero ojo:

> **90% de coverage no significa que tu código tenga 90% de calidad.**

Podrías tener:

```
def dividir(a, b):
    return a / b
```

y conseguir coverage alto sin probar:

```
dividir(10, 2)  → funciona
dividir(10, 0)  → ¿qué ocurre?
```

Por eso coverage es una **métrica de ayuda**, no el objetivo final.


## Ahora mira especialmente `Missing`

Ejecuta:

```
pytest --cov=apps --cov-report=term-missing
```

y fíjate en:

```
Missing
```

Por ejemplo, si aparece:

```
apps/measurements/serializers.py   ...   28-30
```

significa que existen líneas de ese serializer que **ningún test ha ejecutado todavía**.

No vamos a perseguir automáticamente el `100%`.

Primero preguntamos:

> "¿Qué comportamiento importante todavía no estoy probando?"

Ese es el enfoque correcto para SDET.


## Generar reporte HTML

También puedes generar un reporte visual:

```python
pytest --cov=apps --cov-report=html
```

Esto crea:

```
htmlcov/
```

y dentro encontrarás:

```
htmlcov/
└── index.html
```

Como `htmlcov/` es un artefacto generado, agrégalo a `.gitignore`:

```
# Coverage
htmlcov/
.coverage
```

No queremos subir estos archivos al repositorio.

## Ejecuta finalmente toda la suite

Primero:

```python
pytest -v
```

Después:

```python
pytest --cov=apps --cov-report=term-missing
```

