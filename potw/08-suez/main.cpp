#include <bits/stdc++.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;

typedef K::FT IT;
typedef CGAL::Gmpq ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

void solve() {
  int n, m, h, w; std::cin >> n >> m >> h >> w;

  std::vector<P> new_positions;
  for (int i = 0; i < n; i++) {
    int x, y; std::cin >> x >> y;
    new_positions.push_back(P(x, y));
  }

  std::vector<P> old_positions;
  for (int i = 0; i < m; i++) {
    int x, y; std::cin >> x >> y;
    old_positions.push_back(P(x, y));
  }

  Program lp (CGAL::SMALLER, true, 1, false, 0);
  int cnt = 0;

  // old posters
  for (int i = 0; i < n; i++) {
    const P p1 = new_positions[i];

    K::FT b = std::numeric_limits<long>::max();
    for (int j = 0; j < m; j++) {
      const P p2 = old_positions[j];

      const K::FT dx = std::abs(p1.x() - p2.x());
      const K::FT dy = std::abs(p1.y() - p2.y());

      b = std::min(b, std::max(2 * dx / w - 1, 2 * dy / h - 1));
    }

    lp.set_a(i, cnt, 1);
    lp.set_b(cnt, b);
    cnt++;
  }

  // new posters
  for (int i = 0; i < n ; i++) {
    const P p1 = new_positions[i];

    for (int j = i + 1; j < n; j++) {
      const P p2 = new_positions[j];

      const K::FT dx = std::abs(p1.x() - p2.x());
      const K::FT dy = std::abs(p1.y() - p2.y());

      lp.set_a(i, cnt, 1);
      lp.set_a(j, cnt, 1);
      lp.set_b(cnt, std::max(2 * dx / w, 2 * dy / h));
      cnt++;
    }
  }

  for (int i = 0; i < n; i++) {
    lp.set_c(i, - 2 * (w + h));
  }

  Solution s = CGAL::solve_linear_program(lp, ET());
  long result = std::ceil(-CGAL::to_double(s.objective_value()));

  std::cout << result << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
