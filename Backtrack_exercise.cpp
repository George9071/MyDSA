#include <bits/stdc++.h>
using namespace std;

/* Backtracking algorithm: Permutation I */
void backtrack(vector<int> &state, const vector<int> &choices, vector<bool> &selected, vector<vector<int>> &res)
{
    // When the state length equals the number of elements, record the solution
    if (state.size() == choices.size())
    {
        res.push_back(state);
        return;
    }
    // Traverse all choices
    for (int i = 0; i < choices.size(); i++)
    {
        int choice = choices[i];
        // Pruning: do not allow repeated selection of elements
        if (!selected[i])
        {
            // Attempt: make a choice, update the state
            selected[i] = true;
            state.push_back(choice);
            // Proceed to the next round of selection
            backtrack(state, choices, selected, res);
            // Retract: undo the choice, restore to the previous state
            selected[i] = false;
            state.pop_back();
        }
    }
}

/* Permutation I */
vector<vector<int>> permutationsI(vector<int> nums)
{
    vector<int> state;
    vector<bool> selected(nums.size(), false);
    vector<vector<int>> res;
    backtrack(state, nums, selected, res);
    return res;
}

/*      Enter an integer array, which may contain duplicate elements, and return all unique permutations.       */
/* Backtracking algorithm: Permutation II */
void backtrack(vector<int> &state, const vector<int> &choices, vector<bool> &selected, vector<vector<int>> &res)
{
    // When the state length equals the number of elements, record the solution
    if (state.size() == choices.size())
    {
        res.push_back(state);
        return;
    }
    // Traverse all choices
    unordered_set<int> duplicated;
    for (int i = 0; i < choices.size(); i++)
    {
        int choice = choices[i];
        // Pruning: do not allow repeated selection of elements and do not allow repeated selection of equal elements
        if (!selected[i] && duplicated.find(choice) == duplicated.end())
        {
            // Attempt: make a choice, update the state
            duplicated.emplace(choice); // Record selected element values
            selected[i] = true;
            state.push_back(choice);
            // Proceed to the next round of selection
            backtrack(state, choices, selected, res);
            // Retract: undo the choice, restore to the previous state
            selected[i] = false;
            state.pop_back();
        }
    }
}

/* Permutation II */
vector<vector<int>> permutationsII(vector<int> nums)
{
    vector<int> state;
    vector<bool> selected(nums.size(), false);
    vector<vector<int>> res;
    backtrack(state, nums, selected, res);
    return res;
}

/*              Question
    Given an array of positive integers nums and a target positive integer target,
    find all possible combinations such that the sum of the elements in the combination equals target.
    The given array has no duplicate elements, and each element can be chosen multiple times.
    Please return these combinations as a list, which should not contain duplicate combinations.
 */

/* Backtracking algorithm: Subset Sum I */
void backtrack(vector<int> &state, int target, int total, vector<int> &choices, vector<vector<int>> &res)
{
    // When the subset sum equals target, record the solution
    if (total == target)
    {
        res.push_back(state);
        return;
    }
    // Traverse all choices
    for (size_t i = 0; i < choices.size(); i++)
    {
        // Pruning: if the subset sum exceeds target, skip that choice
        if (total + choices[i] > target)
        {
            continue;
        }
        // Attempt: make a choice, update elements and total
        state.push_back(choices[i]);
        // Proceed to the next round of selection
        backtrack(state, target, total + choices[i], choices, res);
        // Retract: undo the choice, restore to the previous state
        state.pop_back();
    }
}

/* Solve Subset Sum I (including duplicate subsets) */
vector<vector<int>> subsetSumINaive(vector<int> &nums, int target)
{
    vector<int> state;       // State (subset)
    int total = 0;           // Subset sum
    vector<vector<int>> res; // Result list (subset list)
    backtrack(state, target, total, nums, res);
    return res;
}

/* Backtracking algorithm: Subset Sum I */
void backtrack(vector<int> &state, int target, vector<int> &choices, int start, vector<vector<int>> &res)
{
    // When the subset sum equals target, record the solution
    if (target == 0)
    {
        res.push_back(state);
        return;
    }
    // Traverse all choices
    // Pruning two: start traversing from start to avoid generating duplicate subsets
    for (int i = start; i < choices.size(); i++)
    {
        // Pruning one: if the subset sum exceeds target, end the loop immediately
        // This is because the array is sorted, and later elements are larger, so the subset sum will definitely exceed target
        if (target - choices[i] < 0)
        {
            break;
        }
        // Attempt: make a choice, update target, start
        state.push_back(choices[i]);
        // Proceed to the next round of selection
        backtrack(state, target - choices[i], choices, i, res);
        // Retract: undo the choice, restore to the previous state
        state.pop_back();
    }
}

