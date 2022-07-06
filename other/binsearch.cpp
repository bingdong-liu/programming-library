template<class T, class F>
T first_true(T lower, T upper, const F& f) {
  upper++;
  assert(lower <= upper);
  while (lower < upper) {
    T t = lower + (upper - lower) / 2;

    if (f(t))
      upper = t;
    else
      lower = t + 1;
  }
  return lower;
}

template<class T, class F>
T last_true(T lower, T upper, const F& f) {
  lower--;
  assert(lower <= upper);
  while (lower < upper) {
    T t = lower + (upper - lower + 1) / 2;

    if (f(t))
      lower = t;
    else
      upper = t - 1;
  }
  return lower;
}
