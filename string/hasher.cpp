seed_seq seq {
  (uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count(),
  (uint64_t) __builtin_ia32_rdtsc(),
  (uint64_t) (uintptr_t) unique_ptr<char>(new char).get()
};
mt19937 rng(seq);

int gen_base() {
  int B = uniform_int_distribution<int>(258, 2e9 - 1)(rng);

  return B % 2 == 0 ? B - 1 : B;
}

struct hasher {
  static const uint64_t MD = (1ULL << 61) - 1;
  static int B;
  static vector<uint64_t> pp;
  vector<uint64_t> hs;

  static inline uint64_t add(uint64_t a, uint64_t b) {
    a += b;
    if (a >= MD)
        a -= MD;
    return a;
  }
  static inline uint64_t sub(uint64_t a, uint64_t b) {
    a -= b;
    if (a >= MD)
        a += MD;
    return a;
  }
  static inline uint64_t mul(uint64_t a, uint64_t b) {
    uint64_t l1 = (uint32_t) a, h1 = a >> 32, l2 = (uint32_t) b, h2 = b >> 32;
    uint64_t l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
    uint64_t ret = (l & MD) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
    
    ret = (ret & MD) + (ret >> 61);
    ret = (ret & MD) + (ret >> 61);
    return ret - 1;
  }
  static void make(int n) {
    while ((int) pp.size() <= n)
      pp.push_back(pp.empty() ? 1 : mul(pp.back(), B));
  }
  hasher(const string &s) {
    make(s.size());
    hs.resize(s.size() + 1);
    for (int i = 0; i < (int) s.size(); i++)
      hs[i + 1] = add(mul(hs[i], B), s[i]);
  }
  uint64_t operator()(int l, int r) const {
    return sub(hs[r + 1], mul(hs[l], pp[r - l + 1]));
  }
};

int hasher::B = gen_base();
vector<uint64_t> hasher::pp;
