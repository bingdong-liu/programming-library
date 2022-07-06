vector<int> suffix_array(const string& s) {
  vector<int> sa(s.size()), cc(s.size());
  int n = s.size();

  for (int i = 0; i < n; i++)
    sa[i] = n - i - 1, cc[i] = s[i];
  stable_sort(sa.begin(), sa.end(), [&s](int i, int j) {
    return s[i] < s[j];
  });
  for (int k = 1; k < n; k <<= 1) {
    vector<int> cc_(cc), kk(n), sa_(sa);

    for (int i = 0; i < n; i++)
      cc[sa[i]] = i && sa[i - 1] + k < n
                    && cc_[sa[i]] == cc_[sa[i - 1]]
                    && cc_[sa[i] + k / 2] == cc_[sa[i - 1] + k / 2]
                    ? cc[sa[i - 1]] : i;
    for (int i = 0; i < n; i++)
      kk[i] = i;
    for (int i = 0; i < n; i++) {
      int s1 = sa_[i] - k;

      if (s1 >= 0)
        sa[kk[cc[s1]]++] = s1;
    }
  }
  return sa;
}

vector<int> lcp_array(const vector<int>& sa, const string& s) {
  vector<int> rank(s.size()), lcp(s.size() - 1);
  int n = s.size(), p;

  for (int i = 0; i < n; i++)
    rank[sa[i]] = i;
  p = 0;
  for (int i = 0; i < n; i++) {
    if (rank[i] < n - 1) {
      int j = sa[rank[i] + 1];
      while (max(i, j) + p < n && s[i + p] == s[j + p])
        p++;
      lcp[rank[i]] = p;
      if (p > 0)
        p--;
    }
  }
  return lcp;
}
