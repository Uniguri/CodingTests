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

int dist[1000001];

int main() {
  FAST_IO();

  fill(&dist[0], &dist[1000001], 0x7FFFFFFF);
  int f, s, g, u, d;
  cin >> f >> s >> g >> u >> d;
  queue<int> q;
  q.push(s);
  dist[s] = 0;
  while (!q.empty()) {
    const int now = q.front();
    q.pop();
    const int now_dist = dist[now];
    if (now == g) {
      cout << now_dist;
      return 0;
    }

    if (now - d > 0 && dist[now - d] > now_dist + 1) {
      dist[now - d] = now_dist + 1;
      q.push(now - d);
    }
    if (now + u <= f && dist[now + u] > now_dist + 1) {
      dist[now + u] = now_dist + 1;
      q.push(now + u);
    }
  }
  cout << "use the stairs";

  return 0;
}

#undef FAST_IO