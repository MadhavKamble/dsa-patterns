# Pattern 35: Interval DP

## Category
Dynamic Programming

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 312. Burst Balloons | Hard | https://leetcode.com/problems/burst-balloons/ |
| 2 | 375. Guess Number Higher or Lower II | Medium | https://leetcode.com/problems/guess-number-higher-or-lower-ii/ |
| 3 | 486. Predict the Winner | Medium | https://leetcode.com/problems/predict-the-winner/ |
| 4 | 516. Longest Palindromic Subsequence | Medium | https://leetcode.com/problems/longest-palindromic-subsequence/ |
| 5 | 877. Stone Game | Medium | https://leetcode.com/problems/stone-game/ |
| 6 | 1039. Minimum Score Triangulation of Polygon | Medium | https://leetcode.com/problems/minimum-score-triangulation-of-polygon/ |

---

## 1. First-Timer Explanation

### What is this pattern?
**Interval DP** solves problems where the answer for an interval [l, r] depends on answers to smaller sub-intervals. You fill the DP table diagonally — start with intervals of length 1, then length 2, and so on.

**Key structure:**
- `dp[l][r]` = optimal answer for the interval/subarray `[l, r]`
- Base case: `dp[i][i]` (single element)
- Transition: try all "split points" k in [l, r]
  - `dp[l][r] = optimal over k of (dp[l][k] + dp[k+1][r] + cost(l,k,r))`

**Fill order**: must fill in increasing interval length, because `dp[l][r]` needs all smaller intervals.

```
Fill order for array of size 4:
Length 1: dp[0][0], dp[1][1], dp[2][2], dp[3][3]
Length 2: dp[0][1], dp[1][2], dp[2][3]
Length 3: dp[0][2], dp[1][3]
Length 4: dp[0][3]
```

**Burst Balloons twist**: dp[l][r] = last balloon to burst in open interval (l, r), not split point dividing [l,r] into two sub-problems.

### Visual Walkthrough
```
Predict the Winner: nums = [1, 5, 2]
dp[l][r] = max score advantage (player1 - player2) for nums[l..r]

dp[0][0]=1, dp[1][1]=5, dp[2][2]=2

dp[0][1]: player picks max of:
  pick left (nums[0]=1): 1 - dp[1][1] = 1 - 5 = -4
  pick right (nums[1]=5): 5 - dp[0][0] = 5 - 1 = 4
  dp[0][1] = max(-4, 4) = 4

dp[1][2]: pick nums[1]=5: 5-2=3 or nums[2]=2: 2-5=-3 → dp[1][2]=3

dp[0][2]: pick nums[0]=1: 1-dp[1][2]=1-3=-2
          pick nums[2]=2: 2-dp[0][1]=2-4=-2
          dp[0][2] = max(-2,-2) = -2

Player1 advantage = -2 < 0 → Player2 wins (or it's a draw in some formulations)
```

### When TO use this pattern
- Optimal parenthesization (matrix chain multiplication)
- Game theory where players pick from ends of array
- "Last element to process" in an interval determines the cost
- Longest palindromic subsequence
- Optimal triangulation of polygon
- Burst balloons / stone merging

### When NOT to use this pattern
- Linear DP (no need for interval state)
- Graph problems (wrong structure)
- When greedy works (not overlapping subproblems)

### Common Beginner Mistakes
- **Fill order**: must fill by interval length, not row by row
- **Burst Balloons**: k = LAST balloon burst, not split point
- **Predict the Winner**: dp[l][r] = advantage (score diff), not absolute score
- **Palindromic subsequence**: can be solved with interval DP or LCS(s, reverse(s)) — both O(n²)

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | "merge intervals optimally", "pick from ends of array", "optimal parenthesization", "last to burst" |
| Core Idea | dp[l][r] = optimal for interval [l..r]; fill in increasing length; try all split/pivot points |
| Trigger Keywords | "burst balloons", "stone merge", "predict winner", "min score triangulation" |
| Avoid When | Linear state sufficient, no interval decomposition |
| Time Complexity | O(n³) typical |
| Space Complexity | O(n²) |

**Gotchas:**
- Fill by increasing interval LENGTH: `for len in 2..n: for l in 0..n-len: r = l+len-1`
- Burst Balloons: open interval (l,r), boundaries are sentinels; k is last to burst, gains `nums[l]*nums[k]*nums[r]`
- Stone Game / Predict Winner: dp[l][r] = score advantage = my_score - opponent_score

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"burst balloons"` → interval DP with last-to-burst pivot
- `"stone game"` / `"piles"` + take from ends → interval DP or greedy
- `"predict the winner"` → interval DP, score advantage
- `"minimum cost to merge"` → interval DP, split point
- `"minimum triangulation"` → interval DP on polygon vertices
- `"longest palindromic subsequence"` → interval DP or LCS trick

---

## 4. C++ Template

```cpp
/*
 * Pattern: Interval DP
 * Time: O(n^3) | Space: O(n^2)
 */

