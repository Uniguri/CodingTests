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

  int n, x;
  int a[100'000];
  int nc[2'000'000];
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  cin >> x;

  uint64 ans = 0;
  for (int i = 0; i < n; ++i) {
    const int n = a[i];
    const int nd = x - n;
    if (nd > 0 && nc[nd]) {
      ++ans;
      --nc[nd];
    } else {
      ++nc[n];
    }
  }
  cout << ans;

  return 0;
}

#undef FAST_IO