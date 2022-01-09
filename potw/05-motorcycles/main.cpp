#include <bits/stdc++.h>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Ray_2 R;

struct Biker {
  int i;
  long y;
  K::FT slope;

  Biker(int i, long y, K::FT slope) : i(i), y(y), slope(slope) {}
};

void solve() {
  int n; std::cin >> n;

  std::vector<Biker> bikers;
  for (int i = 0 ; i < n; i++) {
    long y0, x1, y1; std::cin >> y0 >> x1 >> y1;
    R ray = R(P(0, y0), P(x1, y1));
    K::FT slope = ray.direction().dy() / ray.direction().dx();
    bikers.push_back(Biker(i, y0, slope));
  }
  std::sort(bikers.begin(), bikers.end(), [](const Biker &b1, const Biker &b2) { return b1.y > b2.y; });

  auto slope_comp = [](const Biker &b1, const Biker &b2) { return b1.slope > b2.slope; };
  std::priority_queue<Biker, std::vector<Biker>, decltype(slope_comp)> forever_bikers(slope_comp);

  for (Biker biker : bikers) {
    bool rides_forever = true;
    while (!forever_bikers.empty() && forever_bikers.top().slope < biker.slope) {
      if (CGAL::abs(forever_bikers.top().slope) < CGAL::abs(biker.slope)) { // biker stops
        rides_forever = false;
        break;
      } else { // other biker stops
        forever_bikers.pop();
      }
    }
    if (rides_forever) forever_bikers.push(biker);
  }

  std::vector<int> result;
  while (!forever_bikers.empty()) {
    result.push_back(forever_bikers.top().i);
    forever_bikers.pop();
  }
  std::sort(result.begin(), result.end());

  for (int i : result) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while (t--) solve();
}
