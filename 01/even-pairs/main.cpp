#include <bits/stdc++.h>

void solve() {
  int n; std::cin >> n;

  int even = 0;
  bool is_even = true;
  for (int i = 0; i < n; i++) {
    int x; std::cin >> x;
    is_even = (is_even && x == 0) || (!is_even && x == 1);
    if (is_even) even++;
  }

  int result = even * (even - 1) / 2 + (n - even) * (n - even - 1) / 2 + even;

  std::cout << result << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
