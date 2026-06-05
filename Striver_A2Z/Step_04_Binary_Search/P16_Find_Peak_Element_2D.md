# 🔥 Find Peak Element in 2D Matrix

> **LeetCode #1901** · **Difficulty:** Hard · **Step 4 — Binary Search · P16**

---

## 🧠 Problem Understanding

**What is it asking?**
Given an M×N matrix where no two adjacent cells are equal, find any **peak element** — a cell that is strictly greater than all its neighbors (up, down, left, right). Return its `[row, col]`.

**Input:**
```
matrix = [[1, 4],
           [3, 2]]
```
**Output:** `[0, 1]` (value 4: neighbors are 1, 3, 2 — all smaller)

**Input:**
```
matrix = [[10, 20, 15],
           [21, 30, 14],
           [7,  16, 32]]
```
**Output:** `[1, 1]` (value 30 > 10,15,21,14 all neighbors) OR `[2, 2]` (value 32 > 14,16)

**Constraints:** `1 ≤ M, N ≤ 500`, no two adjacent cells equal, guaranteed peak exists

**Key Observations:**
- A peak always exists (proved by considering boundary values as `-∞`)
- Binary search on columns: for any mid column, find the row with the maximum value — this cell's neighbors in the column are smaller. Check left/right neighbors.
- If left neighbor is larger → peak is left. If right neighbor is larger → peak is right. Otherwise, this cell IS a peak.

---

## 🥉 Brute Force Approach

### Idea
Check every cell; return the first one that is greater than all neighbors.

### Algorithm
1. For each cell `(i, j)`:
   - Check all 4 neighbors
   - If all neighbors are smaller → return `{i, j}`

### Complexity
- **Time:** O(M × N) · **Space:** O(1)

---

## 🥇 Optimal Approach — Binary Search on Columns

### Key Observation

> 💡 For any column `mid`:
> 1. Find the row `maxRow` with the **maximum value** in column `mid`
> 2. Check `matrix[maxRow][mid-1]` (left neighbor) and `matrix[maxRow][mid+1]` (right neighbor)
> 3. If `matrix[maxRow][mid] > both neighbors` → **peak found** ✅
> 4. If left neighbor is larger → peak exists in the left half (a peak must exist by induction: the global max of that half must be a peak)
> 5. If right neighbor is larger → peak is in the right half

**Why does this work?**
The maximum of column `mid` is larger than all elements in its own column. The only way it's NOT a peak is if a horizontal neighbor is larger. That horizontal neighbor's column must have an even larger row-maximum (because of the maximality argument), and a peak must exist in that half.

### Algorithm
1. `lo = 0`, `hi = N - 1`
2. While `lo <= hi`:
   - `midCol = lo + (hi - lo) / 2`
   - Find `maxRow` = row with maximum value in column `midCol`
   - `left = matrix[maxRow][midCol-1]` (or -1 if out of bounds)
   - `right = matrix[maxRow][midCol+1]` (or -1 if out of bounds)
   - If `matrix[maxRow][midCol] > left && > right`: return `{maxRow, midCol}`
   - Else if `left > matrix[maxRow][midCol]`: `hi = midCol - 1` (peak left)
   - Else: `lo = midCol + 1` (peak right)

### Dry Run

**Input:**
```
[[10, 20, 15],
 [21, 30, 14],
 [ 7, 16, 32]]
```
lo=0, hi=2

**midCol=1:** Find max in col 1: [20, 30, 16] → maxRow=1 (value 30)
- left = matrix[1][0] = 21
- right = matrix[1][2] = 14
- 30 > 21 and 30 > 14 → **return {1, 1}** ✅

### Complexity
- **Time:** O(M log N) — O(M) to find max in column, O(log N) columns examined
- **Space:** O(1)

---

## 🎤 Interview Explanation Script

> "The brute force checks all M×N cells — too slow for large matrices."

> "The key insight: binary search on columns. For any column, the row with the maximum value is larger than all cells in that column. The only thing stopping it from being a peak is a larger horizontal neighbor."

> "If the left column has a larger value, then that column's maximum is even larger (it's at least as large as what we saw). By induction, a peak exists there. Same for the right column."

> "So I binary search on columns: find the column max's row, check horizontal neighbors, and move toward the larger neighbor. O(M log N) total."

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * FIND PEAK ELEMENT IN 2D MATRIX — binary search on columns
 *
 * PROBLEM UNDERSTANDING:
 *   Find any cell greater than all 4 neighbors.
 *
 * KEY OBSERVATION:
 *   For mid column, max-row cell dominates its column.
 *   Check horizontal neighbors. Move toward larger neighbor.
 *   Peak guaranteed to exist in that half.
 *
 * COMPLEXITY: Time O(M log N) | Space O(1)
 */
class Solution {
public:
    vector<int> findPeakGrid(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        int lo = 0, hi = n - 1;

        while (lo <= hi) {
            int midCol = lo + (hi - lo) / 2;

            // find row with maximum value in midCol
            int maxRow = 0;
            for (int r = 1; r < m; r++)
                if (mat[r][midCol] > mat[maxRow][midCol])
                    maxRow = r;

            int left  = (midCol > 0)     ? mat[maxRow][midCol - 1] : -1;
            int right = (midCol < n - 1) ? mat[maxRow][midCol + 1] : -1;

            if (mat[maxRow][midCol] > left && mat[maxRow][midCol] > right)
                return {maxRow, midCol};        // peak found
            else if (left > mat[maxRow][midCol])
                hi = midCol - 1;               // peak is in left half
            else
                lo = midCol + 1;               // peak is in right half
        }

        return {-1, -1};  // should never reach here (peak always exists)
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "BS on columns. For mid col: find max row. Check left/right. Peak found or move toward larger neighbor. O(M log N)."

---

## 📝 Short Revision Notes

- Binary search on columns (not rows) — find max in each candidate column
- Column max dominates vertically; only horizontal neighbors matter
- O(M) per column inspection × O(log N) columns = O(M log N)
- For row-oriented variant: BS on rows, find max in each row, check vertical neighbors

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "Find peak in 2D matrix"
- "Cell greater than all neighbors"
- "O(M log N) matrix search"

**I should think of:** Binary search on one dimension, find max in the other

---

## ⚠️ Common Mistakes

❌ Using O(M×N) brute force — misses the binary search opportunity  
❌ Using `-∞` as out-of-bounds instead of -1 or INT_MIN — be consistent  
❌ Moving toward smaller neighbor — always move toward the LARGER one  

---

## 🔥 What Interviewer Is Testing

- **Concept:** Applying binary search to a 2D structure
- **Reasoning:** Why moving toward the larger neighbor guarantees finding a peak

---

## 📚 Related Problems

- [ ] LeetCode #1901 — Find a Peak Element II
- [ ] LeetCode #162 — Find Peak Element (1D, P08)
- [ ] Striver Step 4 P08 — Find Peak Element (1D)

---

## 🏆 Pattern Category

`Binary Search` · `Matrix` · `Peak Finding`

---

## ⏱️ 30-Second Last-Minute Revision

> **Approach:** BS on columns. For mid col: find max row (O(M)). Check left/right neighbors. Peak or move toward larger. O(M log N)/O(1).
