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

constexpr int dx[4] = {1, 0, -1, 0};
constexpr int dy[4] = {0, 1, 0, -1};

char map[1002][1002];
int dist[1002][1002];

int main() {
  FAST_IO();

  int T;
  cin >> T;
  while (T--) {
    int w, h;
    cin >> w >> h;
    fill(&map[0][0], &map[1001][1001], 0);
    fill(&dist[0][0], &dist[1001][1001], 0x7FFFFFFF);
    queue<pair<int, int>> p, f;
    for (int y = 1; y <= h; ++y) {
      for (int x = 1; x <= w; ++x) {
        cin >> map[y][x];
        if (map[y][x] == '@') {
          dist[y][x] = 0;
          p.push(make_pair(x, y));
        } else if (map[y][x] == '*') {
          dist[y][x] = 0;
          f.push(make_pair(x, y));
        }
      }
    }

    while (!f.empty()) {
      const auto t = f.front();
      f.pop();
      const int x = t.first;
      const int y = t.second;
      const int now_dist = dist[y][x];
      for (int i = 0; i < 4; ++i) {
        const int nx = x + dx[i];
        const int ny = y + dy[i];
        if (map[ny][nx] == '.' && dist[ny][nx] > now_dist + 1) {
          dist[ny][nx] = dist[y][x] + 1;
          f.push(make_pair(nx, ny));
        }
      }
    }

    bool do_loop = true;
    while (do_loop && !p.empty()) {
      const auto t = p.front();
      p.pop();
      const int x = t.first;
      const int y = t.second;
      const int now_dist = dist[y][x];
      for (int i = 0; i < 4; ++i) {
        const int nx = x + dx[i];
        const int ny = y + dy[i];
        if (nx <= 0 || nx > w || ny <= 0 || ny > h) {
          cout << now_dist + 1 << '\n';
          do_loop = false;
          break;
        }
        if (map[ny][nx] == '.' && dist[ny][nx] > now_dist + 1) {
          dist[ny][nx] = now_dist + 1;
          p.push(make_pair(nx, ny));
        }
      }
    }
    if (do_loop) {
      cout << "IMPOSSIBLE\n";
    }
  }

  return 0;
}

#undef FAST_IO