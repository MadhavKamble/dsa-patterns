# P62 — Two Pointers with Binary Search (Sorted Matrix / 2D Search)

## 1. First-Timer Explanation

### What Is It?
This pattern combines sorted structure with efficient two-pointer or binary search navigation. Key applications:
1. **Search in 2D sorted matrix:** Navigate using elimination — start top-right corner
2. **Kth smallest in sorted matrix:** Binary search on value
3. **Find pairs satisfying condition:** Sort + binary search for O(n log n) instead of O(n²)

### 2D Matrix Search — Staircase Technique
```
Matrix (rows and columns sorted):
[1,  4,  7,  11]
[2,  5,  8,  12]
[3,  6,  9,  16]
[10, 13, 14, 17]

Target = 5. Start at TOP-RIGHT corner (1, 3) → value 11.

11 > 5 → can't be in this column (all values below are ≥ 11). Move LEFT.
7 > 5 → move left.
4 < 5 → can't be in this row above. Move DOWN.
5 == 5 → FOUND ✓
```

Why top-right? It's the unique "border" cell where you can either go down (larger) or left (smaller). Starting top-left: you could only go right or down (can't eliminate). Starting top-right: you eliminate either a column (too big) or a row (too small) at each step.

### When to Use
- "Search in matrix where rows and columns are sorted"
- "Count pairs where a + b < target" → sort, two pointers
- "Kth smallest in sorted matrix" → binary search on value (P44 alternatively)

### Common Mistakes
1. Starting at wrong corner (bottom-left works too; top-left/bottom-right don't)
2. For pair counting: using binary search per element vs O(n) two pointer

---

## 2. Revision Card

**Recognition Signal:** "sorted matrix search", "2D sorted grid", "count pairs"

**Core Idea:** Start at corner where one direction decreases, other increases. At each step, eliminate a row or column based on comparison with target.

**Trigger Keywords:** sorted matrix, sorted rows and columns, 2D search, staircase search

**Complexity:** O(m+n) for 2D search; O(n log n) with binary search for pair problems

---

## 3. Interview Tell Signs

- "Search in N×M matrix, rows/cols sorted" → staircase from top-right
- "Find pair with sum = target in two sorted arrays" → two pointers O(n)
- "Count pairs with sum < target" → sort + two pointer
- "Kth smallest in sorted matrix" → binary search on value (P44)

---

## 4. C++ Template

```cpp
#include <vector>
using namespace std;

// ── Search in 2D Sorted Matrix (staircase) ───────────────────────────────────
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int rows = matrix.size(), cols = matrix[0].size();
    int r = 0, c = cols - 1; // start top-right
    
    while (r < rows && c >= 0) {
        if (matrix[r][c] == target) return true;
        else if (matrix[r][c] > target) c--; // too big: move left
        else r++;                             // too small: move down
    }
    return false;
}

// ── Search in Sorted Matrix (each row sorted, first elem > last of prev row) ──
bool searchMatrix2(vector<vector<int>>& matrix, int target) {
    int rows = matrix.size(), cols = matrix[0].size();
    int lo = 0, hi = rows * cols - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        int val = matrix[mid/cols][mid%cols];
        if (val == target) return true;
        else if (val < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return false;
}
```

---

## 5. How to Present in Interview

**Verbal Script:**
> "For a matrix where both rows and columns are sorted, I start at the top-right corner. At each step, the current value is either the target, too large (move left to decrease), or too small (move down to increase). Each step eliminates a row or column. Since we start with m rows and n columns, we make at most m+n steps — O(m+n) total."

**Checklist:**
- [ ] Start at top-right corner (row=0, col=n-1)
- [ ] Loop while r < rows and c >= 0
- [ ] If match → true; if too big → c--; if too small → r++
- [ ] For fully sorted matrix (each row's last < next row's first) → treat as 1D and binary search
- [ ] State O(m+n) vs O(log(mn)) for different matrix types

---

## 6. Problems

### Problem 1: Search a 2D Matrix (Fully Sorted, No Gaps)
**Difficulty:** Medium | **LC:** 74

**Note:** Each row's first element > previous row's last element → treat as 1D sorted array.

```cpp
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int rows = matrix.size(), cols = matrix[0].size();
    int lo = 0, hi = rows * cols - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        int val = matrix[mid/cols][mid%cols];
        if (val == target) return true;
        else if (val < target) lo = mid + 1;
        else hi = mid - 1;
    }
    return false;
}
// Time: O(log(mn)) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Search a 2D Matrix II (Rows and Cols Sorted)
**Difficulty:** Medium | **LC:** 240

```cpp
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int r = 0, c = matrix[0].size() - 1;
    while (r < (int)matrix.size() && c >= 0) {
        if (matrix[r][c] == target) return true;
        else if (matrix[r][c] > target) c--;
        else r++;
    }
    return false;
}
// Time: O(m+n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Count Negative Numbers in a Sorted Matrix
**Difficulty:** Easy | **LC:** 1351

