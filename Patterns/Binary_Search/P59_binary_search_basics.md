# P59 — Binary Search Fundamentals

## 1. First-Timer Explanation

### What Is It?
**Binary search** reduces search space by half each step. It works on any **monotone** structure: sorted arrays, functions that are "false then true" or "true then false." The key insight: you don't need to search all n elements — if you can evaluate a condition at the midpoint and know which half to discard, you converge in O(log n).

### The Template That Always Works
```
lo = leftmost_possible
hi = rightmost_possible

while (lo < hi):            ← NOT <=
    mid = lo + (hi - lo) / 2   ← avoids overflow, biases DOWN
    if condition(mid):
        hi = mid            ← mid could be the answer
    else:
        lo = mid + 1        ← mid definitely not the answer

return lo                   ← lo == hi == answer
```

This finds the **first** position where `condition(mid)` is true.

### Visual Walkthrough — Find First Bad Version
```
[G, G, G, B, B, B]  (G=good, B=bad)
 0  1  2  3  4  5

lo=0, hi=5
mid=2: condition(2)=G → lo=3
mid=4: condition(4)=B → hi=4
mid=3: condition(3)=B → hi=3
lo==hi==3 → return 3 ✓
```

### The Three Variants
1. **Find exact value:** standard `lo <= hi`, return when found, else -1
2. **Find first true position:** `lo < hi`, `hi = mid` when true, `lo = mid+1` when false
3. **Find last true position:** use `mid = lo + (hi-lo+1)/2` (bias UP) to avoid infinite loop

### When to Use
- Sorted array, find value/position
- "Find minimum X such that condition holds"
- "Find maximum X such that condition holds"
- Monotone function: if f(x) is true for all x ≥ threshold

### Common Mistakes
1. `lo + hi / 2` instead of `lo + (hi-lo)/2` → integer overflow
2. Using `lo <= hi` for the boundary template → infinite loop
3. `mid = lo + (hi-lo)/2` when looking for LAST true → can loop infinitely (lo never advances)
4. Off-by-one: when `lo = hi`, is the answer `lo` or `lo - 1`?

---

## 2. Revision Card

**Recognition Signal:** "find first/last position", "sorted array search", "minimum/maximum satisfying condition"

**Core Idea:** Two pointers `lo` and `hi` converging. At `mid`, evaluate condition. Move boundary based on monotone property. Converges in O(log n).

**Trigger Keywords:** sorted, find, minimum/maximum X such that, first/last occurrence, search

**Complexity:** O(log n) time, O(1) space always

---

## 3. Interview Tell Signs

- "Find X in sorted array" → basic binary search
- "Find first/last occurrence" → boundary binary search
- "Minimum X where condition holds" → binary search on answer
- "Search in rotated array" → modified binary search (P60)
- Array/range is too large to scan → binary search

---

## 4. C++ Template

```cpp
#include <vector>
using namespace std;

// ── Classic: find exact value ─────────────────────────────────────────────────
int binarySearch(vector<int>& nums, int target) {
    int lo = 0, hi = nums.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] == target) return mid;
        else if (nums[mid] < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

// ── Find FIRST position where condition is true ───────────────────────────────
// condition: a monotone predicate "false...false, true...true"
int findFirst(int lo, int hi, auto condition) {
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (condition(mid)) hi = mid;   // mid might be the answer
        else lo = mid + 1;              // mid is definitely not
    }
    return lo; // lo == hi
}

// ── Find LAST position where condition is true ────────────────────────────────
// condition: "true...true, false...false"
int findLast(int lo, int hi, auto condition) {
    while (lo < hi) {
        int mid = lo + (hi - lo + 1) / 2; // bias UP to avoid lo==mid infinite loop
        if (condition(mid)) lo = mid;
        else hi = mid - 1;
    }
    return lo;
}

// ── std::lower_bound and upper_bound ─────────────────────────────────────────
// lower_bound(begin, end, target): first position >= target
// upper_bound(begin, end, target): first position > target
// First occurrence of target: lower_bound (check if == target)
// Last occurrence: upper_bound - 1 (check if == target)
```

---

## 5. How to Present in Interview

**Verbal Script:**
> "Binary search: maintain [lo, hi] as the search space. At each step, compute mid = lo + (hi-lo)/2 to avoid overflow. If the target is in the right half, set lo = mid+1. If in the left half (or mid might be the answer), set hi = mid. When lo == hi, that's our answer. O(log n) time."

**Checklist:**
- [ ] Compute mid safely: `lo + (hi-lo)/2`
- [ ] Identify: classic search OR first/last boundary?
- [ ] For boundary search: `lo < hi`, not `lo <= hi`
- [ ] For "last true": use biased mid `lo + (hi-lo+1)/2`
- [ ] Verify the loop terminates (lo always advances or hi always shrinks)

---

## 6. Problems

### Problem 1: Binary Search (Classic)
**Difficulty:** Easy | **LC:** 704

```cpp
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
// Time: O(log n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: First Bad Version
**Difficulty:** Easy | **LC:** 278

```cpp
// isBadVersion(version) → API
int firstBadVersion(int n) {
    int lo = 1, hi = n;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (isBadVersion(mid)) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}
// Time: O(log n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Find First and Last Position of Element
**Difficulty:** Medium | **LC:** 34

**Approach:** Two binary searches — one for first occurrence, one for last.

