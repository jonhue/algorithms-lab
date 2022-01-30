# India

* flows
* cost flows
* binary search

We construct a flow graph with a new source and target $a$. We connect the source to the start city $k$ using edge $e$.

Now, we use binary search from $l = 0$ to $r = \min \{in, out\}$ to find the largest flow we can transport without exceeding the budget. $in$ and $out$ are the outgoing and incoming edge capacities of $k$ and $a$, respectively. In each iteration, we compute the min cost max flow. If the flow is smaller than the current iterations value, we update the right solution boundary. For the final update we consider whether the cost exceeds the budget.
