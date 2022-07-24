struct key {
  int l, r;
  mutable int k;
  key() {}
  key(int l, int r, int k) : l(l), r(r), k(k) {}
  bool operator<(const key &o) const {
    return r < o.r;
  }
};
struct tree : set<key> {
  set<key>::iterator split(int x) {
    auto it = lower_bound(key(x, x, 0));
    if (it == end() || it->l > x)
        return it;
    key now = *it;
    erase(now);
    if (x > now.l)
        insert(key(now.l, x - 1, now.k));
    return insert(key(x, now.r, now.k)).first;
  }
  void set(int l, int r, int k) {
    auto R = split(r + 1);
    auto L = split(l);
    erase(L, R);
    insert(key(l, r, k));
  }
};
