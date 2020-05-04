/*
    UCLA ACM ICPC: Interview Track Leetcode Problem Solutions

    Disclaimer: This is not the only valid solution and we do not claim our solutions 
    to be optimal in terms of runtime or memory usage, we are merely giving example 
    solutions to questions for learning purposes only

    Binary Tree Level Order Traversal
    Leetcode Problem 102
    https://leetcode.com/problems/binary-tree-level-order-traversal/
*/

// Given a binary tree, return the level order traversal of its nodes'
// values. (ie, from left to right, level by level).

// For example:
// Given binary tree,

//    3
//   / \
//  9  20
//    /  \
//   15   7

// return its level order traversal as:

// [
//   [3],
//   [9,20],
//   [15,7]
// ]

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    // Our strategy is to use BFS with a queue. For each level process
    // the correct amount of nodes on that level while removing them from
    // the queue. Meanwhile, we add nodes on the next level to the queue
    vector<vector<int>> levelOrder(TreeNode* root) {
        // Edge case: If root is NULL, then we don't do a traversal
        if(root == NULL) return {};

        queue<TreeNode*> q;
        q.push(root);

        // Represents how many nodes are on the current level
        // Our first level only has the root, so it's initially set
        // to 1
        int nodesOnThisLevel = 1;

        // Represents how many nodes are on the next level
        // We don't know how many are on the next level yet, so
        // we set it to 0, and increment it when necessary
        int nodesOnNextLevel = 0;

        vector<vector<int>> result;

        // If there are nodes on our current level, there are
        // still nodes we need to process
        while(nodesOnThisLevel != 0) {
            // This vector represents the current level
            vector<int> level;

            // Process each node of this level
            for(int i = 0; i < nodesOnThisLevel; i++) {
                // Process the front node. This involves just
                // putting it in our vector and dequeueing it
                TreeNode* cur = q.front();
                level.push_back(cur->val);
                q.pop();

                // Add the left child of the current node to the
                // queue if possible
                if(cur->left != NULL) {
                    nodesOnNextLevel++;
                    q.push(cur->left);
                }

                // Add the right child of the current node to the
                // queue if possible
                if(cur->right != NULL) {
                    nodesOnNextLevel++;
                    q.push(cur->right);
                }
            }

            // Add the level to our vector of levels
            result.push_back(level);

            // Update the level variables
            nodesOnThisLevel = nodesOnNextLevel;
            nodesOnNextLevel = 0;
        }
        return result;
    }
};

// Time Complexity: O(N) because each node is looked at a
// constant number of times
// Space Complexity: O(N) because in the worst case, all
// nodes can be in the queue at all times