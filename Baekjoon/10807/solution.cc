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

  int N, v;
  int ds[100];
  cin >> N;
  for (int i = 0; i < N; ++i) {
    cin >> ds[i];
  }
  cin >> v;

  int ans = 0;
  while (N--) {
    if (ds[N] == v) {
      ++ans;
    }
  }
  cout << ans;

  return 0;
}

#undef FAST_IO