# 🔥 Find How Many Times an Array Has Been Rotated

> **GFG Classic** · **Difficulty:** Easy-Medium · **Step 4 — Binary Search · P14**

---

## 🧠 Problem Understanding

**What is it asking?**
Given a sorted array rotated K times (left rotation), find K — the number of times it was rotated.

**Input:** `arr = [4, 5, 6, 7, 0, 1, 2]` → **Output:** `4`
(Original: [0,1,2,4,5,6,7], rotated left 4 times → [4,5,6,7,0,1,2])

**Input:** `arr = [1, 2, 3, 4, 5]` (not rotated) → **Output:** `0`

**Key Observation:**
The number of rotations = **index of the minimum element**.

Why? If we left-rotate a sorted array once, the first element moves to the end. After K rotations, the original minimum element (which was at index 0) is now at index K.

```
Original:    [0, 1, 2, 4, 5, 6, 7]   rotation count = 0
After 1 rot: [1, 2, 4, 5, 6, 7, 0]   min at index 6, count=6? No...

Wait: left rotation means first element goes to end:
[0,1,2,4,5,6,7] → rotate left 1 → [1,2,4,5,6,7,0] → min at index 6

But the problem may define rotation differently. Let me check.

For [4,5,6,7,0,1,2]: minimum is 0 at index 4. Count = 4.
For [1,2,3,4,5]: minimum is 1 at index 0. Count = 0.

So: number of rotations = index of minimum element. ✅
```

---

## 🥉 Brute Force Approach

### Idea
Find the index of the minimum element by linear scan.

```cpp
int countRotations(vector<int>& arr) {
    int minIdx = 0;
    for (int i = 1; i < arr.size(); i++)
        if (arr[i] < arr[minIdx]) minIdx = i;
    return minIdx;
}
// Time O(N), Space O(1)
```

---

## 🥇 Optimal Approach — Binary Search

### Key Observation

> 💡 Number of rotations = index of minimum element. Use the same algorithm as P11 (Find Minimum), but return the **index** instead of the **value**.

### Algorithm
1. `lo = 0`, `hi = N - 1`
2. While `lo < hi`:
   - `mid = lo + (hi - lo) / 2`
   - If `arr[mid] > arr[hi]`: `lo = mid + 1`
   - Else: `hi = mid`
3. Return `lo` (index of minimum = rotation count)

### Dry Run

**Input:** `arr = [4, 5, 6, 7, 0, 1, 2]`

| lo | hi | mid | arr[mid] | arr[hi] | Action |
|----|-----|-----|----------|---------|--------|
| 0 | 6 | 3 | 7 | 2 | 7>2 → lo=4 |
| 4 | 6 | 5 | 1 | 2 | 1<2 → hi=5 |
| 4 | 5 | 4 | 0 | 1 | 0<1 → hi=4 |
| lo=4==hi=4 → **return 4** ✅ |

**Input:** `arr = [1, 2, 3, 4, 5]` (sorted, not rotated)

| lo | hi | mid | arr[mid] | arr[hi] | Action |
|----|-----|-----|----------|---------|--------|
| 0 | 4 | 2 | 3 | 5 | 3<5 → hi=2 |
| 0 | 2 | 1 | 2 | 3 | 2<3 → hi=1 |
| 0 | 1 | 0 | 1 | 2 | 1<2 → hi=0 |
| lo=0==hi=0 → **return 0** ✅ |

### Complexity
- **Time:** O(log N) · **Space:** O(1)

---

## 🎤 Interview Explanation Script

> "The number of rotations equals the index of the minimum element in the rotated array. This is because after K left rotations of a sorted array, the original first element (the minimum) ends up at index K."

> "So I just find the index of the minimum using binary search — same algorithm as 'Find Minimum in Rotated Sorted Array' but return the index instead of the value."

> "Compare `arr[mid]` with `arr[hi]`. If `arr[mid] > arr[hi]`, minimum is right → `lo = mid+1`. Else `hi = mid`. When converged, `lo` is the rotation count."

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * COUNT ROTATIONS — index of minimum element
 *
 * PROBLEM UNDERSTANDING:
 *   K left rotations → minimum element is at index K.
 *   Count rotations = index of minimum.
 *
 * REUSES: Same algorithm as P11 (Find Minimum), returns INDEX not value.
 *
 * COMPLEXITY: Time O(log N) | Space O(1)
 */
class Solution {
public:
    int countRotations(vector<int>& arr) {
        int lo = 0, hi = arr.size() - 1;

        // handle already-sorted case (no rotation)
        if (arr[lo] <= arr[hi]) return 0;

        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;

            if (arr[mid] > arr[hi])
                lo = mid + 1;    // minimum is right of mid
            else
                hi = mid;        // minimum is at mid or left
        }

        return lo;               // index of minimum = rotation count
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "Rotations = index of minimum. Same as Find Minimum (P11) but return `lo` (index) not `arr[lo]` (value)."

---

## 📝 Short Revision Notes

- Key insight: K left rotations → minimum at index K
- Identical to P11 except return `lo` instead of `arr[lo]`
- Early exit: if `arr[0] <= arr[N-1]` → sorted → 0 rotations
- Right rotation by K = left rotation by N-K

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "How many times rotated"
- "Find rotation count of sorted array"

**I should think of:** Index of minimum element → binary search → O(log N)

---

## ⚠️ Common Mistakes

❌ Returning `arr[lo]` (value) instead of `lo` (index)  
❌ Off-by-one in defining "rotation count" — confirm with interviewer if it's 0-indexed  
❌ Not handling the non-rotated case (returns 0 correctly via binary search anyway)  

---

## 🔥 What Interviewer Is Testing

- **Concept:** Connecting rotation count to minimum element's index
- **Reasoning:** Why minimum is at the rotation pivot
- **Reuse:** Building on P11's solution

---

## 📚 Related Problems

- [ ] GFG — Count Rotations of Sorted Array
- [ ] LeetCode #153 — Find Minimum (P11)
- [ ] LeetCode #33 — Search in Rotated Sorted Array (P09)

---

## 🏆 Pattern Category

`Binary Search` · `Rotated Array`

---

## ⏱️ 30-Second Last-Minute Revision

> **Rotations = index of minimum.** Same BS as P11. `arr[mid]>arr[hi]` → `lo=mid+1`. Else `hi=mid`. Return `lo`.
