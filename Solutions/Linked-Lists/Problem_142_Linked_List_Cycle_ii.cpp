/*
    UCLA ACM ICPC: Interview Track Leetcode Problem Solutions

    Disclaimer: This is not the only valid solution and we do not claim our solutions 
    to be optimal in terms of runtime or memory usage, we are merely giving example 
    solutions to questions for learning purposes only

    Linked List Cycle ii
    Leetcode Problem 142
    https://leetcode.com/problems/linked-list-cycle-ii/
*/

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
    ListNode *detectCycle(ListNode *head) {
  		//if the head is null or the linked list contains a single node, then
        //we cannot have a cycle.  
        if(head == nullptr || head->next == nullptr)
  			return nullptr;

        //we start out with a slow pointer and a fast pointer.
        //The slow pointer moves one node every iteration while the fast pointer
        //moves two nodes in every iteration. When the two meet, we know that there
        //exists a cycle.
  		ListNode* slow = head;
  		ListNode* fast = head;
  		while(slow != nullptr && fast != nullptr){
  			slow = slow->next;
  			fast = fast->next;
  			if(fast != nullptr)
  				fast = fast->next;
            else
                break;
            if(slow == fast)
                break;
  		}

        //no cycle exists
  		if(slow == nullptr || fast == nullptr)
  			return nullptr;

        //The node that the two pointer meets is at a point in the cycle 
        //such that it is k places away from the first node in the cycle (from observation).
        //The head node is also k places away from the first node in the cycle.
        //So we start a pointer at the head and advace it as we advace the meeting point node pointer
        //one node at a time and break when the two meet (i.e. the node at the start of the linked list).
  		ListNode* start = head;
  		while(start != slow) {
  			start = start->next;
  			slow = slow->next;
  		}
  		return start;
    }
};