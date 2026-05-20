# P83 — 2D Prefix Sum and Range Queries

## 1. First-Timer Explanation

### What Is It?
**2D prefix sum** extends prefix sums to matrices, enabling O(1) rectangular region sum queries after O(m×n) preprocessing. The formula uses inclusion-exclusion over four corners.

### How It Works
```
prefix[i][j] = sum of all elements in rectangle from (0,0) to (i-1, j-1)

Build: prefix[i][j] = matrix[i-1][j-1]
                    + prefix[i-1][j]    (row above)
                    + prefix[i][j-1]    (col to left)
                    - prefix[i-1][j-1]  (subtract double-counted corner)

Query sum(r1,c1,r2,c2):
= prefix[r2+1][c2+1]
- prefix[r1][c2+1]     (strip above)
- prefix[r2+1][c1]     (strip to left)
+ prefix[r1][c1]       (re-add double-subtracted corner)
```

### Visual Walkthrough
```
Matrix:
1 2 3
4 5 6
7 8 9

prefix (1-indexed, 0-padded):
 0  0  0  0
 0  1  3  6
 0  5 12 21
 0 12 27 45

Sum of (1,1)→(2,2) (0-indexed, inclusive):
= prefix[3][3] - prefix[1][3] - prefix[3][1] + prefix[1][1]
= 45 - 6 - 12 + 1 = 28  (5+6+8+9=28 ✓)
```

### When to Use
- "Sum of elements in rectangular region" → 2D prefix sum
- "Count submatrices with sum = target" → 2D prefix + hash map (flatten rows)
- "Max sum rectangle in 2D" → extend Kadane's per column pair
- "Number of submatrices summing to target" → enumerate row pairs, reduce to 1D

### Common Mistakes
1. Off-by-one: prefix is (m+1) × (n+1); query uses `r1` and `r2+1` (not `r2`)
2. Include-exclude: add back the over-subtracted top-left corner
3. Not initializing prefix with zeros (padding row 0 and col 0)

---

## 2. Revision Card

**Recognition Signal:** "rectangular sum query", "submatrix sum", "2D range query"

**Core Idea:** `prefix[i][j] = mat[i-1][j-1] + prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1]`. Query: `prefix[r2+1][c2+1] - prefix[r1][c2+1] - prefix[r2+1][c1] + prefix[r1][c1]`.

**Trigger Keywords:** rectangle, submatrix, 2D range, region sum

**Complexity:** O(m×n) build, O(1) query

---

## 3. Interview Tell Signs

- "Range sum query 2D (immutable)" → classic 2D prefix sum
- "Number of submatrices that sum to target" → enumerate row pairs, flatten to 1D subarray sum = target
- "Maximum sum rectangle" → Kadane's 2D using prefix sums per column pair
- "Count submatrices with all 1s" → different technique (DP heights per row)

---

## 4. C++ Template

```cpp
#include <vector>
#include <unordered_map>
using namespace std;

// ── 2D Prefix Sum ─────────────────────────────────────────────────────────────
class NumMatrix {
    vector<vector<int>> pre;
public:
    NumMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        pre.assign(m+1, vector<int>(n+1, 0));
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                pre[i][j] = matrix[i-1][j-1]
                           + pre[i-1][j] + pre[i][j-1] - pre[i-1][j-1];
    }
    // Sum of rectangle (r1,c1)→(r2,c2) inclusive, 0-indexed
    int sumRegion(int r1, int c1, int r2, int c2) {
        return pre[r2+1][c2+1] - pre[r1][c2+1] - pre[r2+1][c1] + pre[r1][c1];
    }
};

// ── Count Submatrices Summing to Target ───────────────────────────────────────
int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
    int m = matrix.size(), n = matrix[0].size(), res = 0;
    // Prefix sum each row
    for (auto& row : matrix)
        for (int j = 1; j < n; j++) row[j] += row[j-1];

    // Enumerate all column pairs (c1, c2)
    for (int c1 = 0; c1 < n; c1++) {
        for (int c2 = c1; c2 < n; c2++) {
            // Column sum from c1..c2 for each row → 1D subarray sum = target
            unordered_map<int,int> cnt; cnt[0] = 1;
            int sum = 0;
            for (int r = 0; r < m; r++) {
                sum += matrix[r][c2] - (c1 > 0 ? matrix[r][c1-1] : 0);
                res += cnt[sum - target];
                cnt[sum]++;
            }
        }
    }
    return res;
}

// ── Maximum Sum Rectangle ─────────────────────────────────────────────────────
int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
    int m = matrix.size(), n = matrix[0].size(), res = INT_MIN;
    for (int c1 = 0; c1 < n; c1++) {
        vector<int> colSum(m, 0);
        for (int c2 = c1; c2 < n; c2++) {
            for (int r = 0; r < m; r++) colSum[r] += matrix[r][c2];
            // Find max subarray sum ≤ k using ordered set
            set<int> seen; seen.insert(0);
            int runSum = 0;
            for (int s : colSum) {
                runSum += s;
                auto it = seen.lower_bound(runSum - k);
                if (it != seen.end()) res = max(res, runSum - *it);
                seen.insert(runSum);
            }
        }
    }
    return res;
}
```

