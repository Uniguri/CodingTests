#include <cstring>
#include <iostream>

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

template <typename T, size_t N>
class Queue {
 public:
  static constexpr size_t kMaxSize = N;

  Queue() : size_(0), head_(0), tail_(0) {}

  inline size_t size(void) const { return size_; }
  inline bool empty(void) const { return size() == 0; }

  inline void push(T& val) { push(std::move(T{val})); }
  inline void push(T&& val) {
    if (tail_ < kMaxSize) {
      data_[tail_++] = std::move(val);
    } else {
      data_[tail_ = 0] = std::move(val);
    }
    ++size_;
  }

  inline void pop(void) {
    if (++head_ >= kMaxSize) {
      head_ = 0;
    }
    --size_;
  }

  inline T front(void) const { return data_[head_]; }
  inline T back(void) const { return data_[tail_ - 1]; }

 private:
  T data_[N];
  size_t size_;
  size_t head_;
  size_t tail_;
};

int main() {
  FAST_IO();

  int N;
  cin >> N;

  char s[32];
  Queue<int, 100'000> q;
  while (N--) {
    cin >> s;
    if (!strcmp(s, "push")) {
      int t;
      cin >> t;
      q.push(t);
    } else if (!strcmp(s, "pop")) {
      if (!q.empty()) {
        cout << q.front() << '\n';
        q.pop();
      } else {
        cout << -1 << '\n';
      }
    } else if (!strcmp(s, "size")) {
      cout << q.size() << '\n';
    } else if (!strcmp(s, "empty")) {
      cout << q.empty() << '\n';
    } else if (!strcmp(s, "front")) {
      if (!q.empty()) {
        cout << q.front() << '\n';
      } else {
        cout << -1 << '\n';
      }
    } else if (!strcmp(s, "back")) {
      if (!q.empty()) {
        cout << q.back() << '\n';
      } else {
        cout << -1 << '\n';
      }
    }
  }

  return 0;
}

#undef FAST_IO