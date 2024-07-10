#include <bits/stdc++.h>
using namespace std;

/* AVL tree node */
struct TreeNode
{
    int val{};         // Node value
    int height = 0;    // Node height
    TreeNode *left{};  // Left child
    TreeNode *right{}; // Right child
    TreeNode() = default;
    explicit TreeNode(int x) : val(x) {}
};

/* Get node height */
int height(TreeNode *node)
{
    // Empty node height is -1, leaf node height is 0
    return node == nullptr ? -1 : node->height;
}

/* Update node height */
void updateHeight(TreeNode *node)
{
    // Node height equals the height of the tallest subtree + 1
    node->height = max(height(node->left), height(node->right)) + 1;
}

/* Get balance factor */
int balanceFactor(TreeNode *node)
{
    // Empty node balance factor is 0
    if (node == nullptr)
        return 0;
    // Node balance factor = left subtree height - right subtree height
    return height(node->left) - height(node->right);
}

/* Right rotation operation */
TreeNode *rightRotate(TreeNode *node)
{
    TreeNode *child = node->left;
    TreeNode *grandChild = child->right;
    // Rotate node to the right around child
    child->right = node;
    node->left = grandChild;
    // Update node height
    updateHeight(node);
    updateHeight(child);
    // Return the root of the subtree after rotation
    return child;
}

/* Left rotation operation */
TreeNode *leftRotate(TreeNode *node)
{
    TreeNode *child = node->right;
    TreeNode *grandChild = child->left;
    // Rotate node to the left around child
    child->left = node;
    node->right = grandChild;
    // Update node height
    updateHeight(node);
    updateHeight(child);
    // Return the root of the subtree after rotation
    return child;
}

/* Perform rotation operation to restore balance to the subtree */
TreeNode *rotate(TreeNode *node)
{
    // Get the balance factor of node
    int _balanceFactor = balanceFactor(node);
    // Left-leaning tree
    if (_balanceFactor > 1)
    {
        if (balanceFactor(node->left) >= 0)
        {
            // Right rotation
            return rightRotate(node);
        }
        else
        {
            // First left rotation then right rotation
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }
    // Right-leaning tree
    if (_balanceFactor < -1)
    {
        if (balanceFactor(node->right) <= 0)
        {
            // Left rotation
            return leftRotate(node);
        }
        else
        {
            // First right rotation then left rotation
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }
    // Balanced tree, no rotation needed, return
    return node;
}

/* Insert node */
void insert(int val, TreeNode *root)
{
    root = insertHelper(root, val);
}

/* Recursively insert node (helper method) */
TreeNode *insertHelper(TreeNode *node, int val)
{
    if (node == nullptr)
        return new TreeNode(val);
    /* 1. Find insertion position and insert node */
    if (val < node->val)
        node->left = insertHelper(node->left, val);
    else if (val > node->val)
        node->right = insertHelper(node->right, val);
    else
        return node;    // Do not insert duplicate nodes, return
    updateHeight(node); // Update node height
    /* 2. Perform rotation operation to restore balance to the subtree */
    node = rotate(node);
    // Return the root node of the subtree
    return node;
}

/* Remove node */
void remove(int val, TreeNode *root)
{
    root = removeHelper(root, val);
}

/* Recursively remove node (helper method) */
TreeNode *removeHelper(TreeNode *node, int val)
{
    if (node == nullptr)
        return nullptr;
    /* 1. Find and remove the node */
    if (val < node->val)
        node->left = removeHelper(node->left, val);
    else if (val > node->val)
        node->right = removeHelper(node->right, val);
    else
    {
        if (node->left == nullptr || node->right == nullptr)
        {
            TreeNode *child = node->left != nullptr ? node->left : node->right;
            // Number of child nodes = 0, remove node and return
            if (child == nullptr)
            {
                delete node;
                return nullptr;
            }
            // Number of child nodes = 1, remove node
            else
            {
                delete node;
                node = child;
            }
        }
        else
        {
            // Number of child nodes = 2, remove the next node in in-order traversal and replace the current node with it
            TreeNode *temp = node->right;
            while (temp->left != nullptr)
            {
                temp = temp->left;
            }
            int tempVal = temp->val;
            node->right = removeHelper(node->right, temp->val);
            node->val = tempVal;
        }
    }
    updateHeight(node); // Update node height
    /* 2. Perform rotation operation to restore balance to the subtree */
    node = rotate(node);
    // Return the root node of the subtree
    return node;
}