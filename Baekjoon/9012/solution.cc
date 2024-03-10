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

  int N;
  cin >> N;
  char s[51];
  while (N--) {
    cin >> s;
    stack<char> st;
    for (char* p = s; *p; ++p) {
      const char c = *p;
      if (st.empty() || c == '(') {
        st.push(c);
      } else {
        if (st.top() == '(') {
          st.pop();
        } else {
          break;
        }
      }
    }

    if (st.empty()) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }
  return 0;
}

#undef FAST_IO