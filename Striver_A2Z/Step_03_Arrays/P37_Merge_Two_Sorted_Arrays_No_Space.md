# 🔥 Merge Two Sorted Arrays Without Extra Space

> **LeetCode #88** (variant — no extra space) · **Difficulty:** Hard · **Step 3 — Arrays · P37**

---

## 🧠 Problem Understanding

**What is it asking?**
Given two sorted arrays `arr1[0..M-1]` and `arr2[0..N-1]`, merge them **in-place** such that `arr1` contains the M smallest elements and `arr2` contains the N largest, both in sorted order — without using any extra space.

**Input:** `arr1 = [1, 4, 8, 10]`, `arr2 = [2, 3, 9]`
**Output:** `arr1 = [1, 2, 3, 4]`, `arr2 = [8, 9, 10]`

**Constraints:** O(1) extra space, both arrays sorted afterward

**Key Observations:**
- We can't use an extra array (that's the whole challenge)
- Swapping only works when `arr1[i] > arr2[j]` — move larger to arr2 and smaller to arr1
- Simple O(M×N) swap approach: for each element of arr1, swap with the minimum of arr2, then sort arr2
- Optimal: **Gap method** (Shell Sort idea) — compare elements `gap` positions apart across the combined array, swap if needed, halve gap

**Simple Example:**
```
Combined virtual array: [1, 4, 8, 10 | 2, 3, 9]
Goal:                   [1, 2, 3, 4  | 8, 9, 10]
```

---

## 🥉 Brute Force Approach

### Idea
Use an extra array: copy both, sort, split back.

### Algorithm
1. Copy all M+N elements to `temp`
2. Sort `temp`
3. Copy first M back to `arr1`, last N back to `arr2`

### Complexity
- **Time:** O((M+N) log(M+N))
- **Space:** O(M+N) — violates the constraint

---

## 🥈 Better Approach — Two Pointer Swap

### Idea
For each element in `arr1`, compare with the minimum element in `arr2`. If `arr1[i] > arr2[0]`, swap them, then sort `arr2` to restore its sorted order (or use insertion to reinsert).

### Algorithm
1. For `i` from 0 to M-1:
   - If `arr1[i] > arr2[0]`:
     - Swap `arr1[i]` with `arr2[0]`
     - Re-sort `arr2` (or insert `arr2[0]` in sorted position)

### Complexity
- **Time:** O(M × N) in worst case
- **Space:** O(1)

---

## 🥇 Optimal Approach — Gap Method

### Key Observation

> 💡 The **Gap Method** from Shell Sort:
> 1. Treat both arrays as one virtual combined array of size M+N
> 2. Start with `gap = ceil((M+N) / 2)`
> 3. Compare every pair of elements that are `gap` apart — swap if the left is greater than the right
> 4. Halve the gap: `gap = ceil(gap / 2)` and repeat until `gap == 0`
>
> After all gap passes, the combined array is sorted. The first M elements stay in `arr1`, the last N in `arr2`.

### Why does it work?
This is the same principle as Shell Sort: large gaps fix big inversions first; as the gap shrinks, finer-grained inversions are fixed. The final gap of 1 ensures full sortedness.

### Accessing the virtual array:
For index `k` in the combined array:
- If `k < M`: it's `arr1[k]`
- Else: it's `arr2[k - M]`

### Gap formula:
`gap = ceil(gap / 2) = (gap + 1) / 2` (integer ceiling division)

### Algorithm
1. `gap = (M + N + 1) / 2` (initial gap)
2. While `gap > 0`:
   a. For all pairs `(i, i+gap)` in the combined virtual array:
      - Get `left = virtualArr[i]`, `right = virtualArr[i+gap]`
      - If `left > right`: swap them
   b. `gap = (gap + 1) / 2`
   c. If `gap == 1`: do one final pass and break (to avoid infinite loop)

### Dry Run

**Input:** `arr1 = [1, 5, 9, 10, 15, 20]`, `arr2 = [2, 3, 8, 13]`
M=6, N=4, total=10

