# Return of the Jedi

* minimum spanning tree
* disjoint sets

We begin by computing the minimum spanning tree of the given graph. Then, for each edge in the MST, we compute another MST ignoring that edge. The result is the minimum cost among all the MSTs ignoring one edge.

Computing an MST takes $\mathcal{O}(m \log m)$ time. Thus, the runtime of our algorithm is $\mathcal{O}(n m \log m)$.
