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

constexpr int dx[4] = {1, 0, -1, 0};
constexpr int dy[4] = {0, 1, 0, -1};

int map[102][102];
bool vis[102][102];

void dfs(const int x, const int y, const int bound, const int n);

int main() {
  FAST_IO();

  int N;
  cin >> N;
  int min_h = 0x7FFFFFFF, max_h = 0;
  for (int y = 1; y <= N; ++y) {
    for (int x = 1; x <= N; ++x) {
      cin >> map[y][x];
      min_h = min(min_h, map[y][x]);
      max_h = max(max_h, map[y][x]);
    }
  }

  int max_r = 0;
  for (int h = min_h; h <= max_h; ++h) {
    fill(&vis[0][0], &vis[101][101], 0);
    int r = 0;
    for (int y = 1; y <= N; ++y) {
      for (int x = 1; x <= N; ++x) {
        if (map[y][x] >= h && !vis[y][x]) {
          ++r;
          dfs(x, y, h, N);
        }
      }
    }
    max_r = max(max_r, r);
  }
  cout << max_r;

  return 0;
}

void dfs(const int x, const int y, const int bound, const int n) {
  if (x < 1 || x > n || y < 1 || y > n || map[y][x] < bound || vis[y][x]) {
    return;
  }
  vis[y][x] = 1;
  for (int i = 0; i < 4; ++i) {
    const int nx = x + dx[i];
    const int ny = y + dy[i];
    if (0 < nx && nx <= n && 0 < ny && ny <= n && map[ny][nx] >= bound &&
        !vis[ny][nx]) {
      dfs(nx, ny, bound, n);
    }
  }
}

#undef FAST_IO