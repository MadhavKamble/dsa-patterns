# 🔥 Minimum Days to Make M Bouquets

> **LeetCode #1482** · **Difficulty:** Medium · **Step 4 — Binary Search · P21**

---

## 🧠 Problem Understanding

**What is it asking?**
Given an array `bloomDay` where `bloomDay[i]` is the day flower `i` blooms, and integers `m` (number of bouquets needed) and `k` (flowers per bouquet, must be **adjacent**), find the **minimum number of days** to make `m` bouquets. Return -1 if impossible.

**Input:** `bloomDay = [1,10,3,10,2]`, `m = 3`, `k = 1` → **Output:** `3`
**Input:** `bloomDay = [1,10,3,10,2]`, `m = 3`, `k = 2` → **Output:** `-1` (only 5 flowers, need 6)
**Input:** `bloomDay = [7,7,7,7,12,7,7]`, `m = 2`, `k = 3` → **Output:** `12`

**Constraints:** `1 ≤ bloomDay.length ≤ 10⁵`, `1 ≤ m × k ≤ bloomDay.length`, days up to 10⁹

**Key Observations:**
- Impossible if `m × k > N` — not enough flowers total
- More days = more flowers bloomed = easier to make bouquets (monotone!)
- Search on number of days D: can we make M bouquets on day D?
- Feasibility: count consecutive bloomed flowers (≤ D), form groups of K, count bouquets

**Simple Example:**
```
bloomDay=[7,7,7,7,12,7,7], m=2, k=3
Day 7: flowers 0,1,2,3,5,6 bloom (not 4)
  Consecutive groups of 3: [0,1,2]=1 bouquet, [3,5,6]? No — not consecutive!
  So only 1 bouquet on day 7.
Day 12: flower 4 also blooms
  Groups: [0,1,2,3]=1+, [4,5,6]=1 → 2 bouquets ≥ 2 ✓
Answer: 12
```

---

## 🥉 Brute Force Approach

### Idea
Try every possible day from 1 to max(bloomDay). Return the first day that works.

### Complexity
- **Time:** O(max(bloomDay) × N) — too slow
- **Space:** O(1)

---

## 🥇 Optimal Approach — Binary Search on Days

### Key Observation

> 💡 **Monotone property:** If we can make M bouquets on day D, we can also make them on any day D' > D (more flowers bloomed). This enables binary search.
>
> **Search space:** `[1, max(bloomDay)]`
>
> **Feasibility check** on day D:
> - Scan array; count consecutive flowers with `bloomDay[i] ≤ D`
> - When consecutive count reaches K, that's one complete bouquet; reset count
> - If total bouquets ≥ M: feasible

### Algorithm
1. If `m * k > N`: return -1 (impossible)
2. `lo = 1`, `hi = max(bloomDay)`
3. While `lo < hi`:
   - `mid = lo + (hi - lo) / 2`
   - If `canMakeBouquets(bloomDay, m, k, mid)`: `hi = mid`
   - Else: `lo = mid + 1`
4. Return `lo`

### Dry Run

**Input:** `bloomDay = [1, 10, 3, 10, 2]`, `m = 3`, `k = 1`

Impossible check: 3×1=3 ≤ 5 ✓
`lo = 1`, `hi = 10`

| lo | hi | mid | Bouquets on day mid | ≥3? | Action |
|----|-----|-----|---------------------|-----|--------|
| 1 | 10 | 5 | Day5: bloomed=[1,3,2]→indices 0,2,4. Groups of 1: 3 bouquets | ✅ | hi=5 |
| 1 | 5 | 3 | Day3: bloomed=[1,3,2]→indices 0,2,4. 3 bouquets | ✅ | hi=3 |
| 1 | 3 | 2 | Day2: bloomed=[1,2]→indices 0,4. 2 bouquets | ❌ | lo=3 |
| lo=3==hi=3 → **return 3** ✅ |

### Complexity
- **Time:** O(N × log(max(bloomDay)))
- **Space:** O(1)

---

## 🎤 Interview Explanation Script

> "First, handle the impossible case: if `m × k > N`, we don't have enough flowers regardless of how many days pass."

