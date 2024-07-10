#include <bits/stdc++.h>
using namespace std;

/* Binary search (double closed interval) */
int binarySearch(vector<int> &nums, int target)
{
    // Initialize double closed interval [0, n-1], i.e., i, j point to the first element and last element of the array respectively
    int i = 0, j = nums.size() - 1;
    // Loop until the search interval is empty (when i > j, it is empty)
    while (i <= j)
    {
        int m = i + (j - i) / 2; // Calculate midpoint index m
        if (nums[m] < target)    // This situation indicates that target is in the interval [m+1, j]
            i = m + 1;
        else if (nums[m] > target) // This situation indicates that target is in the interval [i, m-1]
            j = m - 1;
        else // Found the target element, thus return its index
            return m;
    }
    // Did not find the target element, thus return -1
    return -1;
}

/* Binary search (left closed right open interval) */
int binarySearchLCRO(vector<int> &nums, int target)
{
    // Initialize left closed right open interval [0, n), i.e., i, j point to the first element and the last element +1 of the array respectively
    int i = 0, j = nums.size();
    // Loop until the search interval is empty (when i = j, it is empty)
    while (i < j)
    {
        int m = i + (j - i) / 2; // Calculate midpoint index m
        if (nums[m] < target)    // This situation indicates that target is in the interval [m+1, j)
            i = m + 1;
        else if (nums[m] > target) // This situation indicates that target is in the interval [i, m)
            j = m;
        else // Found the target element, thus return its index
            return m;
    }
    // Did not find the target element, thus return -1
    return -1;
}

/* Binary search for insertion point (no duplicate elements) */
int binarySearchInsertionSimple(vector<int> &nums, int target)
{
    int i = 0, j = nums.size() - 1; // Initialize double closed interval [0, n-1]
    while (i <= j)
    {
        int m = i + (j - i) / 2; // Calculate midpoint index m
        if (nums[m] < target)
        {
            i = m + 1; // Target is in interval [m+1, j]
        }
        else if (nums[m] > target)
        {
            j = m - 1; // Target is in interval [i, m-1]
        }
        else
        {
            return m; // Found target, return insertion point m
        }
    }
    // Did not find target, return insertion point i
    return i;
}

/* Binary search for insertion point (with duplicate elements) */
int binarySearchInsertion(vector<int> &nums, int target)
{
    int i = 0, j = nums.size() - 1; // Initialize double closed interval [0, n-1]
    while (i <= j)
    {
        int m = i + (j - i) / 2; // Calculate midpoint index m
        if (nums[m] < target)
        {
            i = m + 1; // Target is in interval [m+1, j]
        }
        else if (nums[m] > target)
        {
            j = m - 1; // Target is in interval [i, m-1]
        }
        else
        {
            j = m - 1; // First element less than target is in interval [i, m-1]
        }
    }
    // Return insertion point i
    return i;
}

/* Binary search for the leftmost target */
int binarySearchLeftEdge(vector<int> &nums, int target)
{
    // Equivalent to finding the insertion point of target
    int i = binarySearchInsertion(nums, target);
    // Did not find target, thus return -1
    if (i == nums.size() || nums[i] != target)
    {
        return -1;
    }
    // Found target, return index i
    return i;
}

/* Binary search for the rightmost target */
int binarySearchRightEdge(vector<int> &nums, int target)
{
    // Convert to finding the leftmost target + 1
    int i = binarySearchInsertion(nums, target + 1);
    // j points to the rightmost target, i points to the first element greater than target
    int j = i - 1;
    // Did not find target, thus return -1
    if (j == -1 || nums[j] != target)
    {
        return -1;
    }
    // Found target, return index j
    return j;
}