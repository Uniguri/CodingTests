#include <algorithm>
#include <iostream>
#include <numeric>
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

  int a[80'000];
  for (int i = 0; i < N; ++i) {
    cin >> a[N - i - 1];
  }

  uint64 c[80'001];
  stack<pair<uint64, uint64>> s;
  for (int i = 0; i < N; ++i) {
    const uint64 h = a[i];

    uint64 pc = 0;
    while (!s.empty() && h > s.top().first) {
      pc += c[s.top().second] + 1;
      s.pop();
    }
    c[i] = pc;
    s.push(make_pair(h, i));
  }
  cout << accumulate(c, c + N, 0llu);

  return 0;
}

#undef FAST_IO