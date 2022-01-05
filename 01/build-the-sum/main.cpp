#include <bits/stdc++.h>

void solve() {
  int n; std::cin >> n;

  int result = 0;
  for (int i = 0; i < n; i++) {
    int a; std::cin >> a;
    result += a;
  }

  std::cout << result << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
