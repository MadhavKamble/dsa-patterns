# 🔥 Kth Missing Positive Number

> **LeetCode #1539** · **Difficulty:** Easy · **Step 4 — Binary Search · P28**

---

## 🧠 Problem Understanding

**What is it asking?**
Given a **strictly increasing** positive integer array and integer `k`, find the `k`th missing positive integer.

**Input:** `arr = [2, 3, 4, 7, 11]`, `k = 5` → **Output:** `9`
Missing: 1, 5, 6, 8, 9, 10, 12, ... → 5th missing is 9.

**Input:** `arr = [1, 2, 3, 4]`, `k = 2` → **Output:** `6`
Missing: 5, 6, 7, ... → 2nd missing is 6.

**Constraints:** `1 ≤ arr.length ≤ 1000`, `1 ≤ arr[i] ≤ 1000`, `1 ≤ k ≤ 1000`

**Key Observations:**
- At index `i` (0-indexed), `arr[i]` should ideally be `i+1` in a gap-free sequence
- Missing count up to `arr[i]` = `arr[i] - (i+1)` (the "deficit")
- Binary search for the first index where `deficit >= k`
- Answer = `index + k` where `index` is the first position with enough missing numbers before it

**Simple Example:**
```
arr = [2, 3, 4, 7, 11], k = 5
Index:  0  1  2  3   4
Ideal:  1  2  3  4   5

missing(i) = arr[i] - (i+1):
  i=0: 2-1=1  (1 missing before position 0: just "1")
  i=1: 3-2=1
  i=2: 4-3=1
  i=3: 7-4=3  (1,5,6 missing before position 3)
  i=4: 11-5=6 (1,5,6,8,9,10 missing before position 4)

We need k=5. First index where deficit >= 5 is i=4 (deficit=6).
So i=4, answer = i + k = 4 + 5 = 9 ✓

Verify: missing list = [1,5,6,8,9,...] → 5th is 9 ✅
```

---

## 🥉 Brute Force Approach

### Idea
Use a set of array elements. Count positive integers not in the set until we reach the kth one.

### Algorithm
1. `missing = 0`, `num = 1`
2. While `missing < k`:
   - If `num` not in set: `missing++`; if `missing == k`: return `num`
   - `num++`

### Complexity
- **Time:** O(N + K) — may need to scan far past the array
- **Space:** O(N) — set storage

---

## 🥇 Optimal Approach — Binary Search

### Key Observation

> 💡 At index `i`, the count of missing numbers before `arr[i]` is `arr[i] - (i+1)`.
>
> This is a **monotone increasing** function of `i`. Binary search for the **first index** where `missing_count(i) >= k`.
>
> When we find that index `lo`:
> - `lo` elements in array, `lo + k` should be the `k`th missing number
> - Why? The first `lo` array elements "block" `lo` positions. The remaining `k` missing numbers are beyond, so the answer is `lo + k`.

### Algorithm
1. `lo = 0`, `hi = N` (hi can be N for "past all elements" case)
2. While `lo < hi`:
   - `mid = lo + (hi - lo) / 2`
   - `missing = arr[mid] - (mid + 1)`
   - If `missing < k`: `lo = mid + 1`
   - Else: `hi = mid`
3. Return `lo + k`

### Dry Run

**Input:** `arr = [2, 3, 4, 7, 11]`, `k = 5`
`lo = 0`, `hi = 5`

| lo | hi | mid | arr[mid] | missing=arr[mid]-(mid+1) | <k=5? | Action |
|----|-----|-----|----------|--------------------------|-------|--------|
| 0 | 5 | 2 | 4 | 4-3=1 | 1<5 ✅ | lo=3 |
| 3 | 5 | 4 | 11 | 11-5=6 | 6<5 ❌ | hi=4 |
| 3 | 4 | 3 | 7 | 7-4=3 | 3<5 ✅ | lo=4 |
| lo=4==hi=4 → **return lo+k = 4+5 = 9** ✅ |

**Input:** `arr = [1, 2, 3, 4]`, `k = 2`
`lo = 0`, `hi = 4`

| lo | hi | mid | missing | <2? | Action |
|----|-----|-----|---------|-----|--------|
| 0 | 4 | 2 | 3-3=0 | ✅ | lo=3 |
| 3 | 4 | 3 | 4-4=0 | ✅ | lo=4 |
| lo=4==hi=4 → **return 4+2 = 6** ✅ (missing after arr: 5,6,7,...  → 2nd is 6) |

