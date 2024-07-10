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

/* Array-based binary tree class */
class ArrayBinaryTree
{
public:
    /* Constructor */
    ArrayBinaryTree(vector<int> arr)
    {
        tree = arr;
    }

    /* List capacity */
    int size()
    {
        return tree.size();
    }

    /* Get the value of the node at index i */
    int val(int i)
    {
        // If index is out of bounds, return INT_MAX, representing a null
        if (i < 0 || i >= size())
            return INT_MAX;
        return tree[i];
    }

    /* Get the index of the left child of the node at index i */
    int left(int i)
    {
        return 2 * i + 1;
    }

    /* Get the index of the right child of the node at index i */
    int right(int i)
    {
        return 2 * i + 2;
    }

    /* Get the index of the parent of the node at index i */
    int parent(int i)
    {
        return (i - 1) / 2;
    }

    /* Level-order traversal */
    vector<int> levelOrder()
    {
        vector<int> res;
        // Traverse array
        for (int i = 0; i < size(); i++)
        {
            if (val(i) != INT_MAX)
                res.push_back(val(i));
        }
        return res;
    }

    /* Pre-order traversal */
    vector<int> preOrder()
    {
        vector<int> res;
        dfs(0, "pre", res);
        return res;
    }

    /* In-order traversal */
    vector<int> inOrder()
    {
        vector<int> res;
        dfs(0, "in", res);
        return res;
    }

    /* Post-order traversal */
    vector<int> postOrder()
    {
        vector<int> res;
        dfs(0, "post", res);
        return res;
    }

private:
    vector<int> tree;

    /* Depth-first traversal */
    void dfs(int i, string order, vector<int> &res)
    {
        // If it is an empty spot, return
        if (val(i) == INT_MAX)
            return;
        // Pre-order traversal
        if (order == "pre")
            res.push_back(val(i));
        dfs(left(i), order, res);
        // In-order traversal
        if (order == "in")
            res.push_back(val(i));
        dfs(right(i), order, res);
        // Post-order traversal
        if (order == "post")
            res.push_back(val(i));
    }
};
