# 🔥 Aggressive Cows

> **Striver / GFG / SPOJ** · **Difficulty:** Hard · **Step 4 — Binary Search · P21**

---

## 🧠 Problem Understanding

**What is it asking?**
Place `cows` cows into stalls at given positions so that the **minimum distance** between any two cows is **as large as possible**. Return that largest minimum distance.

**Input:** `stalls = [1, 2, 8, 4, 9]`, `cows = 3` → **Output:** `3`
(sorted `[1,2,4,8,9]`; place at 1, 4, 8 → min gap 3)

**Key Observation:**
- We search over the **distance** (a value), not an index.
- **Monotonic:** if a distance `d` is achievable, every smaller distance is too. So feasibility flips `true → false` once as `d` grows → binary search.
- This is a **maximize** problem: on feasible, push **right** for a bigger gap.

---

## 🎯 Interview Progression

### 🥉 Brute Force — Try Every Distance

For `d = 1, 2, ...`, greedily check if all cows fit with gap `d`; the answer is the largest feasible `d`. **Time:** O(range · n).

---

### 🥇 Optimal — Binary Search on Distance

> 💡 `canPlace(d)`: place the first cow at `stalls[0]`, then greedily place each next cow at the first stall that is `≥ d` away. Feasible if we seat all cows. Search `[1, max-min]`; on feasible go **right** (maximize).

```cpp
class Solution {
public:
    bool canPlace(vector<int>& stalls,int cows,int d){
        int count=1;
        int lastPos=stalls[0];
        for(int i=1;i<stalls.size();i++){
            if(stalls[i]-lastPos>=d){
                count++;
                lastPos=stalls[i];
            }
            if(count>=cows) return true;
        }
        return false;
    }
    int aggressiveCows(vector<int>& stalls,int cows){
        sort(stalls.begin(),stalls.end());
        int low=1;
        int high=stalls.back()-stalls.front();
        int ans=0;
        while(low<=high){
            int mid=low+(high-low)/2;
            if(canPlace(stalls,cows,mid)){
                ans=mid;
                low=mid+1;
            }else{
                high=mid-1;
            }
        }
        return ans;
    }
};
```

**Time:** O(n log n + n · log(max-min)) · **Space:** O(1).

### Dry Run
`stalls = [1, 2, 4, 8, 9]` (sorted), `cows = 3`, search `[1, 8]`

| low | high | mid | canPlace(mid)? | ans | Action |
|-----|------|-----|----------------|-----|--------|
| 1 | 8 | 4 | place 1,8 → only 2 cows ❌ | 0 | high=3 |
| 1 | 3 | 2 | place 1,4,8 → 3 ✅ | 2 | low=3 |
| 3 | 3 | 3 | place 1,4,8 → 3 ✅ | 3 | low=4 |
| 4 | 3 | — | — | 3 | **return 3** ✅ |

---

## 🧾 Recall Line *(10-Second Revision)*

> "Sort. BS on gap `[1, max-min]`. Greedy `canPlace`. Feasible → **maximize** (`low=mid+1`)."

---

## 📝 Short Revision Notes

- **Sort first** — positions must be ordered for the greedy check.
- Maximize problem → on feasible move `low = mid+1` (opposite of the minimize templates).
- `canPlace` places greedily: seat a cow whenever it's `≥ d` from the last placed cow.
- Search space `[1, stalls.back() - stalls.front()]`.

---

## ⚠️ Common Mistakes

❌ Forgetting to sort the stalls.
❌ Moving the wrong direction — this is maximize, so feasible → go right.
❌ Resetting `lastPos` incorrectly (must track the last *placed* cow, not just the last stall).

---

## 🧠 Pattern Recognition Trigger

**When I see:** "maximize the minimum distance/gap", "place k items as spread out as possible" → **binary search on the answer (maximize)**.

---

## 🏆 Pattern Category

`Binary Search on Answer` · `Maximize Minimum` · `Greedy Check`

---

## ⏱️ 30-Second Last-Minute Revision

> **Sort. BS gap `[1, max-min]`.** Greedy place cows `≥ d` apart. Feasible → maximize (`low=mid+1`). `O(n log n)`.
