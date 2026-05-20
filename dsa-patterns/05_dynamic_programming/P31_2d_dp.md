# Pattern 31: 2D Dynamic Programming

## Category
Dynamic Programming

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 62. Unique Paths | Medium | https://leetcode.com/problems/unique-paths/ |
| 2 | 63. Unique Paths II | Medium | https://leetcode.com/problems/unique-paths-ii/ |
| 3 | 64. Minimum Path Sum | Medium | https://leetcode.com/problems/minimum-path-sum/ |
| 4 | 72. Edit Distance | Hard | https://leetcode.com/problems/edit-distance/ |
| 5 | 97. Interleaving String | Hard | https://leetcode.com/problems/interleaving-string/ |
| 6 | 115. Distinct Subsequences | Hard | https://leetcode.com/problems/distinct-subsequences/ |
| 7 | 1143. Longest Common Subsequence | Medium | https://leetcode.com/problems/longest-common-subsequence/ |
| 8 | 221. Maximal Square | Medium | https://leetcode.com/problems/maximal-square/ |
| 9 | 312. Burst Balloons | Hard | https://leetcode.com/problems/burst-balloons/ |

---

## 1. First-Timer Explanation

### What is this pattern?
**2D DP** uses a 2D table where `dp[i][j]` represents the optimal answer for a subproblem involving the first i elements of one sequence and the first j elements of another (or a 2D grid region).

**Common 2D DP structures:**

**Two-sequence DP (LCS, Edit Distance):**
- `dp[i][j]` = answer for first i chars of s1, first j chars of s2
- Recurrence depends on whether s1[i] == s2[j]

**Grid DP (Unique Paths, Min Path Sum):**
- `dp[r][c]` = answer for reaching cell (r,c) from top-left
- Can only come from above or left

**Interval DP (Burst Balloons):**
- `dp[l][r]` = answer for subarray/interval [l, r]
- Recurrence: try all "last" elements in the interval

### Visual Walkthrough
```
LCS: s1 = "abcde", s2 = "ace"
dp[i][j] = LCS of s1[0..i-1] and s2[0..j-1]

     ""  a  c  e
""  [ 0  0  0  0 ]
a   [ 0  1  1  1 ]
b   [ 0  1  1  1 ]
c   [ 0  1  2  2 ]
d   [ 0  1  2  2 ]
e   [ 0  1  2  3 ]

Recurrence:
  if s1[i-1] == s2[j-1]: dp[i][j] = dp[i-1][j-1] + 1
  else: dp[i][j] = max(dp[i-1][j], dp[i][j-1])

Edit Distance: s1 = "horse", s2 = "ros"
  Match: dp[i][j] = dp[i-1][j-1]
  Mismatch: dp[i][j] = 1 + min(dp[i-1][j-1], dp[i-1][j], dp[i][j-1])
                              (replace,           delete,    insert)
```

### When TO use this pattern
- Two-sequence comparison problems (LCS, edit distance, interleaving)
- Grid traversal with optimal value (min path sum, unique paths)
- Square/rectangle detection in matrices (maximal square)
- Interval DP (optimal parenthesization, burst balloons)
- String matching with wildcards

### When NOT to use this pattern
- Single sequence → 1D DP
- No clear 2D state structure
- Greedy applies (simple grid problems sometimes)

### Common Beginner Mistakes
- **Index offset**: dp[i][j] refers to first i/j elements → s1[i-1] and s2[j-1] in code
- **Edit Distance**: three operations map to three cell references: dp[i-1][j-1] (replace), dp[i-1][j] (delete from s1), dp[i][j-1] (insert into s1)
- **Maximal Square**: dp[i][j] = min of three neighbors + 1 when grid[i][j] == '1'
- **Burst Balloons**: try all LAST balloons to burst in interval [l,r], not first

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | Two sequences, grid traversal, interval optimization, string matching |
| Core Idea | dp[i][j] = optimal for subproblem (i elements of seq1, j elements of seq2) or (row i, col j) |
| Trigger Keywords | "LCS", "edit distance", "unique paths", "interleaving", "maximal square" |
| Avoid When | Only 1D state needed |
| Time Complexity | O(m × n) for most variants |
| Space Complexity | O(m × n) or O(n) with rolling array |

