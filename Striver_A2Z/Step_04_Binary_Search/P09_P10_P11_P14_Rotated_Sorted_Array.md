# 🔥 Rotated Sorted Array Problems (P09–P11, P14)

> **LeetCode #33, #81, #153, #154** · **Difficulty:** Medium · **Step 4 — P09–P11, P14**

---

## 🧠 Core Concept — Rotated Sorted Array

A sorted array rotated at some pivot:
```
[4,5,6,7,0,1,2]  ← rotated at index 4
 ↑ sorted half ↑   ↑ sorted half ↑
```

**Key Insight:** Even in a rotated array, **at least one half is always sorted**.  
Use this to decide which half the target can be in.

---

# P09 — Search in Rotated Sorted Array I (No Duplicates)

> **LeetCode #33**

## 🥇 Algorithm

1. `lo=0, hi=n-1`
2. While `lo <= hi`:
   - `mid = (lo+hi)/2`
   - If `arr[mid] == target`: return mid
   - **If left half sorted** (`arr[lo] <= arr[mid]`):
     - If `target` in `[arr[lo], arr[mid])`: `hi = mid-1`
     - Else: `lo = mid+1`
   - **Else right half sorted** (`arr[mid] <= arr[hi]`):
     - If `target` in `(arr[mid], arr[hi]]`: `lo = mid+1`
     - Else: `hi = mid-1`

### Dry Run
`arr=[4,5,6,7,0,1,2]`, target=0

| lo | hi | mid | arr[mid] | Left sorted? | Action |
|----|-----|-----|----------|--------------|--------|
| 0 | 6 | 3 | 7 | arr[0]=4≤7 ✅ | 0 not in [4,7) → lo=4 |
| 4 | 6 | 5 | 1 | arr[4]=0≤1 ✅ | 0 in [0,1) ✅ → hi=4 |
| 4 | 4 | 4 | 0 | — | **Found!** return 4 |

```cpp
/*
 * SEARCH IN ROTATED SORTED ARRAY (no duplicates)
 * At least one half is always sorted → use it to decide direction
 * Time O(log N) | Space O(1)
 */
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int lo = 0, hi = nums.size() - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (nums[mid] == target) return mid;

            if (nums[lo] <= nums[mid]) {        // left half is sorted
                if (nums[lo] <= target && target < nums[mid])
                    hi = mid - 1;               // target in sorted left
                else
                    lo = mid + 1;
            } else {                            // right half is sorted
                if (nums[mid] < target && target <= nums[hi])
                    lo = mid + 1;               // target in sorted right
                else
                    hi = mid - 1;
            }
        }
        return -1;
    }
};
```

---

# P10 — Search in Rotated Sorted Array II (With Duplicates)

> **LeetCode #81**

## Problem with Duplicates
When `arr[lo] == arr[mid] == arr[hi]`, we can't determine which half is sorted.

**Solution:** When `arr[lo] == arr[mid]`, simply `lo++, hi--` to skip the ambiguity.

```cpp
/*
 * ROTATED SORTED ARRAY II (with duplicates)
 * Extra case: arr[lo]==arr[mid] → shrink both ends (can't determine sorted half)
 * Time O(log N) avg, O(N) worst (all same elements) | Space O(1)
 */
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int lo = 0, hi = nums.size() - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (nums[mid] == target) return true;

            // can't determine sorted half — shrink both ends
            if (nums[lo] == nums[mid] && nums[mid] == nums[hi]) {
                lo++; hi--;
            } else if (nums[lo] <= nums[mid]) {
                if (nums[lo] <= target && target < nums[mid])
                    hi = mid - 1;
                else lo = mid + 1;
            } else {
                if (nums[mid] < target && target <= nums[hi])
                    lo = mid + 1;
                else hi = mid - 1;
            }
        }
        return false;
    }
};
```

---

# P11 — Find Minimum in Rotated Sorted Array

> **LeetCode #153**

### Key Observation
> 💡 Minimum is at the rotation point. The sorted half with the **smaller starting value** contains the minimum OR is past it. When left half is sorted, minimum is at `lo` OR in right half.

