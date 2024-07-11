#include <bits/stdc++.h>
using namespace std;

/*                                          Question
    Given n items, the weight of the i-th item is wgt[i - 1] and its value is val[i - 1],
    and a knapsack with a capacity of 'cap'.Each item can be chosen only once.
    What is the maximum value of items that can be placed in the knapsack under the capacity limit?
*/

/* 0-1 Knapsack: Brute force search */
int knapsackDFS(vector<int> &wgt, vector<int> &val, int i, int c)
{
    // If all items have been chosen or the knapsack has no remaining capacity, return value 0
    if (i == 0 || c == 0)
    {
        return 0;
    }
    // If exceeding the knapsack capacity, can only choose not to put it in the knapsack
    if (wgt[i - 1] > c)
    {
        return knapsackDFS(wgt, val, i - 1, c);
    }
    // Calculate the maximum value of not putting in and putting in item i
    int no = knapsackDFS(wgt, val, i - 1, c);
    int yes = knapsackDFS(wgt, val, i - 1, c - wgt[i - 1]) + val[i - 1];
    // Return the greater value of the two options
    return max(no, yes);
}

/* 0-1 Knapsack: Memoized search */
int knapsackDFSMem(vector<int> &wgt, vector<int> &val, vector<vector<int>> &mem, int i, int c)
{
    // If all items have been chosen or the knapsack has no remaining capacity, return value 0
    if (i == 0 || c == 0)
    {
        return 0;
    }
    // If there is a record, return it
    if (mem[i][c] != -1)
    {
        return mem[i][c];
    }
    // If exceeding the knapsack capacity, can only choose not to put it in the knapsack
    if (wgt[i - 1] > c)
    {
        return knapsackDFSMem(wgt, val, mem, i - 1, c);
    }
    // Calculate the maximum value of not putting in and putting in item i
    int no = knapsackDFSMem(wgt, val, mem, i - 1, c);
    int yes = knapsackDFSMem(wgt, val, mem, i - 1, c - wgt[i - 1]) + val[i - 1];
    // Record and return the greater value of the two options
    mem[i][c] = max(no, yes);
    return mem[i][c];
}

/* 0-1 Knapsack: Dynamic programming */
int knapsackDP(vector<int> &wgt, vector<int> &val, int cap)
{
    int n = wgt.size();
    // Initialize dp table
    vector<vector<int>> dp(n + 1, vector<int>(cap + 1, 0));
    // State transition
    for (int i = 1; i <= n; i++)
    {
        for (int c = 1; c <= cap; c++)
        {
            if (wgt[i - 1] > c)
            {
                // If exceeding the knapsack capacity, do not choose item i
                dp[i][c] = dp[i - 1][c];
            }
            else
            {
                // The greater value between not choosing and choosing item i
                dp[i][c] = max(dp[i - 1][c], dp[i - 1][c - wgt[i - 1]] + val[i - 1]);
            }
        }
    }
    return dp[n][cap];
}

/* 0-1 Knapsack: Space-optimized dynamic programming */
int knapsackDPComp(vector<int> &wgt, vector<int> &val, int cap)
{
    int n = wgt.size();
    // Initialize dp table
    vector<int> dp(cap + 1, 0);
    // State transition
    for (int i = 1; i <= n; i++)
    {
        // Traverse in reverse order
        for (int c = cap; c >= 1; c--)
        {
            if (wgt[i - 1] <= c)
            {
                // The greater value between not choosing and choosing item i
                dp[c] = max(dp[c], dp[c - wgt[i - 1]] + val[i - 1]);
            }
        }
    }
    return dp[cap];
}

/*                                          Question
    Given n items, the weight of the i-th item is wgt[i - 1] and its value is val[i - 1],
    and a knapsack with a capacity of 'cap'. Each item can be selected multiple times
    What is the maximum value of items that can be placed in the knapsack under the capacity limit?
*/

