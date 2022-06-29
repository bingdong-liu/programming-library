/*
min cost max flow
---
- O(F·M log N) for non-negative costs
- O(N·M + F·M log N) for negative costs
*/ 
template<class flow, class cost, bool negative_cost = 0>
struct mcmf {
  int n;
  flow flow_inf;
  cost cost_inf;
  vector<vector<int>> ej;
  vector<flow> cc, ff;
  vector<cost> kk, dd, pi;
  vector<int> ij, hh;
  vector<bool> vis;

  mcmf(int n_, const flow& flow_inf_ = numeric_limits<flow>::max(), const cost& cost_inf_ = numeric_limits<cost>::max())
  : n(n_), flow_inf(flow_inf_), cost_inf(cost_inf_) {
    ej.assign(n, {}), vis.resize(n), dd.resize(n), pi.resize(n), hh.resize(n);
    ij.clear(), cc.clear(), ff.clear(), kk.clear();
  }
  void add(int i, int j, const flow &c, const cost &k) {
    int h = ij.size();

    ij.push_back(i ^ j);
    ej[i].push_back(h << 1 | 0), cc.push_back(c), ff.push_back(0), kk.push_back(+k);
    ej[j].push_back(h << 1 | 1), cc.push_back(0), ff.push_back(0), kk.push_back(-k);
  }
  bool dijkstra(int s, int t) {
    priority_queue<pair<cost, int>, vector<pair<cost, int>>, greater<pair<cost, int>>> qu;

    fill(vis.begin(), vis.end(), false);
    fill(dd.begin(), dd.end(), cost_inf);
    qu.push({dd[s] = 0, s});
    while (!qu.empty()) {
      auto [d, i] = qu.top();

      qu.pop();
      if (vis[i])
        continue;
      vis[i] = 1;
      for (int h : ej[i])
        if (ff[h] != cc[h]) {
          int j = i ^ ij[h >> 1];
          cost d_ = d + kk[h] + pi[i] - pi[j];

          if (dd[j] > d_) {
            hh[j] = h;
            qu.push({dd[j] = d_, j});
          }
        }
    }
    return vis[t];
  }
  pair<flow, cost> run(int s, int t) {
    flow fsum = 0;
    cost csum = 0;

    if (negative_cost) {
      fill(pi.begin(), pi.end(), cost_inf), pi[s] = 0;
      for (int it = 0; it < n; it++)
        for (int i = 0; i < n; i++)
          for (int h : ej[i])
            if (ff[h] != cc[h]) {
              int j = i ^ ij[h >> 1];

              pi[j] = min(pi[j], pi[i] + kk[h]);
            }
    }
    while (dijkstra(s, t)) {
      flow f = flow_inf;

      for (int i = 0; i < n; i++)
        pi[i] += dd[i];
      for (int i = t; i != s; ) {
        int h = hh[i];

        f = min(f, cc[h] - ff[h]);
        i = i ^ ij[h >> 1];
      }
      fsum += f, csum += f * (pi[t] - pi[s]);
      for (int i = t; i != s; ) {
        int h = hh[i];

        ff[h] += f, ff[h ^ 1] -= f;
        i = i ^ ij[h >> 1];
      }
    }
    return {fsum, csum};
  }
};
