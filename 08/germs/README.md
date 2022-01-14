# Germs

* triangulations

We begin by constructing a triangulation of the bacteria. Then, for each bacterium, we find the smallest radius such that it will die (either by touching its closest bacterium or the boundary of the dish). We store these radii in a vector. Then we sort the vector and return the $0$-th, $\lfloor n / 2 \rfloor$-th, and $n - 1$-st elements. The runtime fo our algorithm is $\mathcal{O}(n \log n)$.
