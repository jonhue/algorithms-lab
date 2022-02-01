# Light the Stage

* triangulations

We begin by constructing a triangulation of all lamps. Observe that a participant with radius $r$ is hit by a lamp if and only if its distance to the lamp is strictly less than $r + h$ (because the radius of the disk illuminated by a lamp is exactly $h$). For each participant, we find the first lamp that hits them. As soon as we have found a participant that is not hit by any lamp, we know that any winner must not be hit by any lamp. Thus, for all future participants it suffices to compare them against their nearest lamp.

The worst-case runtime is $\mathcal{O}(n \cdot m)$, however, in practie we do much better as this is the runtime if all participants are hit by the last lamp.
