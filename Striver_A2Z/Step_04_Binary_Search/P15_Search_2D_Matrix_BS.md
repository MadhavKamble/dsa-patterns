# 🔥 Search in a 2D Matrix (Binary Search)

> **LeetCode #74** · **Difficulty:** Medium · **Step 4 — Binary Search · P15**

*(Also covered in Step 3 P15 from the Arrays perspective. This entry focuses on the Binary Search interpretation.)*

---

## 🧠 Problem Understanding

Same as Step 3 P15 — the key here is recognizing it as a **Binary Search on a 1D-indexed structure**.

**Matrix properties:**
- Each row sorted ascending
- First element of row `i+1` > last element of row `i`
→ The entire matrix is globally sorted when read row by row

**Key insight for Step 4:** Map the M×N matrix to a 1D array of length M×N using the formula:  
`matrix[mid/N][mid%N]` for 1D index `mid`.

---

## 💻 Clean C++ Code

```cpp
/*
 * SEARCH IN 2D MATRIX — binary search on 1D index
 * Matrix is globally sorted → treat as sorted 1D array
 * Map: index mid → matrix[mid/N][mid%N]
 * Time O(log(M*N)) | Space O(1)
 */
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        int lo = 0, hi = m * n - 1;

        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            int val = matrix[mid / n][mid % n];

            if (val == target) return true;
            else if (val < target) lo = mid + 1;
            else hi = mid - 1;
        }
        return false;
    }
};
```

**Complexity:** Time O(log(M×N)) | Space O(1)

**Full detailed explanation:** See [Step_03_Arrays/P15_Search_in_2D_Matrix.md](../Step_03_Arrays/P15_Search_in_2D_Matrix.md)

---

## 🧾 Recall Line
> "Treat matrix as sorted 1D array. `val = matrix[mid/N][mid%N]`. BS on [0, M*N-1]."

## 🏆 Pattern Category
`Binary Search` · `Matrix` · `Index Mapping`
