#include <bits/stdc++.h>

typedef std::pair<int, int> Child; // {v, l}
typedef std::vector<std::vector<Child>> Tree;
typedef std::tuple<int, long, long> Result; // {#vertices, #lost galleons, time to explore}
typedef std::tuple<int, Result> IntermResult; // {l, result}

Result rec(Tree &tree, const int u) {
  const std::vector<Child> children = tree[u];
  if (children.empty()) return {1, 0, 0};

  std::vector<IntermResult> results;
  for (const auto [v, l] : children) {
    const auto result = rec(tree, v);
    results.push_back({l, result});
  }

  std::sort(results.begin(), results.end(),
    [](const IntermResult &ir1, const IntermResult &ir2) -> bool {
      const auto [l1, r1] = ir1;
      const auto [m1, g1, t1] = r1;

      const auto [l2, r2] = ir2;
      const auto [m2, g2, t2] = r2;

      return (2 * l1 + t1) / (double)m1 < (2 * l2 + t2) / (double)m2;
    });

  int m = 1;
  long g = 0;
  long t = 0;
  for (const auto [l, ir] : results) {
    const auto [sub_m, sub_g, sub_t] = ir;

    m += sub_m;
    g += (l + t) * sub_m + sub_g;
    t += 2 * l + sub_t;
  }

  return {m, g, t};
}

void solve() {
  int n; std::cin >> n;

  long total_g = 0;
  for (int i = 0; i < n; i++) {
    int g; std::cin >> g;
    total_g += g;
  }

  Tree tree(n + 1, std::vector<Child>());
  for (int i = 0; i < n; i++) {
    int u, v, l; std::cin >> u >> v >> l;
    tree[u].push_back({v, l});
  }

  const auto [m, g, t] = rec(tree, 0);
  long result = total_g - g;

  std::cout << result << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
