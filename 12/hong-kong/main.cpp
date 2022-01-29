#include <bits/stdc++.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;

typedef CGAL::Triangulation_vertex_base_2<K>                   Vb;
typedef CGAL::Triangulation_face_base_with_info_2<K::FT, K>    Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Triangulation;

typedef std::pair<P, K::FT> Balloon; // {pos, radius}

void solve() {
  int n, m; K::FT r; std::cin >> n >> m >> r;

  std::vector<P> trees;
  for (int i = 0; i < n; i++) {
    int x, y; std::cin >> x >> y;
    trees.push_back(P(x, y));
  }

  std::vector<Balloon> balloons;
  for (int i = 0; i < m; i++) {
    int x, y; K::FT s; std::cin >> x >> y >> s;
    balloons.push_back({P(x, y), s});
  }

  Triangulation t;
  t.insert(trees.begin(), trees.end());

  std::priority_queue<std::pair<K::FT, Triangulation::Face_handle>> queue;

  for (auto f = t.all_faces_begin(); f != t.all_faces_end(); f++) {
    f->info() = 0;

    if (t.is_infinite(f)) {
      queue.push({K::FT(std::numeric_limits<long>::max()) * K::FT(std::numeric_limits<long>::max()), f});
    } else {
      queue.push({CGAL::squared_radius(f->vertex(0)->point(), f->vertex(1)->point(), f->vertex(2)->point()), f});
    }
  }

  while (!queue.empty()) {
    const auto [d, f] = queue.top();
    queue.pop();

    if (f->info() >= d) continue;
    f->info() = d;

    for (int i = 0; i < 3; i++) {
      const auto g = f->neighbor(i);
      if (t.is_infinite(g)) continue;

      const K::FT new_d = std::min(d, t.segment(f, i).squared_length());
      if (g->info() >= new_d) continue;
      queue.push({new_d, g});
    }
  }

  for (const auto [p, s] : balloons) {
    const auto v = t.nearest_vertex(p);
    const auto f = t.locate(p);

    const K::FT thresh = (r + s) * (r + s);

    if (thresh > CGAL::squared_distance(p, v->point())) {
      std::cout << "n";
      continue;
    }

    if (4 * thresh > f->info()) {
      std::cout << "n";
      continue;
    }

    std::cout << "y";
  }

  std::cout << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
