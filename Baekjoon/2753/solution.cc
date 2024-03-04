#include <iostream>

#define FAST_IO()                        \
  std::ios_base::sync_with_stdio(false); \
  std::cin.tie(NULL);                    \
  std::cout.tie(NULL)
using namespace std;

bool IsLeapYear(int year);

int main() {
  FAST_IO();

  int y;
  cin >> y;
  cout << IsLeapYear(y);

  return 0;
}

inline bool IsLeapYear(int year) {
  return !(year % 400) || (year % 100) && !(year % 4);
}

#undef FAST_IO