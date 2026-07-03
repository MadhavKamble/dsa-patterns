# 🔥 Find a Peak Element in a 2D Grid

> **LeetCode #1901** · **Difficulty:** Medium · **Step 4 — Binary Search · P31**

---

## 🧠 Problem Understanding

**What is it asking?**
Find **any** peak in a grid — a cell strictly greater than its **up, down, left, right** neighbours. Out-of-grid neighbours count as `-∞`. Return its `[row, col]`.

**Input:**
```
[4, 2, 5, 1, 4, 5]
[2, 9, 3, 2, 3, 2]
[1, 7, 6, 0, 1, 3]
[3, 6, 2, 3, 7, 2]
```
→ **Output:** one valid peak, e.g. `[1, 1]` (value 9).

**Key Observation:**
Binary search on **columns**. For a middle column, take the row of its **maximum** element — that element already dominates its column, so only its left/right neighbours matter. Move toward the larger horizontal neighbour; a peak is guaranteed in that direction.

---

## 🎯 Interview Progression

### 🥉 Brute Force — Check Every Cell

Test all `n·m` cells against 4 neighbours. **Time:** O(n·m).

---

### 🥇 Optimal — Binary Search on Columns

> 💡 In the mid column, find the row with the max value. If it's greater than both horizontal neighbours → peak. If the left neighbour is bigger, a peak lies to the **left**; else to the **right**.

```cpp
class Solution {
public:
    int maxElement(vector<vector<int>>& arr,int col){
        int n=arr.size();
        int max_val=INT_MIN;
        int index=-1;
        for(int i=0;i<n;i++){
            if(arr[i][col]>max_val){
                max_val=arr[i][col];
                index=i;
            }
        }
        return index;
    }
    vector<int> findPeakGrid(vector<vector<int>>& arr){
        int n=arr.size();
        int m=arr[0].size();
        int low=0;
        int high=m-1;
        while(low<=high){
            int mid=(low+high)/2;
            int row=maxElement(arr,mid);
            int left=mid-1>=0?arr[row][mid-1]:INT_MIN;
            int right=mid+1<m?arr[row][mid+1]:INT_MIN;
            if(arr[row][mid]>left && arr[row][mid]>right){
                return {row,mid};
            }else if(left>arr[row][mid]){
                high=mid-1;
            }else{
                low=mid+1;
            }
        }
        return {-1,-1};
    }
};
```

**Time:** O(n · log m) · **Space:** O(1).

### Dry Run (intuition)
Search columns `[0, 5]`. At `mid = 2`, the column max is `6` at row 2; its left neighbour `7 > 6`, so a peak is to the **left** → `high = 1`. Continue until the column-max dominates both sides → return that `[row, col]`.

---

## 🧾 Recall Line *(10-Second Revision)*

> "BS on columns. In mid column, take the max-row. Bigger than L & R → peak. Else move toward the bigger of L/R."

---

## 📝 Short Revision Notes

- Take the **maximum** in the mid column so the vertical neighbours are automatically ≤ it — only left/right remain to check.
- Move toward the larger horizontal neighbour; monotonic climb guarantees a peak.
- O(n log m): each of `log m` columns costs an O(n) column scan.
- Out-of-grid neighbours are `-∞`, so border cells can be peaks.

---

## ⚠️ Common Mistakes

❌ Comparing against only one horizontal neighbour.
❌ Not picking the column **max** (then vertical neighbours aren't guaranteed smaller).
❌ `low <= high` vs boundary handling of `left`/`right` sentinels.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "2D peak element", "greater than 4 neighbours, any peak" → **binary search on columns using the column max**.

---

## 🏆 Pattern Category

`Binary Search` · `Matrix` · `Peak Finding`

---

## ⏱️ 30-Second Last-Minute Revision

> **BS on columns.** Max element of mid column: > both horizontal neighbours → peak; else go toward the bigger side. `O(n log m)`.
