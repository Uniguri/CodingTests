#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

vector<int> DoDijkstra(const int n, const int start,
                       const vector<vector<pair<int, int>>> dist_table) {
  vector<int> dist(n + 1, 1'990'000'001);
  priority_queue<pair<int, int>> pq;
  pq.push(make_pair(start, 0));
  dist[start] = 0;
  while (!pq.empty()) {
    const int current = pq.top().first;
    const int distance = -pq.top().second;
    pq.pop();

    if (distance > dist[current]) continue;

    for (int i = 0; i < dist_table[current].size(); ++i) {
      const auto& path = dist_table[current][i];
      const int next = path.first;
      const int next_distance = dist[current] + path.second;

      if (next_distance < dist[next]) {
        dist[next] = next_distance;
        pq.push(make_pair(next, -next_distance));
      }
    }
  }

  return dist;
}

int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
  int answer = 1'990'000'001;

  vector<vector<pair<int, int>>> dist_table(n + 1, vector<pair<int, int>>());
  for (int i = 0; i < fares.size(); ++i) {
    const auto& row = fares[i];
    const int c = row[0];
    const int d = row[1];
    const int f = row[2];
    dist_table[c].push_back(make_pair(d, f));
    dist_table[d].push_back(make_pair(c, f));
  }

  const auto& distance_from_s = DoDijkstra(n, s, dist_table);
  const auto& distance_from_a = DoDijkstra(n, a, dist_table);
  const auto& distance_from_b = DoDijkstra(n, b, dist_table);

  for (int i = 1; i <= n; ++i) {
    const int cost =
        distance_from_s[i] + distance_from_a[i] + distance_from_b[i];
    if (cost < answer) answer = cost;
  }

  return answer;
}