> "Otherwise, the key insight is monotonicity: more days means more flowers bloomed, which can only help in making bouquets. This lets us binary search on the number of days."

> "For the feasibility check at day D: I scan the array, counting consecutive flowers that have bloomed (bloomDay[i] ≤ D). Whenever consecutive count reaches K, I've made one bouquet. If total bouquets ≥ M, the day is feasible."

> "Search space is [1, max(bloomDay)]. The minimum feasible day is the answer."

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * MINIMUM DAYS TO MAKE M BOUQUETS — binary search on days
 *
 * PROBLEM UNDERSTANDING:
 *   Flowers bloom on given days. Need M bouquets of K adjacent flowers each.
 *   Find minimum day D when M bouquets are possible.
 *
 * KEY OBSERVATION:
 *   More days → more flowers bloomed → easier to form bouquets (monotone).
 *   Binary search on D in [1, max(bloomDay)].
 *
 * FEASIBILITY: on day D, count consecutive groups of K bloomed flowers.
 *   Bloomed: bloomDay[i] <= D. Reset count on non-bloomed flower.
 *
 * EDGE CASE: m * k > n → impossible, return -1.
 *
 * COMPLEXITY: Time O(N log max_day) | Space O(1)
 */
class Solution {
private:
    bool canMake(vector<int>& bloomDay, int m, int k, int day) {
        int bouquets = 0, consecutive = 0;
        for (int d : bloomDay) {
            if (d <= day) {
                consecutive++;
                if (consecutive == k) {
                    bouquets++;         // completed one bouquet
                    consecutive = 0;    // reset for next bouquet
                }
            } else {
                consecutive = 0;        // chain broken
            }
        }
        return bouquets >= m;
    }

public:
    int minDays(vector<int>& bloomDay, int m, int k) {
        long long total = (long long)m * k;
        if (total > bloomDay.size()) return -1;  // impossible

        int lo = 1;
        int hi = *max_element(bloomDay.begin(), bloomDay.end());

        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (canMake(bloomDay, m, k, mid))
                hi = mid;        // feasible, try fewer days
            else
                lo = mid + 1;    // not feasible, need more days
        }

        return lo;
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "BS on days [1, max(bloomDay)]. Feasibility: consecutive groups of K bloomed flowers ≥ M. `m*k > N` → impossible."

---

## 📝 Short Revision Notes

- Impossible check: `(long long)m * k > bloomDay.size()` — use long long
- Search space: [1, max(bloomDay)]
- Feasibility: greedy consecutive count, reset on unbloomed flower
- Template: find minimum → `lo < hi`, valid → `hi = mid`, invalid → `lo = mid+1`
- Bouquet requires K **consecutive** bloomed flowers — adjacency is key

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "Minimum days/time to achieve X"
- "Consecutive grouping condition"
- "Monotone: more days → strictly better"

**I should think of:** Binary search on answer (days/time)

---

## ⚠️ Common Mistakes

❌ Not checking `m * k > N` → returns wrong answer instead of -1  
❌ Integer overflow: `m * k` for large m, k → use `long long`  
❌ Not resetting `consecutive = 0` when flower hasn't bloomed  
❌ Using `>= k` instead of `== k` (extra flowers don't form a new bouquet mid-count — must reset)  

---

## 🔥 What Interviewer Is Testing

- **Concept:** Monotone feasibility → binary search on answer
- **Reasoning:** Consecutive grouping in feasibility check
- **Edge case:** Impossibility when `m * k > N`

---

## 📚 Related Problems

- [ ] LeetCode #1482 — Minimum Number of Days to Make m Bouquets
- [ ] LeetCode #875 — Koko Eating Bananas (P20 — same template)
- [ ] LeetCode #1011 — Ship Packages (P23)
- [ ] LeetCode #1283 — Smallest Divisor (P22)

---

## 🏆 Pattern Category

`Binary Search` · `Search Space` · `Greedy Feasibility`

---

## ⏱️ 30-Second Last-Minute Revision

> **Check:** `m*k > N` → return -1. **BS** [1, max(bloomDay)]. Feasibility: count consecutive bloomed groups of K. If bouquets≥m → `hi=mid`. Else `lo=mid+1`. Return lo.
