# Pattern 32: Knapsack DP (0/1 and Unbounded)

## Category
Dynamic Programming

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 416. Partition Equal Subset Sum | Medium | https://leetcode.com/problems/partition-equal-subset-sum/ |
| 2 | 474. Ones and Zeroes | Medium | https://leetcode.com/problems/ones-and-zeroes/ |
| 3 | 494. Target Sum | Medium | https://leetcode.com/problems/target-sum/ |
| 4 | 518. Coin Change II | Medium | https://leetcode.com/problems/coin-change-ii/ |
| 5 | 1049. Last Stone Weight II | Medium | https://leetcode.com/problems/last-stone-weight-ii/ |
| 6 | 322. Coin Change | Medium | https://leetcode.com/problems/coin-change/ |

---

## 1. First-Timer Explanation

### What is this pattern?
**Knapsack** problems ask: given items with weights/values, and a capacity constraint, what's the optimal selection?

**0/1 Knapsack**: each item used AT MOST ONCE
- Recurrence: `dp[j] = max(dp[j], dp[j-w] + v)` — iterate j REVERSE (right to left) to avoid using item twice

**Unbounded Knapsack**: each item can be used UNLIMITED times
- Recurrence: `dp[j] = max(dp[j], dp[j-w] + v)` — iterate j FORWARD (left to right) so item can be reused

**Subset Sum variant**: `dp[j]` = true/false (can we make exactly j?)
**Count variant**: `dp[j]` = number of ways to make j

**The Fill Direction Rule:**
- 0/1 knapsack → fill j from HIGH to LOW (prevents using same item twice)
- Unbounded knapsack → fill j from LOW to HIGH (allows reuse)

### Visual Walkthrough
```
0/1 Knapsack: items = [(w=2,v=3), (w=3,v=4), (w=4,v=5)], capacity=5
dp[j] = max value achievable with capacity j

Initial: dp = [0, 0, 0, 0, 0, 0]

Item (w=2,v=3): j=5→2 (reverse)
  j=5: dp[5] = max(0, dp[3]+3) = 3
  j=4: dp[4] = max(0, dp[2]+3) = 3
  j=3: dp[3] = max(0, dp[1]+3) = 3
  j=2: dp[2] = max(0, dp[0]+3) = 3
  dp = [0, 0, 3, 3, 3, 3]

Item (w=3,v=4): j=5→3 (reverse)
  j=5: dp[5] = max(3, dp[2]+4) = 7  ← use both items!
  j=4: dp[4] = max(3, dp[1]+4) = 4
  j=3: dp[3] = max(3, dp[0]+4) = 4
  dp = [0, 0, 3, 4, 4, 7]

Item (w=4,v=5): j=5→4 (reverse)
  j=5: dp[5] = max(7, dp[1]+5) = 7
  j=4: dp[4] = max(4, dp[0]+5) = 5
  dp = [0, 0, 3, 4, 5, 7]  → Answer: 7
```

### When TO use this pattern
- "Select items to maximize value within capacity" (0/1 knapsack)
- "Can we partition into subsets with target sum?" (subset sum)
- "Count ways to make target" (count variant)
- Coin change (unbounded)
- "Assign + or - to each number to reach target" (target sum = subset sum)

### When NOT to use this pattern
- Items have fractional values (greedy: fractional knapsack)
- Order matters and items can repeat (permutation DP — different iteration order)
- Items must form contiguous subarrays

### Common Beginner Mistakes
- **0/1: must iterate j in REVERSE**: otherwise dp[j-w] already used the current item
- **Unbounded: forward iteration**: dp[j-w] being already updated = reusing item = correct
- **Target Sum**: transform to subset sum: assign + or - → find subset that sums to (target + total_sum) / 2
- **2D knapsack (Ones and Zeroes)**: two dimensions of capacity (count of 0s and 1s)

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | "select items", "partition sum", "count ways to reach target", "max value with weight limit" |
| Core Idea | dp[j] = optimal for capacity j; direction (reverse=0/1, forward=unbounded) determines reuse |
| Trigger Keywords | "knapsack", "partition", "target sum", "coin change", "ones and zeroes" |
| Avoid When | Fractional items (greedy), order matters (permutation DP) |
| Time Complexity | O(n × capacity) |
| Space Complexity | O(capacity) — 1D rolling |

**Gotchas:**
- 0/1 knapsack: `for j from capacity down to weight` (reverse inner loop)
- Unbounded: `for j from weight to capacity` (forward inner loop)
- Target Sum: dp[j] counts ways; target = (target + sum) / 2 if target + sum is even
- Ones and Zeroes: 2D DP on (ones_capacity, zeros_capacity)

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"partition equal subset"` → 0/1 knapsack, dp[target] == true
- `"target sum"` (+ or -) → count ways to reach (target + sum)/2
- `"coin change"` → unbounded knapsack (min coins or count ways)
- `"ones and zeroes"` → 2D knapsack
- `"last stone weight II"` → minimize difference = subset sum closest to sum/2

---

## 4. C++ Template

```cpp
/*
 * Pattern: Knapsack DP
 * Time: O(n * capacity) | Space: O(capacity)
 */

