# 🔥 Minimize Maximum Distance to Gas Station

> **LeetCode #774** (locked) / GFG · **Difficulty:** Hard · **Step 4 — Binary Search · P29**

---

## 🧠 Problem Understanding

**What is it asking?**
Given N existing gas stations on a number line at positions `stations[0] < stations[1] < ... < stations[N-1]`, add exactly K new gas stations to **minimize the maximum distance** between adjacent stations.

**Input:** `stations = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]`, `k = 9` → **Output:** `0.500000`
**Input:** `stations = [23, 24, 36, 39, 46, 56, 57, 65, 84, 98]`, `k = 1` → **Output:** `14.000000`

**Constraints:** `10 ≤ stations.length ≤ 2000`, `0 ≤ k ≤ 10⁷`, answer accepted within `10⁻⁶` tolerance

**Key Observations:**
- We can only minimize the **maximum gap** between adjacent stations by placing new ones in the largest gaps
- Placing a new station in a gap of length `L` using `p` new stations gives `p+1` equal sub-gaps of `L/(p+1)`
- Binary search on the answer (max gap = `D`): for each gap `g` between existing stations, we need `ceil(g/D) - 1` new stations. Sum across all gaps and check if ≤ K.
- Uses **floating point binary search** (answer is a decimal)

**Simple Example:**
```
stations=[1,2,...,10], k=9: gaps all = 1
Add 9 stations: can halve each gap → max distance = 0.5
```

---

## 🥉 Brute Force / Priority Queue Approach

### Idea
Use a max-heap of (current_gap, partition_count). Always split the largest current gap. Repeat K times.

### Algorithm
1. Compute initial gaps between consecutive stations
2. Use a max-heap: `(gap, 1)` for each gap (current max segment = gap/1)
3. Repeat K times: pop max, split it (increment partition count), push back
4. Return top of heap after K splits

### Complexity
- **Time:** O((N + K) log N)
- **Space:** O(N)

---

## 🥇 Optimal Approach — Floating Point Binary Search on Answer

### Key Observation

> 💡 For a target maximum distance `D`:
> - For each existing gap `g = stations[i+1] - stations[i]`, we need `ceil(g/D) - 1` new stations to ensure no sub-gap exceeds D
> - `ceil(g/D) - 1 = floor((g-ε)/D)` for small ε, equivalently: `(int)(g/D)` new stations (the number of times D fits completely in the gap)
>
> If the total new stations needed ≤ K, then D is achievable. Binary search for the minimum D.

