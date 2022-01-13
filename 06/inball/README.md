# Inball

* linear programming

We model the problem as a linear program with $d$ variables denoting the position of the center of the enclosed circle and a variable $R$ denoting the radius of the circle which is maximized.

To ensure that the circle remains within the cave, we compute the shortest distance between the center of the circle and each of the cave boundaries $i$:

$$\frac{\sum_j (a_i)_j \cdot X_j + b_i}{\|a_i\|_2} \geq R.$$
