# Bonus Level

* dynamic programming (on position of one agent, and vertical distance of the other agent)

The key idea is that we can equivalently go with two agents from position $(0,0)$ to position $(n-1,n-1)$ simultaneously. W.l.o.g. we assume that the second agent is always to the "right" of the first agent. Observe that given the position $(i_1,j_1)$ of the first agent and the vertical distance $d_v$ between the two agents, we have

$$
i_2 = i_1 - v_d, \\
j_2 = j_1 + v_d.
$$

From each position, we have four options (down, down), (down, right), (right, down), and (right, right).

The algorithm has time complexity $\mathcal{O}(n^3)$.
