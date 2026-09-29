Insertion Sort

Enunciado del Problema

Sea \(\alpha \) una fracción en el rango \(0 < \alpha < 1\). Demuestre cómo generalizar el argumento de la cota inferior para el ordenamiento por inserción (_Insertion Sort_) utilizando esta fracción. Especifique qué restricciones adicionales deben aplicarse sobre \(\alpha \) para que el argumento sea válido y determine qué valor de \(\alpha \) maximiza el número de operaciones en la demostración.

---

1. Construcción del Peor Caso y Generalización

Para demostrar matemáticamente la cota inferior \(\Omega(n^2)\) de _Insertion Sort_, diseñamos una configuración del arreglo de tamaño \(n\) que maximice el trabajo obligatorio del algoritmo:

1. **Partición del arreglo:** Dividimos el arreglo en tres regiones consecutivas basándonos en la fracción \(\alpha \):
    - **Región Inicial (A):** Las primeras \(\alpha n\) posiciones del arreglo.
    
    - **Región Intermedia (B):** Las siguientes \((1 - 2\alpha)n\) posiciones.
    - **Región Final (C):** Las últimas \(\alpha n\) posiciones restantes.
2. **Distribución de los elementos:** Colocamos a propósito los \(\alpha n\) elementos **más grandes** de todo el arreglo en la **Región Inicial (A)**. El resto de los elementos se distribuyen en las regiones B y C.
3. **Conexión con las Inversiones y Movimientos:**
    - Una inversión ocurre cuando un elemento mayor aparece antes que uno menor (\(i < j\) pero \(A[i] > A[j]\)).
    - Cada uno de los \(\alpha n\) elementos grandes de la Región A es estrictamente mayor que cualquiera de los \((1 - 2\alpha)n\) elementos que se encuentran en la Región Intermedia B.
    - Dado que _Insertion Sort_ avanza arrastrando cada elemento mediante intercambios de vecinos adyacentes, y cada intercambio elimina exactamente **una inversión**, cada uno de los elementos de la Región A debe cruzar obligatoriamente toda la Región B para llegar a su posición ordenada final (en el extremo derecho).
4. **Conteo de Operaciones Totales (\(T(n)\)):**  
    El número total de operaciones (comparaciones/intercambios) estará acotado inferiormente por el producto de la cantidad de elementos grandes y la distancia mínima que deben recorrer:  
    \(T(n)\ge (\text{Elementos\ en\ A})\times (\text{Longitud\ de\ B})\)  
    \(T(n)\ge (\alpha n)\cdot ((1-2\alpha )n)=\alpha (1-2\alpha )n^{2}\)

Como \(\alpha(1 - 2\alpha)\) es una constante independiente de \(n\), se demuestra formalmente que el tiempo de ejecución en el peor caso es de **\(\Omega(n^2)\)**.

---

2. Restricciones Adicionales sobre \(\alpha \)

Para que este argumento matemático sea estrictamente válido en la práctica, \(\alpha \) debe cumplir con dos condiciones:

1. **Restricción de Enteros:** El valor \(\alpha n\) debe resultar en un número entero, ya que representa un índice físico y una cantidad exacta de elementos dentro del arreglo.
2. **Restricción del Rango Geométrico:** La longitud de la región intermedia B, dada por \((1 - 2\alpha)n\), no puede ser vacía ni negativa. Por lo tanto:  
    \(1-2\alpha >0\implies 1>2\alpha \implies \alpha <\frac{1}{2}\)  
    Combinándolo con la premisa inicial, el rango real y válido para el argumento es **\(0 < \alpha < \frac{1}{2}\)**.

---

3. Maximización de la Cota Inferior (Optimización)

Para encontrar qué fracción \(\alpha \) ofrece la demostración con la cota inferior más pesada (el mayor número de operaciones intermedias), maximizamos la función que acompaña a \(n^{2}\):

Sea la función de eficiencia:  
\(f(\alpha )=\alpha (1-2\alpha )=\alpha -2\alpha ^{2}\)

1. **Primera Derivada:** Derivamos \(f(\alpha)\) respecto a \(\alpha \) para localizar los puntos críticos:  
    \(f^{\prime }(\alpha )=\frac{d}{d\alpha }(\alpha -2\alpha ^{2})=1-4\alpha \)
2. **Cálculo del Punto Crítico:** Igualamos la primera derivada a cero:  
    \(1-4\alpha =0\implies 4\alpha =1\implies \alpha =\frac{1}{4}\)
3. **Prueba de la Segunda Derivada:** Validamos si es un máximo calculando la segunda derivada:  
    \(f^{\prime \prime }(\alpha )=\frac{d}{d\alpha }(1-4\alpha )=-4\)  
    Como \(f''(\alpha) = -4 < 0\), la función es cóncava hacia abajo, confirmando que **\(\alpha = \frac{1}{4}\) (o \(0.25\))** es el máximo absoluto.

Conclusión del ejercicio

Al sustituir el valor óptimo \(\alpha = \frac{1}{4}\) en nuestra ecuación de operaciones, obtenemos:  
\(T(n)\ge \frac{1}{4}\left(1-2\left(\frac{1}{4}\right)\right)n^{2}=\frac{1}{4}\left(\frac{1}{2}\right)n^{2}=\frac{1}{8}n^{2}\)  
El argumento generalizado óptimo demuestra que _Insertion Sort_ requiere, en el peor de los casos, al menos **\(\frac{1}{8}n^2\) operaciones**, manteniendo su comportamiento cuadrático.

---

Si necesitas presentar este ejercicio en algún formato académico en particular, puedo ayudarte a adaptarlo. Si estás estudiando para un examen, ¿te gustaría probar con un **problema similar sobre cotas inferiores** en algoritmos de ordenamiento para practicar?