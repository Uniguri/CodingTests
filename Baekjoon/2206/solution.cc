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

constexpr int dx[4] = {1, 0, -1, 0};
constexpr int dy[4] = {0, 1, 0, -1};

char map[1002][1002];
unsigned int dwcbw[1002][1002];
unsigned int dwocbw[1002][1002];

using T = tuple<short, short, bool>;

int main() {
  FAST_IO();

  fill(&dwcbw[0][0], &dwcbw[1001][1001] + 1, 0xFFFFFFFF);
  fill(&dwocbw[0][0], &dwocbw[1001][1001] + 1, 0xFFFFFFFF);
  int N, M;
  cin >> N >> M;
  for (int y = 1; y <= N; ++y) {
    for (int x = 1; x <= M; ++x) {
      cin >> map[y][x];
    }
  }

  queue<T> q;
  dwcbw[1][1] = 1;
  q.push(make_tuple(1, 1, true));
  while (!q.empty()) {
    const auto& t = q.front();
    const int x = get<0>(t);
    const int y = get<1>(t);
    const bool cbw = get<2>(t);
    q.pop();

    for (int i = 0; i < 4; ++i) {
      const int nx = x + dx[i];
      const int ny = y + dy[i];

      if (map[ny][nx] == '0') {
        if (cbw && dwcbw[ny][nx] > dwcbw[y][x] + 1) {
          dwcbw[ny][nx] = dwcbw[y][x] + 1;
        } else if (!cbw && dwocbw[ny][nx] > dwocbw[y][x] + 1) {
          dwocbw[ny][nx] = dwocbw[y][x] + 1;
        } else {
          continue;
        }
        q.push(make_tuple(nx, ny, cbw));
      } else if (cbw && map[ny][nx] == '1') {
        if (dwocbw[ny][nx] > dwcbw[y][x] + 1) {
          dwocbw[ny][nx] = dwcbw[y][x] + 1;
          q.push(make_tuple(nx, ny, false));
        }
      }
    }
  }

  const auto& r = min(dwcbw[N][M], dwocbw[N][M]);
  if (r == 0xFFFFFFFF) {
    cout << -1;
  } else {
    cout << r;
  }

  return 0;
}

#undef FAST_IO