
### Recurencia 1
$T(n)=T(n-1)+1$

$\begin{equation} T(n) = \left\{ \begin{array}{ll} 1 & \quad \text{si } n = 0 \\ T(n-1) + 1 & \quad \text{si } x > 0 \end{array} \right. \end{equation}$

Se puede utilizar sustitución para obtener el resultado:
$T(n)=n+1$
$O(n)$

### Recurrencia 2

$T(n)=T(n-1)+n$

$\begin{equation} T(n) = \left\{ \begin{array}{ll} 1 & \quad \text{si } n = 0 \\ T(n-1) + n & \quad \text{si } x > 0 \end{array} \right. \end{equation}$

Se puede utilizar sustitución para obtener el resultado:
$T(n)=1 + \frac{n(n+1)}{2}$
$O(n²)$

### Recurrencia 3

$T(n)=T(n-1)+\log{n}$

$\begin{equation} T(n) = \left\{ \begin{array}{ll} 1 & \quad \text{si } n = 0 \\ T(n-1) +\log{n} & \quad \text{si } x > 0 \end{array} \right. \end{equation}$

Se puede utilizar sustitución para obtener el resultado:
$T(n)=1 + \log{n!}$
$O(n\log{n})$

### Recurrencia 4

$T(n)=T(n-1)+n²$

$\begin{equation} T(n) = \left\{ \begin{array}{ll} 1 & \quad \text{si } n = 0 \\ T(n-1) + n² & \quad \text{si } x > 0 \end{array} \right. \end{equation}$

Se puede utilizar sustitución para obtener el resultado:
$O(n³)$

### Recurrencia 5

$T(n)=2T(n-1)+1$

$\begin{equation} T(n) = \left\{ \begin{array}{ll} 1 & \quad \text{si } n = 0 \\ 2T(n-1)+1 & \quad \text{si } x > 0 \end{array} \right. \end{equation}$

Se puede utilizar sustitución para obtener el resultado:
$O(2^n)$

### Recurrencia 6

$T(n)=3T(n-1)+1$

$\begin{equation} T(n) = \left\{ \begin{array}{ll} 1 & \quad \text{si } n = 0 \\ 3T(n-1)+1 & \quad \text{si } x > 0 \end{array} \right. \end{equation}$

Se puede utilizar sustitución para obtener el resultado:
$O(3^n)$

### Recurrencia 7

$T(n)=2T(n-1)+n$

$\begin{equation} T(n) = \left\{ \begin{array}{ll} 1 & \quad \text{si } n = 0 \\ 2T(n-1)+n & \quad \text{si } x > 0 \end{array} \right. \end{equation}$

Se puede utilizar sustitución para obtener el resultado:
$O(n2^n)$


