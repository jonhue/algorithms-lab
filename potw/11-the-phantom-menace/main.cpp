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

int get_obj(const int i, const bool out) {
  return 2 * i + out;
}

void solve() {
  int n, m, s, d; std::cin >> n >> m >> s >> d;

  graph G(2 * n);
  edge_adder adder(G);

  const auto source = boost::add_vertex(G);
  const auto target = boost::add_vertex(G);

  for (int i = 0; i < n; i++) {
    adder.add_edge(get_obj(i, false), get_obj(i, true), 1);
  }

  for (int k = 0; k < m; k++) {
    int i, j; std::cin >> i >> j;
    adder.add_edge(get_obj(i, true), get_obj(j, false), n);
  }

  for (int k = 0; k < s; k++) {
    int i; std::cin >> i;
    adder.add_edge(source, get_obj(i, false), 1);
  }

  for (int k = 0; k < d; k++) {
    int j; std::cin >> j;
    adder.add_edge(get_obj(j, true), target, 1);
  }

  int flow = boost::push_relabel_max_flow(G, source, target);
  std::cout << flow << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
