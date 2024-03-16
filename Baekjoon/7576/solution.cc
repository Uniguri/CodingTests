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

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

// tomatos~~
int tmt[1002][1002];

int main() {
  FAST_IO();

  fill(&tmt[0][0], &tmt[1001][1001], -1);

  int M, N;
  cin >> M >> N;

  queue<pair<int, int>> q;
  for (int y = 1; y <= N; ++y) {
    for (int x = 1; x <= M; ++x) {
      cin >> tmt[y][x];
      if (tmt[y][x] == 1) {
        q.push(make_pair(x, y));
      }
    }
  }

  int r = 0;
  while (!q.empty()) {
    bool does_affect = false;
    queue<pair<int, int>> nq;
    while (!q.empty()) {
      const auto& t = q.front();
      q.pop();
      const int x = t.first;
      const int y = t.second;
      for (int i = 0; i < (int)(sizeof(dx) / sizeof(dx[0])); ++i) {
        const int nx = x + dx[i];
        const int ny = y + dy[i];
        if (tmt[ny][nx] == 0) {
          tmt[ny][nx] = 1;
          does_affect = true;
          nq.push(make_pair(nx, ny));
        }
      }
    }

    q = std::move(nq);
    if (does_affect) {
      ++r;
    }
  }
  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= M; ++j) {
      if (tmt[i][j] == 0) {
        cout << -1;
        return 0;
      }
    }
  }
  cout << r;

  return 0;
}

#undef FAST_IO