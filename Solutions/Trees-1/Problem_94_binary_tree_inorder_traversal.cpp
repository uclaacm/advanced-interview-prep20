/*
    UCLA ACM ICPC: Interview Track Leetcode Problem Solutions

    Disclaimer: This is not the only valid solution and we do not claim our solutions 
    to be optimal in terms of runtime or memory usage, we are merely giving example 
    solutions to questions for learning purposes only

    Binary Tree Inorder Traversal
    Leetcode Problem 94
    https://leetcode.com/problems/binary-tree-inorder-traversal/
*/

// Given a binary tree, return the inorder traversal of its nodes' values.
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
    // Our strategy is to use DFS with a stack. We will have it so that
    // whenever we read the top of the stack, it is the next node we have
    // to process. We do this by trying to always move left until we're
    // forced to do something else
    vector<int> inorderTraversal(TreeNode* root) {
        // Edge case: If root is NULL, then we don't do a traversal
        if(root == NULL) return {};

        vector<int> result;
        stack<TreeNode*> s;
        TreeNode* cur = root->left;
        s.push(root);

        while(true) {
            // If our current node is not NULL, go left
            if(cur != NULL) {
                s.push(cur);
                cur = cur->left;
            } else {
                // If there is nothing in the stack at this point, we
                // have processed all nodes and are done
                if(s.empty()) break;

                // Inorder traversal goes left-current-right. Since we've
                // been going left and adding to the stack until we hit
                // NULL, we know that the top node on the stack is one
                // one we need to process

                // Remove the top of the stack and add its value
                cur = s.top();
                s.pop();
                result.push_back(cur->val);

                // After you process your current node, go right
                cur = cur->right;
            }
        }
        return result;
    }
};

// Time Complexity: O(N) because each node is looked at a
// constant number of times
// Space Complexity: O(N) because in the worst case, all
// nodes can be in the stack at all times