**Initial gap = `(10+1)/2 = 5`**

Virtual: `[1, 5, 9, 10, 15, 20 | 2, 3, 8, 13]`
(indices: 0  1  2   3   4   5    6  7  8   9)

Pairs with gap=5: (0,5),(1,6),(2,7),(3,8),(4,9)
- (0,5): arr1[0]=1 vs arr1[5]=20 → 1<20, no swap
- (1,6): arr1[1]=5 vs arr2[0]=2 → 5>2, **swap** → arr1[1]=2, arr2[0]=5
- (2,7): arr1[2]=9 vs arr2[1]=3 → 9>3, **swap** → arr1[2]=3, arr2[1]=9
- (3,8): arr1[3]=10 vs arr2[2]=8 → 10>8, **swap** → arr1[3]=8, arr2[2]=10
- (4,9): arr1[4]=15 vs arr2[3]=13 → 15>13, **swap** → arr1[4]=13, arr2[3]=15

After gap=5: `arr1=[1,2,3,8,13,20]`, `arr2=[5,9,10,15]`

**gap = (5+1)/2 = 3**

Virtual: `[1, 2, 3, 8, 13, 20 | 5, 9, 10, 15]`

Pairs with gap=3: (0,3),(1,4),(2,5),(3,6),(4,7),(5,8),(6,9)
- (3,6): 8 vs 5 → **swap** → arr1[3]=5, arr2[0]=8
- (4,7): 13 vs 9 → **swap** → arr1[4]=9, arr2[1]=13
- (5,8): 20 vs 10 → **swap** → arr1[5]=10, arr2[2]=20

After gap=3: `arr1=[1,2,3,5,9,10]`, `arr2=[8,13,20,15]`

**gap = (3+1)/2 = 2**... (continuing until gap=1, final pass sorts completely)

**Final:** `arr1=[1,2,3,5,8,9]`, `arr2=[10,13,15,20]` ✅

### Complexity
- **Time:** O((M+N) × log(M+N)) — O(log(M+N)) gap passes, O(M+N) per pass
- **Space:** O(1) — purely in-place

---

## 🎤 Interview Explanation Script

> "The constraint is O(1) space, so we can't use an extra array."

> "The naive approach swaps `arr1[i]` with `arr2[0]` whenever `arr1[i] > arr2[0]`, then re-sorts arr2. That's O(M × N) — too slow."

> "The optimal is the Gap Method, borrowed from Shell Sort. We treat both arrays as one virtual array. We start with a large gap — `ceil((M+N)/2)` — and compare all pairs that are `gap` apart, swapping if out of order. Then we halve the gap and repeat. The large gap fixes big-distance inversions first; smaller gaps clean up remaining ones. Final complexity: O((M+N) log(M+N)) with O(1) space."

> "Key implementation detail: `gap = (gap + 1) / 2` for ceiling division. When gap reaches 1, that final pass guarantees full sortedness."

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * MERGE TWO SORTED ARRAYS WITHOUT EXTRA SPACE — Gap Method
 *
 * PROBLEM UNDERSTANDING:
 *   Merge arr1[0..M-1] and arr2[0..N-1] in-place without extra space.
 *   After merge: arr1 has M smallest, arr2 has N largest, both sorted.
 *
 * KEY OBSERVATION:
 *   Gap method (Shell Sort idea): compare pairs gap-apart in virtual combined array.
 *   Large gap fixes big inversions; shrinking gap fixes smaller ones.
 *
 * VIRTUAL ARRAY ACCESS: index k → arr1[k] if k<M, arr2[k-M] if k>=M
 *
 * COMPLEXITY: Time O((M+N) log(M+N)) | Space O(1)
 */
