# Beach Bars

The crucial bit of information for this problem is that the absolute value of the positions of parasols is at most $10^6$. Further, note that any optimal position of our bar must lie between the left-most and right-most parasols. We are then able to iteratively check all candidates using the Sliding Window approach.

As $n \leq 10^6$, our algorithm attains the time complexity $\mathcal{O}(10^6)$.
