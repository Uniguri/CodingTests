#include <cstring>
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

  int s[10'000];
  // index of last element.
  int t = -1;

  char st[32];
  while (N--) {
    cin >> st;
    if (!strcmp(st, "push")) {
      cin >> s[++t];
    } else if (!strcmp(st, "pop")) {
      if (t < 0) {
        cout << -1 << '\n';
      } else {
        cout << s[t--] << '\n';
      }
    } else if (!strcmp(st, "size")) {
      cout << t + 1 << '\n';
    } else if (!strcmp(st, "empty")) {
      cout << (t < 0) << '\n';
    } else if (!strcmp(st, "top")) {
      if (t < 0) {
        cout << -1 << '\n';
      } else {
        cout << s[t] << '\n';
      }
    }
  }

  return 0;
}

#undef FAST_IO