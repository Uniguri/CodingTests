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

  int x[3], y[3];
  for (int i = 0; i < 3; ++i) {
    cin >> x[i] >> y[i];
  }

  if (x[0] == x[1]) {
    cout << x[2];
  } else if (x[0] == x[2]) {
    cout << x[1];
  } else {
    cout << x[0];
  }
  cout << ' ';
  if (y[0] == y[1]) {
    cout << y[2];
  } else if (y[0] == y[2]) {
    cout << y[1];
  } else {
    cout << y[0];
  }

  return 0;
}

#undef FAST_IO