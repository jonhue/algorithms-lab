# Lannister

* linear programming

This problem is not particularly difficult, although it requires quite some time for modeling.

We are given a collection of $n$ noble houses with positions $(x_i^N,y_i^N)$ and $m$ common houses with positions $(x_j^C,y_j^C)$. We are to find the optimal positions of two perpendicular canals (lines), one for fresh water and one for sewage. Using [GeoGebra](https://www.geogebra.org/calculator) it is fairly easy t figure out that we can encode these lines using three variables $B, C, D$. For the sewage canal, this yields

$x + By + C = 0$

and for the fresh water canal

$Bx - y + D = 0.$

This way, we already ensure that the sewage canal is non-horizontal and the fresh water canal is non-vertical.

We need one additional variable $L \geq 0$ to denote the length of the longest fresh water pipe which we will minimize.

## Constraints

### Cersei

For Cersei's constraint, we need to ensure that the noble and common houses are linearly separable (by the sewage canal). For this we simply add the following constraints:

$$x_i^N + B y_i^N + C \leq 0 \quad \forall i \in [n] \\
x_j^C + B y_j^C + C \geq 0 \quad \forall j \in [m].$$

### Tywin

For Tywin's constraint, we can use that Cersei's constraint is already satisfied. We are interested in the sum of lengths of all sewage pipes (horizontal distances between houses and sewage canal). Given the house $(x,y)$, the length of its sewage pipe is given as $|x - (-By - C)|$. Therefore, we need to satisfy the constraint

$$\sum_{j=1}^m |x_j^C + B y_j^C + C| + \sum_{i=1}^n |x_i^N + B y_i^N + C| \leq s.$$

Using that Cersei's constraint is already satisfied, this is equivalent to

$$\sum_{j=1}^m x_j^C - \sum_{i=1}^n x_i^N + B \left(\sum_{j=1}^m y_j^C - \sum_{i=1}^n y_i^N\right) + C (m - n) \leq s.$$

If $s = -1$ we can skip this constraint.

### Jaimie

Finally, we need to ensure that $L$ is not smaller than the length of the longest fresh water pipe (vertical distance between houses and fresh water canal). Given the house $(x,y)$, the length of its fresh water pipe is given as $|y - (B x + D)|$. For each of the houses (noble and common), we can split this into the two following constraints: $y - B x - D \leq L$ and $-y + B x + D \leq L$.

Now, we simply need to minimize $L$.
