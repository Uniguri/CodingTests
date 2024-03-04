#include <iostream>

#define FAST_IO()                        \
  std::ios_base::sync_with_stdio(false); \
  std::cin.tie(NULL);                    \
  std::cout.tie(NULL)
using namespace std;

int main() {
  FAST_IO();

  int a, b;
  cin >> a >> b;
  cout << a + b;
}

#undef FAST_IO