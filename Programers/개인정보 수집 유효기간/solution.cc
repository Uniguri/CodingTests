#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

int ParseDate(const string& date) {
  stringstream ss(date);
  char trash;
  int year, month, day;
  ss >> year >> trash >> month >> trash >> day;
  month += year * 12;
  day += month * 28;
  return day;
}

pair<char, int> ParseTerm(const string& term) {
  stringstream ss(term);
  char term_name;
  int period;
  ss >> term_name >> period;
  return {term_name, period};
}

pair<int, char> ParsePrivacy(const string& privacy) {
  int date = ParseDate(privacy);
  char term = privacy[privacy.length() - 1];
  return {date, term};
}

int CalculatePrivacyPeriod(const int& date, int period) {
  return date + period * 28 - 1;
}

vector<int> solution(string today, vector<string> terms,
                     vector<string> privacies) {
  vector<int> answer;

  const int& now = ParseDate(today);

  unordered_map<char, int> term_map;
  for (const string& term : terms) {
    const pair<char, int>& t = ParseTerm(term);
    term_map[t.first] = t.second;
  }

  for (int i = 0; i < privacies.size(); ++i) {
    const pair<int, char>& privacy = ParsePrivacy(privacies[i]);
    const int& privacy_date = privacy.first;
    const char& privacy_term = privacy.second;
    const int& privacy_max_date =
        CalculatePrivacyPeriod(privacy_date, term_map[privacy_term]);

    if (now > privacy_max_date) answer.push_back(i + 1);
  }

  return answer;
}