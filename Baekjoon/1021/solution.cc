#include <chrono>
#include <cmath>
#include <deque>
#include <iostream>
#include <thread>

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

  int N, M;
  cin >> N >> M;

  deque<int> dq;
  for (int i = 1; i <= N; ++i) {
    dq.push_back(i);
  }
  int r = 0;
  while (M-- && !dq.empty()) {
    int t;
    cin >> t;
    if (t == dq.front()) {
      dq.pop_front();
    } else {
      int mlc = 0;
      while (dq.front() != t) {
        dq.push_back(dq.front());
        dq.pop_front();
        ++mlc;
      }
      mlc = min(mlc, (int)dq.size() - mlc);
      dq.pop_front();
      r += mlc;
    }
  }
  cout << r;

  return 0;
}

#undef FAST_IO