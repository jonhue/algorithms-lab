#include <bits/stdc++.h>

typedef std::tuple<int, int, int> Result; // {repaired, covered, waiting}

Result rec(const std::vector<std::vector<int>> &successors, const std::vector<int> &costs, const int i) {
  int waiting_sum = 0;
  int covered_sum = 0;
  int min_difference_between_repaired_and_covered = std::numeric_limits<int>::max();
  for (const int j : successors[i]) {
    const auto [repaired, covered, waiting] = rec(successors, costs, j);

    waiting_sum += waiting;
    covered_sum += covered;
    min_difference_between_repaired_and_covered = std::min(min_difference_between_repaired_and_covered, repaired - covered);
  }

  const int repaired = costs[i] + waiting_sum;
  const int covered = std::min(repaired, covered_sum + min_difference_between_repaired_and_covered);
  const int waiting = std::min(covered, covered_sum);
  return {repaired, covered, waiting};
}

void solve() {
  int n; std::cin >> n;

  std::vector<std::vector<int>> successors(n, std::vector<int>());
  for (int k = 0; k < n - 1; k++) {
    int i, j; std::cin >> i >> j;
    successors[i].push_back(j);
  }

  std::vector<int> costs;
  for (int i = 0; i < n; i++) {
    int c; std::cin >> c;
    costs.push_back(c);
  }

  const auto [repaired, covered, waiting] = rec(successors, costs, 0);
  int result = std::min(repaired, covered);

  std::cout << result << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
