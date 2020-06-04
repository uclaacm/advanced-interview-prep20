/*
    UCLA ACM ICPC: Interview Track Leetcode Problem Solutions

    Disclaimer: This is not the only valid solution and we do not claim our solutions 
    to be optimal in terms of runtime or memory usage, we are merely giving example 
    solutions to questions for learning purposes only

    Best Time to Buy and Sell Stock
    Leetcode Problem 121
    https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
*/

// Say you have an array for which the ith element is the price of a given stock on day i.

// If you were only permitted to complete at most one transaction (i.e., buy one and sell
// one share of the stock), design an algorithm to find the maximum profit.

// Note that you cannot sell a stock before you buy one.

class Solution {
public:
    // We will solve this problem by checking
    // the max profit we can make if we sell on
    // day 1, day 2, ..., and day N. The answer
    // will be the max of these values.

    // Intuition: If we're guaranteed to sell on
    // day i, then we must buy before or on day i.
    // The day we choose to buy must be the minimum
    // price before or on day i
    int maxProfit(vector<int>& prices) {
        // `min` represents the minimum value we
        // have encountered so far. We keep this
        // variable so that we don't have to
        // continuously calculate the minimum
        // value before day i.
        int min = INT_MAX;
        
        // `max` represents the maximum profit
        // we can make completing one transaction
        // using the values we have seen so far.
        // We initially set it to 0 because we'll
        // never make a transaction that results
        // in a negative profit.
        int max = 0;
        
        for(int i = 0; i < prices.size(); i++) {
            
            // Update `min` if necessary
            if(prices[i] < min) min = prices[i];
            
            // Update `max` if necessary. This involves comparing
            // our current `max` with a new tranaction: Buying
            // today and selling on the day where that price of
            // the stock is `min`
            if(prices[i] - min > max) max = prices[i] - min;
        }
        
        // After looping through the entire vector, `max`
        // represents the maximum profit we can make completing
        // one transaction using the values in the vector
        return max;
    }
};

// Time Complexity: O(n) - We traverse through the vector once.
// Space Complexity: O(1) - We only store useful information in two variables.