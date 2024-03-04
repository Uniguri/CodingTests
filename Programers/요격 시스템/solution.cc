#include <algorithm>
#include <vector>

using namespace std;

int solution(vector<vector<int>> targets) {
  int answer = 0;
  sort(targets.begin(), targets.end(),
       [](const vector<int>& lhs, const vector<int>& rhs) {
         return lhs[1] < rhs[1];
       });

  int now = 0;
  for (const auto& target : targets) {
    if (target[0] >= now) {
      now = target[1];
      answer++;
    }
  }

  return answer;
}