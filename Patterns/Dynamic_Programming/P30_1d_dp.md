# Pattern 30: 1D Dynamic Programming (Linear DP)

## Category
Dynamic Programming

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 70. Climbing Stairs | Easy | https://leetcode.com/problems/climbing-stairs/ |
| 2 | 198. House Robber | Medium | https://leetcode.com/problems/house-robber/ |
| 3 | 213. House Robber II | Medium | https://leetcode.com/problems/house-robber-ii/ |
| 4 | 300. Longest Increasing Subsequence | Medium | https://leetcode.com/problems/longest-increasing-subsequence/ |
| 5 | 322. Coin Change | Medium | https://leetcode.com/problems/coin-change/ |
| 6 | 377. Combination Sum IV | Medium | https://leetcode.com/problems/combination-sum-iv/ |
| 7 | 416. Partition Equal Subset Sum | Medium | https://leetcode.com/problems/partition-equal-subset-sum/ |
| 8 | 746. Min Cost Climbing Stairs | Easy | https://leetcode.com/problems/min-cost-climbing-stairs/ |
| 9 | 1143. Longest Common Subsequence | Medium | https://leetcode.com/problems/longest-common-subsequence/ |
| 10 | 53. Maximum Subarray | Medium | https://leetcode.com/problems/maximum-subarray/ |

---

## 1. First-Timer Explanation

### What is this pattern?
**1D DP** stores answers to subproblems in a 1D array. Each entry `dp[i]` answers "what is the optimal value for the first i elements (or target i)?"

**The DP mindset — four steps:**
1. **Define**: what does `dp[i]` represent?
2. **Recurrence**: how does `dp[i]` depend on previous states?
3. **Base case**: what are the smallest valid values of i?
4. **Direction**: fill left to right, or right to left?

**Common recurrences:**
- Fibonacci-style: `dp[i] = dp[i-1] + dp[i-2]`
- House Robber: `dp[i] = max(dp[i-1], dp[i-2] + nums[i])`
- Coin Change: `dp[amount] = min(dp[amount], dp[amount-coin] + 1)`
- LIS: `dp[i] = max(dp[j] + 1)` for all j < i where nums[j] < nums[i]

### Visual Walkthrough
```
House Robber: [2, 7, 9, 3, 1]
dp[i] = max money robbing houses 0..i

dp[0] = 2   (rob house 0)
dp[1] = max(2, 7) = 7  (can't rob adjacent, so best of house 0 or house 1)
dp[2] = max(dp[1], dp[0]+9) = max(7, 11) = 11
dp[3] = max(dp[2], dp[1]+3) = max(11, 10) = 11
dp[4] = max(dp[3], dp[2]+1) = max(11, 12) = 12

Answer: 12 (rob houses 0, 2, 4: 2+9+1=12)

Coin Change: coins=[1,5,11], amount=15
dp[0]=0, dp[i]=min(dp[i-c]+1) for each coin c
dp[1]=1, dp[2]=2, ..., dp[5]=1, dp[6]=2, ..., dp[10]=2, dp[11]=1, dp[15]=3
```

### When TO use this pattern
- "Optimal value" for a 1D sequence or target amount
- Overlapping subproblems with clear recurrence
- "Number of ways" to reach a target (combinatorics DP)
- "Can you partition" (knapsack-style)
- Maximum subarray / minimum cost problems

### When NOT to use this pattern
- Need to track exact items chosen (add backtracking/parent pointers)
- 2D state required (two sequences → 2D DP)
- No overlapping subproblems (greedy or divide-and-conquer instead)

### Common Beginner Mistakes
- **Off-by-one**: is dp[0] an empty set or the first element? Define clearly
- **Coin Change direction**: fill `dp[amount]` from small to large (unbounded) or reverse
- **LIS O(n²) vs O(n log n)**: both important — know the binary search optimization
- **House Robber II**: split into two subproblems (include/exclude first house)

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | "optimal for 1D sequence", "number of ways", "minimum coins", "can partition" |
| Core Idea | dp[i] = optimal for subproblem of size i; build up from base cases |
| Trigger Keywords | "climbing stairs", "rob houses", "coin change", "LIS", "partition sum" |
| Avoid When | No clear recurrence, 2D state needed |
| Time Complexity | O(n) to O(n²) depending on recurrence |
| Space Complexity | O(n) or O(1) with rolling variables |

**Gotchas:**
- House Robber: can optimize to O(1) space with two variables (prev2, prev1)
- Coin Change: `dp[amount] = min over coins`; initialize to INT_MAX, be careful of overflow
- LIS O(n log n): maintain a patience-sort array; binary search for insertion position
- Partition Equal Subset Sum: target = sum/2; if sum is odd → immediately false

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"minimum number of coins"` → coin change DP
- `"number of ways to climb"` → Fibonacci-style DP
- `"rob houses"` + `"adjacent"` constraint → house robber DP
- `"longest increasing subsequence"` → LIS dp with O(n²) or O(n log n)
- `"partition into equal subsets"` → subset-sum DP
- `"maximum subarray sum"` → Kadane's algorithm

---

## 4. C++ Template

```cpp
/*
 * Pattern: 1D Dynamic Programming
 * Time: O(n) to O(n^2) | Space: O(n) or O(1)
 */

