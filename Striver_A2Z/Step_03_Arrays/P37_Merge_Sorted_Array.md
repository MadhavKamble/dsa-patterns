# 🔥 Merge Sorted Array

> **LeetCode #88** · **Difficulty:** Easy · **Step 3 — Arrays · P37**

---

## 🧠 Problem Understanding

**What is it asking?**
You are given two integer arrays `nums1` and `nums2`, sorted in non-decreasing order, and two integers `m` and `n`, representing the number of valid elements in `nums1` and `nums2` respectively.

- `nums1` has length `m + n`: first `m` elements are valid, last `n` elements are `0` (placeholders)
- `nums2` has length `n`

Merge `nums2` into `nums1` **in-place** so that `nums1` becomes a single sorted array.

**Input:**
```
nums1 = [1, 2, 3, 0, 0, 0], m = 3
nums2 = [2, 5, 6],          n = 3
```
**Output:** `nums1 = [1, 2, 2, 3, 5, 6]`

**Input:**
```
nums1 = [1], m = 1
nums2 = [],  n = 0
```
**Output:** `nums1 = [1]`

**Input:**
```
nums1 = [0], m = 0
nums2 = [1], n = 1
```
**Output:** `nums1 = [1]`

**Constraints:**
- `nums1.length == m + n`, `nums2.length == n`
- `0 ≤ m, n ≤ 200`, `1 ≤ m + n ≤ 200`
- `-10⁹ ≤ nums1[i], nums2[j] ≤ 10⁹`
- The last `n` elements of `nums1` are `0` — they are placeholders, not valid data

**Key Observations:**
- nums1 already has enough allocated space (m + n elements)
- If we merge from the front, we'd overwrite unprocessed elements in nums1 → wrong
- **Key insight:** Merge from the **back** — the last n positions are placeholders, so we can safely fill from index m+n-1 downward without overwriting unprocessed elements
- Compare the largest unprocessed elements from each array and place the bigger one at the current fill position

**Simple Example:**
```
nums1 = [1, 2, 3, _, _, _]   (m=3, n=3)
nums2 = [2, 5, 6]
         ↑               ↑
       p2=2             p=5  (fill from back)
       p1=2

Compare nums1[2]=3 vs nums2[2]=6 → 6 is bigger → nums1[5]=6, p2--, p--
Compare nums1[2]=3 vs nums2[1]=5 → 5 is bigger → nums1[4]=5, p2--, p--
Compare nums1[2]=3 vs nums2[0]=2 → 3 is bigger → nums1[3]=3, p1--, p--
Compare nums1[1]=2 vs nums2[0]=2 → equal (take either) → nums1[2]=2, p1--, p--
Compare nums1[0]=1 vs nums2[0]=2 → 2 bigger → nums1[1]=2, p2--, p--
p2 < 0, copy remaining nums1: nums1[0]=1 already in place
Result: [1,2,2,3,5,6] ✅
```

---

## 🥉 Brute Force Approach

### Idea
Copy nums2 into the tail of nums1, then sort the entire array.

### Algorithm
1. Copy `nums2[0..n-1]` into `nums1[m..m+n-1]`
2. Sort `nums1[0..m+n-1]`

### Complexity
- **Time:** O((m+n) log(m+n))
- **Space:** O(1) — in-place sort

### C++ Code
```cpp
// BRUTE FORCE: copy then sort
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    for (int i = 0; i < n; i++)
        nums1[m + i] = nums2[i];         // copy nums2 into tail of nums1
    sort(nums1.begin(), nums1.end());    // sort entire array
}
```

---

## 🥇 Optimal Approach — Three Pointers from the Back

### Key Observation

> 💡 If we fill `nums1` from the **back** (largest position first), we never overwrite elements that haven't been processed yet.
>
> Three pointers:
> - `p1 = m - 1`: last valid element in `nums1`
> - `p2 = n - 1`: last element in `nums2`
> - `p = m + n - 1`: current fill position in `nums1`
>
> At each step: compare `nums1[p1]` and `nums2[p2]`. Place the **larger** at `nums1[p]`, decrement the pointer of the chosen array and `p`.
>
> When `nums2` is exhausted (p2 < 0), we're done — remaining `nums1` elements are already in place.

