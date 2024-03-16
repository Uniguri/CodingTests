#include <algorithm>
#include <cstring>
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

const int dx[] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

int main() {
  FAST_IO();

  char map[102][102] = {
      0,
  };
  int cost[102][102];
  fill(&cost[0][0], &cost[101][101], 0x7FFFFFFF);

  int N, M;
  cin >> N >> M;
  for (int y = 1; y <= N; ++y) {
    for (int x = 1; x <= M; ++x) {
      cin >> map[y][x];
    }
  }

  queue<pair<int, int>> q;
  cost[1][1] = 1;
  q.push(make_pair(1, 1));
  while (!q.empty()) {
    const auto& t = q.front();
    q.pop();
    const int x = t.first;
    const int y = t.second;
    if (map[y][x] != '1') {
      continue;
    }
    map[y][x] = '0';
    for (int i = 0; i < (int)(sizeof(dx) / sizeof(dx[0])); ++i) {
      const int nx = x + dx[i];
      const int ny = y + dy[i];
      if (map[ny][nx] != '1') {
        continue;
      }
      if (cost[ny][nx] > cost[y][x] + 1) {
        cost[ny][nx] = cost[y][x] + 1;
        q.push(make_pair(nx, ny));
      }
    }
  }
  cout << cost[N][M];

  return 0;
}

#undef FAST_IO