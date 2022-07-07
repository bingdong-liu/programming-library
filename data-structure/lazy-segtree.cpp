int aa[N], st[N * 4], lz1[N * 4], lz2[N * 4];

void pull(int k, int l, int r) {
  int lc = k << 1 | 0, rc = k << 1 | 1;

  st[k] = (st[lc] + st[rc]) % MD;
}

void put(int k, int l, int r, int x1, int x2) {
  st[k] = ((long long) st[k] * x1 + (long long) x2 * (r - l + 1)) % MD;
  lz1[k] = (long long) lz1[k] * x1 % MD, lz2[k] = ((long long) x1 * lz2[k] + x2) % MD;
}

void push(int k, int l, int r) {
  if (lz1[k] != 1 || lz2[k] != 0) {
    if (l != r) {
      int m = (l + r) / 2;

      put(k << 1 | 0, l, m, lz1[k], lz2[k]);
      put(k << 1 | 1, m + 1, r, lz1[k], lz2[k]);
    }
    lz1[k] = 1, lz2[k] = 0;
  }
}

void build(int k, int l, int r) {
  lz1[k] = 1, lz2[k] = 0;
  if (l == r)
    st[k] = aa[l];
  else {
    int m = (l + r) / 2;

    build(k << 1 | 0, l, m);
    build(k << 1 | 1, m + 1, r);
    pull(k, l, r);
  }
}

void update(int k, int l, int r, int ql, int qr, int x1, int x2) {
  if (ql <= l && qr >= r)
    put(k, l, r, x1, x2);
  else if (qr >= l && ql <= r) {
    int m = (l + r) / 2;

    push(k, l, r);
    update(k << 1 | 0, l, m, ql, qr, x1, x2);
    update(k << 1 | 1, m + 1, r, ql, qr, x1, x2);
    pull(k, l, r);
  }
}

int query(int k, int l, int r, int ql, int qr) {
  if (qr < l || ql > r)
    return 0;
  else if (ql <= l && qr >= r)
    return st[k];
  else {
    int m = (l + r) / 2;

    push(k, l, r);
    return (query(k << 1 | 0, l, m, ql, qr) + query(k << 1 | 1, m + 1, r, ql, qr)) % MD;
  }
}
