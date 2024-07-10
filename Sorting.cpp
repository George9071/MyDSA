#include <bits/stdc++.h>
using namespace std;

/* Selection sort */
void selectionSort(vector<int> &nums)
{
    int n = nums.size();
    // Outer loop: unsorted range is [i, n-1]
    for (int i = 0; i < n - 1; i++)
    {
        // Inner loop: find the smallest element within the unsorted range
        int k = i;
        for (int j = i + 1; j < n; j++)
        {
            if (nums[j] < nums[k])
                k = j; // Record the index of the smallest element
        }
        // Swap the smallest element with the first element of the unsorted range
        swap(nums[i], nums[k]);
    }
}

/* Bubble sort (optimized with flag)*/
void bubbleSortWithFlag(vector<int> &nums)
{
    // Outer loop: unsorted range is [0, i]
    for (int i = nums.size() - 1; i > 0; i--)
    {
        bool flag = false; // Initialize flag
        // Inner loop: swap the largest element in the unsorted range [0, i] to the right end of the range
        for (int j = 0; j < i; j++)
        {
            if (nums[j] > nums[j + 1])
            {
                // Swap nums[j] and nums[j + 1]
                // Here, the std
                swap(nums[j], nums[j + 1]);
                flag = true; // Record swapped elements
            }
        }
        if (!flag)
            break; // If no elements were swapped in this round of "bubbling", exit
    }
}

/* Insertion sort */
void insertionSort(vector<int> &nums)
{
    // Outer loop: sorted range is [0, i-1]
    for (int i = 1; i < nums.size(); i++)
    {
        int base = nums[i], j = i - 1;
        // Inner loop: insert base into the correct position within the sorted range [0, i-1]
        while (j >= 0 && nums[j] > base)
        {
            nums[j + 1] = nums[j]; // Move nums[j] to the right by one position
            j--;
        }
        nums[j + 1] = base; // Assign base to the correct position
    }
}

/* Swap elements */
void swap(vector<int> &nums, int i, int j)
{
    int tmp = nums[i];
    nums[i] = nums[j];
    nums[j] = tmp;
}

/* Partition */
int partition(vector<int> &nums, int left, int right)
{
    // Use nums[left] as the pivot
    int i = left, j = right;
    while (i < j)
    {
        while (i < j && nums[j] >= nums[left])
            j--; // Search from right to left for the first element smaller than the pivot
        while (i < j && nums[i] <= nums[left])
            i++;          // Search from left to right for the first element greater than the pivot
        swap(nums, i, j); // Swap these two elements
    }
    swap(nums, i, left); // Swap the pivot to the boundary between the two subarrays
    return i;            // Return the index of the pivot
}

/* Quick sort */
void quickSort(vector<int> &nums, int left, int right)
{
    // Terminate recursion when subarray length is 1
    if (left >= right)
        return;
    // Partition
    int pivot = partition(nums, left, right);
    // Recursively process the left subarray and right subarray
    quickSort(nums, left, pivot - 1);
    quickSort(nums, pivot + 1, right);
}

/* Select the median of three candidate elements */
int medianThree(vector<int> &nums, int left, int mid, int right)
{
    int l = nums[left], m = nums[mid], r = nums[right];
    if ((l <= m && m <= r) || (r <= m && m <= l))
        return mid; // m is between l and r
    if ((m <= l && l <= r) || (r <= l && l <= m))
        return left; // l is between m and r
    return right;
}

/* Partition (median of three) */
int partition(vector<int> &nums, int left, int right)
{
    // Select the median of three candidate elements
    int med = medianThree(nums, left, (left + right) / 2, right);
    // Swap the median to the array's leftmost position
    swap(nums, left, med);
    // Use nums[left] as the pivot
    int i = left, j = right;
    while (i < j)
    {
        while (i < j && nums[j] >= nums[left])
            j--; // Search from right to left for the first element smaller than the pivot
        while (i < j && nums[i] <= nums[left])
            i++;          // Search from left to right for the first element greater than the pivot
        swap(nums, i, j); // Swap these two elements
    }
    swap(nums, i, left); // Swap the pivot to the boundary between the two subarrays
    return i;            // Return the index of the pivot
}

