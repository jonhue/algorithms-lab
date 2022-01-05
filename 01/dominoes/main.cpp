#include <bits/stdc++.h>

void solve() {
  int n; std::cin >> n;

  std::vector<int> heights;
  for (int i = 0; i < n; i++) {
    int h; std::cin >> h;
    heights.push_back(h);
  }

  int result = 1;
  int pos = heights[0];
  for (int i = 1; i < n; i++) {
    if (i >= pos) break;
    result++;
    pos = std::max(pos, i + heights[i]);
  }

  std::cout << result << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
