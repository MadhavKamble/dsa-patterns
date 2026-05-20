# P60 — Search in Rotated Array

## 1. First-Timer Explanation

### What Is It?
A **rotated sorted array** is a sorted array that has been "rotated" by some pivot: `[4,5,6,7,0,1,2]` is `[0,1,2,4,5,6,7]` rotated at index 3. Binary search still works in O(log n), but we need to determine which half is sorted and whether the target lies in it.

### Key Insight
At any midpoint, one half is ALWAYS fully sorted. Compare `nums[mid]` with `nums[lo]`:
- If `nums[lo] <= nums[mid]`: left half `[lo..mid]` is sorted
- Else: right half `[mid..hi]` is sorted

Once you know which half is sorted, check if target falls within it. If yes, search that half; else search the other.

### Visual Walkthrough
```
nums = [4, 5, 6, 7, 0, 1, 2], target = 0

lo=0, hi=6, mid=3: nums[3]=7
  nums[lo=4] <= nums[mid=7] → LEFT HALF [4,5,6,7] is sorted
  target=0 in [4,7]? NO → search right half
  lo = mid+1 = 4

lo=4, hi=6, mid=5: nums[5]=1
  nums[lo=0] <= nums[mid=1] → LEFT HALF [0,1] is sorted
  target=0 in [0,1]? YES → search left half
  hi = mid = 5

lo=4, hi=5, mid=4: nums[4]=0
  nums[lo=0] <= nums[mid=0] → LEFT HALF [0] is sorted
  target=0 in [0,0]? YES → hi = mid = 4

lo=4, hi=4 → nums[4] = 0 = target ✓
```

### When to Use
- "Search in rotated sorted array"
- "Find minimum in rotated array" (P59's last problem)
- "Array that was sorted but then rotated/shifted"

### Common Mistakes
1. Checking `nums[mid] >= nums[lo]` vs `nums[mid] > nums[lo]` — boundary matters with duplicates
2. Rotated array with duplicates → worst case O(n)
3. Forgetting: target might equal mid → check `nums[mid] == target` first

---

## 2. Revision Card

**Recognition Signal:** "search in rotated sorted array", "sorted array with pivot"

**Core Idea:** At every mid, one half is sorted. If `nums[lo] <= nums[mid]`: left sorted. Check if target in left half. Otherwise search right.

**Trigger Keywords:** rotated, pivot, sorted but shifted, circular array search

**Complexity:** O(log n) no duplicates, O(n) worst case with duplicates

---

## 3. Interview Tell Signs

- "Sorted array, but shifted by some positions" → rotated array search
- "Find minimum element" → find the pivot point (P59)
- "Search target in rotated array" → this pattern
- "Array with duplicates, find minimum after rotation" → worst O(n)

---

## 4. C++ Template

```cpp
#include <vector>
using namespace std;

// ── Search in Rotated Array (no duplicates) ───────────────────────────────────
int search(vector<int>& nums, int target) {
    int lo = 0, hi = nums.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] == target) return mid;
        
        if (nums[lo] <= nums[mid]) { // left half is sorted
            if (nums[lo] <= target && target < nums[mid]) hi = mid - 1;
            else lo = mid + 1;
        } else { // right half is sorted
            if (nums[mid] < target && target <= nums[hi]) lo = mid + 1;
            else hi = mid - 1;
        }
    }
    return -1;
}

// ── Search in Rotated Array (with duplicates) ────────────────────────────────
bool searchWithDuplicates(vector<int>& nums, int target) {
    int lo = 0, hi = nums.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] == target) return true;
        
        // Can't determine which half is sorted when lo==mid==hi
        if (nums[lo] == nums[mid]) { lo++; continue; }
        
        if (nums[lo] < nums[mid]) { // left sorted
            if (nums[lo] <= target && target < nums[mid]) hi = mid - 1;
            else lo = mid + 1;
        } else { // right sorted
            if (nums[mid] < target && target <= nums[hi]) lo = mid + 1;
            else hi = mid - 1;
        }
    }
    return false;
}
```

---

## 5. How to Present in Interview

**Verbal Script:**
> "Standard binary search fails on rotated arrays because we don't know which half to discard. But the key observation: at any midpoint, at least one half is fully sorted. I check if `nums[lo] <= nums[mid]` — if yes, the left half is sorted, and I can tell definitively if the target is in it. Otherwise, the right half is sorted and I do the same check. This gives O(log n)."

**Checklist:**
- [ ] Check `nums[mid] == target` first
- [ ] Determine which half is sorted: `nums[lo] <= nums[mid]` → left sorted
- [ ] For the sorted half: check if target is in range; if yes, go there; else other half
- [ ] Duplicates: add `if nums[lo] == nums[mid]: lo++` to skip ambiguity
- [ ] State O(log n) no dups, O(n) worst case with dups

---

## 6. Problems

### Problem 1: Search in Rotated Sorted Array
**Difficulty:** Medium | **LC:** 33

```cpp
int search(vector<int>& nums, int target) {
    int lo = 0, hi = nums.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] == target) return mid;
        if (nums[lo] <= nums[mid]) {
            if (nums[lo] <= target && target < nums[mid]) hi = mid - 1;
            else lo = mid + 1;
        } else {
            if (nums[mid] < target && target <= nums[hi]) lo = mid + 1;
            else hi = mid - 1;
        }
    }
    return -1;
}
// Time: O(log n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Search in Rotated Sorted Array II (with duplicates)
**Difficulty:** Medium | **LC:** 81

```cpp
bool search(vector<int>& nums, int target) {
    int lo = 0, hi = nums.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] == target) return true;
        if (nums[lo] == nums[mid]) { lo++; continue; } // skip duplicate
        if (nums[lo] < nums[mid]) {
            if (nums[lo] <= target && target < nums[mid]) hi = mid - 1;
            else lo = mid + 1;
        } else {
            if (nums[mid] < target && target <= nums[hi]) lo = mid + 1;
            else hi = mid - 1;
        }
    }
    return false;
}
// Time: O(log n) avg, O(n) worst | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Find Minimum in Rotated Sorted Array
**Difficulty:** Medium | **LC:** 153

