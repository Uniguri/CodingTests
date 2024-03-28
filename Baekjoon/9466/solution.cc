#include <bitset>
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

int arr[100000];

int main() {
  FAST_IO();

  int T;
  cin >> T;
  while (T--) {
    int iic = 0;          // is included count
    int inic = 0;         // is not included count
    bitset<100000> iib;   // is included bit
    bitset<100000> inib;  // is not included bit

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
      int t;
      cin >> t;
      arr[i] = --t;
      if (i == t) {
        iib[i] = true;
        ++iic;
      }
    }

    for (int i = 0; i < n && iic + inic < n; ++i) {
      if (iib[i] || inib[i]) {
        continue;
      }
      bitset<100001> io;  // is occured
      io[i] = true;
      queue<int> q;
      q.push(i);

      int next = i;
      // Max number of loop is n - iic.
      for (int itr_count = 0; itr_count < n - iic - inic; ++itr_count) {
        next = arr[next];
        // When i(n)ib[next] is set, there is a one-way indication. stop loop.
        if (iib[next] || inib[next]) {
          break;
        }
        // next cannot be smaller than i because we iterate from left.
        else if (next < i) {
          break;
        }
        // When io[next] is set, there is a loop.
        else if (io[next]) {
          while (!q.empty() && q.front() != next) {
            inib[q.front()] = true;
            ++inic;
            q.pop();
          }
          while (!q.empty()) {
            const int t = q.front();
            q.pop();
            iib[t] = true;
            ++iic;
          }
          break;
        } else {
          io[next] = true;
          q.push(next);
        }
      }
      while (!q.empty()) {
        const int t = q.front();
        q.pop();
        inib[t] = true;
        ++inic;
      }
    }

    cout << n - iic << '\n';
  }

  return 0;
}

#undef FAST_IO