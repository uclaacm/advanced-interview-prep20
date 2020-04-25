/*
    UCLA ACM ICPC: Interview Track Leetcode Problem Solutions

    Disclaimer: This is not the only valid solution and we do not claim our solutions 
    to be optimal in terms of runtime or memory usage, we are merely giving example 
    solutions to questions for learning purposes only

    Copy List with Random Pointer
    Leetcode Problem 138
    https://leetcode.com/problems/copy-list-with-random-pointer/
*/

// A linked list is given such that each node contains an additional
// random pointer which could point to any node in the list or null.

// Return a deep copy of the list.

// The Linked List is represented in the input/output as a list of n nodes.
// Each node is represented as a pair of [val, random_index] where:
    // val: an integer representing Node.val
    // random_index: the index of the node (range from 0 to n-1) where random
        // pointer points to, or null if it does not point to any node.

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    // Our strategy will be to create a copy of the list within the given
    // list, and then separate the two at the end.
    // Example:

    // Given: 1 -> 2 -> 3 -> 4
    // Copy: 1 -> 1' -> 2 -> 2' -> 3 -> 3' -> 4 -> 4'
    // Separate: 1 -> 2 -> 3 -> 4
    //           1' -> 2' -> 3' -> 4'
    Node* copyRandomList(Node* head) {
        // Base case check
        if(head == NULL) return NULL;

        // Create a copy of the list within the given list,
        // ignoring the values of the random pointers
        Node* cur = head;
        while(cur != NULL) {
            // Suppose cur is node A
            // ... -> A -> B -> ...
            Node* next = cur->next;
            // ... -> A -> A' | B -> ...
            cur->next = new Node(cur->val);
            // ... -> A -> A' -> B -> ...
            cur->next->next = next;
            // cur is now node B
            cur = next;
        }
        
        // Add the values of the random pointers to
        // the duplicate elements of the list
        cur = head;
        while(cur != NULL) {
            // Suppose cur is node A
            // ... -> A -> A' -> B -> B'...
            if(cur->random != NULL)
                // Suppose A->random = C. This
                // instruction makes A'->random = C'
                cur->next->random = cur->random->next;
            // cur is now node B.
            cur = cur->next->next;
        }
        
        // Separate the duplicates from the original list
        cur = head;
        // The head of the copy
        Node* copyHead = head->next;
        Node* copy = copyHead;
        while(copy->next != NULL) {
            // Suppose cur is node A
            // ... -> A -> A' -> B -> B' -> ...
            // A now points to B
            cur->next = cur->next->next;
            // cur now equals B
            cur = cur->next;
            
            // A' now points to B'
            copy->next = copy->next->next;
            // copy now equals B'
            copy = copy->next;
        }

        // The last node (Z) still points to it's copy,
        // so we must make it so it doesn't point to anything
        // ... -> Z -> Z'
        cur->next = NULL;
        // ... -> Z
        return copyHead;
    }
};