// 0/1 KNAPSACK (max value)
int knapsack01(int capacity, vector<int>& weights, vector<int>& values) {
    vector<int> dp(capacity + 1, 0);
    for (int i = 0; i < (int)weights.size(); i++)
        for (int j = capacity; j >= weights[i]; j--)  // REVERSE: each item once
            dp[j] = max(dp[j], dp[j - weights[i]] + values[i]);
    return dp[capacity];
}

// 0/1 SUBSET SUM (can we reach target?)
bool subsetSum(vector<int>& nums, int target) {
    vector<bool> dp(target + 1, false);
    dp[0] = true;
    for (int n : nums)
        for (int j = target; j >= n; j--)  // reverse
            dp[j] = dp[j] || dp[j - n];
    return dp[target];
}

// UNBOUNDED KNAPSACK (min coins)
int coinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, amount + 1);
    dp[0] = 0;
    for (int c : coins)
        for (int j = c; j <= amount; j++)  // FORWARD: coins reusable
            dp[j] = min(dp[j], dp[j - c] + 1);
    return dp[amount] > amount ? -1 : dp[amount];
}

// COUNT WAYS (unbounded)
int countWaysUnbounded(vector<int>& coins, int amount) {
    vector<long long> dp(amount + 1, 0);
    dp[0] = 1;
    for (int c : coins)
        for (int j = c; j <= amount; j++)
            dp[j] += dp[j - c];
    return dp[amount];
}

