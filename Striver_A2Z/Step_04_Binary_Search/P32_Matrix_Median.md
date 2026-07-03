# 🔥 Median of a Row-wise Sorted Matrix

> **Striver / GFG** · **Difficulty:** Hard · **Step 4 — Binary Search · P32**

---

## 🧠 Problem Understanding

**What is it asking?**
Given a matrix with an **odd** number of elements where **each row is sorted**, find the median of all `rows × cols` elements. (`rows*cols` is odd.)

**Input:**
```
[1, 3, 5]
[2, 6, 9]
[3, 6, 9]
```
→ **Output:** `5` (sorted: 1,2,3,3,5,6,6,9,9 → middle is 5)

**Key Observation:**
Don't flatten and sort (O(n·m·log)). **Binary search on the value range.** The median is the smallest value `x` such that at least `(total+1)/2` elements are `≤ x`. Counting "elements ≤ x" per sorted row is a fast `upper_bound`.

---

## 🎯 Interview Progression

### 🥉 Brute Force — Flatten & Sort

Copy all elements, sort, take the middle. **Time:** O(n·m·log(n·m)) · **Space:** O(n·m).

---

### 🥇 Optimal — Binary Search on the Value Range

> 💡 Search `[min(firstCol), max(lastCol)]`. For a candidate `mid`, count elements `≤ mid` across all rows via `upper_bound`. If the count is below the half-mark, the median is larger (`low = mid+1`); else `high = mid`. Converge to the median value.

```cpp
class Solution {
public:
    int countLessEqual(vector<int>& row,int mid){
        return upper_bound(row.begin(),row.end(),mid)-row.begin();
    }
    int findMedian(vector<vector<int>>& matrix){
        int rows=matrix.size();
        int cols=matrix[0].size();
        int low=matrix[0][0];
        int high=matrix[0][cols-1];
        for(int i=1;i<rows;i++){
            low=min(low,matrix[i][0]);
            high=max(high,matrix[i][cols-1]);
        }
        while(low<high){
            int mid=(low+high)/2;
            int count=0;
            for(int i=0;i<rows;i++){
                count+=countLessEqual(matrix[i],mid);
            }
            if(count<(rows*cols+1)/2)
                low=mid+1;
            else
                high=mid;
        }
        return low;
    }
};
```

**Time:** O(log(maxVal) · n · log m) · **Space:** O(1).

### Dry Run
Matrix above, `total = 9`, need count `≥ 5`. Range `[1, 9]`.

| low | high | mid | count(≤mid) | ≥5? | Action |
|-----|------|-----|-------------|-----|--------|
| 1 | 9 | 5 | 2+1+1... → 5 | ✅ | high=5 |
| 1 | 5 | 3 | 2+1+1 = 4 | ❌ | low=4 |
| 4 | 5 | 4 | 2+1+1 = 4 | ❌ | low=5 |
| 5 | 5 | — | — | — | low==high → **median = 5** ✅ |

---

## 🧾 Recall Line *(10-Second Revision)*

> "BS on value `[min(col0), max(lastCol)]`. count(≤mid) per row via upper_bound. `count < (n*m+1)/2` → `low=mid+1`, else `high=mid`. Return low."

---

## 📝 Short Revision Notes

- Binary search on the **value**, not on indices.
- `countLessEqual(row, mid) = upper_bound(row, mid)` — O(log m) per row.
- Half-mark: `(rows*cols + 1) / 2` (matrix has an odd element count).
- Search bounds: smallest first-column value to largest last-column value.
- Uses `low < high` with `high = mid` (no `-1`) so the median value isn't skipped.

---

## ⚠️ Common Mistakes

❌ Flattening and sorting (defeats the log-time goal).
❌ Counting `< mid` instead of `≤ mid` (`upper_bound`, not `lower_bound`).
❌ Wrong half-mark (must be `(n*m+1)/2`).

---

## 🧠 Pattern Recognition Trigger

**When I see:** "median of a row-wise sorted matrix without merging" → **binary search on value + count ≤ mid per row**.

---

## 🏆 Pattern Category

`Binary Search on Answer` · `Matrix` · `Counting`

---

## ⏱️ 30-Second Last-Minute Revision

> **BS on value range.** count(≤mid)=Σ upper_bound(row,mid). `count < (n*m+1)/2` → `low=mid+1`, else `high=mid`. Return `low`. `O(log(maxVal)·n·log m)`.
