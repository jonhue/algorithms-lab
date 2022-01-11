#include <bits/stdc++.h>

typedef std::pair<long, long> Movement; // {distance, time}

void compute_movements_subsets(std::vector<Movement> &result, const long T, const long s, const std::vector<Movement> &movements, const int i, const long d, const long t) {
  if (i == (int)movements.size()) {
    if (t < T) { // prune results
      result.push_back({d, t});
    }
  } else {
    const auto [new_d, new_t] = movements[i];

    compute_movements_subsets(result, T, s, movements, i + 1, d, t); // do not use movement
    compute_movements_subsets(result, T, s, movements, i + 1, d + new_d + s, t + new_t); // use movement
  }
}

bool can_be_reached_in_time(const int n, const long D, const long T, const std::vector<Movement> &movements, const long s) {
  const auto a_movements = *new std::vector<Movement>(movements.begin(), movements.begin() + std::floor(n / 2));
  const auto b_movements = *new std::vector<Movement>(movements.begin() + std::ceil(n / 2), movements.end());

  std::vector<Movement> a_subsets;
  std::vector<Movement> b_subsets;
  compute_movements_subsets(a_subsets, T, s, a_movements, 0, 0, 0);
  compute_movements_subsets(b_subsets, T, s, b_movements, 0, 0, 0);

  // sort movements by time (ascending)
  std::sort(b_subsets.begin(), b_subsets.end(), [](const auto &a, const auto &b) { return a.second < b.second; });

  // propagate distances from smaller durations to larger durations
  long max_b_distance = 0;
  for (int i = 0; i < (int)b_subsets.size(); i++) {
    auto [d, t] = b_subsets[i];
    max_b_distance = std::max(max_b_distance, d);
    b_subsets[i] = {max_b_distance, t};
  }

  long max_distance = 0;
  for (auto [d1, t1] : a_subsets) {
    int l = 0, r = b_subsets.size() - 1;
    while (l < r) {
      int k = std::ceil((l + r) / 2.0);
      auto [d2, t2] = b_subsets[k];

      if (t1 + t2 < T) {
        l = k;
      } else {
        r = k - 1;
      }
    }

    auto [d2, t2] = b_subsets[l];
    max_distance = std::max(max_distance, d1 + d2);
  }

  return max_distance >= D;
}

void solve() {
  int n, m; std::cin >> n >> m;
  long D, T; std::cin >> D >> T;

  std::vector<Movement> movements;
  for (int i = 0; i < n; i++) {
    long d, t; std::cin >> d >> t;
    movements.push_back({d, t});
  }
  std::random_shuffle(movements.begin(), movements.end());

  std::vector<long> gulps;
  for (int j = 0; j < m; j++) {
    long s; std::cin >> s;
    gulps.push_back(s);
  }

  int l = -1, r = m - 1;
  bool is_reached;
  while (l <= r) {
    int k = std::floor((l + r) / 2);
    if (k == -1) {
      is_reached = can_be_reached_in_time(n, D, T, movements, 0);
    } else {
      is_reached = can_be_reached_in_time(n, D, T, movements, gulps[k]);
    }

    if (is_reached) {
      r = k - 1;
    } else {
      l = k + 1;
    }
  }

  if (!is_reached && l >= m) {
    std::cout << "Panoramix captured" << std::endl;
  } else {
    std::cout << l + 1 << std::endl;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
