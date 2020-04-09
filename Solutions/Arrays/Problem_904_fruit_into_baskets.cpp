/*
    UCLA ACM ICPC: Interview Track Leetcode Problem Solutions

    Disclaimer: This is not the only valid solution and we do not claim our solutions 
    to be optimal in terms of runtime or memory usage, we are merely giving example 
    solutions to questions for learning purposes only

    Fruit Into Baskets
    Leetcode Problem 904
    https://leetcode.com/problems/fruit-into-baskets/
*/

// In a row of trees, the i-th tree produces fruit with type tree[i].

// You start at any tree of your choice, then repeatedly perform the
// following steps:

    // Add one piece of fruit from this tree to your baskets.  If you cannot, stop.

    // Move to the next tree to the right of the current tree.  If there is no
    // tree to the right, stop.

// Note that you do not have any choice after the initial choice of starting tree:

// you must perform step 1, then step 2, then back to step 1, then step 2, and so
// on until you stop.

// You have two baskets, and each basket can carry any quantity of fruit, but you
// want each basket to only carry one type of fruit each.

// What is the total amount of fruit you can collect with this procedure?
class Solution {
public:
    // We want to solve this problem in O(N) time because an O(N^2) time solution
    // is trivial. The optimal solution probably won't in O(N logN) because the
    // nature of this problem won't let us rearrange the fruits.

    // One way to solve this problem is to start at the index 0 and begin picking
    // up fruit with your two baskets. When you come across a third fruit, you want
    // to empty the appropriate basket to make room for the third fruit. All the
    // while, you are keeping track of the total amount of fruits you have in the
    // baskets at one time, and when you reach the end, you return the max number.
    int totalFruit(vector<int>& tree) {
        // Represents the largest amount of fruits
        // you've had in your two baskets at one time.
        int maxFruits = 1;

        // A hash map that maps a partifular fruit to
        // the last index that we encounted that fruit
        unordered_map<int, int> map;

        // Two pointers. At the end of each loop iteration,
        // we will have a valid sequence of fruits which we
        // can put into two baskets. `i` represents the start
        // of that sequence, and `j` represents the first index
        // not in the sequence
        int i = 0, j = 0;

        while(j < tree.size()) {
            // Recall that `tree[j]` is a fruit, which we want to map
            // to the last index that we encountered it, which in
            // this case is `j`. 
            map[tree[j]] = j;

            // We want `j` to represent the first index not in the
            // sequence, so we increment `j`
            j++;

            // `map.size() > 2` means we have encountered a third
            // fruit that doesn't fit into our two baskets.
            if(map.size() > 2) {
                // We need to decide which basket to empty out.
                // Since we want our sequence of fruits to be
                // continuous, we want to empty the basket that
                // contains the fruit which we have not seen
                // the longest.

                // Example: Suppose we have fruits A and B in
                // our baskets and we encounter fruit C.

                // A A A B C -> Empty basket with A because we
                // have seen B more recently than A. Our new
                // sequence is B C

                // B A A A C -> Empty basket with B because we
                // have seen A more recently than B. Our new
                // sequence is A A A C

                // We do this by removing the fruit in our hash
                // map that contains the smallest index.
                int minIndex = tree.size() - 1;
                for(auto k = map.begin(); k != map.end(); k++) {
                    int index = k->second;
                    minIndex = min(minIndex, index);
                }
                map.erase(tree[minIndex]);

                // We update `i` to make it the start of our
                // new sequence. That value is `minIndex + 1`
                // since `minIndex` is the last index before
                // the sequence that is not in it.
                i = minIndex + 1;
            }

            // `j - i` represents the length of our current sequence
            // of fruits. If it's longer than our maximum sequence
            // length, update the `maxFruits` variable
            maxFruits = max(maxFruits, j - i);
        }

        return maxFruits;
    }
};