# 🔥 Matrix Median

> **GFG Classic** · **Difficulty:** Hard · **Step 4 — Binary Search · P17**

---

## 🧠 Problem Understanding

**What is it asking?**
Given an M×N matrix where **each row is sorted**, find the **median** of all M×N elements. M×N is always **odd** (guaranteed).

**Input:**
```
matrix = [[1, 3, 5],
           [2, 6, 9],
           [3, 6, 9]]
```
**Output:** `5` (sorted: [1,2,3,3,5,6,6,9,9] → median = 5th element = 5)

**Constraints:** 1 ≤ M, N ≤ 500, 1 ≤ matrix[i][j] ≤ 10⁹, M×N is odd

**Key Observations:**
- Median is the `(M×N + 1) / 2` th smallest element
- For any value `x`: count of elements ≤ x across all rows can be computed in O(M log N) using `upper_bound` on each row
- Binary search on the VALUE: find the smallest `x` such that count(elements ≤ x) ≥ (M×N + 1) / 2

**Simple Example:**
```
desired position = (3*3+1)/2 = 5

For x=5: count of elements ≤ 5:
  Row 0: [1,3,5] → upper_bound(5) = index 3 → 3 elements
  Row 1: [2,6,9] → upper_bound(5) = index 1 → 1 element
  Row 2: [3,6,9] → upper_bound(5) = index 1 → 1 element
  Total = 5 ≥ 5 ✓

For x=4: Total = 2+1+1=4 < 5 ✗
→ Median = 5 ✅
```

---

## 🥉 Brute Force Approach

### Idea
Flatten all elements into a single array, sort, return middle element.

### Algorithm
1. Copy all M×N elements into `arr`
2. Sort `arr`
3. Return `arr[(M*N)/2]`

### Complexity
- **Time:** O(M×N log(M×N))
- **Space:** O(M×N)

---

## 🥇 Optimal Approach — Binary Search on Value

### Key Observation