### Algorithm
1. `lo = 0`, `hi = max_gap`
2. **Floating point binary search** (iterate ~100 times for precision):
   - `mid = (lo + hi) / 2`
   - `needed = Σ (int)(gap / mid)` for all gaps
   - If `needed <= K`: `hi = mid` (valid, try smaller D)
   - Else: `lo = mid` (need smaller gap, can't achieve with K stations)
3. Return `lo` (or `hi`, they converge)

### Dry Run

**Input:** `stations = [1, 5, 8, 10]`, `k = 2`
Gaps: [4, 3, 2]

lo=0, hi=4

**~100 iterations converge to optimal D:**

At D=2.0:
- gap 4: floor(4/2) = 2 stations needed
- gap 3: floor(3/2) = 1 station needed
- gap 2: floor(2/2) = 1 station needed
- Total = 4 > 2 → lo = 2.0

At D=2.5:
- gap 4: floor(4/2.5) = 1 station
- gap 3: floor(3/2.5) = 1 station
- gap 2: floor(2/2.5) = 0 stations
- Total = 2 ≤ 2 → hi = 2.5

Continues converging... final answer ≈ 2.0 → let's verify:
At D=2.0: need 2+1+1=4 > 2. At D=2.5: need 1+1+0=2 ≤ 2.

After 100 iterations: answer ≈ **2.5** ✅
(Place one new station at 3 → gaps become [2,2,3,2] → wait, need to think about optimal placement)

Actually at D=2.5: we need 2 stations. Place one in gap 4 → [1,3,5,8,10], now gap [2,2,3,2]. Then gap 3 needs 1 more → [1,3,5,7,8,10], gaps=[2,2,2,1,2] → max=2. Wait, k=2 stations and max gap = 2 < 2.5. ✓

### Complexity
- **Time:** O(N × 100) = O(N) for ~100 iterations of floating point BS
- **Space:** O(1)

---

## 🎤 Interview Explanation Script

> "This problem requires floating point binary search — the answer is a real number."

> "I binary search on the maximum gap D. For each gap between existing stations, the number of new stations needed to ensure no sub-gap exceeds D is `floor(gap/D)`. Summing across all gaps gives the total new stations needed."

> "If this total ≤ K, D is achievable. I use ~100 iterations of floating point binary search to get precision within 10⁻⁶."

> "The priority queue approach is O((N+K) log N) — much slower for K up to 10⁷. The binary search approach is O(N × 100) regardless of K."

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * MINIMIZE MAXIMUM DISTANCE TO GAS STATION — floating point binary search
 *
 * PROBLEM UNDERSTANDING:
 *   Add K new stations to minimize the maximum gap between adjacent stations.
 *
 * KEY OBSERVATION:
 *   For max gap D: stations needed per existing gap = floor(gap/D).
 *   If total needed ≤ K, D is achievable.
 *   Binary search on D (floating point).
 *
 * PRECISION: 100 iterations gives precision ~10^-30, far exceeding 10^-6 requirement.
 *
 * COMPLEXITY: Time O(N * 100) ≈ O(N) | Space O(1)
 */
class Solution {
private:
    // count new stations needed to make all sub-gaps <= maxDist
    int stationsNeeded(vector<int>& stations, double maxDist) {
        int needed = 0;
        for (int i = 0; i + 1 < stations.size(); i++) {
            double gap = stations[i + 1] - stations[i];
            needed += (int)(gap / maxDist);   // floor(gap/D) new stations
        }
        return needed;
    }

public:
    double minMaxGasDist(vector<int>& stations, int k) {
        double lo = 0, hi = 0;

        // find initial maximum gap
        for (int i = 0; i + 1 < stations.size(); i++)
            hi = max(hi, (double)(stations[i + 1] - stations[i]));

        // floating point binary search
        for (int iter = 0; iter < 100; iter++) {
            double mid = (lo + hi) / 2;
            if (stationsNeeded(stations, mid) <= k)
                hi = mid;    // achievable, try smaller distance
            else
                lo = mid;    // need more stations, increase allowed distance
        }

        return lo;           // lo and hi have converged
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "Float BS [0, max_gap]. Needed = Σfloor(gap/D). Needed≤K → hi=mid. Else lo=mid. 100 iterations for precision."

---

## 📝 Short Revision Notes

- Floating point BS: 100 iterations instead of `while lo < hi` (convergence by precision)
- Stations needed for gap `g` at max dist `D`: `floor(g/D)` = `(int)(g/D)`
- `hi = max_gap` initially (worst case: no new stations, max gap stays)
- `lo = 0` (best case: infinite stations, max gap → 0)
- Precision: 100 iterations achieves ~2⁻¹⁰⁰ relative precision

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "Minimize maximum distance/gap"
- "Add K elements, minimize maximum"
- "Answer is a real number"

**I should think of:** Floating point binary search on answer

---

## ⚠️ Common Mistakes

❌ Using integer binary search — answer is floating point  
❌ `ceil(gap/D) - 1` vs `floor(gap/D)` — they should be equal: `ceil(g/D) - 1 = floor((g-ε)/D) = floor(g/D)` when D doesn't divide g exactly  
❌ `while lo < hi` for float BS — use fixed iterations instead (avoids infinite loop)  

---

## 🔥 What Interviewer Is Testing

- **Concept:** Floating point binary search on a real-valued answer
- **Reasoning:** Why `floor(gap/D)` gives stations needed
- **Precision:** Understanding convergence via fixed iterations

---

## 🚀 Alternative Approaches

| Approach | Time | Space | Notes |
|----------|------|-------|-------|
| Floating point BS | O(N × 100) | O(1) | Best for large K |
| Priority queue | O((N+K) log N) | O(N) | Better for small K |

---

## 📚 Related Problems

- [ ] LeetCode #774 — Minimize Max Distance to Gas Station (premium)
- [ ] LeetCode #1552 — Magnetic Force Between Two Balls (same maximize-minimum pattern)
- [ ] Striver P25 — Aggressive Cows (maximize minimum — integer version)

---

## 🏆 Pattern Category

`Binary Search` · `Search Space` · `Floating Point`

---

## ⏱️ 30-Second Last-Minute Revision

> Float BS [0, max_gap]. `needed = Σ(int)(gap/D)`. needed≤K → hi=mid. Else lo=mid. Run 100 iterations. Return lo.
