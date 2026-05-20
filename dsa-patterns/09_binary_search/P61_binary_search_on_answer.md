# P61 — Binary Search on Answer

## 1. First-Timer Explanation

### What Is It?
**Binary search on the answer** applies binary search not to an array index, but to the **value of the answer itself**. If you can:
1. Define a range of possible answers [lo, hi]
2. Write a feasibility check `canAchieve(mid)` that's monotone (once true, always true for larger/smaller mid)

Then you can binary search for the optimal answer in O(log(hi-lo)) × O(check time).

### The Pattern
```
"Find the minimum X such that condition(X) is true"
→ Binary search on X in [lo, hi]
→ For each mid, check if condition(mid) holds
→ If yes: hi = mid (maybe smaller works)
→ If no: lo = mid + 1 (need larger)
```

### Visual Walkthrough — Koko Eating Bananas
```
Piles = [3, 6, 7, 11], h = 8
"Find minimum eating speed k so Koko finishes in h hours"

Speed k: 1 → hours needed = 3+6+7+11 = 27 > 8 → too slow
Speed k: 11 → hours = 1+1+1+1 = 4 ≤ 8 → fast enough

Binary search on speed [1, 11]:
mid=6: hours = ceil(3/6)+ceil(6/6)+ceil(7/6)+ceil(11/6) = 1+1+2+2=6 ≤ 8 → hi=6
mid=3: hours = 1+2+3+4=10 > 8 → lo=4
mid=5: hours = 1+2+2+3=8 ≤ 8 → hi=5
mid=4: hours = 1+2+2+3=8 ≤ 8 → hi=4
lo==hi=4 → minimum speed = 4 ✓
```

### Identifying the Pattern
Ask: "If mid works, does mid+1 always work too?" (or "mid-1?")
- If yes → monotone → binary search on answer

### When to Use
- "Minimum/maximum X such that..." → binary search on X
- "Can we achieve Y in Z steps/units?" + optimize → binary search
- O(n log n) or O(n) feasibility check + large answer range → binary search over brute force

### Common Mistakes
1. Not identifying the monotone property
2. Wrong bounds [lo, hi] — too narrow misses answers
3. Integer ceiling: `(a + b - 1) / b` not `a / b` when computing hours/batches
4. Overflow: answer range might require long long

---

## 2. Revision Card

**Recognition Signal:** "minimum X to achieve Y", "feasibility check + optimize", answer is a value in a range

**Core Idea:** Binary search on the answer space [lo, hi]. `check(mid)` = can we achieve the goal with mid? Monotone → convergence.

**Trigger Keywords:** minimum speed, maximum pages, minimum time, capacity, feasibility, threshold

**Complexity:** O(n log(answer_range)) — n for check, log for search

---

## 3. Interview Tell Signs

- "Find the minimum capacity/speed/time to accomplish X" → binary search on answer
- "Split array into K parts, minimize max part sum" → check: can K parts all have sum ≤ mid?
- "Allocate books/pages among K students, minimize max" → same pattern
- "Koko eating bananas / ship packages in D days" → classic examples

---

## 4. C++ Template

```cpp
#include <vector>
#include <algorithm>
using namespace std;

// ── Generic Binary Search on Answer ──────────────────────────────────────────
// Returns minimum X in [lo, hi] such that check(X) is true
// Assumes: check(lo) might be false, check(hi) is true
template<typename F>
int binarySearchOnAnswer(int lo, int hi, F check) {
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (check(mid)) hi = mid; // mid works, try smaller
        else lo = mid + 1;       // mid doesn't work, need larger
    }
    return lo;
}

// ── Koko Eating Bananas ───────────────────────────────────────────────────────
int minEatingSpeed(vector<int>& piles, int h) {
    int lo = 1, hi = *max_element(piles.begin(), piles.end());
    
    auto canFinish = [&](int speed) {
        long long hours = 0;
        for (int p : piles) hours += (p + speed - 1) / speed; // ceiling division
        return hours <= h;
    };
    
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (canFinish(mid)) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}
```

