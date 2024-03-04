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
  int A, B;
  cin >> A >> B;
  cout << A + B << '\n';
  cout << A - B << '\n';
  cout << A * B << '\n';
  cout << A / B << '\n';
  cout << A % B << '\n';
  return 0;
}

#undef FAST_IO