/*
line container
---
add lines and query max value for given x
*/
template<class T>
struct line {
  mutable T k, m, p;

  bool operator<(const line& l) const {
    return k < l.k;
  }
  bool operator<(T x) const {
    return p < x;
  }
  T operator()(const T& x) const {
    return k * x + m;
  }
};

template<class T>
struct line_container {
  static const T inf = numeric_limits<T>::max();
  multiset<line<T>, less<>> cc;

  T div(T a, T b) {
    return a / b - ((a ^ b) < 0 && a % b); }
  template<class I>
  bool isect(I x, I y) {
    if (y == cc.end())
      return x->p = inf, 0;
    if (x->k == y->k)
      x->p = x->m > y->m ? inf : -inf;
    else
      x->p = div(y->m - x->m, x->k - y->k);
    return x->p >= y->p;
  }
  void add(T k, T m) {
    auto z = cc.insert({k, m, 0}), y = z++, x = y;

    while (isect(y, z))
      z = cc.erase(z);
    if (x != cc.begin() && isect(--x, y))
      isect(x, y = cc.erase(y));
    while ((y = x) != cc.begin() && (--x)->p >= y->p)
      isect(x, cc.erase(y));
  }
  T query(T x) {
    assert(!cc.empty());

    return (*cc.lower_bound(x))(x);
  }
};
