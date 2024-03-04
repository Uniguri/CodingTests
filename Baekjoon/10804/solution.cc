#include <algorithm>
#include <array>
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

  array<int, 21> arr = {0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10,
                        11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
  const auto& ib = arr.begin();
  int N = 10;
  while (N--) {
    int a, b;
    cin >> a >> b;
    reverse(ib + a, ib + b + 1);
  }

  for (int i = 1; i < 21; ++i) {
    cout << arr[i] << ' ';
  }

  return 0;
}

#undef FAST_IO