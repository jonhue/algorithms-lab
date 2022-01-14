#include <bits/stdc++.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;

void solve(const int n) {
  std::vector<P> restaurants;
  for (int i = 0; i < n; i++) {
    int x, y; std::cin >> x >> y;
    restaurants.push_back(P(x, y));
  }

  Triangulation t;
  t.insert(restaurants.begin(), restaurants.end());

  int m; std::cin >> m;
  for (int i = 0; i < m; i++) {
    int x, y; std::cin >> x >> y;
    P p = P(x, y);

    P nearest_p = t.nearest_vertex(p)->point();
    K::FT distance = CGAL::squared_distance(p, nearest_p);

    long result = CGAL::to_double(distance);
    std::cout << result << std::endl;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int n; std::cin >> n;
  while (n > 0) {
    solve(n);
    std::cin >> n;
  }
}
