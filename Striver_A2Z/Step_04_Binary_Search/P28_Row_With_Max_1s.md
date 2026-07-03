# 🔥 Find the Row with Maximum Number of 1s

> **Striver / GFG** · **Difficulty:** Easy-Medium · **Step 4 — Binary Search · P28**

---

## 🧠 Problem Understanding

**What is it asking?**
Given a matrix where **each row is sorted** (all 0s then all 1s), find the index of the row with the **most 1s**. On ties, return the smallest index. Return `-1` if there are no 1s.

**Input:** `matrix = [[1,1,1],[0,0,1],[0,0,0]]` → **Output:** `0` (row 0 has three 1s)

**Key Observation:**
In a row of `0...01...1`, the count of 1s = `m - (index of first 1)`. The **first 1** is exactly the **lower bound of 1**. So each row is an O(log m) query instead of O(m).

---

## 🎯 Interview Progression

### 🥉 Brute Force — Count Every Cell

Scan all cells, count 1s per row, track the max. **Time:** O(n·m).

---

### 🥇 Optimal — Lower Bound per Row

> 💡 For each row, `lowerBound(1)` gives the first index holding a 1; then `ones = m - thatIndex`. Track the row with the maximum.

```cpp
class Solution {
public:
    int lowerBound(vector<int>& arr,int n,int x){
        int low=0,high=n-1;
        int ans=n;
        while(low<=high){
            int mid=(low+high)/2;
            if(arr[mid]>=x){
                ans=mid;
                high=mid-1;
            }else{
                low=mid+1;
            }
        }
        return ans;
    }
    int rowWithMax1s(vector<vector<int>>& matrix,int n,int m){
        int cnt_max=0;
        int index=-1;
        for(int i=0;i<n;i++){
            int cnt_ones=m-lowerBound(matrix[i],m,1);
            if(cnt_ones>cnt_max){
                cnt_max=cnt_ones;
                index=i;
            }
        }
        return index;
    }
};
```

**Time:** O(n · log m) · **Space:** O(1).

### Dry Run
`matrix = [[1,1,1],[0,0,1],[0,0,0]]`, `m = 3`

| Row | lowerBound(1) | ones = 3 - lb | cnt_max | index |
|-----|---------------|---------------|---------|-------|
| 0 | 0 | 3 | 3 | 0 |
| 1 | 2 | 1 | 3 | 0 |
| 2 | 3 (no 1) | 0 | 3 | 0 |

**Output:** `0` ✅

---

## 🧾 Recall Line *(10-Second Revision)*

> "Each row sorted 0s→1s. ones = `m - lowerBound(1)`. Track the row with the max. O(n log m)."

---

## 📝 Short Revision Notes

- Works only because each row is **sorted** (0s before 1s).
- `ones = m - lowerBound(row, 1)`; a row of all 0s gives `lowerBound = m` → 0 ones.
- Strict `>` when updating keeps the **smallest** index on ties.
- Beats the O(n·m) brute force by turning each row into an O(log m) query.

---

## ⚠️ Common Mistakes

❌ Applying this to unsorted rows.
❌ Using `>=` in the update → returns a later tied row instead of the earliest.
❌ Off-by-one: `ones = m - firstOneIndex`, not `m - 1 - firstOneIndex`.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "each row sorted", "row with most 1s / count of a value per row" → **lower bound per row**.

---

## 🏆 Pattern Category

`Binary Search` · `Matrix` · `Lower Bound`

---

## ⏱️ 30-Second Last-Minute Revision

> **Row sorted 0→1.** ones = `m - lowerBound(1)`. Max over rows, strict `>` for earliest tie. `O(n log m)`.
