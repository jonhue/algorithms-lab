# Evolution

* depth-first search
* binary search

We traverse the tree using depth-first search which allows us to keep track of the path from the root to the current vertex. Then, for each query starting from the current vertex, we use binary search along the path from the root to find the desired species. Overall, the runtime of our algorithm is $\mathcal{O}((n + q) \log n)$ asusming the names of two species can be compared in constant time.
