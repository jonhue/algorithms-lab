# Punch

* dynamic programming (on #encountered drinks and #liters)

This problem is similar to a Knapsack. For each #drinks encountered and #liters, we can either choose to use the current drink or can choose not to. We remember the minimum cost, number of used drinks, and whether the current drink has already been used.

The time complexity is given as $\mathcal{O}(n \cdot k)$.
