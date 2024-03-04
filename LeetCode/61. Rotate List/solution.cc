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
  ListNode* rotateRight(ListNode* head, int k) {
    if (!head || !head->next) {
      return head;
    }
    ListNode* const startNode = head;
    ListNode* newStartNode = nullptr;
    // check list size : O(N)
    int listSize = 1;
    while (head->next) {
      listSize++;
      head = head->next;
    }
    // make cycle list
    head->next = startNode;

    // make rotated list : O(k)
    head = startNode;
    k %= listSize;
    for (int i = 0; i < listSize - k - 1; i++) {
      head = head->next;
    }
    newStartNode = head->next;
    head->next = nullptr;

    return newStartNode;
  }
};