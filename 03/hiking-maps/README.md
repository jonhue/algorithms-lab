# Hiking Maps

* sliding window
* triangles

## Constructing the triangles

The simple approach to constructing the triangles requires exact constructions and is not sufficient to pass the third testcase. The better approach is to construct the lines making up the triangles in such a way that their positive side is the bounded side with respect to the triangle. This way, we only use predicates.

## Remaining algorithm

Once we have a representation of the triangles, we can check for each map part and segment of the trip in linear time whether the segment is contained by the map part. The full table can be constructed in $\mathcal{O}(n \cdot m)$ time. Using the sliding window technique we can now find the length of the smallest sequence of map parts that contains all trip segments.
