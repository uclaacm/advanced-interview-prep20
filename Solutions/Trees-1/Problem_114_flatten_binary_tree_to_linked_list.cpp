/*
    UCLA ACM ICPC: Interview Track Leetcode Problem Solutions

    Disclaimer: This is not the only valid solution and we do not claim our solutions 
    to be optimal in terms of runtime or memory usage, we are merely giving example 
    solutions to questions for learning purposes only

    Binary Tree Inorder Traversal
    Leetcode Problem 94
    https://leetcode.com/problems/binary-tree-inorder-traversal/
*/

// Given a binary tree, flatten it to a linked list in-place.
// For example, given the following tree:
/*
        1
       / \
      2   5
     / \   \
    3   4   6
*/
// The flattened tree should look like:
/*
    1
     \
      2
       \
        3
         \
          4
           \
            5
             \
              6
*/

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
    // We will use simple recursion to solve this problem
    void flatten(TreeNode* root) {
        // Base Case: If the root is NULL, there's nothing to do
        if(root == NULL) return;

        // Recursive Case: If the root has no left subtree, all
        // you need to do is flatten the right subtree
        else if(root->left == NULL) flatten(root->right);

        // Recursive Case: If the root has a left subtree...
        else {
            // Flatten both subtrees
            flatten(root->left);
            flatten(root->right);
            
            // Construct `leftTail`, a variable representing the
            // end of the flattened left subtree
            TreeNode* leftTail = root->left;
            while(leftTail->right != NULL) leftTail = leftTail->right;
            
            // Add the right subtree to the end of the left subtree
            leftTail->right = root->right;
            
            // Replace the location of the right subtree with the
            // left subtree
            root->right = root->left;

            // Replace the location of the left subtree with NULL
            root->left = NULL;
        }
    }
};

// Time Complexity: O(N) because each node is looked at a
// constant number of times in the worst case
// Space Complexity: O(1) because the algorithm is done in-place