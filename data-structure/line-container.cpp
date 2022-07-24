/*
line container
---
add lines and query max value for given x
*/

struct line {
  mutable long long k, m, p;

  bool operator<(const line& l) const {
    return k < l.k;
  }
  bool operator<(long long x) const {
    return p < x;
  }
  long long operator()(const long long& x) const {
    return k * x + m;
  }
};

struct line_container : multiset<line, less<>> {
  long long div(long long a, long long b) {
    return a / b - ((a ^ b) < 0 && a % b); }
  bool isect(iterator x, iterator y) {
    if (y == end())
      return x->p = LLONG_MAX, 0;
    if (x->k == y->k)
      x->p = x->m > y->m ? LLONG_MAX : -LLONG_MAX;
    else
      x->p = div(y->m - x->m, x->k - y->k);
    return x->p >= y->p;
  }
  void add(long long k, long long m) {
    auto z = insert({k, m, 0}), y = z++, x = y;
    while (isect(y, z))
      z = erase(z);
    if (x != begin() && isect(--x, y))
      isect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p)
      isect(x, erase(y));
  }
  long long query(long long x) {
    assert(!empty());
    return (*lower_bound(x))(x);
  }
};
