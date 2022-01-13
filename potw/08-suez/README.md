# Suez

* linear programming

The problem can be modeled as a linear program. For each of the $n$ posters to be added to the wall, we introduce the variable $A_i$ denoting the magnification of poster $i$. The sum of perimeters of all new posters is

$$2 \sum_{i = 1}^n A_i (w + h)$$

which we maximize.

## Constraints

As constraints we need to ensure that the new posters do not overlap with each other and the existing posters.

### Old Posters

We need to make sure that one of the following holds:

$$2 |x_i - x_j| \geq A_i w + w \\ 2 |y_i - y_j| \geq A_i h + h.$$

This is equivalent to:

$$A_i \leq \max \{2 \frac{|x_i - x_j|}{w} - 1, 2 \frac{|y_i - y_j|}{h} - 1\}.$$

### New Posters

For the new posters we obtain

$$A_i + A_j \leq \max \{2 \frac{|x_i - x_j|}{w}, 2 \frac{|y_i - y_j|}{h}\}$$

analogously.
