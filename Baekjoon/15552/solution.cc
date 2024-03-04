#include <iostream>

#define FAST_IO()                        \
  std::ios_base::sync_with_stdio(false); \
  std::cin.tie(NULL);                    \
  std::cout.tie(NULL)
#define int8 cha
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

  uint64 T;
  cin >> T;
  while (T--) {
    int A, B;
    cin >> A >> B;
    cout << A + B << '\n';
  }

  return 0;
}

#undef FAST_IO