#include <bits/stdc++.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/biconnected_components.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
  boost::no_property, boost::property<boost::edge_index_t, int>> graph;
typedef boost::property_map<graph, boost::edge_index_t>::type    edge_index_map;
typedef boost::graph_traits<graph>::edge_iterator                edge_it;

void solve() {
  int n, m; std::cin >> n >> m;

  graph G(n);
  edge_index_map edge_index_map = boost::get(boost::edge_index, G);

  std::vector<std::pair<int, int>> edges;
  for (int i = 0; i < m; i++) {
    int u, v; std::cin >> u >> v;

    auto edge = boost::add_edge(u, v, G).first;
    edge_index_map[edge] = i;
    if (u < v) {
      edges.push_back({u, v});
    } else {
      edges.push_back({v, u});
    }
  }

  std::vector<int> component_map(m);
  int nbc = boost::biconnected_components(G, boost::make_iterator_property_map(component_map.begin(), edge_index_map));

  std::vector<int> num_edges_per_bc(nbc, 0);
  for (int i = 0; i < m; i++) num_edges_per_bc[component_map[i]]++;

  std::vector<std::pair<int, int>> critical_edges;
  for (int i = 0; i < m; i++) {
    if (num_edges_per_bc[component_map[i]] == 1) critical_edges.push_back(edges[i]);
  }

  std::sort(critical_edges.begin(), critical_edges.end());

  std::cout << critical_edges.size() << "\n";
  for (auto [u, v] : critical_edges) std::cout << u << " " << v << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
