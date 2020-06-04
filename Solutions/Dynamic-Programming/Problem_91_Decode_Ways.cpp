/*
    UCLA ACM ICPC: Interview Track Leetcode Problem Solutions

    Disclaimer: This is not the only valid solution and we do not claim our solutions 
    to be optimal in terms of runtime or memory usage, we are merely giving example 
    solutions to questions for learning purposes only

    Decode Ways
    Leetcode Problem 91
    https://leetcode.com/problems/decode-ways/
*/

// A message containing letters from A-Z is being encoded to numbers
// using the following mapping:

// 'A' -> 1
// 'B' -> 2
// ...
// 'Z' -> 26

// Given a non-empty string containing only digits, determine the
// total number of ways to decode it.

class Solution {
public:
    // Base case: If the string length is 1, then there's one way to
    // decode the string iff the string is in between 1 - 9
    // Base case: If the string length is 2, then there's one way to
    // decode the string iff the string is in between 10 - 26
    // Recursive case: If the string length is N, then the string can
    // be split into two cases:
        // The first (N-1) characters + the last character
        // The first (N-2) characters + the last two characters
    // If the last character can be decoded, then we add the number
    // of ways to decode the first (N-1) characters to our result
    // If the last two character can be decoded, then we add the number
    // of ways to decode the first (N-2) characters to our result
    int numDecodings(string s) {

        // Instead of recursion, we will use dynamic programming for
        // optimization purposes. Given a string of length N, we need
        // the subsolutions for the N-1 and N-2 case, so we only need
        // to allocate two variables for this solution.

        // Given a number i...
        // let X be the subsolution for the i-1 case
        // Let Y be the subsolution for the i case
        
        // Pretend that this is our first iteration (i=1)
        // x represents the number of ways to decode nothing
        // y represents the number of ways to decode the first character
        ////////////////////////////////////////////////////////////////
        // There is 1 way to decode nothing
        int x = 1;
        // Then there is 1 way to decode the first character
        // if it is nonzero, and 0 otherwise
        int y = s[0] != '0' ? 1 : 0;
        
        for(int i = 2; i <= s.size(); i++) {
            int z = 0;
            
            // first represents the i'th character
            // second represents the (i-1)'th and i'th character
            int first = stoi(s.substr(i-1, 1));
            int second = stoi(s.substr(i-2, 2));

            // If the i'th character can be decoded by itself, then
            // we want to add the number of ways to decode the
            // first (i-1) characters
            if(first >= 1 && first <= 9) z += y;

            // If the last two characters can be decoded by itself,
            // then we want to add the number of ways to decode the
            // first (i-2) characters
            if(second >= 10 && second <= 26) z += x;

            // Update variables:
            x = y;  // x now represents the number of ways to decode
                    // the first (i-1) characters
            y = z;  // y now represents the number of ways to decode
                    // the first i characters
        }
        
        // By the end of the loop, y represents the
        // number of ways to decode the entire string
        return y;
    }
};

// Time Complexity: O(n) - We traverse through the string once.
// Space Complexity: O(1) - We only store useful information in
// a constant number variables.