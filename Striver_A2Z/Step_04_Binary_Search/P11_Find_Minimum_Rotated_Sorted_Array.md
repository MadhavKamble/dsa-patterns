# 🔥 Find Minimum in Rotated Sorted Array

> **LeetCode #153** · **Difficulty:** Medium · **Step 4 — Binary Search · P11**

---

## 🧠 Problem Understanding

**What is it asking?**
Given a sorted array rotated at some pivot, find the **minimum element**. All elements are distinct. O(log N) required.

**Input:** `nums = [3, 4, 5, 1, 2]` → **Output:** `1`
**Input:** `nums = [4, 5, 6, 7, 0, 1, 2]` → **Output:** `0`
**Input:** `nums = [11, 13, 15, 17]` (not rotated) → **Output:** `11`

**Constraints:** O(log N), all distinct elements

**Key Observations:**
- Minimum is at the **rotation point** — where the array "resets" from large to small
- In a fully sorted (non-rotated) array, minimum is `arr[0]`
- Binary search: if `arr[mid] > arr[hi]`, the minimum is to the right of mid. Otherwise it's at or to the left.

**Simple Example:**
```
[4, 5, 6, 7, 0, 1, 2]
           ↑ rotation point (minimum is here)

arr[mid]=7 > arr[hi]=2 → minimum is RIGHT of mid (lo = mid+1)
```

---

## 🥉 Brute Force Approach

### Idea
Linear scan, find the minimum.

```cpp
int findMin(vector<int>& nums) {
    return *min_element(nums.begin(), nums.end());
}
// Time O(N), Space O(1)
```

---

## 🥇 Optimal Approach — Binary Search

### Key Observation

> 💡 Compare `arr[mid]` with `arr[hi]`:
>
> - If `arr[mid] > arr[hi]`: The minimum is in the **right half** (rotation is right of mid). `lo = mid + 1`
> - If `arr[mid] < arr[hi]`: The minimum is at **mid or to the left**. `hi = mid`
>
> When `lo == hi`, we've found the minimum.

**Why compare with `arr[hi]` (not `arr[lo]`)?**
Comparing with `arr[lo]` is trickier: if `arr[lo] < arr[mid]`, the left half is sorted but minimum could be `arr[lo]` itself OR in the right half. Using `arr[hi]` gives a cleaner invariant.

### Algorithm
1. `lo = 0`, `hi = N - 1`
2. While `lo < hi`:
   - `mid = lo + (hi - lo) / 2`
   - If `arr[mid] > arr[hi]`: `lo = mid + 1`
   - Else: `hi = mid`
3. Return `arr[lo]`

### Dry Run

**Input:** `arr = [4, 5, 6, 7, 0, 1, 2]`

| lo | hi | mid | arr[mid] | arr[hi] | arr[mid]>arr[hi]? | Action |
|----|-----|-----|----------|---------|-------------------|--------|
| 0 | 6 | 3 | 7 | 2 | ✅ | lo = 4 |
| 4 | 6 | 5 | 1 | 2 | ❌ | hi = 5 |
| 4 | 5 | 4 | 0 | 1 | ❌ | hi = 4 |
| lo=4==hi=4 → **return arr[4] = 0** ✅ |

**Input:** `arr = [11, 13, 15, 17]` (not rotated)

| lo | hi | mid | arr[mid] | arr[hi] | Action |
|----|-----|-----|----------|---------|--------|
| 0 | 3 | 1 | 13 | 17 | ❌ hi=1 |
| 0 | 1 | 0 | 11 | 13 | ❌ hi=0 |
| lo=0==hi=0 → **return arr[0] = 11** ✅ |

### Complexity
- **Time:** O(log N) · **Space:** O(1)

### Why `lo < hi` (not `lo <= hi`)?

We converge to the minimum index. When `lo == hi`, we've narrowed to a single element — that's the answer. Using `lo <= hi` would try to continue past that.

---

## 🎤 Interview Explanation Script

> "I binary search by comparing `arr[mid]` with `arr[hi]`. If `arr[mid] > arr[hi]`, the rotation (and minimum) is somewhere to the right of mid — so `lo = mid + 1`. Otherwise, mid could be the minimum or the minimum is to its left — `hi = mid`."

> "I use `lo < hi` as the loop condition. When `lo == hi`, we've pinpointed the minimum. Using `arr[hi]` as the reference is cleaner than `arr[lo]` because it avoids ambiguity when mid equals lo."

