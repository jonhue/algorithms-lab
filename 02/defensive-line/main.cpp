#include <bits/stdc++.h>

int get_k(const int n, const int i, const int j) {
  return (i - 1) * n + (j - 1);
}

// i: #attackers, j: #defenders
int rec(std::vector<int> &mem, const std::vector<int> &interval_lengths, const int n, const int i, const int j) {
  if (i <= 0) return 0;
  if (j <= 0) return -1;

  int k = get_k(n, i, j);
  if (mem[k] != -2) return mem[k];

  int no_attack = rec(mem, interval_lengths, n, i, j - 1);

  int interval_length = interval_lengths[j - 1];
  int attack = rec(mem, interval_lengths, n, i - 1, j - interval_length);

  int result;
  if (interval_length > 0 && attack != -1) {
    result = std::max(interval_length + attack, no_attack);
  } else {
    result = no_attack;
  }

  mem[k] = result;
  return result;
}

void solve() {
  int n, m, k; std::cin >> n >> m >> k;

  std::vector<int> values;
  for (int i = 0; i < n; i++) {
    int v; std::cin >> v;
    values.push_back(v);
  }

  std::vector<int> interval_lengths(n, 0);
  int cum_value = 0;
  int i = 0;
  for (int j = 0; j < n; j++) {
    cum_value += values[j];

    while (cum_value > k) {
      cum_value -= values[i];
      i++;
    }

    if (cum_value == k) interval_lengths[j] = j - i + 1;
  }

  std::vector<int> mem(m * n, -2);
  int result = rec(mem, interval_lengths, n, m, n);

  if (result != -1) {
    std::cout << result << std::endl;
  } else {
    std::cout << "fail" << std::endl;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
   while (t--) solve();
}
