# Real Estate Market

* cost flows

This problem is relatively simple. We construct the graph as follows. We have $N + M + S$ vertices. Each buyer vertice has supply $1$. From each buyer we add an edge to each of the sites with capacity $1$ and cost $\max_{i',j'} b_{i',j'} - b_{i,j}$. From each site we add an edge to the corresponding state with capacity one. From state $i$ we add an edge to the target with capacity $l_i$. The final profit is given as $f \max_{i',j'} b_{i',j'} - c$ where $c$ is the minimum cost. Note that this construction ensures that edge weights are non-negative.
