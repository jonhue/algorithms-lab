# Rubeus Hagrid

* depth-first search
* greedy

Note that the chamber network has a tree structure. Using depth-first search we compute for each subtree

* the number of vertices $m$;
* the number of galleons lost after exploring it $g$; and
* the time it takes to explore the entire subtree $t$.

It is optimal to choose the next subtree to explore by minimizing the greedy criterion,

$$\frac{2 l + t}{m}.$$

Next, we recursively compute the quantities of the sub-tree with the current node as root,

$$
m = m + m_S \\
g = (l + t) \cdot m_S + g_S \\
t = 2 l + t_S.
$$

After obtaining the result for the root node $0$, we simply return the difference between the total number of galleons and $g$.
