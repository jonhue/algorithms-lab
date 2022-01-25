#include <bits/stdc++.h>

#include <boost/pending/disjoint_sets.hpp>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;

typedef CGAL::Triangulation_vertex_base_with_info_2<int, K>    Vb;
typedef CGAL::Triangulation_face_base_2<K>                     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb>           Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds>                 Triangulation;

typedef std::tuple<int, int, K::FT, bool> Edge; // {u, v, 4 * squared radius, is a bone}

void solve() {
  int n, m; std::cin >> n >> m;
  long s; std::cin >> s;
  int k; std::cin >> k;

  std::vector<std::pair<P, int>> trees;
  for (int i = 0; i < n; i++) {
    int x, y; std::cin >> x >> y;
    trees.push_back({P(x, y), i});
  }

  Triangulation t;
  t.insert(trees.begin(), trees.end());

  std::vector<Edge> edges;
  std::vector<int> bones_by_tree(n, 0);
  int a = 0;

  for (int j = 0; j < m; j++) {
    int x, y; std::cin >> x >> y;
    const P p = P(x, y);
    const auto u = t.nearest_vertex(p);
    const int i = u->info();
    const K::FT dist = 4 * CGAL::squared_distance(p, u->point());
    edges.push_back({i, i, dist, true});

    if (dist <= s) {
      bones_by_tree[i]++;
      a = std::max(a, bones_by_tree[i]);
    }
  }

  boost::disjoint_sets_with_storage<> uf(n);

  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); e++) {
    int i1 = e->first->vertex((e->second+1)%3)->info();
    int i2 = e->first->vertex((e->second+2)%3)->info();

    if (i1 > i2) std::swap(i1, i2); // ensure smaller index comes first

    const K::FT dist = t.segment(e).squared_length();
    edges.push_back({i1, i2, dist, false});

    if (dist <= s) {
      const int c1 = uf.find_set(i1);
      const int c2 = uf.find_set(i2);
      if (c1 == c2) continue;

      uf.link(c1, c2);
      const int c = uf.find_set(c1);
      bones_by_tree[c] = bones_by_tree[c1] + bones_by_tree[c2];
      a = std::max(a, bones_by_tree[c]);
    }
  }

  std::cout << a << " ";

  std::sort(edges.begin(), edges.end(),
    [](const Edge &e1, const Edge &e2) -> bool {
      return std::get<2>(e1) < std::get<2>(e2);
    });

  uf = boost::disjoint_sets_with_storage<>(n);
  std::fill(bones_by_tree.begin(), bones_by_tree.end(), 0);

  K::FT q = 0;
  for (const auto [u, v, dist, is_bone] : edges) {
    q = dist;
    if (is_bone) {
      const int c = uf.find_set(u);
      bones_by_tree[c]++;
      if (bones_by_tree[c] >= k) break;
    } else {
      const int c1 = uf.find_set(u);
      const int c2 = uf.find_set(v);
      if (c1 == c2) continue;

      uf.link(c1, c2);
      const int c = uf.find_set(c1);
      bones_by_tree[c] = bones_by_tree[c1] + bones_by_tree[c2];
      if (bones_by_tree[c] >= k) break;
    }
  }

  std::cout << CGAL::to_double(q) << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
