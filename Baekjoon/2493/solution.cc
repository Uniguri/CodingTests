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

  stack<pair<int, int>> s;
  s.push(make_pair(0, 0));
  for (int i = 1; i <= N; ++i) {
    int t;
    cin >> t;

    while (!s.empty() && s.top().first < t) {
      s.pop();
    }
    if (s.empty()) {
      cout << 0 << ' ';
    } else {
      cout << s.top().second << ' ';
    }
    s.push(make_pair(t, i));
  }

  return 0;
}

#undef FAST_IO