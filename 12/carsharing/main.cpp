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

typedef std::tuple<int, int, int, int, int> Request; // {s, r, d, a, p}

const int T = 100'000;
const int MAX_PROFIT = 100;

void solve() {
  int N, S; std::cin >> N >> S;

  std::vector<int> supplies;
  int total_supply = 0;
  for (int i = 0; i < S; i++) {
    int l; std::cin >> l;
    supplies.push_back(l);
    total_supply += l;
  }

  std::vector<Request> requests;
  for (int i = 0; i < N; i++) {
    int s, t, d, a, p; std::cin >> s >> t >> d >> a >> p;
    requests.push_back({s, t, d, a, p});
  }

  std::vector<std::map<int, int>> times(S, std::map<int, int>()); // for each station, maps time to unique index
  for (int i = 0; i < S; i++) {
    times[i][0] = 0;
    times[i][T] = 0;
  }
  for (const auto &[s, t, d, a, p] : requests) {
    times[s - 1][d] = 0;
    times[t - 1][a] = 0;
  }
  int idx;
  for (int i = 0; i < S; i++) {
    for (auto &[k, v] : times[i]) {
      v = idx++;
    }
  }

  graph G(idx);
  edge_adder adder(G);

  const auto source = boost::add_vertex(G);
  const auto target = boost::add_vertex(G);

  // add initial & final transitions
  for (int i = 0; i < S; i++) {
    adder.add_edge(source, times[i][0], supplies[i], 0);
    adder.add_edge(times[i][T], target, total_supply, 0);
  }

  // transitions between states of the same station
  for (int i = 0; i < S; i++) {
    auto prev = times[i].begin();
    for (auto curr = ++times[i].begin(); curr != times[i].end(); curr++) {
      const auto [d, i1] = *prev;
      const auto [a, i2] = *curr;
      adder.add_edge(i1, i2, total_supply, (a - d) * MAX_PROFIT);

      prev = curr;
    }
  }

  // requests
  for (const auto [s, t, d, a, p] : requests) {
    adder.add_edge(times[s - 1][d], times[t - 1][a], 1, (a - d) * MAX_PROFIT - p);
  }

  boost::successive_shortest_path_nonnegative_weights(G, source, target);
  int cost = boost::find_flow_cost(G);

  int result = (long)T * (long)total_supply * (long)MAX_PROFIT - cost;

  std::cout << result << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
