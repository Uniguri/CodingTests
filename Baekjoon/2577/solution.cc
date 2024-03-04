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

  uint32 A, B, C;
  cin >> A >> B >> C;

  uint64 ABC = A * B * C;
  char d[10] = {
      0,
  };

  while (ABC) {
    uint8 r = ABC % 10;
    ABC /= 10;

    ++d[r];
  }

  for (int i = 0; i < sizeof(d); ++i) {
    cout << (uint32)d[i] << '\n';
  }

  return 0;
}

#undef FAST_IO