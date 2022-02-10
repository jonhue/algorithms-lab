# Planet Express

* (strongly) connected components
* shortest paths

We begin by constructing the provided graph. Because we want to compute the distance between vertice $n - 1$ and all vertices from $0$ through $k - 1$, we insert edges in the reverse direction.

Next, we find all strongly connected components which can be done in $\mathcal{O}(n + m)$ time. For each strongly connected component, we add two vertices to represent transitions through the local teleportation network (this adds $\mathcal{O}(n)$ vertices).

Finally, we use Dijkstra's algorithm to compute the distances of the shortest paths from $n - 1$ to the vertices $0$ through $k - 1$. We return the shortest of these distances.

Overall, the algorithm runs in $\mathcal{O}(n \log n + m)$ time.
