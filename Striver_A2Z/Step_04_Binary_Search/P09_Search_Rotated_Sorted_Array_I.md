# 🔥 Search in Rotated Sorted Array I (No Duplicates)

> **LeetCode #33** · **Difficulty:** Medium · **Step 4 — Binary Search · P09**

---

## 🧠 Problem Understanding

**What is it asking?**
A sorted array has been rotated at some unknown pivot. Given a target, find its index. Return -1 if not found. All elements are **distinct**.

**Input:** `nums = [4, 5, 6, 7, 0, 1, 2]`, `target = 0` → **Output:** `4`
**Input:** `nums = [4, 5, 6, 7, 0, 1, 2]`, `target = 3` → **Output:** `-1`
**Input:** `nums = [1]`, `target = 0` → **Output:** `-1`

**Constraints:** O(log N) required, no duplicates.

**Key Observations:**
- A rotated sorted array always has **at least one sorted half** around any midpoint
- If `arr[lo] <= arr[mid]`: left half `[lo..mid]` is sorted
- Else: right half `[mid..hi]` is sorted
- Once we know which half is sorted, we can check if target lies in it

**Simple Example:**
```
[4, 5, 6, 7, 0, 1, 2]
           ↑ mid=3 (value=7)

arr[0]=4 <= arr[3]=7 → left half [4,5,6,7] is sorted
target=0: 0 not in [4,7] → search right half [0,1,2]
```

---

## 🥉 Brute Force Approach

### Idea
Linear scan the entire array.

### Complexity
- **Time:** O(N) · **Space:** O(1)

---

## 🥇 Optimal Approach — Modified Binary Search

### Key Observation

> 💡 In any rotated sorted array with distinct elements, when we pick `mid`:
>
> **Case 1:** `arr[lo] <= arr[mid]` → **left half is sorted**
> - If `arr[lo] <= target < arr[mid]`: target is in left half → `hi = mid - 1`
> - Else: target is in right half → `lo = mid + 1`
>
> **Case 2:** `arr[mid] < arr[lo]` → **right half is sorted**
> - If `arr[mid] < target <= arr[hi]`: target is in right half → `lo = mid + 1`
> - Else: target is in left half → `hi = mid - 1`

### Algorithm
1. `lo = 0`, `hi = N - 1`
2. While `lo <= hi`:
   - `mid = lo + (hi - lo) / 2`
   - If `arr[mid] == target`: return `mid`
   - If `arr[lo] <= arr[mid]` (left half sorted):
     - If `arr[lo] <= target < arr[mid]`: `hi = mid - 1`
     - Else: `lo = mid + 1`
   - Else (right half sorted):
     - If `arr[mid] < target <= arr[hi]`: `lo = mid + 1`
     - Else: `hi = mid - 1`
3. Return `-1`

### Dry Run

**Input:** `arr = [4, 5, 6, 7, 0, 1, 2]`, `target = 0`

| lo | hi | mid | arr[mid] | Left sorted? | Target range check | Action |
|----|-----|-----|----------|--------------|-------------------|--------|
| 0 | 6 | 3 | 7 | arr[0]=4≤7 ✅ | 0 in [4,7)? ❌ | lo=4 |
| 4 | 6 | 5 | 1 | arr[4]=0≤1 ✅ | 0 in [0,1)? ✅ | hi=4 |
| 4 | 4 | 4 | 0 | — | arr[4]==0 == target | **return 4** ✅ |

**Input:** `arr = [4, 5, 6, 7, 0, 1, 2]`, `target = 3`

| lo | hi | mid | arr[mid] | Left sorted? | Check | Action |
|----|-----|-----|----------|--------------|-------|--------|
| 0 | 6 | 3 | 7 | ✅ | 3 in [4,7)? ❌ | lo=4 |
| 4 | 6 | 5 | 1 | arr[4]=0≤1 ✅ | 3 in [0,1)? ❌ | hi=4 |
| 4 | 4 | 4 | 0 | arr[4]=0≤0 ✅ | 3 in [0,0)? ❌ | lo=5 |
| lo=5 > hi=4 → **return -1** ✅ |

### Complexity
- **Time:** O(log N) · **Space:** O(1)

### Why is this optimal?
Each iteration eliminates exactly half the remaining search space — same as standard binary search. O(log N) is the best possible for search in a sorted structure.

---

## 🎤 Interview Explanation Script

> "In a rotated sorted array, standard binary search doesn't work directly because the array isn't globally sorted. But the key insight is: at any midpoint, **at least one half is always sorted**."

