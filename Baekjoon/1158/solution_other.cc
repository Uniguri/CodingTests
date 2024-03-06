#include <iostream>
#include <queue>

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

  int N, K;
  cin >> N >> K;
  --K;
  queue<int> q;
  for (int i = 1; i <= N; ++i) {
    q.push(i);
  }

  cout << '<';
  int t;
  while (!q.empty()) {
    const int k = K % q.size();
    for (int i = 0; i < k; ++i) {
      t = q.front();
      q.pop();
      q.push(t);
    }
    t = q.front();
    q.pop();
    cout << t;
    if (q.empty()) {
      cout << '>';
    } else {
      cout << ", ";
    }
  }

  return 0;
}

#undef FAST_IO