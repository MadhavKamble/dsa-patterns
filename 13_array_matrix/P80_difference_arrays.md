# P80 — Difference Arrays and Range Updates

## 1. First-Timer Explanation

### What Is It?
**Difference array** supports efficient range update operations: "add value v to all elements from index l to r" in O(1), then reconstructs the final array in O(n). It is the complement to prefix sum: prefix sum answers range queries, difference array handles range updates.

### How It Works
```
diff[i] = arr[i] - arr[i-1]   (with diff[0] = arr[0])

To add v to range [l, r]:
  diff[l] += v       (start of range)
  diff[r+1] -= v     (cancel after range end)

To reconstruct: arr[i] = arr[i-1] + diff[i]  (running prefix sum of diff)
```

### Visual Walkthrough
```
arr = [0, 0, 0, 0, 0] (all zeros)
diff = [0, 0, 0, 0, 0]

Operation 1: add 3 to [1, 3]:
  diff[1] += 3 → diff = [0, 3, 0, 0, -3]

Operation 2: add 2 to [2, 4]:
  diff[2] += 2, diff[5] -= 2 (out of bounds, ignore)
  diff = [0, 3, 2, 0, -3]

Reconstruct prefix sum:
  arr[0]=0, arr[1]=0+3=3, arr[2]=3+2=5, arr[3]=5+0=5, arr[4]=5+(-3)=2
  Result: [0, 3, 5, 5, 2]
```

### When to Use
- "Apply multiple range increments, then query final array" → difference array
- "Corporate flight bookings" / "car pooling" → range add, query max or sum
- "Meeting rooms" / "event scheduler" with count → difference + prefix sum for max overlap
- "Paint fence" / "range cover queries" → difference array

### Common Mistakes
1. Off-by-one: `diff[r+1] -= v` — if r+1 >= n, skip (or use size n+1 array)
2. Not reconstructing: forget to convert diff back to actual values via prefix sum
3. Confusing with prefix sum: prefix sum = fast queries, difference = fast updates

---

## 2. Revision Card

**Recognition Signal:** "range update, then read final state", "flights/bookings seats", "car pooling capacity"

**Core Idea:** `diff[l] += v; diff[r+1] -= v`. Then `prefix_sum(diff)` gives final values. O(1) per update, O(n) reconstruction.

**Trigger Keywords:** range update, booking, overlap count, car pooling, corporate flights

**Complexity:** O(q) for q updates + O(n) reconstruction; O(n + q) total

---

## 3. Interview Tell Signs

- "Range add operations, find final array" → difference array
- "Maximum number of overlapping intervals at any point" → difference array + prefix max
- "Car pooling" (capacity constraint) → difference array, check if any value exceeds capacity
- "Corporate flight bookings" → difference array with seats += bookings[i][2]
- "Stamping" or "painting" problems where ranges are updated → difference array

---

## 4. C++ Template

```cpp
#include <vector>
using namespace std;

// ── Difference Array ──────────────────────────────────────────────────────────
class DifferenceArray {
    vector<int> diff;
public:
    DifferenceArray(int n) : diff(n + 1, 0) {}

    // Add val to range [l, r] (0-indexed)
    void update(int l, int r, int val) {
        diff[l] += val;
        if (r + 1 < (int)diff.size()) diff[r + 1] -= val;
    }

    // Reconstruct: returns prefix sum of diff
    vector<int> result() {
        vector<int> res(diff.size() - 1);
        res[0] = diff[0];
        for (int i = 1; i < (int)res.size(); i++) res[i] = res[i-1] + diff[i];
        return res;
    }
};

// ── Corporate Flight Bookings ─────────────────────────────────────────────────
vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
    vector<int> diff(n + 1, 0);
    for (auto& b : bookings) {
        diff[b[0] - 1] += b[2];    // 1-indexed → 0-indexed
        if (b[1] < n) diff[b[1]] -= b[2];
    }
    for (int i = 1; i < n; i++) diff[i] += diff[i-1];
    return vector<int>(diff.begin(), diff.begin() + n);
}

// ── Car Pooling ───────────────────────────────────────────────────────────────
bool carPooling(vector<vector<int>>& trips, int capacity) {
    vector<int> diff(1001, 0);
    for (auto& t : trips) {
        diff[t[1]] += t[0];  // pick up passengers at t[1]
        diff[t[2]] -= t[0];  // drop off at t[2]
    }
    int running = 0;
    for (int x : diff) {
        running += x;
        if (running > capacity) return false;
    }
    return true;
}

// ── Minimum Number of Arrows (Overlap Detection) ─────────────────────────────
// For counting max overlap at any point (e.g., meeting rooms):
int maxOverlap(vector<pair<int,int>>& intervals) {
    map<int,int> diff;
    for (auto& [s, e] : intervals) { diff[s]++; diff[e]--; }
    int cur = 0, maxOv = 0;
    for (auto& [_, d] : diff) { cur += d; maxOv = max(maxOv, cur); }
    return maxOv;
}
```

