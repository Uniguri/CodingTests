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

  cout << arr[0] << '\n';
  cout << arr[1] << '\n';
  cout << arr[2] << '\n';

  return 0;
}

#undef FAST_IO