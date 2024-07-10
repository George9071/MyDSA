#include <bits/stdc++.h>
using namespace std;

/* Binary tree node */
struct TreeNode
{
    int val;         // Node value
    TreeNode *left;  // Pointer to left child node
    TreeNode *right; // Pointer to right child node
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

vector<TreeNode*> res1, path;
vector<vector<TreeNode*>> res2, res3;

/*  Example 1
    Given a binary tree, search and record all nodes with a value of 7, please return a list of nodes.
*/

/* Pre-order traversal: Example one */
void preOrder(TreeNode *root) {
    if (root == nullptr) {
        return;
    }
    if (root->val == 7) {
        // Record solution
        res1.push_back(root);
    }
    preOrder(root->left);
    preOrder(root->right);
}

/*  Example 2
    Given a binary tree, search and record all nodes with a value of 7, please return the paths from the root node to these nodes
*/

/* Pre-order traversal: Example two */
void preOrder(TreeNode *root) {
    if (root == nullptr) {
        return;
    }
    // Attempt
    path.push_back(root);
    if (root->val == 7) {
        // Record solution
        res2.push_back(path);
    }
    preOrder(root->left);
    preOrder(root->right);
    // Retract
    path.pop_back();
}

/*  Example 3
    Given a binary tree, search and record all nodes with a value of 7 
    and return the paths from the root to these nodes, 
    requiring that the paths do not contain nodes with a value of 3
*/

/* Pre-order traversal: Example 3 */
void preOrder(TreeNode *root) {
    // Pruning
    if (root == nullptr || root->val == 3) {
        return;
    }
    // Attempt
    path.push_back(root);
    if (root->val == 7) {
        // Record solution
        res3.push_back(path);
    }
    preOrder(root->left);
    preOrder(root->right);
    // Retract
    path.pop_back();
}