#include <iostream>

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

  int N, K;
  cin >> N >> K;
  int st[2][7] = {
      0,
  };
  for (int i = 0; i < N; ++i) {
    int s, y;
    cin >> s >> y;
    ++st[s][y];
  }
  int ans = 0;
  for (int s = 0; s < 2; ++s) {
    for (int y = 1; y < 7; ++y) {
      const int t = st[s][y];
      ans += (t / K) + (t % K != 0);
    }
  }
  cout << ans;

  return 0;
}

#undef FAST_IO