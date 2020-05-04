/*
    UCLA ACM ICPC: Interview Track Leetcode Problem Solutions

    Disclaimer: This is not the only valid solution and we do not claim our solutions 
    to be optimal in terms of runtime or memory usage, we are merely giving example 
    solutions to questions for learning purposes only

    Binary Tree Postorder Traversal
    Leetcode Problem 145
    https://leetcode.com/problems/binary-tree-postorder-traversal/
*/

// Given a binary tree, return the postorder traversal of its nodes' values.
// Follow up: Recursive solution is trivial, could you do it iteratively?

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    // Our strategy is to run a preorder traversal of the tree,
    // putting each value we come across onto a stack. Popping
    // off all the values of the stack yields a postorder traversal.

    // This works because in a preorder traversal, the parent is
    // processed before the children. In this case, this means the
    // children will be put into the stack after the parent, and will
    // be taken out first.
    vector<int> postorderTraversal(TreeNode* root) {
        // Edge case: If root is NULL, then we don't do a traversal
        if(root == NULL) return {};

        stack<TreeNode*> s1;
        stack<int> s2;
        s1.push(root);

        while(!s1.empty()) {
            TreeNode* cur = s1.top();

            // Take `cur` out of `s1` and push its value to `s2`
            s1.pop();
            s2.push(cur->val);

            // Push the children of `cur` onto `s1` if they exist
            if(cur->left != NULL) s1.push(cur->left);
            if(cur->right != NULL) s1.push(cur->right);

            // Note: We push the left child onto the node first
            // because that means the right child will be on top in
            // Stack 1. After adding the values of each child onto
            // Stack 2, the left child's value will be on top of
            // the right child's, which is what we want. 
        }

        // Convert the stack into a vector and return it
        vector<int> result;
        while(!s2.empty()) {
            result.push_back(s2.top());
            s2.pop();
        }
        return result;
    }
};

// Time Complexity: O(N) because each node is looked at a constant number
// of times when it is being processed. It is also takes linear time to
// convert the second stack into a vector
// Space Complxity: O(N) because each of the data structures has as most
// N items in it in the worse case