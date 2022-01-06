# From Russia with Love

* dynamic programming (on sovereigns)

I find this problem statement rather confusing. Originally, I interpreted it as that we should find the largest winnings of player $k$ _regardless_ of how other players play. That is, the largest possible winnings of player $k$. However, what we are supposed to find is the maximal _guaranteed_ winnings of player $k$ (assuming all other players play adversarially).

Both are quite straightforward, though, and their implementation differs in only one line.

We observe that given a subsequence of sovereigns (from $i$ to $j$) we have a fixed result. This is because for each such subsequence there is a single player whose turn it is. Thus, $i$ and $j$ identify non-overlapping subproblems which we use to setup our dynamic program. Note that this is very similar to what we have done in Burning Coins.

Overall, our algorithm attains a time complexity of $\mathcal{O}(n^2)$.
