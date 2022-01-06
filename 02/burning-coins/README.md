# Burning Coins

* dynamic programming (on subsequences of coins)

In this problem, we clearly have many overlapping supbroblems, hence, we use dynamic programming. For any subsequence of coins starting with coin $i$ and ending with coin $j$, the guaranteed amount we win from this subsequence is fixed. This is because we can use the number of taken coins to deduce whose turn it is. In our turn, we maximize our return, while in our opponents turn, they minimize our return.

Due to the subproblem structure our algorithm has a time complexity of $\mathcal{O}(n^2)$.
