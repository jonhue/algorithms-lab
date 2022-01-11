# Asterix the Gaul

* binary search
* split & list

To solve this problem, we do a binary search over all possible numbers of potion gulps (from $0$ to $m$). For a fixed amount of potion $k$, we then need to determine the maximum distance that can be traveled in less than $T$ time and check if this maximum distance is greater or equal to $D$. We cannot use a greedy approach to compute this distance, hence, we resort to a brute-force computation of all possible subsets of movements. To stay within the time limit we use the Split & List technique. That is, we split the movements into two subsets $A$ and $B$ of equal size and compute all subsets within either of them. Then, for all subsets of $A$, we perform a binary search on the subsets of $B$ to find the best possible choice of movements. As the number of movements is at most $30$, the time complexity of the algorithm is $\mathcal{O}((15 \cdot 2^{15}) \cdot \log m)$.