class Solution {
private:
    // get/set element in virtual combined array
    int& getElem(vector<int>& a, vector<int>& b, int k) {
        return (k < (int)a.size()) ? a[k] : b[k - (int)a.size()];
    }

public:
    void merge(vector<int>& arr1, int m, vector<int>& arr2, int n) {
        int total = m + n;
        int gap = (total + 1) / 2;    // ceil(total / 2)

        while (gap > 0) {
            // compare all pairs (i, i+gap) in the virtual combined array
            for (int i = 0; i + gap < total; i++) {
                int j = i + gap;
                // map to actual arrays
                int& left  = (i < m) ? arr1[i]     : arr2[i - m];
                int& right = (j < m) ? arr1[j]     : arr2[j - m];

                if (left > right) swap(left, right);
            }

            if (gap == 1) break;              // avoid infinite loop
            gap = (gap + 1) / 2;              // ceiling division
        }
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "Gap method: virtual combined array, compare pairs `gap` apart, swap if needed, halve gap. `gap = (gap+1)/2`. O((M+N)log(M+N)) / O(1)."

---

## 📝 Short Revision Notes

- Gap formula: `(gap + 1) / 2` for ceiling (not `gap / 2`)
- Virtual access: index `k` → `arr1[k]` if `k < M`, else `arr2[k-M]`
- `if (gap == 1) break` prevents infinite loop (1 → (1+1)/2 = 1 again)
- Alternative O(M+N) space: use extra array and copy back
- This is the standard Shell Sort principle applied to a 2-array merge problem
- LeetCode #88 allows O(M+N) space (extra array), this GFG variant requires O(1)

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "Merge two sorted arrays, O(1) space"
- "In-place merge"

**I should think of:** Gap method (Shell Sort principle)

---

## ⚠️ Common Mistakes

❌ `gap = gap / 2` instead of `(gap + 1) / 2` — undercounts for odd gaps  
❌ Not including `if (gap == 1) break` — infinite loop  
❌ Wrong virtual array indexing: off-by-one when crossing the arr1/arr2 boundary  
❌ Initializing gap as `(M + N) / 2` (floor) instead of ceiling → may miss first gap value  

---

## 🔥 What Interviewer Is Testing

- **Concept:** Shell Sort's gap-based comparison as an in-place merge technique
- **Reasoning:** Why the gap approach works (large inversions → small inversions)
- **Implementation:** Clean virtual array access across two separate arrays

---

## 🚀 Alternative Approaches

| Approach | Time | Space | Notes |
|----------|------|-------|-------|
| Gap method | O((M+N) log(M+N)) | O(1) | Optimal for O(1) space |
| Naive swap + re-sort | O(M×N) | O(1) | Simpler but slower |
| Extra array | O(M+N) | O(M+N) | LeetCode #88 standard |

---

## 📚 Related Problems

- [ ] LeetCode #88 — Merge Sorted Array (with extra space)
- [ ] LeetCode #21 — Merge Two Sorted Lists (linked list version)
- [ ] Striver Step 2 P04 — Merge Sort (uses merge as subroutine)
- [ ] Striver Step 3 P39 — Count Inversions (merge sort counting)

---

## 🏆 Pattern Category

`Arrays` · `Sorting` · `Two Pointers` · `Shell Sort`

---

## 🎯 Difficulty Analysis

**Rating:** Hard

**Why challenging:** The O(1) space constraint rules out all obvious approaches. The Gap Method is non-intuitive without knowing Shell Sort, making this a test of algorithm breadth.

---

## 📈 Progression Insight

**Easier version:** LeetCode #88 — same problem but arr1 has M+N allocated space, just fill from the back with two pointers.

**Pattern generalization:** The gap-halving idea from Shell Sort is also used in: Bitonic Sort, optimized Bubble Sort variants, parallel comparison networks.

---

## ⏱️ 30-Second Last-Minute Revision

> **Problem:** Merge two sorted arrays in-place, O(1) space  
> **Approach:** Gap method. `gap = ceil((M+N)/2)`. Compare pairs `(i, i+gap)` across virtual combined array. Swap if needed. `gap = ceil(gap/2)`. Stop after gap=1 pass.  
> **Key trick:** `gap = (gap+1)/2` for ceiling; `break` when gap was 1  
> **Time:** O((M+N) log(M+N)) | **Space:** O(1)  
> **Watch out for:** Ceiling division, not floor; `if gap==1: break`
