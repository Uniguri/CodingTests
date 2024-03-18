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

char map[27][27];

int dfs(int x, int y);

int main() {
  FAST_IO();

  int N;
  cin >> N;
  for (int y = 1; y <= N; ++y) {
    for (int x = 1; x <= N; ++x) {
      cin >> map[y][x];
    }
  }
  int c = 0;
  priority_queue<int, vector<int>, greater<int>> pq;
  for (int y = 1; y <= N; ++y) {
    for (int x = 1; x <= N; ++x) {
      if (map[y][x] == '1') {
        ++c;
        pq.push(dfs(x, y));
      }
    }
  }
  cout << c << '\n';
  while (!pq.empty()) {
    cout << pq.top() << '\n';
    pq.pop();
  }

  return 0;
}

int dfs(int x, int y) {
  if (x < 0 || x >= 27 || y < 0 || y >= 27 || map[y][x] != '1') {
    return 0;
  }

  map[y][x] = 0;
  int ret = 1;
  for (int i = 0; i < 4; ++i) {
    const int nx = x + dx[i];
    const int ny = y + dy[i];
    if (0 <= nx && nx < 27 && 0 <= ny && ny < 27 && map[ny][nx] == '1') {
      ret += dfs(nx, ny);
    }
  }
  return ret;
}

#undef FAST_IO