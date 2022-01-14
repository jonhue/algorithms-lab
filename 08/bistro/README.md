# Bistro

* triangulations

We simply construct the triangulation of all existing restaurants. Then, for each possible new location, we find the nearest vertex and compute the squared distance between the location and the nearest existing restaurant. The runtime of our algorithm is $\mathcal{O}(n \log n + m)$.
