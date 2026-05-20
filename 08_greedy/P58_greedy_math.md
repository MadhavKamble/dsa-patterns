# P58 — Greedy Math Problems

## 1. First-Timer Explanation

### What Is It?
**Greedy math problems** use mathematical insight to make the optimal choice at each step: maximize product by choosing which numbers to multiply, minimize by choosing when to round or split, count by detecting patterns. The key is recognizing the mathematical invariant that makes the local choice globally optimal.

### Key Observations
1. **Break product:** To maximize product of integers summing to n, never use 1 (adds nothing), prefer 3s over 2s (3+3 > 2+2+2 but 3×3=9 > 2×2×2=8 when sum=6)
2. **Minimize by math:** Maximum score from matrix by alternating — parity/XOR tricks
3. **Count operations:** Count swaps needed by inversions or cycle detection

### Visual — Maximize Product (Integer Break)
```
n=10:
Options: 5+5=10, product=25
         3+3+4=10, product=36 ← better
         3+3+2+2=10, product=36 (same)
         
Key: prefer 3s. 10 = 3+3+4 (use 4 as 2+2, not split further)
10 // 3 = 3 remainder 1 → never leave remainder 1 (1×3 < 2+1... no: 2×2=4 > 1×3=3)
If remainder=1: convert last 3+1 to 2+2
```

### When to Use
- "Maximize product/split/break"
- "Minimum operations to transform number"
- "Count swaps needed"
- "Optimal rounding"

### Common Mistakes
1. Integer break: forgetting to handle n ≤ 3 specially
2. Using integer arithmetic where float needed
3. Not recognizing greedy vs DP distinction

---

## 2. Revision Card

**Recognition Signal:** "maximize product from split", "minimum swaps", "optimal pairing"

**Core Idea:** Apply mathematical theorem directly. Integer break: use 3s (and one 2 or 4 for remainder). Swap counting: count cycles in permutation.

**Trigger Keywords:** maximize product, split integer, minimum swaps, optimal value, mathematical

**Complexity:** O(log n) for most math problems; O(n) for permutation-based

---

## 3. Interview Tell Signs

- "Break integer n into parts, maximize product" → use 3s
- "Minimum swaps to sort" → count cycles in permutation
- "Minimum moves to equal array" → median minimizes absolute deviation
- "Maximize sum after k negations" → flip smallest negatives first

---

## 4. C++ Template

```cpp
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

// ── Integer Break (maximize product) ─────────────────────────────────────────
int integerBreak(int n) {
    if (n <= 3) return n - 1;
    int threes = n / 3;
    int rem = n % 3;
    if (rem == 0) return pow(3, threes);
    if (rem == 1) return pow(3, threes-1) * 4; // replace 3+1 with 2+2
    return pow(3, threes) * 2; // rem==2
}

// ── Minimum Moves to Equal Array (median) ────────────────────────────────────
int minMoves2(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int median = nums[nums.size()/2], moves = 0;
    for (int x : nums) moves += abs(x - median);
    return moves;
}

// ── Minimum Swaps to Sort (cycle count) ──────────────────────────────────────
int minSwapsToSort(vector<int>& arr) {
    int n = arr.size();
    vector<pair<int,int>> sorted_arr(n);
    for (int i = 0; i < n; i++) sorted_arr[i] = {arr[i], i};
    sort(sorted_arr.begin(), sorted_arr.end());
    
    vector<bool> visited(n, false);
    int swaps = 0;
    for (int i = 0; i < n; i++) {
        if (visited[i] || sorted_arr[i].second == i) continue;
        int cycle = 0, j = i;
        while (!visited[j]) { visited[j] = true; j = sorted_arr[j].second; cycle++; }
        swaps += cycle - 1; // cycle of length k needs k-1 swaps
    }
    return swaps;
}
```

---

## 5. How to Present in Interview

**Verbal Script (Integer Break):**
> "Mathematically, 3 is the optimal factor. 3+3 gives product 9, while 2+2+2 (same sum 6) gives 8. So I should use as many 3s as possible. If the remainder is 1 after dividing by 3, replace one 3+1 with 2+2 (product 4 > 3). If remainder is 2, multiply by one extra 2."

