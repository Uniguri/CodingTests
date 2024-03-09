#include <iostream>
#include <string>

template <typename T, size_t N>
class Dequeue {
 public:
  static constexpr size_t kMaxSize = N;

  Dequeue(void) : size_(0), head_(0), tail_(0) {}

  inline void push_front(const T& val) {
    if (head_ == 0) {
      data_[head_ = kMaxSize - 1] = val;
    } else {
      data_[--head_] = val;
    }
    ++size_;
  }
  inline void push_back(const T& val) {
    if (tail_ < kMaxSize) {
      data_[tail_++] = val;
    } else {
      tail_ = 0;
      data_[tail_++] = val;
    }
    ++size_;
  }

  inline void pop_front(void) {
    if (++head_ >= kMaxSize) {
      head_ = 0;
    }
    --size_;
  }
  inline void pop_back(void) {
    if (--tail_ > kMaxSize) {
      tail_ = kMaxSize - 1;
    }
    --size_;
  }

  inline size_t size(void) { return size_; }
  inline bool empty(void) { return size_ == 0; }

  inline T front(void) { return data_[head_]; }
  inline T back(void) {
    if (tail_ == 0) {
      return data_[kMaxSize - 1];
    } else {
      return data_[tail_ - 1];
    }
  }

 private:
  T data_[kMaxSize];
  size_t size_;
  size_t head_, tail_;
};

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

int main() {
  FAST_IO();

  int N;
  cin >> N;

  string s;
  Dequeue<int, 10'000> dq;
  while (N--) {
    cin >> s;
    if (s == "push_front") {
      int t;
      cin >> t;
      dq.push_front(t);
    } else if (s == "push_back") {
      int t;
      cin >> t;
      dq.push_back(t);
    } else if (s == "pop_front") {
      if (!dq.empty()) {
        cout << dq.front() << '\n';
        dq.pop_front();
      } else {
        cout << -1 << '\n';
      }
    } else if (s == "pop_back") {
      if (!dq.empty()) {
        cout << dq.back() << '\n';
        dq.pop_back();
      } else {
        cout << -1 << '\n';
      }
    } else if (s == "size") {
      cout << dq.size() << '\n';
    } else if (s == "empty") {
      cout << dq.empty() << '\n';
    } else if (s == "front") {
      if (!dq.empty()) {
        cout << dq.front() << '\n';
      } else {
        cout << -1 << '\n';
      }
    } else if (s == "back") {
      if (!dq.empty()) {
        cout << dq.back() << '\n';
      } else {
        cout << -1 << '\n';
      }
    }
  }
  return 0;
}

#undef FAST_IO