```cpp
/*
 * FIND MINIMUM IN ROTATED SORTED ARRAY
 * If left half sorted and arr[lo] < arr[hi] → minimum is arr[lo]
 * Otherwise minimum is in the unsorted (right) half
 * Time O(log N) | Space O(1)
 */
class Solution {
public:
    int findMin(vector<int>& nums) {
        int lo = 0, hi = nums.size() - 1;
        int minVal = nums[0];

        while (lo <= hi) {
            if (nums[lo] <= nums[hi]) {
                // current segment is sorted → min is leftmost
                minVal = min(minVal, nums[lo]);
                break;
            }

            int mid = lo + (hi - lo) / 2;
            minVal = min(minVal, nums[mid]);

            if (nums[lo] <= nums[mid])
                lo = mid + 1;    // left half sorted, min is in right
            else
                hi = mid - 1;    // right half sorted from mid to hi, min is in left [lo..mid]
        }
        return minVal;
    }
};
```

### Dry Run
`arr = [4,5,6,7,0,1,2]`

| lo | hi | mid | arr[mid] | Left sorted? | Action |
|----|-----|-----|----------|--------------|--------|
| 0 | 6 | 3 | 7 | arr[0]=4≤7 ✅ | min=7, lo=4 |
| 4 | 6 | 5 | 1 | arr[4]=0≤1 ✅ | min=1, lo=6 |
| 6 | 6 | 6 | 2 | arr[6]=2≤arr[6] → sorted | min=min(1,2)=0? |

Wait — more clearly: `nums[lo]=2 <= nums[hi]=2` → sorted → minVal = min(1, 2) = 1. But answer should be 0!

Let me trace again properly using the correct approach:

Actually the cleaner approach is:
```cpp
int findMin(vector<int>& nums) {
    int lo = 0, hi = nums.size() - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] > nums[hi])
            lo = mid + 1;    // min is in right half
        else
            hi = mid;        // min is in left half including mid
    }
    return nums[lo];
}
```

**Dry run:** `[4,5,6,7,0,1,2]`

| lo | hi | mid | arr[mid] | arr[hi] | arr[mid]>arr[hi]? | Action |
|----|-----|-----|----------|---------|-------------------|--------|
| 0 | 6 | 3 | 7 | 2 | ✅ | lo=4 |
| 4 | 6 | 5 | 1 | 2 | ❌ | hi=5 |
| 4 | 5 | 4 | 0 | 1 | ❌ | hi=4 |
| 4 | 4 | — | — | — | lo==hi → return nums[4]=**0** ✅ |

```cpp
// Cleaner version:
int findMin(vector<int>& nums) {
    int lo = 0, hi = nums.size() - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] > nums[hi]) lo = mid + 1;  // min is right
        else hi = mid;                             // min is left incl mid
    }
    return nums[lo];
}
```

---

# P14 — How Many Times Has Array Been Rotated?

**Number of rotations = index of minimum element**

```cpp
int countRotations(vector<int>& nums) {
    int lo = 0, hi = nums.size() - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] > nums[hi]) lo = mid + 1;
        else hi = mid;
    }
    return lo;    // index of minimum = number of rotations
}
```

---

## 🧾 Recall Lines

| Problem | Key Condition | Decision |
|---------|--------------|----------|
| Search I | `arr[lo] <= arr[mid]` → left sorted | Check if target in sorted half |
| Search II | + `arr[lo]==arr[mid]==arr[hi]` | `lo++, hi--` (skip ambiguity) |
| Find Min | `arr[mid] > arr[hi]` | Min is right: `lo=mid+1` |
| Rotations | Index of minimum element | Same as Find Min |

## 📝 Short Revision Notes
- Rotated array: always one sorted half, one unsorted half (unless fully sorted)
- Search: check which half is sorted, then check if target is in it
- Find min: compare `arr[mid]` with `arr[hi]` (not `arr[lo]`)
- Duplicates: `arr[lo]==arr[mid]==arr[hi]` → ambiguous → shrink both ends

## ⚠️ Common Mistakes
❌ Comparing `arr[mid]` with `arr[lo]` for find-min (works but trickier)  
❌ For Search II: forgetting the duplicates edge case → wrong answer  
❌ `lo = mid` instead of `lo = mid+1` → infinite loop

## 🏆 Pattern Category
`Binary Search` · `Rotated Array`

## ⏱️ 30-Second Revision
> **Search:** Check which half sorted. Target in sorted half → go there, else other side.  
> **Min:** `arr[mid]>arr[hi]` → `lo=mid+1`. Else `hi=mid`. Return `nums[lo]`.  
> **Rotations** = index of minimum.