**Gotchas:**
- LCS base case: dp[0][j] = dp[i][0] = 0 (empty string has no common subsequence)
- Edit Distance base case: dp[i][0] = i (delete all), dp[0][j] = j (insert all)
- Maximal Square: answer is max_dp² (side length → area)
- Burst Balloons: add sentinel balloons at boundaries with value 1

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"longest common subsequence"` → classic 2D DP
- `"edit distance"` / `"minimum operations to convert"` → 2D DP with 3 operations
- `"unique paths"` / `"count paths"` in grid → 2D DP (or combinatorics)
- `"maximal square"` → 2D DP with min-of-three-neighbors
- `"interleaving string"` → 2D DP checking both sequences simultaneously
- `"distinct subsequences"` → 2D count DP

---

## 4. C++ Template

```cpp
/*
 * Pattern: 2D Dynamic Programming
 * Time: O(m*n) | Space: O(m*n) or O(n) with rolling array
 */

// LONGEST COMMON SUBSEQUENCE
int longestCommonSubsequence(string s1, string s2) {
    int m = s1.size(), n = s2.size();
    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++) {
            if (s1[i-1] == s2[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
            else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    return dp[m][n];
}

// EDIT DISTANCE
int minDistance(string s1, string s2) {
    int m = s1.size(), n = s2.size();
    vector<vector<int>> dp(m+1, vector<int>(n+1));
    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int j = 0; j <= n; j++) dp[0][j] = j;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++) {
            if (s1[i-1] == s2[j-1]) dp[i][j] = dp[i-1][j-1];
            else dp[i][j] = 1 + min({dp[i-1][j-1], dp[i-1][j], dp[i][j-1]});
        }
    return dp[m][n];
}

// UNIQUE PATHS (grid, no obstacles)
int uniquePaths(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n, 1));
    for (int r = 1; r < m; r++)
        for (int c = 1; c < n; c++)
            dp[r][c] = dp[r-1][c] + dp[r][c-1];
    return dp[m-1][n-1];
}

// MAXIMAL SQUARE
int maximalSquare(vector<vector<char>>& matrix) {
    int rows = matrix.size(), cols = matrix[0].size(), maxSide = 0;
    vector<vector<int>> dp(rows, vector<int>(cols, 0));
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++) {
            if (matrix[r][c] == '0') continue;
            dp[r][c] = (r>0 && c>0) ? min({dp[r-1][c], dp[r][c-1], dp[r-1][c-1]}) + 1 : 1;
            maxSide = max(maxSide, dp[r][c]);
        }
    return maxSide * maxSide;
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"For LCS, I define dp[i][j] as the length of the longest common subsequence of the first i characters of s1 and first j characters of s2. If s1[i-1] == s2[j-1], they match and we extend the LCS by 1: dp[i][j] = dp[i-1][j-1] + 1. If they don't match, we take the best of skipping a character from either string: dp[i][j] = max(dp[i-1][j], dp[i][j-1])."

### Interview Flow Checklist
- [ ] Define dp[i][j] precisely (what two subproblems does it combine?)
- [ ] Set base cases (dp[0][*] and dp[*][0])
- [ ] Write recurrence for match and mismatch cases
- [ ] Fill table row by row
- [ ] Identify the answer cell (usually dp[m][n])
- [ ] Consider space optimization if asked

---

## 6. Problems

---

