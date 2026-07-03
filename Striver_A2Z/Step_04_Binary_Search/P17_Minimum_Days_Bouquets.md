# 🔥 Minimum Days to Make M Bouquets

> **LeetCode #1482** · **Difficulty:** Medium · **Step 4 — Binary Search · P17**

---

## 🧠 Problem Understanding

**What is it asking?**
`bloomDay[i]` is the day flower `i` blooms. A bouquet needs `k` **adjacent** bloomed flowers. Find the **minimum number of days** to make `m` bouquets. Return `-1` if impossible.

**Input:** `bloomDay = [1, 10, 3, 10, 2]`, `m = 3`, `k = 1` → **Output:** `3`
**Input:** `bloomDay = [1, 10, 3, 10, 2]`, `m = 3`, `k = 2` → **Output:** `-1` (need 6 flowers, only 5 exist)

**Key Observation:**
- We search over **days** (a value).
- **Monotonic:** more days → more flowers bloomed → easier to form bouquets. Feasibility flips `false → true` once.
- Impossible upfront if `m * k > n`.

---

## 🎯 Interview Progression

### 🥉 Brute Force — Try Every Day

For each day from `min` to `max` bloom, check if `m` bouquets can form; return the first that works. **Time:** O(maxDay · n).

---

### 🥇 Optimal — Binary Search on Days

> 💡 Search `[min(bloomDay), max(bloomDay)]`. `canMake(day)` greedily counts **adjacent** bloomed flowers (reset the run when a flower hasn't bloomed). Feasible → minimize (`high = mid-1`); else increase days.

```cpp
class Solution {
public:
    bool canMake(vector<int>& bloomDay,int m,int k,int days){
        int bouquets=0,flowers=0;
        for(int d:bloomDay){
            if(d<=days){
                flowers++;
                if(flowers==k){
                    bouquets++;
                    flowers=0;
                }
            }else{
                flowers=0;
            }
        }
        return bouquets>=m;
    }
    int minDays(vector<int>& bloomDay,int m,int k){
        int n=bloomDay.size();
        if((long long)m*k>n) return -1;
        int low=*min_element(bloomDay.begin(),bloomDay.end());
        int high=*max_element(bloomDay.begin(),bloomDay.end());
        int ans=-1;
        while(low<=high){
            int mid=low+(high-low)/2;
            if(canMake(bloomDay,m,k,mid)){
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

**Time:** O(n · log(maxDay)) · **Space:** O(1).

### Dry Run
`bloomDay = [1, 10, 3, 10, 2]`, `m = 3`, `k = 1`, search `[1, 10]`

| low | high | mid | bouquets(day≤mid) | ≥3? | ans | Action |
|-----|------|-----|-------------------|-----|-----|--------|
| 1 | 10 | 5 | flowers on days ≤5: idx 0,2,4 → 3 | ✅ | 5 | high=4 |
| 1 | 4 | 2 | idx 0,4 → 2 | ❌ | 5 | low=3 |
| 3 | 4 | 3 | idx 0,2,4 → 3 | ✅ | 3 | high=2 |
| 3 | 2 | — | — | — | 3 | **return 3** ✅ |

---

## 🧾 Recall Line *(10-Second Revision)*

> "BS on day `[min, max]`. `canMake`: count **adjacent** bloomed flowers, reset on a gap. `m*k>n` → -1."

---

## 📝 Short Revision Notes

- Impossibility check first: `m*k > n` → `-1` (cast to `long long` to avoid overflow).
- Adjacency matters: reset `flowers = 0` whenever a flower hasn't bloomed yet.
- On completing `k` flowers, increment `bouquets` and reset the run.
- Search space is the bloom-day range `[min, max]`.

---

## ⚠️ Common Mistakes

❌ Not resetting the flower run on a non-bloomed flower → counts non-adjacent flowers.
❌ Skipping the `m*k > n` check → wrong `-1` handling.
❌ `int` overflow in `m*k`.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "minimum day/time so that a greedy condition holds", "adjacent groups" → **binary search on answer + greedy check**.

---

## 🏆 Pattern Category

`Binary Search on Answer` · `Greedy Check`

---

## ⏱️ 30-Second Last-Minute Revision

> **BS day `[min,max]`.** Greedy count adjacent bloomed flowers into bouquets. `bouquets>=m` → minimize. `m*k>n` → -1. `O(n·log maxDay)`.
