# Kingdom Defence

* flows

We simply apply the standard techniques from the lecture. Each vertex has a given supply and demand. For each edge, we add the minimum capacity to the demand of the origin and to the supply of the endpoint. The edge capacity is $C - c$. Then, we compute the maximum flow. All requirements are satisified if and only if the maximum flow is equal to the sum of all demands (sum of the vertex-specific demands plus the sum of the minimum edge capacities).
