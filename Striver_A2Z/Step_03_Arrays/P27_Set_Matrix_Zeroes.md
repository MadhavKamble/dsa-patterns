# 🔥 Set Matrix Zeroes

> **LeetCode #73** · **Difficulty:** Medium · **Step 3 — Arrays · P27**

---

## 🧠 Problem Understanding

Given an M×N matrix, if any cell is 0, set its entire row and column to 0. **Do it in-place.**

**Input:**
```
[[1,1,1],
 [1,0,1],
 [1,1,1]]
```
**Output:**
```
[[1,0,1],
 [0,0,0],
 [1,0,1]]
```

**Key Observation:** We can't set zeros while scanning (cascades). We must first mark which rows/cols need zeroing, then apply.

---

## 🥉 Brute Force
Use -1 as temporary marker; two passes. **Time:** O(M×N×(M+N))

## 🥈 Better — Extra Space
Store which rows/cols have zeros in boolean arrays. **Time:** O(M×N) · **Space:** O(M+N)

---

## 🥇 Optimal — Use First Row/Col as Markers

### Key Observation
> 💡 Use `matrix[0][j]` as marker for column `j`, and `matrix[i][0]` as marker for row `i`. Handle first row and first column separately (they share the `matrix[0][0]` cell).

### Algorithm
1. Check if first row has any 0 → `firstRowZero`
2. Check if first col has any 0 → `firstColZero`
3. For `i=1, j=1` to end: if `matrix[i][j]==0`, mark `matrix[i][0]=0` and `matrix[0][j]=0`
4. Apply zeros: for `i=1, j=1`: if `matrix[i][0]==0` OR `matrix[0][j]==0`, set `matrix[i][j]=0`
5. If `firstRowZero`: zero out first row
6. If `firstColZero`: zero out first col

### Dry Run
```
[[0,1,2,0],       firstRowZero=true (has 0)
 [3,4,5,2],       firstColZero=false
 [1,3,1,5]]
```
Step 3 markers: `matrix[0][0]=0` (from (0,0)), `matrix[0][3]=0` (from (0,3))

```
After step 4: [[0,1,2,0],[0,4,5,0],[0,3,1,0]]
After step 5 (first row zero): [[0,0,0,0],[0,4,5,0],[0,3,1,0]]
```
✅

### Complexity
- **Time:** O(M×N) · **Space:** O(1)

---

## 💻 Clean C++ Code

```cpp
/*
 * SET MATRIX ZEROES — use first row/col as markers
 *
 * TRICK: matrix[0][j] marks if col j needs zeroing
 *        matrix[i][0] marks if row i needs zeroing
 *        First row/col handled separately with boolean flags
 *
 * CRITICAL ORDER: apply markers before zeroing first row/col
 *   (else marker info is destroyed)
 *
 * Time O(M*N) | Space O(1)
 */
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        bool firstRowZero = false, firstColZero = false;

        // check if first row/col have any zeros
        for (int j = 0; j < n; j++) if (matrix[0][j] == 0) firstRowZero = true;
        for (int i = 0; i < m; i++) if (matrix[i][0] == 0) firstColZero = true;

        // use first row/col as markers for the rest
        for (int i = 1; i < m; i++)
            for (int j = 1; j < n; j++)
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }

        // apply markers to inner cells
        for (int i = 1; i < m; i++)
            for (int j = 1; j < n; j++)
                if (matrix[i][0] == 0 || matrix[0][j] == 0)
                    matrix[i][j] = 0;

        // zero out first row and col based on flags
        if (firstRowZero) for (int j = 0; j < n; j++) matrix[0][j] = 0;
        if (firstColZero) for (int i = 0; i < m; i++) matrix[i][0] = 0;
    }
};
```

---

## 🎤 Interview Explanation Script
> "Naive approach: when we see a 0, we mark the row and col with -1 temporarily, then convert -1s to 0s. But this is O(M×N×(M+N)) and uses sentinel values."

> "Better: store which rows and columns need zeroing in boolean arrays. O(M×N) time, O(M+N) space."

> "Optimal: use the first row and first column themselves as markers — they already exist in the matrix. I separately check if the first row and column originally had any zeros (using boolean flags), then use them as a marker space for the rest of the matrix."

> "Critical: I must apply the markers to inner cells BEFORE zeroing the first row/col. Otherwise I'd destroy the marker information."

---

## 🧾 Recall Line
> "First row/col = marker space. Check first row/col separately with flags. Mark → apply → zero first row/col."

## 📝 Short Revision Notes
- 4 passes total, all O(M×N)
- Order matters: mark → apply inner → zero first row/col
- `matrix[0][0]` is shared by first row and first column markers — handle with `firstColZero` flag
- Why separate flags? To not overwrite marker data needed for inner cells

## ⚠️ Common Mistakes
❌ Zeroing first row/col BEFORE applying markers → destroys marker data  
❌ Not handling `matrix[0][0]` collision between row 0 and col 0 markers  
❌ Setting zeros during the same scan (cascades wrongly)

## 🔥 What Interviewer Is Testing
- In-place space optimization using existing matrix storage
- Order of operations to avoid data corruption

## 📚 Related Problems
- [ ] LeetCode #73 — Set Matrix Zeroes
- [ ] LeetCode #74 — Search a 2D Matrix
- [ ] Striver P28 — Rotate Matrix

## 🏆 Pattern Category
`Arrays` · `Matrix` · `In-Place`

## ⏱️ 30-Second Revision
> Check first row/col for zeros (flags). Mark inner using first row/col. Apply inner. Zero first row/col using flags. O(MN)/O(1).
