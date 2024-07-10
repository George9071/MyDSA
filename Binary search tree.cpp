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

/* Search node */
TreeNode *search(int num, TreeNode *root)
{
    TreeNode *cur = root;
    // Loop find, break after passing leaf nodes
    while (cur != nullptr)
    {
        // Target node is in cur's right subtree
        if (cur->val < num)
            cur = cur->right;
        // Target node is in cur's left subtree
        else if (cur->val > num)
            cur = cur->left;
        // Found target node, break loop
        else
            break;
    }
    // Return target node
    return cur;
}

/* Insert node */
void insert(int num, TreeNode *root)
{
    // If tree is empty, initialize root node
    if (root == nullptr)
    {
        root = new TreeNode(num);
        return;
    }
    TreeNode *cur = root, *pre = nullptr;
    // Loop find, break after passing leaf nodes
    while (cur != nullptr)
    {
        // Found duplicate node, thus return
        if (cur->val == num)
            return;
        pre = cur;
        // Insertion position is in cur's right subtree
        if (cur->val < num)
            cur = cur->right;
        // Insertion position is in cur's left subtree
        else
            cur = cur->left;
    }
    // Insert node
    TreeNode *node = new TreeNode(num);
    if (pre->val < num)
        pre->right = node;
    else
        pre->left = node;
}

/* Remove node */
void remove(int num, TreeNode *root)
{
    // If tree is empty, return
    if (root == nullptr)
        return;
    TreeNode *cur = root, *pre = nullptr;
    // Loop find, break after passing leaf nodes
    while (cur != nullptr)
    {
        // Found node to be removed, break loop
        if (cur->val == num)
            break;
        pre = cur;
        // Node to be removed is in cur's right subtree
        if (cur->val < num)
            cur = cur->right;
        // Node to be removed is in cur's left subtree
        else
            cur = cur->left;
    }
    // If no node to be removed, return
    if (cur == nullptr)
        return;
    // Number of child nodes = 0 or 1
    if (cur->left == nullptr || cur->right == nullptr)
    {
        // When the number of child nodes = 0 / 1, child = nullptr / that child node
        TreeNode *child = cur->left != nullptr ? cur->left : cur->right;
        // Remove node cur
        if (cur != root)
        {
            if (pre->left == cur)
                pre->left = child;
            else
                pre->right = child;
        }
        else
        {
            // If the removed node is the root, reassign the root
            root = child;
        }
        // Free memory
        delete cur;
    }
    // Number of child nodes = 2
    else
    {
        // Get the next node in in-order traversal of cur
        TreeNode *tmp = cur->right;
        while (tmp->left != nullptr)
        {
            tmp = tmp->left;
        }
        int tmpVal = tmp->val;
        // Recursively remove node tmp
        remove(tmp->val, root);
        // Replace cur with tmp
        cur->val = tmpVal;
    }
}