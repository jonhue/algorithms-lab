# Idefix and the Mansions of the Gods

* triangulations
* disjoint sets

We solve each of the two problems separately. We begin by constructing a triangulation of trees. We then construct a list of edges of the triangulation together with bones and their squared distances to the nearest vertex. While constructing this list, we use a disjoint set data structure to obtain the maximum number of bones that are covered by trees of radius up to $r$.

In the second step, we iterate through the sorted edges (& bones) and use a new disjoint set data structure to find the smallest radius such that at least $k$ bones can be collected.

As we are only iterating through the trees and bones once together, the runtime of our algorithm is $\mathcal{O}((n+m) \log n)$.