**Checklist:**
- [ ] State the mathematical theorem (why 3 is optimal)
- [ ] Handle edge cases n ≤ 3 separately
- [ ] Remainder 1 → replace with 2+2
- [ ] Use `pow` or `long long` for large results

---

## 6. Problems

### Problem 1: Integer Break
**Difficulty:** Medium | **LC:** 343

```cpp
int integerBreak(int n) {
    if (n == 2) return 1;
    if (n == 3) return 2;
    long long result = 1;
    while (n > 4) { result *= 3; n -= 3; }
    return result * n;
}
// Time: O(log n) | Space: O(1)
// Edge: n=4 → 2*2=4 (not 3+1=3) ← handle by stopping at n<=4
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Minimum Moves to Equal Array Elements II
**Difficulty:** Medium | **LC:** 462

**Approach:** Optimal target = median. Sum of |x - median| is minimized.

```cpp
int minMoves2(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int median = nums[nums.size()/2], ans = 0;
    for (int x : nums) ans += abs(x - median);
    return ans;
}
// Time: O(n log n) | Space: O(1)
// Why median? L1 distance minimized at median (provable by calculus/exchange arg)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: K-th Symbol in Grammar
**Difficulty:** Medium | **LC:** 779

**Approach:** Mathematical recursion. The K-th symbol in row N is determined by parent in row N-1.

```cpp
int kthGrammar(int n, int k) {
    if (n == 1) return 0;
    int parent = kthGrammar(n - 1, (k + 1) / 2);
    bool isLeft = k % 2 == 1;
    return isLeft ? parent : (1 - parent);
}
// Time: O(n) | Space: O(n) recursion
// Key: left child = same as parent, right child = flip of parent
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Maximum Sum of 3 Non-Overlapping Subarrays
**Difficulty:** Hard | **LC:** 689

**Approach:** Precompute window sums. Use three passes to find best left, right, and middle windows.

```cpp
vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> sums(n-k+1);
    int s = 0;
    for (int i = 0; i < k; i++) s += nums[i];
    sums[0] = s;
    for (int i = 1; i <= n-k; i++) { s += nums[i+k-1] - nums[i-1]; sums[i] = s; }
    
    // left[i] = index of max sum window in [0, i]
    vector<int> left(n-k+1), right(n-k+1);
    int best = 0;
    for (int i = 0; i <= n-k; i++) { if (sums[i] > sums[best]) best = i; left[i] = best; }
    best = n-k;
    for (int i = n-k; i >= 0; i--) { if (sums[i] >= sums[best]) best = i; right[i] = best; }
    
    vector<int> res(3, -1);
    int maxSum = 0;
    for (int mid = k; mid <= n-2*k; mid++) {
        int l = left[mid-k], r = right[mid+k];
        int total = sums[l] + sums[mid] + sums[r];
        if (total > maxSum) { maxSum = total; res = {l, mid, r}; }
    }
    return res;
}
// Time: O(n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Maximize Sum After K Negations
**Difficulty:** Easy | **LC:** 1005

**Approach:** Sort by absolute value. Flip negative numbers first. If k still remains, flip smallest absolute value element (possibly repeatedly, net effect only matters parity).

```cpp
int largestSumAfterKNegations(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end(), [](int a, int b) { return abs(a) > abs(b); });
    for (int i = 0; i < (int)nums.size() && k > 0; i++) {
        if (nums[i] < 0) { nums[i] = -nums[i]; k--; }
    }
    // If k still odd, flip smallest absolute value (last element after sort)
    int sum = accumulate(nums.begin(), nums.end(), 0);
    if (k % 2 == 1) sum -= 2 * nums.back();
    return sum;
}
// Time: O(n log n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: Score After Flipping Matrix
**Difficulty:** Medium | **LC:** 861

**Approach:** Greedy. First toggle rows to make first column all 1s. Then for each column, toggle if it increases count of 1s.

```cpp
int matrixScore(vector<vector<int>>& A) {
    int rows = A.size(), cols = A[0].size();
    // Toggle rows where A[i][0] == 0
    for (int i = 0; i < rows; i++)
        if (A[i][0] == 0)
            for (int j = 0; j < cols; j++) A[i][j] ^= 1;
    
    int score = 0;
    for (int j = 0; j < cols; j++) {
        int ones = 0;
        for (int i = 0; i < rows; i++) ones += A[i][j];
        score += max(ones, rows - ones) * (1 << (cols - 1 - j));
    }
    return score;
}
// Time: O(rows * cols) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** Integer Break for n=10. Apply the greedy formula.
<details><summary>Reveal</summary>
10 = 3+3+4. Product = 3×3×4 = 36. Or: 3×3×2×2=36. Formula: 10%3=1 → threes=(10/3-1)=2, use 2×2 for remainder: 3²×4=36. Answer: 36.
</details>

