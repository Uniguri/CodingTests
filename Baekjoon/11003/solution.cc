#include <deque>
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

  size_t N, L;
  cin >> N >> L;

  // arr deque; this deque is similar to sliding window.
  deque<int> adq;
  // min deque; this deque must have values with increasing order.
  deque<int> mdq;
  while (N--) {
    int t;
    cin >> t;

    // If current value(t) is smaller than back, pop back to make mdq increasing
    // order.
    while (!mdq.empty() && t < mdq.back()) {
      mdq.pop_back();
    }
    mdq.push_back(t);

    adq.push_back(t);
    if (adq.size() > L) {
      // If some value is out of range, pop it from mdq.
      if (mdq.front() == adq.front()) {
        mdq.pop_front();
      }
      adq.pop_front();
    }

    cout << mdq.front() << ' ';
  }

  return 0;
}

#undef FAST_IO