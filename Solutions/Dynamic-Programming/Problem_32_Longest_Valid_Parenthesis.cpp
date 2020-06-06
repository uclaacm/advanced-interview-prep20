class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> parens;
        vector<int> dp(s.length(), 0);
        for(int i = 0; i < s.length(); i++){
            if(s[i] == '('){
                parens.push(i);
            }else{
                if(parens.size()){
                    int j = parens.top();
                    if(j != 0){
                        dp[i] = dp[i-1] + dp[j-1] + 2; 
                    }else{
                        dp[i] = dp[i-1] + 2;
                    }
                    parens.pop();
                }
            }
        }
        int max_substring = 0;
        for(int i = 0; i < s.length(); i++) max_substring = max(max_substring, dp[i]);
        return max_substring;
    }
};