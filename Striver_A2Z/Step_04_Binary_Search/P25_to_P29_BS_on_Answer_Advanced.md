# 🔥 Binary Search on Answer — Advanced Problems (P25–P29)

> **GFG + LeetCode** · **Difficulty:** Hard · **Step 4 — P25–P29**

---

## 🧠 Recap: The Master Template

```cpp
// Find MINIMUM answer satisfying a condition
int lo = min_possible, hi = max_possible;
while (lo < hi) {
    int mid = lo + (hi - lo) / 2;
    if (feasible(mid)) hi = mid;   // valid, try smaller
    else lo = mid + 1;             // not valid, need more
}
return lo;

// Find MAXIMUM answer satisfying a condition
while (lo < hi) {
    int mid = lo + (hi - lo + 1) / 2;  // upper mid to avoid infinite loop
    if (feasible(mid)) lo = mid;   // valid, try bigger
    else hi = mid - 1;
}
return lo;
```

---

# P25 — Aggressive Cows

> **GFG Classic / SPOJ AGGRCOW**

**Problem:** Place C cows in N stalls at given positions. Maximize the minimum distance between any two cows.

**Feasibility:** Given minimum distance D, can we place all C cows such that no two are closer than D?

```cpp
/*
 * AGGRESSIVE COWS — maximize minimum distance
 * Feasibility: greedily place cows with at least D gap
 * Time O(N log N + N log(max_dist)) | Space O(1)
 */
class Solution {
    bool canPlace(vector<int>& stalls, int cows, int minDist) {
        int count = 1, last = stalls[0];
        for (int i = 1; i < stalls.size(); i++) {
            if (stalls[i] - last >= minDist) {
                count++;
                last = stalls[i];
                if (count == cows) return true;
            }
        }
        return count >= cows;
    }
public:
    int aggressiveCows(vector<int>& stalls, int k) {
        sort(stalls.begin(), stalls.end());
        int lo = 1, hi = stalls.back() - stalls.front();
        int ans = 1;

        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (canPlace(stalls, k, mid)) { ans = mid; lo = mid + 1; }
            else hi = mid - 1;
        }
        return ans;    // maximize → store ans and go right
    }
};
```

**Note:** This is a **maximize** problem (`lo <= hi`, store ans, `lo = mid+1`).

---

# P26 — Book Allocation Problem

> **GFG Classic** (same as LeetCode #410 Split Array Largest Sum)

**Problem:** Allocate N books to M students. Each student gets contiguous books. Minimize the maximum pages any student reads.

**Feasibility:** With limit X, can we allocate books to all M students?

```cpp
/*
 * BOOK ALLOCATION / SPLIT ARRAY — minimize maximum sum
 * Same as: split array into M parts, minimize maximum part sum
 * lo = max(books), hi = sum(books)
 * Time O(N log(sum)) | Space O(1)
 */
class Solution {
    bool isPossible(vector<int>& books, int students, int limit) {
        int count = 1, pages = 0;
        for (int b : books) {
            if (b > limit) return false;      // single book exceeds limit
            if (pages + b > limit) { count++; pages = 0; }
            pages += b;
        }
        return count <= students;
    }
public:
    int findPages(vector<int>& books, int students) {
        if (books.size() < students) return -1;
        int lo = *max_element(books.begin(), books.end());
        int hi = accumulate(books.begin(), books.end(), 0);

        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (isPossible(books, students, mid)) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }
};
```

---

# P27 — Split Array — Largest Sum

> **LeetCode #410** (same as P26 above)

Identical to Book Allocation. Split array into `m` non-empty contiguous subarrays, minimize the maximum sum. Same code as P26.

---

# P28 — Kth Missing Positive Number

> **LeetCode #1539**

**Problem:** Find the Kth missing positive integer in a sorted array.

**Observation:** At index `i`, missing count = `arr[i] - (i+1)`. Binary search for first index where missing count ≥ K.

```cpp
/*
 * KTH MISSING POSITIVE — binary search on index
 * missing(i) = arr[i] - (i+1)  (how many missing up to arr[i])
 * Find first index where missing >= K, then compute answer
 * Time O(log N) | Space O(1)
 */
class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        int lo = 0, hi = arr.size();

        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (arr[mid] - (mid + 1) < k)   // fewer than k missing before arr[mid]
                lo = mid + 1;
            else
                hi = mid;
        }
        // lo = first index where missing count >= k
        // answer = lo + k (lo positions filled + k more)
        return lo + k;
    }
};
```

**Dry Run:** `arr=[2,3,4,7,11]`, k=5

| lo | hi | mid | arr[mid]-(mid+1) | <k? | Action |
|----|----|-----|-----------------|-----|--------|
| 0 | 5 | 2 | 4-3=1 | 1<5 ✅ | lo=3 |
| 3 | 5 | 4 | 11-5=6 | 6<5 ❌ | hi=4 |
| 3 | 4 | 3 | 7-4=3 | 3<5 ✅ | lo=4 |
| 4 | 4 | — | — | lo==hi → return 4+5=**9** ✅ |

(Missing: 1,5,6,8,9 — 5th is 9) ✅

---

# P29 — Minimize Max Distance to Gas Station

> **GFG / LC Hard**

**Problem:** Given gas station positions on a number line, add K more stations to minimize the maximum distance between consecutive stations.

**Search space:** answer (max gap) ∈ [0, max_gap]. Find minimum D such that we need ≤ K new stations.

```cpp
/*
 * MINIMIZE MAX GAS STATION DISTANCE — binary search on answer (floating point)
 * For distance D: stations needed = Σ⌈gap[i]/D⌉ - 1
 * Time O(N log(1/eps)) | Space O(1)
 * Note: floating point binary search
 */
class Solution {
public:
    double minMaxGasDist(vector<int>& stations, int k) {
        double lo = 0, hi = 1e8;

        // floating point binary search
        for (int iter = 0; iter < 100; iter++) {
            double mid = (lo + hi) / 2;
            int needed = 0;
            for (int i = 1; i < stations.size(); i++)
                needed += (int)((stations[i] - stations[i-1]) / mid);
            if (needed <= k) hi = mid;
            else lo = mid;
        }
        return lo;
    }
};
```

---

## 🧾 Summary Table

| Problem | Search space | lo | hi | Template |
|---------|-------------|----|----|----------|
| Aggressive Cows | min distance | 1 | max_gap | **maximize** |
| Book Allocation | max pages | max(book) | sum | **minimize** |
| Split Array | max sum | max(arr) | sum | **minimize** |
| Kth Missing | index | 0 | n | `ans = lo+k` |
| Gas Station | max gap | 0 | 1e8 | floating point |

## 📝 Key Notes
- **Maximize minimum:** `lo <= hi`, store `ans=mid`, `lo=mid+1` when feasible
- **Minimize maximum:** `lo < hi`, `hi=mid` when feasible, return `lo`
- Aggressive Cows: greedy placement (first cow at stalls[0], place when gap ≥ D)
- Book Allocation: greedy allocation (new student when adding exceeds limit)

## ⚠️ Common Mistakes
❌ P25: Using `lo < hi` template for maximize (should use `lo <= hi` with stored ans)  
❌ P28: `return (lo + k - 1)` — wrong; correct is `lo + k`  
❌ P29: Using integer binary search instead of floating point

## 🏆 Pattern Category
`Binary Search` · `Search Space` · `Greedy Feasibility`

## ⏱️ 30-Second Revision
> All are "binary search on answer" with a greedy feasibility check. min→`hi=mid`. max→store ans, `lo=mid+1`. P28: `missing=arr[mid]-(mid+1)`, ans=`lo+k`.
