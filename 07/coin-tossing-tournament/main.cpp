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

void solve() {
  int n, m; std::cin >> n >> m;

  graph G(n + m);
  edge_adder adder(G);

  const auto source = boost::add_vertex(G);
  const auto target = boost::add_vertex(G);

  for (int j = 0; j < m; j++) {
    int k = n + j;

    adder.add_edge(source, k, 1);

    int a, b, c; std::cin >> a >> b >> c;
    if (c == 0 || c == 1) adder.add_edge(k, a, 1);
    if (c == 0 || c == 2) adder.add_edge(k, b, 1);
  }

  int total_s = 0;
  for (int i = 0; i < n; i++) {
    int s; std::cin >> s;
    adder.add_edge(i, target, s);
    total_s += s;
  }

  if (total_s != m) {
    std::cout << "no" << std::endl;
    return;
  }

  int flow = boost::push_relabel_max_flow(G, source, target);
  if (flow == total_s) {
    std::cout << "yes" << std::endl;
  } else {
    std::cout << "no" << std::endl;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
