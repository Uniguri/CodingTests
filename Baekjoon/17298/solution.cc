#include <iostream>
#include <stack>

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

  int ar[1'000'000];
  int N;
  cin >> N;
  for (int i = N - 1; i >= 0; --i) {
    cin >> ar[i];
  }

  stack<int> s;
  for (int i = 0; i < N; ++i) {
    const int t = ar[i];

    while (!s.empty() && s.top() <= t) {
      s.pop();
    }
    if (s.empty()) {
      ar[i] = -1;
    } else {
      ar[i] = s.top();
    }
    s.push(t);
  }
  for (int i = N - 1; i >= 0; --i) {
    cout << ar[i] << ' ';
  }

  return 0;
}

#undef FAST_IO