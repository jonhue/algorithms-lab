#include <bits/stdc++.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_face_base_2.h>
#include <boost/pending/disjoint_sets.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;

typedef CGAL::Triangulation_vertex_base_with_info_2<int,K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation;

typedef std::tuple<int, int, long> Edge;

void solve() {
  int n, k, f_0; long s_0; std::cin >> n >> k >> f_0 >> s_0;

  std::vector<std::pair<P, int>> tents;
  for (int i = 0; i < n; i++) {
    int x, y; std::cin >> x >> y;
    tents.push_back({P(x, y), i});
  }

  Triangulation t;
  t.insert(tents.begin(), tents.end());

  std::vector<Edge> edges;
  for (auto e = t.finite_edges_begin(); e != t.finite_edges_end(); ++e) {
    int i1 = e->first->vertex((e->second+1)%3)->info();
    int i2 = e->first->vertex((e->second+2)%3)->info();
    if (i1 > i2) std::swap(i1, i2); // ensure smaller index comes first
    edges.push_back({i1, i2, t.segment(e).squared_length()});
  }
  std::sort(edges.begin(), edges.end(),
    [](const Edge& e1, const Edge& e2) -> bool {
      return std::get<2>(e1) < std::get<2>(e2);
    }); // sort edges by distance (ascending)

  boost::disjoint_sets_with_storage<> uf(n);
  std::vector<int> num_tents(n, 1);

  std::vector<int> num_components_by_size(k + 1, 0);
  num_components_by_size[1] = n;

  long max_s = 0;
  int max_f = 0;

  int f = num_components_by_size[k];

  for (const auto [i, j, s] : edges) {
    const int c1 = uf.find_set(i);
    const int c2 = uf.find_set(j);
    if (c1 == c2) continue;

    uf.link(c1, c2);
    int c = uf.find_set(c1);

    if (f >= f_0) max_s = std::max(max_s, s);
    if (s >= s_0) max_f = std::max(max_f, f);

    num_components_by_size[std::min(k, num_tents[c1])]--;
    num_components_by_size[std::min(k, num_tents[c2])]--;
    num_components_by_size[std::min(k, num_tents[c1] + num_tents[c2])]++;

    num_tents[c] = num_tents[c1] + num_tents[c2];

    f = num_components_by_size[k];

    switch(k) {
      case 2:
        f += num_components_by_size[1] / 2;
        break;
      case 3:
        f += std::min(num_components_by_size[1], num_components_by_size[2]);
        if (num_components_by_size[2] > num_components_by_size[1]) {
          f += (num_components_by_size[2] - num_components_by_size[1]) / 2;
        } else {
          f += (num_components_by_size[1] - num_components_by_size[2]) / 3;
        }
        break;
      case 4:
        f += num_components_by_size[2] / 2;
        f += std::min(num_components_by_size[1], num_components_by_size[3]);
        int rem = std::abs(num_components_by_size[3] - num_components_by_size[1]);

        if (num_components_by_size[3] > num_components_by_size[1]) {
          f += rem / 2;
          f += ((rem % 2) && (num_components_by_size[2] % 2));
        } else {
          f += rem / 4;
          f += ((rem % 4) >= 2 && (num_components_by_size[2] % 2));
        }
        break;
    }
  }

  std::cout << max_s << " " << max_f << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
