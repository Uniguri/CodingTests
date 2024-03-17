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

int cnt[200'001];

int main() {
  FAST_IO();

  int N, K;
  cin >> N >> K;
  fill(&cnt[0], &cnt[200'001], 0x7FFFFFFF);
  queue<int> q;
  cnt[N] = 0;
  q.push(N);
  while (!q.empty()) {
    const int now = q.front();
    q.pop();
    const int cur_cnt = cnt[now];
    if (now == K) {
      cout << cur_cnt;
      return 0;
    }
    if (now - 1 == K || now + 1 == K || 2 * now == K) {
      cout << cur_cnt + 1;
      return 0;
    }

    if (0 < now && cnt[now - 1] > cur_cnt + 1) {
      cnt[now - 1] = cur_cnt + 1;
      q.push(now - 1);
    }
    if (now <= K * 1.5 && cnt[now + 1] > cur_cnt + 1) {
      cnt[now + 1] = cur_cnt + 1;
      q.push(now + 1);
    }
    if (now * 1.5 <= K && cnt[now * 2] > cur_cnt + 1) {
      cnt[now * 2] = cur_cnt + 1;
      q.push(now * 2);
    }
  }
  return 0;
}

#undef FAST_IO