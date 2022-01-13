#include <bits/stdc++.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

class edge_adder {
  graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

int get_v(const int m, const int i, const int j, const bool is_out) {
  return 2 * (i * m + j) + is_out;
}

void solve() {
  int m, n, k, C; std::cin >> m >> n >> k >> C;

  if (m == 0 || n == 0) {
    std::cout << 0 << std::endl;
    return;
  }

  graph G(2 * n * m);
  edge_adder adder(G);

  const auto source = boost::add_vertex(G);
  const auto target = boost::add_vertex(G);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      adder.add_edge(get_v(m, i, j, false), get_v(m, i, j, true), C); // vertex capacity

      // inner hallways
      if (i > 0) adder.add_edge(get_v(m, i, j, true), get_v(m, i - 1, j, false), 1); // north
      if (i < n - 1) adder.add_edge(get_v(m, i, j, true), get_v(m, i + 1, j, false), 1); // south
      if (j > 0) adder.add_edge(get_v(m, i, j, true), get_v(m, i, j - 1, false), 1); // west
      if (j < m - 1) adder.add_edge(get_v(m, i, j, true), get_v(m, i, j + 1, false), 1); // east
    }
  }

  // outer hallways
  for (int i = 0; i < n; i++) {
    adder.add_edge(get_v(m, i, 0, true), target, 1);
    adder.add_edge(get_v(m, i, m - 1, true), target, 1);
  }
  for (int j = 0; j < m; j++) {
    adder.add_edge(get_v(m, 0, j, true), target, 1);
    adder.add_edge(get_v(m, n - 1, j, true), target, 1);
  }

  for (int l = 0; l < k; l++) {
    int j, i; std::cin >> j >> i;
    adder.add_edge(source, get_v(m, i, j, false), 1);
  }

  int result = boost::push_relabel_max_flow(G, source, target);

  std::cout << result << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
