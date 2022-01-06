#include <bits/stdc++.h>

int get_k(const int n, const int i, const int j) {
  return i * n + j;
}

int rec(std::vector<int> &mem, const std::vector<int> &values, const int n, const int i, const int j) {
  int coins_left = j - i + 1;
  int coins_taken = n - coins_left;

  if (coins_left == 0) return 0;

  int k = get_k(n, i, j);
  if (mem[k] != -1) return mem[k];

  int take_left = rec(mem, values, n, i + 1, j);
  int take_right = rec(mem, values, n, i, j - 1);
  int result;
  if (coins_taken % 2 == 0) { // our turn
    result = std::max(values[i] + take_left, values[j] + take_right);
  } else { // their turn
    result = std::min(take_left, take_right);
  }

  mem[get_k(n, i, j)] = result;
  return result;
}

void solve() {
  int n; std::cin >> n;

  std::vector<int> values;
  for (int i = 0; i < n; i++) {
    int v; std::cin >> v;
    values.push_back(v);
  }

  std::vector<int> mem(n * n, -1);
  int result = rec(mem, values, n, 0, n - 1);

  std::cout << result << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
