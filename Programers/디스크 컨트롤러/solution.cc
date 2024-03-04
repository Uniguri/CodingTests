#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> jobs) {
  int answer = 0;
  sort(jobs.begin(), jobs.end(),
       [](const vector<int>& lhs, const vector<int>& rhs) {
         return lhs[1] < rhs[1];
       });

  int st = 0, os = jobs.size();
  while (!jobs.empty()) {
    for (int i = 0; i < jobs.size(); ++i) {
      if (jobs[i][0] <= st) {
        answer += (jobs[i][1] + st - jobs[i][0]);
        st += jobs[i][1];
        jobs.erase(jobs.begin() + i);
        break;
      }

      if (i == jobs.size() - 1) ++st;
    }
  }

  answer /= os;

  return answer;
}