# The Iron Islands

* sliding window
* dynamic programming (on number of men needed to conquer a maximum number of islands)

Observe that a valid plan may either consist of neighboring islands from only a single waterway or from neighboring islands of two waterways joined at vertex $0$ (Pike).

To compute the maximum number of islands that can be conquered on a single waterway we can use the standard sliding window technique.

For the joined waterways, we iterate over all waterways. We use a dynamic program that memoizes the maximum number of islands (among all _previous_ waterways) that can be conquered using $j$ men. Now we can first check if we can find a sequence of islands which together with our memory forms a valid plan. Then, we update our memory to include the current waterway.

The complexity of our algorithm is $\mathcal{O}(k + n)$ as each island is considered only a constant number of times.
