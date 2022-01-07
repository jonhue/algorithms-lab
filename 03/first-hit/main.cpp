#include <bits/stdc++.h>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2 P;
typedef K::Segment_2 S;
typedef K::Ray_2 R;

double floor_to_double(const K::FT& x) {
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

void solve(const int n) {
  long x, y, a, b; std::cin >> x >> y >> a >> b;

  std::vector<S> segments;
  for (int i = 0; i < n; i++) {
    long r, s, t, u; std::cin >> r >> s >> t >> u;
    segments.push_back(S(P(r, s), P(t, u)));
  }
  std::random_shuffle(segments.begin(), segments.end());

  const P start = P(x, y);
  const R ray = R(start, P(a, b));

  bool clipped = false;
  S clipped_ray = S(start, P(a, b));
  for (auto segment : segments) {
    if ((!clipped && CGAL::do_intersect(ray, segment)) || (clipped && CGAL::do_intersect(clipped_ray, segment))) {
      auto o = clipped ? CGAL::intersection(clipped_ray, segment) : CGAL::intersection(ray, segment);
      if (const P* op = boost::get<P>(&*o)) {
        clipped_ray = S(start, *op);
      } else if (const S* os = boost::get<S>(&*o)) {
        if (CGAL::squared_distance(start, os->source()) < CGAL::squared_distance(start, os->target())) {
          clipped_ray = S(start, os->source());
        } else {
          clipped_ray = S(start, os->target());
        }
      } else throw std::runtime_error("strange segment intersection");
      clipped = true;
    }
  }

  if (!clipped) {
    std::cout << "no" << std::endl;
  } else {
    std::cout << floor_to_double(clipped_ray.target().x()) << " " << floor_to_double(clipped_ray.target().y()) << std::endl;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cout << std::fixed << std::setprecision(0);

  int n; std::cin >> n;
  while (n > 0) {
    solve(n);
    std::cin >> n;
  }
}
