# Asterix and the Roman Legions

* linear programming

This problem can be solved with a linear program. As variables we use the coordinates to start a fire $X, Y$ as well as the time for the first Roman soldier to get there $T \geq 0$. We want to maximize $T$.

We need to encode two constraints. First, the orientation of the coordinates with respect to the Roman legions to align with the starting location. Second, the time until a soldier of a legion reches the fire place.

Note that for the first constraint, we can use that if $a x_s + b y_s + c > 0$, then $a X + b Y + c$ must be greater than zero as well. Analogously for the other direction.

For the second constraint, observe

$$T \leq \frac{1}{v} |d((X, Y), l)| \quad \forall l.$$
