# 🔥 Single Element in a Sorted Array

> **LeetCode #540** · **Difficulty:** Medium · **Step 4 — Binary Search · P12**

---

## 🧠 Problem Understanding

Every element appears **exactly twice** except one. Find the single element. O(log N) required.

**Input:** `[1,1,2,3,3,4,4,8,8]` → **Output:** `2`

**Key Observation:** Before the single element, pairs are at `(even, odd)` indices. After, pairs shift to `(odd, even)`. Use this parity shift to binary search.

---

## 🥇 Optimal — Binary Search on Parity

### Key Observation
> 💡 At `mid` (even index): if `arr[mid] == arr[mid+1]`, single element is to the **right** (pair is normal, single hasn't appeared yet). If `arr[mid] != arr[mid+1]`, single is at or to the **left**.

```
Before single: pairs at (0,1), (2,3), (4,5)...
After single:  pairs at (1,2), (3,4), (5,6)...
```

### Algorithm
1. `lo=0, hi=n-1`
2. While `lo < hi`:
   - `mid = lo + (hi-lo)/2` — ensure mid is even: `if mid % 2 == 1: mid--`
   - If `arr[mid] == arr[mid+1]`: single is right → `lo = mid+2`
   - Else: single is at mid or left → `hi = mid`
3. Return `arr[lo]`

### Dry Run
`arr = [1,1,2,3,3,4,4,8,8]` (indices 0–8)

| lo | hi | mid (even) | arr[mid] | arr[mid+1] | equal? | Action |
|----|-----|-----------|----------|------------|--------|--------|
| 0 | 8 | 4 | 3 | 4 | ❌ | hi=4 |
| 0 | 4 | 2 | 2 | 3 | ❌ | hi=2 |
| 0 | 2 | 0 | 1 | 1 | ✅ | lo=2 |
| 2 | 2 | — | — | — | lo==hi → return arr[2]=**2** ✅ |

### Complexity
- **Time:** O(log N) · **Space:** O(1)

---

## 💻 Clean C++ Code

```cpp
/*
 * SINGLE ELEMENT IN SORTED ARRAY — binary search on parity
 *
 * KEY INSIGHT: Before single: pair starts at even index.
 *              At even mid: if arr[mid]==arr[mid+1] → single is right (lo=mid+2)
 *                           if arr[mid]!=arr[mid+1] → single is here or left (hi=mid)
 *
 * Always work with even mid for clean parity logic.
 *
 * Time O(log N) | Space O(1)
 */
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int lo = 0, hi = nums.size() - 1;

        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (mid % 2 == 1) mid--;            // ensure mid is even

            if (nums[mid] == nums[mid + 1])
                lo = mid + 2;                   // pair intact → single is right
            else
                hi = mid;                       // pair broken → single is here or left
        }

        return nums[lo];
    }
};
```

---

## 🎤 Interview Explanation Script
> "The key observation is about parity. Before the single element, every pair starts at an even index. After the single element, pairs shift to odd indices. At an even `mid`: if `arr[mid] == arr[mid+1]`, the pair is intact — the single is to the right. If `arr[mid] != arr[mid+1]`, the pairing is broken — the single is at or before `mid`."

---

## 🧾 Recall Line
> "Even `mid`. If `arr[mid]==arr[mid+1]` (pair intact) → single is right, `lo=mid+2`. Else `hi=mid`."

## 📝 Short Revision Notes
- Always force even mid: `if mid%2==1: mid--`
- `lo=mid+2` skips the entire pair (both elements)
- Edge: single at start → lo converges to 0; single at end → hi converges to n-1
- XOR approach O(N) is simpler but doesn't meet O(log N) requirement

## ⚠️ Common Mistakes
❌ Not adjusting mid to be even → inconsistent pair comparison  
❌ `lo = mid+1` instead of `mid+2` → off-by-one (doesn't skip full pair)

## 🔥 What Interviewer Is Testing
- Non-obvious binary search (no explicit sorted target)
- Parity reasoning about array structure

## 🏆 Pattern Category
`Binary Search` · `Parity`

## ⏱️ 30-Second Revision
> `lo<hi`. Make mid even. `arr[mid]==arr[mid+1]` → `lo=mid+2`. Else `hi=mid`. Return `nums[lo]`.
