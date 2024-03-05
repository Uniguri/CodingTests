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

  int s[1'000'001] = {
      0,
      0,
      1,
      1,
  };
  int N;
  cin >> N;

  for (int i = 4; i <= N; ++i) {
    int nmm1 = 1'000'001;  // now_min_minus_1
    if (i % 3 == 0 && nmm1 > s[i / 3]) {
      nmm1 = s[i / 3];
    }
    if (i % 2 == 0 && nmm1 > s[i / 2]) {
      nmm1 = s[i / 2];
    }
    if (nmm1 > s[i - 1]) {
      nmm1 = s[i - 1];
    }

    s[i] = nmm1 + 1;
  }
  cout << s[N];
  return 0;
}

#undef FAST_IO