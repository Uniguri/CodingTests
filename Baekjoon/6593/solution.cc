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

char map[32][32][32];
int dist[32][32][32];

int main() {
  FAST_IO();

  while (1) {
    int L, R, C;
    cin >> L >> R >> C;
    if (L == 0 && R == 0 && C == 0) {
      break;
    }
    fill(&map[0][0][0], &map[31][31][31 + 1], 0);
    fill(&dist[0][0][0], &dist[31][31][31 + 1], 0x7FFFFFFF);
    queue<tuple<int, int, int>> q;
    for (int z = 1; z <= L; ++z) {
      for (int y = 1; y <= R; ++y) {
        for (int x = 1; x <= C; ++x) {
          cin >> map[z][y][x];
          if (map[z][y][x] == 'S') {
            dist[z][y][x] = 0;
            q.push(make_tuple(x, y, z));
          }
        }
      }
    }

    bool does_find = false;
    while (!does_find && !q.empty()) {
      const auto& t = q.front();
      const int x = get<0>(t);
      const int y = get<1>(t);
      const int z = get<2>(t);
      const int now_dist = dist[z][y][x];
      q.pop();

      for (int i = 0; i < 6; ++i) {
        const int nx = x + dx[i];
        const int ny = y + dy[i];
        const int nz = z + dz[i];
        if (map[nz][ny][nx] == 'E') {
          cout << "Escaped in " << now_dist + 1 << " minute(s).\n";
          does_find = true;
          break;
        }
        if (map[nz][ny][nx] == '.' && dist[nz][ny][nx] > now_dist + 1) {
          dist[nz][ny][nx] = now_dist + 1;
          q.push(make_tuple(nx, ny, nz));
        }
      }
    }
    if (!does_find) {
      cout << "Trapped!\n";
    }
  }

  return 0;
}

#undef FAST_IO