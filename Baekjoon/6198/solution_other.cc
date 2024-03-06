#include <algorithm>
#include <iostream>
#include <numeric>
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

  int N;
  cin >> N;

  uint64 r = 0;
  stack<int> s;
  while (N--) {
    int h;
    cin >> h;

    while (!s.empty() && h >= s.top()) {
      s.pop();
    }

    r += s.size();
    s.push(h);
  }
  cout << r;

  return 0;
}

#undef FAST_IO