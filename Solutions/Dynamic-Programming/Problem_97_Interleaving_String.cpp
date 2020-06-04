/*
    UCLA ACM ICPC: Interview Track Leetcode Problem Solutions

    Disclaimer: This is not the only valid solution and we do not claim our solutions 
    to be optimal in terms of runtime or memory usage, we are merely giving example 
    solutions to questions for learning purposes only

    Interleaving String
    Leetcode Problem 97
    https://leetcode.com/problems/interleaving-string/
*/

// Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

class Solution {
public:
    // We will solve this problem using dynamic programming
    bool isInterleave(string s1, string s2, string s3) {
        // If the size of s3 isn't the num of the sizes of
        // s1 and s2, we can just stop here and return false
        if(s3.size() != s1.size() + s2.size()) return false;
        
        // Set up out DP vector.
        // DP[i][j] represents whether it is the first i
        // characters of s1 and the first j characters of
        // s2 interleave the first (i+j) characters of s3
        vector<vector <bool>> dp(s1.size() + 1);
        for(int i = 0; i < s1.size() + 1; i++) {
            for(int j = 0; j < s2.size() + 1; j++) {
                dp[i].push_back(false);
            }
        }
        
        for(int i=0; i < s1.length() + 1; i++) {
            for(int j=0; j < s2.length() + 1; j++) {

                // Base case: Trivially, the first 0 characters of s1 and
                // s2 always interleave the first 0 characters of s3
                if(i==0 && j==0)
                    dp[i][j] = true;

                // Recusrive case: The first i characters of s1 and the
                // first j characters of s2 always interleave the first
                // (i+j) characters of s3 if and only if...

                // The first (i-1) characters of s1 and the first j
                // characters of s2 interleave the first (i+j-1) characters
                // of s3, and the i-th character of s1 is the same as
                // the (i+j)-th character of s3

                // OR

                // The first i characters of s1 and the first (j-1)
                // characters of s2 interleave the first (i+j-1) characters
                // of s3, and the j-th character of s2 is the same as
                // the (i+j)-th character of s3

                else if(i == 0)
                    dp[i][j] = (dp[i][j-1] && s2[j-1] == s3[i+j-1]);
                else if(j == 0)
                    dp[i][j] = (dp[i-1][j] && s1[i-1] == s3[i+j-1]);
                else
                    dp[i][j] = (dp[i-1][j] && s1[i-1] == s3[i+j-1]) ||
                               (dp[i][j-1] && s2[j-1] == s3[i+j-1]);
            }
        }
        
        // Return the value that represents whether the characters of s1
        // and the characters of s2 interleave the characters of s3
        return dp[s1.length()][s2.length()];
    }
};

// Time Complexity: O(N * M), where N is the size of s1, and M is the size
// of s2. We have a nested loop where we do M conputations N times.
// Space Complexity: O(N * M), where N is the size of s1, and M is the size
// of s2. We make a N * M vector to solve the dynamic programming problem