#include <cstring>
#include <iostream>
#include <string>

#define FAST_IO()                        \
  std::ios_base::sync_with_stdio(false); \
  std::cin.tie(NULL);                    \
  std::cout.tie(NULL)
using namespace std;

int main() {
  FAST_IO();

  string s;
  char common[51] = {
      0,
  };
  int N;

  cin >> N;

  cin >> common;
  --N;
  size_t string_len = strlen(common);

  while (N--) {
    cin >> s;
    for (int i = 0; i < string_len; ++i) {
      if (s[i] != common[i]) {
        common[i] = '?';
      }
    }
  }

  cout << common;
}

#undef FAST_IO