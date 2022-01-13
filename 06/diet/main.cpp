#include <bits/stdc++.h>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef int IT;
typedef CGAL::Gmpq ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

void solve(const int n, const int m) {
  std::vector<std::pair<int, int>> nutrients;
  for (int i = 0; i < n; i++) {
    int min, max; std::cin >> min >> max;
    nutrients.push_back({min, max});
  }

  std::vector<int> prices;
  std::vector<std::vector<int>> foods(m, std::vector<int>());
  for (int j = 0; j < m; j++) {
    int p; std::cin >> p;
    prices.push_back(p);

    for (int i = 0; i < n; i++) {
      int C; std::cin >> C;
      foods[j].push_back(C);
    }
  }

  Program lp (CGAL::SMALLER, true, 0, false, 0);
  int cnt = 0;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      lp.set_a(j, cnt, -foods[j][i]);
      lp.set_a(j, cnt + 1, foods[j][i]);
    }

    auto [min, max] = nutrients[i];
    lp.set_b(cnt, -min);
    lp.set_b(cnt + 1, max);

    cnt += 2;
  }

  for (int j = 0; j < m; j++) {
    lp.set_c(j, prices[j]);
  }

  Solution s = CGAL::solve_linear_program(lp, ET());
  if (s.is_infeasible()) {
    std::cout << "No such diet." << std::endl;
  } else {
    int result = std::floor(CGAL::to_double(s.objective_value()));
    std::cout << result << std::endl;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int n, m; std::cin >> n >> m;
  while (n > 0 && m > 0) {
    solve(n, m);
    std::cin >> n >> m;
  }
}