```cpp
vector<int> searchRange(vector<int>& nums, int target) {
    auto findFirst = [&]() {
        int lo = 0, hi = nums.size();
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (nums[mid] >= target) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    };
    auto findLast = [&]() {
        int lo = 0, hi = nums.size();
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (nums[mid] > target) hi = mid;
            else lo = mid + 1;
        }
        return lo - 1;
    };
    
    int first = findFirst();
    if (first == (int)nums.size() || nums[first] != target) return {-1, -1};
    return {first, findLast()};
}
// Time: O(log n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Search Insert Position
**Difficulty:** Easy | **LC:** 35

```cpp
int searchInsert(vector<int>& nums, int target) {
    int lo = 0, hi = nums.size();
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] >= target) hi = mid;
        else lo = mid + 1;
    }
    return lo; // first position >= target (insert point)
}
// Time: O(log n) | Space: O(1)
// Equivalent to: lower_bound(nums.begin(), nums.end(), target) - nums.begin()
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Sqrt(x)
**Difficulty:** Easy | **LC:** 69

**Approach:** Find largest k where k² ≤ x. Binary search on [0, x].

```cpp
int mySqrt(int x) {
    if (x < 2) return x;
    int lo = 1, hi = x / 2;
    while (lo < hi) {
        int mid = lo + (hi - lo + 1) / 2; // bias UP: find last true
        if ((long long)mid * mid <= x) lo = mid;
        else hi = mid - 1;
    }
    return lo;
}
// Time: O(log x) | Space: O(1)
// Finds last k where k*k <= x
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: Find Minimum in Rotated Sorted Array
**Difficulty:** Medium | **LC:** 153

**Approach:** Compare mid with hi. If nums[mid] > nums[hi], minimum is in right half.

```cpp
int findMin(vector<int>& nums) {
    int lo = 0, hi = nums.size() - 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (nums[mid] > nums[hi]) lo = mid + 1; // min in right half
        else hi = mid;                           // mid could be min
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

## 7. Pattern Recognition Drill

**Drill 1:** "Find the insertion point for target in sorted array." Which std function and what does it return?
<details><summary>Reveal</summary>
`lower_bound(arr.begin(), arr.end(), target) - arr.begin()`. Returns the first index where arr[i] >= target. If target exists, points to it. If not, points to where it would be inserted.
</details>

**Drill 2:** Why does "find last true" need `mid = lo + (hi-lo+1)/2` (biased up)?
<details><summary>Reveal</summary>
Without the +1, when lo=0 and hi=1: mid=0. If condition(0) is true, we set lo=mid=0 — no progress, infinite loop. Biasing mid up ensures when lo and hi differ by 1, mid equals hi, which can cause hi to advance to mid-1 (breaking the loop).
</details>

**Drill 3:** nums=[1,2,3,4,5], target=6. What does `lower_bound` return?
<details><summary>Reveal</summary>
It returns an iterator to nums.end() (one past last). As an index: 5. This is the insertion position — insert after position 4 (index 5). If we check nums[5] != 6, we know target doesn't exist.
</details>

**Drill 4:** Find minimum in rotated sorted [4,5,6,7,0,1,2]. Trace the search.
<details><summary>Reveal</summary>
lo=0,hi=6. mid=3, nums[3]=7 > nums[6]=2 → lo=4. lo=4,hi=6. mid=5, nums[5]=1 <= nums[6]=2 → hi=5. lo=4,hi=5. mid=4, nums[4]=0 <= nums[5]=1 → hi=4. lo==hi=4. nums[4]=0 ✓.
</details>

**Drill 5:** Binary search: when should you use `lo <= hi` vs `lo < hi`?
<details><summary>Reveal</summary>
`lo <= hi`: classic search for exact value. You exit when lo > hi (not found). `lo < hi`: boundary search (find first/last true). You exit when lo == hi, which is the answer. The `lo < hi` variant needs careful `hi = mid` or `lo = mid+1` to guarantee progress.
</details>

---

## 8. Complexity Cheatsheet

| Operation | STL | Time |
|-----------|-----|------|
| Find exact | `lower_bound` + check | O(log n) |
| First occurrence | `lower_bound` | O(log n) |
| Last occurrence | `upper_bound - 1` | O(log n) |
| Insert position | `lower_bound` | O(log n) |
| Count of target | `upper_bound - lower_bound` | O(log n) |

---

## 9. Common Follow-up Questions

**Q: Binary search on floating point?**
A: Replace loop with fixed iterations (e.g., 100 iterations for sufficient precision): `while (hi - lo > 1e-9)`. No off-by-one issues with floats.

**Q: Binary search on infinite arrays?**
A: First find the range: start at [0, 1], double until you find a value > target. Then binary search that range.

**Q: When is binary search NOT applicable?**
A: When the search space isn't monotone — i.e., you can't determine which half to discard from the midpoint value alone.

---

## 10. Cross-Pattern Connections

- **P60 (Search in Rotated Array):** Rotated sorted array binary search
- **P61 (Binary Search on Answer):** Apply binary search to answer space, not array
- **P53 (Interval Scheduling):** Binary search used to find non-overlapping intervals in O(n log n)
- **P25 (Union-Find):** `lower_bound` used in Kruskal's sorted edge processing
- **P64 (Monotonic Stack):** Stack + binary search for some range problems
