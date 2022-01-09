# Buddy Selection

* two pointers
* maximum cardinality matching

To solve this problem one needs to overcome two challenges. First, how to efficiently construct a graph representing the shared characteristics between people. Second, how to use such a graph to check whether there is a better choice of buddies than the provided baseline.

## Efficiently constructing the graph

We begin by reading the characteristics of each vertex into a vector and sorting it.

Then, for each pair of vertices, we iterate through their (sorted) lists of characteristics once using two pointers to count the number of shared characteristics.

This can be done in $\mathcal{O}(n \cdot c \log c \cdot l + n^2 \cdot c \cdot l)$ time.

## Analyzing the graph

We subtract $f$ from the weight of each edge. Then we find a maximum cardinality matching. If this matching matches all vertices, then there is clearly a better choice of buddies than the baseline. If, on the other hand, this matching does not match all vertices, the provided baseline is already optimal.