---

## 5. How to Present in Interview

**Verbal Script (2D Prefix Sum):**
> "I build a (m+1)×(n+1) prefix sum table padded with zeros. `prefix[i][j]` = sum of all elements in the rectangle from row 0, col 0 to row i-1, col j-1. The recurrence is: `prefix[i][j] = matrix[i-1][j-1] + prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1]` — standard inclusion-exclusion. For a query, I use four corners: add bottom-right, subtract the two strips above and to the left, add back the doubly-subtracted top-left corner."

**Checklist:**
- [ ] Prefix table size: `(m+1) × (n+1)` with all zeros
- [ ] Build: `pre[i][j] = mat[i-1][j-1] + pre[i-1][j] + pre[i][j-1] - pre[i-1][j-1]`
- [ ] Query: `pre[r2+1][c2+1] - pre[r1][c2+1] - pre[r2+1][c1] + pre[r1][c1]`
- [ ] Count submatrices: enumerate column pairs, apply 1D hash map technique per column strip
- [ ] Max ≤ k: use ordered set with lower_bound to find prefix sums in range

---

## 6. Problems

### Problem 1: Range Sum Query 2D — Immutable
**Difficulty:** Medium | **LC:** 304

```cpp
class NumMatrix {
    vector<vector<int>> pre;
public:
    NumMatrix(vector<vector<int>>& m) {
        int rows=m.size(), cols=m[0].size();
        pre.assign(rows+1, vector<int>(cols+1,0));
        for (int i=1;i<=rows;i++) for (int j=1;j<=cols;j++)
            pre[i][j]=m[i-1][j-1]+pre[i-1][j]+pre[i][j-1]-pre[i-1][j-1];
    }
    int sumRegion(int r1,int c1,int r2,int c2){
        return pre[r2+1][c2+1]-pre[r1][c2+1]-pre[r2+1][c1]+pre[r1][c1];
    }
};
// Build: O(m*n) | Query: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Number of Submatrices That Sum to Target
**Difficulty:** Hard | **LC:** 1074

```cpp
int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
    int m=matrix.size(), n=matrix[0].size(), res=0;
    for (auto& row:matrix) for (int j=1;j<n;j++) row[j]+=row[j-1];
    for (int c1=0;c1<n;c1++) for (int c2=c1;c2<n;c2++) {
        unordered_map<int,int> cnt; cnt[0]=1; int sum=0;
        for (int r=0;r<m;r++) {
            sum+=matrix[r][c2]-(c1>0?matrix[r][c1-1]:0);
            res+=cnt[sum-target]; cnt[sum]++;
        }
    }
    return res;
}
// Time: O(m*n²) | Space: O(m)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Max Sum of Rectangle No Larger Than K
**Difficulty:** Hard | **LC:** 363

