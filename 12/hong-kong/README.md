# Hong Kong

* triangulations
* greedy

We begin by constructing a triangulation of trees. Then, to compute the maximum escape radius of each face, we initialize a priority queue. Infinite faces are initialized with the maximum escape distance, all finite faces are initialized with their take-off clearance. Until the priority queue is empty, we pick the top element. If its escape distance has already been set (to a greater value), we skip it. If it has not been set yet, we store its escape distance and iterate over all neighbors. Each neighbor has as potential new escape distance the minimum of the escape distance of the current face and the length of the shared edge. Finally, we check for each balloon if its distance to the nearest vertex and the escape distance of its face are satisfactory.

The triangulation can be computed in $\mathcal{O}(n \log n)$ time. The escape distance of each face is computed in $\mathcal{O}(n)$ time as there are linearly many faces and each face has its escape distance set only once.
