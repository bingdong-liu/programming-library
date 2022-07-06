template<class T>
struct bit {
  vector<T> ft;
 
  bit() {}
  bit(int n) {
    ft.assign(n, 0);
  }
  void update(int i, const T& x) {
    while (i < (int) ft.size()) {
      ft[i] += x;
      i |= i + 1;
    }
  }
  void update(int l, int r, const T& x) {
    update(l, +x), update(r + 1, -x);
  }
  T query(int i) {
    T sum = 0;
 
    while (i >= 0) {
      sum += ft[i];
      i &= i + 1, i--;
    }
    return sum;
  }
};
