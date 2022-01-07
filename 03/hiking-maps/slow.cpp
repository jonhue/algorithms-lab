#include <bits/stdc++.h>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Triangle_2 T;
typedef K::Line_2 L;

void solve() {
  int m, n; std::cin >> m >> n;

  std::vector<P> points;
  for (int i = 0; i < m; i++) {
    int x, y; std::cin >> x >> y;
    points.push_back(P(x, y));
  }

  std::vector<T> triangles;
  for (int i = 0; i < n; i++) {
    std::array<L, 3> lines;
    for (int j = 0; j < 3; j++) {
      int a, b, c, d; std::cin >> a >> b >> c >> d;
      lines[j] = L(P(a, b), P(c, d));
    }

    std::array<P, 3> vertices;
    for (int j = 0; j < 3; j++) {
      auto o = CGAL::intersection(lines[j], lines[(j + 1) % 3]);
      if (const P* op = boost::get<P>(&*o))
        vertices[j] = *op;
      else throw std::runtime_error("unexpected intersection");
    }

    triangles.push_back(T(vertices[0], vertices[1], vertices[2]));
  }

  std::vector<std::vector<int>> map_contains_segment(n, std::vector<int>(m - 1, 0));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m - 1; j++) {
      if (triangles[i].bounded_side(points[j]) != CGAL::Bounded_side::ON_UNBOUNDED_SIDE &&
          triangles[i].bounded_side(points[j + 1]) != CGAL::Bounded_side::ON_UNBOUNDED_SIDE) {
        map_contains_segment[i][j] = 1;
      }
    }
  }

  int l = 0, r = 0;
  int k = n;

  std::vector<int> contained_segments = map_contains_segment[0];
  while (r < n) {
    while (std::all_of(contained_segments.begin(), contained_segments.end(), [](const int count) { return count > 0; })) {
      if (r - l + 1 < k) k = r - l + 1;

      // l can never be equals to r!
      for (int j = 0; j < m - 1; j++) {
        contained_segments[j] -= map_contains_segment[l][j];
      }
      l++;
    }

    r++; if (r >= n) break;
    for (int j = 0; j < m - 1; j++) {
      contained_segments[j] += map_contains_segment[r][j];
    }
  }

  std::cout << k << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
