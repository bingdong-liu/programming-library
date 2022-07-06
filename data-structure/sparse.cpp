template<class T>
struct sparse {
  vector<T> aa;
  vector<vector<int>> pp;

  int merge(int i, int j) {
    return aa[i] == aa[j] ? min(i, j) : aa[i] < aa[j] ? i : j;
  }
  sparse() {}
  sparse(const vector<int>& aa_) : aa(aa_) {
    pp = {vector<int>(aa.size())};
    iota(pp[0].begin(), pp[0].end(), 0);
    for (int b = 1; 1 << b <= (int) aa.size(); b++) {
      pp.push_back(vector<int>(aa.size() - (1 << b) + 1));
      for (int i = 0; i < (int) pp[b].size(); i++)
        pp[b][i] = merge(pp[b - 1][i], pp[b - 1][i + (1 << (b - 1))]);
    }
  }
  int index(int l, int r) {
    int b;

    assert(l <= r);
    b = 31 - __builtin_clz(r - l + 1);
    return merge(pp[b][l], pp[b][r - (1 << b) + 1]);
  }
  T query(int l, int r) {
    return aa[index(l, r)];
  }
};
