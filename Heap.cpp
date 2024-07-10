#include <bits/stdc++.h>
using namespace std;

// priority_queue<int, vector<int>, greater<int>> minHeap;
// priority_queue<int, vector<int>, less<int>> maxHeap;

/* Get index of left child node */
int left(int i)
{
    return 2 * i + 1;
}

/* Get index of right child node */
int right(int i)
{
    return 2 * i + 2;
}

/* Get index of parent node */
int parent(int i)
{
    return (i - 1) / 2; // Integer division down
}

vector<int> minHeap;
vector<int> maxHeap;

/* Access heap top element */
int peek()
{
    return maxHeap[0];
}

int size()
{
    return maxHeap.size();
}

bool isEmpty()
{
    return maxHeap.empty();
}

/* Push the element into heap */
void push(int val)
{
    // Add node
    maxHeap.push_back(val);
    // Heapify from bottom to top
    siftUp(size() - 1);
}

/* Start heapifying node i, from bottom to top */
void siftUp(int i)
{
    while (true)
    {
        // Get parent node of node i
        int p = parent(i);
        // When "crossing the root node" or "node does not need repair", end heapification
        if (p < 0 || maxHeap[i] <= maxHeap[p])
            break;
        // Swap two nodes
        swap(maxHeap[i], maxHeap[p]);
        // Loop upwards heapification
        i = p;
    }
}

/* Element exits heap */
void pop()
{
    // Empty handling
    if (isEmpty())
    {
        throw out_of_range("Heap is empty");
    }
    // Swap the root node with the rightmost leaf node (swap the first element with the last element)
    swap(maxHeap[0], maxHeap[size() - 1]);
    // Remove node
    maxHeap.pop_back();
    // Heapify from top to bottom
    siftDown(0);
}

/* Start heapifying node i, from top to bottom */
void siftDown(int i)
{
    while (true)
    {
        // Determine the largest node among i, l, r, noted as ma
        int l = left(i), r = right(i), ma = i;
        if (l < size() && maxHeap[l] > maxHeap[ma])
            ma = l;
        if (r < size() && maxHeap[r] > maxHeap[ma])
            ma = r;
        // If node i is the largest or indices l, r are out of bounds, no further heapification needed, break
        if (ma == i)
            break;
        swap(maxHeap[i], maxHeap[ma]);
        // Loop downwards heapification
        i = ma;
    }
}

/* Constructor, build heap based on input list */
void MaxHeap(vector<int> nums)
{
    // Add all list elements into the heap
    maxHeap = nums;
    // Heapify all nodes except leaves
    for (int i = parent(size() - 1); i >= 0; i--)
    {
        siftDown(i);
    }
}

/*The time complexity of inserting n elements into a heap and building the heap can be optimized to O(n)*/

/* Using heap to find the largest k elements in an array [O(nlogk)]*/
priority_queue<int, vector<int>, greater<int>> topKHeap(vector<int> &nums, int k)
{
    // Initialize min-heap
    priority_queue<int, vector<int>, greater<int>> heap;
    // Enter the first k elements of the array into the heap
    for (int i = 0; i < k; i++)
    {
        heap.push(nums[i]);
    }
    // From the k+1th element, keep the heap length as k
    for (int i = k; i < nums.size(); i++)
    {
        // If the current element is larger than the heap top element, remove the heap top element and enter the current element into the heap
        if (nums[i] > heap.top())
        {
            heap.pop();
            heap.push(nums[i]);
        }
    }
    return heap;
}