```cpp
int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
    int m=matrix.size(), n=matrix[0].size(), res=INT_MIN;
    for (int c1=0;c1<n;c1++) {
        vector<int> cs(m,0);
        for (int c2=c1;c2<n;c2++) {
            for (int r=0;r<m;r++) cs[r]+=matrix[r][c2];
            set<int> seen; seen.insert(0); int runSum=0;
            for (int s:cs) {
                runSum+=s;
                auto it=seen.lower_bound(runSum-k);
                if (it!=seen.end()) res=max(res,runSum-*it);
                seen.insert(runSum);
            }
        }
    }
    return res;
}
// Time: O(n²*m*log m) | Space: O(m)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Count Submatrices With All Ones
**Difficulty:** Medium | **LC:** 1504

**Approach:** For each cell (i,j), count consecutive 1s above (height[j]). Then for each row, count valid rectangles.

```cpp
int numSubmat(vector<vector<int>>& mat) {
    int m=mat.size(), n=mat[0].size(), res=0;
    vector<int> height(n,0);
    for (int i=0;i<m;i++) {
        for (int j=0;j<n;j++) height[j] = mat[i][j]==0 ? 0 : height[j]+1;
        // For each ending column j, count rectangles using monotone stack
        vector<int> stk;
        vector<int> cnt(n,0);
        for (int j=0;j<n;j++) {
            while (!stk.empty()&&height[stk.back()]>=height[j]) stk.pop_back();
            cnt[j] = stk.empty() ? (j+1)*height[j] : (j-stk.back())*height[j]+cnt[stk.back()];
            stk.push_back(j);
            res+=cnt[j];
        }
    }
    return res;
}
// Time: O(m*n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Largest Rectangle in Histogram (2D Extension)
**Difficulty:** Hard | **LC:** 85 (Maximal Rectangle)

**Approach:** Build histogram heights per row, apply largest rectangle in histogram (LC 84) to each row.

```cpp
int largestRectangleInHistogram(vector<int>& heights) {
    stack<int> stk; int res=0;
    heights.push_back(0);
    for (int i=0;i<(int)heights.size();i++) {
        while (!stk.empty()&&heights[stk.top()]>heights[i]) {
            int h=heights[stk.top()]; stk.pop();
            int w=stk.empty()?i:i-stk.top()-1;
            res=max(res,h*w);
        }
        stk.push(i);
    }
    return res;
}
int maximalRectangle(vector<vector<char>>& matrix) {
    int m=matrix.size(), n=matrix[0].size(), res=0;
    vector<int> heights(n,0);
    for (int i=0;i<m;i++) {
        for (int j=0;j<n;j++) heights[j]=matrix[i][j]=='0'?0:heights[j]+1;
        res=max(res,largestRectangleInHistogram(heights));
    }
    return res;
}
// Time: O(m*n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: Matrix Block Sum
**Difficulty:** Medium | **LC:** 1314

```cpp
vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int k) {
    int m=mat.size(), n=mat[0].size();
    // Build 2D prefix sum
    vector<vector<int>> pre(m+1,vector<int>(n+1,0));
    for (int i=1;i<=m;i++) for (int j=1;j<=n;j++)
        pre[i][j]=mat[i-1][j-1]+pre[i-1][j]+pre[i][j-1]-pre[i-1][j-1];
    auto query=[&](int r1,int c1,int r2,int c2){
        r1=max(r1,0); c1=max(c1,0); r2=min(r2,m-1); c2=min(c2,n-1);
        return pre[r2+1][c2+1]-pre[r1][c2+1]-pre[r2+1][c1]+pre[r1][c1];
    };
    vector<vector<int>> ans(m,vector<int>(n));
    for (int i=0;i<m;i++) for (int j=0;j<n;j++)
        ans[i][j]=query(i-k,j-k,i+k,j+k);
    return ans;
}
// Time: O(m*n) | Space: O(m*n)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** Build prefix for [[1,2],[3,4]]. What is pre[2][2]?
<details><summary>Reveal</summary>
pre (3×3): pre[1][1]=1, pre[1][2]=1+2=3, pre[2][1]=1+3=4, pre[2][2]=4+pre[1][2]+pre[2][1]-pre[1][1]=4+3+4-1=10. (Full matrix sum=10 ✓).
</details>

**Drill 2:** Using the prefix from Drill 1, find sum of (0,0)→(1,1).
<details><summary>Reveal</summary>
sumRegion(0,0,1,1) = pre[2][2]-pre[0][2]-pre[2][0]+pre[0][0] = 10-0-0+0=10. (All 4 elements: 1+2+3+4=10 ✓).
</details>

