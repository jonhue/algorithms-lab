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
  int N, M, S; std::cin >> N >> M >> S;

  std::vector<int> limits;
  for (int i = 0; i < S; i++) {
    int l; std::cin >> l;
    limits.push_back(l);
  }

  std::vector<int> states;
  for (int i = 0; i < M; i++) {
    int s; std::cin >> s;
    states.push_back(s);
  }

  std::vector<std::vector<int>> bids(N, std::vector<int>());
  int max_bid = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      int b; std::cin >> b;
      bids[i].push_back(b);
      max_bid = std::max(max_bid, b);
    }
  }

  graph G(N + M + S);
  edge_adder adder(G);
  auto c_map = boost::get(boost::edge_capacity, G);
  auto rc_map = boost::get(boost::edge_residual_capacity, G);

  const auto source = boost::add_vertex(G);
  const auto target = boost::add_vertex(G);

  const int sites_offset = N;
  const int states_offset = N + M;

  for (int i = 0; i < N; i++) {
    adder.add_edge(source, i, 1, 0);

    for (int j = 0; j < M; j++) {
      adder.add_edge(i, sites_offset + j, 1, max_bid - bids[i][j]);
    }
  }

  for (int i = 0; i < M; i++) {
    int j = states[i] - 1;
    adder.add_edge(sites_offset + i, states_offset + j, 1, 0);
  }

  for (int i = 0; i < S; i++) {
    adder.add_edge(states_offset + i, target, limits[i], 0);
  }

  boost::successive_shortest_path_nonnegative_weights(G, source, target);
  int cost = boost::find_flow_cost(G);
  int flow = 0;
  out_edge_it e, eend;
  for (boost::tie(e, eend) = boost::out_edges(boost::vertex(source, G), G); e != eend; e++) {
    flow += c_map[*e] - rc_map[*e];
  }

  int profit = flow * max_bid - cost;

  std::cout << flow << " " << profit << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
