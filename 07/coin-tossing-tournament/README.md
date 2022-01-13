# Coin Tossing Tournament

* flows

We construct a graph with $n + m$ vertices. We supply each vertex representing a round with flow $1$ and add edges to the one or two potential winners of this round. Finally, we add a demand of the expected score to each vertex representing a player. If the maximu flow is equal to the sum of all scores, the scoreboard is possible. We additionally need to check that the sum of all scores is indeed equal to the number of rounds.
