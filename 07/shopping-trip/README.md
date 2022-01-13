# Shopping Trip

* flows

We model the map as a graph where streets can be used in either direction with capacity $1$. We add a supply of $s$ to vertex $0$ and demand of $1$ to each of the store vertices. Then, we simply check if the maximum flow is equal to $s$.
