# 🔥 Binary Search Fundamentals: Search, Lower Bound, Upper Bound, Insert Position

> **LeetCode #704, #35** · **Difficulty:** Easy · **Step 4 — Binary Search · P01–P04**

---

## 🧠 The Core Template

Binary Search works on **sorted** arrays by repeatedly halving the search space.

```
INVARIANT: Target is always in arr[lo..hi] (if it exists)
```

**The 3-line template (memorize this):**
```cpp
int lo = 0, hi = n - 1;
while (lo <= hi) {
    int mid = lo + (hi - lo) / 2;      // overflow-safe
    if (arr[mid] == target) return mid;
    else if (arr[mid] < target) lo = mid + 1;
    else hi = mid - 1;
}
return -1;
```

**Why `lo + (hi - lo) / 2` not `(lo + hi) / 2`?**  
`lo + hi` can overflow when both are large. `lo + (hi - lo) / 2` is always safe.

---

# P01 — Standard Binary Search

**Find index of `target` in sorted array. Return -1 if not found.**

```cpp
/*
 * BINARY SEARCH — classic template
 * Sorted array, find target index
 * Time O(log N) | Space O(1)
 */
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int lo = 0, hi = nums.size() - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (nums[mid] == target) return mid;
            else if (nums[mid] < target) lo = mid + 1;
            else hi = mid - 1;
        }
        return -1;
    }
};
```

### Dry Run
`arr=[1,3,5,7,9,11]`, target=7

| lo | hi | mid | arr[mid] | Action |
|----|----|-----|----------|--------|
| 0 | 5 | 2 | 5 | 5<7 → lo=3 |
| 3 | 5 | 4 | 9 | 9>7 → hi=3 |
| 3 | 3 | 3 | 7 | **Found!** return 3 |

---

# P02 — Lower Bound

**Find the index of the first element ≥ target. (Same as `std::lower_bound`)**

### Key Observation
> 💡 Instead of returning on exact match, keep narrowing: when `arr[mid] >= target`, store mid as answer and go left.

```cpp
/*
 * LOWER BOUND — first index where arr[index] >= target
 * Returns N if all elements < target
 * Time O(log N) | Space O(1)
 */
int lowerBound(vector<int>& arr, int target) {
    int lo = 0, hi = arr.size();    // hi = n (past end), answer starts here
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] < target) lo = mid + 1;
        else hi = mid;              // arr[mid] >= target: candidate, go left
    }
    return lo;                      // lo == hi is the answer
}
```

**STL equivalent:** `lower_bound(arr.begin(), arr.end(), target) - arr.begin()`

### Dry Run
`arr=[1,3,5,7,9]`, target=6. Find first element ≥ 6.

| lo | hi | mid | arr[mid] | Action |
|----|-----|-----|----------|--------|
| 0 | 5 | 2 | 5 | 5<6 → lo=3 |
| 3 | 5 | 4 | 9 | 9≥6 → hi=4 |
| 3 | 4 | 3 | 7 | 7≥6 → hi=3 |
| 3 | 3 | — | — | lo==hi → return 3 |

**Answer:** index 3 (value 7, first ≥ 6) ✅

---

# P03 — Upper Bound

**Find the index of the first element > target. (Same as `std::upper_bound`)**

```cpp
/*
 * UPPER BOUND — first index where arr[index] > target
 * Returns N if all elements <= target
 * Time O(log N) | Space O(1)
 */
int upperBound(vector<int>& arr, int target) {
    int lo = 0, hi = arr.size();
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] <= target) lo = mid + 1;  // <= (strict upper bound)
        else hi = mid;
    }
    return lo;
}
```

**STL equivalent:** `upper_bound(arr.begin(), arr.end(), target) - arr.begin()`

**Difference from lower bound:**
- Lower bound: first `≥ target` → `arr[mid] < target` moves lo
- Upper bound: first `> target` → `arr[mid] <= target` moves lo

---

# P04 — Search Insert Position

**Return index where target would be inserted to keep array sorted.**

This is exactly **Lower Bound** — insert position = first index ≥ target.

```cpp
int searchInsert(vector<int>& nums, int target) {
    return lowerBound(nums, target);    // same as lower bound
}
```

**Examples:**
- `[1,3,5,6]`, target=5 → 2 (exists)
- `[1,3,5,6]`, target=2 → 1 (between 1 and 3)
- `[1,3,5,6]`, target=7 → 4 (after all)

---

## 🧾 Recall Lines

| Problem | Key | Template detail |
|---------|-----|-----------------|
| Standard BS | `==` check, lo/hi converge | `lo <= hi`, return mid on match |
| Lower Bound | First `≥ target` | `arr[mid] < target` → lo++; else hi=mid |
| Upper Bound | First `> target` | `arr[mid] <= target` → lo++; else hi=mid |
| Insert Position | = Lower Bound | Same code, different framing |

## 📝 Key Notes

- **`lo <= hi`** for standard search (looking for exact match)
- **`lo < hi`** for bound problems (converging to answer index)
- `hi = n` (not `n-1`) for bounds — answer could be past end
- `mid = lo + (hi-lo)/2` always — prevents overflow

## ⚠️ Common Mistakes

❌ `(lo+hi)/2` → overflow when lo and hi are large  
❌ `lo <= hi` vs `lo < hi` — wrong termination condition for bounds  
❌ `hi = n-1` for bounds problems — misses "insert at end" case  
❌ `lo = mid` instead of `lo = mid+1` → infinite loop when lo==hi-1

## 🏆 Pattern Category

`Binary Search` · `Arrays` · `Sorted`

## ⏱️ 30-Second Revision

> Standard: `lo<=hi`, return mid on match. **Lower bound:** `arr[mid]<target→lo=mid+1, else hi=mid`, return lo. **Upper bound:** `arr[mid]<=target→lo=mid+1, else hi=mid`, return lo. `hi=n` for bounds.
