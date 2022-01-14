#include <bits/stdc++.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;

void solve() {
  int m, n; std::cin >> m >> n;

  std::vector<std::pair<P, int>> participants;
  for (int i = 0; i < m; i++) {
    int x, y, r; std::cin >> x >> y >> r;
    participants.push_back({P(x, y), r});
  }

  int h; std::cin >> h;

  std::vector<P> lamps;
  for (int i = 0; i < n; i++) {
    int x, y; std::cin >> x >> y;
    lamps.push_back(P(x, y));
  }

  Triangulation t;
  t.insert(lamps.begin(), lamps.end());

  std::vector<int> survival_time(m, n);
  bool survival_required = false;
  for (int i = 0; i < m; i++) {
    const auto [p, r] = participants[i];
    const K::FT min_dist = r + h;

    if (survival_required) {
      const P lamp = t.nearest_vertex(p)->point();

      if (CGAL::squared_distance(p, lamp) >= min_dist * min_dist) {
        std::cout << i << " ";
      }
    } else {
      for (int j = 0; j < n; j++) {
        const P lamp = lamps[j];

        if (CGAL::squared_distance(p, lamp) < min_dist * min_dist) {
          survival_time[i] = j;
          break;
        }
      }

      if (survival_time[i] == n) {
        survival_required = true;
        std::cout << i << " ";
      }
    }
  }

  if (!survival_required) {
    int winning_time = 0;
    std::vector<int> winners;
    for (int i = 0; i < m; i++) {
      if (survival_time[i] > winning_time) {
        winning_time = survival_time[i];
        winners.clear();
        winners.push_back(i);
      } else if (survival_time[i] == winning_time) {
        winners.push_back(i);
      }
    }

    for (const int i : winners) std::cout << i << " ";
  }

  std::cout << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
