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

  int N;
  cin >> N;
  // stack with first: height; second: duplicated count
  stack<pair<int, int>> s;
  int64 r = 0;
  while (N--) {
    // height
    int h;
    cin >> h;
    // duplicated height count
    int dhc = 0;
    while (!s.empty()) {
      // If top height is smaller than current height, they can see each other.
      while (!s.empty() && s.top().first < h) {
        // consider duplicated height.
        r += s.top().second;
        s.pop();
      }
      if (s.empty()) {
        break;
      }

      // Now top height can be higher than or equal to current height.
      // When greater, one higher person can be see each other.
      if (s.top().first > h) {
        ++r;
        break;
      }
      // When eqaul, every person who has euqal height can see each other.
      else {
        // update duplicated height count except current person.
        dhc = s.top().second;
        // current person can see people who have duplicated height.
        r += dhc;
        s.pop();
      }
    }
    s.push(make_pair(h, dhc + 1));
  }
  cout << r;

  return 0;
}

#undef FAST_IO