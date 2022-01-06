# The Great Game

For this problem, it suffices to calculate the minimal and maximal number of moves from each position to reach the target. As the player alternates in each step, the minimizing player minimizes the number of moves to the target among all the maximum number of moves from all possible destinations. The maximizing player behaves symmetrically.

If the minimal number of moves from the position of the red meeple and the black meeple are different, we have a clear winner (note that Holmes and Moriarty begin by moving their meeple). If they are the same, we need to check if Holmes last moved the red or the black meeple. Observe that if the required number of moves is even, he moves the black meeple in his last move and thus Moriarty wins.
