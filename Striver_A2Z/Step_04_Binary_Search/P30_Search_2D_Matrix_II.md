# 🔥 Search in a 2D Matrix II

> **LeetCode #240** · **Difficulty:** Medium · **Step 4 — Binary Search · P30**

---

## 🧠 Problem Understanding

**What is it asking?**
Search `target` in an `n × m` matrix where **each row is sorted left-to-right** and **each column is sorted top-to-bottom** — but it is **not** globally sorted (a row-start can be smaller than the previous row-end).

**Input:**
```
[ 1,  4,  7, 11, 15]
[ 2,  5,  8, 12, 19]
[ 3,  6,  9, 16, 22]
[10, 13, 14, 17, 24]
[18, 21, 23, 26, 30]
```
`target = 8` → **Output:** `true`

**Key Observation:**
Start at the **top-right corner**. That cell is the largest in its row and smallest in its column — so each comparison eliminates an entire row or column.

---

## 🎯 Interview Progression

### 🥉 Brute Force — Scan Everything

Check all cells. **Time:** O(n·m).

### 🥈 Better — Row-wise Binary Search

Binary search each row. **Time:** O(n · log m).

---

### 🥇 Optimal — Staircase Search from Top-Right

> 💡 From `(0, m-1)`: if the cell `> target`, move **left** (drop that column); if `< target`, move **down** (drop that row). Equal → found. Each step removes a full row or column.

```cpp
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix,int target){
        int n=matrix.size();
        int m=matrix[0].size();
        int row=0;
        int col=m-1;
        while(row<n && col>=0){
            if(matrix[row][col]==target){
                return true;
            }else if(matrix[row][col]<target){
                row++;
            }else{
                col--;
            }
        }
        return false;
    }
};
```

**Time:** O(n + m) · **Space:** O(1).

### Dry Run
`target = 8`, start at `(0, 4)` = 15

| row | col | value | vs 8 | Action |
|-----|-----|-------|------|--------|
| 0 | 4 | 15 | > | col-- |
| 0 | 3 | 11 | > | col-- |
| 0 | 2 | 7 | < | row++ |
| 1 | 2 | 8 | == | **true** ✅ |

---

## 🧾 Recall Line *(10-Second Revision)*

> "Start top-right. `>target` → left (col--), `<target` → down (row++). Each step kills a row/column. O(n+m)."

---

## 📝 Short Revision Notes

- Rows **and** columns sorted, but **not** globally → can't flatten (that's P29 / Matrix I).
- Top-right (or bottom-left) is the pivot corner where one comparison eliminates a line.
- O(n+m), O(1) space — better than O(n log m) row-wise search for this structure.
- Bottom-left works symmetrically: `<target` → right, `>target` → up.

---

## ⚠️ Common Mistakes

❌ Starting at top-left or bottom-right → can't decide which direction eliminates a line.
❌ Trying the flatten-to-1D trick (only valid for the globally-sorted Matrix I).
❌ Wrong bounds check (`row < n && col >= 0`).

---

## 🧠 Pattern Recognition Trigger

**When I see:** "rows sorted AND columns sorted, not globally" → **staircase search from a corner**.

---

## 🏆 Pattern Category

`Matrix` · `Staircase Search` · `Two Pointers`

---

## ⏱️ 30-Second Last-Minute Revision

> **Top-right start.** `>target` → col--, `<target` → row++, equal → found. `O(n+m)`. (Globally sorted → use Matrix I flatten instead.)
