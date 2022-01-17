# GoldenEye

* triangulations
* disjoint-sets

We begin by constructing a triangulation of jammers. Then, we first use a disjoint-set to track all jammers with overlapping umbrellas when the power consumption is $p$. Finally, we iterate over all missions. For each mission we first check using the disjoint-set data structure whether it is successful with power consumption $p$. We add two additional disjoint-sets for tracking the connected jammers for all missions to be successful and for at least the possible missions (with power consumption $p$) to be successful.
