int ff[N + 1], vv[N + 1], gg[N + 1];

int inv(int a) {
  return a == 1 ? 1 : (long long) inv(a - MD % a) * (MD / a + 1) % MD;
}

void init() {
  ff[0] = vv[1] = gg[0] = 1;
  for (int i = 1; i <= N; i++) {
    ff[i] = (long long) ff[i - 1] * i % MD;
    if (i > 1)
      vv[i] = (long long) vv[MD % i] * (MD - MD / i) % MD;
    gg[i] = (long long) gg[i - 1] * vv[i] % MD;
  }
}

int ch(int n, int k) {
  return (long long) ff[n] * gg[k] % MD * gg[n - k] % MD;
}
