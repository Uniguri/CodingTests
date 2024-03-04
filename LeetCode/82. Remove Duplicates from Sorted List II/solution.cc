/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
 public:
  ListNode* deleteDuplicates(ListNode* head) {
    if (!head) {
      return head;
    }
    ListNode* ret = new ListNode(0);
    ListNode* p = ret;
    int last_val = head->val;
    int last_count = 0;
    while (head) {
      if (head->val == last_val) {
        last_count++;
      } else {
        if (last_count == 1) {
          p->next = new ListNode(last_val);
          p = p->next;
        }
        last_val = head->val;
        last_count = 1;
      }
      head = head->next;
    }

    if (last_count == 1) {
      p->next = new ListNode(last_val);
    }

    return ret->next;
  }
};