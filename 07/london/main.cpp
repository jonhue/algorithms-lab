#include <bits/stdc++.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;

class edge_adder {
  graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

const int OFFSET = 65;
const int NUM_CHARS = 26;

void solve() {
  int h, w; std::cin >> h >> w;
  std::string note; std::cin >> note;
  int n = note.size();

  std::vector<int> note_count(NUM_CHARS, 0);
  for (char c : note) {
    note_count[(int)c - OFFSET]++;
  }

  std::vector<std::string> front;
  for (int i = 0; i < h; i++) {
    std::string line; std::cin >> line;
    front.push_back(line);
  }
  std::vector<std::string> back;
  for (int i = 0; i < h; i++) {
    std::string line; std::cin >> line;
    back.push_back(line);
  }

  std::vector<std::vector<int>> newspaper_count(NUM_CHARS, std::vector<int>(NUM_CHARS, 0));
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      char c1 = front[i][j];
      char c2 = back[i][w - j - 1];

      newspaper_count[(int)c1 - OFFSET][(int)c2 - OFFSET]++;
    }
  }

  graph G(NUM_CHARS + NUM_CHARS * NUM_CHARS);
  edge_adder adder(G);

  const auto source = boost::add_vertex(G);
  const auto target = boost::add_vertex(G);

  for (int i = 0; i < NUM_CHARS; i++) {
    for (int j = 0; j < NUM_CHARS; j++) {
      int k = NUM_CHARS + i * NUM_CHARS + j;

      adder.add_edge(source, k, newspaper_count[i][j]);

      adder.add_edge(k, i, std::numeric_limits<int>::max());
      adder.add_edge(k, j, std::numeric_limits<int>::max());
    }
  }

  for (int i = 0; i < NUM_CHARS; i++) {
    adder.add_edge(i, target, note_count[i]);
  }

  int flow = boost::push_relabel_max_flow(G, source, target);
  if (flow == n) {
    std::cout << "Yes" << std::endl;
  } else {
    std::cout << "No" << std::endl;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
