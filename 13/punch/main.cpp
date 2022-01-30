#include <bits/stdc++.h>

typedef std::tuple<int, int, bool> MemEntry; // {min cost, max #drinks, uses i-th drink}
typedef std::vector<std::vector<MemEntry>> Mem; // number of drinks (i), number of liters (j)
typedef std::pair<int, int> Drink; // {cost, volume}

MemEntry rec(Mem &mem, const std::vector<Drink> &drinks, const int i, const int j) {
  if (j == 0) return {0, 0, false};
  if (i == 0) return {std::numeric_limits<int>::max(), 0, false};

  if (std::get<0>(mem[i][j]) != -1) return mem[i][j];

  const auto [c, v] = drinks[i - 1];

  const auto [cost1, no1, _used1] = rec(mem, drinks, i - 1, j); // do not use beverage i
  const auto [cost2r, no2r, used2] = rec(mem, drinks, i, std::max(0, j - v)); // use beverage i
  const int cost2 = cost2r + c;
  const int no2 = no2r + (used2 ? 0 : 1);

  MemEntry result;
  if (cost1 < cost2 || (cost1 == cost2 && no1 >= no2)) {
    result = {cost1, no1, false};
  } else {
    result = {cost2, no2, true};
  }

  mem[i][j] = result;
  return result;
}

void solve() {
  int n, k; std::cin >> n >> k;

  std::vector<Drink> drinks;
  for (int i = 0; i < n; i++) {
    int c, v; std::cin >> c >> v;
    drinks.push_back({c, v});
  }

  Mem mem(n + 1, std::vector<MemEntry>(k + 1, {-1, -1, false}));
  const auto [cost, no, _used] = rec(mem, drinks, n, k);

  std::cout << cost << " " << no << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
