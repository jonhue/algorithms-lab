# H1N1

* triangulations
* greedy

We begin by constructing a triangulation of infected people. Then, for each face, we compute the maximum distance one can keep to infected people while escaping. Finally, for each user, we check its distance to the nearest infected person and the escape distance of the face where he is currently located. The last step can clearly be done in $\mathcal{O}(m)$ time.

### Calculating the Escape Distance

We use a greedy approach to calculate the escape distance. We begin with all infinite faces to which we assign an infinite escape distance. We add them to a priority queue which always returns the face with the maximum escape distance. Now, for every face in the queue, we check if its escape distance was already found to be larger than what was stored in the queue. If yes, we skip this face. Otherwise, we update the escape distance of the face and queue all neighboring faces. Here, we can use that the largest distance one can keep while passing from one face to the other is determined by the length of the corresponding edge in the triangulation.

Whenever we encounter a neighboring face which has already had its escape distance set (no matter how small), we can safely skip this face as we know that any subsequent access to this field must necessarily yield a smaller escape distance. Thus, this greedy computation takes $\mathcal{O(n)}$ time as our triangulation has $\mathcal{O}(n)$ faces.

Overall, the runtime of our algorithm is $\mathcal{O}(n \log n + m)$.
