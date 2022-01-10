#include <bits/stdc++.h>

long find_max_power(
  std::vector<std::vector<std::vector<long>>> &mem,
  const int n,
  const long H,
  const std::vector<std::pair<long, long>> &a_potions,
  const int i,
  const int j,
  const long k
) {
  if (j == 0) {
    if (k == 0) return 0;
    else return -1;
  }
  if (i < 0) return -1;
  if (k > H) return -1;

  if (mem[i][j][k] != -2) return mem[i][j][k];

  const auto [p, h] = a_potions[i];

  const long dont_use = find_max_power(mem, n, H, a_potions, i - 1, j, k);
  const long use = find_max_power(mem, n, H, a_potions, i - 1, j - 1, std::max(0l, k - h));

  long result = dont_use;
  if (use != -1) result = std::max(result, use + p);

  mem[i][j][k] = result;
  return result;
}

void solve() {
  int n, m; std::cin >> n >> m;
  long a, b; std::cin >> a >> b;
  long P, H, W; std::cin >> P >> H >> W;

  std::vector<std::pair<long, long>> a_potions;
  for (int i = 0; i < n; i++) {
    long p, h; std::cin >> p >> h;
    a_potions.push_back({p, h});
  }

  std::vector<long> b_potions;
  for (int j = 0; j < m; j++) {
    long w; std::cin >> w;
    b_potions.push_back(w);
  }
  std::sort(b_potions.begin(), b_potions.end(), std::greater<long>());

  std::vector<std::vector<std::vector<long>>>
    mem(n, std::vector<std::vector<long>>(n + 1, std::vector<long>(H + 1, -2))); // [curr. potion (index), #picked, min. happiness]
  std::vector<long> max_power;
  for (int l = 1; l <= n; l++) {
    max_power.push_back(find_max_power(mem, n, H, a_potions, n - 1, l, H));
  }

  int result = std::numeric_limits<int>::max();
  for (int i = 0; i < n; i++) {
    const int num_a_potions = i + 1;

    long power = max_power[i];
    long wit = -a * num_a_potions;
    if (power == -1) continue;

    for (int j = 0; j < m; j++) {
      const int num_b_potions = j + 1;

      power -= b;
      wit += b_potions[j];

      if (power < P) break;
      if (wit >= W) {
        result = std::min(result, num_a_potions + num_b_potions);
        break;
      }
    }
  }

  if (result == std::numeric_limits<int>::max()) {
    std::cout << -1 << std::endl;
  } else {
    std::cout << result << std::endl;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
