# First Hit

* intersections

The trick is to minimize the number of constructions (as opposed to predicates) by only constructing intersections when we _know_ they are closer to the intersecting point we have constructed thus far.

To reduce the impact of adversarial inputs, we randomly shuffle the given segments beforehand. The runtime of our algorithm is linear in the number of obstacles.
