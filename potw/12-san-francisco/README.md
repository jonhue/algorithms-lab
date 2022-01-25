# San Francisco

* dynamic programming (on number of moves and current position)

For up to $k$ moves, we iterate over each hole. For each hole we find the optimal predecessor (from one move earlier). As soon as we reach $x$ points or more, we return the current move.

The time complexity is $\mathcal{O}(n \cdot k)$.
