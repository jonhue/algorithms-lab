#include <bits/stdc++.h>

const int MAX_SIZE = 2000000;
const int OFFSET = 100;

int get_i(const int x) {
  return MAX_SIZE / 2 + x - 1;
}

int get(const std::vector<int> &xs, const int x) {
  if (std::abs(x) > MAX_SIZE / 2) return 0;
  return xs[get_i(x)];
}

void solve() {
  int n; std::cin >> n;

  std::vector<int> xs(MAX_SIZE, 0);
  int L = std::numeric_limits<int>::max();
  int R = std::numeric_limits<int>::min();
  for (int i = 0; i < n; i++) {
    int x; std::cin >> x;
    xs[get_i(x)] = 1;

    if (x < L) L = x;
    if (x > R) R = x;
  }

  std::deque<int> parasols;
  for (int x = L; x < L + OFFSET; x++) {
    if (get(xs, x) == 1) parasols.push_back(x);
  }

  int max_parasols = 0, min_max_dist = OFFSET;
  std::vector<int> opt;

  for (int x = L; x <= R; x++) {
    if (get(xs, x + OFFSET) == 1) parasols.push_back(x + OFFSET);

    int max_dist = std::max(std::abs(x - parasols.front()), std::abs(x - parasols.back()));

    if ((int)parasols.size() > max_parasols) {
      max_parasols = parasols.size();
      min_max_dist = max_dist;
      opt.clear();
      opt.push_back(x);
    } else if ((int)parasols.size() == max_parasols) {
      if (max_dist < min_max_dist) {
        min_max_dist = max_dist;
        opt.clear();
        opt.push_back(x);
      } else if (max_dist == min_max_dist) {
        opt.push_back(x);
      }
    }

    if (get(xs, x - OFFSET)) parasols.pop_front();
  }

  std::cout << max_parasols << " " << min_max_dist << "\n";
  for (int x : opt) std::cout << x << " ";
  std::cout << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
