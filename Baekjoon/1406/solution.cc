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

template <typename T>
struct Node {
  T data;
  Node* fd;
  Node* bk;

  Node(T& d) : data(d), fd(nullptr), bk(nullptr) {}
  Node(T&& d) : data(std::move(d)), fd(nullptr), bk(nullptr) {}
  Node(T& d, Node* f, Node* b) : data(d), fd(f), bk(b) {}
  Node(T&& d, Node* f, Node* b) : data(std::move(d)), fd(f), bk(b) {}
};

template <typename T>
class List {
 public:
  List() : size_(0), head_(nullptr), tail_(nullptr) {}

  inline size_t size(void) noexcept { return size_; }
  inline bool empty(void) noexcept { return size_ == 0; }

  inline Node<T>* head(void) noexcept { return head_; }
  inline Node<T>* tail(void) noexcept { return tail_; }
  inline T& front(void) { return head_->get(); }
  inline T& back(void) { return tail_->get(); }

  void claer(void) {
    Node<T>* fd;
    for (Node<T>* node = head_; node; node = fd) {
      fd = node->fd;
      delete node;
    }

    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
  }
  // Insert value left of pos.
  // @param pos_or_null: position; if it is null, insert at end.
  // @param val: value to insert.
  // @return pointer to inserted node.
  inline Node<T>* insert(Node<T>* pos_or_null, T& val) {
    return insert(pos_or_null, T(val));
  }
  // Insert value left of pos.
  // @param pos_or_null: position; if it is nullptr, insert at end.
  // @param val: value to insert.
  // @return pointer to inserted node.
  Node<T>* insert(Node<T>* pos_or_null, T&& val) {
    if (!pos_or_null) {
      push_back(std::move(val));
      return tail_;
    } else if (pos_or_null == head_) {
      push_front(std::move(val));
      return head_;
    } else {
      Node<T>* new_node =
          new Node<T>(std::move(val), pos_or_null, pos_or_null->bk);
      pos_or_null->bk->fd = new_node;
      pos_or_null->bk = new_node;
      ++size_;
      return new_node;
    }
  }
  // Erase pos and return its right node.
  // @param pos: pointer to erase.
  // @return pointer to pos's right node. new tail_ if pos is tail_. nullptr if
  // list is empty after erase.
  Node<T>* erase(Node<T>* pos) {
    if (empty()) {
      return nullptr;
    }

    if (pos == head_) {
      pop_front();
      return head_;
    } else if (pos == tail_) {
      pop_back();
      return tail_;
    } else {
      Node<T>* fd = pos->fd;
      fd->bk = pos->bk;
      pos->bk->fd = fd;
      --size_;
      delete pos;
      return fd;
    }
  }
  inline void push_back(T& val) { return push_back(T(val)); }
  void push_back(T&& val) {
    if (size_ == 0) {
      size_ = 1;
      head_ = tail_ = new Node<T>(std::move(val));
    } else {
      Node<T>* new_node = new Node<T>(std::move(val), nullptr, tail_);
      tail_->fd = new_node;
      ++size_;
      tail_ = new_node;
    }
  }
  void pop_back(void) {
    if (size_ <= 1) {
      delete tail_;
      size_ = 0;
      head_ = tail_ = nullptr;
      return;
    }

    Node<T>* tail_bk = tail_->bk;
    tail_bk->fd = nullptr;
    --size_;
    delete tail_;
    tail_ = tail_bk;
  }
  inline void push_front(T& val) { return push_front(T(val)); }
  void push_front(T&& val) {
    if (size_ == 0) {
      size_ = 1;
      tail_ = head_ = new Node<T>(std::move(val));
    } else {
      Node<T>* new_node = new Node<T>(std::move(val), head_, nullptr);
      head_->bk = new_node;
      ++size_;
      head_ = new_node;
    }
  }
  void pop_front(void) {
    if (size_ <= 1) {
      delete head_;
      tail_ = head_ = nullptr;
      size_ = 0;
      return;
    }

    Node<T>* head_fd = head_->fd;
    head_fd->bk = nullptr;
    --size_;
    delete head_;
    head_ = head_fd;
  }

 private:
  size_t size_;
  Node<T>* head_;
  Node<T>* tail_;
};

int main() {
  FAST_IO();

  List<char> l;
  {
    char s[100'001];
    cin >> s;
    for (char* p = s; *p; ++p) {
      l.push_back(*p);
    }
    l.push_back(0);
  }
  int N;
  cin >> N;
  Node<char>* cur = l.tail();
  while (N--) {
    if (l.empty()) {
      l.push_back(0);
      cur = l.head();
    }

    char s[2];
    cin >> s;
    switch (*s) {
      case 'L': {
        if (cur->bk) {
          cur = cur->bk;
        }
        break;
      }
      case 'D': {
        if (cur->fd) {
          cur = cur->fd;
        }
        break;
      }
      case 'B': {
        if (cur->bk) {
          cur = l.erase(cur->bk);
        }
        break;
      }
      case 'P': {
        cin >> s;
        l.insert(cur, *s);
        break;
      }
    }
  }
  for (Node<char>* cur = l.head(); cur && cur->data != 0; cur = cur->fd) {
    cout << cur->data;
  }

  return 0;
}

#undef FAST_IO