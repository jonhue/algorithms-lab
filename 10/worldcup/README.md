# Worldcup

* triangulations
* linear programming

The first intuition might be to use cost flows to model this problem. This is not possible, however, as this does not allow us to model the upper limit on alcohol in each stadium. Instead, we use a linear program.

## Counting traversed contour lines

Here, it is crucial to note that we have _at most_ $100$ contour lines that have at least one stadium or warehouse in their interior. Thus, we first eliminate all contour lines that have no points in their interior using a triangulation of points and computing their distance to the nearest vertex. Then, for each warehouse and stadium, we count the number of circles that contain exactly one of the two positions. This is the number of contour lines that need to be traversed.

## Linear program

In our linear program, we use as variables the amounts of beer (in liters) that are moved from a warehouse to a stadium. We have four constraints:

* the sent beer does not exceed the supply (for any warehouse);
* the received beer meets the demand exactly (for any stadium);
* there is not too much beer sent on a single route (for any warehouse and stadium); and
* the upper limits on alcohol are met (for any stadium)

We maximize the total profit. Note that the profit and the last constraint can be scaled by $100$ to obtain a linear program with integral coefficients.
