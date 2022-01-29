# On Her Majesty's Secret Service

* shortest paths
* binary search
* maximum cardinality matching

We begin by constructing a directed weighted graph of all positions, slopes and lifts. We duplicate each shelter $c$ many times and store it with its entrance delay $j * d$ where $j \in [1,c]$ is the copy number.

Next, we compute for each agent its shortest path to all of the shelters. This can be done in $\mathcal{O}(a \cdot s \cdot (n \log n + m))$ time.

Finally, we do a binary search over all non-negative integers. In each iteration, we construct a matching graph of all agents and all shelters. We add an edge for each pair whose distance is less than $m$. Now, if we can find a matching of size $a$, we know that everyone can be evacuated. The binary sarch completes in $\mathcal{O}(a \cdot s \cdot \log \mathrm{MAX\_INT})$ time.