**Approach:** Staircase from bottom-left. Count negatives per row using binary search or pointer.

```cpp
int countNegatives(vector<vector<int>>& grid) {
    int rows = grid.size(), cols = grid[0].size();
    int r = rows - 1, c = 0, count = 0; // start bottom-left
    while (r >= 0 && c < cols) {
        if (grid[r][c] < 0) { count += cols - c; r--; } // all in this row from c are negative
        else c++;
    }
    return count;
}
// Time: O(m+n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Find Target Indices After Sorting Array
**Difficulty:** Easy | **LC:** 2089

```cpp
vector<int> targetIndices(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    int lo = lower_bound(nums.begin(), nums.end(), target) - nums.begin();
    int hi = upper_bound(nums.begin(), nums.end(), target) - nums.begin();
    vector<int> res;
    for (int i = lo; i < hi; i++) res.push_back(i);
    return res;
}
// Time: O(n log n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: K-th Smallest Prime Fraction (Binary Search on Value)
**Difficulty:** Medium | **LC:** 786

```cpp
vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
    int n = arr.size();
    double lo = 0, hi = 1;
    
    while (hi - lo > 1e-9) {
        double mid = (lo + hi) / 2;
        int count = 0, p = 0, q = 1;
        int j = 1;
        for (int i = 0; i < n; i++) {
            while (j < n && arr[i] > mid * arr[j]) j++;
            count += n - j;
            if (j < n && p * arr[j] < q * arr[i]) { p = arr[i]; q = arr[j]; }
        }
        if (count == k) return {p, q};
        else if (count > k) hi = mid;
        else lo = mid;
    }
    return {};
}
// Time: O(n log(1/eps)) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** Why can't we start at the top-left corner for the staircase search?
<details><summary>Reveal</summary>
At top-left, if value < target: we could go right OR down (both increase). We can't eliminate a row or column, so we have no greedy choice. Starting top-right: if value > target, must go left (column eliminated). If value < target, must go down (row eliminated). Unambiguous choices.
</details>

**Drill 2:** Matrix74 vs Matrix240 — what's the structural difference?
<details><summary>Reveal</summary>
LC74: Each row is sorted AND the first element of each row is greater than the last element of the previous row. Essentially a 1D sorted array folded into 2D → binary search on virtual index. LC240: Each row AND each column is sorted, but rows don't "wrap" — O(m+n) staircase needed.
</details>

**Drill 3:** Count pairs (a,b) in sorted array where a + b < target. How?
<details><summary>Reveal</summary>
Two pointers: lo=0, hi=n-1. If arr[lo]+arr[hi] < target: all pairs (lo, lo+1..hi) are valid → count += hi-lo, lo++. Else: hi--. O(n) after O(n log n) sort.
</details>

**Drill 4:** Kth smallest in sorted matrix: why might binary search on value work even though values aren't a sorted array?
<details><summary>Reveal</summary>
The count function `count(x) = how many elements ≤ x` is monotonically non-decreasing in x. Binary search finds the smallest x where count(x) ≥ k AND x exists in the matrix. The staircase technique computes count(x) in O(m+n).
</details>

**Drill 5:** For fully sorted matrix treated as 1D, index `mid=5` in a 3×4 matrix. What's the (row, col)?
<details><summary>Reveal</summary>
row = mid / cols = 5 / 4 = 1. col = mid % cols = 5 % 4 = 1. Matrix position (1, 1). Verify: 0→(0,0), 1→(0,1), 2→(0,2), 3→(0,3), 4→(1,0), 5→(1,1) ✓.
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Space |
|---------|------|-------|
| 2D search (staircase) | O(m+n) | O(1) |
| 2D search (binary, fully sorted) | O(log(mn)) | O(1) |
| Count pairs with sum | O(n log n + n) | O(1) |
| Kth smallest in sorted matrix | O((m+n) log(max-min)) | O(1) |

---

## 9. Common Follow-up Questions

**Q: What if the matrix is HUGE and doesn't fit in memory?**
A: Binary search on value works in O(m×log(max-min)) with the staircase count — no need to load the whole matrix.

**Q: Find all pairs with sum = target in two sorted arrays?**
A: Two pointers: one starts at beginning of first array, one at end of second. If sum = target: record. If sum < target: advance pointer 1. If sum > target: retreat pointer 2. O(n+m).

**Q: What if the matrix has random-access but arbitrary values?**
A: No O(m+n) algorithm exists. Best is O(mn log n) = sort rows then binary search each.

---

## 10. Cross-Pattern Connections

- **P59 (Binary Search Basics):** Treats 2D sorted matrix as 1D
- **P44 (K-Way Merge):** K-th smallest in sorted matrix via min-heap
- **P04 (Two Pointers):** Pair counting is two-pointer on sorted arrays
- **P61 (Binary Search on Answer):** Binary search on value for kth smallest
