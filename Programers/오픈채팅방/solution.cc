#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

vector<string> solution(vector<string> record) {
  vector<string> answer;

  unordered_map<string, string> nm;
  size_t tk;
  string uid, name, cmd;
  for (const auto& s : record) {
    stringstream ss{s};
    ss >> cmd >> uid;
    switch (cmd[0]) {
      case 'E':
        ss >> name;
        nm[uid] = name;
        break;
      case 'L':
        break;
      case 'C':
        ss >> name;
        nm[uid] = name;
        break;
      default:
        break;
    }
  }

  for (const auto& s : record) {
    stringstream ss{s};
    ss >> cmd >> uid;
    switch (cmd[0]) {
      case 'E':
        answer.push_back(nm[uid] + "님이 들어왔습니다.");
        break;
      case 'L':
        answer.push_back(nm[uid] + "님이 나갔습니다.");
        break;
      case 'C':
        break;
      default:
        break;
    }
  }

  return answer;
}