---

## 5. How to Present in Interview

**Verbal Script:**
> "I'll use a difference array. For each range update [l, r] with value v, I mark `diff[l] += v` and `diff[r+1] -= v`. After all updates, I compute the prefix sum of `diff` to get the actual values. Each update is O(1), and the final reconstruction is O(n). This gives O(q + n) total for q updates."

**Checklist:**
- [ ] Use size n+1 for `diff` to safely write `diff[r+1]` when r = n-1
- [ ] Reconstruct by prefix summing the diff array
- [ ] 1-indexed problems (like bookings): convert to 0-indexed carefully
- [ ] For overlap counting with coordinate compression: use `map<int,int>` as the diff array
- [ ] Car pooling: drop-off means passengers leave, so `diff[t[2]] -= t[0]`

---

## 6. Problems

### Problem 1: Corporate Flight Bookings
**Difficulty:** Medium | **LC:** 1109

```cpp
vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
    vector<int> diff(n+1, 0);
    for (auto& b : bookings) {
        diff[b[0]-1] += b[2];
        if (b[1] < n) diff[b[1]] -= b[2];
    }
    for (int i=1; i<n; i++) diff[i] += diff[i-1];
    return {diff.begin(), diff.begin()+n};
}
// Time: O(n + q) | Space: O(n)
// b[0],b[1] are 1-indexed, b[2] = seats
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Car Pooling
**Difficulty:** Medium | **LC:** 1094

```cpp
bool carPooling(vector<vector<int>>& trips, int capacity) {
    vector<int> diff(1001, 0);
    for (auto& t : trips) { diff[t[1]] += t[0]; diff[t[2]] -= t[0]; }
    int cur = 0;
    for (int x : diff) { cur += x; if (cur > capacity) return false; }
    return true;
}
// Time: O(n + 1001) = O(n) | Space: O(1001) = O(1)
// Key: drop-off at t[2] means passengers leave AT t[2] (not t[2]+1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Range Addition
**Difficulty:** Medium | **LC:** 370

```cpp
vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
    vector<int> diff(length + 1, 0);
    for (auto& u : updates) {
        diff[u[0]] += u[2];
        if (u[1] + 1 < length + 1) diff[u[1] + 1] -= u[2];
    }
    for (int i = 1; i < length; i++) diff[i] += diff[i-1];
    return {diff.begin(), diff.begin() + length};
}
// Time: O(n + q) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Shifting Letters II
**Difficulty:** Medium | **LC:** 2381

**Approach:** Difference array tracks net shift for each position; then apply shifts.

```cpp
string shiftingLetters(string s, vector<vector<int>>& shifts) {
    int n = s.size();
    vector<int> diff(n + 1, 0);
    for (auto& sh : shifts) {
        int dir = sh[2] == 1 ? 1 : -1;
        diff[sh[0]] += dir;
        if (sh[1] + 1 <= n) diff[sh[1] + 1] -= dir;
    }
    int shift = 0;
    for (int i = 0; i < n; i++) {
        shift += diff[i];
        int c = ((s[i] - 'a' + shift) % 26 + 26) % 26;
        s[i] = 'a' + c;
    }
    return s;
}
// Time: O(n + q) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Count Positions on Street with Required Brightness
**Difficulty:** Medium | **LC:** 2238

**Approach:** Difference array over position range; check each position against requirement.

