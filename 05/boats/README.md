# Boats

* greedy

Observe that the right boundary of any selected boat will be in the interval $[position, position + length]$. The greedy choice for this problem is to iteratively select the boat with the leftmost right boundary (where boats are sorted based on their positions from left to right). Thus, if the position of the $i$-th boat is larger than the  right boundary of the previous boat, we can simply add the right boat. Otherwise, we need to check whether we want to keep the $i$-th boat or the previously selected boat.

## Proof of Optimality

![image](https://user-images.githubusercontent.com/13420273/148954675-4cddb6d0-2e8a-4d90-9c9d-6625cbea6d33.png)
