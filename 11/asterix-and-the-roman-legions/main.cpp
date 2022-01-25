#include <bits/stdc++.h>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpz ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

typedef std::tuple<int, int, int, int> Legion; // {a, b, c, v}

void solve() {
  int xs, ys, n; std::cin >> xs >> ys >> n;

  std::vector<Legion> legions;
  for (int i = 0; i < n; i++) {
    int a, b, c, v; std::cin >> a >> b >> c >> v;
    legions.push_back({a, b, c, v});
  }

  Program lp (CGAL::SMALLER, false, 0, false, 0);
  int cnt = 0;

  const int X = 0;
  const int Y = 1;
  const int T = 2; lp.set_l(T, true, 0);

  for (const auto [a, b, c, v] : legions) {
    const int Z = std::sqrt(a * a + b * b);

    const int ps = a * xs + b * ys + c;
    if (ps >= 0) {
      // orientation
      lp.set_a(X, cnt, -a);
      lp.set_a(Y, cnt, -b);
      lp.set_b(cnt, c);

      // time
      lp.set_a(T, cnt, v * Z);
      lp.set_a(X, cnt, -a);
      lp.set_a(Y, cnt, -b);
      lp.set_b(cnt, c);
      cnt++;
    } else {
      // orientation
      lp.set_a(X, cnt, a);
      lp.set_a(Y, cnt, b);
      lp.set_b(cnt, -c);

      // time
      lp.set_a(T, cnt, v * Z);
      lp.set_a(X, cnt, a);
      lp.set_a(Y, cnt, b);
      lp.set_b(cnt, -c);
    }
    cnt++;
  }

  lp.set_c(T, -1);

  Solution s = CGAL::solve_linear_program(lp, ET());
  int result = std::floor(CGAL::to_double(-s.objective_value()));

  std::cout << result << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
