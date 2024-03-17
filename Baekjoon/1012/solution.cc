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

char map[52][52];

void dfs(int x, int y);

int main() {
  FAST_IO();

  int T;
  cin >> T;
  while (T--) {
    int M, N, K;
    fill(&map[0][0], &map[51][51], 0);
    cin >> M >> N >> K;
    while (K--) {
      int x, y;
      cin >> x >> y;
      map[y + 1][x + 1] = 1;
    }

    int r = 0;
    for (int y = 0; y <= N; ++y) {
      for (int x = 0; x <= M; ++x) {
        if (map[y][x]) {
          ++r;
          dfs(x, y);
        }
      }
    }
    cout << r << '\n';
  }

  return 0;
}

void dfs(int x, int y) {
  if (!map[y][x]) {
    return;
  }

  map[y][x] = 0;
  for (int i = 0; i < 4; ++i) {
    const int nx = x + dx[i];
    const int ny = y + dy[i];
    if (map[ny][nx]) {
      dfs(nx, ny);
    }
  }
}

#undef FAST_IO