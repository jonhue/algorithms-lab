#include <bits/stdc++.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/bipartite.hpp>
#include <boost/graph/connected_components.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;

typedef CGAL::Triangulation_vertex_base_with_info_2<int,K>     Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Triangulation;

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> graph;

typedef std::pair<P, P> Clue; // {a, b}

void solve() {
  int n, m; K::FT r; std::cin >> n >> m >> r;
  K::FT squared_r = r * r;

  std::vector<std::pair<P, int>> stations;
  for (int i = 0; i < n; i++) {
    int x, y; std::cin >> x >> y;
    stations.push_back({P(x, y), i});
  }

  std::vector<Clue> clues;
  for (int i = 0; i < m; i++) {
    int ax, ay, bx, by; std::cin >> ax >> ay >> bx >> by;
    clues.push_back({P(ax, ay), P(bx, by)});
  }

  Triangulation t;
  t.insert(stations.begin(), stations.end());

  graph G(n);

  for (auto v = t.finite_vertices_begin(); v != t.finite_vertices_end(); v++) {
    int i = v->info();

    auto c1 = t.incident_vertices(v);
    do {
      if (t.is_infinite(c1)) continue;
      int i1 = c1->info();
      if (CGAL::squared_distance(v->point(), c1->point()) <= squared_r) boost::add_edge(i, i1, G);

      auto c2 = t.incident_vertices(c1);
      do {
        if (t.is_infinite(c2)) continue;
        int i2 = c2->info();
        if (i == i2) continue;
        if (CGAL::squared_distance(v->point(), c2->point()) <= squared_r) boost::add_edge(i, i2, G);
      } while (++c2 != t.incident_vertices(c1));
    } while (++c1 != t.incident_vertices(v));
  }

  if (!boost::is_bipartite(G)) {
    for (int i = 0; i < m; i++) {
      std::cout << "n";
    }
    std::cout << std::endl;
    return;
  }

  std::vector<int> component_map(n);
  int ncc = boost::connected_components(G,
    boost::make_iterator_property_map(component_map.begin(), boost::get(boost::vertex_index, G)));

  for (const auto [a, b] : clues) {
    if (CGAL::squared_distance(a, b) <= squared_r) {
      std::cout << "y";
      continue;
    }

    const auto v1 = t.nearest_vertex(a);
    const auto v2 = t.nearest_vertex(b);

    if (std::max(CGAL::squared_distance(a, v1->point()), CGAL::squared_distance(b, v2->point())) > squared_r) {
      std::cout << "n";
      continue;
    }

    const int i1 = v1->info();
    const int i2 = v2->info();

    std::cout << (component_map[i1] == component_map[i2] ? "y" : "n");
  }
  std::cout << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
