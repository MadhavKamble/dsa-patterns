# 🔥 Koko Eating Bananas

> **LeetCode #875** · **Difficulty:** Medium · **Step 4 — Binary Search · P20**

---

## 🧠 Problem Understanding

**What is it asking?**
Koko has N piles of bananas and H hours before guards return. She can eat at speed K bananas/hour. Each hour she picks one pile and eats up to K bananas from it (can't switch piles mid-hour). Find the **minimum eating speed K** to finish all bananas within H hours.

**Input:** `piles = [3, 6, 7, 11]`, `h = 8` → **Output:** `4`
**Input:** `piles = [30, 11, 23, 4, 20]`, `h = 5` → **Output:** `30`
**Input:** `piles = [30, 11, 23, 4, 20]`, `h = 6` → **Output:** `23`

**Constraints:** `1 ≤ len(piles) ≤ 10⁴`, `1 ≤ h ≤ 10⁹`, `1 ≤ piles[i] ≤ 10⁹`

**Key Observations:**
- At speed K, hours for pile `p` = `ceil(p / K)` = `(p + K - 1) / K`
- If speed K works, any speed > K also works (monotone property → binary search!)
- Search space: K ∈ [1, max(piles)] (minimum: 1 banana/hour; maximum: largest pile in one hour)

**Simple Example:**
```
piles=[3,6,7,11], h=8
At K=4: hours = ceil(3/4)+ceil(6/4)+ceil(7/4)+ceil(11/4) = 1+2+2+3 = 8 ≤ 8 ✓
At K=3: hours = 1+2+3+4 = 10 > 8 ✗
Answer: 4
```

---

## 🥉 Brute Force Approach

### Idea
Try every speed from 1 to max(piles). Return the first speed that works.

### Algorithm
1. For K from 1 to max(piles):
   - Compute total hours at speed K
   - If total hours ≤ H: return K

### Complexity
- **Time:** O(max(piles) × N) — too slow for piles[i] up to 10⁹
- **Space:** O(1)

---

## 🥇 Optimal Approach — Binary Search on Speed

### Key Observation

> 💡 The feasibility function is **monotone**: if speed K allows Koko to finish in H hours, then any speed K' > K also works. This monotone property enables binary search on the speed.
>
> **Search space:** [1, max(piles)]
> - `lo = 1`: slowest possible speed
> - `hi = max(piles)`: fastest needed (eats largest pile in 1 hour, rest in ≤ 1 hour each)
>
> Find the **leftmost valid** K (minimum speed that works).

### Algorithm
1. `lo = 1`, `hi = max(piles)`
2. While `lo < hi`:
   - `mid = lo + (hi - lo) / 2`
   - Compute `hours = Σ ceil(pile / mid)` for all piles
   - If `hours <= H`: valid speed → try smaller: `hi = mid`
   - Else: too slow → need faster: `lo = mid + 1`
3. Return `lo`

### Dry Run

**Input:** `piles = [3, 6, 7, 11]`, `h = 8`
`lo = 1`, `hi = 11`

| lo | hi | mid | Hours at mid | ≤ 8? | Action |
|----|-----|-----|-------------|------|--------|
| 1 | 11 | 6 | ⌈3/6⌉+⌈6/6⌉+⌈7/6⌉+⌈11/6⌉=1+1+2+2=6 | ✅ | hi=6 |
| 1 | 6 | 3 | ⌈3/3⌉+⌈6/3⌉+⌈7/3⌉+⌈11/3⌉=1+2+3+4=10 | ❌ | lo=4 |
| 4 | 6 | 5 | ⌈3/5⌉+⌈6/5⌉+⌈7/5⌉+⌈11/5⌉=1+2+2+3=8 | ✅ | hi=5 |
| 4 | 5 | 4 | ⌈3/4⌉+⌈6/4⌉+⌈7/4⌉+⌈11/4⌉=1+2+2+3=8 | ✅ | hi=4 |
| lo=4==hi=4 → **return 4** ✅ |

### Complexity
- **Time:** O(N × log(max(piles))) — O(log(max)) iterations × O(N) per check
- **Space:** O(1)

### Why `lo < hi` and `hi = mid`?
We want the **minimum valid** speed. When a speed works, we record it (via `hi = mid`) and try smaller. When `lo == hi`, we've found the minimum.

---

## 🎤 Interview Explanation Script

> "The brute force tries every speed from 1 to max(piles). That's too slow — piles can be up to 10⁹."

> "The key insight: if speed K works, speed K+1 also works. This monotone property lets us binary search."

> "The search space for speed is [1, max(piles)]. We don't need to go higher than max(piles) because at that speed, every pile takes at most 1 hour. We binary search for the minimum K where total hours ≤ H."

> "For feasibility, at speed K, hours for pile p is `ceil(p/K) = (p+K-1)/K`. Sum across all piles and compare to H."

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * KOKO EATING BANANAS — binary search on eating speed
 *
 * PROBLEM UNDERSTANDING:
 *   Find minimum speed K to eat all piles within H hours.
 *   Each pile takes ceil(pile/K) hours.
 *
 * KEY OBSERVATION:
 *   Feasibility is monotone: faster speed → fewer hours.
 *   Binary search on K in [1, max(piles)].
 *
 * FEASIBILITY: total_hours(K) <= H
 *   hours per pile = ceil(p/K) = (p + K - 1) / K
 *
 * BINARY SEARCH TEMPLATE: find minimum valid → lo<hi, hi=mid when valid
 *
 * COMPLEXITY: Time O(N log max_pile) | Space O(1)
 */
class Solution {
private:
    bool canFinish(vector<int>& piles, long long speed, int h) {
        long long hours = 0;
        for (int pile : piles) {
            hours += (pile + speed - 1) / speed;   // ceil(pile/speed)
            if (hours > h) return false;            // early exit
        }
        return hours <= h;
    }

public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int lo = 1;
        int hi = *max_element(piles.begin(), piles.end());

        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (canFinish(piles, mid, h))
                hi = mid;         // valid speed, try to minimize
            else
                lo = mid + 1;     // too slow, need faster
        }

        return lo;
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "BS on speed [1, max(piles)]. `hours = Σceil(pile/K)`. Valid → `hi=mid`. Else `lo=mid+1`. Return lo."

---

## 📝 Short Revision Notes

- Search space: [1, max(piles)] — never need speed > max pile
- `ceil(a/b)` in integers: `(a + b - 1) / b`
- Template: minimize → `lo < hi`, valid → `hi = mid`, invalid → `lo = mid+1`
- Early exit in feasibility: once hours > H, return false (optimization)
- N up to 10⁴, piles up to 10⁹ → log(10⁹) ≈ 30 → 30 × 10⁴ = 300,000 ops

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "Find minimum X such that some condition holds"
- "Minimum rate/speed/capacity"
- "Monotone feasibility on continuous range"

**I should think of:** Binary search on answer space

---

## ⚠️ Common Mistakes

❌ `lo = 0` — speed 0 causes division by zero  
❌ `hi = sum(piles)` — too large, slows binary search  
❌ `while lo <= hi` with `hi = mid - 1` — misses the exact answer  
❌ Not using `long long` for hours accumulation — can overflow for large inputs  

---

## 🔥 What Interviewer Is Testing

- **Concept:** Binary search on answer space (monotone feasibility)
- **Reasoning:** Why [1, max(piles)] is the right search space
- **Implementation:** Correct ceil formula, loop termination

---

## 🚀 Alternative Approaches

| Approach | Time | Space | Notes |
|----------|------|-------|-------|
| Binary search on speed | O(N log max) | O(1) | Optimal |
| Linear scan on speeds | O(N × max) | O(1) | Too slow |

---

## 📚 Related Problems

- [ ] LeetCode #875 — Koko Eating Bananas
- [ ] LeetCode #1011 — Capacity to Ship Packages (P23 — same template)
- [ ] LeetCode #1482 — Minimum Days to Make Bouquets (P21)
- [ ] LeetCode #1283 — Find the Smallest Divisor (P22)

---

## 🏆 Pattern Category

`Binary Search` · `Search Space` · `Greedy Feasibility`

---

## 🎯 Difficulty Analysis

**Rating:** Medium

**Why challenging:** Requires recognizing the monotone feasibility pattern. The search space (1 to max pile) and the ceil formula are the two key implementation details.

---

## 📈 Progression Insight

**Same template:** Capacity to Ship (P23), Book Allocation, Aggressive Cows — all use the exact same binary search structure. Master one, master all.

**Harder:** When feasibility check itself requires binary search → nested binary search O(N log² N)

---

## ⏱️ 30-Second Last-Minute Revision

> **Problem:** Min speed K to eat all piles in H hours  
> **Approach:** BS [1, max(piles)]. `hours = Σ(pile+K-1)/K`. If hours≤H → `hi=mid`. Else `lo=mid+1`. Return lo.  
> **Key trick:** `ceil(a/b) = (a+b-1)/b`; search [1, max] not [1, sum]  
> **Time:** O(N log max) | **Space:** O(1)