> "For a non-rotated array, `arr[mid] < arr[hi]` always → hi keeps shrinking → converges to index 0 (arr[0] is the minimum). Correct."

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * FIND MINIMUM IN ROTATED SORTED ARRAY
 *
 * PROBLEM UNDERSTANDING:
 *   Sorted array rotated at unknown pivot. Find minimum element.
 *
 * KEY OBSERVATION:
 *   Compare arr[mid] with arr[hi]:
 *   arr[mid] > arr[hi] → rotation/min is RIGHT of mid → lo = mid+1
 *   arr[mid] < arr[hi] → min is at mid or LEFT → hi = mid
 *
 * LOOP: lo < hi (converge to minimum index, not lo <= hi)
 *
 * COMPLEXITY: Time O(log N) | Space O(1)
 */
class Solution {
public:
    int findMin(vector<int>& nums) {
        int lo = 0, hi = nums.size() - 1;

        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;

            if (nums[mid] > nums[hi])
                lo = mid + 1;   // min is in right half (rotation point is right)
            else
                hi = mid;       // min is at mid or left (mid could be the minimum)
        }

        return nums[lo];        // lo == hi → minimum element
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "`arr[mid]>arr[hi]` → min is right, `lo=mid+1`. Else `hi=mid`. Use `lo<hi`. Return `arr[lo]`."

---

## 📝 Short Revision Notes

- Compare `arr[mid]` with `arr[hi]` (not `arr[lo]`)
- `lo < hi` loop (converge to minimum, not `lo <= hi`)
- `arr[mid] > arr[hi]` → minimum is strictly RIGHT → `lo = mid+1` (mid is not min)
- `arr[mid] < arr[hi]` → minimum is at mid or left → `hi = mid` (mid COULD be min)
- Non-rotated: `arr[mid] < arr[hi]` always → hi converges to 0 correctly
- For duplicates (LC #154): when `arr[mid] == arr[hi]`, just `hi--` (can't tell which side)

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "Find minimum in rotated sorted array"
- "Rotation point", "number of rotations"
- "Binary search, partially sorted"

**I should think of:** Compare `arr[mid]` with `arr[hi]`, converge with `lo < hi`

---

## ⚠️ Common Mistakes

❌ `lo <= hi` loop condition → tries to continue when lo==hi, may skip the answer  
❌ `lo = mid` instead of `lo = mid+1` → infinite loop when hi=lo+1 and arr[mid]>arr[hi]  
❌ Comparing `arr[mid]` with `arr[lo]` → trickier invariant, more edge cases  
❌ Not handling non-rotated array specially — the algorithm handles it naturally  

---

## 🔥 What Interviewer Is Testing

- **Concept:** Rotation point as the minimum location
- **Reasoning:** Why compare with `arr[hi]` gives cleaner logic
- **Detail:** `lo < hi` vs `lo <= hi`, `hi = mid` vs `hi = mid - 1`

---

## 🚀 Alternative Approaches

| Approach | Time | Space | Notes |
|----------|------|-------|-------|
| Compare with arr[hi] | O(log N) | O(1) | Cleanest |
| Compare with arr[lo] | O(log N) | O(1) | Trickier but valid |
| Linear scan | O(N) | O(1) | Too slow |

---

## 📚 Related Problems

- [ ] LeetCode #153 — Find Minimum in Rotated Sorted Array
- [ ] LeetCode #154 — Find Minimum in Rotated Sorted Array II (duplicates)
- [ ] Striver Step 4 P09 — Search in Rotated Sorted Array
- [ ] Striver Step 4 P14 — Count Rotations (index of minimum = rotation count)

---

## 🏆 Pattern Category

`Binary Search` · `Rotated Array`

---

## 🎯 Difficulty Analysis

**Rating:** Medium

**Why challenging:** The choice of comparing with `arr[hi]` vs `arr[lo]` and the `lo < hi` loop condition require careful reasoning. Common to get an off-by-one or infinite loop.

---

## ⏱️ 30-Second Last-Minute Revision

> **Problem:** Find minimum in rotated sorted array  
> **Approach:** `lo<hi`. `arr[mid]>arr[hi]` → `lo=mid+1`. Else `hi=mid`. Return `arr[lo]`.  
> **Key trick:** Compare with `arr[hi]`, not `arr[lo]`; use `hi=mid` not `hi=mid-1`  
> **Time:** O(log N) | **Space:** O(1)
