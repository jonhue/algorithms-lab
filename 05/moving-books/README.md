# Moving Books

* greedy

Here, the greedy approach is quite easy to figure out. Clearly it is optimal for each friend to always take the heaviest box they can carry. The difficulty is with coming up with an efficient implementation.

The idea is to sort the strengths of friends and weights of boxes in descending order. Then, until there are no boxes left, we can rotate through the friends, find the heaviest box a particular friend can carry, and delete this box. We use a multiset to encapsulate the boxes as this provides a logarithmic deletion time and logarithmic time for finding the heaviest box for a friend. In this way we can figure out the number of necessary rounds $r$. The final result is $3r - 1$.

The overall time complexity is $\mathcal{O}((n + m) \log (n + m))$.

## Proof of Optimality

![image](https://user-images.githubusercontent.com/13420273/148954699-9dcb6bdf-558b-4890-8413-6234577824cd.png)
