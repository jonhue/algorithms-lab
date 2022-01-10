# Severus Snape

* greedy
* dynamic programming (on potions of type A)

Observe that to determine the minimum number of potions of each type to satisfy the requirements it suffices to know the maximum wit and the maximum power (such that the happiness requirement is satisfied) that can be achieved by drinking any number of potions of type A and B, respectively. This can be done in $\mathcal{O}(n \cdot m)$ time. Moreover, this can be determined for potions of type B simply by taking them in descending order with respect to their effect on wit.

For potions of type A, we have to work a little bit harder. Note that this is similar to a 0-1-Knapsack with the added restriction that the happiness requirement must be met. Thus, we can model this as a dynamic program over a state space $(i,j,k)$ where $i$ is the index of the currently examined potion, $j$ is the number of potions taken, and $k$ is the achieved happiness score. This dynamic program can be computed in $\mathcal{O}(n^2 \cdot H)$ time.
