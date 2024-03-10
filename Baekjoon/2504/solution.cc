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
  stack<char> stc;
  stack<pair<size_t, uint64>> str;
  bool iw = false, ibo = false;
  for (char* p = s; *p; ++p) {
    const char c = *p;
    if (c == '(' || c == '[') {
      stc.push(c);
      ibo = true;
    } else {
      if (stc.empty() || (stc.top() == '(' && c != ')') ||
          (stc.top() == '[' && c != ']')) {
        iw = true;
        break;
      }

      const uint64 n = c == ')' ? 2 : 3;
      if (ibo) {
        str.push(make_pair(stc.size(), n));
      } else {
        uint64 t = 0;
        while (!str.empty() && str.top().first > stc.size()) {
          t += str.top().second;
          str.pop();
        }
        str.push(make_pair(stc.size(), n * t));
      }

      stc.pop();
      ibo = false;
    }
  }
  if (iw || !stc.empty()) {
    cout << 0;
  } else {
    uint64 t = 0;
    while (!str.empty()) {
      t += str.top().second;
      str.pop();
    }
    cout << t;
  }

  return 0;
}

#undef FAST_IO