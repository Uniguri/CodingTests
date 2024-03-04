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
  ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode* ret = new ListNode(0);
    ListNode* l = ret;

    ListNode *p = list1, *q = list2;
    while (p && q) {
      if (p->val <= q->val) {
        l->next = new ListNode(p->val);
        l = l->next;
        p = p->next;
      } else {
        l->next = new ListNode(q->val);
        l = l->next;
        q = q->next;
      }
    }

    if (!p) {
      while (q) {
        l->next = new ListNode(q->val);
        l = l->next;
        q = q->next;
      }
    } else {
      while (p) {
        l->next = new ListNode(p->val);
        l = l->next;
        p = p->next;
      }
    }

    return ret->next;
  }
};