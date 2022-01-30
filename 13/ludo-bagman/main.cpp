#include <bits/stdc++.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph;

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;

class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  void add_edge(int from, int to, long capacity, long cost) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    auto w_map = boost::get(boost::edge_weight, G); // new!
    const edge_desc e = boost::add_edge(from, to, G).first;
    const edge_desc rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
    w_map[e] = cost;   // new assign cost
    w_map[rev_e] = -cost;   // new negative cost
  }
};

typedef std::tuple<int, int, int> Match; // {u, v, r}

void solve() {
  int e, w, m, d, p, l; std::cin >> e >> w >> m >> d >> p >> l;

  std::vector<Match> non_difficult_matches;
  for (int i = 0; i < m; i++) {
    int u, v, r; std::cin >> u >> v >> r;
    non_difficult_matches.push_back({u, v, r});
  }

  std::vector<Match> difficult_matches;
  for (int i = 0; i < d; i++) {
    int u, v, r; std::cin >> u >> v >> r;
    difficult_matches.push_back({u, v, r});
  }

  graph G(2 * (e + w));
  edge_adder adder(G);

  const auto source = boost::add_vertex(G);
  const auto target = boost::add_vertex(G);

  const auto free_e = boost::add_vertex(G);
  const auto free_w = boost::add_vertex(G);

  adder.add_edge(source, free_e, p - e * l, 0);
  adder.add_edge(free_w, target, p - w * l, 0);

  for (int i = 0; i < e; i++) {
    adder.add_edge(source, 2 * i, l, 0);
    adder.add_edge(free_e, 2 * i, p, 0);
    adder.add_edge(free_e, 2 * i + 1, p, 0);
  }

  for (int i = e; i < e + w; i++) {
    adder.add_edge(2 * i, target, l, 0);
    adder.add_edge(2 * i, free_w, p, 0);
    adder.add_edge(2 * i + 1, free_w, p, 0);
  }

  for (const auto [u, v, r] : non_difficult_matches) {
    adder.add_edge(2 * u, 2 * (e + v), 1, r);
  }

  for (const auto [u, v, r] : difficult_matches) {
    adder.add_edge(2 * u + 1, 2 * (e + v) + 1, 1, r);
  }

  long flow = boost::push_relabel_max_flow(G, source, target);
  if (flow == p) {
    boost::successive_shortest_path_nonnegative_weights(G, source, target);
    long cost = boost::find_flow_cost(G);

    std::cout << cost << std::endl;
  } else {
    std::cout << "No schedule!" << std::endl;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
