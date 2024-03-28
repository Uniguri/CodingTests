#include <algorithm>
#include <bitset>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <utility>

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

constexpr int dx[4] = {1, 0, -1, 0};
constexpr int dy[4] = {0, 1, 0, -1};

#define GLIFXY(x, y) (302 * y + x)  // GET_LINEAR_IDX_FROM_XY

int map[302][302];
int ntvc;  // need to visit count

int main() {
  FAST_IO();

  // Get inputs
  int N, M;
  cin >> N >> M;
  for (int y = 1; y <= N; ++y) {
    for (int x = 1; x <= M; ++x) {
      int t;
      cin >> t;
      if ((map[y][x] = t) > 0) {
        // increase ntvc.
        ++ntvc;
      }
    }
  }

  int r = 0;
  while (ntvc) {
    int nntvc = ntvc;             // new need to visit count
    int vc = 0;                   // visit count
    bitset<302 * 302> vis;        // is visited
    unordered_map<int, int> mbc;  // map before changed

    // Find first node to visit
    queue<pair<int, int>> q;
    for (int y = 1; y <= N && q.empty(); ++y) {
      for (int x = 1; x <= M && q.empty(); ++x) {
        if (map[y][x] > 0) {
          q.push(make_pair(x, y));
          // Check with visited node.
          vis[GLIFXY(x, y)] = 1;
          ++vc;
        }
      }
    }

    while (!q.empty()) {
      const auto& t = q.front();
      const int x = t.first;
      const int y = t.second;
      q.pop();

      int sc = 0;  // sea count
      for (int i = 0; i < 4; ++i) {
        const int nx = x + dx[i];
        const int ny = y + dy[i];

        // Check iceberg(map) exist. If there is backup map, use it.
        if (max(map[ny][nx], mbc[GLIFXY(nx, ny)]) > 0) {
          if (!vis[GLIFXY(nx, ny)]) {
            vis[GLIFXY(nx, ny)] = 1;
            ++vc;
            q.push(make_pair(nx, ny));
          }
        } else {
          ++sc;
        }
      }
      // If there are sea nodes, decrease iceberg count.
      if (sc && map[y][x] > 0) {
        // Save map before changed.
        mbc[GLIFXY(x, y)] = map[y][x];
        map[y][x] -= sc;
        // If iceberg disappeared, ntvc will descrease.
        if (map[y][x] <= 0) {
          --nntvc;
        }
      }
    }
    // When visited node count is differ to ntvc(need to visit count), There are
    // more than two iceberg.
    if (ntvc != vc) {
      cout << r;
      return 0;
    }

    // Update ntvc.
    ntvc = nntvc;
    ++r;
  }
  cout << 0;

  return 0;
}

#undef FAST_IO