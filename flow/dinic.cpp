/*
dinic's algorithm
- finds maximum flow
- O(N²·M) for general graphs, but in practice O(M√M)
- O(M√N) for bipartite matching
- O(M·min(N^(2/3),√M)) for unit capacity graphs
*/
template<class flow>
struct dinic {
  int n;
  flow inf;
  vector<vector<int>> ej;
  vector<flow> cc, ff;
  vector<int> ij, dd, pp;

  dinic(int n_, const flow& inf_ = numeric_limits<flow>::max())
  : n(n_), inf(inf_) {
    ej.assign(n, {}), dd.resize(n), pp.resize(n);
    cc.clear(), ff.clear(), ij.clear();
  }
  void add(int i, int j, const flow& c) {
    int h = ij.size();

    ij.push_back(i ^ j);
    ej[i].push_back(h << 1 | 0), cc.push_back(c), ff.push_back(0);
    ej[j].push_back(h << 1 | 1), cc.push_back(0), ff.push_back(0);
  }
  bool bfs(int s, int t) {
    queue<int> qu;

    qu.push(s);
    fill(dd.begin(), dd.end(), -1), dd[s] = 0;
    fill(pp.begin(), pp.end(), 0);
    while (!qu.empty()) {
      int i = qu.front(), d = dd[i] + 1;

      qu.pop();
      for (int h : ej[i])
        if (ff[h] != cc[h]) {
          int j = i ^ ij[h >> 1];

          if (dd[j] == -1) {
            dd[j] = d;
            if (j == t)
              return 1;
            qu.push(j);
          }
        }
    }
    return 0;
  }
  flow dfs(int i, int t, const flow& c) {
    int d = dd[i] + 1;

    if (i == t || c == 0)
      return c;
    for (int& p = pp[i]; p < (int) ej[i].size(); p++) {
      int h = ej[i][p];

      if (ff[h] != cc[h]) {
        int j = i ^ ij[h >> 1];
        
        if (dd[j] == d) {
          flow f = dfs(j, t, min(c, cc[h] - ff[h]));

          if (f) {
            ff[h] += f, ff[h ^ 1] -= f;
            return f;
          }
        }
      }
    }
    dd[i] = -1;
    return 0;
  }
  flow run(int s, int t) {
    flow sum = 0;
    
    while (bfs(s, t)) {
      flow f;

      while ((f = dfs(s, t, inf)))
        sum += f;
    }
    return sum;
  }
};
