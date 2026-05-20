# Pattern 39: Matrix Chain / Divide-and-Conquer DP

## Category
Dynamic Programming

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 87. Scramble String | Hard | https://leetcode.com/problems/scramble-string/ |
| 2 | 95. Unique Binary Search Trees II | Medium | https://leetcode.com/problems/unique-binary-search-trees-ii/ |
| 3 | 96. Unique Binary Search Trees | Medium | https://leetcode.com/problems/unique-binary-search-trees/ |
| 4 | 410. Split Array Largest Sum | Hard | https://leetcode.com/problems/split-array-largest-sum/ |
| 5 | 1547. Minimum Cost to Cut a Stick | Hard | https://leetcode.com/problems/minimum-cost-to-cut-a-stick/ |

---

## 1. First-Timer Explanation

### What is this pattern?
**Matrix Chain / Divide-and-Conquer DP** applies to problems where you split a sequence at some pivot and the cost of the split depends on both sub-results. Two main variants:

**Matrix Chain Multiplication (classical):**
- Multiply a chain of matrices with minimum scalar multiplications
- dp[i][j] = min cost to multiply matrices i through j
- Pivot k: `dp[i][j] = min(dp[i][k] + dp[k+1][j] + rows[i]*cols[k]*cols[j])`

**Catalan Number / BST counting:**
- Count structurally distinct BSTs with n nodes
- dp[n] = sum over root k: dp[k-1] * dp[n-k] (left × right subtree combinations)
- This Catalan recurrence appears in many divide-and-conquer DP problems

**Divide-and-Conquer DP optimization:**
- When the optimal split point for `dp[i][j]` is monotone (opt[i][j-1] ≤ opt[i][j] ≤ opt[i+1][j])
- Reduces O(n³) to O(n² log n) or even O(n²) with Knuth's optimization

### Visual Walkthrough
```
Unique BSTs: n=3, nodes {1, 2, 3}

For each root k:
  k=1: left subtree has 0 nodes, right has 2 → dp[0]*dp[2] = 1*2 = 2
       BSTs: 1(null, 2(null,3)) and 1(null, 3(2,null))
  k=2: left has 1 node, right has 1 → dp[1]*dp[1] = 1*1 = 1
       BST: 2(1, 3)
  k=3: left has 2 nodes, right has 0 → dp[2]*dp[0] = 2*1 = 2
       BSTs: 3(2(1,null), null) and 3(1(null,2), null)

Total: dp[3] = 2 + 1 + 2 = 5 (Catalan number C(3) = 5)

Minimum Cost to Cut a Stick: stick=[0,7], cuts=[1,3,4,5]
Add endpoints: [0,1,3,4,5,7]
dp[i][j] = min cost to make all cuts between positions i and j
Each cut costs (length of current segment) = positions[j] - positions[i]
Fill by length (interval DP style)
```

### When TO use this pattern
- Optimal way to split/partition a sequence
- Count of distinct structures (BSTs, parenthesizations, trees)
- Matrix chain multiplication
- "Min cost to cut" problems
- Scramble string checking

### When NOT to use this pattern
- Linear DP sufficient (no divide/conquer split)
- Greedy works
- All partitions can be evaluated independently

### Common Beginner Mistakes
- **Catalan confusion**: dp[n] counts BSTs with n nodes (dp[0]=1, dp[1]=1, dp[2]=2, dp[3]=5...)
- **Cut stick**: add 0 and stick-length as boundary points; sort cuts array; dp on sub-segments
- **Scramble**: memoize with string pairs or (start1, start2, length) — avoid O(n^4) without memoization

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | "optimal partition", "count structures", "scramble string", "min cost to cut" |
| Core Idea | Split at pivot k; combine left/right sub-solutions; find optimal k |
| Trigger Keywords | "unique BSTs", "scramble", "min cost cut", "matrix multiplication order" |
| Avoid When | Linear DP, greedy, simple recursion suffices |
| Time Complexity | O(n³) typical; O(n² log n) with D&C optimization |
| Space Complexity | O(n²) |

