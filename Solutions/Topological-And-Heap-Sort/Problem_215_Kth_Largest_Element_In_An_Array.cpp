/*
    UCLA ACM ICPC: Interview Track Leetcode Problem Solutions

    Disclaimer: This is not the only valid solution and we do not claim our solutions 
    to be optimal in terms of runtime or memory usage, we are merely giving example 
    solutions to questions for learning purposes only

    Kth Largest Element in an Array
    Leetcode Problem 215
    https://leetcode.com/problems/kth-largest-element-in-an-array/submissions/
*/

class Solution {
public:
    // A trivial solution is to sort the vector to find
    // the k-th largest, which has a runtime on O(N log N).
    // We can do a bit better by building a max heap with
    // the contents of the vector, and then finding the
    // largest element k times.
    int findKthLargest(vector<int>& nums, int k) {
        // By default, priority queues in C++ are max heaps
        priority_queue<int> maxHeap(nums.begin(), nums.end());

        // Pull out the first k-1 largest elements
        for(int i = 0; i < k-1; i++) maxHeap.pop();
        
        // Get the kth largest element
        return maxHeap.top();
    }
};

// Time complexity: O(N + K logN). It takes O(N) to build the
// heap, and we remove from the heap K times, which takes
// O(log N) time.

// Space complexity: O(N). A heap takes O(N) space