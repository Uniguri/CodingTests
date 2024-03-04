#include <algorithm>
#include <array>
#include <iostream>

#define FAST_IO()                        \
  std::ios_base::sync_with_stdio(false); \
  std::cin.tie(NULL);                    \
  std::cout.tie(NULL)
using namespace std;

int main() {
  FAST_IO();

  array<int, 3> arr;
  cin >> arr[0];
  cin >> arr[1];
  cin >> arr[2];
  sort(arr.begin(), arr.end());

  int sc = 0;
  bool s01 = false, s02 = false, s12 = false;
  if (arr[0] == arr[1]) {
    s01 = true;
    ++sc;
  }
  if (arr[0] == arr[2]) {
    s02 = true;
    ++sc;
  }
  if (arr[1] == arr[2]) {
    s12 = true;
    ++sc;
  }

  switch (sc) {
    case 0:
      cout << arr[2] * 100;
      break;
    case 1:
      if (s01 || s02) {
        cout << 1'000 + arr[0] * 100;
      } else if (s12) {
        cout << 1'000 + arr[1] * 100;
      }
      break;
    case 2:
    case 3:
      cout << 10'000 + arr[2] * 1'000;
      break;
    default:
      break;
  }

  return 0;
}

#undef FAST_IO