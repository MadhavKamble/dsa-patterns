# 🔥 Binary Search on 2D Arrays (P15–P17)

> **LeetCode #74, #162, #1** · **Difficulty:** Medium-Hard · **Step 4 — P15–P17**

---

# P15 — Search in a 2D Matrix

*(Already covered in Step 3 P15 — see [Step_03_Arrays/P15_P16_Search_2D_Matrix_MaxOnes_Row.md])*

**Quick recap:** Binary search on `[0, M*N-1]`, mapping `mid → (mid/N, mid%N)`.  
**Time:** O(log(M×N)) · **Space:** O(1)

---

# P16 — Find Peak Element in 2D Matrix

> **LeetCode #1901**

## 🧠 Problem Understanding

Find any peak element in an M×N matrix where a peak is strictly greater than its neighbors (up/down/left/right). Return its row/col index.

**Key Observation:** Binary search on **columns**. For each mid column, find the row with the maximum element. Check if it's a peak. If left neighbor is bigger, go left. If right neighbor is bigger, go right.

```cpp
/*
 * 2D PEAK ELEMENT — binary search on columns
 * For mid column: find row with max → check left/right neighbors
 * Time O(M log N) | Space O(1)
 */
class Solution {
public:
    vector<int> findPeakGrid(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        int lo = 0, hi = n - 1;

        while (lo <= hi) {
            int midCol = lo + (hi - lo) / 2;

            // find row with max in midCol
            int maxRow = 0;
            for (int r = 0; r < m; r++)
                if (mat[r][midCol] > mat[maxRow][midCol])
                    maxRow = r;

            int left  = (midCol > 0)   ? mat[maxRow][midCol-1] : -1;
            int right = (midCol < n-1) ? mat[maxRow][midCol+1] : -1;

            if (mat[maxRow][midCol] > left && mat[maxRow][midCol] > right)
                return {maxRow, midCol};         // peak found
            else if (left > mat[maxRow][midCol])
                hi = midCol - 1;                 // peak is left
            else
                lo = midCol + 1;                 // peak is right
        }
        return {-1, -1};
    }
};
// Time O(M log N) | Space O(1)
```

---

# P17 — Matrix Median

> **GFG Classic**

## 🧠 Problem Understanding

Given an M×N matrix where each row is sorted, find the **overall median**. M×N is always odd.

**Key Observation:** The median is the smallest number `x` such that at least `(M*N+1)/2` elements are ≤ `x`. Binary search on the value `x`, count elements ≤ `x` using upper bound on each row.

```cpp
/*
 * MATRIX MEDIAN — binary search on answer value
 * count(x) = total elements <= x using upper_bound on each row
 * Find smallest x where count(x) >= (M*N+1)/2
 * Time O(M * log(max_val) * log(N)) | Space O(1)
 */
class Solution {
public:
    int matrixMedian(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        int desired = (m * n + 1) / 2;

        // binary search on value range
        int lo = 1, hi = 1e9;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;

            // count elements <= mid across all rows
            int count = 0;
            for (auto& row : mat)
                count += upper_bound(row.begin(), row.end(), mid) - row.begin();

            if (count < desired) lo = mid + 1;
            else hi = mid;
        }
        return lo;
    }
};
```

---

## 🧾 Recall Lines
> **P15:** Binary search on 1D index → 2D mapping `mid/N, mid%N`.  
> **P16:** Binary search on columns, find max row in mid column, compare left/right.  
> **P17:** Binary search on value. Count ≤ mid using `upper_bound` per row. Find first with count ≥ (MN+1)/2.

## 📝 Short Revision Notes
- P15: Requires full 2D sorted order (row[i+1][0] > row[i][N-1])
- P16: O(M log N) — works even if matrix not fully sorted
- P17: Binary search on answer space — classic "binary search on value" pattern

## 🏆 Pattern Category
`Binary Search` · `2D Matrix` · `Search Space`

## ⏱️ 30-Second Revision
> P15: 1D BS, `mat[mid/n][mid%n]`. P16: BS on cols, max row in mid col, check neighbors. P17: BS on value, count ≤ mid with upper_bound per row.