### Why does this work?
The fill position `p` starts at `m+n-1` and moves left. The elements being written are always ≥ both `p1` and `p2`, so they're being placed in their correct final position. Since `p ≥ p1` always (fill position is always ahead of or at the read position), we never clobber unread data.

### Algorithm
1. `p1 = m - 1`, `p2 = n - 1`, `p = m + n - 1`
2. While `p1 >= 0` AND `p2 >= 0`:
   - If `nums1[p1] > nums2[p2]`: `nums1[p] = nums1[p1]`, `p1--`
   - Else: `nums1[p] = nums2[p2]`, `p2--`
   - `p--`
3. While `p2 >= 0`: `nums1[p--] = nums2[p2--]` (copy remaining nums2)
4. (No need to copy remaining nums1 — already in place)

### Dry Run

**Input:** `nums1 = [1, 2, 3, 0, 0, 0]`, `m=3`, `nums2 = [2, 5, 6]`, `n=3`

Initial: `p1=2, p2=2, p=5`

| Step | nums1[p1] | nums2[p2] | Compare | nums1[p] | p1 | p2 | p |
|------|-----------|-----------|---------|----------|----|----|---|
| 1 | 3 | 6 | 3<6 | **6** | 2 | 1 | 4 |
| 2 | 3 | 5 | 3<5 | **5** | 2 | 0 | 3 |
| 3 | 3 | 2 | 3>2 | **3** | 1 | 0 | 2 |
| 4 | 2 | 2 | 2≤2 | **2** (from nums2) | 1 | -1 | 1 |
| p2<0 → stop | | | | | | | |

Remaining `p1=1, p=1`: `nums1[0..1]` = `[1,2]` — already correct.

**Output:** `nums1 = [1, 2, 2, 3, 5, 6]` ✅

**Input:** `nums1 = [0]`, `m=0`, `nums2 = [1]`, `n=1`

Initial: `p1=-1, p2=0, p=0`

- Main while: `p1 < 0`, skip.
- Remaining nums2: `nums1[0] = nums2[0] = 1`, `p2=-1, p=-1`.

**Output:** `nums1 = [1]` ✅

### Complexity
- **Time:** O(m + n) — each element is placed exactly once
- **Space:** O(1) — in-place, no extra array

### Why is this optimal?
We must read every element at least once → Ω(m+n). The three-pointer approach achieves this exactly.

---

## 🎤 Interview Explanation Script

> "The brute force copies nums2 into the tail of nums1 and sorts — O((m+n) log(m+n)) time."

> "The key insight for O(m+n): merge from the **back**. nums1 already has m+n allocated space with the last n spots being zeros (placeholders). If I compare the largest unprocessed elements of both arrays and fill from position m+n-1 downward, I never overwrite any element before it's been processed."

> "I use three pointers: p1 at the last valid element in nums1, p2 at the last element in nums2, and p at the current fill position. I pick the larger of nums1[p1] and nums2[p2], place it at nums1[p], and advance the corresponding pointer."

