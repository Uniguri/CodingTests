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

int map[101][101];

int dfs(int x, int y, int n, int m);

int main() {
  FAST_IO();

  fill(&map[0][0], &map[100][100], 1);
  int M, N, K;
  cin >> M >> N >> K;
  while (K--) {
    int x0, y0, x1, y1;
    cin >> x0 >> y0 >> x1 >> y1;
    for (int y = y0; y < y1; ++y) {
      for (int x = x0; x < x1; ++x) {
        map[y][x] = 0;
      }
    }
  }

  int c = 0;
  priority_queue<int, vector<int>, greater<int>> pq;
  for (int y = 0; y < M; ++y) {
    for (int x = 0; x < N; ++x) {
      if (map[y][x]) {
        ++c;
        pq.push(dfs(x, y, N, M));
      }
    }
  }
  cout << c << '\n';
  while (!pq.empty()) {
    cout << pq.top() << ' ';
    pq.pop();
  }

  return 0;
}

int dfs(int x, int y, int n, int m) {
  if (x < 0 || x >= n || y < 0 || y >= m || !map[y][x]) {
    return 0;
  }
  map[y][x] = 0;
  int ret = 1;
  for (int i = 0; i < 4; ++i) {
    const int nx = x + dx[i];
    const int ny = y + dy[i];
    if (0 <= nx && nx < n && 0 <= y && y < m && map[ny][nx]) {
      ret += dfs(nx, ny, n, m);
    }
  }
  return ret;
}

#undef FAST_IO