#include <iostream>
#include <list>

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
  list<int> l;
  for (int i = 1; i <= N; ++i) {
    l.push_back(i);
  }

  cout << '<';
  int t;
  while (!l.empty()) {
    const int k = K % l.size();
    for (int i = 0; i < k; ++i) {
      t = l.front();
      l.pop_front();
      l.push_back(t);
    }
    t = l.front();
    l.pop_front();
    cout << t;
    if (l.empty()) {
      cout << '>';
    } else {
      cout << ", ";
    }
  }

  return 0;
}

#undef FAST_IO