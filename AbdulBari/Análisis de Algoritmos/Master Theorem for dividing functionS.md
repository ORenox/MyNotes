$$T(n)=a\cdot T\left( \frac{n}{b} \right) + f(n) $$
$$a\geq 1 \qquad b >1 $$
$$f(n)=\Theta(n^k\cdot \log^p{n})$$
$$\begin{align*}
    \text{if } \log_b a > k &\quad \text{then } \quad T(n) = \Theta\left(n^{\log_b a}\right) \\[1ex]
    \text{if } \log_b a = k &\quad \text{then } \quad \begin{cases} 
        \Theta\left(n^k \cdot \log^{p+1} n\right) & \text{si } p > -1 \\ 
        \Theta\left(n^k \cdot \log \log n\right) & \text{si } p = -1 \\ 
        \Theta\left(n^k\right) & \text{si } p < -1 
    \end{cases} \\[1ex]
    \text{if } \log_b a < k &\quad \text{then } \quad \begin{cases} 
        \Theta\left(n^k \cdot \log^p n\right) & \text{si } p \geq 0 \\ 
        \Theta\left(n^k\right) & \text{si } p < 0 
    \end{cases}
\end{align*}

$$