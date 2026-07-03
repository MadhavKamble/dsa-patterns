# 🔥 Find Peak Element

> **LeetCode #162** · **Difficulty:** Medium · **Step 4 — Binary Search · P13**

---

## 🧠 Problem Understanding

**What is it asking?**
A peak element is **strictly greater than its neighbours**. Return the index of **any** peak. Assume `nums[-1] = nums[n] = -∞`, so the ends can be peaks.

**Input:** `nums = [1, 2, 3, 1]` → **Output:** `2` (value 3)
**Input:** `nums = [1, 2, 1, 3, 5, 6, 4]` → **Output:** `5` (or `1` — both valid)

**Edge cases:** single element (it's the peak); first or last element can be a peak; multiple peaks allowed.

**Key Observation:**
- On an **increasing** slope (`nums[mid] < nums[mid+1]`), a peak must exist to the **right**.
- On a **decreasing** slope (`nums[mid] > nums[mid+1]`), a peak exists at `mid` or to the **left**.
- Because the array rises then falls somewhere, a peak is guaranteed.

---

## 🎯 Interview Progression

### 🥉 Brute Force — Linear Scan

Return any `i` with `nums[i] > nums[i-1]` and `nums[i] > nums[i+1]`. **Time:** O(N).

---

### 🥇 Optimal — Binary Search on the Slope

> 💡 Compare `nums[mid]` with `nums[mid+1]`. If ascending, move right (`low = mid+1`); if descending, move left keeping `mid` (`high = mid`). We always walk uphill, so we converge to a peak.

```cpp
class Solution {
public:
    int findPeakElement(vector<int>& nums){
        int low=0,high=nums.size()-1;
        while(low<high){
            int mid=low+(high-low)/2;
            if(nums[mid]<nums[mid+1]){
                low=mid+1;
            }else{
                high=mid;
            }
        }
        return low;
    }
};
```

**Time:** O(log N) · **Space:** O(1).

### Dry Run
`nums = [1, 2, 1, 3, 5, 6, 4]`

| low | high | mid | nums[mid] | nums[mid+1] | Slope | Action |
|-----|------|-----|-----------|-------------|-------|--------|
| 0 | 6 | 3 | 3 | 5 | up | low=4 |
| 4 | 6 | 5 | 6 | 4 | down | high=5 |
| 4 | 5 | 4 | 5 | 6 | up | low=5 |
| 5 | 5 | — | — | — | — | low==high → **return 5** ✅ |

---

## 🧾 Recall Line *(10-Second Revision)*

> "`nums[mid]<nums[mid+1]` (uphill) → `low=mid+1`. Else `high=mid`. Return `low`. Use `low<high`."

---

## 📝 Short Revision Notes

- Use `low < high` (converge to a peak), with `high = mid` (mid stays a candidate).
- Comparing `mid` vs `mid+1` is enough — no need to look at `mid-1`.
- Works with the assumed `-∞` sentinels at both ends, so end elements can be peaks.
- Finds **any** peak, not necessarily the global maximum.

---

## ⚠️ Common Mistakes

❌ `low <= hi` → infinite loop (mid+1 can go out of bounds too).
❌ `low = mid` instead of `mid+1` → infinite loop when `high = low+1`.
❌ `high = mid-1` → may skip the actual peak.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "peak element", "greater than neighbours", "any local maximum in log time" → **binary search on the slope**.

---

## 🏆 Pattern Category

`Binary Search` · `Peak Finding`

---

## ⏱️ 30-Second Last-Minute Revision

> **Walk uphill.** `nums[mid]<nums[mid+1]` → go right; else `high=mid`. Return `low`. `O(log N)`.
