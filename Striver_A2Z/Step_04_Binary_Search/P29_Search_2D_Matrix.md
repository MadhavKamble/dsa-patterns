# 🔥 Search in a 2D Matrix

> **LeetCode #74** · **Difficulty:** Medium · **Step 4 — Binary Search · P29**

---

## 🧠 Problem Understanding

**What is it asking?**
Search for `target` in an `n × m` matrix where:
- Each row is sorted left-to-right, and
- The first element of each row is greater than the last element of the previous row.

So the matrix is **globally sorted** if read row by row.

**Input:** `matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]`, `target = 8` → **Output:** `true`

**Key Observation:**
Treat the matrix as a **virtual 1D sorted array** of length `n*m`. Map a 1D index `mid` back to 2D with `row = mid / m`, `col = mid % m`, then do plain binary search.

---

## 🎯 Interview Progression

### 🥉 Brute Force — Scan Everything

Check all `n*m` cells. **Time:** O(n·m).

### 🥈 Better — Row-wise Binary Search

Find the candidate row (by range), binary-search within it. **Time:** O(n + log m) or O(n·log m).

---

### 🥇 Optimal — Binary Search on the Flattened Index

> 💡 One binary search over `[0, n*m - 1]`. Convert `mid` to `matrix[mid/m][mid%m]` and compare with `target`.

```cpp
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix,int target){
        int n=matrix.size();
        int m=matrix[0].size();
        int low=0,high=n*m-1;
        while(low<=high){
            int mid=(low+high)/2;
            int row=mid/m;
            int col=mid%m;
            if(matrix[row][col]==target) return true;
            else if(matrix[row][col]<target) low=mid+1;
            else high=mid-1;
        }
        return false;
    }
};
```

**Time:** O(log(n·m)) · **Space:** O(1).

### Dry Run
`matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]`, `target = 8`, `m = 4`, search `[0, 11]`

| low | high | mid | row=mid/4 | col=mid%4 | value | Action |
|-----|------|-----|-----------|-----------|-------|--------|
| 0 | 11 | 5 | 1 | 1 | 6 | 6<8 → low=6 |
| 6 | 11 | 8 | 2 | 0 | 9 | 9>8 → high=7 |
| 6 | 7 | 6 | 1 | 2 | 7 | 7<8 → low=7 |
| 7 | 7 | 7 | 1 | 3 | 8 | ==8 → **true** ✅ |

---

## 🧾 Recall Line *(10-Second Revision)*

> "Flatten to 1D. BS on `[0, n*m-1]`, `value = matrix[mid/m][mid%m]`. Standard binary search."

---

## 📝 Short Revision Notes

- Only valid when the matrix is **globally sorted** (row-start > previous row-end).
- Index mapping: `row = mid / m`, `col = mid % m` (divide/mod by **column count**).
- Single O(log(n·m)) search — same as searching a sorted array of size `n·m`.
- Different from "Search a 2D Matrix II" (rows & columns sorted but not globally) — that uses the staircase O(n+m) method.

---

## ⚠️ Common Mistakes

❌ Dividing/modding by `n` (rows) instead of `m` (columns).
❌ Applying this flatten trick when the matrix isn't globally sorted (that's Matrix II).
❌ `high = n*m` instead of `n*m - 1`.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "sorted matrix, each row-start > previous row-end", "search target" → **flatten to 1D binary search**.

---

## 🏆 Pattern Category

`Binary Search` · `Matrix` · `Index Mapping`

---

## ⏱️ 30-Second Last-Minute Revision

> **Flatten `n×m` → 1D.** BS `[0, n*m-1]`, `matrix[mid/m][mid%m]`. `O(log(n·m))`. (Globally sorted only — else use Matrix II staircase.)
