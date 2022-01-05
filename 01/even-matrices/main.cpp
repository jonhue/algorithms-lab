#include <bits/stdc++.h>

void solve() {
  int n; std::cin >> n;

  std::vector<std::vector<int>> xs(n); // values of matrix are indexed starting with 0
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int x; std::cin >> x;
      xs[i].push_back(x);
    }
  }

  std::vector<std::vector<int>> S(n + 1, std::vector<int>(n + 1, 0)); // first value represents boundary; values of matrix are indexed starting with 1
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      S[i][j] = S[i-1][j] + S[i][j-1] - S[i-1][j-1] + xs[i-1][j-1];
    }
  }

  int result = 0;
  for (int i1 = 1; i1 <= n; i1++) {
    for (int i2 = i1; i2 <= n; i2++) {
      int j1 = 1;

      int even = 0;
      for (int j2 = 1; j2 <= n; j2++) {
        int sum = S[i2][j2] - S[i1-1][j2] - S[i2][j1-1] + S[i1-1][j1-1];
        if (sum % 2 == 0) even++;
      }

      result += even * (even - 1) / 2 + (n - even) * (n - even - 1) / 2 + even;
    }
  }

  std::cout << result << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