> 💡 **Binary search on the answer space** `[min_val, max_val]`.
>
> **Feasibility check:** For value `x`, count total elements ≤ x. This is doable in O(M log N) using `upper_bound` on each sorted row.
>
> Find the **smallest x** where `count(elements ≤ x) ≥ (M×N + 1) / 2`.
>
> That x is the median (it's the `(M×N+1)/2`th smallest element).

**Why `upper_bound`?** `upper_bound(row, x)` returns an iterator to the first element > x, so the number of elements ≤ x in the row = `upper_bound(row, x) - row.begin()`.

### Algorithm
1. `lo = 1` (minimum possible value), `hi = 10⁹` (maximum possible value)
2. `desired = (M × N + 1) / 2`
3. While `lo < hi`:
   - `mid = lo + (hi - lo) / 2`
   - `count = Σ upper_bound(row, mid) - row.begin()` for each row
   - If `count < desired`: `lo = mid + 1`
   - Else: `hi = mid`
4. Return `lo`

### Dry Run

**Matrix:**
```
[[1, 3, 5],
 [2, 6, 9],
 [3, 6, 9]]
```
`desired = 5`, `lo = 1`, `hi = 10⁹`

Iteration 1: `mid = 500000000`
- count = 3+3+3=9 ≥ 5 → `hi = 500000000`

...binary search converges...

Iteration (near answer): `mid = 5`
- Row 0: upper_bound(5) → index 3 (3 elements ≤ 5: 1,3,5)
- Row 1: upper_bound(5) → index 1 (1 element ≤ 5: 2)
- Row 2: upper_bound(5) → index 1 (1 element ≤ 5: 3)
- count = 5 ≥ 5 → `hi = 5`

Iteration: `mid = 4`
- Row 0: upper_bound(4) → 2 (1,3 ≤ 4)
- Row 1: upper_bound(4) → 1 (2 ≤ 4)
- Row 2: upper_bound(4) → 1 (3 ≤ 4)
- count = 4 < 5 → `lo = 5`

`lo = hi = 5` → **return 5** ✅

### Complexity
- **Time:** O(M log N × log(max_val)) — O(log(max_val)) ≈ O(30) iterations × O(M log N) per iteration
- **Space:** O(1)

---

## 🎤 Interview Explanation Script

> "The brute force flattens and sorts: O(MN log MN) time and O(MN) space."

> "The optimal uses binary search on the value range. The key insight: for any candidate median value `x`, I can count how many matrix elements are ≤ x in O(M log N) — one `upper_bound` call per row."

> "The median is the smallest `x` such that at least `(MN+1)/2` elements are ≤ x. I binary search for this `x` in [1, 10⁹]. Each iteration does O(M log N) work, and there are O(log(10⁹)) ≈ 30 iterations."

> "Total: O(M log N × 30) which for M=N=500 is about 500 × 9 × 30 = 135,000 operations. Very fast."

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * MATRIX MEDIAN — binary search on answer value
 *
 * PROBLEM UNDERSTANDING:
 *   M×N matrix, each row sorted. Find median (M×N is odd).
 *
 * KEY OBSERVATION:
 *   Median = smallest x such that count(elements ≤ x) ≥ (MN+1)/2
 *   Count using upper_bound on each sorted row: O(M log N) per check.
 *
 * BINARY SEARCH on value range [lo, hi] = [1, 10^9]
 *
 * COMPLEXITY: Time O(M log N × log(max_val)) | Space O(1)
 */
class Solution {
private:
    // count elements ≤ x across all rows
    int countLessEqual(vector<vector<int>>& mat, int x) {
        int count = 0;
        for (auto& row : mat)
            count += (int)(upper_bound(row.begin(), row.end(), x) - row.begin());
        return count;
    }

public:
    int matrixMedian(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        int desired = (m * n + 1) / 2;    // median position

        // search space: [min_value, max_value]
        int lo = 1, hi = 1e9;

        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;

            if (countLessEqual(mat, mid) < desired)
                lo = mid + 1;    // too few elements ≤ mid, need larger value
            else
                hi = mid;        // enough elements ≤ mid, try smaller
        }

        return lo;
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "BS on value [1, 10⁹]. Count ≤ mid using upper_bound per row. Find smallest with count ≥ (MN+1)/2."

---

## 📝 Short Revision Notes

- Binary search on VALUE, not index
- `desired = (M*N + 1) / 2` — for odd M*N, this is the median position
- `upper_bound(row, x) - row.begin()` = count of elements ≤ x in that row
- lo/hi: `lo = mat[0][0]` (global min) to `mat[M-1][N-1]` (global max) more precisely, or just [1, 10⁹]
- Return `lo` (smallest x with enough elements ≤ it)

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "Median of matrix/multiple sorted arrays"
- "Find Kth smallest in sorted rows"
- "Binary search on value when index search is hard"

**I should think of:** BS on value + count using upper_bound per row

---

## ⚠️ Common Mistakes

❌ Using `lower_bound` instead of `upper_bound` — counts elements < x, not ≤ x  
❌ `desired = (M*N) / 2` — off by one; correct is `(M*N + 1) / 2`  
❌ Initializing `lo = 0` — if matrix has non-zero positive integers, lo should be ≥ 1  

---

## 🔥 What Interviewer Is Testing

- **Concept:** Binary search on answer space (value, not index)
- **Reasoning:** Why `upper_bound` per row gives correct count in O(log N)
- **Design:** Connecting "find Kth smallest" to a monotone feasibility condition

---

## 🚀 Alternative Approaches

| Approach | Time | Space | Notes |
|----------|------|-------|-------|
| BS on value | O(M log N × log V) | O(1) | Optimal |
| Flatten + sort | O(MN log MN) | O(MN) | Simple but much slower |
| Min-heap K-way merge | O(MN log M) | O(M) | Alternative but slower |

---

## 📚 Related Problems

- [ ] LeetCode #378 — Kth Smallest Element in Sorted Matrix (similar BS on value)
- [ ] LeetCode #668 — Kth Smallest Number in Multiplication Table
- [ ] GFG — Matrix Median
- [ ] Striver Step 4 P13 — Kth Element of Two Sorted Arrays

---

## 🏆 Pattern Category

`Binary Search` · `Matrix` · `Search Space` · `Counting`

---

## 🎯 Difficulty Analysis

**Rating:** Hard

**Why challenging:** Connecting the "find median" problem to "binary search on value with counting" requires a significant shift in thinking. The `upper_bound` trick and the exact `desired` formula are non-trivial.

---

## 📈 Progression Insight

**Related:** LC #378 (Kth Smallest in Sorted Matrix) — same pattern, generalized to Kth element

**Pattern:** "Binary search on answer + count" appears in many hard problems: Koko bananas, book allocation, ship packages, gas stations — all use this exact template.

---

## ⏱️ 30-Second Last-Minute Revision

> **Problem:** Median of row-sorted M×N matrix (M×N odd)  
> **Approach:** BS on value [1, 10⁹]. `desired = (M*N+1)/2`. Count ≤ mid using `upper_bound` per row. `count < desired` → `lo=mid+1`. Else `hi=mid`. Return `lo`.  
> **Time:** O(M log N × log V) | **Space:** O(1)  
> **Watch out for:** `upper_bound` not `lower_bound`; `desired = (MN+1)/2`
