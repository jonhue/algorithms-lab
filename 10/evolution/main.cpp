#include <bits/stdc++.h>

typedef std::pair<int, int> Query; // {index, age}

void dfs(
  std::vector<std::string> &results,
  const std::map<std::string, int> &ages,
  const std::map<std::string, std::vector<std::string>> &successors,
  const std::map<std::string, std::vector<Query>> &queries,
  std::vector<std::string> &path,
  const std::string s
) {
  path.push_back(s);

  if (queries.find(s) != queries.end()) {
    for (const auto [i, b] : queries.at(s)) {
      int l = 0, r = path.size();
      while (l < r) {
        const int m = std::floor((l + r) / 2.0);
        if (ages.at(path[m]) > b) {
          l = m + 1;
        } else {
          r = m;
        }
      }
      results[i] = path[l];
    }
  }

  if (successors.find(s) != successors.end()) {
    for (const auto t : successors.at(s)) dfs(results, ages, successors, queries, path, t);
  }

  path.pop_back();
}

void solve() {
  int n, q; std::cin >> n >> q;

  std::map<std::string, int> ages;
  std::string luca;
  int max_age = -1;
  for (int i = 0; i < n; i++) {
    std::string s; std::cin >> s;
    int a; std::cin >> a;
    ages[s] = a;
    if (a > max_age) {
      max_age = a;
      luca = s;
    }
  }

  std::map<std::string, std::vector<std::string>> successors;
  for (int i = 0; i < n - 1; i++) {
    std::string s, p; std::cin >> s >> p;
    if (successors.find(p) != successors.end()) {
      successors[p].push_back(s);
    } else {
      successors.insert({p, {s}});
    }
  }

  std::map<std::string, std::vector<Query>> queries;
  for (int i = 0; i < q; i++) {
    std::string s; std::cin >> s;
    int b; std::cin >> b;
    if (queries.find(s) != queries.end()) {
      queries[s].push_back({i, b});
    } else {
      queries.insert({s, {{i, b}}});
    }
  }

  std::vector<std::string> results(q, "");
  std::vector<std::string> path;
  dfs(results, ages, successors, queries, path, luca);

  for (const auto s : results) {
    std::cout << s << " ";
  }
  std::cout << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
