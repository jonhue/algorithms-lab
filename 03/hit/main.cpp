#include <bits/stdc++.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;

void solve(const int n) {
  long x, y, a, b; std::cin >> x >> y >> a >> b;

  P start = P(x, y);
  R ray = R(start, P(a, b));

  std::vector<S> segments;
  for (int i = 0; i < n; i++) {
    long r, s, t, u; std::cin >> r >> s >> t >> u;
    segments.push_back(S(P(r, s), P(t, u)));
  }

  for (auto segment : segments) {
    if (CGAL::do_intersect(ray, segment)) {
      std::cout << "yes" << std::endl;
      return;
    }
  }

  std::cout << "no" << std::endl;
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int n; std::cin >> n;
  while (n > 0) {
    solve(n);
    std::cin >> n;
  }
}