---

## 5. How to Present in Interview

**Verbal Script:**
> "This is binary search on the answer. The answer (e.g., eating speed) has a range [1, max_pile]. For any speed, I can check feasibility in O(n) by computing total hours. The key property: if speed k works, any higher speed also works — so the feasibility check is monotone. I binary search on speed: if mid works, try smaller (hi=mid); if not, need larger (lo=mid+1). O(n log(max_pile))."

**Checklist:**
- [ ] Identify answer range [lo, hi]
- [ ] Write `check(mid)` — can we achieve goal with mid?
- [ ] Verify monotone: if mid works, does mid+1 always work?
- [ ] Use ceiling division when needed: `(a + b - 1) / b`
- [ ] State total time: O(n log(range))

---

## 6. Problems

### Problem 1: Koko Eating Bananas
**Difficulty:** Medium | **LC:** 875

```cpp
int minEatingSpeed(vector<int>& piles, int h) {
    int lo = 1, hi = *max_element(piles.begin(), piles.end());
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        long long hours = 0;
        for (int p : piles) hours += (p + mid - 1) / mid;
        if (hours <= h) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}
// Time: O(n log(max_pile)) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Capacity to Ship Packages Within D Days
**Difficulty:** Medium | **LC:** 1011

**Approach:** Binary search on capacity [max_weight, sum_weight]. Check: can all packages be shipped in D days with capacity mid?

```cpp
int shipWithinDays(vector<int>& weights, int days) {
    int lo = *max_element(weights.begin(), weights.end());
    int hi = accumulate(weights.begin(), weights.end(), 0);
    
    auto canShip = [&](int cap) {
        int d = 1, cur = 0;
        for (int w : weights) {
            if (cur + w > cap) { d++; cur = 0; }
            cur += w;
        }
        return d <= days;
    };
    
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (canShip(mid)) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}
// Time: O(n log(sum)) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Split Array Largest Sum
**Difficulty:** Hard | **LC:** 410

**Approach:** Binary search on max subarray sum [max_elem, total_sum]. Check: can array be split into ≤ k subarrays each with sum ≤ mid?

```cpp
int splitArray(vector<int>& nums, int k) {
    int lo = *max_element(nums.begin(), nums.end());
    long long hi = accumulate(nums.begin(), nums.end(), 0LL);
    
    auto canSplit = [&](long long cap) {
        int parts = 1; long long cur = 0;
        for (int x : nums) {
            if (cur + x > cap) { parts++; cur = 0; }
            cur += x;
        }
        return parts <= k;
    };
    
    while (lo < hi) {
        long long mid = lo + (hi - lo) / 2;
        if (canSplit(mid)) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}
// Time: O(n log(sum)) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Minimize Max Distance to Gas Station
**Difficulty:** Hard | **LC:** 774

**Approach:** Binary search on the max gap distance. Feasibility: how many stations needed to reduce all gaps to ≤ mid?

```cpp
int minmaxGasDist(vector<int>& stations, int k) {
    double lo = 0, hi = stations.back() - stations[0];
    
    auto check = [&](double maxGap) {
        int added = 0;
        for (int i = 1; i < (int)stations.size(); i++) {
            double gap = stations[i] - stations[i-1];
            added += (int)(gap / maxGap); // how many stations to add
        }
        return added <= k;
    };
    
    for (int iter = 0; iter < 100; iter++) { // float binary search
        double mid = (lo + hi) / 2;
        if (check(mid)) hi = mid;
        else lo = mid;
    }
    return lo; // 10^-6 precision
}
// Time: O(n * 100) = O(n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Kth Smallest Number in Multiplication Table
**Difficulty:** Hard | **LC:** 668

**Approach:** Binary search on value [1, m×n]. Count numbers ≤ mid in the multiplication table.

