#include <cmath>
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

  char s1[1'001];
  char s2[1'001];
  cin >> s1 >> s2;
  int ac['z' - 'a' + 1] = {
      0,
  };
  for (char* p = s1; *p; ++p) {
    ++ac[*p - 'a'];
  }
  for (char* p = s2; *p; ++p) {
    --ac[*p - 'a'];
  }

  int ans = 0;
  for (int i = 0; i < (int)(sizeof(ac) / sizeof(ac[0])); ++i) {
    ans += abs(ac[i]);
  }
  cout << ans;

  return 0;
}

#undef FAST_IO