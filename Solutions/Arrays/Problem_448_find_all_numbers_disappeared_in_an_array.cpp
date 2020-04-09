/*
    UCLA ACM ICPC: Interview Track Leetcode Problem Solutions

    Disclaimer: This is not the only valid solution and we do not claim our solutions 
    to be optimal in terms of runtime or memory usage, we are merely giving example 
    solutions to questions for learning purposes only

    Find All Numbers Disappeared in an Array
    Leetcode Problem 448
    https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/
*/

// Given an array of integers where 1 ≤ a[i] ≤ n (n = size of array),
// some elementsappear twice and others appear once.
// Find all the elements of [1, n] inclusive that do not appear in this array.
class Solution {
public:
    // We want to solve this problem without using extra space and in O(N)
    // runtime, since a O(N) time and O(N) space complexity can be easily
    // solved with a hash set.

    // For each number we encounter in the array, we want to somehow mark that we
    // have already seen this number. Since the integers in the array range from
    // 1 to n, we can use array indexes.
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        vector<int> result;

        // Our stretegy is for each number X we encounter, we can show that
        // we have seen this number by marking nums at index nums[X]-1 (We
        // subtract 1 since the X range from 1 to N). However, we want to
        // mark nums[nums[i]-1] in a way that preserves the value at
        // nums[nums[X]-1]. We do this be making nums[nums[X]-1] a
        // negative value
        for(int i = 0; i < nums.size(); i++) {
            // For each integer X in range 0 to N-1, it's not guaranteed that
            // nums[X] is positive since we manipulate the sign of array elements
            // in the loop. Therefore, every time we get the value at nums[X],
            // we take the absolute value of it.
            nums[abs(nums[i])-1] = -abs(nums[abs(nums[i])-1]);
        }
        
        // For each index i, if nums[i] is unmarked (positive), then
        // we know that we have not seen the number i+1 in the array
        // (We add 1 since i ranges from 0 to N-1).
        for(int i = 0; i < nums.size(); i++) {
            if(nums[i] > 0) result.push_back(i + 1);
        }
        
        return result;
    }
};