/* Complete knapsack: Dynamic programming */
int unboundedKnapsackDP(vector<int> &wgt, vector<int> &val, int cap)
{
    int n = wgt.size();
    // Initialize dp table
    vector<vector<int>> dp(n + 1, vector<int>(cap + 1, 0));
    // State transition
    for (int i = 1; i <= n; i++)
    {
        for (int c = 1; c <= cap; c++)
        {
            if (wgt[i - 1] > c)
            {
                // If exceeding the knapsack capacity, do not choose item i
                dp[i][c] = dp[i - 1][c];
            }
            else
            {
                // The greater value between not choosing and choosing item i
                dp[i][c] = max(dp[i - 1][c], dp[i][c - wgt[i - 1]] + val[i - 1]);
            }
        }
    }
    return dp[n][cap];
}

/* Complete knapsack: Space-optimized dynamic programming */
int unboundedKnapsackDPComp(vector<int> &wgt, vector<int> &val, int cap)
{
    int n = wgt.size();
    // Initialize dp table
    vector<int> dp(cap + 1, 0);
    // State transition
    for (int i = 1; i <= n; i++)
    {
        for (int c = 1; c <= cap; c++)
        {
            if (wgt[i - 1] > c)
            {
                // If exceeding the knapsack capacity, do not choose item i
                dp[c] = dp[c];
            }
            else
            {
                // The greater value between not choosing and choosing item i
                dp[c] = max(dp[c], dp[c - wgt[i - 1]] + val[i - 1]);
            }
        }
    }
    return dp[cap];
}

/*                                          Question
    Given n types coins, the denomination of the i-th type of coin is coins[i - 1], and the target amount is 'amt'
    Each type of coin can be selected multiple times. What is the minimum number of coins needed to make up the target amount?
    If it is impossible to make up the target amount, return -1
*/

/* Coin change: Dynamic programming */
int coinChangeDP(vector<int> &coins, int amt)
{
    int n = coins.size();
    int MAX = amt + 1;
    // Initialize dp table
    vector<vector<int>> dp(n + 1, vector<int>(amt + 1, 0));
    // State transition: first row and first column
    for (int a = 1; a <= amt; a++)
    {
        dp[0][a] = MAX;
    }
    // State transition: the rest of the rows and columns
    for (int i = 1; i <= n; i++)
    {
        for (int a = 1; a <= amt; a++)
        {
            if (coins[i - 1] > a)
            {
                // If exceeding the target amount, do not choose coin i
                dp[i][a] = dp[i - 1][a];
            }
            else
            {
                // The smaller value between not choosing and choosing coin i
                dp[i][a] = min(dp[i - 1][a], dp[i][a - coins[i - 1]] + 1);
            }
        }
    }
    return dp[n][amt] != MAX ? dp[n][amt] : -1;
}

/* Coin change: Space-optimized dynamic programming */
int coinChangeDPComp(vector<int> &coins, int amt)
{
    int n = coins.size();
    int MAX = amt + 1;
    // Initialize dp table
    vector<int> dp(amt + 1, MAX);
    dp[0] = 0;
    // State transition
    for (int i = 1; i <= n; i++)
    {
        for (int a = 1; a <= amt; a++)
        {
            if (coins[i - 1] > a)
            {
                // If exceeding the target amount, do not choose coin i
                dp[a] = dp[a];
            }
            else
            {
                // The smaller value between not choosing and choosing coin i
                dp[a] = min(dp[a], dp[a - coins[i - 1]] + 1);
            }
        }
    }
    return dp[amt] != MAX ? dp[amt] : -1;
}

/*                                          Question
    Given n types coins, the denomination of the i-th type of coin is coins[i - 1], and the target amount is 'amt'
    Each type of coin can be selected multiple times.
    How many combinations of coins can make up the target amount
*/

