inline namespace input {
  inline void rd(string& s) {
    char c = getchar();

    while (c <= ' ')
      ;
    s.clear();
    while (c > ' ')
      s += c, c = getchar();
  }
  template<class T>
  inline typename enable_if<is_floating_point<T>::value, void>::type rd(T& x) {
    string s;

    rd(s);
    x = static_cast<T>(stod(s));
  }
  template<class T>
  inline typename enable_if<is_integral<T>::value, void>::type rd(T& x) {
    char c = getchar();
    bool neg = false;

    x = 0;
    while (c < '0' || c > '9')
      neg |= c == '-', c = getchar();
    while (c >= '0' && c <= '9')
      x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
    if (neg)
      x = -x;
  }
  template<class T, class...U>
  inline void rd(T& t, U&... u) {
    rd(t), rd(u...);
  }
};
