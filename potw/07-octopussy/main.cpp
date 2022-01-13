#include <bits/stdc++.h>

void solve() {
  int n; std::cin >> n;

  std::vector<int> times;
  for (int i = 0; i < n; i++) {
    int t; std::cin >> t;
    times.push_back(t);
  }

  for (int i = 0; i < (n - 1) / 2; i++) {
    times[2 * i + 1] = std::min(times[2 * i + 1], times[i]);
    times[2 * i + 2] = std::min(times[2 * i + 2], times[i]);
  }

  std::sort(times.begin(), times.end());

  for (int t = 0; t < n; t++) {
    if (t >= times[t]) {
      std::cout << "no" << std::endl;
      return;
    }
  }

  std::cout << "yes" << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
