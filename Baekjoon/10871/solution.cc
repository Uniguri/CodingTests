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

  int N, X, t;
  cin >> N >> X;
  while (N--) {
    cin >> t;
    if (t < X) {
      cout << t << " ";
    }
  }
  return 0;
}

#undef FAST_IO