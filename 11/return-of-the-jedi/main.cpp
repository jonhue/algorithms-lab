#include <bits/stdc++.h>

#include <boost/pending/disjoint_sets.hpp>

typedef std::tuple<int, int, int> Edge; // {i, j, c}

int compute_mst(const int n, const std::vector<Edge> &edges, std::vector<Edge> &mst, const std::pair<int, int> &ignored_edge) {
  boost::disjoint_sets_with_storage<> uf(n);

  int cost = 0;

  for (const auto [i, j, c] : edges) {
    if (ignored_edge == std::make_pair(i, j)) continue;

    const int c1 = uf.find_set(i);
    const int c2 = uf.find_set(j);
    if (c1 == c2) continue;

    mst.push_back({i, j, c});
    cost += c;
    uf.link(c1, c2);

    if (mst.size() == n - 1) break;
  }

  return cost;
}

void solve() {
  int n, i; std::cin >> n >> i;

  std::vector<Edge> edges;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      int c; std::cin >> c;
      edges.push_back({i, j, c});
    }
  }

  std::sort(edges.begin(), edges.end(),
    [](const Edge &e1, const Edge &e2) -> bool {
      return std::get<2>(e1) < std::get<2>(e2);
    });

  std::vector<Edge> mst;
  compute_mst(n, edges, mst, {-1, -1});

  int result = std::numeric_limits<int>::max();
  for (const auto [i, j, _c] : mst) {
    std::vector<Edge> _unused;
    int cost = compute_mst(n, edges, _unused, {i, j});
    result = std::min(result, cost);
  }

  std::cout << result << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
