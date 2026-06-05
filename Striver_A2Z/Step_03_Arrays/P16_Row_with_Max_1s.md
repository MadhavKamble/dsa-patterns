# 🔥 Find the Row with Maximum Number of 1s

> **GFG Classic** · **Difficulty:** Easy-Medium · **Step 3 — Arrays · P16**

---

## 🧠 Problem Understanding

**What is it asking?**
Given a binary matrix (only 0s and 1s) where **every row is sorted**, find the row that contains the maximum number of 1s. Return the 0-indexed row number.

**Input:**
```
matrix = [[0, 1, 1, 1],
           [0, 0, 1, 1],
           [1, 1, 1, 1],
           [0, 0, 0, 0]]
```
**Output:** `2` (row 2 has 4 ones — the most)

**Constraints:**
- Each row is sorted (all 0s then all 1s)
- 1 ≤ M, N ≤ 10³
- Return `-1` if all rows are all 0s

**Key Observations:**
- Since each row is sorted, 1s form a contiguous block at the right end
- The number of 1s in row `i` = N - (first index of 1 in row i)
- We can use binary search per row — but that's O(M log N)
- Optimal: staircase traversal from top-right, O(M + N)

**Simple Example:**
```
Row 0: [0,1,1,1] → 3 ones (first 1 at index 1)
Row 1: [0,0,1,1] → 2 ones (first 1 at index 2)
Row 2: [1,1,1,1] → 4 ones (first 1 at index 0) ← MAX
Row 3: [0,0,0,0] → 0 ones
Answer: Row 2
```

---

## 🥉 Brute Force Approach

### Idea
Count 1s in each row linearly. Track the row with the maximum count.

### Algorithm
1. `maxOnes = 0`, `maxRow = -1`
2. For each row `i`:
   - Count 1s in the row
   - If count > maxOnes: update `maxOnes = count`, `maxRow = i`
3. Return `maxRow`

### Complexity
- **Time:** O(M × N) — counting each cell
- **Space:** O(1)

### C++ Code
```cpp
// BRUTE FORCE: count ones in every row
int rowWithMax1s(vector<vector<int>>& matrix) {
    int maxOnes = 0, maxRow = -1;
    int m = matrix.size(), n = matrix[0].size();
    for (int i = 0; i < m; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) count += matrix[i][j];
        if (count > maxOnes) { maxOnes = count; maxRow = i; }
    }
    return maxRow;
}
```

---

## 🥈 Better Approach — Binary Search Per Row

### Idea
Since each row is sorted, the first 1 can be found with binary search. Count of 1s = N - (first index of 1).

### Algorithm
1. For each row `i`:
   - Use `lower_bound` to find first 1 (i.e., first element ≥ 1)
   - `ones = N - lower_bound_index`
   - Track row with maximum `ones`

### Complexity
- **Time:** O(M log N)
- **Space:** O(1)

### C++ Code
```cpp
// BETTER: binary search per row
int rowWithMax1s(vector<vector<int>>& matrix) {
    int maxOnes = 0, maxRow = -1;
    int n = matrix[0].size();
    for (int i = 0; i < matrix.size(); i++) {
        // lower_bound finds first element >= 1, i.e., first 1
        int pos = lower_bound(matrix[i].begin(), matrix[i].end(), 1) - matrix[i].begin();
        int ones = n - pos;
        if (ones > maxOnes) { maxOnes = ones; maxRow = i; }
    }
    return maxRow;
}
```

---

## 🥇 Optimal Approach — Staircase Traversal

### Key Observation

> 💡 Start from the **top-right corner** `(row=0, col=N-1)`.
>
> - If `matrix[row][col] == 1`: this row has at least `N-col` ones. It's a candidate. Move **left** (`col--`) trying to find even more ones.
> - If `matrix[row][col] == 0`: no point checking further left in this row for improvement. Move **down** (`row++`).
>
> The column pointer only ever moves left (decreasing), so it visits at most N positions. The row pointer only moves down, visiting at most M positions. Total: **O(M + N)**.

```
Start at top-right (0, N-1):
  matrix[0][3] = 1 → maxRow=0, col→2
  matrix[0][2] = 1 → maxRow=0, col→1
  matrix[0][1] = 1 → maxRow=0, col→0
  matrix[0][0] = 0 → row→1
  matrix[1][0] = 0 → row→2
  matrix[2][0] = 1 → maxRow=2, col→-1 → stop
```

