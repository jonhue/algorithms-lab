# Canteen

* cost flows

We construct a graph with $n$ vertices, one vertex for each day. Vertex $i$ has supply $a_i$ with cost $c_i$ and demand $s_i$ with cost $\max_{i'} p_{i'} - p'$. In addition, we add an edge from vertex $i$ to vertex $i + 1$ with capacity $v_i$ and cost $e_i$. The maximum flow corresponds to the maximum number of students we are able to serve. The profit is given as $f \cdot \max_{i'} p_{i'} - c$ where $f$ is the maximum flow and $c$ is the minimum cost.
