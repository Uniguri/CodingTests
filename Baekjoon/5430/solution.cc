#include <deque>
#include <iostream>
#include <sstream>
#include <string>

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

void GetArray(deque<int>& dq, int n) {
  string s;
  cin >> s;
  stringstream ss{std::move(s)};
  int t;
  char c;
  ss >> c;
  for (int i = 0; i < n; ++i) {
    ss >> t >> c;
    dq.push_back(t);
  }
}

void PrintArray(deque<int>& dq, const bool do_reverse) {
  cout << '[';
  if (!dq.empty()) {
    if (do_reverse) {
      while (dq.size() > 1) {
        cout << dq.back() << ',';
        dq.pop_back();
      }
      cout << dq.back();
    } else {
      while (dq.size() > 1) {
        cout << dq.front() << ',';
        dq.pop_front();
      }
      cout << dq.front();
    }
  }
  cout << "]\n";
}

int main() {
  FAST_IO();

  int tcc;
  cin >> tcc;
  char s[100'001];
  while (tcc--) {
    int n;
    cin >> s >> n;
    deque<int> dq;
    GetArray(dq, n);

    bool do_reverse = false;
    bool is_correct = true;
    for (char* p = s; *p; ++p) {
      const char c = *p;
      if (c == 'R') {
        do_reverse ^= 1;
      } else if (c == 'D') {
        if (dq.empty()) {
          cout << "error\n";
          is_correct = false;
          break;
        }

        if (do_reverse) {
          dq.pop_back();
        } else {
          dq.pop_front();
        }
      }
    }
    if (is_correct) {
      PrintArray(dq, do_reverse);
    }
  }

  return 0;
}

#undef FAST_IO