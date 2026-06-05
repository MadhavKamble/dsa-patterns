# 🔥 Capacity to Ship Packages Within D Days

> **LeetCode #1011** · **Difficulty:** Medium · **Step 4 — Binary Search · P23**

---

## 🧠 Problem Understanding

**What is it asking?**
Given the weights of packages (must be shipped in order) and D days, find the **minimum ship capacity** to ship all packages within D days.

**Input:** `weights = [1,2,3,4,5,6,7,8,9,10]`, `days = 5` → **Output:** `15`
**Input:** `weights = [3,2,2,4,1,4]`, `days = 3` → **Output:** `6`
**Input:** `weights = [1,2,3,1,1]`, `days = 4` → **Output:** `3`

**Constraints:** `1 ≤ weights.length ≤ 500`, `1 ≤ days ≤ weights.length`, `1 ≤ weights[i] ≤ 500`

**Key Observations:**
- Packages must be loaded in **given order** (no reordering)
- Each day we load as many consecutive packages as fit within capacity
- Minimum capacity = `max(weights)` (must fit at least the heaviest package)
- Maximum capacity = `sum(weights)` (all in one day)
- More capacity → fewer days needed (monotone property)

**Simple Example:**
```
weights=[1,2,3,4,5,6,7,8,9,10], days=5
At capacity=15:
  Day1: 1+2+3+4+5=15 ✓
  Day2: 6+7=13, next 8>2 remaining → wait
  Day2: 6+7=13, leave 2 for later? No — can't go back
  Day2: 6+7=13 ✓ (13 < 15)
  Day3: 8 ✓
  Day4: 9 ✓
  Day5: 10 ✓
  5 days ✓
At capacity=14:
  Day1: 1+2+3+4+5=15>14, try less: 1+2+3+4=10, next 5: 10+5=15>14
  Day1: 1+2+3+4=10 ✓, then 5+6=11 ✓, then 7+8=15>14, 7 ✓, 8 ✓, 9 ✓, 10 ✓ = 7 days > 5 ✗
Answer: 15
```

---

## 🥉 Brute Force Approach

### Idea
Try every capacity from max(weights) to sum(weights). Return the first valid one.

### Complexity
- **Time:** O(N × sum(weights)) — too slow
- **Space:** O(1)

---

## 🥇 Optimal Approach — Binary Search on Capacity

### Key Observation

> 💡 **Monotone:** Higher capacity → fewer days (monotone decreasing). Binary search for **minimum capacity**.
>
> **Search space:** `[max(weights), sum(weights)]`
> - `lo = max(weights)`: must carry heaviest package in one day
> - `hi = sum(weights)`: carry all packages in one day
>
> **Feasibility:** Greedily fill each day: keep adding packages until next package would exceed capacity → new day.

### Algorithm
1. `lo = max(weights)`, `hi = sum(weights)`
2. While `lo < hi`:
   - `mid = lo + (hi - lo) / 2`
   - `days_needed = countDays(weights, mid)`
   - If `days_needed <= D`: `hi = mid`
   - Else: `lo = mid + 1`
3. Return `lo`

### `countDays(weights, capacity)`:
1. `days = 1`, `currentLoad = 0`
2. For each weight:
   - If `currentLoad + weight > capacity`: `days++`, `currentLoad = 0`
   - `currentLoad += weight`
3. Return `days`

### Dry Run

**Input:** `weights = [3, 2, 2, 4, 1, 4]`, `days = 3`
`lo = 4`, `hi = 16`

| lo | hi | mid | Days needed | ≤3? | Action |
|----|-----|-----|-------------|-----|--------|
| 4 | 16 | 10 | [3,2,2]=7≤10 D1 / [4,1,4]=9≤10 D2 → 2 days | ✅ | hi=10 |
| 4 | 10 | 7 | D1:[3,2,2]=7 / D2:[4,1]=5 / D3:[4]=4 → 3 days | ✅ | hi=7 |
| 4 | 7 | 5 | D1:[3,2]=5 / D2:[2] / D3:[4,1]=5 / D4:[4]=4 → 4 days | ❌ | lo=6 |
| 6 | 7 | 6 | D1:[3,2]=5≤6+[1next]=6 D1:[3,2,?]3+2=5,next:2+2=4≤6 so [3,2,2]=7>6 → D1:[3,2]=5 D2:[2,4]=6 D3:[1,4]=5 → 3 | ✅ | hi=6 |
| lo=6==hi=6 → **return 6** ✅ |

### Complexity
- **Time:** O(N × log(sum(weights)))
- **Space:** O(1)

---

## 🎤 Interview Explanation Script

> "More capacity means fewer days needed — monotone property. So I binary search on capacity."

> "The minimum possible capacity is `max(weights)` — we must fit the heaviest package. The maximum is `sum(weights)` — everything in one day."

> "For the feasibility check: I greedily pack packages left to right. If adding the next package exceeds capacity, I start a new day. Count total days and compare to D."

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * CAPACITY TO SHIP PACKAGES — binary search on capacity
 *
 * PROBLEM UNDERSTANDING:
 *   Ship packages in order. Find minimum capacity to finish in D days.
 *
 * KEY OBSERVATION:
 *   More capacity → fewer days (monotone). Binary search on capacity.
 *   lo = max(weights): must fit heaviest package.
 *   hi = sum(weights): all packages in one day.
 *
 * FEASIBILITY: greedy — fill each day until next package won't fit.
 *
 * COMPLEXITY: Time O(N log sum) | Space O(1)
 */
class Solution {
private:
    int daysNeeded(vector<int>& weights, int capacity) {
        int days = 1, currentLoad = 0;
        for (int w : weights) {
            if (currentLoad + w > capacity) {
                days++;            // start new day
                currentLoad = 0;
            }
            currentLoad += w;
        }
        return days;
    }

public:
    int shipWithinDays(vector<int>& weights, int days) {
        int lo = *max_element(weights.begin(), weights.end());  // must fit heaviest
        int hi = accumulate(weights.begin(), weights.end(), 0); // all in one day

        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (daysNeeded(weights, mid) <= days)
                hi = mid;        // valid capacity, try to minimize
            else
                lo = mid + 1;    // need more capacity
        }

        return lo;
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "BS [max(w), sum(w)]. Greedily fill days: new day when load+w > capacity. daysNeeded≤D → hi=mid. Else lo=mid+1."

---

## 📝 Short Revision Notes

- `lo = max(weights)` not 1 — can't carry a package heavier than capacity
- `hi = sum(weights)` — one day carries everything
- Feasibility: greedy, linear scan, new day on overflow
- Same template as Koko/Bouquets/Divisor: minimize → `lo < hi`, valid → `hi = mid`

---

## ⚠️ Common Mistakes

❌ `lo = 1` — capacity must be at least `max(weights)`  
❌ `hi = max(weights)` — upper bound is `sum(weights)` not max  
❌ `currentLoad = weight` instead of `currentLoad = 0; currentLoad += weight` when starting new day  

---

## 📚 Related Problems

- [ ] LeetCode #1011 — Capacity to Ship Packages Within D Days
- [ ] LeetCode #875 — Koko Eating Bananas (P20 — same template)
- [ ] LeetCode #410 — Split Array Largest Sum (P27 — identical problem)
- [ ] GFG — Book Allocation Problem (P26)

---

## 🏆 Pattern Category

`Binary Search` · `Search Space` · `Greedy Feasibility`

---

## ⏱️ 30-Second Last-Minute Revision

> BS [max(w), sum(w)]. Greedily count days at mid capacity. daysNeeded≤D → `hi=mid`. Else `lo=mid+1`. Return lo.
