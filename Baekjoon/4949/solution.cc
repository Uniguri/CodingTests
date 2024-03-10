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

  char s[101];
  while (cin.getline(s, 101) && *s != '.') {
    stack<char> st;
    bool is_correct = true;
    for (char* p = s; *p; ++p) {
      const char c = *p;
      if (c == '(' || c == '[') {
        st.push(c);
      } else if (c == ')' || c == ']') {
        if (st.empty() || (c == ')' && st.top() != '(') ||
            (c == ']' && st.top() != '[')) {
          is_correct = false;
          break;
        }
        st.pop();
      }
    }
    if (st.empty() && is_correct) {
      cout << "yes\n";
    } else {
      cout << "no\n";
    }
  }
  return 0;
}

#undef FAST_IO