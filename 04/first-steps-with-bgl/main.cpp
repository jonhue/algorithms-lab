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
  int n, m; std::cin >> n >> m;

  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);

  for (int i = 0; i < m; i++) {
    int u, v, w; std::cin >> u >> v >> w;
    edge_desc e = boost::add_edge(u, v, G).first; weights[e] = w;
  }

  // Kruskal
  std::vector<edge_desc> mst;
  boost::kruskal_minimum_spanning_tree(G, std::back_inserter(mst));

  int mst_weight = 0;
  for (auto e : mst) mst_weight += weights[e];

  // Dijkstra
  std::vector<int> dist_map(n);
  boost::dijkstra_shortest_paths(G, 0,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));

  int max_dist = 0;
  for (int v = 1; v < n; v++) max_dist = std::max(max_dist, dist_map[v]);

  std::cout << mst_weight << " " << max_dist << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