// GENERAL INTERVAL DP TEMPLATE
int intervalDP(vector<int>& arr) {
    int n = arr.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    // base case: single elements
    for (int i = 0; i < n; i++) dp[i][i] = /* base value */0;

    // fill by increasing interval length
    for (int len = 2; len <= n; len++) {
        for (int l = 0; l + len - 1 < n; l++) {
            int r = l + len - 1;
            dp[l][r] = INT_MAX;  // or INT_MIN for maximization
            for (int k = l; k < r; k++) {
                int val = dp[l][k] + dp[k+1][r] + /* cost(l,k,r) */0;
                dp[l][r] = min(dp[l][r], val);
            }
        }
    }
    return dp[0][n-1];
}

// PREDICT THE WINNER (game theory)
bool predictTheWinner(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> dp(n, vector<int>(n));
    for (int i = 0; i < n; i++) dp[i][i] = nums[i];
    for (int len = 2; len <= n; len++)
        for (int l = 0; l + len - 1 < n; l++) {
            int r = l + len - 1;
            dp[l][r] = max(nums[l] - dp[l+1][r], nums[r] - dp[l][r-1]);
        }
    return dp[0][n-1] >= 0;
}

// BURST BALLOONS
int maxCoins(vector<int>& nums) {
    nums.insert(nums.begin(), 1); nums.push_back(1);
    int n = nums.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int len = 2; len < n; len++)
        for (int l = 0; l + len < n; l++) {
            int r = l + len;
            for (int k = l+1; k < r; k++)
                dp[l][r] = max(dp[l][r], dp[l][k] + nums[l]*nums[k]*nums[r] + dp[k][r]);
        }
    return dp[0][n-1];
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"This is an interval DP problem. I define dp[l][r] as the optimal answer for the subarray from index l to r. The key insight is the filling order: I must compute all intervals of length 2 before length 3, and so on — filling by increasing interval length ensures all sub-intervals are ready when needed. For each interval [l, r], I try all split points k and combine the two sub-solutions."

### Interview Flow Checklist
- [ ] Define dp[l][r] clearly
- [ ] Establish base cases (single elements, length 1)
- [ ] Identify split point k and the cost formula
- [ ] Fill by increasing interval length (outer loop = length)
- [ ] Return dp[0][n-1]

---

## 6. Problems

---

### Problem 1: 312. Burst Balloons
**Difficulty:** Hard
**Leetcode:** https://leetcode.com/problems/burst-balloons/
**Optimal C++ Solution:**
```cpp
int maxCoins(vector<int>& nums) {
    nums.insert(nums.begin(), 1); nums.push_back(1);
    int n = nums.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int len = 2; len < n; len++)
        for (int l = 0; l + len < n; l++) {
            int r = l + len;
            for (int k = l+1; k < r; k++)
                dp[l][r] = max(dp[l][r],
                    dp[l][k] + nums[l]*nums[k]*nums[r] + dp[k][r]);
        }
    return dp[0][n-1];
}
```
**Edge Cases:** [ ] Single balloon, [ ] All balloons same value

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 486. Predict the Winner
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/predict-the-winner/
**Optimal C++ Solution:**
```cpp
bool predictTheWinner(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> dp(n, vector<int>(n));
    for (int i = 0; i < n; i++) dp[i][i] = nums[i];
    for (int len = 2; len <= n; len++)
        for (int l = 0; l + len - 1 < n; l++) {
            int r = l + len - 1;
            dp[l][r] = max(nums[l] - dp[l+1][r], nums[r] - dp[l][r-1]);
        }
    return dp[0][n-1] >= 0;  // Player 1 wins or ties
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 3: 516. Longest Palindromic Subsequence
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/longest-palindromic-subsequence/
**Optimal C++ Solution:**
```cpp
int longestPalindromeSubseq(string s) {
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) dp[i][i] = 1;
    for (int len = 2; len <= n; len++)
        for (int l = 0; l + len - 1 < n; l++) {
            int r = l + len - 1;
            if (s[l] == s[r]) dp[l][r] = dp[l+1][r-1] + 2;
            else dp[l][r] = max(dp[l+1][r], dp[l][r-1]);
        }
    return dp[0][n-1];
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 4: 1039. Minimum Score Triangulation of Polygon
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/minimum-score-triangulation-of-polygon/
**Why this pattern fits:** Split polygon [l,r] at vertex k; cost = values[l]*values[k]*values[r]