> "When p2 drops below 0, I'm done — remaining nums1 elements are already sorted and in the correct positions."

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * MERGE SORTED ARRAY (LeetCode #88)
 *
 * PROBLEM UNDERSTANDING:
 *   nums1 has m valid elements + n zeros (placeholders).
 *   nums2 has n elements.
 *   Merge both sorted arrays into nums1 in-place.
 *
 * EDGE CASES:
 *   - m = 0: just copy nums2 into nums1
 *   - n = 0: nothing to do, nums1 is already correct
 *   - All nums1 elements < all nums2: p1 exhausts first, then copy nums2
 *   - All nums1 elements > all nums2: p2 exhausts first, nums1 already in place
 *
 * KEY OBSERVATION:
 *   Fill from the BACK to avoid overwriting unprocessed nums1 elements.
 *   Three pointers: p1 (end of valid nums1), p2 (end of nums2), p (fill position).
 *
 * COMPLEXITY: Time O(m+n) | Space O(1)
 */
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int p1 = m - 1;        // last valid element in nums1
        int p2 = n - 1;        // last element in nums2
        int p  = m + n - 1;    // current fill position (start from back)

        // merge from back: larger element goes to current fill position
        while (p1 >= 0 && p2 >= 0) {
            if (nums1[p1] > nums2[p2])
                nums1[p--] = nums1[p1--];   // take from nums1
            else
                nums1[p--] = nums2[p2--];   // take from nums2
        }

        // copy remaining nums2 elements (if any)
        // note: if p2 < 0, remaining nums1 elements are already in correct place
        while (p2 >= 0)
            nums1[p--] = nums2[p2--];
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "Three pointers from the back: `p1=m-1, p2=n-1, p=m+n-1`. Place larger element at `nums1[p]`. Copy remaining `nums2` if `p2 >= 0` at end."

---

## 📝 Short Revision Notes

- Fill from back = no overwrite of unprocessed data
- `p1 = m-1` (0-indexed last valid), `p2 = n-1`, `p = m+n-1`
- Loop exits when either pointer goes negative
- Only need to copy remaining `nums2` — if `p1` exhausts first, remaining `nums1` is already in place
- No need for a separate step for remaining `nums1` — it's already where it should be
- Edge: `m=0` — entire loop is the `while (p2 >= 0)` part
- Edge: `n=0` — both loops are skipped, nums1 already correct

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "Merge two sorted arrays in-place"
- "Extra space at end of first array"
- "Don't return, modify in-place"

**I should think of:** Three pointers from the back (reverse two-pointer merge)

---

## ⚠️ Common Mistakes

❌ Merging from the **front** → overwrites unprocessed `nums1` elements  
❌ Forgetting the remaining `nums2` copy after main loop  
❌ Adding a remaining `nums1` copy — unnecessary (it's already in place)  
❌ `while (p1 >= 0)` after main loop — wastes operations, elements are already correct  
❌ Using `>` vs `>=` in comparison — both work, just affects stability (which copy of equal values comes first)  

---

## 🔥 What Interviewer Is Testing

- **Concept:** Reverse-direction two-pointer merge
- **Reasoning:** Why filling from back avoids overwrite
- **Observation:** No need to handle remaining `nums1` elements
- **Edge cases:** m=0 and n=0 handling

---

## 🚀 Alternative Approaches

| Approach | Time | Space | Notes |
|----------|------|-------|-------|
| Three pointers from back | O(m+n) | O(1) | Optimal |
| Copy + sort | O((m+n) log(m+n)) | O(1) | Simple but slow |
| Extra array merge | O(m+n) | O(m+n) | Standard merge, wastes space |

---

## 📚 Related Problems

- [ ] LeetCode #88 — Merge Sorted Array
- [ ] LeetCode #21 — Merge Two Sorted Lists (same idea, linked list)
- [ ] Striver Step 2 P04 — Merge Sort (merge step is similar but forward direction)
- [ ] LeetCode #4 — Median of Two Sorted Arrays (partition-based, harder)

---

## 🏆 Pattern Category

`Arrays` · `Two Pointers` · `In-Place` · `Sorting`

---

## 🎯 Difficulty Analysis

**Rating:** Easy

**Why challenging:** The direction is the counter-intuitive part — most people instinctively try to merge forward and hit the overwrite problem. Once you realize "fill from back," the rest is a standard merge.

---

## 📈 Progression Insight

**This problem appears in interviews as a warmup.** The follow-up questions are:
1. What if nums1 doesn't have extra space? → Need extra array or Gap Method
2. What if there are K sorted arrays? → K-way merge with a heap
3. What's the time complexity of the sort-based approach vs this? → O((m+n) log(m+n)) vs O(m+n)

---

## ⏱️ 30-Second Last-Minute Revision

> **Problem:** Merge nums2 into nums1 in-place. nums1 has m valid + n zeros.  
> **Approach:** `p1=m-1, p2=n-1, p=m+n-1`. While both valid: place `max(nums1[p1], nums2[p2])` at `nums1[p]`. Copy remaining nums2.  
> **Key trick:** Fill from back — no overwrite. Remaining nums1 is already in place.  
> **Time:** O(m+n) | **Space:** O(1)  
> **Watch out for:** Only copy remaining nums2, NOT remaining nums1
