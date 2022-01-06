#include <bits/stdc++.h>

typedef std::pair<int, int> Result; // {min #moves, max #moves}

Result rec(std::vector<Result> &mem, const std::vector<std::vector<int>> &neighbors, const int n, const int u) {
  if (u == n) return {0, 0};

  if (mem[u - 1].first != -1 && mem[u - 1].second != -1) return mem[u - 1];

  std::vector<int> successors = neighbors[u - 1];
  int new_min = n, new_max = 0;
  for (int v : successors) {
    auto [min, max] = rec(mem, neighbors, n, v);

    if (max < new_min) new_min = max;
    if (min > new_max) new_max = min;
  }

  mem[u - 1] = {new_min + 1, new_max + 1};
  return mem[u - 1];
}

void solve() {
  int n, m, r, b; std::cin >> n >> m >> r >> b;

  std::vector<std::vector<int>> neighbors(n, std::vector<int>());
  for (int i = 0; i < m; i++) {
    int u, v; std::cin >> u >> v;
    neighbors[u - 1].push_back(v);
  }

  std::vector<Result> mem(n, {-1, -1});
  auto [min_r, max_r] = rec(mem, neighbors, n, r);
  auto [min_b, max_b] = rec(mem, neighbors, n, b);

  if (min_r < min_b) {
    std::cout << 0 << std::endl;
  } else if (min_b < min_r) {
    std::cout << 1 << std::endl;
  } else {
    // holmes moves black meeple last if his total number of moves is even
    std::cout << (min_r % 2 == 0) << std::endl;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
