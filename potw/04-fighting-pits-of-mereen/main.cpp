#include <bits/stdc++.h>

const int MAX_DIFF = 10;
const int MAX_MEMORY = 3;

typedef std::array<int, MAX_MEMORY - 1> History;
typedef std::tuple<int, int, History, History> State; // {#fighters taken, p - q, last m - 1 types at north entrance, last m - 1 types at south entrance}

int get_excitement(const int diff, History history, const int type) {
  std::sort(history.begin(), history.end());
  int num_types = std::unique(history.begin(), history.end()) - history.begin();
  if (std::find(history.begin(), history.end(), type) == history.end()) num_types++;
  if (std::find(history.begin(), history.end(), -1) != history.end()) num_types--;

  int result = 1000 * num_types - (1 << std::abs(diff));
  return result;
}

History get_new_history(const int m, History history, const int type) {
  auto end = std::find(history.begin(), history.end(), -1);
  if (end == history.begin() + m - 1) {
    std::rotate(history.begin(), history.begin() + 1, history.begin() + m - 1);
    history[m - 2] = type;
  } else {
    *end = type;
  }
  return history;
}

int rec(std::map<State, int> &mem, const int k, const int m, const std::vector<int> &types, const State &state) {
  auto [fighters_taken, diff, north, south] = state;

  if (fighters_taken >= (int)types.size()) return 0;
  if (std::abs(diff) > MAX_DIFF) return -1;

  if (mem.find(state) != mem.end()) return mem[state];

  int type = types[fighters_taken];

  int result = -1;

  // choosing north
  int exc_north = get_excitement(diff + 1, north, type);
  History new_north = get_new_history(m, north, type);
  int rec_north = rec(mem, k, m, types, {fighters_taken + 1, diff + 1, new_north, south});
  if (rec_north >= 0 && exc_north >= 0) result = std::max(result, rec_north + exc_north);

  // choosing south
  int exc_south = get_excitement(diff - 1, south, type);
  History new_south = get_new_history(m, south, type);
  int rec_south = rec(mem, k, m, types, {fighters_taken + 1, diff - 1, north, new_south});
  if (rec_south >= 0 && exc_south >= 0) result = std::max(result, rec_south + exc_south);

  mem[state] = result;
  return result;
}

void solve() {
  int n, k, m; std::cin >> n >> k >> m;

  std::vector<int> types;
  for (int i = 0; i < n; i++) {
    int x; std::cin >> x;
    types.push_back(x);
  }

  std::map<State, int> mem;
  History init_north = {-1, -1};
  History init_south = {-1, -1};
  int result = rec(mem, k, m, types, {0, 0, init_north, init_south});

  std::cout << result << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
