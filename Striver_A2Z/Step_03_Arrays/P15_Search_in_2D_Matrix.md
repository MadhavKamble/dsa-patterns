# 🔥 Search an Element in a 2D Matrix

> **LeetCode #74** · **Difficulty:** Medium · **Step 3 — Arrays · P15**

---

## 🧠 Problem Understanding

**What is it asking?**
Given an M×N integer matrix where:
- Each row is sorted in ascending order
- The first integer of each row is greater than the last integer of the previous row

Determine if `target` exists in the matrix.

**Input:** `matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]]`, `target = 3`
**Output:** `true`

**Constraints:** `1 ≤ M, N ≤ 100`

**Key Observations:**
- The entire matrix is essentially a sorted 1D array "folded" row by row
- A cell at `(row, col)` in the 1D-equivalent index `k` maps as: `row = k / N`, `col = k % N`
- This makes the whole matrix binary-searchable as one sorted sequence

**Simple Example:**
```
Matrix:          Equivalent 1D:
1  3  5  7       [1, 3, 5, 7, 10, 11, 16, 20, 23, 30, 34, 60]
10 11 16 20
23 30 34 60

target = 3 → index 1 in 1D → (1/4, 1%4) = (0,1) → matrix[0][1] = 3 ✅
```

---

## 🥉 Brute Force Approach

### Idea
Check every cell in the matrix linearly.

### Algorithm
1. For each row `i` from 0 to M-1:
2.   For each column `j` from 0 to N-1:
3.     If `matrix[i][j] == target`: return `true`
4. Return `false`

### Complexity
- **Time:** O(M × N)
- **Space:** O(1)

### C++ Code
```cpp
// BRUTE FORCE: linear scan every cell
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    for (auto& row : matrix)
        for (int val : row)
            if (val == target) return true;
    return false;
}
```

---

## 🥈 Better Approach — Staircase Search

### Why Improve?
We can use the sorted-row property without full binary search.

### Idea
Start from the **top-right corner**. If `matrix[r][c] == target`, found. If `matrix[r][c] > target`, move left (`c--`). If `matrix[r][c] < target`, move down (`r++`).

### Complexity
- **Time:** O(M + N)
- **Space:** O(1)

### C++ Code
```cpp
// STAIRCASE: start top-right, eliminate row or column each step
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int r = 0, c = matrix[0].size() - 1;
    while (r < matrix.size() && c >= 0) {
        if (matrix[r][c] == target) return true;
        else if (matrix[r][c] > target) c--;
        else r++;
    }
    return false;
}
```

> **Note:** This staircase approach works for LC #240 (each row AND column sorted). For LC #74 (fully sorted row-by-row), binary search is strictly better.

---

## 🥇 Optimal Approach — Binary Search (Treat as 1D)

### Key Observation

> 💡 Since the matrix is globally sorted (row 0's last element < row 1's first element), we can treat the entire M×N matrix as a single sorted array of length M×N and binary search directly.
>
> **Mapping:** For any 1D index `mid`:
> - `row = mid / N`
> - `col = mid % N`

### Algorithm
1. `lo = 0`, `hi = M*N - 1`
2. While `lo <= hi`:
   - `mid = lo + (hi - lo) / 2`
   - `val = matrix[mid / N][mid % N]`
   - If `val == target`: return `true`
   - If `val < target`: `lo = mid + 1`
   - Else: `hi = mid - 1`
3. Return `false`

### Dry Run

**Input:** `matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]]`, `target = 3`  
M=3, N=4, hi=11

| lo | hi | mid | row=mid/4 | col=mid%4 | val | Action |
|----|-----|-----|-----------|-----------|-----|--------|
| 0 | 11 | 5 | 1 | 1 | 11 | 11>3 → hi=4 |
| 0 | 4 | 2 | 0 | 2 | 5 | 5>3 → hi=1 |
| 0 | 1 | 0 | 0 | 0 | 1 | 1<3 → lo=1 |
| 1 | 1 | 1 | 0 | 1 | 3 | **3==3 → true** ✅ |

### Complexity
- **Time:** O(log(M × N))
- **Space:** O(1)

### Why is this optimal?
We inspect O(log(MN)) cells instead of O(M+N). This is the tightest possible bound given that the matrix is globally sorted — each comparison eliminates half the remaining search space.

---

## 🎤 Interview Explanation Script

> "The brute force scans every cell in O(M×N). We can do better."

> "The key observation: because the first element of each row is greater than the last element of the previous row, the entire matrix is globally sorted. We can treat it as a single sorted array of M×N elements."

