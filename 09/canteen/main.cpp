#include <bits/stdc++.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > graph;

typedef boost::graph_traits<graph>::edge_descriptor             edge_desc;
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it;
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

void solve() {
  int n; std::cin >> n;

  std::vector<std::pair<int, int>> in;
  for (int i = 0; i < n; i++) {
    int a, c; std::cin >> a >> c;
    in.push_back({a, c});
  }

  std::vector<std::pair<int, int>> out;
  int total_s = 0;
  int max_p = 0;
  for (int i = 0; i < n; i++) {
    int s, p; std::cin >> s >> p;
    out.push_back({s, p});
    total_s += s;
    max_p = std::max(max_p, p);
  }

  std::vector<std::pair<int, int>> trans;
  for (int i = 0; i < n - 1; i++) {
    int v, e; std::cin >> v >> e;
    trans.push_back({v, e});
  }

  graph G(n);
  edge_adder adder(G);
  auto c_map = boost::get(boost::edge_capacity, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);

  const auto source = boost::add_vertex(G);
  const auto target = boost::add_vertex(G);

  for (int i = 0; i < n; i++) {
    const auto [a, c] = in[i];
    adder.add_edge(source, i, a, c);

    const auto [s, p] = out[i];
    adder.add_edge(i, target, s, max_p - p);

    if (i + 1 < n) {
      const auto [v, e] = trans[i];
      adder.add_edge(i, i + 1, v, e);
    }
  }

  boost::successive_shortest_path_nonnegative_weights(G, source, target);
  int cost = boost::find_flow_cost(G);
  int flow = 0;
  out_edge_it e, eend;
  for (boost::tie(e, eend) = boost::out_edges(boost::vertex(source, G), G); e != eend; e++) {
    flow += c_map[*e] - rc_map[*e];
  }

  int profit = flow * max_p - cost;

  if (flow == total_s) {
    std::cout << "possible ";
  } else {
    std::cout << "impossible ";
  }
  std::cout << flow << " " << profit << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