### Problem 1: 1143. Longest Common Subsequence
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/longest-common-subsequence/
**Optimal C++ Solution:**
```cpp
int longestCommonSubsequence(string text1, string text2) {
    int m = text1.size(), n = text2.size();
    vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++) {
            if (text1[i-1] == text2[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
            else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    return dp[m][n];
}
```
**Edge Cases:** [ ] Empty string, [ ] No common characters, [ ] One string is prefix of other

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 72. Edit Distance
**Difficulty:** Hard
**Leetcode:** https://leetcode.com/problems/edit-distance/
**Optimal C++ Solution:**
```cpp
int minDistance(string word1, string word2) {
    int m = word1.size(), n = word2.size();
    vector<vector<int>> dp(m+1, vector<int>(n+1));
    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int j = 0; j <= n; j++) dp[0][j] = j;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++) {
            if (word1[i-1] == word2[j-1]) dp[i][j] = dp[i-1][j-1];
            else dp[i][j] = 1 + min({dp[i-1][j-1], dp[i-1][j], dp[i][j-1]});
        }
    return dp[m][n];
}
```
**Edge Cases:** [ ] One empty string (insert/delete all), [ ] Identical strings (return 0)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 3: 62. Unique Paths
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/unique-paths/
**Optimal C++ Solution:**
```cpp
int uniquePaths(int m, int n) {
    vector<int> dp(n, 1);
    for (int r = 1; r < m; r++)
        for (int c = 1; c < n; c++)
            dp[c] += dp[c-1];
    return dp[n-1];
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 4: 64. Minimum Path Sum
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/minimum-path-sum/
**Optimal C++ Solution:**
```cpp
int minPathSum(vector<vector<int>>& grid) {
    int rows = grid.size(), cols = grid[0].size();
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++) {
            if (r == 0 && c == 0) continue;
            else if (r == 0) grid[r][c] += grid[r][c-1];
            else if (c == 0) grid[r][c] += grid[r-1][c];
            else grid[r][c] += min(grid[r-1][c], grid[r][c-1]);
        }
    return grid[rows-1][cols-1];
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 5: 221. Maximal Square
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/maximal-square/
**Optimal C++ Solution:**
```cpp
int maximalSquare(vector<vector<char>>& matrix) {
    int rows = matrix.size(), cols = matrix[0].size(), maxSide = 0;
    vector<vector<int>> dp(rows, vector<int>(cols, 0));
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++) {
            if (matrix[r][c] == '1') {
                dp[r][c] = (r>0 && c>0) ?
                    min({dp[r-1][c], dp[r][c-1], dp[r-1][c-1]}) + 1 : 1;
                maxSide = max(maxSide, dp[r][c]);
            }
        }
    return maxSide * maxSide;
}
```
**Edge Cases:** [ ] All 0s (return 0), [ ] 1×1 grid

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 6: 312. Burst Balloons
**Difficulty:** Hard
**Leetcode:** https://leetcode.com/problems/burst-balloons/
**Why this pattern fits:** Interval DP — dp[l][r] = max coins from bursting all balloons in (l,r)

