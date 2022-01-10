#include <bits/stdc++.h>

typedef std::pair<int, int> Boat; // {length, position}

void solve() {
  int n; std::cin >> n;

  std::vector<Boat> boats;
  for (int i = 0; i < n; i++) {
    int l, p; std::cin >> l >> p;
    boats.push_back({l, p});
  }
  std::sort(boats.begin(), boats.end(), [](Boat &b1, Boat &b2) { return b1.second < b2.second; });

  int pos = std::numeric_limits<int>::min();
  int last_pos = std::numeric_limits<int>::min();
  int result = 0;
  for (auto [l, p] : boats) {
    if (p >= last_pos) { // add boat
      result++;
      pos = last_pos;
      last_pos = std::max(last_pos + l, p);
    } else { // consider replacing last boat
      int new_last_pos = std::max(pos + l, p);
      last_pos = std::min(last_pos, new_last_pos);
    }
  }

  std::cout << result << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
