# Placing Knights

* maximum inependent set
* maximum cardinality matching

We construct the "threatening graph" where we connect positions with an edge if and only if knights at these positions threaten each other. Observe that this graph is bipartite as knights on a white square only threaten knights on black squares and vice versa. We are interested in the size of the maximum independent set which we know is the number of vertices minus the size of the minimum vertex cover. Moreover, we know that in a bipartite graph, the size of the minimum vertex cover is equal to the size of the largest matching.
