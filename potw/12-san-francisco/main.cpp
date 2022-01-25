#include <bits/stdc++.h>

typedef std::pair<int, long> Canal; // {u, p}

void solve() {
  int n, m, k; long x; std::cin >> n >> m >> x >> k;

  std::vector<std::vector<Canal>> predecessors(n, std::vector<Canal>());
  std::vector<int> outgoing(n, 0);

  for(int i = 0; i < m; i++) {
    int u, v; std::cin >> u >> v;
    long p; std::cin >> p;

    predecessors[v].push_back({u, p});
    outgoing[u]++;
  }

  for(int i = 0; i < n; i++) {
    if (outgoing[i] == 0) {
      for (const auto &c : predecessors[i]) {
        predecessors[0].push_back(c);
      }
    }
  }

  std::vector<std::vector<long>> mem(k + 1, std::vector<long>(n, -1));
  mem[0][0] = 0;
  for (int i = 1; i <= k; i++) {
    for (int v = 0; v < n; v++) {
      long best = -1;
      for (const auto &[u, p] : predecessors[v]) {
        if (mem[i - 1][u] != -1) best = std::max(best, mem[i - 1][u] + p);
      }
      mem[i][v] = best;

      if (best >= x) {
        std::cout << i << std::endl;
        return;
      }
    }
  }

  std::cout << "Impossible" << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
