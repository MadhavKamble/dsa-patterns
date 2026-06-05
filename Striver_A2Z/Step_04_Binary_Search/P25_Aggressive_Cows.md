# 🔥 Aggressive Cows

> **SPOJ AGGRCOW / GFG Classic** · **Difficulty:** Hard · **Step 4 — Binary Search · P25**

---

## 🧠 Problem Understanding

**What is it asking?**
Given N stall positions and C cows, place all C cows in stalls such that the **minimum distance between any two cows is maximized**. Return that maximum minimum distance.

**Input:** `stalls = [1, 2, 8, 4, 9]`, `cows = 3` → **Output:** `3`

**Constraints:** `2 ≤ N ≤ 10⁵`, `2 ≤ C ≤ N`, stall positions up to 10⁹

**Key Observations:**
- Sort stalls first — we'll place cows in sorted order
- Binary search on the answer: minimum distance D ∈ [1, max_stall - min_stall]
- Feasibility: greedily place cows with gap ≥ D — check if C cows fit

**Simple Example:**
```
stalls = [1,2,8,4,9] → sorted: [1,2,4,8,9]
C = 3

D=3: Place cow 1 at 1, next needs pos ≥ 4 → 4, next needs ≥ 7 → 8 or 9 → 8. 3 cows placed ✓
D=4: Place at 1, next ≥ 5 → 8, next ≥ 12 → none. Only 2 cows ✗
Answer: 3
```

---

## 🥉 Brute Force Approach

### Idea
Try every possible minimum distance from 1 to (max-min). Return the largest that works.

### Complexity
- **Time:** O((max-min) × N) — too slow
- **Space:** O(1)

---

## 🥇 Optimal Approach — Binary Search on Minimum Distance

### Key Observation

> 💡 **Monotone:** If minimum distance D works, D-1 also works (less restrictive). So there's a threshold: all D ≤ answer work, all D > answer fail. Binary search on D.
>
> **Search space:** `[1, stalls[N-1] - stalls[0]]`
>
> **Feasibility:** Greedy — place first cow at leftmost stall. For each subsequent cow, place it at the first stall that is at least D away from the last placed cow. Count how many cows we can place.

### Note: This is a **maximize minimum** problem
The template is slightly different:
- `lo <= hi` (not `lo < hi`)
- When feasible: record answer, try **larger** D (`lo = mid + 1`)
- When not feasible: try **smaller** D (`hi = mid - 1`)

### Algorithm
1. Sort `stalls`
2. `lo = 1`, `hi = stalls[N-1] - stalls[0]`, `ans = 1`
3. While `lo <= hi`:
   - `mid = lo + (hi - lo) / 2`
   - If `canPlace(stalls, cows, mid)`:
     - `ans = mid` (record best so far)
     - `lo = mid + 1` (try larger minimum distance)
   - Else:
     - `hi = mid - 1` (too large, reduce)
4. Return `ans`

### `canPlace(stalls, cows, minDist)`:
1. Place first cow at `stalls[0]`, `count = 1`, `lastPlaced = stalls[0]`
2. For each stall from 1 to N-1:
   - If `stalls[i] - lastPlaced >= minDist`: place cow, `count++`, `lastPlaced = stalls[i]`
3. Return `count >= cows`

### Dry Run

**Input:** `stalls = [1, 2, 4, 8, 9]`, `cows = 3`
`lo = 1`, `hi = 9 - 1 = 8`

| lo | hi | mid | canPlace(3, mid)? | ans | Action |
|----|-----|-----|------------------|-----|--------|
| 1 | 8 | 4 | stalls[0]=1, need≥5: 8, need≥12: ✗ → 2 cows ✗ | 1 | hi=3 |
| 1 | 3 | 2 | 1, need≥3: 4, need≥6: 8 → 3 cows ✓ | 2 | lo=3 |
| 3 | 3 | 3 | 1, need≥4: 4, need≥7: 8 → 3 cows ✓ | **3** | lo=4 |
| lo=4 > hi=3 → **return 3** ✅ |

