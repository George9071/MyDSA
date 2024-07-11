#include <bits/stdc++.h>
using namespace std;

/*                                          Question
    Given a staircase with n steps, where you can climb 1 or 2 steps at a time, how many different ways are there to reach the top?
*/

/* Backtracking */
void backtrack(vector<int> &choices, int state, int n, vector<int> &res)
{
    // When climbing to the nth step, add 1 to the number of solutions
    if (state == n)
        res[0]++;
    // Traverse all choices
    for (auto &choice : choices)
    {
        // Pruning: do not allow climbing beyond the nth step
        if (state + choice > n)
            continue;
        // Attempt: make a choice, update the state
        backtrack(choices, state + choice, n, res);
        // Retract
    }
}

/* Climbing stairs: Backtracking */
int climbingStairsBacktrack(int n)
{
    vector<int> choices = {1, 2}; // Can choose to climb up 1 step or 2 steps
    int state = 0;                // Start climbing from the 0th step
    vector<int> res = {0};        // Use res[0] to record the number of solutions
    backtrack(choices, state, n, res);
    return res[0];
}

/* Search */
int dfs(int i)
{
    // Known dp[1] and dp[2], return them
    if (i == 1 || i == 2)
        return i;
    // dp[i] = dp[i-1] + dp[i-2]
    int count = dfs(i - 1) + dfs(i - 2);
    return count;
}

/* Climbing stairs: Search */
int climbingStairsDFS(int n)
{
    return dfs(n);
}

/* Memoized search */
int dfs(int i, vector<int> &mem)
{
    // Known dp[1] and dp[2], return them
    if (i == 1 || i == 2)
        return i;
    // If there is a record for dp[i], return it
    if (mem[i] != -1)
        return mem[i];
    // dp[i] = dp[i-1] + dp[i-2]
    int count = dfs(i - 1, mem) + dfs(i - 2, mem);
    // Record dp[i]
    mem[i] = count;
    return count;
}

/* Climbing stairs: Memoized search */
int climbingStairsDFSMem(int n)
{
    // mem[i] records the total number of solutions for climbing to the ith step, -1 means no record
    vector<int> mem(n + 1, -1);
    return dfs(n, mem);
}

/* Climbing stairs: Dynamic programming */
int climbingStairsDP(int n)
{
    if (n == 1 || n == 2)
        return n;
    // Initialize dp table, used to store subproblem solutions
    vector<int> dp(n + 1);
    // Initial state: preset the smallest subproblem solution
    dp[1] = 1;
    dp[2] = 2; // 0 --> 2 || 0 --> 1 --> 2
    // State transition: gradually solve larger subproblems from smaller ones
    for (int i = 3; i <= n; i++)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}

/* Climbing stairs: Space-optimized dynamic programming */
int climbingStairsDPComp(int n)
{
    if (n == 1 || n == 2)
        return n;
    int a = 1, b = 2;
    for (int i = 3; i <= n; i++)
    {
        int tmp = b;
        b = a + b;
        a = tmp;
    }
    return b;
}

/*                                          Question
    Given a staircase, you can step up 1 or 2 steps at a time,
    and each step on the staircase has a non-negative integer representing the cost you need to pay at that step.
    Given a non-negative integer array 'cost', where cost[i] represents the cost you need to pay at the i-th step
    cost[0] is the ground (starting point). What is the minimum cost required to reach the top?

    -->             dp[i] = min(dp[i-2], dp[i-1]) + cost[i]
*/

/* Climbing stairs with minimum cost: Dynamic programming */
int minCostClimbingStairsDP(vector<int> &cost)
{
    int n = cost.size() - 1;
    if (n == 1 || n == 2)
        return cost[n];
    // Initialize dp table, used to store subproblem solutions
    vector<int> dp(n + 1);
    // Initial state: preset the smallest subproblem solution
    dp[1] = cost[1];
    dp[2] = cost[2];
    // State transition: gradually solve larger subproblems from smaller ones
    for (int i = 3; i <= n; i++)
    {
        dp[i] = min(dp[i - 1], dp[i - 2]) + cost[i];
    }
    return dp[n];
}

/* Climbing stairs with minimum cost: Space-optimized dynamic programming */
int minCostClimbingStairsDPComp(vector<int> &cost)
{
    int n = cost.size() - 1;
    if (n == 1 || n == 2)
        return cost[n];
    int a = cost[1], b = cost[2];
    for (int i = 3; i <= n; i++)
    {
        int tmp = b;
        b = min(a, tmp) + cost[i];
        a = tmp;
    }
    return b;
}

