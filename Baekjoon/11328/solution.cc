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

  int N;
  cin >> N;
  char s[1'001];
  while (N--) {
    char ac['z' - 'a' + 1] = {
        0,
    };
    cin >> s;
    for (char* p = s; *p; ++p) {
      ++ac[*p - 'a'];
    }
    cin >> s;
    for (char* p = s; *p; ++p) {
      --ac[*p - 'a'];
    }
    bool suc = true;
    for (int i = 0; i < (int)sizeof(ac); ++i) {
      if (ac[i]) {
        suc = false;
        break;
      }
    }
    if (suc) {
      cout << "Possible\n";
    } else {
      cout << "Impossible\n";
    }
  }

  return 0;
}

#undef FAST_IO