#include <algorithm>
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

int sol(uint32 n) {
  if (n <= 1) {
    return 0;
  }
  return min(sol(n / 2) + n % 2, sol(n / 3) + n % 3) + 1;
}

int main() {
  FAST_IO();

  int N;
  cin >> N;
  cout << sol(N);

  return 0;
}

#undef FAST_IO