/* Quick sort (tail recursion optimization) */
void quickSort(vector<int> &nums, int left, int right)
{
    // Terminate when subarray length is 1
    while (left < right)
    {
        // Partition operation
        int pivot = partition(nums, left, right);
        // Perform quick sort on the shorter of the two subarrays
        if (pivot - left < right - pivot)
        {
            quickSort(nums, left, pivot - 1); // Recursively sort the left subarray
            left = pivot + 1;                 // Remaining unsorted interval is [pivot + 1, right]
        }
        else
        {
            quickSort(nums, pivot + 1, right); // Recursively sort the right subarray
            right = pivot - 1;                 // Remaining unsorted interval is [left, pivot - 1]
        }
    }
}

/* Merge left subarray and right subarray */
void merge(vector<int> &nums, int left, int mid, int right)
{
    // Left subarray interval is [left, mid], right subarray interval is [mid+1, right]
    // Create a temporary array tmp to store the merged results
    vector<int> tmp(right - left + 1);
    // Initialize the start indices of the left and right subarrays
    int i = left, j = mid + 1, k = 0;
    // While both subarrays still have elements, compare and copy the smaller element into the temporary array
    while (i <= mid && j <= right)
    {
        if (nums[i] <= nums[j])
            tmp[k++] = nums[i++];
        else
            tmp[k++] = nums[j++];
    }
    // Copy the remaining elements of the left and right subarrays into the temporary array
    while (i <= mid)
    {
        tmp[k++] = nums[i++];
    }
    while (j <= right)
    {
        tmp[k++] = nums[j++];
    }
    // Copy the elements from the temporary array tmp back to the original array nums at the corresponding interval
    for (k = 0; k < tmp.size(); k++)
    {
        nums[left + k] = tmp[k];
    }
}

/* Merge sort */
void mergeSort(vector<int> &nums, int left, int right)
{
    // Termination condition
    if (left >= right)
        return; // Terminate recursion when subarray length is 1
    // Partition stage
    int mid = left + (right - left) / 2; // Calculate midpoint
    mergeSort(nums, left, mid);          // Recursively process the left subarray
    mergeSort(nums, mid + 1, right);     // Recursively process the right subarray
    // Merge stage
    merge(nums, left, mid, right);
}

/* Heap length is n, start heapifying node i, from top to bottom */
void siftDown(vector<int> &nums, int n, int i)
{
    while (true)
    {
        // Determine the largest node among i, l, r, noted as ma
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int ma = i;
        if (l < n && nums[l] > nums[ma])
            ma = l;
        if (r < n && nums[r] > nums[ma])
            ma = r;
        // If node i is the largest or indices l, r are out of bounds, no further heapification needed, break
        if (ma == i)
        {
            break;
        }
        // Swap two nodes
        swap(nums[i], nums[ma]);
        // Loop downwards heapification
        i = ma;
    }
}

/* Heap sort */
void heapSort(vector<int> &nums)
{
    // Build heap operation: heapify all nodes except leaves
    for (int i = nums.size() / 2 - 1; i >= 0; --i)
    {
        siftDown(nums, nums.size(), i);
    }
    // Extract the largest element from the heap and repeat for n-1 rounds
    for (int i = nums.size() - 1; i > 0; --i)
    {
        // Swap the root node with the rightmost leaf node (swap the first element with the last element)
        swap(nums[0], nums[i]);
        // Start heapifying the root node, from top to bottom
        siftDown(nums, i, 0);
    }
}

/* Bucket sort */
void bucketSort(vector<float> &nums)
{
    // Initialize k = n/2 buckets, expected to allocate 2 elements per bucket
    int k = nums.size() / 2;
    vector<vector<float>> buckets(k);
    // 1. Distribute array elements into various buckets
    for (float num : nums)
    {
        // Input data range is [0, 1), use num * k to map to index range [0, k-1]
        int i = num * k;
        // Add number to bucket_idx
        buckets[i].push_back(num);
    }
    // 2. Sort each bucket
    for (vector<float> &bucket : buckets)
    {
        // Use built-in sorting function, can also replace with other sorting algorithms
        sort(bucket.begin(), bucket.end());
    }
    // 3. Traverse buckets to merge results
    int i = 0;
    for (vector<float> &bucket : buckets)
    {
        for (float num : bucket)
        {
            nums[i++] = num;
        }
    }
}

