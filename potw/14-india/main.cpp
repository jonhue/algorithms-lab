#include <bits/stdc++.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
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
typedef boost::graph_traits<graph>::out_edge_iterator           out_edge_it;

class edge_adder {
 graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}
  edge_desc add_edge(int from, int to, long capacity, long cost) {
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
    return e;
  }
};

void solve() {
  int c, g, b, k, a; std::cin >> c >> g >> b >> k >> a;

  graph G(c);
  edge_adder adder(G);
  auto c_map = boost::get(boost::edge_capacity, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);

  int in_sum = 0, out_sum = 0;
  for (int i = 0; i < g; i++) {
    int x, y, d, e; std::cin >> x >> y >> d >> e;
    adder.add_edge(x, y, e, d);

    if (x == k) in_sum += e;
    if (y == a) out_sum += e;
  }

  const auto source = boost::add_vertex(G);
  const auto edge = adder.add_edge(source, k, 0, 0);

  int l = 0;
  int r = std::min(in_sum, out_sum);

  while (l < r) {
    const int m = std::floor((l + r + 1) / 2);
    c_map[edge] = m;

    boost::successive_shortest_path_nonnegative_weights(G, source, a);
    int cost = boost::find_flow_cost(G);

    int flow = 0;
    out_edge_it e, eend;
    for (boost::tie(e, eend) = boost::out_edges(boost::vertex(source, G), G); e != eend; ++e) {
      flow += c_map[*e] - rc_map[*e];
    }

    if (flow < m) {
      r = m - 1;
      continue;
    }

    if (cost <= b) {
      l = m;
    } else {
      r = m - 1;
    }
  }

  std::cout << l << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
