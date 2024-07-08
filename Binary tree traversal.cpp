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

vector<TreeNode> vec;

/* Level-order traversal */
vector<int> levelOrder(TreeNode *root)
{
    // Initialize queue, add root node
    queue<TreeNode *> queue;
    queue.push(root);
    // Initialize a list to store the traversal sequence
    vector<int> vec;
    while (!queue.empty())
    {
        TreeNode *node = queue.front();
        queue.pop();              // Queue dequeues
        vec.push_back(node->val); // Save node value
        if (node->left != nullptr)
            queue.push(node->left); // Left child node enqueues
        if (node->right != nullptr)
            queue.push(node->right); // Right child node enqueues
    }
    return vec;
}

/* Pre-order traversal */
void preOrder(TreeNode *root)
{
    if (root == nullptr)
        return;
    // Visit priority: root node -> left subtree -> right subtree
    vec.push_back(root->val);
    preOrder(root->left);
    preOrder(root->right);
}

/* In-order traversal */
void inOrder(TreeNode *root)
{
    if (root == nullptr)
        return;
    // Visit priority: left subtree -> root node -> right subtree
    inOrder(root->left);
    vec.push_back(root->val);
    inOrder(root->right);
}

/* Post-order traversal */
void postOrder(TreeNode *root)
{
    if (root == nullptr)
        return;
    // Visit priority: left subtree -> right subtree -> root node
    postOrder(root->left);
    postOrder(root->right);
    vec.push_back(root->val);
}

int main()
{
}