#include <bits/stdc++.h>

int get_l(const int n, const int i, const int j) {
  return i * n + j;
}

int rec(std::vector<int> &mem, const std::vector<int> &values, const int n, const int m, const int k, const int i, const int j) {
  if (i > j) return 0;

  int l = get_l(n, i, j);
  if (mem[l] != -1) return mem[l];

  int coins_left = j - i + 1;
  int coins_taken = n - coins_left;
  int current_player = coins_taken % m;

  int left = rec(mem, values, n, m, k, i + 1, j);
  int right = rec(mem, values, n, m, k, i, j - 1);

  int result;
  if (current_player == k) {
    result = std::max(values[i] + left, values[j] + right);
  } else {
    result = std::min(left, right);
  }

  mem[l] = result;
  return result;
}

void solve() {
  int n, m, k; std::cin >> n >> m >> k;

  std::vector<int> values;
  for (int i = 0; i < n; i++) {
    int x; std::cin >> x;
    values.push_back(x);
  }

  std::vector<int> mem(n * n, -1);
  int result = rec(mem, values, n, m, k, 0, n - 1);

  std::cout << result << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
