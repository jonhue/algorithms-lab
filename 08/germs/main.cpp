#include <bits/stdc++.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;

long dist_to_time(const K::FT distance) {
  return std::ceil(std::sqrt(distance - 0.5));
}

void solve(const int n) {
  int l, b, r, t; std::cin >> l >> b >> r >> t;

  std::vector<P> bacteria;
  for (int i = 0; i < n; i++) {
    int x, y; std::cin >> x >> y;
    bacteria.push_back(P(x, y));
  }

  Triangulation dt;
  dt.insert(bacteria.begin(), bacteria.end());

  std::vector<K::FT> distances;
  for (auto v = dt.finite_vertices_begin(); v != dt.finite_vertices_end(); v++) {
    const K::FT x = v->point().x();
    const K::FT y = v->point().y();
    K::FT min_dist = std::min({std::abs(l - x), std::abs(r - x), std::abs(t - y), std::abs(b - y)});

    K::FT min_squared_dist = std::numeric_limits<double>::max();
    auto u = dt.incident_vertices(v);
    if (u != 0) {
      do {
        if (dt.is_infinite(u)) continue;
        const K::FT squared_dist = CGAL::squared_distance(v->point(), u->point());
        min_squared_dist = std::min(min_squared_dist, squared_dist);
      } while (++u != dt.incident_vertices(v));
    }

    distances.push_back(std::min(min_dist, std::sqrt(min_squared_dist) / 2));
  }

  std::sort(distances.begin(), distances.end());

  std::cout
    << dist_to_time(distances[0]) << " "
    << dist_to_time(distances[std::floor(n / 2)]) << " "
    << dist_to_time(distances[n - 1]) << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int n; std::cin >> n;
  while (n > 0) {
    solve(n);
    std::cin >> n;
  }
}
