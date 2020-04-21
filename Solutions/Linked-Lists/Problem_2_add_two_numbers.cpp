/*
    UCLA ACM ICPC: Interview Track Leetcode Problem Solutions

    Disclaimer: This is not the only valid solution and we do not claim our solutions 
    to be optimal in terms of runtime or memory usage, we are merely giving example 
    solutions to questions for learning purposes only

    Add Two Numbers
    Leetcode Problem 2
    https://leetcode.com/problems/add-two-numbers/
*/

// You are given two non-empty linked lists representing two
// non-negative integers. The digits are stored in reverse order
// and each of their nodes contain a single digit. Add the two
// numbers and return it as a linked list.

// Note: You may assume the two numbers do not contain any
// leading zero, except the number 0 itself.

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // If a linked list represents the number 0,
        // just return the other linked list
        if(l1->val == 0 && l1->next == NULL) return l2;
        if(l2->val == 0 && l2->next == NULL) return l1;
        
        // Create a node for the head. It will have the
        // value of the 1's place of l1's val + l2's val,
        // which we get from doing `% 10`
        int val = l1->val + l2->val;
        ListNode* head = new ListNode(val % 10);

        // Represents the value we carry over to the next
        // node. It will either be 0 or 1 depending on
        // whether `val >= 10`
        int carry = val / 10;

        // The loop will compute the next node, which we
        // have to connect to the previous one, which is
        // represented by this pointer
        ListNode* prev = head;
        
        // While there are still nodes to compute
        while(l1->next != NULL || l2->next != NULL) {
            // Compute the value of the next node
            int val1 = l1->next ? l1->next->val : 0;
            int val2 = l2->next ? l2->next->val : 0;
            ListNode* next = new ListNode((val1 + val2 + carry) % 10);

            // Determine if we have to carry over a 1 or not
            carry = (val1 + val2 + carry) / 10;

            // Update the pointers
            prev->next = next;
            prev = next;
            l1 = l1->next ? l1->next : l1;
            l2 = l2->next ? l2->next : l2;
        }

        // If `carry == 1`, then we need to create a new node
        // with the value of 1 to place at the end.
        // Ex. 9 -> 9 (99) + 1 (1) = 0 -> 0 -> 1 (100)
        if(carry) {
            ListNode* tail = new ListNode(1);
            prev->next = tail;
        }
        
        return head;
    }
};