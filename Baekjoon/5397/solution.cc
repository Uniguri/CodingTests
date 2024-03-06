#include <iostream>
#include <list>

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
  char s[1'000'001];
  while (N--) {
    cin >> s;
    list<char> l;
    auto it = l.begin();
    for (char* p = s; *p; ++p) {
      const char c = *p;
      if (c == '-') {
        if (l.empty() || it == l.begin()) {
          continue;
        }
        it = l.erase(--it);
      } else if (c == '<') {
        if (it != l.begin()) {
          --it;
        }
      } else if (c == '>') {
        if (it != l.end()) {
          ++it;
        }
      } else {
        it = ++l.insert(it, c);
      }
    }

    for (const char c : l) {
      cout << c;
    }
    cout << '\n';
  }
  return 0;
}

#undef FAST_IO