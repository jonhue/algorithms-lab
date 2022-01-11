#include <bits/stdc++.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

const int SECOND = 1'000'000;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

void solve() {
  int n, m, k, T; std::cin >> n >> m >> k >> T;

  std::vector<int> network;
  for (int i = 0; i < T; i++) {
    int t; std::cin >> t;
    network.push_back(t);
  }

  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);

  for (int i = 0; i < m; i++) {
    int u, v, c; std::cin >> u >> v >> c;
    const auto edge = boost::add_edge(v, u, G).first;
    weights[edge] = c;
  }

  std::vector<int> component_map(n);
  const int nscc = boost::strong_components(G,
    boost::make_iterator_property_map(component_map.begin(), boost::get(boost::vertex_index, G)));

  std::vector<int> network_size(nscc, 0);
  for (auto t : network) network_size[component_map[t]]++;

  std::vector<std::pair<vertex_desc, vertex_desc>> network_vertices;
  for (int i = 0; i < nscc; i++) {
    const auto in = boost::add_vertex(G);
    const auto out = boost::add_vertex(G);
    network_vertices.push_back({in, out});

    const auto edge = boost::add_edge(in, out, G).first;
    weights[edge] = network_size[i] - 1;
  }
  for (auto t : network) {
    const auto [in, out] = network_vertices[component_map[t]];

    const auto in_edge = boost::add_edge(t, in, G).first;
    weights[in_edge] = 0;

    const auto out_edge = boost::add_edge(out, t, G).first;
    weights[out_edge] = 0;
  }

  std::vector<int> dist_map(boost::num_vertices(G));
  boost::dijkstra_shortest_paths(G, n - 1,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));

  int min_dist = std::numeric_limits<int>::max();
  for (int i = 0; i < k; i++) {
    min_dist = std::min(min_dist, dist_map[i]);
  }

  if (min_dist <= SECOND) {
    std::cout << min_dist << std::endl;
  } else {
    std::cout << "no" << std::endl;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
