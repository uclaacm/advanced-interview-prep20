/*
    UCLA ACM ICPC: Interview Track Leetcode Problem Solutions

    Disclaimer: This is not the only valid solution and we do not claim our solutions 
    to be optimal in terms of runtime or memory usage, we are merely giving example 
    solutions to questions for learning purposes only

    Binary Tree Preorder Traversal
    Leetcode Problem 144
    https://leetcode.com/problems/binary-tree-preorder-traversal/
*/

// Given a binary tree, return the preorder traversal of its nodes' values.
// Follow up: Recursive solution is trivial, could you do it iteratively?

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
    // Our strategy is to use DFS with a stack, where the top of the
    // stack represents the next element we need to process
    vector<int> preorderTraversal(TreeNode* root) {
        // Edge case: If root is NULL, then we don't do a traversal
        if(root == NULL) return {};

        vector<int> result;
        stack<TreeNode*> s;
        s.push(root);

        while(!s.empty()) {
            // Process the current node. This involves
            // popping it off the stack and putting it in our vector
            TreeNode* cur = s.top();
            s.pop();
            result.push_back(cur->val);
            
            // Add the right child to the stack if it exists
            if(cur->right != NULL) s.push(cur->right);

            // Add the left child to the stack if it exists
            if(cur->left != NULL) s.push(cur->left);

            // Note: We add the right child and then the left child
            // because we want to process the left child first. Since
            // stacks are LIFO, the last thing going into it will be
            // the first thing coming out.
        }
        return result;
    }
};

// Time Complexity: O(N) because each node is looked at a
// constant number of times
// Space Complexity: O(N) because in the worst case, all
// nodes can be in the stack at all times