/* Solve Subset Sum I */
vector<vector<int>> subsetSumI(vector<int> &nums, int target)
{
    vector<int> state;              // State (subset)
    sort(nums.begin(), nums.end()); // Sort nums
    int start = 0;                  // Start point for traversal
    vector<vector<int>> res;        // Result list (subset list)
    backtrack(state, target, nums, start, res);
    return res;
}

/*                                          Question
    Given an array of positive integers 'nums' and a target positive integer 'target',
    find all possible combinations such that the sum of the elements in the combination equals 'target'.
    The given array may contain duplicate elements, and each element can only be chosen once.
    Please return these combinations as a list, which should not contain duplicate combinations.
*/

/* Backtracking algorithm: Subset Sum II */
void backtrack(vector<int> &state, int target, vector<int> &choices, int start, vector<vector<int>> &res)
{
    // When the subset sum equals target, record the solution
    if (target == 0)
    {
        res.push_back(state);
        return;
    }
    // Traverse all choices
    // Pruning two: start traversing from start to avoid generating duplicate subsets
    // Pruning three: start traversing from start to avoid repeatedly selecting the same element
    for (int i = start; i < choices.size(); i++)
    {
        // Pruning one: if the subset sum exceeds target, end the loop immediately
        // This is because the array is sorted, and later elements are larger, so the subset sum will definitely exceed target
        if (target - choices[i] < 0)
        {
            break;
        }
        // Pruning four: if the element equals the left element, it indicates that the search branch is repeated, skip it
        if (i > start && choices[i] == choices[i - 1])
        {
            continue;
        }
        // Attempt: make a choice, update target, start
        state.push_back(choices[i]);
        // Proceed to the next round of selection
        backtrack(state, target - choices[i], choices, i + 1, res);
        // Retract: undo the choice, restore to the previous state
        state.pop_back();
    }
}

/* Solve Subset Sum II */
vector<vector<int>> subsetSumII(vector<int> &nums, int target)
{
    vector<int> state;              // State (subset)
    sort(nums.begin(), nums.end()); // Sort nums
    int start = 0;                  // Start point for traversal
    vector<vector<int>> res;        // Result list (subset list)
    backtrack(state, target, nums, start, res);
    return res;
}

/*                                          Question
    According to the rules of chess, a queen can attack pieces in the same row, column, or on a diagonal line.
    Given n queens and an n x n chessboard, find arrangements where no two queens can attack each other.
*/

/* Backtracking algorithm: n queens */
void backtrack(int row, int n, vector<vector<string>> &state, vector<vector<vector<string>>> &res, vector<bool> &cols,
               vector<bool> &diags1, vector<bool> &diags2)
{
    // When all rows are placed, record the solution
    if (row == n)
    {
        res.push_back(state);
        return;
    }
    // Traverse all columns
    for (int col = 0; col < n; col++)
    {
        // Calculate the main and minor diagonals corresponding to the cell
        int diag1 = row - col + n - 1;
        int diag2 = row + col;
        // Pruning: do not allow queens on the column, main diagonal, or minor diagonal of the cell
        if (!cols[col] && !diags1[diag1] && !diags2[diag2])
        {
            // Attempt: place the queen in the cell
            state[row][col] = "Q";
            cols[col] = diags1[diag1] = diags2[diag2] = true;
            // Place the next row
            backtrack(row + 1, n, state, res, cols, diags1, diags2);
            // Retract: restore the cell to an empty spot
            state[row][col] = "#";
            cols[col] = diags1[diag1] = diags2[diag2] = false;
        }
    }
}

/* Solve n queens */
vector<vector<vector<string>>> nQueens(int n)
{
    // Initialize an n*n size chessboard, where 'Q' represents the queen and '#' represents an empty spot
    vector<vector<string>> state(n, vector<string>(n, "#"));
    vector<bool> cols(n, false);           // Record columns with queens
    vector<bool> diags1(2 * n - 1, false); // Record main diagonals with queens
    vector<bool> diags2(2 * n - 1, false); // Record minor diagonals with queens
    vector<vector<vector<string>>> res;

    backtrack(0, n, state, res, cols, diags1, diags2);

    return res;
}

// if($?) { g++ ex4.cpp -o ex4 } ; if($?) { ./ex4 }
