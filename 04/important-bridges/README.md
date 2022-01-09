# Important Bridges

* biconnected components

This problem is very similar to finding the articulation points of a graph, only that we are not interested in critical vertices but in critical edges. Observe that an edge is critical if and only if its biconnected component consists only of this one edge.

We first construct the biconnected components and then count the number of edges they contain. This takes $\mathcal{O}(n + m)$ time.