// HOUSE ROBBER
int rob(vector<int>& nums) {
    int n = nums.size();
    if (n == 1) return nums[0];
    int prev2 = nums[0], prev1 = max(nums[0], nums[1]);
    for (int i = 2; i < n; i++) {
        int cur = max(prev1, prev2 + nums[i]);
        prev2 = prev1; prev1 = cur;
    }
    return prev1;
}

// COIN CHANGE (min coins)
int coinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, amount + 1);  // init to impossible value
    dp[0] = 0;
    for (int a = 1; a <= amount; a++)
        for (int c : coins)
            if (c <= a) dp[a] = min(dp[a], dp[a-c] + 1);
    return dp[amount] > amount ? -1 : dp[amount];
}

// LIS — O(n^2)
int lengthOfLIS(vector<int>& nums) {
    int n = nums.size(), best = 1;
    vector<int> dp(n, 1);
    for (int i = 1; i < n; i++)
        for (int j = 0; j < i; j++)
            if (nums[j] < nums[i]) { dp[i] = max(dp[i], dp[j]+1); best = max(best, dp[i]); }
    return best;
}

// LIS — O(n log n) with patience sort
int lengthOfLIS_fast(vector<int>& nums) {
    vector<int> tails;
    for (int x : nums) {
        auto it = lower_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) tails.push_back(x);
        else *it = x;
    }
    return tails.size();
}