**Gotchas:**
- Catalan numbers: dp[0]=1 (empty tree), recurrence = sum dp[k]*dp[n-1-k] for k=0..n-1
- Cut stick: sort cuts + add endpoints; dp[i][j] = min cost = min over cuts k in (i,j) of dp[i][k]+dp[k][j]+pos[j]-pos[i]
- Scramble: string s can be split into two parts (s[0..i] and s[i+1..n-1]), then either keep or swap
- Memoization: use `unordered_map<string, bool>` for scramble, or (i,j,len) tuple

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"unique binary search trees"` → Catalan number DP
- `"scramble string"` → divide-and-conquer string DP
- `"minimum cost to cut"` → interval DP with cut cost
- `"split array largest sum"` → binary search on answer + greedy, or divide-and-conquer DP
- `"optimal matrix multiplication"` → matrix chain DP

---

## 4. C++ Template

```cpp
/*
 * Pattern: Matrix Chain / Divide-and-Conquer DP
 * Time: O(n^3) | Space: O(n^2)
 */

// UNIQUE BSTs — CATALAN NUMBER DP
int numTrees(int n) {
    vector<int> dp(n+1, 0);
    dp[0] = dp[1] = 1;
    for (int i = 2; i <= n; i++)
        for (int k = 1; k <= i; k++)
            dp[i] += dp[k-1] * dp[i-k];  // k = root; left has k-1 nodes, right has i-k
    return dp[n];
}

// GENERATE UNIQUE BST STRUCTURES
vector<TreeNode*> generateTrees(int n) {
    if (n == 0) return {};
    function<vector<TreeNode*>(int,int)> gen = [&](int lo, int hi) -> vector<TreeNode*> {
        if (lo > hi) return {nullptr};
        vector<TreeNode*> result;
        for (int k = lo; k <= hi; k++) {
            for (auto* left  : gen(lo, k-1))
                for (auto* right : gen(k+1, hi))
                    result.push_back(new TreeNode(k, left, right));
        }
        return result;
    };
    return gen(1, n);
}

// MIN COST TO CUT STICK
int minCost(int n, vector<int>& cuts) {
    cuts.push_back(0); cuts.push_back(n);
    sort(cuts.begin(), cuts.end());
    int m = cuts.size();
    vector<vector<int>> dp(m, vector<int>(m, 0));
    for (int len = 2; len < m; len++)
        for (int l = 0; l + len < m; l++) {
            int r = l + len;
            dp[l][r] = INT_MAX;
            for (int k = l+1; k < r; k++)
                dp[l][r] = min(dp[l][r], dp[l][k] + dp[k][r] + cuts[r]-cuts[l]);
        }
    return dp[0][m-1];
}