```cpp
int findKthNumber(int m, int n, int k) {
    int lo = 1, hi = m * n;
    
    auto count = [&](int mid) {
        int cnt = 0;
        for (int i = 1; i <= m; i++) cnt += min(mid/i, n); // row i: values i, 2i, ..., n*i
        return cnt;
    };
    
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (count(mid) >= k) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}
// Time: O(m log(m*n)) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: Find the Smallest Divisor Given a Threshold
**Difficulty:** Medium | **LC:** 1283

```cpp
int smallestDivisor(vector<int>& nums, int threshold) {
    int lo = 1, hi = *max_element(nums.begin(), nums.end());
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        long long sum = 0;
        for (int x : nums) sum += (x + mid - 1) / mid;
        if (sum <= threshold) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}
// Time: O(n log(max)) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** "Minimum speed for Koko." Why is hi = max_pile (not sum)?
<details><summary>Reveal</summary>
At speed = max_pile, Koko eats every pile in 1 hour, finishing all piles in exactly n hours. That's always sufficient (we need ≤ h hours, and h ≥ n in all valid inputs). A higher speed gives no benefit since 1 hour per pile is the minimum for any single pile.
</details>

**Drill 2:** Canship check for D days: why start `d = 1` and not `d = 0`?
<details><summary>Reveal</summary>
We always need at least 1 day. Starting with d=1 represents the first day's shipment. When adding a new package would exceed capacity, we start a new day (d++). At the end, we've used d days total.
</details>

**Drill 3:** Split Array: why is `lo = max_element` and not `lo = 1`?
<details><summary>Reveal</summary>
Each subarray must contain at least one element. If the maximum element is 10, no valid split allows a subarray sum less than 10. Setting lo = max_element ensures we never check infeasible lower bounds, making convergence faster.
</details>

**Drill 4:** For float binary search (gas station), why 100 iterations instead of a termination condition?
<details><summary>Reveal</summary>
Floating point `lo < hi` can have precision issues. After 100 iterations, the range [lo, hi] is narrowed by 2^100 ≈ 10^30 times, giving ≈ 10^-24 precision (far beyond any requirement). It's simpler and safer than comparing floats with epsilon.
</details>

**Drill 5:** Kth in multiplication table: explain `min(mid/i, n)` in the count function.
<details><summary>Reveal</summary>
In row i, the values are i, 2i, 3i, ..., n×i. Values ≤ mid: we need j×i ≤ mid → j ≤ mid/i. Since j ≤ n (at most n columns), the count for row i is min(mid/i, n). Summing over all m rows gives total count of values ≤ mid.
</details>

---

## 8. Complexity Cheatsheet

| Problem | Check O | Search O | Total |
|---------|---------|----------|-------|
| Koko Eating | O(n) | O(log M) | O(n log M) |
| Ship Packages | O(n) | O(log S) | O(n log S) |
| Split Array | O(n) | O(log S) | O(n log S) |
| Kth in Mult Table | O(m) | O(log(mn)) | O(m log(mn)) |
| Gas Station (float) | O(n) | 100 iters | O(100n) |

M = max value, S = sum

---

## 9. Common Follow-up Questions

**Q: How do you know the answer is exactly at lo when the loop ends?**
A: By the invariant: at every step, `check(hi)` is true and `check(lo-1)` is false (or lo is the minimum). Since lo=hi when we exit, that's the minimum X where check is true.

**Q: What if the check function is expensive (O(n log n))?**
A: Total is O(n log n × log(range)). Usually still acceptable. Consider if there's a closed-form check.

**Q: Can you binary search on a non-integer answer?**
A: Yes — use float binary search with fixed iterations (100 typically gives 10^-30 precision). Alternatively, parametrize and binary search on rational fractions.

---

## 10. Cross-Pattern Connections

- **P59 (Binary Search Basics):** Same template; here applied to answer space not array
- **P60 (Rotated Array):** Also binary search, but on array index
- **P39 (Matrix Chain DP):** Split Array is also solvable with DP O(n²k); binary search is O(n log sum)
- **P53 (Interval Scheduling):** Greedy check inside binary search on time