**Drill 3:** Count submatrices summing to target=3 in [[1,2],[3,4]]. How many?
<details><summary>Reveal</summary>
Row prefix after modification: [[1,3],[3,7]]. Column pairs: (c1=0,c2=0): colSums=[1,3]. cnt={0:1}. sum=1: cnt[1-3]=cnt[-2]=0, cnt={0:1,1:1}. sum=4: cnt[4-3]=cnt[1]=1, res=1. cnt={0:1,1:1,4:1}. (c1=0,c2=1): colSums=[3,7]. sum=3: cnt[3-3]=1, res=2. sum=10: cnt[10-3]=cnt[7]=0. (c1=1,c2=1): colSums=[2,4]. sum=2: cnt[-1]=0. sum=6: cnt[3]=0. Total: 2 submatrices with sum=3.
</details>

**Drill 4:** Max sum rectangle ≤ k: why use `set::lower_bound(runSum - k)` instead of checking all previous prefix sums?
<details><summary>Reveal</summary>
We want max(runSum - prevSum) where prevSum ≤ runSum - target (so runSum - prevSum ≥ target... wait, we want ≤ k). We want the largest valid rectangle sum ≤ k, i.e., runSum - prevSum ≤ k, i.e., prevSum ≥ runSum - k. lower_bound(runSum-k) finds the smallest prevSum that is ≥ runSum-k. Subtracting: runSum - prevSum ≤ k (valid) and as small as possible (maximized). Without lower_bound, we'd need O(m) to find the optimal previous prefix sum.
</details>

**Drill 5:** Maximal rectangle in [["1","0","1","0"],["1","0","1","1"],["1","1","1","1"]]. What are the heights after row 2?
<details><summary>Reveal</summary>
Row 0: heights=[1,0,1,0]. Row 1: heights=[2,0,2,1]. Row 2: heights=[3,1,3,2]. Largest rectangle in histogram [3,1,3,2]: monotone stack gives max area = 1*4=4 (using height=1 spanning all 4 columns). Or 3*1+3*1=6? Let's check: stack approach: push 0(h=3). i=1(h=1)<3: pop 0, w=1, area=3*1=3. Push 1(h=1). i=2(h=3)>1: push 2. i=3(h=2)<3: pop 2, w=3-1-1=1, area=3*1=3. h=2>1: push 3. End: pop 3, w=4-1-1=2, area=2*2=4. Pop 1, w=4, area=1*4=4. Max=4. Maximal rectangle = 4.
</details>

---

## 8. Complexity Cheatsheet

| Operation | Time | Space |
|-----------|------|-------|
| Build 2D prefix sum | O(m×n) | O(m×n) |
| Range sum query 2D | O(1) | O(1) |
| Count submatrices sum = target | O(m×n²) | O(m) |
| Max sum rectangle ≤ k | O(n²×m log m) | O(m) |
| Maximal rectangle | O(m×n) | O(n) |
| Matrix block sum | O(m×n) | O(m×n) |

---

## 9. Common Follow-up Questions

**Q: Can 2D prefix sum handle updates?**
A: Static prefix sum cannot handle updates efficiently. For dynamic updates, use a 2D Fenwick Tree (BIT) which supports point updates and rectangle queries in O(log m × log n).

**Q: How do you count the number of submatrices with all 1s in O(m×n)?**
A: Per-row histogram heights + monotone stack. For each column j, cnt[j] = number of rectangles ending at column j in the current histogram. Use a decreasing stack to compute cnt[j] in amortized O(1).

**Q: What if the matrix is very large (sparse zeros)?**
A: For sparse matrices, coordinate compression reduces the effective size. Store only non-zero elements and use compressed 2D prefix sums.

---

## 10. Cross-Pattern Connections

- **P79 (Prefix Sums):** 1D prefix sum is a special case; same inclusion-exclusion idea
- **P64 (Monotonic Stack):** Maximal rectangle uses the histogram + stack pattern
- **P97 (Segment Tree):** 2D segment tree handles dynamic 2D range queries
- **P98 (Fenwick Tree):** 2D BIT handles dynamic 2D point update + prefix query
- **P81 (Matrix):** Matrix traversal patterns complement 2D prefix sum
