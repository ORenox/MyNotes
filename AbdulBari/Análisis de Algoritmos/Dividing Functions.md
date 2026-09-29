### Recurrencia 1
$T(n)=T\left( \frac{n}{2} \right)+1$
$\begin{equation} T(n) = \left\{ \begin{array}{ll} 1 & \quad \text{si } n = 1 \\ T\left( \frac{n}{2} \right)+1 & \quad \text{si } x > 1 \end{array} \right. \end{equation}$

Se puede utilizar sustitución para obtener el resultado:
$T(n)=1+\log_{2}{n}$
$O(\log{n})$

### Recurrencia 2
$T(n)=T\left( \frac{n}{2} \right)+n$
$\begin{equation} T(n) = \left\{ \begin{array}{ll} 1 & \quad \text{si } n = 1 \\ T\left( \frac{n}{2} \right)+n & \quad \text{si } x > 1 \end{array} \right. \end{equation}$

aqui pasa que $\sum_{i=0}^{k}{\frac{1}{2^{i}}}$ va a dar uno, es la sumatoria de partes de un circulo, empiezo la mita, la cuarta parte, la octava parte .... al final su sumatoria completa un circulo entero o un entero = 1:
$T(n)=1+2\cdot n$
$O(n)$

### Recurrencia 3
$T(n)=2T\left( \frac{n}{2} \right)+n$
$\begin{equation} T(n) = \left\{ \begin{array}{ll} 1 & \quad \text{si } n = 1 \\ 2T\left( \frac{n}{2} \right) + n & \quad \text{si } x > 1 \end{array} \right. \end{equation}$

Se puede utilizar sustitución para obtener el resultado:
$T(n)=n+n\cdot \log{n}$
$O(n\cdot \log{n})$


