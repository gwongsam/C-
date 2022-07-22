#pragma once
#include <stack>
#include <string>
#include <vector>

#include "../public/public.hpp"
namespace Leetcode {
class Node {
 public:
  int val;
  Node* left;
  Node* right;
  Node* next;

  Node() : val(0), left(NULL), right(NULL), next(NULL) {}

  Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

  Node(int _val, Node* _left, Node* _right, Node* _next)
      : val(_val), left(_left), right(_right), next(_next) {}
};
struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};
// 0019
ListNode* RemoveNthFromEnd(ListNode* head, int n) {
  ListNode* dummy = new ListNode(0, head);
  ListNode* fast = head;
  ListNode* slow = dummy;
  for (int i = 0; i < n; ++i) {
    fast = fast->next;
  }
  while (fast) {
    fast = fast->next;
    slow = slow->next;
  }
  slow->next = slow->next->next;
  ListNode* ans = dummy->next;
  delete dummy;
  return ans;
}
//
// int EvalRPN(std::vector<std::string>& tokens) {
//   std::stack<int> stk;
//   int n = tokens.size();
//   for (int i = 0; i < n; i++) {
//     std::string& token = tokens[i];
//     if (isNumber(token)) {
//       stk.emplace(std::atoi(token.c_str()));
//     } else {
//       int num2 = stk.top();
//       stk.pop();
//       int num1 = stk.top();
//       stk.pop();
//       switch (token[0]) {
//         case '+':
//           stk.emplace(num1 + num2);
//         case '-':
//           stk.emplace(num1 - num2);
//         case '*':
//           stk.emplace(num1 * num2);
//         case '/':
//           stk.emplace(num1 / num2);
//           break;

//         default:
//           break;
//       }
//     }
//   }
//   return stk.top();
// }
// 0021
ListNode* MergeTwoLists(ListNode* list1, ListNode* list2) {
  // if (list1 == nullptr) {
  //   return list2;
  // } else if (list2 == nullptr) {
  //   return list1;
  // } else if (list1->val < list2->val) {
  //   list1->next = MergeTwoLists(list1->next, list2);
  //   return list1;
  // } else {
  //   list2->next = MergeTwoLists(list1, list2->next);
  //   return list2;
  // }
  ListNode* dummy = new ListNode(-1);
  ListNode* head = dummy;
  while (list1 != nullptr && list2 != nullptr) {
    if (list1->val < list2->val) {
      head->next = list1;
      list1 = list1->next;
    } else {
      head->next = list2;
      list2 = list2->next;
    }
    head = head->next;
  }
  head->next = list1 == nullptr ? list2 : list1;
  head = dummy->next;
  delete dummy;
  return head;
}
// 0083
ListNode* DeleteDuplicates(ListNode* head) {
  ListNode* temp = head;
  while (temp != nullptr && temp->next != nullptr) {
    if (temp->val == temp->next->val) {
      temp->next = temp->next->next;
    } else {
      temp = temp->next;
    }
  }
  return head;
}
// 0116
Node* ConnectRight(Node* root) {
  if (root == nullptr) {
    return root;
  }
  Node* leftmost = root;
  while (leftmost->left != nullptr) {
    Node* head = leftmost;
    while (head != nullptr) {
      head->left->next = head->right;
      if (head->next != nullptr) {
        head->right->next = head->next->left;
      }
      head = head->next;
    }
    leftmost = leftmost->left;
  }
  return root;
}
// 0203
ListNode* RemoveElements(ListNode* head, int val) {
  ListNode* dummy = new ListNode(-1, head);
  ListNode* temp = dummy;
  while (temp->next != nullptr) {
    if (temp->next->val == val) {
      temp->next = temp->next->next;
    } else {
      temp = temp->next;
    }
  }
  temp = dummy->next;
  delete dummy;
  return temp;
  // if (head == nullptr) {
  //   return head;
  // }
  // head->next = RemoveElement(head->next, val);
  // return head->val == val ? head->next : head;
  // ListNode* dummy = new ListNode(-1, head);
  // ListNode* slow = dummy;
  // ListNode* fast = head;
  // while (fast != nullptr) {
  //   if (fast->val == val) {
  //     slow->next = fast->next;
  //     fast = fast->next;
  //   } else {
  //     slow = slow->next;
  //     fast = fast->next;
  //   }
  // }
  // slow = dummy->next;
  // delete dummy;
  // return slow;
}
// 0206
ListNode* ReverseList(ListNode* head) {
  if (head == nullptr || head->next == nullptr) {
    return head;
  }
  ListNode* new_node = ReverseList(head->next);
  head->next->next = head;
  head->next = nullptr;
  return new_node;
  // ListNode* prev = nullptr;
  // ListNode* curr = head;
  // while (curr != nullptr) {
  //   ListNode* next = curr->next;
  //   curr->next = prev;
  //   prev = curr;
  //   curr = next;
  // }
  // return prev;
}
// 0617
TreeNode* MergeTrees(TreeNode* root1, TreeNode* root2) {
  if (root1 == nullptr) {
    return root2;
  }
  if (root2 == nullptr) {
    return root1;
  }
  TreeNode* merged = new TreeNode(root1->val + root2->val);
  merged->left = MergeTrees(root1->left, root2->left);
  merged->right = MergeTrees(root1->right, root2->right);
  return merged;
}
}  // namespace Leetcode