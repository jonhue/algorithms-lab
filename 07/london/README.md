# London

* flows

Observe that any piece cut out of the newspaper is of one of $26 \cdot 26$ types. We begin by counting the number of pieces of each of the types. We also count the occurrences of each letter in the given note.

We then construct a graph with one vertex for each type of piece and one vertex for each letter. Each piece is supplied with flow corresponding to its occurrences in the newspaper. Then, we add an edge from each piece to the two letters it could potentially be used as. Finally, we add a demand to each letter corresponding to its occurrences in the note. We know that the note can be constructed from the newspaper if and only if the maximum flow is equal to the length of the note.

The runtime of our algorithm is $\mathcal{O}(h \cdot w + n)$.
