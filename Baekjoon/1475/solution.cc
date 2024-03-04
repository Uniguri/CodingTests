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

  uint64 N;
  cin >> N;
  uint64 d[10] = {
      0,
  };
  while (N) {
    uint8 r = N % 10;
    N /= 10;
    ++d[r];
  }
  {
    uint64 s = d[6] + d[9];
    d[6] = s / 2;
    d[9] = (s + 1) / 2;
  }

  uint64 ans = 0;
  while (1) {
    bool f = false;
    for (int i = 0; i < sizeof(d) / sizeof(d[0]); ++i) {
      if (!d[i]) {
        continue;
      }

      if (!f) {
        f = true;
        ++ans;
      }
      if (f) {
        --d[i];
      }
    }
    if (!f) {
      break;
    }
  }
  cout << ans;

  return 0;
}

#undef FAST_IO