/* Counting sort */
// Simple implementation, cannot be used for sorting objects
void countingSortNaive(vector<int> &nums)
{
    // 1. Count the maximum element m in the array
    int m = 0;
    for (int num : nums)
    {
        m = max(m, num);
    }
    // 2. Count the occurrence of each digit
    // counter[num] represents the occurrence of num
    vector<int> counter(m + 1, 0);
    for (int num : nums)
    {
        counter[num]++;
    }
    // 3. Traverse counter, filling each element back into the original array nums
    int i = 0;
    for (int num = 0; num < m + 1; num++)
    {
        for (int j = 0; j < counter[num]; j++, i++)
        {
            nums[i] = num;
        }
    }
}

/* Counting sort */
// Complete implementation, can sort objects and is a stable sort
void countingSort(vector<int> &nums)
{
    // 1. Count the maximum element m in the array
    int m = 0;
    for (int num : nums)
    {
        m = max(m, num);
    }
    // 2. Count the occurrence of each digit
    // counter[num] represents the occurrence of num
    vector<int> counter(m + 1, 0);
    for (int num : nums)
    {
        counter[num]++;
    }
    // 3. Calculate the prefix sum of counter, converting "occurrence count" to "tail index"
    // counter[num]-1 is the last index where num appears in res
    for (int i = 0; i < m; i++)
    {
        counter[i + 1] += counter[i];
    }
    // 4. Traverse nums in reverse order, placing each element into the result array res
    // Initialize the array res to record results
    int n = nums.size();
    vector<int> res(n);
    for (int i = n - 1; i >= 0; i--)
    {
        int num = nums[i];
        res[counter[num] - 1] = num; // Place num at the corresponding index
        counter[num]--;              // Decrement the prefix sum by 1, getting the next index to place num
    }
    // Use result array res to overwrite the original array nums
    nums = res;
}

/* Get the k-th digit of element num, where exp = 10^(k-1) */
int digit(int num, int exp)
{
    // Passing exp instead of k can avoid repeated expensive exponentiation here
    return (num / exp) % 10;
}

/* Counting sort (based on nums k-th digit) */
void countingSortDigit(vector<int> &nums, int exp)
{
    // Decimal digit range is 0~9, therefore need a bucket array of length 10
    vector<int> counter(10, 0);
    int n = nums.size();
    // Count the occurrence of digits 0~9
    for (int i = 0; i < n; i++)
    {
        int d = digit(nums[i], exp); // Get the k-th digit of nums[i], noted as d
        counter[d]++;                // Count the occurrence of digit d
    }
    // Calculate prefix sum, converting "occurrence count" into "array index"
    for (int i = 1; i < 10; i++)
    {
        counter[i] += counter[i - 1];
    }
    // Traverse in reverse, based on bucket statistics, place each element into res
    vector<int> res(n, 0);
    for (int i = n - 1; i >= 0; i--)
    {
        int d = digit(nums[i], exp);
        int j = counter[d] - 1; // Get the index j for d in the array
        res[j] = nums[i];       // Place the current element at index j
        counter[d]--;           // Decrease the count of d by 1
    }
    // Use result to overwrite the original array nums
    for (int i = 0; i < n; i++)
        nums[i] = res[i];
}

/* Radix sort */
void radixSort(vector<int> &nums)
{
    // Get the maximum element of the array, used to determine the maximum number of digits
    int m = *max_element(nums.begin(), nums.end());
    // Traverse from the lowest to the highest digit
    for (int exp = 1; exp <= m; exp *= 10)
        // Perform counting sort on the k-th digit of array elements
        // k = 1 -> exp = 1
        // k = 2 -> exp = 10
        // i.e., exp = 10^(k-1)
        countingSortDigit(nums, exp);
}
