# 🔥 Koko Eating Bananas

> **LeetCode #875** · **Difficulty:** Medium · **Step 4 — Binary Search · P16**

---

## 🧠 Problem Understanding

**What is it asking?**
Koko eats bananas at a chosen integer speed `k` per hour. Each hour she eats from a single pile; if a pile has fewer than `k` bananas she finishes it and waits out the hour. Find the **minimum speed** that finishes all piles within `h` hours.

**Input:** `piles = [3, 6, 7, 11]`, `h = 8` → **Output:** `4`
**Input:** `piles = [30, 11, 23, 4, 20]`, `h = 5` → **Output:** `30`

**Key Observation:**
- We search over **speed** (a value), not an index.
- **Monotonic:** higher speed → fewer hours needed. So "can she finish in `h` hours?" flips from `false` to `true` exactly once as speed rises.
- Hours at speed `k` = `Σ ceil(pile / k)`.

---

## 🎯 Interview Progression

### 🥉 Brute Force — Try Every Speed

Loop `k = 1, 2, ... max(pile)`, return the first `k` that finishes in `h` hours. **Time:** O(max(pile) · n).

---

### 🥇 Optimal — Binary Search on Speed

> 💡 Search space `[1, max(pile)]`. If speed `mid` finishes in time, it's a candidate → try slower (`high = mid-1`); otherwise go faster (`low = mid+1`).

```cpp
class Solution {
public:
    bool canFinish(vector<int>& piles,int h,int speed){
        long long hours=0;
        for(int pile:piles){
            hours+=(pile+speed-1)/speed;
        }
        return hours<=h;
    }
    int minEatingSpeed(vector<int>& piles,int h){
        int low=1;
        int high=*max_element(piles.begin(),piles.end());
        int ans=high;
        while(low<=high){
            int mid=low+(high-low)/2;
            if(canFinish(piles,h,mid)){
                ans=mid;
                high=mid-1;
            }else{
                low=mid+1;
            }
        }
        return ans;
    }
};
```

**Time:** O(n · log(max(pile))) · **Space:** O(1).

### Dry Run
`piles = [3, 6, 7, 11]`, `h = 8`, search `[1, 11]`

| low | high | mid | hours = Σceil(pile/mid) | ≤8? | ans | Action |
|-----|------|-----|--------------------------|-----|-----|--------|
| 1 | 11 | 6 | 1+1+2+2 = 6 | ✅ | 6 | high=5 |
| 1 | 5 | 3 | 1+2+3+4 = 10 | ❌ | 6 | low=4 |
| 4 | 5 | 4 | 1+2+2+3 = 8 | ✅ | 4 | high=3 |
| 4 | 3 | — | — | — | 4 | **return 4** ✅ |

---

## 🧾 Recall Line *(10-Second Revision)*

> "BS on speed `[1, max(pile)]`. `hours = Σceil(pile/speed)`. Feasible → shrink (try slower), else faster."

---

## 📝 Short Revision Notes

- `ceil(pile/speed)` without floats: `(pile + speed - 1) / speed`.
- Search space is `[1, max(pile)]` — never need to exceed the biggest pile.
- Accumulate `hours` in `long long` to avoid overflow.
- Feasible predicate is monotonic → standard "minimize feasible value" binary search.

---

## ⚠️ Common Mistakes

❌ Using floating `ceil` → precision bugs; use integer `(x+d-1)/d`.
❌ `int` overflow when summing hours for many/large piles.
❌ Upper bound larger than `max(pile)` — wasteful (and speed beyond that never helps).

---

## 🧠 Pattern Recognition Trigger

**When I see:** "minimum rate/speed to finish within a limit", "monotonic feasibility" → **binary search on the answer**.

---

## 🏆 Pattern Category

`Binary Search on Answer` · `Feasibility Predicate`

---

## ⏱️ 30-Second Last-Minute Revision

> **BS speed `[1, max]`.** `hours=Σceil(pile/speed)`. `hours<=h` → try slower; else faster. Minimize. `O(n·log max)`.