```cpp
int findMin(vector<int>& nums) {
    int lo = 0, hi = nums.size() - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] > nums[hi]) lo = mid + 1; // min in right
        else hi = mid;                           // min in left (mid could be min)
    }
    return nums[lo];
}
// Time: O(log n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Find Minimum in Rotated Sorted Array II (with duplicates)
**Difficulty:** Hard | **LC:** 154

```cpp
int findMin(vector<int>& nums) {
    int lo = 0, hi = nums.size() - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] > nums[hi]) lo = mid + 1;
        else if (nums[mid] < nums[hi]) hi = mid;
        else hi--; // nums[mid]==nums[hi]: can't determine, shrink hi
    }
    return nums[lo];
}
// Time: O(log n) avg, O(n) worst | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** nums=[5,6,7,8,9,1,2,3], target=1. Which half is sorted at mid=3 (value=8)?
<details><summary>Reveal</summary>
nums[lo=5] <= nums[mid=8] → LEFT half [5,6,7,8] is sorted. Is target=1 in [5,8]? No → search right half. lo=4.
</details>

**Drill 2:** Why check `nums[lo] <= nums[mid]` (not strict <) for "left half sorted"?
<details><summary>Reveal</summary>
When `lo == mid` (single element or adjacent), `nums[lo] == nums[mid]` and the left half trivially is "sorted." Using `<=` correctly handles this case. If we used strict `<`, we'd miss this and go to the else branch incorrectly.
</details>

**Drill 3:** nums=[3,1] (2-element rotation), target=1. Trace.
<details><summary>Reveal</summary>
lo=0,hi=1. mid=0. nums[0]=3 ≠ 1. nums[lo=3] <= nums[mid=3] → left sorted. target=1 in [3,3)? No → lo=1. lo==hi=1. nums[1]=1=target → return 1 ✓.
</details>

**Drill 4:** For duplicates [1,1,1,0,1], find minimum. Trace.
<details><summary>Reveal</summary>
lo=0,hi=4. mid=2: nums[2]=1, nums[4]=1 → equal, hi=3. mid=1: nums[1]=1, nums[3]=0 → nums[mid]>nums[hi]? No (1>0 yes!) → lo=2. mid=2: nums[2]=1,nums[3]=0 → lo=3. lo==hi=3. nums[3]=0 ✓.
</details>

**Drill 5:** What's the rotation pivot of [4,5,6,7,0,1,2]? How would you find it?
<details><summary>Reveal</summary>
Pivot (rotation point) is at index 4 (value 0). Use "find minimum" binary search: it returns the pivot's index where nums[i] < nums[i-1] (i.e., the minimum). The original sorted array starts at the pivot.
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Worst (dups) |
|---------|------|------|
| Search (no dups) | O(log n) | O(log n) |
| Search (with dups) | O(log n) avg | O(n) |
| Find min (no dups) | O(log n) | O(log n) |
| Find min (with dups) | O(log n) avg | O(n) |

---

## 9. Common Follow-up Questions

**Q: How do you handle the case where the array isn't rotated at all?**
A: The algorithm handles it naturally. If not rotated, `nums[lo] <= nums[mid]` is always true, and it degenerates to standard binary search.

**Q: Can you find the rotation index without searching for a target?**
A: Yes — use the "find minimum" binary search. The rotation index is where the minimum element is.

**Q: What if the array is rotated multiple times?**
A: Only the final rotation matters. A sorted array rotated k times is the same as rotated once (at position k mod n).

---

## 10. Cross-Pattern Connections

- **P59 (Binary Search Basics):** Template is identical; just the condition changes
- **P61 (Binary Search on Answer):** Both use binary search; this is on array, that is on value space
- **P04 (Two Pointers):** Two pointers on sorted arrays; binary search for O(log n) vs O(n)
