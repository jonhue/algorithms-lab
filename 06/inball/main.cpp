#include <bits/stdc++.h>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpz ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

void solve(const int n) {
  int d; std::cin >> d;

  std::vector<std::vector<int>> as(n, std::vector<int>());
  std::vector<int> bs;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < d; j++) {
      int a; std::cin >> a;
      as[i].push_back(a);
    }

    int b; std::cin >> b;
    bs.push_back(b);
  }

  Program lp (CGAL::SMALLER, false, 0, false, 0);

  const int R = 0;
  lp.set_l(R, true, 0);

  for (int i = 0; i < n; i++) {
    int sum_squares = 0;
    for (int j = 0; j < d; j++) {
      sum_squares += as[i][j] * as[i][j];
    }
    int norm = std::sqrt(sum_squares); // assumed to be an int

    lp.set_a(R, i, norm);
    for (int j = 0; j < d; j++) {
      lp.set_a(j + 1, i, -as[i][j]);
    }
    lp.set_b(i, bs[i]);
  }

  lp.set_c(R, -1);

  Solution s = CGAL::solve_linear_program(lp, ET());
  if (s.is_infeasible()) {
    std::cout << "none" << std::endl;
  } else if (s.is_unbounded()) {
    std::cout << "inf" << std::endl;
  } else {
    int result = std::floor(-CGAL::to_double(s.objective_value()));
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
