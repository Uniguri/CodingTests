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

  char r[200'000];
  int idx = -1;
  int max = 0;
  stack<int> s;
  s.push(0);
  while (N--) {
    int t;
    cin >> t;

    if (t > s.top() && max < t) {
      for (int i = max + 1; i <= t; ++i) {
        r[++idx] = '+';
        s.push(i);
      }
      r[++idx] = '-';
      s.pop();
      max = t;
    } else if (t == s.top()) {
      r[++idx] = '-';
      s.pop();
    } else {
      cout << "NO";
      return 0;
    }
  }

  for (int i = 0; i <= idx; ++i) {
    cout << r[i] << '\n';
  }

  return 0;
}

#undef FAST_IO