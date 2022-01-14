#include <bits/stdc++.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor                       vertex_desc;

bool is_white(const int n, const int i, const int j) {
  return (i + j) & 1;
}

int from_coords(const int n, const int i, const int j) {
  return i * n + j;
}

void solve() {
  int n; std::cin >> n;

  std::vector<std::vector<bool>> is_present(n, std::vector<bool>());
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      bool p; std::cin >> p;
      is_present[i].push_back(p);
    }
  }

  graph G(n * n);

  int count = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (!is_present[i][j]) continue;
      count++;

      if (is_white(n, i, j)) continue;
      const int k = from_coords(n, i, j);

      if (i-1 >= 0 && j-2 >= 0 && is_present[i-1][j-2]) boost::add_edge(k, from_coords(n, i-1, j-2), G);
      if (i-1 >= 0 && j+2 < n && is_present[i-1][j+2]) boost::add_edge(k, from_coords(n, i-1, j+2), G);
      if (i+1 < n && j-2 >= 0 && is_present[i+1][j-2]) boost::add_edge(k, from_coords(n, i+1, j-2), G);
      if (i+1 < n && j+2 < n && is_present[i+1][j+2]) boost::add_edge(k, from_coords(n, i+1, j+2), G);
      if (i-2 >= 0 && j-1 >= 0 && is_present[i-2][j-1]) boost::add_edge(k, from_coords(n, i-2, j-1), G);
      if (i-2 >= 0 && j+1 < n && is_present[i-2][j+1]) boost::add_edge(k, from_coords(n, i-2, j+1), G);
      if (i+2 < n && j-1 >= 0 && is_present[i+2][j-1]) boost::add_edge(k, from_coords(n, i+2, j-1), G);
      if (i+2 < n && j+1 < n && is_present[i+2][j+1]) boost::add_edge(k, from_coords(n, i+2, j+1), G);
    }
  }

  std::vector<vertex_desc> mate_map(n * n);
  boost::edmonds_maximum_cardinality_matching(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
  int matching_size = boost::matching_size(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));

  int result = count - matching_size;
  std::cout << result << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
