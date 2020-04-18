/*
    UCLA ACM ICPC: Interview Track Leetcode Problem Solutions

    Disclaimer: This is not the only valid solution and we do not claim our solutions 
    to be optimal in terms of runtime or memory usage, we are merely giving example 
    solutions to questions for learning purposes only

    Longest Valid Parentheses
    Leetcode Problem 32
    https://leetcode.com/problems/longest-valid-parentheses/
*/

// Given a string containing just the characters '(' and ')', find
// the length of the longest valid (well-formed) parentheses substring.

class Solution {
public:
    int longestValidParentheses(string s) {
        int left = 0;
        int right = 0;
        int longest = 0;
        
        // Iterate through the string from left to right, keeping
        // a counter of the number of left parentheses and the
        // number of right parentheses
        for(int i = 0; i < s.size(); i++) {
            if(s[i] == '(') left++;
            if(s[i] == ')') right++;
            
            // P1: When the number of left and right parentheses equal,
            // we have a valid set of parentheses of size `left + right`.

            // If P1, check to see if it's the longest valid set we've seen
            if(left == right) longest = max(longest, left + right);

            // When the number of right parentheses becomes larger than
            // the number of left parentheses, reset the counts to ensure
            // that P1 always remains true.
            if(right > left) {
                left = 0;
                right = 0;
            }
        }
        

        left = 0;
        right = 0;

        // Reset the counters, and do the exact same process going
        // from right to left.
        for(int i = s.size() - 1; i >= 0; i--) {
            if(s[i] == '(') left++;
            if(s[i] == ')') right++;
            if(left == right) longest = max(longest, left + right);

            // Remember to swap left and right when going from right to
            // left to ensure P1 remains true going from right to left
            if(left > right) {
                left = 0;
                right = 0;
            }
        }
        
        return longest;
    }
};

// The time complexity is O(n) because we make two loops
// through the string.
// The space is complexity is O(1) because we only store a
// constant amount of memory.