/* Coin change II: Dynamic programming */
int coinChangeIIDP(vector<int> &coins, int amt)
{
    int n = coins.size();
    // Initialize dp table
    vector<vector<int>> dp(n + 1, vector<int>(amt + 1, 0));
    // Initialize first column
    for (int i = 0; i <= n; i++)
    {
        dp[i][0] = 1;
    }
    // State transition
    for (int i = 1; i <= n; i++)
    {
        for (int a = 1; a <= amt; a++)
        {
            if (coins[i - 1] > a)
            {
                // If exceeding the target amount, do not choose coin i
                dp[i][a] = dp[i - 1][a];
            }
            else
            {
                // The sum of the two options of not choosing and choosing coin i
                dp[i][a] = dp[i - 1][a] + dp[i][a - coins[i - 1]];
            }
        }
    }
    return dp[n][amt];
}

/* Coin change II: Space-optimized dynamic programming */
int coinChangeIIDPComp(vector<int> &coins, int amt)
{
    int n = coins.size();
    // Initialize dp table
    vector<int> dp(amt + 1, 0);
    dp[0] = 1;
    // State transition
    for (int i = 1; i <= n; i++)
    {
        for (int a = 1; a <= amt; a++)
        {
            if (coins[i - 1] > a)
            {
                // If exceeding the target amount, do not choose coin i
                dp[a] = dp[a];
            }
            else
            {
                // The sum of the two options of not choosing and choosing coin i
                dp[a] = dp[a] + dp[a - coins[i - 1]];
            }
        }
    }
    return dp[amt];
}

/*                                          Question
    Given two strings s and t, return the minimum number of edits required to transform s into t
    You can perform three types of edits on a string:
        insert a character,
        delete a character,
        replace a character with any other character.

    Consider the subproblem dp[i,j], whose corresponding tail characters of the two strings are s[i - 1] and t[j - 1]
    which can be divided into 3 scenarios
        Add t[j - 1] after s[i - 1]         then the remaining subproblem is dp[i][j - 1]
        Delete s[i - 1]                     then the remaining subproblem is dp[i - 1][j]
        Replace s[i - 1] with t[j - 1]      then the remaining subproblem is dp[i - 1][j - 1]

        --> dp[i][j] = min(dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]) + 1;

    When s[i - 1] = t[j - 1]    then    dp[i][j] = dp[i - 1][j - 1]
*/

/* Edit distance: Dynamic programming */
int editDistanceDP(string s, string t)
{
    int n = s.length(), m = t.length();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    // State transition: first row and first column
    for (int i = 1; i <= n; i++)
    {
        dp[i][0] = i;
    }
    for (int j = 1; j <= m; j++)
    {
        dp[0][j] = j;
    }
    // State transition: the rest of the rows and columns
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s[i - 1] == t[j - 1])
            {
                // If the two characters are equal, skip these two characters
                dp[i][j] = dp[i - 1][j - 1];
            }
            else
            {
                // The minimum number of edits = the minimum number of edits from three operations (insert, remove, replace) + 1
                dp[i][j] = min(min(dp[i][j - 1], dp[i - 1][j]), dp[i - 1][j - 1]) + 1;
            }
        }
    }
    return dp[n][m];
}

/* Edit distance: Space-optimized dynamic programming */
int editDistanceDPComp(string s, string t)
{
    int n = s.length(), m = t.length();
    vector<int> dp(m + 1, 0);
    // State transition: first row
    for (int j = 1; j <= m; j++)
    {
        dp[j] = j;
    }
    // State transition: the rest of the rows
    for (int i = 1; i <= n; i++)
    {
        // State transition: first column
        int leftup = dp[0]; // Temporarily store dp[i-1, j-1]
        dp[0] = i;
        // State transition: the rest of the columns
        for (int j = 1; j <= m; j++)
        {
            int temp = dp[j];
            if (s[i - 1] == t[j - 1])
            {
                // If the two characters are equal, skip these two characters
                dp[j] = leftup;
            }
            else
            {
                // The minimum number of edits = the minimum number of edits from three operations (insert, remove, replace) + 1
                dp[j] = min(min(dp[j - 1], dp[j]), leftup) + 1;
            }
            leftup = temp; // Update for the next round of dp[i-1, j-1]
        }
    }
    return dp[m];
}
