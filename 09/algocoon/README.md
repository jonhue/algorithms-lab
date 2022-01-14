# Algocoön Group

* minimum cuts
* flows

This problem is relatively simple. We just need to compute the minimum cut. W.l.o.g we can fix vertex $0$ to belong to one set. Then, we simply take the smallest of all minimum cuts between $0$ and any other vertex (and vice versa).