> "I binary search on the 1D index range [0, M×N-1]. For any index `mid`, the corresponding cell is `matrix[mid/N][mid%N]`. Standard binary search applies from there."

> "This gives O(log(M×N)) time — the best possible for a sorted search."

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * SEARCH IN 2D MATRIX (LeetCode #74)
 *
 * PROBLEM UNDERSTANDING:
 *   Matrix is globally sorted: last element of row i < first element of row i+1.
 *   This makes the entire matrix equivalent to one sorted 1D array.
 *
 * KEY OBSERVATION:
 *   Map 1D index mid → 2D position: row = mid/N, col = mid%N
 *
 * EDGE CASES:
 *   - Empty matrix or empty row: return false
 *   - Target smaller than matrix[0][0]: hi converges before lo, return false
 *   - Target larger than matrix[M-1][N-1]: same
 *
 * COMPLEXITY: Time O(log(M*N)) | Space O(1)
 */
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) return false;

        int m = matrix.size(), n = matrix[0].size();
        int lo = 0, hi = m * n - 1;

        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            int val = matrix[mid / n][mid % n];   // 1D index → 2D mapping

            if (val == target) return true;
            else if (val < target) lo = mid + 1;
            else hi = mid - 1;
        }

        return false;
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "Treat matrix as sorted 1D array. `val = matrix[mid/N][mid%N]`. Binary search on [0, M*N-1]."

---

## 📝 Short Revision Notes

- **Requires:** row[i+1][0] > row[i][N-1] (globally sorted) — not just each row sorted
- 1D→2D mapping: `row = mid / N`, `col = mid % N`
- `hi = M*N - 1` (not M*N)
- Staircase O(M+N) works for LC #240 (weaker guarantee); binary search O(log MN) is better for LC #74
- Always check `mid/n` not `mid/m` for column calculation

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "sorted matrix where each row's first > previous row's last"
- "2D search, globally ordered"

**I should think of:** Binary search with 1D-to-2D index mapping

---

## ⚠️ Common Mistakes

❌ Using `mid / M` instead of `mid / N` for row — M is rows, N is cols  
❌ `hi = M*N` instead of `M*N - 1` → accesses out-of-bounds  
❌ Applying this to LC #240 (only rows sorted) — that matrix is NOT globally sorted  
❌ Overflow: `M*N` when M=N=100 is only 10,000, fine for `int`

---

## 🔥 What Interviewer Is Testing

- **Concept:** Recognizing global sorted order in a 2D structure
- **Reasoning:** 1D index ↔ 2D coordinate mapping
- **Optimization:** Jumping from O(M+N) staircase to O(log MN) binary search

---

## 🚀 Alternative Approaches

| Approach | Time | Space | When to use |
|----------|------|-------|-------------|
| Binary search (1D mapping) | O(log MN) | O(1) | LC #74 — globally sorted |
| Staircase (top-right) | O(M+N) | O(1) | LC #240 — only rows/cols sorted |
| Brute force | O(MN) | O(1) | Never in interview |

---

## 📚 Related Problems

- [ ] LeetCode #74 — Search a 2D Matrix
- [ ] LeetCode #240 — Search a 2D Matrix II (use staircase instead)
- [ ] LeetCode #378 — Kth Smallest Element in Sorted Matrix
- [ ] Striver Step 3 P16 — Row with Maximum Number of 1s

---

## 🏆 Pattern Category

`Binary Search` · `Matrix` · `Index Mapping`

---

## 🎯 Difficulty Analysis

**Rating:** Medium

**Why challenging:** Recognizing that the matrix is globally sorted (not just row-wise) and making the 1D→2D index mapping cleanly are the two non-obvious steps.

---

## 📈 Progression Insight

**Harder variant:** LC #240 — matrix where only rows and columns are independently sorted. Binary search on full 1D doesn't work; must use staircase O(M+N) or binary search per row O(M log N).

**Even harder:** LC #378 — Kth smallest in sorted matrix → binary search on value with counting.

---

## ⏱️ 30-Second Last-Minute Revision

> **Problem:** Search target in globally-sorted M×N matrix  
> **Approach:** Binary search on [0, M*N-1]. `val = matrix[mid/N][mid%N]`.  
> **Key trick:** 1D→2D: `row = mid/N`, `col = mid%N`  
> **Time:** O(log MN) | **Space:** O(1)  
> **Watch out for:** `hi = M*N - 1`; row uses `/N` not `/M`
