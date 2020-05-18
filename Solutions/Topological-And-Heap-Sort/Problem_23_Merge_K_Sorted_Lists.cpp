struct CompareHead { 
    bool operator()(ListNode* const& h1, ListNode* const& h2) 
    {  
        return h1->val > h2->val; 
    } 
}; 

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        //initialize a priority queue.
        priority_queue<ListNode*, vector<ListNode*>, CompareHead> Q;
        //use a dummy head to mark the beginning of the result linked list.
        ListNode* dummy = new ListNode(0);
        dummy->next = nullptr;
        ListNode* curr = dummy;
        //push all the linked lists in the lists vector into our priority queue
        //which orders them based on the custom comparator defined above.
        for(int i = 0; i < lists.size(); i++) {
            if(lists[i] != nullptr)
                Q.push(lists[i]);
        }
        //while we still have elements in the Priority Queue.
        while(Q.size()){
            ListNode* temp = Q.top();
            Q.pop();
            //append the popped head to the result linked list.
            curr->next = new ListNode(temp->val);
            curr = curr->next;
            curr->next = nullptr;
            //advance the head by one node if there are elements left in the
            //linked list.
            if(temp->next != nullptr)
                Q.push(temp->next);
        }
        return dummy->next;
    }
};