### Why `return lo + k`?
After binary search, `lo` is the smallest index where `missing_count >= k`. At this position, there are `lo` array elements and `lo + k - 1` total positions covered (lo array + kth missing). So the kth missing is at value `lo + k`.

More precisely: `lo` elements from the array take up positions 1 to arr[lo-1]. The kth missing number needs to "jump over" those lo array elements, landing at position `lo + k`.

### Complexity
- **Time:** O(log N)
- **Space:** O(1)

---

## 🎤 Interview Explanation Script

> "The brute force counts missing numbers linearly — O(N + K). For O(log N), I use binary search."

> "The key insight: at index `i`, the count of missing numbers up to `arr[i]` is `arr[i] - (i+1)`. This is monotone increasing."

> "I binary search for the first index `lo` where `missing_count >= k`. At that point, there are `lo` array elements that 'take up' positions, so the kth missing number is at position `lo + k`."

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * KTH MISSING POSITIVE NUMBER — binary search
 *
 * PROBLEM UNDERSTANDING:
 *   Find kth missing positive in sorted array.
 *
 * KEY OBSERVATION:
 *   missing(i) = arr[i] - (i+1) = count of missing numbers before arr[i].
 *   This is monotone → binary search.
 *   First index lo where missing(lo) >= k → answer = lo + k.
 *
 * COMPLEXITY: Time O(log N) | Space O(1)
 */
class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        int lo = 0, hi = arr.size();

        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            // missing count at index mid = arr[mid] - (mid + 1)
            if (arr[mid] - (mid + 1) < k)
                lo = mid + 1;    // not enough missing yet, go right
            else
                hi = mid;        // enough or more missing, go left
        }

        // lo + k: lo elements in array "occupy" positions, kth missing at lo + k
        return lo + k;
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "`missing(i) = arr[i] - (i+1)`. BS for first index with missing ≥ k. Return `lo + k`."

---

## 📝 Short Revision Notes

- Key formula: `missing(i) = arr[i] - (i+1)` (arr[i] minus its 1-indexed position)
- Binary search finds first `lo` where `missing(lo) >= k`
- Answer is `lo + k` — not `arr[lo]` or `arr[lo-1] + something`
- `hi = N` (not N-1) — k might be past all array elements
- Works even when k > all missing numbers within the array range

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "Kth missing positive in sorted array"
- "Count missing elements up to position i"

**I should think of:** Monotone missing-count formula + binary search → `lo + k` formula

---

## ⚠️ Common Mistakes

❌ Returning `arr[lo]` instead of `lo + k`  
❌ `hi = N - 1` — misses case where k-th missing is past all array elements  
❌ Off-by-one: `arr[mid] - mid` vs `arr[mid] - (mid+1)` — must subtract 1-indexed position  

---

## 🔥 What Interviewer Is Testing

- **Concept:** Translating "kth missing" to a monotone binary search problem
- **Reasoning:** Why `lo + k` gives the correct answer
- **Detail:** Exact formula and hi boundary

---

## 🚀 Alternative Approaches

| Approach | Time | Space | Notes |
|----------|------|-------|-------|
| Binary search | O(log N) | O(1) | Optimal |
| Linear scan | O(N + K) | O(1) | Simple, acceptable for small inputs |
| Hash set | O(N + K) | O(N) | Unnecessary for sorted array |

---

## 📚 Related Problems

- [ ] LeetCode #1539 — Kth Missing Positive Number
- [ ] LeetCode #441 — Arranging Coins (similar formula-based binary search)
- [ ] GFG — Kth Missing Element in Array

---

## 🏆 Pattern Category

`Binary Search` · `Search Space` · `Formula-based`

---

## 🎯 Difficulty Analysis

**Rating:** Easy (rating), Medium (insight)

**Why:** The binary search framework isn't obvious here — recognizing the `arr[i] - (i+1)` formula and the `lo + k` return value are the non-trivial steps.

---

## ⏱️ 30-Second Last-Minute Revision

> `missing(i) = arr[i] - (i+1)`. BS: `missing < k` → `lo = mid+1`. Else `hi = mid`. Return `lo + k`.  
> `hi = arr.size()` not `N-1`.
