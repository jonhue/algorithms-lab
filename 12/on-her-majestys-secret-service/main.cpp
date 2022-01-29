#include <bits/stdc++.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, boost::property<boost::edge_weight_t, int> >      weighted_graph;
typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::graph_traits<weighted_graph>::edge_descriptor            weighted_edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          weighted_vertex_desc;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;
typedef boost::graph_traits<graph>::vertex_descriptor                       vertex_desc;

typedef std::pair<int, int> Shelter; // {position, delay}

void solve() {
  int n, m, a, s, c, d; std::cin >> n >> m >> a >> s >> c >> d;

  weighted_graph G(n);
  weight_map weights = boost::get(boost::edge_weight, G);

  for (int i = 0; i < m; i++) {
    char w; int x, y, z; std::cin >> w >> x >> y >> z;

    const auto edge = boost::add_edge(x, y, G).first; weights[edge] = z;
    if (w == 'L') {
      const auto edge = boost::add_edge(y, x, G).first; weights[edge] = z;
    }
  }

  std::vector<int> agents;
  for (int i = 0; i < a; i++) {
    int alpha; std::cin >> alpha;
    agents.push_back(alpha);
  }

  std::vector<Shelter> shelters;
  for (int i = 0; i < s; i++) {
    int omega; std::cin >> omega;

    for (int j = 1; j <= c; j++) {
      shelters.push_back({omega, j * d});
    }
  }

  std::vector<std::vector<int>> distances(a, std::vector<int>(c * s, -1)); // min distance per agent to any of the shelters
  for (int i = 0; i < a; i++) {
    const int alpha = agents[i];

    std::vector<int> dist_map(n);
    boost::dijkstra_shortest_paths(G, alpha,
      boost::distance_map(boost::make_iterator_property_map(
        dist_map.begin(), boost::get(boost::vertex_index, G))));

    for (int j = 0; j < c * s; j++) {
      const auto [omega, delay] = shelters[j];
      if (dist_map[omega] < std::numeric_limits<int>::max()) {
        distances[i][j] = dist_map[omega] + delay;
      }
    }
  }

  long l = 0;
  long u = std::numeric_limits<int>::max() - 1;
  while (l < u) {
    const int m = (l == 0 && u == std::numeric_limits<int>::max() - 1) ? 10 : std::floor((l + u) / 2);

    graph F(a + c * s);
    for (int i = 0; i < a; i++) {
      for (int j = 0; j < c * s; j++) {
        if (distances[i][j] >= 0 && distances[i][j] <= m) {
          boost::add_edge(i, a + j, F);
        }
      }
    }

    std::vector<vertex_desc> mate_map(a + c * s);
    boost::edmonds_maximum_cardinality_matching(F,
      boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, F)));
    const int matching_size = boost::matching_size(F,
      boost::make_iterator_property_map(mate_map.begin(), boost::get(boost::vertex_index, F)));

    if (matching_size == a) {
      u = m;
    } else {
      l = m + 1;
    }
  }

  std::cout << l << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