### Complexity
- **Time:** O(N log N + N × log(max_dist)) — sort + binary search × feasibility check
- **Space:** O(1) after sort

---

## 🎤 Interview Explanation Script

> "This is a classic 'maximize minimum' binary search problem. I binary search on the answer — the minimum distance D."

> "The feasibility check is greedy: sort the stalls, place the first cow at the leftmost, then place each subsequent cow at the first stall that's at least D away from the previous. If we can place all C cows, D is achievable."

> "I use `lo <= hi` and store the best valid D, trying to increase it with `lo = mid + 1`. When feasibility fails, I decrease with `hi = mid - 1`."

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * AGGRESSIVE COWS — maximize minimum distance (binary search on answer)
 *
 * PROBLEM UNDERSTANDING:
 *   Place C cows in N stalls. Maximize minimum distance between any two.
 *
 * KEY OBSERVATION:
 *   Monotone: if D works, D-1 also works. Binary search on D.
 *   This is MAXIMIZE → store answer and try larger (lo = mid+1 when valid).
 *
 * FEASIBILITY: greedy placement with minimum gap D.
 *
 * COMPLEXITY: Time O(N log N + N log max_dist) | Space O(1)
 */
class Solution {
private:
    bool canPlace(vector<int>& stalls, int cows, int minDist) {
        int count = 1;
        int lastPlaced = stalls[0];

        for (int i = 1; i < stalls.size(); i++) {
            if (stalls[i] - lastPlaced >= minDist) {
                count++;
                lastPlaced = stalls[i];
                if (count == cows) return true;  // early exit
            }
        }
        return count >= cows;
    }

public:
    int aggressiveCows(vector<int>& stalls, int k) {
        sort(stalls.begin(), stalls.end());

        int lo = 1;
        int hi = stalls.back() - stalls.front();
        int ans = 1;

        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (canPlace(stalls, k, mid)) {
                ans = mid;          // valid, record and try larger
                lo = mid + 1;
            } else {
                hi = mid - 1;       // too large a gap, reduce
            }
        }

        return ans;
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "Sort stalls. BS [1, max-min]. Maximize → store ans=mid, lo=mid+1 when valid. Greedy placement for feasibility."

---

## 📝 Short Revision Notes

- **Maximize minimum** template: `lo <= hi`, record ans on valid, `lo = mid+1`
- **Minimize maximum** template: `lo < hi`, `hi = mid` on valid
- Sort stalls first — greedy placement requires sorted order
- Feasibility: greedy, place at first stall ≥ D away from last placed
- `hi = stalls.back() - stalls.front()` — maximum possible gap

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "Maximize minimum distance/gap"
- "Place k items, maximize closest pair distance"
- "AGGRCOW-style problems"

**I should think of:** Binary search on answer + greedy feasibility

---

## ⚠️ Common Mistakes

❌ Using `lo < hi` instead of `lo <= hi` for maximize problems  
❌ Using `hi = mid` instead of recording ans and doing `lo = mid+1`  
❌ Not sorting stalls — greedy only works on sorted positions  

---

## 🔥 What Interviewer Is Testing

- **Concept:** "Maximize minimum" binary search pattern
- **Reasoning:** Distinguishing from "minimize maximum" (different templates)
- **Application:** Greedy feasibility check

---

## 📚 Related Problems

- [ ] SPOJ AGGRCOW — Aggressive Cows (original)
- [ ] LeetCode #2560 — House Robber IV (same maximize-minimum pattern)
- [ ] GFG — Book Allocation (P26 — minimize maximum)
- [ ] LeetCode #1011 — Ship Packages (P23 — minimize maximum)

---

## 🏆 Pattern Category

`Binary Search` · `Search Space` · `Greedy` · `Maximize Minimum`

---

## ⏱️ 30-Second Last-Minute Revision

> Sort stalls. BS [1, max-min]. Feasibility: greedy placement with gap≥D. **Maximize**: `ans=mid, lo=mid+1` when valid. `hi=mid-1` when not. Return ans.
