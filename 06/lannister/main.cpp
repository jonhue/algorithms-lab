#include <bits/stdc++.h>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef long IT;
typedef CGAL::Gmpz ET;

typedef CGAL::Quadratic_program<IT> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

void solve() {
  int n, m; std::cin >> n >> m;
  long s; std::cin >> s;

  std::vector<std::pair<int, int>> nobles;
  long nobles_x = 0, nobles_y = 0;
  for (int i = 0; i < n; i++) {
    int x, y; std::cin >> x >> y;
    nobles.push_back({x, y});
    nobles_x += x;
    nobles_y += y;
  }

  std::vector<std::pair<int, int>> commoners;
  long commoners_x = 0, commoners_y = 0;
  for (int j = 0; j < m; j++) {
    int x, y; std::cin >> x >> y;
    commoners.push_back({x, y});
    commoners_x += x;
    commoners_y += y;
  }

  Program lp (CGAL::SMALLER, false, 0, false, 0);
  int cnt = 0;

  const int L = 0; lp.set_l(L, true, 0);
  const int B = 1;
  const int C = 2;
  const int D = 3;

  // Cersei
  for (auto [x, y] : nobles) {
    lp.set_a(B, cnt, y);
    lp.set_a(C, cnt, 1);
    lp.set_b(cnt, -x);
    cnt++;
  }
  for (auto [x, y] : commoners) {
    lp.set_a(B, cnt, -y);
    lp.set_a(C, cnt, -1);
    lp.set_b(cnt, x);
    cnt++;
  }

  Solution sol = CGAL::solve_linear_program(lp, ET());
  if (sol.is_infeasible()) {
    std::cout << "Yuck!" << std::endl;
    return;
  }

  // Tywin
  if (s != -1) {
    lp.set_a(B, cnt, commoners_y - nobles_y);
    lp.set_a(C, cnt, m - n);
    lp.set_b(cnt, s - (commoners_x - nobles_x));
    cnt++;

    sol = CGAL::solve_linear_program(lp, ET());
    if (sol.is_infeasible()) {
      std::cout << "Bankrupt!" << std::endl;
      return;
    }
  }

  // Jamie
  for (auto [x, y] : nobles) {
    lp.set_a(L, cnt, -1);
    lp.set_a(B, cnt, -x);
    lp.set_a(D, cnt, -1);
    lp.set_b(cnt, -y);
    cnt++;

    lp.set_a(L, cnt, -1);
    lp.set_a(B, cnt, x);
    lp.set_a(D, cnt, 1);
    lp.set_b(cnt, y);
    cnt++;
  }
  for (auto [x, y] : commoners) {
    lp.set_a(L, cnt, -1);
    lp.set_a(B, cnt, -x);
    lp.set_a(D, cnt, -1);
    lp.set_b(cnt, -y);
    cnt++;

    lp.set_a(L, cnt, -1);
    lp.set_a(B, cnt, x);
    lp.set_a(D, cnt, 1);
    lp.set_b(cnt, y);
    cnt++;
  }

  lp.set_c(L, 1);

  sol = CGAL::solve_linear_program(lp, ET());
  long result = std::ceil(CGAL::to_double(sol.objective_value()));

  std::cout << result << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