### Algorithm
1. `row = 0`, `col = N - 1`, `maxRow = -1`
2. While `row < M` and `col >= 0`:
   - If `matrix[row][col] == 1`:
     - `maxRow = row` (this row has at least N - col ones)
     - `col--` (try to find a row with even more)
   - Else:
     - `row++` (this row can't beat current best from this column)
3. Return `maxRow`

### Dry Run

**Input:**
```
[[0, 1, 1, 1],
 [0, 0, 1, 1],
 [1, 1, 1, 1],
 [0, 0, 0, 0]]
```

Start: `row=0, col=3`

| row | col | val | Action | maxRow |
|-----|-----|-----|--------|--------|
| 0 | 3 | 1 | col-- | 0 |
| 0 | 2 | 1 | col-- | 0 |
| 0 | 1 | 1 | col-- | 0 |
| 0 | 0 | 0 | row++ | 0 |
| 1 | 0 | 0 | row++ | 0 |
| 2 | 0 | 1 | col-- | **2** |
| 2 | -1 | — | col<0 → stop | 2 |

**Output:** `2` ✅

### Complexity
- **Time:** O(M + N) — col moves left at most N times, row moves down at most M times
- **Space:** O(1)

### Why is this optimal?
Each step either decrements `col` or increments `row`. Since `col` can decrease at most N times and `row` can increase at most M times, the total steps are at most M + N. We cannot do better because we must at least inspect cells along one anti-diagonal path.

---

## 🎤 Interview Explanation Script

> "The brute force counts ones in every cell — O(M×N). Since each row is sorted, we can use binary search per row for O(M log N)."

> "The optimal is O(M+N) using a staircase traversal. I start at the top-right corner. If I see a 1, this row is a new best candidate — I record its index and move left, trying to find a row that beats it. If I see a 0, no elements to the left in this row can help since the row is sorted — I move down."

> "The column pointer only moves left, the row pointer only moves down. Total moves ≤ M + N. This is optimal because we're essentially walking down the boundary of 0s and 1s."

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * ROW WITH MAXIMUM 1s — staircase traversal from top-right
 *
 * PROBLEM UNDERSTANDING:
 *   Binary matrix, rows sorted. Find row with most 1s.
 *
 * KEY OBSERVATION:
 *   Start top-right. 1 → record row, go left (try to improve).
 *   0 → go down (this row can't beat current best starting from col).
 *
 * INVARIANT: col is always the "minimum column" needed to beat current best.
 *
 * COMPLEXITY: Time O(M+N) | Space O(1)
 */
class Solution {
public:
    int rowWithMax1s(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        int row = 0, col = n - 1;
        int maxRow = -1;

        while (row < m && col >= 0) {
            if (matrix[row][col] == 1) {
                maxRow = row;   // this row has at least (n - col) ones — new best
                col--;          // try to find a row with even more ones
            } else {
                row++;          // this row can't improve from this column — go down
            }
        }

        return maxRow;
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "Start top-right. 1 → record row, col--. 0 → row++. O(M+N)."

---

## 📝 Short Revision Notes

- Staircase: start `(0, N-1)`. 1 → `maxRow = row, col--`. 0 → `row++`
- Column only decreases → moves at most N times
- Row only increases → moves at most M times
- Total: O(M+N)
- Return `-1` if all rows are all zeros (maxRow never updated)
- Binary search per row: O(M log N) — acceptable but not optimal

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "Binary matrix with sorted rows"
- "Find row with most 1s / fewest 0s"
- "Count-based query on sorted 2D structure"

**I should think of:** Staircase traversal from corner

---

## ⚠️ Common Mistakes

❌ Starting at bottom-left instead of top-right (also works but less intuitive)  
❌ Updating `maxRow` when seeing a 0 — only update on 1  
❌ Using `col >= 0` in loop but not checking it — loop terminates early if col goes negative  
❌ Not returning `-1` when no 1s exist

---

## 🔥 What Interviewer Is Testing

- **Concept:** Staircase traversal — eliminating rows/columns from consideration
- **Reasoning:** Why this is O(M+N) and why binary search per row is suboptimal
- **Pattern:** Same idea appears in LC #240 (Search Matrix II)

---

## 🚀 Alternative Approaches

| Approach | Time | Space | Notes |
|----------|------|-------|-------|
| Staircase (optimal) | O(M+N) | O(1) | Best |
| Binary search per row | O(M log N) | O(1) | Good alternative |
| Brute force | O(M×N) | O(1) | Too slow |

---

## 📚 Related Problems

- [ ] LeetCode #240 — Search a 2D Matrix II (staircase for sorted rows+cols)
- [ ] LeetCode #74 — Search a 2D Matrix (binary search 1D mapping)
- [ ] Striver Step 3 P15 — Search in 2D Matrix
- [ ] GFG — Row with Max 1s

---

## 🏆 Pattern Category

`Arrays` · `Matrix` · `Two Pointers` · `Staircase`

---

## 🎯 Difficulty Analysis

**Rating:** Easy-Medium

**Why challenging:** The O(M log N) binary search solution is intuitive. The O(M+N) staircase is the optimization that interviewers look for — it requires recognizing that you can "share" progress across rows.

---

## 📈 Progression Insight

**Harder variant:** Matrix where both rows AND columns are sorted (LC #240) → same staircase but searching for a target value, not counting 1s.

**Even harder:** Find the row with the Kth most 1s → needs a different approach (sort rows by count while preserving indices).

---

## ⏱️ 30-Second Last-Minute Revision

> **Problem:** Find row with most 1s in row-sorted binary matrix  
> **Approach:** Start `(0, N-1)`. If 1 → `maxRow=row, col--`. If 0 → `row++`.  
> **Key trick:** Column only decreases, row only increases → O(M+N) total  
> **Time:** O(M+N) | **Space:** O(1)  
> **Watch out for:** Return -1 if all zeros; update maxRow ONLY on 1
