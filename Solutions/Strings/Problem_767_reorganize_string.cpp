/*
    UCLA ACM ICPC: Interview Track Leetcode Problem Solutions

    Disclaimer: This is not the only valid solution and we do not claim our solutions 
    to be optimal in terms of runtime or memory usage, we are merely giving example 
    solutions to questions for learning purposes only

    Reorganize String
    Leetcode Problem 767
    https://leetcode.com/problems/reorganize-string/
*/

// Given a string S, check if the letters can be rearranged so that
// two characters that are adjacent to each other are not the same.

// If possible, output any possible result.
// If not possible, return the empty string.

class Solution {
public:
    // Take the count of each letter in S and find the character C
    // with the most occurrences in S. If the size of S is N, and
    // There are more than (N + 1) / 2 occurrences of C, then we
    // can't reorganize the string (Why? Hint: Pigeonhole Principle)

    // Otherwise, we space out the occurrences of each character in
    // S starting with C. We do this by filling in positions in the
    // order of 0, 2, 4... and then 1, 3, 5...
    // Example:

    // aaaabbbbb
    // -> b_b_b_b_b
    // -> babababab

    // aaabbbcdd
    // -> a_a_a____
    // -> aba_a_b_b
    // -> abaca_b_b
    // -> abacadbdb
    string reorganizeString(string S) {
        // Take the count of each letter in S

        // Initialize a vector of 0's of size 26
        vector<int> hash(26, 0);
        for(int i = 0; i < S.size(); i++)
            hash[S[i] - 'a']++;
            // Note: Since we are guaranteed that S only contains
            // lowercase letters, we can map each letter to a
            // number by subtracting 'a'
        
        // Find the index in the vector with the highest value
        // and store the index and value
        int maxCount = 0;
        int maxIndex = 0;
        for(int i = 0; i < 26; i++) {
            if(maxCount < hash[i]) {
                maxIndex = i;
                maxCount = hash[i];
            }
        }
        
        // Pigeonhole Principle check
        if(maxCount > (S.size() + 1) / 2) return "";
        

        // Initialize a string of the same size as S,
        // but every character is a '*'
        string result(S.size(), '*');
        int curIndex = 0;

        // Starting with the character C, filling in positions in
        // the order of 0, 2, 4...
        // We do it this way because it's the only way to ensure
        // we can space out all instances of C.
        while(hash[maxIndex] > 0) {
            result[curIndex] = maxIndex + 'a';
            curIndex += 2;
            hash[maxIndex]--;
        }
        
        // Continue filling in positions in the order of 0, 2, 4...
        // but now we are allowed to use any character
        int j = 0;
        while(curIndex < S.size()) {
            while(hash[j] == 0) j++;
            result[curIndex] = j + 'a';
            hash[j]--;
            curIndex += 2;
        }
        
        // Fill in positions in the order of 1, 3, 5...
        curIndex = 1;
        while(curIndex < S.size()) {
            while(hash[j] == 0) j++;
            result[curIndex] = j + 'a';
            hash[j]--;
            curIndex += 2;
        }
        
        return result;
    }
};

// The time complexity is O(n) because we make loops through
// structures as big as the string.
// The space complexity is O(n) because we construct a new
// string of the same size for the answer.