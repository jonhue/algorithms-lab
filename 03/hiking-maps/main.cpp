#include <bits/stdc++.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Line_2 L;

bool triangle_contains_point(const std::array<L, 3> &triangle, const P &point) {
  for (int i = 0; i < 3; i++) {
    if (triangle[i].has_on_negative_side(point)) return false;
  }
  return true;
}

void solve() {
  int m, n; std::cin >> m >> n;

  std::vector<P> points;
  for (int i = 0; i < m; i++) {
    int x, y; std::cin >> x >> y;
    points.push_back(P(x, y));
  }

  std::vector<std::array<L, 3>> triangles;
  for (int i = 0; i < n; i++) {
    std::array<P, 6> points;
    for (int j = 0; j < 6; j++) {
      int x, y; std::cin >> x >> y;
      points[j] = P(x, y);
    }

    std::array<L, 3> lines;
    for (int j = 0; j < 3; j++) {
      P a = points[2 * j];
      P b = points[2 * j + 1];
      P c = points[(2 * j + 2) % 6];
      if (CGAL::right_turn(a, b, c)) std::swap(a, b);

      lines[j] = L(a, b);
    }

    triangles.push_back(lines);
  }

  std::vector<std::vector<int>> map_contains_segment(n, std::vector<int>(m - 1, 0));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m - 1; j++) {
      if (triangle_contains_point(triangles[i], points[j]) &&
          triangle_contains_point(triangles[i], points[j + 1])) {
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
