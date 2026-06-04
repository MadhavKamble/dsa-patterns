# 🔥 Binary Search on Answer — Classic Problems (P20–P23)

> **LeetCode #875, #1482, #1283, #1011** · **Difficulty:** Medium · **Step 4 — P20–P23**

---

## 🧠 The Pattern

All four problems follow the same template:

```
1. Identify the search space [lo, hi]
2. Define a feasibility check: "can we achieve X with this answer?"
3. Binary search: find minimum/maximum X where feasible(X) = true
```

---

# P20 — Koko Eating Bananas

> **LeetCode #875**

**Problem:** Given piles of bananas and H hours, find the minimum eating speed K such that Koko can eat all bananas in ≤ H hours.

**Feasibility:** At speed K, hours needed = Σ⌈pile[i]/K⌉. Is this ≤ H?

**Search space:** K ∈ [1, max(piles)]

```cpp
/*
 * KOKO EATING BANANAS — minimum speed to finish in H hours
 * Feasibility: total_hours(K) <= H
 * Binary search on speed K
 * Time O(N log max_pile) | Space O(1)
 */
class Solution {
    bool canFinish(vector<int>& piles, long long speed, int h) {
        long long hours = 0;
        for (int pile : piles)
            hours += (pile + speed - 1) / speed;  // ceil(pile/speed)
        return hours <= h;
    }
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int lo = 1, hi = *max_element(piles.begin(), piles.end());
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (canFinish(piles, mid, h)) hi = mid;   // valid, try smaller
            else lo = mid + 1;                         // too slow, need faster
        }
        return lo;
    }
};
```

---

# P21 — Minimum Days to Make M Bouquets

> **LeetCode #1482**

**Problem:** Given bloom days and bouquet size K, find minimum days to make M bouquets. Each bouquet needs K consecutive bloomed flowers.

**Feasibility:** On day D, count consecutive bloomed flowers, count complete bouquets of size K. Is count ≥ M?

**Search space:** D ∈ [1, max(bloomDay)]

```cpp
class Solution {
    bool canMakeBouquets(vector<int>& bloomDay, int m, int k, int day) {
        int bouquets = 0, consecutive = 0;
        for (int d : bloomDay) {
            if (d <= day) {
                consecutive++;
                if (consecutive == k) { bouquets++; consecutive = 0; }
            } else {
                consecutive = 0;
            }
        }
        return bouquets >= m;
    }
public:
    int minDays(vector<int>& bloomDay, int m, int k) {
        if ((long long)m * k > bloomDay.size()) return -1;  // impossible
        int lo = 1, hi = *max_element(bloomDay.begin(), bloomDay.end());
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (canMakeBouquets(bloomDay, m, k, mid)) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }
};
```

---

# P22 — Find the Smallest Divisor

> **LeetCode #1283**

**Problem:** Find smallest divisor such that sum of all ⌈arr[i]/divisor⌉ ≤ threshold.

**Search space:** divisor ∈ [1, max(arr)]

```cpp
class Solution {
    bool feasible(vector<int>& nums, int div, int threshold) {
        long long sum = 0;
        for (int x : nums) sum += (x + div - 1) / div;
        return sum <= threshold;
    }
public:
    int smallestDivisor(vector<int>& nums, int threshold) {
        int lo = 1, hi = *max_element(nums.begin(), nums.end());
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (feasible(nums, mid, threshold)) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }
};
```

---

# P23 — Capacity to Ship Packages within D Days

> **LeetCode #1011**

**Problem:** Find minimum ship capacity to ship all packages within D days. Must ship in order.

**Search space:** capacity ∈ [max(weights), sum(weights)]  
`lo = max weight` (must fit heaviest package)  
`hi = total weight` (ship everything in 1 day)

```cpp
class Solution {
    bool canShip(vector<int>& weights, int capacity, int days) {
        int daysNeeded = 1, currentLoad = 0;
        for (int w : weights) {
            if (currentLoad + w > capacity) {
                daysNeeded++;           // new day
                currentLoad = 0;
            }
            currentLoad += w;
        }
        return daysNeeded <= days;
    }
public:
    int shipWithinDays(vector<int>& weights, int days) {
        int lo = *max_element(weights.begin(), weights.end());
        int hi = accumulate(weights.begin(), weights.end(), 0);
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (canShip(weights, mid, days)) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }
};
```

---

## 🎤 Interview Explanation Script (applies to all 4)
> "These are all 'binary search on answer' problems. The key insight: instead of searching in the array, I binary search over the **answer space**."

> "I identify: what's the minimum/maximum answer? What's the maximum? Then I write a feasibility function: 'given this answer, is it achievable?' This function is monotone — if X works, X+1 also works. So I binary search for the minimum valid X."

---

## 🧾 Recall Lines

| Problem | lo | hi | Feasibility check |
|---------|----|----|------------------|
| Koko | 1 | max(piles) | total hours ≤ H |
| Bouquets | 1 | max(bloom) | consecutive groups ≥ M |
| Divisor | 1 | max(arr) | ceil sum ≤ threshold |
| Ship | max(w) | sum(w) | days needed ≤ D |

## 📝 Key Notes
- Template: `while lo < hi: if feasible(mid) hi=mid else lo=mid+1`
- Return `lo` (minimum valid answer)
- `ceil(a/b)` in integer: `(a + b - 1) / b`
- Always check edge case: M*K > N for bouquets → impossible

## ⚠️ Common Mistakes
❌ `lo = 0` when 0 capacity/speed is meaningless  
❌ `while lo <= hi` instead of `lo < hi` for "find minimum" BS  
❌ `hi = mid - 1` instead of `hi = mid` when mid is a valid answer  
❌ Integer overflow in `m * k` check (P21) — use `long long`

## 🏆 Pattern Category
`Binary Search` · `Search Space` · `Greedy Feasibility`

## ⏱️ 30-Second Revision
> All 4: `lo < hi`. `feasible(mid)` → `hi = mid`. Else `lo = mid+1`. Return lo. Key: monotone feasibility on answer range.
