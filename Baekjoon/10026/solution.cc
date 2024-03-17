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

char mfh[102][102];
char mfc[102][102];

void dfs(char map[102][102], int x, int y, char c);

int main() {
  FAST_IO();

  int N;
  cin >> N;
  for (int y = 1; y <= N; ++y) {
    for (int x = 1; x <= N; ++x) {
      char t;
      cin >> t;
      mfh[y][x] = t;
      if (t == 'R') {
        mfc[y][x] = 'G';
      } else {
        mfc[y][x] = t;
      }
    }
  }

  int rh = 0, rc = 0;
  for (int y = 1; y <= N; ++y) {
    for (int x = 1; x <= N; ++x) {
      if (mfh[y][x]) {
        ++rh;
        dfs(mfh, x, y, mfh[y][x]);
      }
      if (mfc[y][x]) {
        ++rc;
        dfs(mfc, x, y, mfc[y][x]);
      }
    }
  }
  cout << rh << ' ' << rc;
  return 0;
}

void dfs(char map[102][102], int x, int y, char c) {
  if (!map[y][x] || map[y][x] != c) {
    return;
  }

  map[y][x] = 0;
  for (int i = 0; i < 4; ++i) {
    const int nx = x + dx[i];
    const int ny = y + dy[i];
    if (map[ny][nx] == c) {
      dfs(map, nx, ny, c);
    }
  }
}

#undef FAST_IO