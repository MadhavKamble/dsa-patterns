# 🔥 Search in 2D Matrix & Row with Max 1s

> **LeetCode #74 & #1074** · **Difficulty:** Easy-Medium · **Step 3 — P15 & P16**

---

# P15 — Search an Element in a 2D Matrix

## 🧠 Problem Understanding

Given an M×N matrix where each row is sorted and first element of each row > last element of previous row. Search for a target.

**Input:** `matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]]`, target=3 → **Output:** `true`

**Key Observation:** This matrix is essentially a sorted 1D array folded into 2D. Binary search on it directly.

---

## 🥉 Brute Force
Linear scan all elements. **Time:** O(M×N) · **Space:** O(1)

---

## 🥇 Optimal — Binary Search (Treat as 1D)

### Key Observation
> 💡 Map 1D index `mid` → 2D: `row = mid / N`, `col = mid % N`. Binary search on [0, M*N-1].

### Algorithm
1. `lo=0, hi=M*N-1`
2. While `lo <= hi`:
   - `mid = (lo+hi)/2`
   - `val = matrix[mid/N][mid%N]`
   - If `val == target`: return true
   - If `val < target`: `lo = mid+1`
   - Else: `hi = mid-1`
3. Return false

### Dry Run
`matrix` above, target=3. M=3, N=4, hi=11

| lo | hi | mid | val | Action |
|----|-----|-----|-----|--------|
| 0 | 11 | 5 | matrix[1][1]=11 | 11>3 → hi=4 |
| 0 | 4 | 2 | matrix[0][2]=5 | 5>3 → hi=1 |
| 0 | 1 | 0 | matrix[0][0]=1 | 1<3 → lo=1 |
| 1 | 1 | 1 | matrix[0][1]=3 | 3==3 → **true** |

**Time:** O(log(M×N)) · **Space:** O(1)

```cpp
/*
 * SEARCH 2D MATRIX — binary search treating matrix as sorted 1D array
 * Mapping: index i → row = i/N, col = i%N
 * Time O(log(M*N)) | Space O(1)
 */
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        int lo = 0, hi = m * n - 1;

        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            int val = matrix[mid / n][mid % n];   // 2D mapping

            if (val == target) return true;
            else if (val < target) lo = mid + 1;
            else hi = mid - 1;
        }
        return false;
    }
};
```

---

# P16 — Row with Maximum Number of 1s

## 🧠 Problem Understanding

Given a binary matrix (sorted rows), find the row with the maximum number of 1s.

**Input:**
```
[[0,1,1,1],
 [0,0,1,1],
 [1,1,1,1],
 [0,0,0,0]]
```
**Output:** Row 2 (0-indexed), count = 4

**Key Observation:** Each row is sorted → binary search for first 1 in each row. Or: staircase from top-right.

---

## 🥇 Optimal — Staircase from Top-Right

### Algorithm
1. Start at `(row=0, col=N-1)` — top-right corner
2. If `mat[row][col] == 1`: `col--` (try to go further left to get more 1s), update `maxRow = row`
3. If `mat[row][col] == 0`: `row++` (move down)
4. Repeat until `row==M` or `col<0`

### Dry Run
Matrix above, starting at (0, 3):

| row | col | val | Action |
|-----|-----|-----|--------|
| 0 | 3 | 1 | col-- → maxRow=0 |
| 0 | 2 | 1 | col-- → maxRow=0 |
| 0 | 1 | 1 | col-- → maxRow=0 |
| 0 | 0 | 0 | row++ |
| 1 | 0 | 0 | row++ |
| 2 | 0 | 1 | col-- → maxRow=2 |
| 2 | -1 | stop | |

**Output:** Row 2 ✅ **Time:** O(M+N) · **Space:** O(1)

```cpp
/*
 * ROW WITH MAX 1s — staircase from top-right corner
 * When 1: go left (more 1s possible), update maxRow
 * When 0: go down (this row can't beat current best starting from this col)
 * Time O(M+N) | Space O(1)
 */
class Solution {
public:
    int rowWithMax1s(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        int row = 0, col = n - 1;
        int maxRow = -1;

        while (row < m && col >= 0) {
            if (mat[row][col] == 1) {
                maxRow = row;    // this row has at least (n-col) ones
                col--;           // try to find more
            } else {
                row++;           // this row can't improve, move down
            }
        }
        return maxRow;
    }
};
```

---

## 🧾 Recall Lines
> **P15:** Binary search on `[0, M*N-1]`. Index `mid` → `row=mid/N, col=mid%N`.  
> **P16:** Staircase from top-right. 1→go left (update maxRow), 0→go down.

## 📝 Short Revision Notes
**P15:** Requires rows sorted AND row[i+1][0] > row[i][N-1] (full 2D ordering)  
**P16:** Only needs rows sorted. Staircase visits at most M+N cells.  
Both O(1) space.

## ⚠️ Common Mistakes
**P15:** Using M*N as hi (should be M*N-1)  
**P16:** Not updating maxRow inside the `1` branch

## 🏆 Pattern Category
`Arrays` · `Binary Search` · `Matrix` · `Two Pointers`

## ⏱️ 30-Second Revision
> P15: Treat matrix as 1D, binary search. `val = mat[mid/N][mid%N]`. O(log MN)/O(1).  
> P16: Start (0, N-1). 1→col--, update maxRow. 0→row++. O(M+N)/O(1).