// SCRAMBLE STRING
unordered_map<string, bool> memo;
bool isScramble(string s1, string s2) {
    if (s1 == s2) return true;
    string key = s1 + "#" + s2;
    if (memo.count(key)) return memo[key];
    int n = s1.size();
    // check if same character multiset
    string sorted1 = s1, sorted2 = s2;
    sort(sorted1.begin(), sorted1.end());
    sort(sorted2.begin(), sorted2.end());
    if (sorted1 != sorted2) return memo[key] = false;
    for (int i = 1; i < n; i++) {
        // no swap
        if (isScramble(s1.substr(0,i), s2.substr(0,i)) &&
            isScramble(s1.substr(i), s2.substr(i)))
            return memo[key] = true;
        // swap
        if (isScramble(s1.substr(0,i), s2.substr(n-i)) &&
            isScramble(s1.substr(i), s2.substr(0,n-i)))
            return memo[key] = true;
    }
    return memo[key] = false;
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"For Unique BSTs, each value from 1 to n can be the root. If k is the root, the left subtree contains values 1..k-1 (dp[k-1] ways) and right subtree contains k+1..n (dp[n-k] ways). Multiplying gives the count for root k. Summing over all k gives the Catalan number: dp[n] = sum of dp[k-1] × dp[n-k] for k=1 to n."

### Interview Flow Checklist
- [ ] Identify the "split point" (root, pivot, cut position)
- [ ] Define dp[i][j] or dp[n] for the sub-problem
- [ ] Write recurrence: for all valid split points k, combine left and right
- [ ] Fill in correct order (length for interval DP, bottom-up for Catalan)
- [ ] Return dp[0][m-1] or dp[n]

---

## 6. Problems

---

### Problem 1: 96. Unique Binary Search Trees
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/unique-binary-search-trees/
**Optimal C++ Solution:**
```cpp
int numTrees(int n) {
    vector<int> dp(n+1, 0);
    dp[0] = dp[1] = 1;
    for (int i = 2; i <= n; i++)
        for (int k = 0; k < i; k++)
            dp[i] += dp[k] * dp[i-1-k];
    return dp[n];
}
```
**Edge Cases:** [ ] n=1 (return 1), [ ] n=0 (return 1 — empty tree)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 95. Unique Binary Search Trees II
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/unique-binary-search-trees-ii/
**Optimal C++ Solution:**
```cpp
vector<TreeNode*> generateTrees(int n) {
    function<vector<TreeNode*>(int,int)> gen = [&](int lo, int hi) -> vector<TreeNode*> {
        if (lo > hi) return {nullptr};
        vector<TreeNode*> res;
        for (int k = lo; k <= hi; k++)
            for (auto* l : gen(lo, k-1))
                for (auto* r : gen(k+1, hi))
                    res.push_back(new TreeNode(k, l, r));
        return res;
    };
    return gen(1, n);
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 3: 1547. Minimum Cost to Cut a Stick
**Difficulty:** Hard
**Leetcode:** https://leetcode.com/problems/minimum-cost-to-cut-a-stick/
**Optimal C++ Solution:**
```cpp
int minCost(int n, vector<int>& cuts) {
    cuts.push_back(0); cuts.push_back(n);
    sort(cuts.begin(), cuts.end());
    int m = cuts.size();
    vector<vector<int>> dp(m, vector<int>(m, 0));
    for (int len = 2; len < m; len++)
        for (int l = 0; l + len < m; l++) {
            int r = l + len;
            dp[l][r] = INT_MAX;
            for (int k = l+1; k < r; k++)
                dp[l][r] = min(dp[l][r], dp[l][k] + dp[k][r] + cuts[r]-cuts[l]);
        }
    return dp[0][m-1];
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 4: 87. Scramble String
**Difficulty:** Hard
**Leetcode:** https://leetcode.com/problems/scramble-string/
**Optimal C++ Solution:**
```cpp
bool isScramble(string s1, string s2) {
    unordered_map<string, bool> memo;
    function<bool(string, string)> solve = [&](string a, string b) -> bool {
        if (a == b) return true;
        string key = a + "#" + b;
        if (memo.count(key)) return memo[key];
        string sa = a, sb = b;
        sort(sa.begin(), sa.end()); sort(sb.begin(), sb.end());
        if (sa != sb) return memo[key] = false;
        int n = a.size();
        for (int i = 1; i < n; i++) {
            if ((solve(a.substr(0,i), b.substr(0,i)) && solve(a.substr(i), b.substr(i))) ||
                (solve(a.substr(0,i), b.substr(n-i)) && solve(a.substr(i), b.substr(0,n-i))))
                return memo[key] = true;
        }
        return memo[key] = false;
    };
    return solve(s1, s2);
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 5: 410. Split Array Largest Sum
**Difficulty:** Hard
**Leetcode:** https://leetcode.com/problems/split-array-largest-sum/
**Why this pattern fits:** Split array into k subarrays; minimize the maximum subarray sum — binary search + greedy OR DP

**Optimal C++ Solution (Binary Search + Greedy):**
```cpp
int splitArray(vector<int>& nums, int k) {
    long long lo = *max_element(nums.begin(), nums.end());
    long long hi = accumulate(nums.begin(), nums.end(), 0LL);
    while (lo < hi) {
        long long mid = lo + (hi - lo) / 2;
        // check if we can split into at most k subarrays with max sum ≤ mid
        int parts = 1; long long curSum = 0;
        for (int x : nums) {
            if (curSum + x > mid) { parts++; curSum = x; }
            else curSum += x;
        }
        if (parts <= k) hi = mid;
        else lo = mid + 1;
    }
    return (int)lo;
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> Count the number of distinct ways to fully parenthesize an expression of n numbers.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Catalan number
**Reason:** This is exactly the Catalan number C(n-1). The recurrence is the same as unique BSTs: for each split position k (which operator is evaluated last), left has k sub-expressions and right has n-k, giving dp[k] × dp[n-k] ways. dp[1]=1, dp[n] = sum dp[k]*dp[n-k] for k=1..n-1.
</details>

---

**Drill 2:**
> You have a chain of n matrices and must multiply them. Given the dimensions, find the minimum number of scalar multiplications.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Matrix Chain Multiplication (classic interval DP)
**Reason:** dp[i][j] = min multiplications to compute product of matrices i..j. For each split k: dp[i][j] = min(dp[i][k] + dp[k+1][j] + dims[i]*dims[k+1]*dims[j+1]). Fill by increasing interval length. O(n³) time. The canonical D&C DP problem.
</details>

---

**Drill 3:**
> Divide an array into k groups of consecutive elements. Minimize the maximum group sum. What is the minimum possible maximum?

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Binary Search + Greedy (same as Split Array Largest Sum)
**Reason:** Binary search on the answer (max group sum). For a given candidate max, greedily check: can we split the array into ≤ k groups each with sum ≤ max? Greedy: fill each group until adding next element would exceed max. O(n log(sum)) total.
</details>

---

**Drill 4:**
> Count the number of distinct binary trees (not BSTs) with n nodes.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Catalan number (same formula, different interpretation)
**Reason:** The number of full binary trees with n+1 leaves (= n internal nodes) is C(n), the n-th Catalan number. Recurrence: for each left subtree size k (0 to n-1): dp[n] += dp[k] × dp[n-1-k]. Same formula as unique BSTs. C(0)=1, C(1)=1, C(2)=2, C(3)=5...
</details>

---

**Drill 5:**
> Given a sequence of numbers, find the minimum cost to reduce them all to a single number where the cost of merging two adjacent groups is the sum of their sizes.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Interval DP (Stone merging variant)
**Reason:** dp[l][r] = min cost to merge nums[l..r] into one. With prefix sums for O(1) sum queries: dp[l][r] = min over k in (l,r) of dp[l][k] + dp[k+1][r] + sum(l,r). Fill by length. Standard interval DP. O(n³) time.
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Space | Notes |
|---------|------|-------|-------|
| Catalan DP (BST count) | O(n²) | O(n) | 1D DP |
| Generate BSTs | O(C(n) × n) | O(C(n) × n) | Exponential output |
| Min cost to cut | O(n³) | O(n²) | n = cuts + 2 |
| Scramble string | O(n⁴) | O(n³) | Memoized recursion |
| Split array (BS+greedy) | O(n log S) | O(1) | S = total sum |
| Matrix chain | O(n³) | O(n²) | Classic interval DP |

---

## 9. Common Follow-up Questions

1. What are Catalan numbers and where do they appear? (C(n) = (2n choose n) / (n+1). Appears in: BST count, parenthesization count, full binary trees, mountain polygons, non-crossing partitions)
2. When does binary search apply instead of DP for partition problems? (When the problem has monotone feasibility: "is max ≤ X feasible?" with X monotone → binary search. DP for min/max cost of the partition itself)
3. Knuth's optimization for interval DP — when does it apply? (When optimal split point is monotone: opt[i][j] ≥ opt[i][j-1] and opt[i][j] ≥ opt[i+1][j]. Reduces O(n³) to O(n²))
4. How to generate all unique BSTs without exponential memory? (Use an iterator/generator pattern; generate trees lazily on demand rather than storing all at once)

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| Interval DP | Same structure; split at pivot | 1547. Min Cost Cut, Burst Balloons |
| Binary Search | Partition with monotone feasibility | 410. Split Array Largest Sum |
| Recursion + Memo | Top-down version of interval DP | 87. Scramble String |
| Catalan Numbers | Count structures with divide-and-conquer | 96. Unique BSTs |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
