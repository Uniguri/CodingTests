#include <string>
#include <vector>

using namespace std;

vector<int> solution(int n, int s) {
  vector<int> answer;
  if (s < n) return vector<int>{-1};

  answer.reserve(s / n + 1);
  for (int i = 0; i < n - s % n; ++i) answer.push_back(s / n);
  for (int i = 0; i < s % n; ++i) answer.push_back(s / n + 1);

  return answer;
}