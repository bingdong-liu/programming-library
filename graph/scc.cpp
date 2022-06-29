struct scc {
  int n, time;
  vector<vector<int>> ej;
  vector<bool> marked;
  vector<int> id, stack;

  scc() {}
  scc(int n_) : n(n_) {
    ej.assign(n, {});
    id.resize(n), marked.resize(n);
  }
  void add(int i, int j) {
    ej[i].push_back(j);
  }
  template<class F>
  int dfs(int i, const F &f) {
    int low = id[i] = time++;

    stack.push_back(i);
    for (int j : ej[i])
      if (!marked[j])
        low = min(low, id[j] != -1 ? id[j] : dfs(j, f));
    if (low == id[i]) {
      vector<int> ii;

      for (int j = -1; j != i; ) {
        marked[j = stack.back()] = true;
        ii.push_back(j);
        stack.pop_back();
      }
      f(ii);
    }
    return low;
  }
  template<class F>
  void run(const F &f) {
    time = 0;
    fill(id.begin(), id.end(), -1);
    fill(marked.begin(), marked.end(), false);
    for (int i = 0; i < n; i++)
      if (id[i] == -1)
        dfs(i, f);
  }
};
