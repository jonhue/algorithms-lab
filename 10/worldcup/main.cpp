#include <bits/stdc++.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;

typedef int IT;
typedef CGAL::Gmpz ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

typedef std::tuple<P, int, int> Warehouse; // {location, supply, alcohol (percent)}
typedef std::tuple<P, int, int> Stadium; // {location, demand, alcohol limit}
typedef std::pair<P, K::FT> ContourLine; // {center, radius}

int get_var(const int m, const int i, const int j) {
  return i * m + j;
}

void solve() {
  int n, m, c; std::cin >> n >> m >> c;

  std::vector<P> points;

  std::vector<Warehouse> warehouses;
  for (int i = 0; i < n; i++) {
    int x, y, s, a; std::cin >> x >> y >> s >> a;
    P p = P(x, y);
    points.push_back(p);
    warehouses.push_back({p, s, a});
  }

  std::vector<Stadium> stadiums;
  for (int j = 0; j < m; j++) {
    int x, y, d, u; std::cin >> x >> y >> d >> u;
    P p = P(x, y);
    points.push_back(p);
    stadiums.push_back({p, d, u});
  }

  std::vector<std::vector<int>> revenues(n, std::vector<int>());
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int r; std::cin >> r;
      revenues[i].push_back(r);
    }
  }

  std::vector<ContourLine> contour_lines;
  for (int k = 0; k < c; k++) {
    int x, y; std::cin >> x >> y;
    K::FT r; std::cin >> r;
    contour_lines.push_back({P(x, y), r});
  }

  Triangulation t;
  t.insert(points.begin(), points.end());

  std::vector<ContourLine> used_contour_lines;
  for (const auto [p, r] : contour_lines) {
    if (CGAL::squared_distance(p, t.nearest_vertex(p)->point()) <= r * r) {
      used_contour_lines.push_back({p, r});
    }
  }

  std::vector<std::vector<int>> traverses(n, std::vector<int>());
  for (int i = 0; i < n; i++) {
    const auto [w, _s, _a] = warehouses[i];
    for (int j = 0; j < m; j++) {
      const auto [s, _d, _u] = stadiums[j];
      int t = 0;
      for (const auto [p, r] : used_contour_lines) {
        const bool contains_w = CGAL::squared_distance(p, w) <= r * r;
        const bool contains_s = CGAL::squared_distance(p, s) <= r * r;
        if ((contains_w && !contains_s) || (!contains_w && contains_s)) t++;
      }
      traverses[i].push_back(t);
    }
  }

  Program lp (CGAL::SMALLER, true, 0, false, 0);
  int cnt = 0;

  for (int i = 0; i < n; i++) {
    const auto [_w, s, _a] = warehouses[i];
    for (int j = 0; j < m; j++) {
      lp.set_a(get_var(m, i, j), cnt, 1);
    }
    lp.set_b(cnt, s);
    cnt++;
  }

  for (int j = 0; j < m; j++) {
    const auto [_s, d, _u] = stadiums[j];
    for (int i = 0; i < n; i++) {
      lp.set_a(get_var(m, i, j), cnt, 1);
    }
    lp.set_b(cnt, d);
    cnt++;
    for (int i = 0; i < n; i++) {
      lp.set_a(get_var(m, i, j), cnt, -1);
    }
    lp.set_b(cnt, -d);
    cnt++;
  }

  for (int j = 0; j < m; j++) {
    const auto [_s, _d, u] = stadiums[j];
    for (int i = 0; i < n; i++) {
      const auto [_w, _s, a] = warehouses[i];
      lp.set_a(get_var(m, i, j), cnt, a);
    }
    lp.set_b(cnt, 100 * u);
    cnt++;
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      const int r = revenues[i][j];
      const int t = traverses[i][j];
      lp.set_c(get_var(m, i, j), - 100 * r + t);
    }
  }

  Solution s = CGAL::solve_linear_program(lp, ET());
  if (s.is_infeasible()) {
    std::cout << "RIOT!" << std::endl;
  } else {
    const int result = std::floor(- CGAL::to_double(s.objective_value()) / 100);
    std::cout << result << std::endl;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
