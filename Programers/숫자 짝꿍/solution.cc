#include <math.h>

#include <map>
#include <string>
#include <vector>

using namespace std;

string solution(string X, string Y) {
  string answer = "";

  map<char, int> edx, edy;
  for (const char c : X) ++edx[c];
  for (const char c : Y) ++edy[c];

  for (char i = '9'; i >= '0'; --i) answer += string(min(edx[i], edy[i]), i);

  if (answer.empty())
    answer = string{"-1"};
  else if (answer[0] == '0')
    answer = string{"0"};

  return answer;
}