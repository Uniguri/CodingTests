#include <algorithm>
#include <array>
#include <iostream>
#include <string>

#define FAST_IO()                        \
  std::ios_base::sync_with_stdio(false); \
  std::cin.tie(NULL);                    \
  std::cout.tie(NULL)
using namespace std;

int main() {
  FAST_IO();
  constexpr int N = 5;
  int sum = 0;
  array<int, N> arr;

  for (int i = 0; i < N; ++i) {
    cin >> arr[i];
    sum += arr[i];
  }

  sort(arr.begin(), arr.end());
  cout << sum / N << '\n';
  cout << arr[N / 2];
  return 0;
}

#undef FAST_IO