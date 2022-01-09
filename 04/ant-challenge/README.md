# Ant Challenge

* minimum spanning tree
* shortest paths

This problem is relatively simple. The idea ist to first construct $s$ private networks using Kruskal's algorithm, then combine all private networks into a single graph and use Dijkstra's algorithm to compute the distance between $a$ and $b$.
