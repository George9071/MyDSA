#include <bits/stdc++.h>
using namespace std;

/*                                          Question
    Given n types coins,  where the denomination of the i-th type of coin is coins[i - 1], and the target amount is 'amt'
    With each type of coin available indefinitely, what is the minimum number of coins needed to make up the target amount?
    If it is not possible to make up the target amount, return -1
*/

/* Coin change: Greedy */
int coinChangeGreedy(vector<int> &coins, int amt)
{
    // Assume coins list is ordered
    int i = coins.size() - 1;
    int count = 0;
    // Loop for greedy selection until no remaining amount
    while (amt > 0)
    {
        // Find the smallest coin close to and less than the remaining amount
        while (i > 0 && coins[i] > amt)
        {
            i--;
        }
        // Choose coins[i]
        amt -= coins[i];
        count++;
    }
    // If no feasible solution is found, return -1
    return amt == 0 ? count : -1;
}

/*                                          Question
    Given n items, the weight of the i-th item is wgt[i - 1] and its value is val[i - 1] and a knapsack with a capacity of 'cap'
    Each item can be chosen only once, but a part of the item can be selected,
    with its value calculated based on the proportion of the weight chosen
    What is the maximum value of the items in the knapsack under the limited capacity ?
*/

/* Item */
class Item
{
public:
    int w; // Item weight
    int v; // Item value

    Item(int w, int v) : w(w), v(v)
    {
    }
};

/* Fractional knapsack: Greedy */
double fractionalKnapsack(vector<int> &wgt, vector<int> &val, int cap)
{
    // Create an item list, containing two properties: weight, value
    vector<Item> items;
    for (int i = 0; i < wgt.size(); i++)
    {
        items.push_back(Item(wgt[i], val[i]));
    }
    // Sort by unit value item.v / item.w from high to low
    sort(items.begin(), items.end(), [](Item &a, Item &b)
         { return (double)a.v / a.w > (double)b.v / b.w; });
    // Loop for greedy selection
    double res = 0;
    for (auto &item : items)
    {
        if (item.w <= cap)
        {
            // If the remaining capacity is sufficient, put the entire item into the knapsack
            res += item.v;
            cap -= item.w;
        }
        else
        {
            // If the remaining capacity is insufficient, put part of the item into the knapsack
            res += (double)item.v / item.w * cap;
            // No remaining capacity left, thus break the loop
            break;
        }
    }
    return res;
}

/*                                          Question
    Input an array ht, where each element represents the height of a vertical partition.
    Any two partitions in the array, along with the space between them, can form a container.
    The capacity of the container is the product of the height and the width (area),
    where the height is determined by the shorter partition, and the width is the difference in array indices between the two partitions.
    Please select two partitions in the array that maximize the container's capacity and return this maximum capacity.

                    cap[i,j] = min(ht[i], ht[j]) x (j - i)

    1. Initially, the pointers i and j are positioned at the ends of the array.
    2. Calculate the current state's capacity cap[i,j] and update the maximum capacity.
    3. Compare the heights of partitions i and j, and move the shorter partition inward by one step.
    4. Repeat steps 2 and 3 until i and j meet
*/

/* Maximum capacity: Greedy */
int maxCapacity(vector<int> &ht)
{
    // Initialize i, j, making them split the array at both ends
    int i = 0, j = ht.size() - 1;
    // Initial maximum capacity is 0
    int res = 0;
    // Loop for greedy selection until the two boards meet
    while (i < j)
    {
        // Update maximum capacity
        int cap = min(ht[i], ht[j]) * (j - i);
        res = max(res, cap);
        // Move the shorter board inward
        if (ht[i] < ht[j])
        {
            i++;
        }
        else
        {
            j--;
        }
    }
    return res;
}

/*                                          Question
    Given a positive integer n, split it into at least two positive integers that sum up to n
    Find the maximum product of these integers.

    Suppose we split a factor of 2 from n, then their product is 2(n - 2)
                            2(n - 2) >= n
                                n    >= 4
    So when n >= 4, splitting out a 2 increases the product, which indicates that integers greater than or equal to 4 should be split
    --> The final split should only include factors 1,2,3

    Splitting 1 is the worst as 1 x (n - 1) < n

    3 x 3 > 2 x 2 x 2   --> In the splitting scheme, there should be at most two 2s.
                            Because three 2s can always be replaced by two 3s to obtain a higher product.

    The following greedy strategies can be derived.
    1. Input integer n, continually split out factor 3 until the remainder is 0,1,2
    2. When the remainder is 0, it means n is a multiple of 3, so no further action is taken.
    3. When the remainder is 2, do not continue to split, keep it.
    4. When the remainder is 1, the last 3 should be replace by 2 (2 x 2 > 1 x 3)

        --> n = 3a + b      [n <= 3  --> 1 * (n-1)]
*/

/* Maximum product of cutting: Greedy */
int maxProductCutting(int n)
{
    // When n <= 3, must cut out a 1
    if (n <= 3)
    {
        return 1 * (n - 1);
    }
    // Greedy cut out 3s, a is the number of 3s, b is the remainder
    int a = n / 3;
    int b = n % 3;
    if (b == 1)
    {
        // When the remainder is 1, convert a pair of 1 * 3 into 2 * 2
        return (int)pow(3, a - 1) * 2 * 2;
    }
    if (b == 2)
    {
        // When the remainder is 2, do nothing
        return (int)pow(3, a) * 2;
    }
    // When the remainder is 0, do nothing
    return (int)pow(3, a);
}
