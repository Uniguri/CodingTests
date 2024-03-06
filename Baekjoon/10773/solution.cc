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

  int K;
  cin >> K;
  stack<int> s;
  while (K--) {
    int t;
    cin >> t;
    if (t) {
      s.push(t);
    } else {
      s.pop();
    }
  }
  uint32 sum = 0;
  while (!s.empty()) {
    sum += s.top();
    s.pop();
  }
  cout << sum;

  return 0;
}

#undef FAST_IO