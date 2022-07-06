struct dsu {
  vector<int> ds;

  dsu() {}
  dsu(int n) {
    ds.assign(n, -1);
  }
  int find(int i) {
    return ds[i] < 0 ? i : ds[i] = find(ds[i]);
  }
  int size(int i) {
    return -ds[find(i)];
  }
  bool same(int i, int j) {
    return find(i) == find(j);
  }
  bool join(int i, int j) {
    i = find(i), j = find(j);
    if (i == j)
      return false;
    if (ds[i] > ds[j])
      swap(i, j);
    ds[i] += ds[j], ds[j] = i;
    return true;
  }
};
