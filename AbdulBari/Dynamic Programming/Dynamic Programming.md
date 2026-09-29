Muy aplicado en problemas de **optimización**

**Optimization problems** pueden tener muchas soluciones,  y yo quiero encontrar la solución más óptima, con el valor mínimo o máximo.

hay que diferenciar entre **an Optimal solution**, que es una de las soluciones óptimas, de **the Optimal solution** 

hay que seguir los siguientes 4 pasos:

1. Characterize the structure of an optimal solution 
2. Recursively define the value of an optimal solution
3. Compute the value of an optimal solution, typically in a bottom-up fashion
4. Construct an optimal solution from computed information

los pasos del 1 al 3 ya me dan una solución óptima "¿Cuál es el valor máximo/mínimo?", si quiero la solución por sí misma del problema "¿Qué decisiones producen ese máximo/mínimo?, debo usar el paso 4.


1. **¿Cuál es el valor óptimo?** → por ejemplo, el máximo beneficio = `42`.
2. **¿Cuál es la solución que produce ese valor?** → por ejemplo, elegir los elementos `{2, 5, 7}`.

La estructura de datos que necesitas depende justamente de **qué quieres recuperar**.


# Bottom-up vs Top-down

Esto es otra cosa que conviene separar.

Son dos maneras de **calcular la tabla DP**.

## Bottom-up

Literalmente:

> de abajo hacia arriba.

Primero resuelves los casos pequeños:

```
dp[0]
dp[1]
dp[2]
dp[3]
...
dp[n]
```

Por ejemplo Fibonacci:

```
function fib(n) {
    const dp = [0, 1];

    for (let i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[n];
}
```

La dirección es:

```
casos pequeños
      ↓
      ↓
      ↓
caso grande
```

Esto es **bottom-up**.

---

# 8. Top-down

Top-down comienza preguntando:

> "Necesito resolver `fib(10)`."

Para resolverlo:

```
fib(10)
   ↓
fib(9) + fib(8)
   ↓
fib(8), fib(7), ...
```

Pero guardamos los resultados que ya calculamos.

Eso se llama **memoization**.

```
function fib(n, memo = {}) {
    if (n <= 1) return n;

    if (memo[n] !== undefined) {
        return memo[n];
    }

    memo[n] = fib(n - 1, memo) + fib(n - 2, memo);

    return memo[n];
}
```

La dirección conceptual es:

```
problema grande
      ↓
subproblemas
      ↓
casos pequeños
```

Eso es **top-down**.

# La diferencia fundamental

Puedes memorizarlo así:

||Top-down|Bottom-up|
|---|---|---|
|Idea|Empiezo por el problema grande|Empiezo por casos pequeños|
|Técnica|Recursión + memoization|Iteración + tabla|
|Calcula|Solo estados necesarios|Normalmente todos los estados|
|Estructura|`memo`|`dp`|
|Riesgo|Profundidad de recursión|Mayor uso de tabla|
|Reconstrucción|Puede hacerse|Puede hacerse|

---

