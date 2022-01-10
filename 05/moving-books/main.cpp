#include <bits/stdc++.h>

void solve() {
  int n, m; std::cin >> n >> m;

  std::vector<int> friends;
  for (int i = 0; i < n; i++) {
    int s; std::cin >> s;
    friends.push_back(s);
  }
  std::sort(friends.begin(), friends.end(), std::greater<int>());

  std::multiset<int, std::greater<int>> boxes;
  for (int j = 0; j < m; j++) {
    int w; std::cin >> w;
    boxes.insert(w);
  }

  if (friends[0] < *boxes.begin()) {
    std::cout << "impossible" << std::endl;
    return;
  }

  int rounds = 0;
  int i = 0;
  int max_i = n;

  while (!boxes.empty()) {
    if (i == 0) rounds++;

    auto it = boxes.lower_bound(friends[i]);
    if (it == boxes.end()) { // all boxes too heavy
      max_i = i;
      i = 0;
    } else {
      boxes.erase(it);
      i = (i + 1) % max_i;
    }
  }

  int result = 3 * rounds - 1;
  std::cout << result << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
