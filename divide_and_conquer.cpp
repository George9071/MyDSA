#include <bits/stdc++.h>
using namespace std;

/* Binary search: problem f(i, j) */
int dfs(vector<int> &nums, int target, int i, int j)
{
    // If the interval is empty, indicating no target element, return -1
    if (i > j)
    {
        return -1;
    }
    // Calculate midpoint index m
    int m = i + (j - i) / 2;
    if (nums[m] < target)
    {
        // Recursive subproblem f(m+1, j)
        return dfs(nums, target, m + 1, j);
    }
    else if (nums[m] > target)
    {
        // Recursive subproblem f(i, m-1)
        return dfs(nums, target, i, m - 1);
    }
    else
    {
        // Found the target element, thus return its index
        return m;
    }
}

/* Binary search */
int binarySearch(vector<int> &nums, int target)
{
    int n = nums.size();
    // Solve problem f(0, n-1)
    return dfs(nums, target, 0, n - 1);
}

/*  Question
    Given the pre-order traversal and in-order traversal of a binary tree,
    construct the binary tree and return the root node of the binary tree.
    Assume that there are no duplicate values in the nodes of the binary tree.

    Pre-order traversal: [ Root | Left Subtree | Right Subtree ]
    In-order traversal: [ Left Subtree | Root | Right Subtree ]

    Let the index of the current tree's root node in preorder be denoted as i
    Let the index of the current tree's root node in inorder be denoted as m
    Let the index interval of the current tree in inorder be denoted as [l,r]

                        Root node index in preorder                 Subtree index interval in inorder
    Current tree                   i                                           [l,r]
    Left subtree                 i + 1                                      [l, m - 1]
    Right subtree            i + 1 + (m - l)                                [m + 1, r]
*/

/* Binary tree node */
struct TreeNode
{
    int val;         // Node value
    TreeNode *left;  // Pointer to left child node
    TreeNode *right; // Pointer to right child node
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/* Build binary tree: Divide and conquer */
TreeNode *dfs(vector<int> &preorder, unordered_map<int, int> &inorderMap, int i, int l, int r)
{
    // Terminate when subtree interval is empty
    if (r - l < 0)
        return NULL;
    // Initialize root node
    TreeNode *root = new TreeNode(preorder[i]);
    // Query m to divide left and right subtrees
    int m = inorderMap[preorder[i]];
    // Subproblem: build left subtree
    root->left = dfs(preorder, inorderMap, i + 1, l, m - 1);
    // Subproblem: build right subtree
    root->right = dfs(preorder, inorderMap, i + 1 + m - l, m + 1, r);
    // Return root node
    return root;
}

/* Build binary tree */
TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
{
    // Initialize hash table, storing in-order elements to indices mapping
    unordered_map<int, int> inorderMap;
    for (int i = 0; i < inorder.size(); i++)
    {
        inorderMap[inorder[i]] = i;
    }
    TreeNode *root = dfs(preorder, inorderMap, 0, 0, inorder.size() - 1);
    return root;
}

/*  Tower of Hanoi Problem
    We denote the Tower of Hanoi of size i as f(i). For example, f(3) represents the Tower of Hanoi of moving 3 discs from A to C.
    Base case
    f(1)    directly move it from A to C
    f(2)
            First, move the smaller disc from A to B.
            Then move the larger disc from A to C.
            Finally, move the smaller disc from B to C.

    f(3)    divide into 2 subproblems f(2) and 1 subproblem f(1)
            Let B be the target pillar and C the buffer pillar, and move the two discs from A to B. f(2)
            Move the remaining disc from A directly to C. f(1)
            Let C be the target pillar and A the buffer pillar, and move the two discs from B to C. f(2)

    -->     f(n) = 2 f(n-1) + f(1)
                                    Move n - 1 discs with the help of C from A to B.
                                    Move the remaining one disc directly from A to C.
                                    Move n - 1 discs with the help of A from B to C.

*/

/* Move a disc */
void move(vector<int> &src, vector<int> &tar)
{
    // Take out a disc from the top of src
    int pan = src.back();
    src.pop_back();
    // Place the disc on top of tar
    tar.push_back(pan);
}

/* Solve the Tower of Hanoi problem f(i) */
void dfs(int i, vector<int> &src, vector<int> &buf, vector<int> &tar)
{
    // If only one disc remains on src, move it to tar
    if (i == 1)
    {
        move(src, tar);
        return;
    }
    // Subproblem f(i-1): move the top i-1 discs from src with the help of tar to buf
    dfs(i - 1, src, tar, buf);
    // Subproblem f(1): move the remaining one disc from src to tar
    move(src, tar);
    // Subproblem f(i-1): move the top i-1 discs from buf with the help of src to tar
    dfs(i - 1, buf, src, tar);
}

/* Solve the Tower of Hanoi problem */
void solveHanota(vector<int> &A, vector<int> &B, vector<int> &C)
{
    int n = A.size();
    // Move the top n discs from A with the help of B to C
    dfs(n, A, B, C);
}