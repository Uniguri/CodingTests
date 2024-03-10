#include <iostream>
#include <stack>

#define FAST_IO()                        \
  std::ios_base::sync_with_stdio(false); \
  std::cin.tie(NULL);                    \
  std::cout.tie(NULL)
#define int8 char
#define int16 short
#define int32 int
#define int64 long long
#define uint8 unsigned int8
#define uint16 unsigned int16
#define uint32 unsigned int32
#define uint64 unsigned int64
using namespace std;

int main() {
  FAST_IO();

  char s[31];
  cin >> s;
  stack<char> st;
  int r = 0, w = 1;
  bool iw = false, ibo = false;
  for (char* p = s; *p; ++p) {
    const char c = *p;
    if (c == '(' || c == '[') {
      st.push(c);
      w *= (c == '(') ? 2 : 3;
      ibo = true;
    } else {
      if (st.empty() || (st.top() == '(' && c != ')') ||
          (st.top() == '[' && c != ']')) {
        iw = true;
        break;
      }

      if (ibo) {
        r += w;
      }
      st.pop();
      w /= (c == ')') ? 2 : 3;
      ibo = false;
    }
  }
  if (iw || !st.empty()) {
    cout << 0;
  } else {
    cout << r;
  }

  return 0;
}

#undef FAST_IO