/*                                          Question
   Given a staircase with n steps, you can go up 1 or 2 steps each time,
   but you cannot jump 1 step twice in a row. How many ways are there to climb to the top?
*/

/* Constrained climbing stairs: Dynamic programming */
int climbingStairsConstraintDP(int n)
{
    if (n == 1 || n == 2)
    {
        return 1;
    }
    // Initialize dp table, used to store subproblem solutions
    vector<vector<int>> dp(n + 1, vector<int>(3, 0));
    // Initial state: preset the smallest subproblem solution
    dp[1][1] = 1;
    dp[1][2] = 0;
    dp[2][1] = 0;
    dp[2][2] = 1;
    // State transition: gradually solve larger subproblems from smaller ones
    for (int i = 3; i <= n; i++)
    {
        dp[i][1] = dp[i - 1][2];
        dp[i][2] = dp[i - 2][1] + dp[i - 2][2];
    }
    return dp[n][1] + dp[n][2];
}

/*                                          Question
   Given an n x m two-dimensional grid,
   each cell in the grid contains a non-negative integer representing the cost of that cell
   The robot starts from the top-left cell and can only move down or right at each step until it reaches the bottom-right cell.
   Return the minimum path sum from the top-left to the bottom-right.
*/

/* Minimum path sum: Brute force search */
int minPathSumDFS(vector<vector<int>> &grid, int i, int j)
{
    // If it's the top-left cell, terminate the search
    if (i == 0 && j == 0)
    {
        return grid[0][0];
    }
    // If the row or column index is out of bounds, return a +∞ cost
    if (i < 0 || j < 0)
    {
        return INT_MAX;
    }
    // Calculate the minimum path cost from the top-left to (i-1, j) and (i, j-1)
    int up = minPathSumDFS(grid, i - 1, j);
    int left = minPathSumDFS(grid, i, j - 1);
    // Return the minimum path cost from the top-left to (i, j)
    return min(left, up) != INT_MAX ? min(left, up) + grid[i][j] : INT_MAX;
}

/* Minimum path sum: Memoized search */
int minPathSumDFSMem(vector<vector<int>> &grid, vector<vector<int>> &mem, int i, int j)
{
    // If it's the top-left cell, terminate the search
    if (i == 0 && j == 0)
    {
        return grid[0][0];
    }
    // If the row or column index is out of bounds, return a +∞ cost
    if (i < 0 || j < 0)
    {
        return INT_MAX;
    }
    // If there is a record, return it
    if (mem[i][j] != -1)
    {
        return mem[i][j];
    }
    // The minimum path cost from the left and top cells
    int up = minPathSumDFSMem(grid, mem, i - 1, j);
    int left = minPathSumDFSMem(grid, mem, i, j - 1);
    // Record and return the minimum path cost from the top-left to (i, j)
    mem[i][j] = min(left, up) != INT_MAX ? min(left, up) + grid[i][j] : INT_MAX;
    return mem[i][j];
}

/* Minimum path sum: Dynamic programming */
int minPathSumDP(vector<vector<int>> &grid)
{
    int n = grid.size(), m = grid[0].size();
    // Initialize dp table
    vector<vector<int>> dp(n, vector<int>(m));
    dp[0][0] = grid[0][0];
    // State transition: first row
    for (int j = 1; j < m; j++)
    {
        dp[0][j] = dp[0][j - 1] + grid[0][j];
    }
    // State transition: first column
    for (int i = 1; i < n; i++)
    {
        dp[i][0] = dp[i - 1][0] + grid[i][0];
    }
    // State transition: the rest of the rows and columns
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < m; j++)
        {
            dp[i][j] = min(dp[i][j - 1], dp[i - 1][j]) + grid[i][j];
        }
    }
    return dp[n - 1][m - 1];
}

/* Minimum path sum: Space-optimized dynamic programming */
int minPathSumDPComp(vector<vector<int>> &grid)
{
    int n = grid.size(), m = grid[0].size();
    // Initialize dp table
    vector<int> dp(m);
    // State transition: first row
    dp[0] = grid[0][0];
    for (int j = 1; j < m; j++)
    {
        dp[j] = dp[j - 1] + grid[0][j];
    }
    // State transition: the rest of the rows
    for (int i = 1; i < n; i++)
    {
        // State transition: first column
        dp[0] = dp[0] + grid[i][0];
        // State transition: the rest of the columns
        for (int j = 1; j < m; j++)
        {
            dp[j] = min(dp[j - 1], dp[j]) + grid[i][j];
        }
    }
    return dp[m - 1];
}