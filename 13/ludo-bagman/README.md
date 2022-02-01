# Ludo Bagman

* flows
* cost flows

This problem can be written as a flow problem. We introduce two vertices for each team, one for the non-difficult (nd) and one for the difficult (d) matches. Each nd-vertex of an eastern team has supply $l$, each nd-vertex of a western team has demand $l$. We add two additional vertices corresponding to the free matches of the eastern teams and the western teams, respectively. They have supply/demand $p - l * e$ and $p - l * w$.

Finally, we add edges for all matches. If there is a flow of $p$, we know that there is a schedule and can call a min cost max flow algorithm to obtain its cost. Otherwise, we return no schedule.
