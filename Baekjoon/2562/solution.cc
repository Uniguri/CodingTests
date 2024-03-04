#include <algorithm>
#include <array>
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

  array<int, 9> arr1;
  array<int, 9> arr2;
  for (int i = 0; i < 9; ++i) {
    int t;
    cin >> t;
    arr1[i] = arr2[i] = t;
  }
  sort(arr2.begin(), arr2.end());

  int idx = distance(arr1.begin(), find(arr1.begin(), arr1.end(), arr2[8]));
  cout << arr2[8] << '\n';
  cout << idx + 1;

  return 0;
}

#undef FAST_IO