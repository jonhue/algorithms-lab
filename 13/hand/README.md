# Hand

* triangulations
* disjoint sets

We begin by constructing a triangulation of tents. Then we iterate over all edges sorted by their length (ascending).

We a disjoint-sets data structure to track the "components" of tents that are connected and can only be taken by a single family.
We store for each component the number of tents it contains.
We also store the number of components of a certain size (up to $k$). All components with size larger than $k$ are simply counted as components of size $k$.

Note that at any time, the number of families that can live in the tents is given by the number of components of size $k$ (if they all live together) plus additional terms for scattering between components of smaller size than $k$.
