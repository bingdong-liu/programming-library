template<int root, int mod>
struct ntt {
  static const int R = root, MD = mod;
  static vector<vector<int>> wu, wv;

  static int power(int a, int k) {
    long long b = a, p = 1;

    while (k) {
      if (k & 1)
        p = p * b % MD;
      b = b * b % MD;
      k >>= 1;
    }
    return p;
  }
  static void make(int l_) {
    for (int l = wu.size(); l < l_; l++) {
      int n = 1 << l, u = power(R, (MD - 1) >> (l + 1)), v = power(u, MD - 2);;
      vector<int> wu_(n), wv_(n);

      wu_[0] = wv_[0] = 1;
      for (int i = 1; i < n; i++) {
        wu_[i] = (long long) wu_[i - 1] * u % MD;
        wv_[i] = (long long) wv_[i - 1] * v % MD;
      }
      wu.push_back(wu_), wv.push_back(wv_);
    }
  }
  static void dft(vector<int> &pp, int l_, bool inverse) {
    int n_ = 1 << l_;
    
    for (int i = 0, j = 1; j < n_; j++) {
      for (int b = n_ >> 1; (i ^= b) < b; b >>= 1)
        ;
      if (i < j)
        swap(pp[i], pp[j]);
    }
    for (int l = 0; l < l_; l++) {
      const vector<int> &ww = inverse ? wv[l] : wu[l];
      int n = 1 << l;

      for (int i = 0; i < n_; i += n << 1)
        for (int j = 0; j < n; j++) {
          int a = pp[i + j], b = (long long) pp[i + j + n] * ww[j] % MD;

          if ((pp[i + j] = a + b) >= MD)
            pp[i + j] -= MD;
          if ((pp[i + j + n] = a - b) < 0)
            pp[i + j + n] += MD;
        }
    }
    if (inverse) {
      int v = power(n_, MD - 2);

      for (int i = 0; i < n_; i++)
        pp[i] = (long long) pp[i] * v % MD;
    }
  }
  static vector<int> run(vector<int> pp, vector<int> qq) {
    int n = pp.size() + qq.size() - 1, n_, l;

    for (l = 0; (n_ = 1 << l) < n; l++)
      ;
    make(l);
    pp.resize(n_), dft(pp, l, 0);
    qq.resize(n_), dft(qq, l, 0);
    for (int i = 0; i < n_; i++)
      pp[i] = (long long) pp[i] * qq[i] % MD;
    dft(pp, l, 1), pp.resize(n);
    return pp;
  }
};

template<int root, int mod>
vector<vector<int>> ntt<root, mod>::wu;
template<int root, int mod>
vector<vector<int>> ntt<root, mod>::wv; 

template<class ntt_type>
vector<int> mult(vector<int> pp, vector<int> qq) {
  if (min(pp.size(), qq.size()) <= 64) {
    vector<int> rr(pp.size() + qq.size() - 1);

    for (int i = 0; i < (int) pp.size(); i++)
      for (int j = 0; j < (int) qq.size(); j++)
        rr[i + j] = (rr[i + j] + (long long) pp[i] * qq[j]) % ntt_type::MD;
    return rr;
  }
  return ntt_type::run(pp, qq);
}

template<class ntt_type1, class ntt_type2>
vector<long long> mult(vector<int> pp, vector<int> qq) {
  vector<int> rr = mult<ntt_type1>(pp, qq), ss = mult<ntt_type2>(pp, qq);
  vector<long long> tt(pp.size() + qq.size() - 1);

  auto garner = [&](int a1, int a2) {
    static int V = ntt_type2::power(ntt_type1::MD, ntt_type2::MD - 2);
   
    a2 = (long long) (a2 - a1) * V % ntt_type2::MD;
    if (a2 < 0)
      a2 += ntt_type2::MD;
    return (long long) a2 * ntt_type1::MD + a1;
  };
  
  for (int i = 0; i < (int) tt.size(); i++)
    tt[i] = garner(rr[i], ss[i]);
  return tt;
}

using ntt469 = ntt<3, 469762049>;
using ntt998 = ntt<3, 998244353>;
