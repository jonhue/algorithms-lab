#include <bits/stdc++.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

void solve() {
  int n, e, s, a, b; std::cin >> n >> e >> s >> a >> b;

  std::vector<weighted_graph> networks;
  std::vector<weight_map> network_weights;
  for (int i = 0; i < s; i++) {
    weighted_graph network(n);
    weight_map weights = boost::get(boost::edge_weight, network);
    networks.push_back(network);
    network_weights.push_back(weights);
  }

  for (int i = 0; i < e; i++) {
    int u, v; std::cin >> u >> v;
    for (int j = 0; j < s; j++) {
      int w; std::cin >> w;
      edge_desc edge = boost::add_edge(u, v, networks[j]).first;
      network_weights[j][edge] = w;
    }
  }

  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);

  for (int i = 0; i < s; i++) {
    int h; std::cin >> h;

    auto network = networks[i];

    std::vector<edge_desc> mst;
    boost::kruskal_minimum_spanning_tree(network, std::back_inserter(mst));

    for (auto edge : mst) {
      int u = boost::source(edge, network);
      int v = boost::target(edge, network);
      int w = network_weights[i][edge];
      if (boost::edge(u, v, G).second) { // edge exists
        auto new_edge = boost::edge(u, v, G).first;
        weights[new_edge] = std::min(weights[new_edge], w);
      } else { // edge does not exist
        auto new_edge = boost::add_edge(u, v, G).first;
        weights[new_edge] = w;
      }
    }
  }

  std::vector<int> dist_map(n);
  boost::dijkstra_shortest_paths(G, a,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));
  int result = dist_map[b];

  std::cout << result << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
