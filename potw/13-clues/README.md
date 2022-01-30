# Clues

* triangulations
* bipartite
* connected components

We begin by constructing a triangulation of stations. Then we construct a graph where each overlapping stations are connected. This can be done by iterating over each vertice of the triangulation and then looping over all neighbors and the neighbors of all neighbors! This is necessary because two stations could overlap without sharing a direct edge in the triangulation!

Next, to check whether the network can operate without interferences, we need to check if there is a 2-coloring of the vertices. This is equivalent to checking if the graph is bipartite.

Finally, we compute the connected components and loop through all clues. A cloue can be communicated if the two points can communicate directly or if the two points are close enough to the nearest vertex and those vertices are in the same connected component.

The time complexity is $\mathcal{O}(n \log n + m)$.
