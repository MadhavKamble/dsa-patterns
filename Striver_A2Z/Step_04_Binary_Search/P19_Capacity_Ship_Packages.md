# 🔥 Capacity to Ship Packages Within D Days

> **LeetCode #1011** · **Difficulty:** Medium · **Step 4 — Binary Search · P19**

---

## 🧠 Problem Understanding

**What is it asking?**
Packages with given `weights` must ship in order over `days` days. Each day the ship loads packages (in order) up to its capacity. Find the **minimum ship capacity** that ships everything within `days`.

**Input:** `weights = [1,2,3,4,5,6,7,8,9,10]`, `days = 5` → **Output:** `15`
**Input:** `weights = [3,2,2,4,1,4]`, `days = 3` → **Output:** `6`

**Key Observation:**
- We search over **capacity** (a value).
- **Monotonic:** higher capacity → fewer days needed.
- Search space: `low = max(weights)` (must fit the heaviest single package), `high = sum(weights)` (ship everything in one day).

---

## 🎯 Interview Progression

### 🥉 Brute Force — Try Every Capacity

For `cap = max(weights) ... sum(weights)`, simulate and return the first that fits in `days`. **Time:** O(sum · n).

---

### 🥇 Optimal — Binary Search on Capacity

> 💡 `canShip(cap)` greedily fills each day until adding the next package would overflow, then starts a new day. If days used `≤ days`, `cap` is feasible → try smaller; else increase.

```cpp
class Solution {
public:
    bool canShip(vector<int>& weights,int days,int cap){
        int d=1,load=0;
        for(int w:weights){
            if(load+w>cap){
                d++;
                load=w;
            }else{
                load+=w;
            }
        }
        return d<=days;
    }
    int shipWithinDays(vector<int>& weights,int days){
        int low=*max_element(weights.begin(),weights.end());
        int high=accumulate(weights.begin(),weights.end(),0);
        int ans=high;
        while(low<=high){
            int mid=low+(high-low)/2;
            if(canShip(weights,days,mid)){
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

**Time:** O(n · log(sum(weights))) · **Space:** O(1).

### Dry Run
`weights = [3,2,2,4,1,4]`, `days = 3`, search `[4, 16]`

| low | high | mid | days needed at cap=mid | ≤3? | ans | Action |
|-----|------|-----|------------------------|-----|-----|--------|
| 4 | 16 | 10 | [3,2,2],[4,1,4] → 2 | ✅ | 10 | high=9 |
| 4 | 9 | 6 | [3,2],[2,4],[1,4] → 3 | ✅ | 6 | high=5 |
| 4 | 5 | 4 | [3],[2,2],[4],[1],[4] → 5 | ❌ | 6 | low=5 |
| 5 | 5 | 5 | [3,2],[2],[4,1],[4] → 4 | ❌ | 6 | low=6 |
| 6 | 5 | — | — | — | 6 | **return 6** ✅ |

---

## 🧾 Recall Line *(10-Second Revision)*

> "BS on capacity `[max(w), sum(w)]`. Greedy `canShip` counts days. Feasible → smaller cap, else larger."

---

## 📝 Short Revision Notes

- `low = max(weights)` (heaviest package must fit); `high = sum(weights)` (one-day ship).
- Greedy day count: start a new day when the next package overflows the current load.
- Twin of "Split Array Largest Sum" / "Book Allocation" — minimize the max load.
- For very large sums, use `long long` for `high`/`accumulate`.

---

## ⚠️ Common Mistakes

❌ `low = 0` or `low = 1` instead of `max(weights)` → allows an impossible capacity.
❌ Forgetting `load = w` (not `load = 0`) when starting a new day.
❌ Overflow in `accumulate` for large inputs.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "minimum capacity / max-load to partition an ordered array into ≤ D groups" → **binary search on answer + greedy split**.

---

## 🏆 Pattern Category

`Binary Search on Answer` · `Greedy Partition`

---

## ⏱️ 30-Second Last-Minute Revision

> **BS capacity `[max(w), sum(w)]`.** Greedy day count; `days<=D` → shrink cap, else grow. Minimize. `O(n·log sum)`.