**Optimal C++ Solution:**
```cpp
int maxCoins(vector<int>& nums) {
    // add sentinel balloons of value 1
    nums.insert(nums.begin(), 1);
    nums.push_back(1);
    int n = nums.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int len = 2; len < n; len++) {     // interval length
        for (int l = 0; l + len < n; l++) { // left boundary
            int r = l + len;
            for (int k = l+1; k < r; k++) { // k = LAST balloon burst in (l,r)
                dp[l][r] = max(dp[l][r],
                    dp[l][k] + nums[l]*nums[k]*nums[r] + dp[k][r]);
            }
        }
    }
    return dp[0][n-1];
}
```
**Edge Cases:** [ ] Single balloon, [ ] All 1s

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 7: 97. Interleaving String
**Difficulty:** Hard
**Leetcode:** https://leetcode.com/problems/interleaving-string/
**Optimal C++ Solution:**
```cpp
bool isInterleave(string s1, string s2, string s3) {
    int m = s1.size(), n = s2.size();
    if (m + n != (int)s3.size()) return false;
    vector<vector<bool>> dp(m+1, vector<bool>(n+1, false));
    dp[0][0] = true;
    for (int i = 1; i <= m; i++) dp[i][0] = dp[i-1][0] && s1[i-1]==s3[i-1];
    for (int j = 1; j <= n; j++) dp[0][j] = dp[0][j-1] && s2[j-1]==s3[j-1];
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            dp[i][j] = (dp[i-1][j] && s1[i-1]==s3[i+j-1]) ||
                       (dp[i][j-1] && s2[j-1]==s3[i+j-1]);
    return dp[m][n];
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> Find the longest palindromic subsequence in a string.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** 2D DP or 1D DP via LCS
**Reason:** Method 1: LCS(s, reverse(s)) = longest palindromic subsequence. Method 2: dp[l][r] = longest palindromic subsequence in s[l..r]. If s[l]==s[r]: dp[l][r]=dp[l+1][r-1]+2. Else: dp[l][r]=max(dp[l+1][r], dp[l][r-1]). LC 516.
</details>

---

**Drill 2:**
> Count the number of distinct ways to reach the bottom-right of a grid with obstacles (some cells are blocked).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** 2D DP (Unique Paths II)
**Reason:** dp[r][c] = number of paths to (r,c). If cell is obstacle, dp[r][c]=0. Otherwise dp[r][c] = dp[r-1][c] + dp[r][c-1]. Base case: dp[0][0]=1 if not obstacle, 0 otherwise. LC 63.
</details>

---

**Drill 3:**
> You have two strings. Find the minimum number of characters to insert into either string to make them equal.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** 2D DP (LCS variant)
**Reason:** Minimum insertions = len(s1) + len(s2) - 2 * LCS(s1, s2). Characters in LCS stay; all others must be inserted to match. LC 1312 variant.
</details>

---

**Drill 4:**
> In a grid, each cell has a value. Find the path from top-left to bottom-right (only right/down moves) that maximizes the product of values along the path (values can be negative).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** 2D DP with (max, min) pair
**Reason:** Track both maximum and minimum product to each cell (negative * negative = positive). dp_max[r][c] = max(max_prev * val, min_prev * val). dp_min[r][c] similarly. LC 1594.
</details>

---

**Drill 5:**
> Given two sequences, find the shortest supersequence containing both as subsequences.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** 2D DP (LCS + reconstruction)
**Reason:** Shortest common supersequence length = len(s1) + len(s2) - LCS(s1, s2). To reconstruct: trace back through the DP table — when characters match (LCS), include once; when they don't, include the character from whichever sequence we skip. LC 1092.
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Space | Notes |
|---------|------|-------|-------|
| LCS | O(m×n) | O(m×n) → O(n) rolling | |
| Edit Distance | O(m×n) | O(m×n) → O(n) rolling | |
| Unique Paths | O(m×n) | O(n) 1D rolling | |
| Min Path Sum | O(m×n) | O(1) in-place | |
| Maximal Square | O(m×n) | O(n) rolling | |
| Burst Balloons (interval) | O(n³) | O(n²) | Interval DP |
| Interleaving | O(m×n) | O(n) rolling | |

---

## 9. Common Follow-up Questions

1. Can you reduce 2D DP space to O(n)? (Yes for most — process row by row, keeping only previous row. Some problems need careful order of column updates to avoid using values from the current row)
2. How to reconstruct the LCS string? (Backtrack through dp table: when s1[i-1]==s2[j-1], include character and move diagonally. Otherwise move in direction of larger value)
3. What's the difference between LCS and longest common substring? (LCS: subsequence, not necessarily contiguous — 2D DP. Substring: contiguous — dp[i][j] = length of common substring ending at i,j; reset to 0 on mismatch)
4. Edit Distance with only insertions and deletions (no replace)? (Cost = len(s1) + len(s2) - 2*LCS(s1, s2) — each LCS character is "kept," all others require one insert and one delete)

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| 1D DP | Space optimization: rolling array | LCS, Edit Distance |
| String operations | LCS → edit distance → interleaving | Text processing problems |
| Interval DP | 2D where l≤r, diagonal fill | 312. Burst Balloons, 516. Palindrome |
| Backtracking | Reconstruct DP path | LCS reconstruction, Edit ops sequence |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
