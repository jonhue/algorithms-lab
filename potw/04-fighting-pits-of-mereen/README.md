# Fighting Pits of Mereen

* dynamic programming

The key to solving this problem is finding a good characterization of the overlapping subproblems. Observe that for any number of taken fighters, difference $p - q$, and histories for each gate of length $m - 1$, the excitement of the next round can be computed in constant time (for both choices -- sending to the north and south gate). Note that the difference $|p - q|$ can be at most $10$, otherwise the excitement of a round will always be negative. Thus, beginning from the state $(0, 0, \emptyset, \emptyset)$, we can iteratively compute the value of all states, maximizing the excitement.

The time complexity of the resulting algorithm is $\mathcal{O}(n \cdot 21 \cdot ((m - 1) \cdot k)^2)$.