```cpp
int meetRequirement(int n, vector<vector<int>>& lights, vector<int>& requirement) {
    vector<int> diff(n + 2, 0);
    for (auto& l : lights) {
        int lo = max(0, l[0] - l[1]);
        int hi = min(n - 1, l[0] + l[1]);
        diff[lo]++; diff[hi + 1]--;
    }
    int cur = 0, res = 0;
    for (int i = 0; i < n; i++) {
        cur += diff[i];
        if (cur >= requirement[i]) res++;
    }
    return res;
}
// Time: O(n + m) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: Check if Array Pairs Are Divisible by K
**Difficulty:** Medium | **LC:** 1497

**Approach:** Frequency count of remainders. Pair remainder r with k-r.

```cpp
bool canArrange(vector<int>& arr, int k) {
    vector<int> freq(k, 0);
    for (int x : arr) freq[((x % k) + k) % k]++;
    if (freq[0] % 2 != 0) return false;
    for (int r = 1; r <= k / 2; r++) {
        if (freq[r] != freq[k - r]) return false;
    }
    return true;
}
// Time: O(n + k) | Space: O(k)
// Note: this uses modular counting (related to difference arrays)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** Apply "add 5 to [0,2]" and "add 3 to [1,3]" on a 5-element zero array. Show diff and result.
<details><summary>Reveal</summary>
diff = [0,0,0,0,0,0] (size 6). Op1: diff[0]+=5, diff[3]-=5 → [5,0,0,-5,0,0]. Op2: diff[1]+=3, diff[4]-=3 → [5,3,0,-5,-3,0]. Reconstruct prefix sum: arr[0]=5, arr[1]=5+3=8, arr[2]=8+0=8, arr[3]=8-5=3, arr[4]=3-3=0. Result: [5,8,8,3,0] ✓.
</details>

**Drill 2:** Car pooling: trips=[[2,1,5],[3,3,7]], capacity=4. Is it feasible?
<details><summary>Reveal</summary>
diff = [0...]. Trip1: diff[1]+=2, diff[5]-=2. Trip2: diff[3]+=3, diff[7]-=3. Running sum: pos0=0, pos1=2, pos2=2, pos3=2+3=5. At pos3, 5>4 → return false. Not feasible ✓.
</details>

**Drill 3:** Why use a map<int,int> instead of array for coordinate-compressed difference arrays?
<details><summary>Reveal</summary>
When coordinates can be very large (like timestamps or geographic coordinates up to 10^9), an array of that size would be impractical. A map only stores entries where diff is nonzero, keeping space O(number of events) instead of O(max_coordinate). The map's ordered iteration then naturally processes events in sorted order.
</details>

**Drill 4:** Corporate flights: bookings=[[1,2,10],[2,3,20],[2,5,25]], n=5. What is the diff array before reconstruction?
<details><summary>Reveal</summary>
Convert 1-indexed: [1,2,10]→diff[0]+=10, diff[2]-=10. [2,3,20]→diff[1]+=20, diff[3]-=20. [2,5,25]→diff[1]+=25 (5=n, so no diff[5]-=25). diff = [10, 45, -10, -20, 0]. Reconstruct: [10, 55, 45, 25, 25] ✓.
</details>

**Drill 5:** How does the difference array handle the case where r+1 is out of bounds?
<details><summary>Reveal</summary>
Use size n+1 for the diff array. The extra slot at index n safely absorbs the `diff[r+1] -= v` when r = n-1, without going out of bounds. During reconstruction, we only read indices 0 to n-1, so this extra slot never affects the result but prevents an array out-of-bounds access.
</details>

---

## 8. Complexity Cheatsheet

| Operation | Time | Space |
|-----------|------|-------|
| Range update | O(1) | O(n) |
| Reconstruct array | O(n) | O(1) |
| q updates + reconstruction | O(q + n) | O(n) |
| Coordinate-compressed | O(q log q) | O(q) |
| Max overlap at any point | O(n log n) with map | O(q) |

---

## 9. Common Follow-up Questions

**Q: Can you do range updates AND range queries efficiently?**
A: Yes — use a Fenwick Tree (BIT, P98) with a technique called "range update range query" using two BITs. Or use a Segment Tree (P97) with lazy propagation.

**Q: What if updates multiply instead of add?**
A: Difference arrays only work for additive operations (due to the linearity of prefix sums). For multiplicative updates, segment trees with lazy propagation are the standard approach.

**Q: What about 2D range updates?**
A: Use a 2D difference array. `diff[r1][c1] += v; diff[r1][c2+1] -= v; diff[r2+1][c1] -= v; diff[r2+1][c2+1] += v`. Then two prefix sums (row then column) reconstruct the 2D result.

---

## 10. Cross-Pattern Connections

- **P79 (Prefix Sums):** Prefix sum answers queries; difference array enables updates — they are inverses
- **P97 (Segment Tree):** Lazy segment tree handles both range updates and queries in O(log n)
- **P98 (Fenwick Tree):** Range update range query with two BITs
- **P84 (Sweep Line):** Sweep line events on a difference array is the core overlap-counting technique
- **P53 (Interval Scheduling):** Both operate on intervals; difference array counts coverage
