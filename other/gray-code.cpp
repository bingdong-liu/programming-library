template<class F>
void gray_code(int n, const F& f) {
  for (int b = 0; b < 1 << n; b++)
    f(b ^ (b >> 1));
}
