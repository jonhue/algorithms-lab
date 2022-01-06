# Even Matrices

## Precomputing Partial Sums

We first compute the sums $S_{i,j}$ for all quadruples $(1,i,1,j)$. This can be done in $\mathcal{O}(n^2)$:

$$
S_{i,j} = \sum_{i'=0}^i \sum_{j'=0}^j x_{i',j'} = S_{i-1,j} + S_{i,j-1} - S_{i-1,j-1} + x_{i,j}.
$$

## Computing the number of even quadruples

The trick is to observe that for any fixed $i_1$ and $i_2$ (i.e., fixed rows) we can use our approach from Even Pairs to compute the number of even quadruples for any $j_1$ and $j_2$ in linear time.

To this end, we fix $j_1 = 1$ and count the number of even quadruples $(i_1,i_2,j_1,j_2)$ for all $j_2$ from $1$ to $n$. Let's refer to this sum as $E$. We then use the formula from Even Pairs to compute the number of even quadruples:

$$
{E \choose 2} + {{n - E} \choose 2} + E.
$$

The total number of even quadruples is the sum of this term over all choices for $i_1$ and $i_2$. Thus, our algorithm runs in time $\mathcal{O}(n^3)$.
