#include <algorithm>
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

int dfs(int map[502][502], int x, int y);

int main() {
  FAST_IO();

  int map[502][502] = {
      0,
  };

  int n, m;
  cin >> n >> m;
  for (int y = 1; y <= n; ++y) {
    for (int x = 1; x <= m; ++x) {
      cin >> map[y][x];
    }
  }
  int max_val = 0;
  int count = 0;
  for (int y = 1; y <= n; ++y) {
    for (int x = 1; x <= m; ++x) {
      const int t = dfs(map, x, y);
      if (t) {
        max_val = max(t, max_val);
        ++count;
      }
    }
  }
  cout << count << '\n' << max_val;

  return 0;
}

int dfs(int map[502][502], int x, int y) {
  if (!map[y][x]) {
    return 0;
  }
  map[y][x] = 0;
  return 1 + dfs(map, x + 1, y) + dfs(map, x - 1, y) + dfs(map, x, y - 1) +
         dfs(map, x, y + 1);
}

#undef FAST_IO