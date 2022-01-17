#include <bits/stdc++.h>

#include <boost/pending/disjoint_sets.hpp>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K>    Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb>           Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds>                 Triangulation;

typedef K::Point_2 P;

typedef std::tuple<int, int, K::FT> Edge; // {u, v, squared_length}

void solve() {
  int n, m; std::cin >> n >> m;
  K::FT p; std::cin >> p;

  std::vector<std::pair<P, int>> jammers;
  for (int i = 0; i < n; i++) {
    int x, y; std::cin >> x >> y;
    jammers.push_back({P(x, y), i});
  }

  std::vector<std::pair<P, P>> missions;
  for (int j = 0; j < m; j++) {
    int x0, y0, x1, y1; std::cin >> x0 >> y0 >> x1 >> y1;
    missions.push_back({P(x0, y0), P(x1, y1)});
  }

  Triangulation t;
  t.insert(jammers.begin(), jammers.end());

  std::vector<Edge> edges;
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); e++) {
    int i1 = e->first->vertex((e->second+1)%3)->info();
    int i2 = e->first->vertex((e->second+2)%3)->info();
    if (i1 > i2) std::swap(i1, i2); // ensure smaller index comes first
    edges.push_back({i1, i2, t.segment(e).squared_length()});
  }
  std::sort(edges.begin(), edges.end(),
    [](const Edge &e1, const Edge &e2) -> bool {
      return std::get<2>(e1) < std::get<2>(e2);
    });

  boost::disjoint_sets_with_storage<> uf(n);
  for (const auto [i1, i2, power] : edges) {
    if (power > p) break;

    const int c1 = uf.find_set(i1);
    const int c2 = uf.find_set(i2);
    if (c1 == c2) continue;

    uf.link(c1, c2);
  }

  K::FT req_p = 0;
  K::FT min_p = 0;
  boost::disjoint_sets_with_storage<> req_uf(n);
  boost::disjoint_sets_with_storage<> min_uf(n);

  for (const auto [p1, p2] : missions) {
    const auto v1 = t.nearest_vertex(p1);
    const auto v2 = t.nearest_vertex(p2);

    const int c1 = uf.find_set(v1->info());
    const int c2 = uf.find_set(v2->info());

    const K::FT min_power = 4 * std::max(
      CGAL::squared_distance(p1, v1->point()),
      CGAL::squared_distance(p2, v2->point()));

    bool possible = min_power <= p && c1 == c2;

    req_p = std::max(req_p, min_power);
    for (const auto [i1, i2, power] : edges) {
      const int d1 = req_uf.find_set(v1->info());
      const int d2 = req_uf.find_set(v2->info());
      if (d1 == d2) break;

      const int e1 = req_uf.find_set(i1);
      const int e2 = req_uf.find_set(i2);
      req_uf.link(e1, e2);
      req_p = std::max(req_p, power);
    }

    if (possible) {
      min_p = std::max(min_p, min_power);
      for (const auto [i1, i2, power] : edges) {
        const int d1 = min_uf.find_set(v1->info());
        const int d2 = min_uf.find_set(v2->info());
        if (d1 == d2) break;

        const int e1 = min_uf.find_set(i1);
        const int e2 = min_uf.find_set(i2);
        min_uf.link(e1, e2);
        min_p = std::max(min_p, power);
      }
    }

    std::cout << (possible ? "y" : "n");
  }

  std::cout
    << "\n"
    << std::ceil(CGAL::to_double(req_p)) << "\n"
    << std::ceil(CGAL::to_double(min_p)) << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  std::cout << std::fixed << std::setprecision(0);

  int t; std::cin >> t;
  while (t--) solve();
}