**Drill 2:** Minimum moves to equal [1,2,3]. Why is median (2) optimal?
<details><summary>Reveal</summary>
Moves to target=1: |1-1|+|2-1|+|3-1|=3. Target=2: 1+0+1=2. Target=3: 2+1+0=3. Mean=2 (coincidence here). Median=2. |1-2|+|2-2|+|3-2|=2. Median minimizes L1 distance by calculus — derivative of sum of absolute values is 0 at median.
</details>

**Drill 3:** Minimum swaps to sort [4,3,2,1]. Count cycles.
<details><summary>Reveal</summary>
Sorted: [1,2,3,4]. Mapping: 4→pos0→should be at pos3; 3→pos1→should be at pos2; 2→pos2→should be at pos1; 1→pos3→should be at pos0. Cycle 1: 0→3→0 (length 2, needs 1 swap). Cycle 2: 1→2→1 (length 2, needs 1 swap). Total swaps = 2.
</details>

**Drill 4:** Maximize sum after k=4 negations: nums=[3,-1,0,2]. Sort by abs desc: [3,2,-1,0]. Flip negatives: flip -1 → [3,2,1,0], k=3. k odd, flip smallest (0) doesn't change sum. Sum=6. What if last flip matters?
<details><summary>Reveal</summary>
After flipping -1: [3,2,1,0], k=3 remaining (odd). Smallest absolute value = 0 (last). Sum = 6. If k odd: sum - 2*0 = 6. Same answer. If smallest was 1: sum - 2*1 = 4. The `2*smallest` formula correctly handles any case.
</details>

**Drill 5:** K-th Grammar: why is k even → flip of parent?
<details><summary>Reveal</summary>
The grammar rule: 0 → 01, 1 → 10. So every left child = parent's value, every right child = 1 - parent's value. k-th element of row N: parent = ((k+1)/2)-th element of row N-1. If k is even, it's a right child → flipped. If k is odd, left child → same.
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Space |
|---------|------|-------|
| Integer Break | O(log n) | O(1) |
| Min Moves to Equal | O(n log n) | O(1) |
| Swaps to Sort (cycles) | O(n log n) | O(n) |
| K Negations | O(n log n) | O(1) |
| Matrix Score | O(R×C) | O(1) |

---

## 9. Common Follow-up Questions

**Q: Integer break — why not use 2s instead of 3s?**
A: For large n, 3/ln(3) > 2/ln(2), meaning 3s pack more "product per unit sum." Specifically: 3² = 9 > 2³ = 8 (same sum 6). So 3 is more efficient.

**Q: Minimum moves when you can only increment? (not decrement)**
A: Move everything to the max, but use modular trick: moving to max - (difference mod n) equivalently. O(n) math.

**Q: Can you solve Integer Break with DP?**
A: Yes: `dp[i] = max(j * (i-j), j * dp[i-j])` for j in [1, i-1]. O(n²). Greedy is O(log n).

---

## 10. Cross-Pattern Connections

- **P30 (1D DP):** Integer break, min moves, etc. all have DP formulations; greedy is faster
- **P70 (Bit Manipulation):** Matrix Score uses XOR for toggling; bit tricks overlap
- **P53 (Interval Scheduling):** Both use mathematical proof of greedy optimality
- **P04 (Two Pointers):** Two-pointer patterns appear in min-moves problems on sorted arrays
