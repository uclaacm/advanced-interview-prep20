/*
    UCLA ACM ICPC: Interview Track Leetcode Problem Solutions

    Disclaimer: This is not the only valid solution and we do not claim our solutions 
    to be optimal in terms of runtime or memory usage, we are merely giving example 
    solutions to questions for learning purposes only

    ZigZag Conversion
    Leetcode Problem 6
    https://leetcode.com/problems/zigzag-conversion/
*/

// The string "PAYPALISHIRING" is written in a zigzag pattern on a
// given number of rows (in this case, 3) like this:

// P   A   H   N
// A P L S I I G
// Y   I   R

// And then read line by line: "PAHNAPLSIIGYIR"

// Write the code that will take a string and make this conversion
// given a number of rows

class Solution {
public:
    // Our algorithm will loop through the string to create a vector
    // representing each row. Then, we concatenate all the strings
    // to get our answer.
    string convert(string s, int numRows) {

        // If there is only one row, or there are more rows than
        // characters in the string, then the solution is trivially
        // just the string itself.
        if(numRows == 1 || s.size() < numRows) return s;
         
        vector<string> rows(numRows);
        int curRow = 0;
        bool goingDown = false;
        
        // Trace through the zigzag pattern. 
        for(char c: s) {
            rows[curRow] += c;

            // If we are on the first row, move from going up to going down.
            // It we are on the last row, move from going down to going up.
            if(curRow == 0 || curRow == numRows - 1) goingDown = !goingDown;

            // If we are going down, move down a row.
            // If we are going up, move up a row.
            curRow += goingDown ? 1 : -1;
        }
        
        // Concatenate all the row strings
        string result = "";
        for(string row : rows) result += row;
        return result;
    }
};

// The time complexity is O(n) because we make one loop through the string.
// The space complexity is O(n) because all the rows add up to a string
// that has the same size as the original string.