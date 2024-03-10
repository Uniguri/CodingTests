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

  char s[100'001];
  cin >> s;
  bool ibo = false;
  stack<char> st;
  int r = 0;
  for (char* p = s; *p; ++p) {
    const char c = *p;
    if (c == '(') {
      ibo = true;
      st.push(c);
    } else {
      st.pop();
      if (ibo) {
        r += st.size();
      } else {
        ++r;
      }
      ibo = false;
    }
  }
  cout << r;

  return 0;
}

#undef FAST_IO