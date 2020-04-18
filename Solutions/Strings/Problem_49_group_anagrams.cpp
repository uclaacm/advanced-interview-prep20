/*
    UCLA ACM ICPC: Interview Track Leetcode Problem Solutions

    Disclaimer: This is not the only valid solution and we do not claim our solutions 
    to be optimal in terms of runtime or memory usage, we are merely giving example 
    solutions to questions for learning purposes only

    Group Anagrams
    Leetcode Problem 49
    https://leetcode.com/problems/group-anagrams/
*/

class Solution {
public:
    // Our strategy is to map each string to its group of anagrams
    // We do this by categorizing each string by the counts of
    // each letter, and then mapping that to a group of anagrams.

    // Example:
    // ["aab", "aba", "baa", "abbccc"]
        // "a2b1c0...z0" -> ["aab", "aba", "baa"]
        // "a1b2c3...z0" -> ["abbccc"]
    vector<vector<string>> groupAnagrams(vector<string>& strs) {

        // If there are no strings in the given vector,
        // the answer is trivial
        if(strs.size() == 0) return {};

        // Initialize a vector of size 26:
        // The number of lowercase letters in the alphabet
        vector<int> count(26);
        unordered_map<string, vector<string>> anagrams;

        for(string s : strs) {
            // Fill the vector with 0's
            fill(count.begin(), count.end(), 0);

            // Get the counts of each character
            for(char c : s) count[c - 'a']++;
            // Note: Since we are guaranteed that S only contains
            // lowercase letters, we can map each letter to a
            // number by subtracting 'a'

            // Generate the string with the
            // counts of each character
            string key = "";
            for(int i = 0; i < 26; i++) {
                key += i + 'a';
                key += count[i];
            }

            // Add to the current string to the appropriate
            // list of anagrams using the key
            anagrams[key].push_back(s);
        }

        // Return a vector of all the anagram groups
        vector<vector<string>> result;
        for(auto i = anagrams.begin(); i != anagrams.end(); i++)
            result.push_back(i->second);
        return result;
    }
};

// Our time complexity is O(MN), where M is the number of strings given,
// and N is the average number of characters per string. The O(M) comes
// from looping through each string, and O(N) is for looping through
// each character of the string.

// Our space complexity is also O(MN). We store each given string as a
// part of our answer, which has a size of O(MN).