# 🔥 Find Peak Element

> **LeetCode #162** · **Difficulty:** Medium · **Step 4 — Binary Search · P08**

---

## 🧠 Problem Understanding

A peak element is one that is **strictly greater than its neighbors**. Find any peak index. Array may have multiple peaks. `nums[-1] = nums[n] = -∞`.

**Input:** `[1,2,3,1]` → **Output:** `2` (index of value 3)  
**Input:** `[1,2,1,3,5,6,4]` → **Output:** `1` or `5` (both are valid peaks)

**Key Observation:** Binary search works because: if `arr[mid] < arr[mid+1]`, a peak exists in the right half (mid+1..n-1). If `arr[mid] > arr[mid+1]`, a peak exists in the left half (0..mid).

---

## 🥉 Brute Force
Linear scan, return first element greater than both neighbors. **Time:** O(N)

---

## 🥇 Optimal — Binary Search O(log N)

### Key Observation
> 💡 **If `arr[mid] < arr[mid+1]`:** The right side is ascending — a peak must exist there (either mid+1 itself or further right).  
> **If `arr[mid] > arr[mid+1]`:** A peak exists on the left including mid.

### Algorithm
1. `lo=0, hi=n-1`
2. While `lo < hi`:
   - `mid = lo + (hi-lo)/2`
   - If `arr[mid] < arr[mid+1]`: `lo = mid+1` (peak is right)
   - Else: `hi = mid` (peak is left, mid itself is candidate)
3. Return `lo`

### Dry Run
`arr = [1,2,1,3,5,6,4]`

| lo | hi | mid | arr[mid] | arr[mid+1] | Action |
|----|-----|-----|----------|------------|--------|
| 0 | 6 | 3 | 3 | 5 | 3<5 → lo=4 |
| 4 | 6 | 5 | 6 | 4 | 6>4 → hi=5 |
| 4 | 5 | 4 | 5 | 6 | 5<6 → lo=5 |
| 5 | 5 | — | — | — | lo==hi → return 5 |

**Answer:** index 5 (value 6) ✅

### Complexity
- **Time:** O(log N) · **Space:** O(1)

---

## 💻 Clean C++ Code

```cpp
/*
 * FIND PEAK ELEMENT — binary search
 *
 * KEY: arr[mid] < arr[mid+1] → peak is RIGHT of mid (right side ascending)
 *      arr[mid] > arr[mid+1] → peak is LEFT including mid (mid could be peak)
 *
 * LOOP: lo < hi (not lo <= hi) — we converge to the peak index
 *
 * Time O(log N) | Space O(1)
 */
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int lo = 0, hi = nums.size() - 1;

        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;

            if (nums[mid] < nums[mid + 1])
                lo = mid + 1;       // ascending slope → peak is right
            else
                hi = mid;           // descending slope → peak is left (or mid)
        }

        return lo;                  // lo == hi → peak index
    }
};
```

---

## 🎤 Interview Explanation Script
> "The key insight is that a peak must always exist somewhere in the array. If `arr[mid] < arr[mid+1]`, the array is ascending at `mid` — so a peak exists somewhere to the right. If `arr[mid] > arr[mid+1]`, the array is descending — a peak exists at or to the left of `mid`. Binary search converges to a peak."

---

## 🧾 Recall Line
> "`arr[mid] < arr[mid+1]` → peak right (lo=mid+1). Else peak left (hi=mid). Use `lo < hi`."

## 📝 Short Revision Notes
- Use `lo < hi` (converge), not `lo <= hi` (exit on found)
- No need to check `arr[mid-1]` — the two-way decision on `mid` vs `mid+1` is sufficient
- Works for arrays with multiple peaks — finds any valid one
- Edge cases: single element → peak is that element; sorted ascending → last element is peak

## ⚠️ Common Mistakes
❌ `lo <= hi` instead of `lo < hi` → infinite loop  
❌ `lo = mid` instead of `lo = mid+1` → infinite loop when hi = lo+1  
❌ `hi = mid-1` instead of `hi = mid` → may skip the actual peak

## 🔥 What Interviewer Is Testing
- Non-obvious binary search application (no explicit target)
- Why the binary decision on slope guarantees a peak exists in chosen half

## 📚 Related Problems
- [ ] LeetCode #162 — Find Peak Element
- [ ] LeetCode #1095 — Find in Mountain Array
- [ ] GFG — Peak element in mountain array

## 🏆 Pattern Category
`Binary Search` · `Peak Finding`

## ⏱️ 30-Second Revision
> `lo=0, hi=n-1`. While `lo<hi`: if `arr[mid]<arr[mid+1]` → `lo=mid+1`, else `hi=mid`. Return lo.