**Optimal C++ Solution:**
```cpp
int minScoreTriangulation(vector<int>& values) {
    int n = values.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int len = 2; len < n; len++)
        for (int l = 0; l + len < n; l++) {
            int r = l + len;
            dp[l][r] = INT_MAX;
            for (int k = l+1; k < r; k++)
                dp[l][r] = min(dp[l][r],
                    dp[l][k] + values[l]*values[k]*values[r] + dp[k][r]);
        }
    return dp[0][n-1];
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 5: 375. Guess Number Higher or Lower II
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/guess-number-higher-or-lower-ii/
**Why this pattern fits:** dp[l][r] = min guaranteed cost to guess number in [l,r]

**Optimal C++ Solution:**
```cpp
int getMoneyAmount(int n) {
    vector<vector<int>> dp(n+2, vector<int>(n+2, 0));
    for (int len = 2; len <= n; len++)
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            dp[l][r] = INT_MAX;
            for (int k = l; k <= r; k++) {
                int cost = k + max(k>l ? dp[l][k-1] : 0,
                                   k<r ? dp[k+1][r] : 0);
                dp[l][r] = min(dp[l][r], cost);
            }
        }
    return dp[1][n];
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> You have a row of n books. Adjacent books can be merged at a cost equal to the sum of their page counts. Merged book has combined page count. Find minimum cost to merge all books into one.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Interval DP (same as stone merging)
**Reason:** dp[l][r] = min cost to merge books[l..r]. Precompute prefix sums for O(1) range sum. For split k: dp[l][r] = min(dp[l][k] + dp[k+1][r] + sum(l,r)). Fill by length. Classic matrix chain / stone merge pattern.
</details>

---

**Drill 2:**
> In a game, two players alternately remove either the leftmost or rightmost stone. Each stone has a value. The player with the highest total value wins. Does the first player always win?

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Interval DP or observation
**Reason:** This is Stone Game (LC 877). Mathematical observation: first player can always win (for even n, stones can be split into odd and even indexed; one group always has higher sum; first player picks the group). Interval DP also works: dp[l][r] = advantage. First player wins if dp[0][n-1] > 0.
</details>

---

**Drill 3:**
> Given a string, find the minimum number of deletions to make it a palindrome.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Interval DP or LCS
**Reason:** Method 1: Interval DP on palindromic subsequence. Min deletions = n - LPS(s). Method 2: LCS(s, reverse(s)) gives longest palindromic subsequence length. Min deletions = n - LCS_length. Both O(n²).
</details>

---

**Drill 4:**
> You have an expression with numbers and operators (+, *). Different parenthesizations give different results. Find all possible results (count distinct values).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Interval DP (Different Ways to Add Parentheses)
**Reason:** dp[l][r] = set of values achievable from expression[l..r]. For each operator k in [l,r]: combine all values from left side (dp[l][k-1]) with all values from right side (dp[k+1][r]) using the operator at k. LC 241.
</details>

---

**Drill 5:**
> Given a list of words, find the minimum number of words to read such that you can form all possible subsequences up to length k. Words can be concatenated.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Not typically interval DP; context-dependent
**Reason:** This problem depends heavily on specific constraints. If it involves optimal grouping of a sequence, interval DP might apply. If it's about covering subsequences, it could be a set cover problem (NP-hard). Clarify constraints before choosing the approach.
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Space | Notes |
|---------|------|-------|-------|
| Standard Interval DP | O(n³) | O(n²) | Three nested loops |
| Burst Balloons | O(n³) | O(n²) | Sentinels at boundaries |
| Predict the Winner | O(n²) | O(n²) → O(n) | No split point; pick from ends |
| LPS (Interval DP) | O(n²) | O(n²) → O(n) | Or use LCS trick |
| Triangulation | O(n³) | O(n²) | Fixed vertex style |

---

## 9. Common Follow-up Questions

1. Can Interval DP be optimized below O(n³)? (Knuth's optimization reduces certain interval DP problems to O(n²) when the optimal split point is monotone — applicable to optimal BST, matrix chain multiplication)
2. Why fill by length instead of by row? (dp[l][r] depends on dp[l][k] and dp[k+1][r] where both k and k+1 define smaller intervals — if you fill by row, these sub-intervals aren't computed yet)
3. What's the space optimization for Interval DP? (Difficult — unlike linear DP, you generally need the full O(n²) table because dp[l][r] can depend on any sub-interval, not just the previous row/column)
4. Predict the Winner: is there a closed-form? (Yes for the pure game theory case — if n is odd, first player always wins. If n is even, it depends on whether sum of even-indexed or odd-indexed elements is larger, which first player can guarantee)

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| Prefix Sums | O(1) range sum in interval cost | Stone merging |
| Game Theory | Pick from ends → score advantage | 486, 877 |
| LCS | LPS = LCS(s, rev(s)) — simpler code | 516. LPS |
| Matrix Chain | Classic interval DP (not on LC) | Optimal parenthesization |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
