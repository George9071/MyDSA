/* Given an integer array 'nums' and a target element 'target', 
please search for two elements in the array whose "sum" equals 'target', 
and return their array indices. Any solution is acceptable.*/

#include <bits/stdc++.h>
using namespace std;
/* Method one: Brute force enumeration */
vector<int> twoSumBruteForce(vector<int> &nums, int target) {
    int size = nums.size();
    // Two-layer loop, time complexity is O(n^2)
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (nums[i] + nums[j] == target)
                return {i, j};
        }
    }
    return {};
}

/* Method two: Auxiliary hash table */
vector<int> twoSumHashTable(vector<int> &nums, int target) {
    int size = nums.size();
    // Auxiliary hash table, space complexity is O(n)
    unordered_map<int, int> dic;
    // Single-layer loop, time complexity is O(n)
    for (int i = 0; i < size; i++) {
        if (dic.find(target - nums[i]) != dic.end()) {
            return {dic[target - nums[i]], i};
        }
        dic.emplace(nums[i], i);
    }
    return {};
}