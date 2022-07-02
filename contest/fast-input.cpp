inline namespace input {
  inline char get_char() {
    #ifdef LOCAL
      return getchar();
    #else
      static const int SIZE = 1 << 20;
      static char buf[SIZE], *b = buf;
      static int cnt = 0;

      if (cnt == 0) {
        if ((cnt = fread(buf, 1, SIZE, stdin)) == 0)
          return EOF;
        b = buf;
      }
      return cnt--, *b++;
    #endif
  }
  inline void rd(string& s) {
    char c = get_char();

    while (c <= ' ')
      ;
    s.clear();
    while (c > ' ')
      s += c, c = get_char();
  }
  template<class T>
  inline typename enable_if<is_floating_point<T>::value, void>::type rd(T& x) {
    string s;

    rd(s);
    x = static_cast<T>(stod(s));
  }
  template<class T>
  inline typename enable_if<is_integral<T>::value, void>::type rd(T& x) {
    char c = get_char();
    bool neg = false;

    x = 0;
    while (c < '0' || c > '9')
      neg |= c == '-', c = get_char();
    while (c >= '0' && c <= '9')
      x = (x << 3) + (x << 1) + (c ^ 48), c = get_char();
    if (neg)
      x = -x;
  }
  template<class T, class...U>
  inline void rd(T& t, U&... u) {
    rd(t), rd(u...);
  }
};
