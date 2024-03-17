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

constexpr int dx[4] = {0, 1, 0, -1};
constexpr int dy[4] = {1, 0, -1, 0};

char map[1002][1002];
int cnt[1002][1002];

int main() {
  FAST_IO();

  int R, C;
  cin >> R >> C;
  fill(&map[0][0], &map[1001][1001], '#');
  fill(&cnt[0][0], &cnt[1001][1001], 0x7FFFFFFF);
  queue<pair<int, int>> j, f;
  for (int y = 1; y <= R; ++y) {
    for (int x = 1; x <= C; ++x) {
      cin >> map[y][x];
      if (map[y][x] == 'J') {
        cnt[y][x] = 0;
        j.push(make_pair(x, y));
      } else if (map[y][x] == 'F') {
        cnt[y][x] = 0;
        f.push(make_pair(x, y));
      }
    }
  }
  while (!f.empty()) {
    const auto& t = f.front();
    f.pop();
    const int x = t.first;
    const int y = t.second;
    for (int i = 0; i < 4; ++i) {
      const int nx = x + dx[i];
      const int ny = y + dy[i];
      if (map[ny][nx] == '.' && cnt[ny][nx] > cnt[y][x] + 1) {
        cnt[ny][nx] = cnt[y][x] + 1;
        f.push(make_pair(nx, ny));
      }
    }
  }
  while (!j.empty()) {
    const auto& t = j.front();
    j.pop();
    const int x = t.first;
    const int y = t.second;
    for (int i = 0; i < 4; ++i) {
      const int nx = x + dx[i];
      const int ny = y + dy[i];
      if ((ny <= 0 || ny > R || nx <= 0 || nx > C)) {
        cout << cnt[y][x] + 1 << endl;
        return 0;
      }
      if (map[ny][nx] == '.' && cnt[ny][nx] > cnt[y][x] + 1) {
        cnt[ny][nx] = cnt[y][x] + 1;
        j.push(make_pair(nx, ny));
      }
    }
  }
  cout << "IMPOSSIBLE" << endl;

  return 0;
}

#undef FAST_IO