> "If `arr[lo] <= arr[mid]`, the left half is sorted. I check whether the target lies in that sorted range. If yes, search left; otherwise search right. Similar logic when the right half is sorted."

> "This guarantees we eliminate half the search space each step, maintaining O(log N) time."

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * SEARCH IN ROTATED SORTED ARRAY (no duplicates)
 *
 * PROBLEM UNDERSTANDING:
 *   Sorted array rotated at unknown pivot. Find target index.
 *
 * KEY OBSERVATION:
 *   At any mid: at least one half is sorted (no duplicates guarantee).
 *   Check which half is sorted, then check if target is in that range.
 *
 * EDGE CASES:
 *   - Not rotated (already sorted): arr[lo] <= arr[mid] always → works normally
 *   - Single element: lo==hi==mid, check directly
 *
 * COMPLEXITY: Time O(log N) | Space O(1)
 */
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int lo = 0, hi = nums.size() - 1;

        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;

            if (nums[mid] == target) return mid;

            // determine which half is sorted
            if (nums[lo] <= nums[mid]) {
                // left half [lo..mid] is sorted
                if (nums[lo] <= target && target < nums[mid])
                    hi = mid - 1;    // target in sorted left half
                else
                    lo = mid + 1;    // target in right half
            } else {
                // right half [mid..hi] is sorted
                if (nums[mid] < target && target <= nums[hi])
                    lo = mid + 1;    // target in sorted right half
                else
                    hi = mid - 1;    // target in left half
            }
        }

        return -1;
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "`arr[lo]<=arr[mid]` → left sorted. Check if target in left range → hi=mid-1. Else lo=mid+1. Mirror for right sorted."

---

## 📝 Short Revision Notes

- At least one half is always sorted when no duplicates
- Left sorted: `arr[lo] <= arr[mid]`; Right sorted: otherwise
- Range check for left sorted half: `arr[lo] <= target < arr[mid]`
- Range check for right sorted half: `arr[mid] < target <= arr[hi]`
- Works for non-rotated arrays too (left condition always true)

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "Search in rotated sorted array"
- "Sorted array, unknown rotation point"
- "Binary search, not globally sorted"

**I should think of:** Check which half is sorted, then check target range

---

## ⚠️ Common Mistakes

❌ Checking `arr[lo] < arr[mid]` (strict) instead of `<=` — misses non-rotated case  
❌ Range condition: `arr[lo] <= target && target < arr[mid]` vs `<= arr[mid]` — target at mid is caught by the `==` check first  
❌ `nums[mid] < target && target <= nums[hi]` — both conditions needed for right half  

---

## 🔥 What Interviewer Is Testing

- **Concept:** Modified binary search for partially sorted data
- **Reasoning:** Why at least one half is always sorted (pigeonhole with rotation)
- **Detail:** Exact range conditions for each sorted half

---

## 🚀 Alternative Approaches

| Approach | Time | Space | Notes |
|----------|------|-------|-------|
| Modified binary search | O(log N) | O(1) | Optimal |
| Find pivot then binary search | O(log N) | O(1) | Two-pass, same complexity |
| Linear scan | O(N) | O(1) | Too slow |

---

## 📚 Related Problems

- [ ] LeetCode #33 — Search in Rotated Sorted Array
- [ ] LeetCode #81 — Search in Rotated Sorted Array II (with duplicates) → P10
- [ ] LeetCode #153 — Find Minimum in Rotated Sorted Array → P11
- [ ] Striver Step 4 P14 — Count Rotations

---

## 🏆 Pattern Category

`Binary Search` · `Rotated Array`

---

## 🎯 Difficulty Analysis

**Rating:** Medium

**Why challenging:** Standard binary search doesn't apply directly. The insight — one half is always sorted — requires careful reasoning about the rotation. Range conditions are easy to get wrong.

---

## 📈 Progression Insight

**Harder variant (P10):** Same problem with duplicates — when `arr[lo] == arr[mid]`, can't determine sorted half → must shrink both ends.

---

## ⏱️ 30-Second Last-Minute Revision

> **Problem:** Find target in rotated sorted array (no dups)  
> **Approach:** `arr[lo]<=arr[mid]` → left sorted → if `lo<=target<mid` then `hi=mid-1` else `lo=mid+1`. Else right sorted → if `mid<target<=hi` then `lo=mid+1` else `hi=mid-1`.  
> **Time:** O(log N) | **Space:** O(1)  
> **Watch out for:** `<=` not `<` when checking `arr[lo] <= arr[mid]`
