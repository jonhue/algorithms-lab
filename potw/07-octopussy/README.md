# Octopussy

* greedy

We begin by propagating the explosion times to the bombs on the ground layer. The idea is that a bomb on the ground layer has to be deactivated before it explodes and before any of the bombs on top explode.

Then, all that is left to check is that Bond can "stay ahead" of the bombs. We sort the vector of explosion times and check if we can deactivate them one by one. This deactivation strategy is greedy. Clearly, it is always optimal to deactivate the bomb which explodes next first.
