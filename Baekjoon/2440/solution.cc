#include <iostream>

#define FAST_IO()                        \
  std::ios_base::sync_with_stdio(false); \
  std::cin.tie(NULL);                    \
  std::cout.tie(NULL)
using namespace std;

int main() {
  FAST_IO();

  int N;
  cin >> N;
  for (int i = N; i > 0; --i) {
    for (int j = 0; j < i; ++j) {
      cout << '*';
    }
    cout << '\n';
  }

  return 0;
}

#undef FAST_IO