// COUNT WAYS (0/1: order doesn't matter)
int countWays01(vector<int>& nums, int target) {
    vector<int> dp(target + 1, 0);
    dp[0] = 1;
    for (int n : nums)
        for (int j = target; j >= n; j--)  // reverse
            dp[j] += dp[j - n];
    return dp[target];
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"This is a 0/1 knapsack problem — each item can be used at most once. I'll use a 1D DP array where dp[j] represents the maximum value achievable with capacity j. For each item, I iterate the capacity from high to low. This backward pass ensures we don't use the same item twice in a single iteration — if I went forward, dp[j-w] might already include the current item."

### Interview Flow Checklist
- [ ] Identify: 0/1 (each item once) or unbounded (unlimited reuse)?
- [ ] Identify: maximize/minimize value, or count ways, or boolean?
- [ ] Initialize dp[0] and other base cases
- [ ] For each item: inner loop — REVERSE for 0/1, FORWARD for unbounded
- [ ] Return dp[target/capacity]

---

## 6. Problems

---

### Problem 1: 416. Partition Equal Subset Sum
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/partition-equal-subset-sum/
**Optimal C++ Solution:**
```cpp
bool canPartition(vector<int>& nums) {
    int sum = accumulate(nums.begin(), nums.end(), 0);
    if (sum % 2) return false;
    int target = sum / 2;
    vector<bool> dp(target+1, false);
    dp[0] = true;
    for (int n : nums)
        for (int j = target; j >= n; j--)
            dp[j] = dp[j] || dp[j-n];
    return dp[target];
}
```
**Edge Cases:** [ ] Odd total sum, [ ] Single element equals target

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 494. Target Sum
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/target-sum/
**Why this pattern fits:** Assign + or - to each num → count ways to reach sum S = (target + total) / 2

**Optimal C++ Solution:**
```cpp
int findTargetSumWays(vector<int>& nums, int target) {
    int total = accumulate(nums.begin(), nums.end(), 0);
    if ((total + target) % 2 != 0 || abs(target) > total) return 0;
    int S = (total + target) / 2;
    vector<int> dp(S+1, 0);
    dp[0] = 1;
    for (int n : nums)
        for (int j = S; j >= n; j--)
            dp[j] += dp[j-n];
    return dp[S];
}
```
**Complexity Analysis:**
- Time: O(n × S) where S = (target + sum) / 2
- Space: O(S)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 3: 518. Coin Change II (Count Ways)
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/coin-change-ii/
**Why this pattern fits:** Unbounded knapsack, count ways, order doesn't matter

**Optimal C++ Solution:**
```cpp
int change(int amount, vector<int>& coins) {
    vector<int> dp(amount+1, 0);
    dp[0] = 1;
    for (int c : coins)
        for (int j = c; j <= amount; j++)  // forward = unbounded
            dp[j] += dp[j-c];
    return dp[amount];
}
```
**Edge Cases:** [ ] Amount 0 (return 1 — one way: use no coins), [ ] No valid combo (return 0)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 4: 474. Ones and Zeroes
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/ones-and-zeroes/
**Why this pattern fits:** 2D 0/1 knapsack with two capacity dimensions

**Optimal C++ Solution:**
```cpp
int findMaxForm(vector<string>& strs, int m, int n) {
    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
    for (string& s : strs) {
        int zeros = count(s.begin(), s.end(), '0');
        int ones  = s.size() - zeros;
        for (int i = m; i >= zeros; i--)    // reverse both dims: 0/1 knapsack
            for (int j = n; j >= ones; j--)
                dp[i][j] = max(dp[i][j], dp[i-zeros][j-ones] + 1);
    }
    return dp[m][n];
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 5: 1049. Last Stone Weight II
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/last-stone-weight-ii/
**Why this pattern fits:** Minimize |group1 - group2| = minimize (sum - 2 * max_subset_sum_≤ sum/2)

**Optimal C++ Solution:**
```cpp
int lastStoneWeightII(vector<int>& stones) {
    int sum = accumulate(stones.begin(), stones.end(), 0);
    int target = sum / 2;
    vector<bool> dp(target+1, false);
    dp[0] = true;
    for (int s : stones)
        for (int j = target; j >= s; j--)
            dp[j] = dp[j] || dp[j-s];
    for (int j = target; j >= 0; j--)
        if (dp[j]) return sum - 2*j;
    return sum;
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> You have n items. You can take at most 2 of each item. Find the maximum value within a weight capacity.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Bounded knapsack (2 copies) — treat each item as 2 separate 0/1 items
**Reason:** Duplicate each item twice and run standard 0/1 knapsack. Or use binary representation: 2 copies = [1 copy, 1 copy]. For k copies: break into powers of 2 groups (1, 2, 4, ...) — binary grouping trick reduces O(nkC) to O(n log k C).
</details>

---

**Drill 2:**
> Count the number of ways to express n as an ordered sum of positive integers (composition count).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Unbounded knapsack with ORDER mattering (permutation counting)
**Reason:** dp[0]=1. For each target j from 1 to n: dp[j] = sum of dp[j-k] for k=1 to j. Outer loop on AMOUNTS (not items) because order matters → this is LC 377 Combination Sum IV pattern. Different from Coin Change II where order doesn't matter (outer loop on coins).
</details>

---

**Drill 3:**
> Given a list of weights, partition them into two groups to minimize the absolute difference between the two groups' total weights.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Subset sum → find max sum ≤ total/2
**Reason:** This is exactly Last Stone Weight II. Run 0/1 knapsack (boolean) with target = total/2. Find the largest j ≤ total/2 where dp[j] is true. Answer = total - 2*j. Same as LC 1049.
</details>

---

**Drill 4:**
> A store has multiple types of products. Each type has unlimited supply. Find the minimum cost to buy exactly k items total (one item from each type at most once, minimizing total cost).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** 0/1 knapsack with count constraint
**Reason:** 2D DP: dp[i][j] = min cost buying exactly j items from first i products. dp[i][j] = min(dp[i-1][j], dp[i-1][j-1] + cost[i]) — either skip product i or buy it. Answer = dp[n][k].
</details>

---

**Drill 5:**
> You have items with both a weight and a volume. Find maximum value given weight capacity W and volume capacity V.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** 2D knapsack (like Ones and Zeroes)
**Reason:** dp[w][v] = max value with weight ≤ w and volume ≤ v. For each item: iterate both dimensions in reverse (0/1 knapsack). dp[w][v] = max(dp[w][v], dp[w-wi][v-vi] + value_i). Same structure as LC 474 with (0s,1s) → (weight,volume).
</details>

---

## 8. Complexity Cheatsheet

| Variant | Time | Space | Notes |
|---------|------|-------|-------|
| 0/1 Knapsack | O(n × C) | O(C) | Reverse inner loop |
| Unbounded Knapsack | O(n × C) | O(C) | Forward inner loop |
| 2D Knapsack | O(n × C1 × C2) | O(C1 × C2) | 474. Ones and Zeroes |
| Subset Sum (bool) | O(n × target) | O(target) | 0/1 variant |
| Count Ways 0/1 | O(n × target) | O(target) | 494. Target Sum |
| Count Ways Unbounded | O(n × target) | O(target) | 518. Coin Change II |

---

## 9. Common Follow-up Questions

1. What's the difference between Coin Change (min coins) and Coin Change II (count ways)? (Same code structure! Change `min` to `+=` and initialize dp[0]=1 vs dp[0]=0. Direction unchanged: both forward)
2. Why does order of loops (items vs capacity) matter for counting? (Outer loop on items → each combination counted once (unordered). Outer loop on amounts → each ordering counted separately (ordered = permutations))
3. 0/1 knapsack with exact capacity (must use exactly W, not at most)? (Initialize dp to INT_MIN/impossible; only dp[0]=0. Fill normally. dp[W] = INT_MIN means impossible)
4. How to reconstruct which items were selected? (2D DP: keep parent array or re-derive by checking if dp[i][j] came from dp[i-1][j] (skip) or dp[i-1][j-w]+v (take))

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| 1D DP | Knapsack IS 1D DP on capacity | 322. Coin Change |
| 2D DP | Two capacity dimensions | 474. Ones and Zeroes |
| Backtracking | Reconstruct which items selected | Knapsack reconstruction |
| Greedy | Fractional knapsack (divide allowed) | Fractional Knapsack (offline) |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
