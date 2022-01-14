#include <bits/stdc++.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;

typedef CGAL::Triangulation_vertex_base_2<K>                   Vb;
typedef CGAL::Triangulation_face_base_with_info_2<K::FT,K>     Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>            Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                  Triangulation;

void solve(const int n) {
  std::vector<P> infected;
  for (int i = 0; i < n; i++) {
    int x, y; std::cin >> x >> y;
    infected.push_back(P(x, y));
  }

  int m; std::cin >> m;

  std::vector<std::pair<P, long>> users;
  for (int i = 0; i < m; i++) {
    int x, y; std::cin >> x >> y;
    K::FT d; std::cin >> d;
    users.push_back({P(x, y), d});
  }

  Triangulation t;
  t.insert(infected.begin(), infected.end());

  std::priority_queue<std::pair<K::FT, Triangulation::Face_handle>> queue; // always continue with the face with the largest escape size

  for (auto f = t.all_faces_begin(); f != t.all_faces_end(); f++) {
    if (t.is_infinite(f)) {
      queue.push({std::numeric_limits<double>::max(), f});
    } else {
      f->info() = 0;
    }
  }

  while (!queue.empty()) {
    const auto [d, f] = queue.top();
    queue.pop();

    if (f->info() >= d) continue;
    f->info() = d;

    for (int i = 0; i < 3; i++) {
      const auto g = f->neighbor(i);
      if (g->info() != 0) continue;

      const K::FT squared_dist = t.segment(f, i).squared_length();
      queue.push({std::min(f->info(), squared_dist / 4), g});
    }
  }

  for (const auto [p, d] : users) {
    const auto f = t.locate(p);
    const auto v = t.nearest_vertex(p);

    if (d > CGAL::squared_distance(p, v->point())) {
      std::cout << "n";
      continue;
    }

    if (d > f->info()) {
      std::cout << "n";
      continue;
    }

    std::cout << "y";
  }
  std::cout << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int n; std::cin >> n;
  while (n > 0) {
    solve(n);
    std::cin >> n;
  }
}