// KADANE'S (max subarray)
int maxSubArray(vector<int>& nums) {
    int cur = nums[0], best = nums[0];
    for (int i = 1; i < (int)nums.size(); i++) {
        cur = max(nums[i], cur + nums[i]);
        best = max(best, cur);
    }
    return best;
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"This has optimal substructure — the best solution for i depends on optimal solutions for smaller subproblems. I'll define dp[i] as [state definition], establish the recurrence from the problem constraints, and fill it bottom-up. For House Robber: dp[i] = max(dp[i-1], dp[i-2] + nums[i]) — either skip house i (keep dp[i-1]) or rob it (add to best up to i-2). I can optimize space to O(1) by keeping only two variables."

### Interview Flow Checklist
- [ ] Define what dp[i] represents precisely
- [ ] Identify recurrence from problem structure
- [ ] Set base cases (dp[0], dp[1], or empty case)
- [ ] Fill array iteratively
- [ ] Consider space optimization (rolling variables if only need last 1-2 states)
- [ ] Test with example

---

## 6. Problems

---

### Problem 1: 198. House Robber
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/house-robber/
**Optimal C++ Solution:**
```cpp
int rob(vector<int>& nums) {
    int n = nums.size();
    if (n == 1) return nums[0];
    int prev2 = nums[0], prev1 = max(nums[0], nums[1]);
    for (int i = 2; i < n; i++) {
        int cur = max(prev1, prev2 + nums[i]);
        prev2 = prev1; prev1 = cur;
    }
    return prev1;
}
```
**Edge Cases:** [ ] Single house, [ ] Two houses

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 213. House Robber II
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/house-robber-ii/
**Why this pattern fits:** Circular → split into two linear problems

**Optimal C++ Solution:**
```cpp
int rob(vector<int>& nums) {
    int n = nums.size();
    if (n == 1) return nums[0];
    auto robLinear = [&](int lo, int hi) {
        int prev2 = 0, prev1 = 0;
        for (int i = lo; i <= hi; i++) {
            int cur = max(prev1, prev2 + nums[i]);
            prev2 = prev1; prev1 = cur;
        }
        return prev1;
    };
    // Can't rob both first and last
    return max(robLinear(0, n-2), robLinear(1, n-1));
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 3: 322. Coin Change
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/coin-change/
**Optimal C++ Solution:**
```cpp
int coinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount+1, amount+1);
    dp[0] = 0;
    for (int a = 1; a <= amount; a++)
        for (int c : coins)
            if (c <= a) dp[a] = min(dp[a], dp[a-c]+1);
    return dp[amount] > amount ? -1 : dp[amount];
}
```
**Edge Cases:** [ ] Amount 0 (return 0), [ ] No coins can form amount (return -1)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 4: 300. Longest Increasing Subsequence
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/longest-increasing-subsequence/
**Optimal C++ Solution:**
```cpp
int lengthOfLIS(vector<int>& nums) {
    vector<int> tails;  // patience sort: tails[i] = smallest tail of IS of length i+1
    for (int x : nums) {
        auto it = lower_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) tails.push_back(x);
        else *it = x;
    }
    return tails.size();
}
```
**Complexity Analysis:**
- Time: O(n log n) with patience sort binary search
- Space: O(n)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 5: 53. Maximum Subarray (Kadane's)
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/maximum-subarray/
**Optimal C++ Solution:**
```cpp
int maxSubArray(vector<int>& nums) {
    int cur = nums[0], best = nums[0];
    for (int i = 1; i < (int)nums.size(); i++) {
        cur = max(nums[i], cur + nums[i]);  // extend or restart
        best = max(best, cur);
    }
    return best;
}
```
**Edge Cases:** [ ] All negative (answer = max single element), [ ] Single element

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 6: 416. Partition Equal Subset Sum
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/partition-equal-subset-sum/
**Why this pattern fits:** Subset-sum DP (can we pick elements summing to target?)

**Optimal C++ Solution:**
```cpp
bool canPartition(vector<int>& nums) {
    int sum = accumulate(nums.begin(), nums.end(), 0);
    if (sum % 2 != 0) return false;
    int target = sum / 2;
    vector<bool> dp(target+1, false);
    dp[0] = true;
    for (int n : nums)
        for (int j = target; j >= n; j--)  // reverse to avoid using n twice
            dp[j] = dp[j] || dp[j-n];
    return dp[target];
}
```
**Edge Cases:** [ ] Odd total sum (return false), [ ] Single element equals target/2

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 7: 70. Climbing Stairs
**Difficulty:** Easy
**Leetcode:** https://leetcode.com/problems/climbing-stairs/
**Optimal C++ Solution:**
```cpp
int climbStairs(int n) {
    if (n <= 2) return n;
    int prev2 = 1, prev1 = 2;
    for (int i = 3; i <= n; i++) {
        int cur = prev1 + prev2;
        prev2 = prev1; prev1 = cur;
    }
    return prev1;
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> You have a string. Find the minimum number of characters to delete to make it a palindrome.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** 2D DP (LCS variant)
**Reason:** Minimum deletions to make string S a palindrome = len(S) - LCS(S, reverse(S)). The LCS between S and its reverse gives the longest palindromic subsequence — delete everything else. This is a 2D DP problem, not 1D.
</details>

---

**Drill 2:**
> Count the number of ways to make change for a given amount using coins (each coin can be used unlimited times).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** 1D DP (unbounded knapsack — count ways)
**Reason:** dp[amount] = number of ways. For each coin (outer loop), for each amount from coin to target (inner loop): dp[a] += dp[a-coin]. Outer coin loop (not amount loop) gives each combination counted once. LC 518.
</details>

---

**Drill 3:**
> You have a jump game: from index i, you can jump up to nums[i] steps. Find the minimum number of jumps to reach the last index.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Greedy (or DP)
**Reason:** Greedy O(n): at each step, track the furthest reachable position. When you reach the boundary of current jump, increment jumps and extend boundary to furthest. DP O(n²) also works: dp[i] = min jumps to reach i. LC 45.
</details>

---

**Drill 4:**
> Given a list of integers, find the length of the longest subsequence where adjacent elements differ by at most 1.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** 1D DP with hash map
**Reason:** dp[v] = length of longest subsequence ending with value v. For each number x: dp[x] = max(dp[x-1], dp[x+1]) + 1. Process sequentially; use unordered_map for dp. LC 1218.
</details>

---

**Drill 5:**
> You have n tasks, each requiring some days to complete. If you do the same task as yesterday, you get a bonus. Maximize total reward.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** 1D DP
**Reason:** dp[i] = max reward for first i tasks. Recurrence considers two cases: task i is different from task i-1 (dp[i] = dp[i-1] + reward[i]), or same (dp[i] = dp[i-2] + 2*reward[i] + bonus, but tasks must match). Adapt based on exact problem constraints.
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Space | Notes |
|---------|------|-------|-------|
| Climbing Stairs / Fibonacci | O(n) | O(1) | Two variables |
| House Robber | O(n) | O(1) | Two variables |
| Coin Change | O(n × amount) | O(amount) | Double loop |
| LIS (O(n²)) | O(n²) | O(n) | dp[i] = max(dp[j]+1) |
| LIS (O(n log n)) | O(n log n) | O(n) | Patience sort + binary search |
| Partition Subset Sum | O(n × sum) | O(sum) | 0/1 knapsack; reverse fill |
| Kadane's (max subarray) | O(n) | O(1) | |

---

## 9. Common Follow-up Questions

1. How to reconstruct the actual subsequence for LIS? (Maintain a `parent[]` array; when dp[i] is updated from dp[j], set parent[i] = j. Trace back from the optimal i)
2. What's the difference between coin change (min coins) and combination sum (count ways)? (Coin change: minimize count, dp[a] = min. Combination sum IV: count ordered ways, dp[a] = sum of dp[a-c] for each coin)
3. Partition subset sum for three subsets? (NP-hard in general; if three equal parts needed: target = sum/3; extend the DP — harder but doable with bitmask)
4. House Robber on a tree? (Pattern 15 — return (rob, skip) pair from each subtree. P337 House Robber III)

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| Binary Search | LIS O(n log n) via patience sort | 300. LIS |
| 2D DP | Two sequences → LCS, Edit Distance | 1143. LCS |
| Backtracking | Reconstruct DP path | LIS path reconstruction |
| Greedy | Sometimes replaces DP (jump game, gas station) | 45. Jump Game II |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
