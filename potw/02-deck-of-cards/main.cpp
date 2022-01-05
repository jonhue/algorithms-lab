#include <bits/stdc++.h>

void solve() {
  int n, k; std::cin >> n >> k;

  std::vector<int> vs;
  for (int i = 0; i < n; i++) {
    int v; std::cin >> v;
    vs.push_back(v);
  }

  int opt = std::numeric_limits<int>::max();
  int i_opt = -1, j_opt = -1;

  int i = 0, j = 0;
  int sum = vs[0];

  while (j < n) {
    int val = std::abs(k - sum);
    if (val < opt) {
      opt = val;
      i_opt = i;
      j_opt = j;
    }
    if (val == 0) break;

    if (k > sum) {
      j++;
      if (j < n) sum += vs[j];
    } else { // k < sum
      sum -= vs[i];
      i++;

      if (i > j) {
        j++;
        if (j < n) sum += vs[j];
      }
    }
  }

  std::cout << i_opt << " " << j_opt << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
