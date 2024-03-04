class Solution {
 public:
  bool isValid(string s) {
    stack<char> brackets_stack;
    for (const char& c : s) {
      if (c == '(' || c == '{' || c == '[')
        brackets_stack.push(c);
      else {
        if (brackets_stack.empty()) return false;

        switch (c) {
          case ')':
            if (brackets_stack.top() == '(')
              brackets_stack.pop();
            else
              return false;
            break;
          case '}':
            if (brackets_stack.top() == '{')
              brackets_stack.pop();
            else
              return false;
            break;
          case ']':
            if (brackets_stack.top() == '[')
              brackets_stack.pop();
            else
              return false;
            break;
        }
      }
    }

    if (!brackets_stack.empty()) return false;
    return true;
  }
};