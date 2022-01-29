#include <bits/stdc++.h>

int get_idx(const int n, const int i1, const int j1, const int vd) {
  return n * (n * i1 + j1) + vd;
}

// go with two agents to (n-1,n-1) simultaneously
int rec(
  std::vector<int> &mem,
  const std::vector<std::vector<int>> &as,
  const int n,
  const int i1,
  const int j1,
  const int vd
) {
  const int i2 = i1 - vd;
  const int j2 = j1 + vd;

  if (i1 < 0 || i1 >= n || i2 < 0 || i2 >= n || j1 < 0 || j1 >= n || j2 < 0 || j2 >= n) return 0;
  if (i1 == n - 1 && j1 == n - 1 && i2 == n - 1 && j2 == n - 1) return as[n - 1][n - 1];

  const int idx = get_idx(n, i1, j1, vd);
  if (mem[idx] != -1) return mem[idx];

  int result = (i1 == i2 && j1 == j2) ? as[i1][j1] : as[i1][j1] + as[i2][j2];

  const int a = rec(mem, as, n, i1 + 1, j1, vd); // down, down
  const int b = rec(mem, as, n, i1 + 1, j1, vd + 1); // down, right
  const int c = rec(mem, as, n, i1, j1 + 1, vd - 1); // right, down
  const int d = rec(mem, as, n, i1, j1 + 1, vd); // right, right

  result += std::max({a, b, c, d});

  mem[idx] = result;
  return result;
}

void solve() {
  int n; std::cin >> n;

  std::vector<std::vector<int>> as(n, std::vector<int>());
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int a; std::cin >> a;
      as[i].push_back(a);
    }
  }

  std::vector<int> mem(n * n * n, -1);
  int result = rec(mem, as, n, 0, 0, 0);

  std::cout << result << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
