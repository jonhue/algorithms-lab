#include <bits/stdc++.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor                       vertex_desc;

int count_shared_characteristics(const int c, const std::vector<std::string> v1, const std::vector<std::string> v2) {
  int i1 = 0, i2 = 0;
  int result = 0;
  while (i1 < c && i2 < c) {
    int cmp = v1[i1].compare(v2[i2]);
    if (cmp == 0) {
      result++;
      i1++;
      i2++;
    } else if (cmp < 0) {
      i1++;
    } else if (cmp > 0) {
      i2++;
    }
  }
  return result;
}

void solve() {
  int n, c, f; std::cin >> n >> c >> f;

  std::vector<std::vector<std::string>> characteristics(n, std::vector<std::string>());
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < c; j++) {
      std::string key; std::cin >> key;
      characteristics[i].push_back(key);
    }
    std::sort(characteristics[i].begin(), characteristics[i].end());
  }

  graph G(n);

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (count_shared_characteristics(c, characteristics[i], characteristics[j]) > f) {
        boost::add_edge(i, j, G);
      }
    }
  }

  std::vector<vertex_desc> mate_map(n);

  boost::edmonds_maximum_cardinality_matching(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));
  int matching_size = boost::matching_size(G,
    boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, G)));

  if (matching_size == n / 2) {
    std::cout << "not optimal" << std::endl;
  } else {
    std::cout << "optimal" << std::endl;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
