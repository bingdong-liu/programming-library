template<class T>
struct segtree {
  T id = INT_MAX;
  T merge(T a, T b) {
    return min(a, b);
  }
  vector<T> st;
  int n_;

  segtree() {}
  segtree(int n) {
    n_ = 1;
    while (n_ < n)
      n_ <<= 1;
    st.assign(n_ << 1, id);
  }
  segtree(const vector<T>& aa) {
    *this = segtree((int) aa.size());
    copy(aa.begin(), aa.end(), st.begin() + n_);
    for (int i = n_ - 1; i > 0; i--)
      pull(i);
  }
  T& operator[](int i) {
    return st[i];
  }
  const T& operator[](int i) const {
    return st[i];
  }
  void pull(int i) {
    st[i] = merge(st[i << 1 | 0], st[i << 1 | 1]);
  }
  void update(int i, const T& a) {
    st[i |= n_] = a;
    while (i >>= 1)
      pull(i);
  }
  T query(int l, int r) {
    T ll = id, rr = id;

    for (l |= n_, r |= n_; l <= r; l >>= 1, r >>= 1) {
      if ((l & 1) == 1)
        ll = merge(ll, st[l++]);
      if ((r & 1) == 0)
        rr = merge(st[r--], rr);
    }
    return merge(ll, rr);
  }
};
