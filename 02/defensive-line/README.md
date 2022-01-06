# Defensive Line

We begin by precomputing for each position $i$ in the defensive line, the length of the interval beginning at position $i$ such that the cumulative value of the defenders is $k$. We set this to $0$ if there is no such interval.

Then, we can setup the dynamic program to operate on the number of remaining attackers and remaining defenders. In each iteration, we determine whether to attack the interval beginning at the current defender $j$ (using one attacker), or to skip the defender and proceeding with defender $j - 1$.

Clearly, we have $\mathcal{O}(n \cdot m)$ overlapping subproblems, which is also the runtime of our algorithm.
