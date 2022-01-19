# Asterix and the Chariot Race

* greedy
* depth-first search

Observe that the problem exhibits a tree structure. Every city is reachable from city $0$ (the root) and we have $n - 1$ edges. Moreover, note that any particular city exhibits one of three states: either it is repaired, or it is covered by one of its successors, or it is covered (rather waiting to be covered) by one of its predecessors.

We can therefore compute the minimum cost for each city and each of these states recursively using depth-first search. The final result is the minimum of the cost for city $0$ to be either covered by its successors or repaired itself. The resulting runtime is linear.
