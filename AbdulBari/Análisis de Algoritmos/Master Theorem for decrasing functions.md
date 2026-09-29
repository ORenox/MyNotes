$$T(n)=aT(n-b)+f(n)$$
$$a>0 \qquad  b>0 \qquad f(n)=O(n^k) \qquad k\geq 0$$$\text{if} \quad a=1 \quad \text{then} \quad O(n \cdot f(n))$
$\text{if} \quad a>1 \quad \text{then} \quad O(n^k \cdot a^{\frac{n}{b}})$
$\text{if} \quad a<1 \quad \text{then} \quad O(n^k )$