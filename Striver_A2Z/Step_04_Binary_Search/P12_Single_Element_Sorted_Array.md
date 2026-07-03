# 🔥 Single Element in a Sorted Array

> **LeetCode #540** · **Difficulty:** Medium · **Step 4 — Binary Search · P12**

---

## 🧠 Problem Understanding

**What is it asking?**
Every element appears **exactly twice** except one, which appears once. Find that single element in O(log N) time, O(1) space.

**Input:** `nums = [1, 1, 2, 3, 3, 4, 4, 8, 8]` → **Output:** `2`
**Input:** `nums = [3, 3, 7, 7, 10, 11, 11]` → **Output:** `10`

**Edge cases:** single element array; the unique element at the very start or end.

**Key Observation — index parity:**
- **Before** the single element, pairs start at **even** indices: `(0,1), (2,3), (4,5)...`
- **After** the single element, pairs start at **odd** indices: `(1,2), (3,4)...`

That break in the pattern is what we binary-search for.

---

## 🎯 Interview Progression

### 🥉 Brute Force — Frequency / Linear

Count frequencies (or scan checking neighbours) and return the one with count 1. **Time:** O(N).

### 🥈 Better — XOR

XOR of all elements cancels the pairs, leaving the single element. **Time:** O(N), **Space:** O(1) — but still linear, doesn't meet the O(log N) ask.

---

### 🥇 Optimal — Binary Search on Parity

> 💡 Force `mid` to an **even** index. If `nums[mid] == nums[mid+1]`, the pairing is still intact up to here → the single element is to the **right** (`low = mid+2`). Otherwise the pairing already broke → the single is at `mid` or to the **left** (`high = mid`).

```cpp
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums){
        int low=0,high=nums.size()-1;
        while(low<high){
            int mid=low+(high-low)/2;
            if(mid%2==1) mid--;
            if(nums[mid]==nums[mid+1]){
                low=mid+2;
            }else{
                high=mid;
            }
        }
        return nums[low];
    }
};
```

**Time:** O(log N) · **Space:** O(1).

### Dry Run
`nums = [1, 1, 2, 3, 3, 4, 4, 8, 8]` (indices 0–8)

| low | high | mid (even) | nums[mid] | nums[mid+1] | Equal? | Action |
|-----|------|-----------|-----------|-------------|--------|--------|
| 0 | 8 | 4 | 3 | 4 | ❌ | high=4 |
| 0 | 4 | 2 | 2 | 3 | ❌ | high=2 |
| 0 | 2 | 0 | 1 | 1 | ✅ | low=2 |
| 2 | 2 | — | — | — | — | low==high → **return nums[2]=2** ✅ |

---

## 🧾 Recall Line *(10-Second Revision)*

> "Make mid even. `nums[mid]==nums[mid+1]` (pair intact) → `low=mid+2`. Else `high=mid`. Return `nums[low]`."

---

## 📝 Short Revision Notes

- Force even mid: `if(mid%2==1) mid--`.
- `low = mid+2` skips the whole intact pair; `high = mid` keeps `mid` as a candidate.
- Pairs are even-indexed **before** the single element, odd-indexed **after**.
- XOR is simpler but O(N) — doesn't satisfy the log-time requirement.

---

## ⚠️ Common Mistakes

❌ Not normalizing `mid` to even → inconsistent pair comparison.
❌ `low = mid+1` instead of `mid+2` → doesn't skip the full pair.
❌ `high = mid-1` → may skip the single element.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "every element twice except one", "single element, O(log N)" → **binary search on index parity**.

---

## 🏆 Pattern Category

`Binary Search` · `Parity`

---

## ⏱️ 30-Second Last-Minute Revision

> **Even mid.** Pair intact (`nums[mid]==nums[mid+1]`) → go right `low=mid+2`; else `high=mid`. Return `nums[low]`. `O(log N)`.
