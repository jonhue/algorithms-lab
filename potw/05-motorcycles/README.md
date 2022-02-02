# Motorcycles

* greedy

First, we observe that if the trajectory of two bikers intersects, then the biker with the smaller absolute slope continues their journey (if the absolute slopes are equal the biker with the smaller starting position continues their journey). Moreover, if biker $i$ starts from a higher position than biker $j$, then their trajectories intersect if and only if the slope of biker $i$ is strictly smaller than the slope of biker $j$.

Thus we can proceed as follows: We first order the bikers by their starting position (descending). Moreover, we construct a priority queue that tracks all bikers riding forever (ordered by their slope, ascending). Then we iterate over all bikers. For each biker, we compare it against the first biker of the priority queue. We skip the current biker or remove bikers from the priority queue until we are in a consistent state. Finally, we sort the resulting bikers by their indices and return.
