struct scc {
  int n, time;
  vector<vector<int>> ej;
  vector<bool> marked;
  vector<int> id, stack;

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
      vector<int> ii = {i};

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

struct two_sat {
  int n;
  scc gr;
  vector<bool> status;

  two_sat(int n_) : n(n_), gr(n * 2) {
    status.resize(n);
  }
  int operator[](int i) {
    return status[i];
  }
  void either(int i, int j) {
    i = max(i * 2, -1 - i * 2);
    j = max(j * 2, -1 - j * 2);
    gr.add(i ^ 1, j ^ 0), gr.add(j ^ 1, i ^ 0);
  }
  void implies(int i, int j) {
    either(~i, j);
  }
  void must(int i) {
    either(i, i);
  }
  bool run() {
    vector<int> cc(n * 2), tmp;
    int c = 0;

    gr.run([&](vector<int> &ii) {
      for (int i : ii)
        cc[i] = c;
      c++;
    });
    tmp.resize(c);
    for (int i = 0; i < n; i++) {
      if (cc[i << 1 | 0] == cc[i << 1 | 1])
        return false;
      tmp[cc[i << 1 | 0]] = cc[i << 1 | 1];
      tmp[cc[i << 1 | 1]] = cc[i << 1 | 0];
    }
    while (c--)
      if (tmp[c] >= 0)
        tmp[tmp[c]] = -2, tmp[c] = -1;
    for (int i = 0; i < n; i++)
      status[i] = tmp[cc[i << 1 | 0]] != -1;
    return true;
  }
};
