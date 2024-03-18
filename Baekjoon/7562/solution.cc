#include <algorithm>
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

constexpr int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
constexpr int dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};

int dist[300][300];

int main() {
  FAST_IO();

  int n;
  cin >> n;
  while (n--) {
    fill(&dist[0][0], &dist[299][299], 0x7FFFFFFF);
    queue<pair<int, int>> q;
    int l;
    cin >> l;
    pair<int, int> s, e;
    cin >> s.first >> s.second >> e.first >> e.second;
    dist[s.second][s.first] = 0;
    q.push(make_pair(s.first, s.second));

    bool does_find = false;
    while (!does_find && !q.empty()) {
      const auto t = q.front();
      q.pop();
      const int x = t.first;
      const int y = t.second;
      if (x == e.first && y == e.second) {
        cout << dist[y][x] << '\n';
        does_find = true;
        break;
      }

      for (int i = 0; i < 8; ++i) {
        const int nx = x + dx[i];
        const int ny = y + dy[i];
        if (nx < 0 || nx >= l || ny < 0 || ny >= l) {
          continue;
        }
        if (dist[ny][nx] > dist[y][x] + 1) {
          dist[ny][nx] = dist[y][x] + 1;
          q.push(make_pair(nx, ny));
        }
      }
    }
    if (!does_find) {
      cout << 0 << '\n';
    }
  }

  return 0;
}

#undef FAST_IO