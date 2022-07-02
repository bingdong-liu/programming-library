#include <bits/stdc++.h>
using namespace std;

#define sz(v) static_cast<int>((v).size())
#define long long long

inline namespace input {
  inline char get_char() {
    #ifdef LOCAL
      return getchar();
    #else
      static const int B = 1 << 20;
      static char bb[B], *b = bb;
      static int cnt = 0;

      if (cnt == 0) {
        if ((cnt = fread(bb, 1, B, stdin)) == 0)
          return EOF;
        b = bb;
      }
      return cnt--, *b++;
    #endif
  }
  inline void scan(string& s) {
    char c = get_char();

    while (c <= ' ')
      ;
    s.clear();
    while (c > ' ')
      s += c, c = get_char();
  }
  template<class T>
  inline typename enable_if<is_floating_point<T>::value, void>::type scan(T& x) {
    string s;

    scan(s);
    x = static_cast<T>(stod(s));
  }
  template<class T>
  inline typename enable_if<is_integral<T>::value, void>::type scan(T& x) {
    char c = get_char();
    bool f = false;

    x = 0;
    while (c < '0' || c > '9')
      f |= c == '-', c = get_char();
    while (c >= '0' && c <= '9')
      x = (x << 3) + (x << 1) + (c ^ 48), c = get_char();
    if (f)
      x = -x;
  }
  template<class T, class...U>
  inline void scan(T& t, U&... u) {
    scan(t), scan(u...);
  }
};

#ifdef LOCAL
  #define dbg(...) printf("\033[1;34m% 4d \033[32m|\033[0m ", __LINE__), printf(__VA_ARGS__)
#else
  #define dbg(...) 0
#endif

int main() {
  
  return 0;
}
