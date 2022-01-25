#include <bits/stdc++.h>

void solve() {
  int n, k, w; std::cin >> n >> k >> w;

  std::vector<int> men_required;
  for (int i = 0; i < n; i++) {
    int c; std::cin >> c;
    men_required.push_back(c);
  }

  std::vector<std::vector<int>> waterways(w, std::vector<int>());
  for (int i = 0; i < w; i++) {
    int l; std::cin >> l;
    for (int j = 0; j < l; j++) {
      int r; std::cin >> r;
      waterways[i].push_back(r);
    }
  }

  int result = 0;

  // find maximum number of islands on single waterway
  for (const auto &waterway : waterways) {
    int l = 0, u = 0;
    int men = men_required[waterway[0]];

    while (u < (int)waterway.size()) {
      if (men == k) {
        result = std::max(result, u - l + 1);
      }

      if (men < k) {
        u++;
        if (u >= (int)waterway.size()) break;
        men += men_required[waterway[u]];
      } else if (men >= k) {
        men -= men_required[waterway[l]];
        l++;

        if (l > u) {
          u++;
          if (u >= (int)waterway.size()) break;
          men += men_required[waterway[u]];
        }
      }
    }
  }

  // find maximum number of islands on two waterways connected at Pike
  std::vector<int> max_islands_by_men(std::max(0, k - men_required[0] + 1), -1); // starting from (not including) Pike
  for (const auto &waterway : waterways) {
    // combine with best previous waterways
    int men = 0;
    for (int j = 1; j < (int)waterway.size(); j++) {
      men += men_required[waterway[j]];
      if (men > k - men_required[0]) break;
      if (max_islands_by_men[k - men - men_required[0]] < 0) continue;
      result = std::max(result, j + max_islands_by_men[k - men - men_required[0]] + 1);
    }

    // add waterway to memory
    men = 0;
    for (int j = 1; j < (int)waterway.size(); j++) {
      men += men_required[waterway[j]];
      if (men > k - men_required[0]) break;
      max_islands_by_men[men] = std::max(max_islands_by_men[men], j);
    }
  }

  std::cout << result << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
