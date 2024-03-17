#include <algorithm>
#include <iostream>
#include <queue>
#include <tuple>

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

constexpr int dx[6] = {1, 0, 0, -1, 0, 0};
constexpr int dy[6] = {0, 1, 0, 0, -1, 0};
constexpr int dz[6] = {0, 0, 1, 0, 0, -1};

char map[102][102][102];

int main() {
  FAST_IO();

  int M, N, H;
  fill(&map[0][0][0], &map[101][101][101], -1);
  cin >> M >> N >> H;
  queue<tuple<int, int, int>> q;
  for (int z = 1; z <= H; ++z) {
    for (int y = 1; y <= N; ++y) {
      for (int x = 1; x <= M; ++x) {
        int t;
        cin >> t;
        map[z][y][x] = t;
        if (t == 1) {
          q.push(make_tuple(x, y, z));
        }
      }
    }
  }
  int r = 0;
  while (!q.empty()) {
    queue<tuple<int, int, int>> nq;
    while (!q.empty()) {
      const auto t = q.front();
      q.pop();
      const int x = get<0>(t);
      const int y = get<1>(t);
      const int z = get<2>(t);
      if (map[z][y][x] != 1) {
        continue;
      }
      for (int i = 0; i < 6; ++i) {
        const int nx = x + dx[i];
        const int ny = y + dy[i];
        const int nz = z + dz[i];
        if (map[nz][ny][nx] == 0) {
          map[nz][ny][nx] = 1;
          nq.push(make_tuple(nx, ny, nz));
        }
      }
    }
    if (!nq.empty()) {
      ++r;
      q = std::move(nq);
    }
  }
  for (int z = 1; z <= H; ++z) {
    for (int y = 1; y <= N; ++y) {
      for (int x = 1; x <= M; ++x) {
        if (map[z][y][x] == 0) {
          cout << -1;
          return 0;
        }
      }
    }
  }
  cout << r;

  return 0;
}

#undef FAST_IO