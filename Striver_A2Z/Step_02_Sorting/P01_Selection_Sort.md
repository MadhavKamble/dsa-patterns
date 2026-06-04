# 🔥 Selection Sort

> **Step 2 — Sorting Techniques · P01**  
> **Difficulty:** Easy · **LeetCode #912** (Sort an Array)

---

## 🧠 Problem Understanding

**What is it asking?**  
Sort an array of N integers in ascending order using the Selection Sort algorithm.

**Core Idea:** Find the minimum element in the unsorted portion and place it at the correct position.

**Input:** Unsorted array of integers  
**Output:** Sorted array in ascending order

**Key Observations:**
- After each pass `i`, the first `i+1` elements are sorted
- Makes exactly N-1 passes
- Each pass finds the minimum in `arr[i..N-1]` and swaps it to position `i`

**Simple Example:**
```
arr = [64, 25, 12, 22, 11]
Pass 1: min=11 at index 4 → swap(0,4) → [11, 25, 12, 22, 64]
Pass 2: min=12 at index 2 → swap(1,2) → [11, 12, 25, 22, 64]
Pass 3: min=22 at index 3 → swap(2,3) → [11, 12, 22, 25, 64]
Pass 4: min=25 at index 3 → no swap   → [11, 12, 22, 25, 64]
```

---

## 🥇 The Algorithm

### Key Observation

> 💡 In each pass `i`, select the minimum from `arr[i]` to `arr[N-1]` and swap it into position `i`. After pass `i`, elements `arr[0..i]` are in their final sorted positions.

```
Invariant: After pass i, arr[0..i] is sorted and contains the i+1 smallest elements.
```

### Algorithm
1. For `i` from `0` to `N-2`:
   - Find index `minIdx` of minimum element in `arr[i..N-1]`
   - Swap `arr[i]` with `arr[minIdx]`
2. Done — array is sorted

### Dry Run

**Input:** `[64, 25, 12, 22, 11]`

| Pass i | Unsorted range | minIdx | Swap | Array after pass |
|--------|---------------|--------|------|-----------------|
| 0 | [0..4] | 4 (val=11) | swap(0,4) | **11** 25 12 22 64 |
| 1 | [1..4] | 2 (val=12) | swap(1,2) | 11 **12** 25 22 64 |
| 2 | [2..4] | 3 (val=22) | swap(2,3) | 11 12 **22** 25 64 |
| 3 | [3..4] | 3 (val=25) | no swap   | 11 12 22 **25** 64 |

**Output:** `[11, 12, 22, 25, 64]` ✅

### Complexity
- **Time:** O(N²) — always, even for sorted arrays (no early exit)
- **Space:** O(1) — in-place

### Why O(N²)?
Pass 0 does N-1 comparisons, pass 1 does N-2, ..., pass N-2 does 1.  
Total = (N-1) + (N-2) + ... + 1 = N(N-1)/2 = O(N²)

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * SELECTION SORT
 *
 * IDEA: In each pass i, find minimum in arr[i..N-1] and swap to position i.
 *
 * INVARIANT: After pass i, arr[0..i] contains final sorted elements.
 *
 * COMPLEXITY: Time O(N²) | Space O(1)
 *
 * WHEN TO USE: Small arrays, when writes are expensive (fewest swaps: O(N))
 * WHEN NOT: Large arrays — O(N²) is too slow
 */

class Solution {
public:
    void selectionSort(vector<int>& arr) {
        int n = arr.size();

        for (int i = 0; i < n - 1; i++) {
            int minIdx = i;                          // assume current position is min

            // find actual minimum in unsorted portion arr[i+1..n-1]
            for (int j = i + 1; j < n; j++) {
                if (arr[j] < arr[minIdx])
                    minIdx = j;
            }

            // place minimum at position i
            if (minIdx != i)
                swap(arr[i], arr[minIdx]);
        }
    }
};
```

---

## 🎤 Interview Explanation Script

> "Selection Sort works by repeatedly selecting the minimum element from the unsorted portion and placing it at the front."

> "In each pass `i`, I scan from index `i` to `N-1` to find the minimum, then swap it to position `i`."

> "After `i` passes, the first `i` elements are in their final sorted positions."

> "Time complexity is always O(N²) — even on a sorted array, we still scan the full unsorted portion. Space is O(1)."

> "Its one advantage: it makes at most O(N) swaps — the fewest of any comparison sort. This is useful when writes are expensive."

---

## 🧾 Recall Line *(10-Second Revision)*

> "Each pass: find min in `arr[i..N-1]`, swap to index `i`. O(N²) time, O(N) swaps."

---

## 📝 Short Revision Notes

- N-1 passes; pass `i` selects min from `arr[i..N-1]`
- Not stable — equal elements may be reordered (swap can skip over equal elements)
- Always O(N²) — no best-case optimization
- Advantage: minimum number of swaps — O(N) total swaps
- In-place: O(1) space
- Use when: memory writes are expensive; small arrays

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "sort with minimum number of writes/swaps"
- "sort small array in-place"

**I should think of:** Selection Sort (minimum swaps), or check if a better O(N log N) sort is needed

---

## ⚠️ Common Mistakes

❌ Looping outer to `N` instead of `N-1` — last element is automatically in place  
❌ Forgetting to check `minIdx != i` before swapping (wastes a swap)  
❌ Claiming Selection Sort is stable — it is **NOT** stable  
❌ Inner loop starting at `i` instead of `i+1` — comparing element with itself  

---

## 🔥 What Interviewer Is Testing

- **Concept:** Understanding the selection invariant
- **Reasoning:** Why O(N²), why not stable, when it has an advantage
- **Key insight:** Fewest swaps among simple sorts → useful in specific hardware contexts

---

## 🚀 Comparison with Other Sorts

| Sort | Best | Average | Worst | Space | Stable | Swaps |
|------|------|---------|-------|-------|--------|-------|
| Selection | O(N²) | O(N²) | O(N²) | O(1) | ❌ | O(N) |
| Bubble | O(N) | O(N²) | O(N²) | O(1) | ✅ | O(N²) |
| Insertion | O(N) | O(N²) | O(N²) | O(1) | ✅ | O(N²) |
| Merge | O(N log N) | O(N log N) | O(N log N) | O(N) | ✅ | — |
| Quick | O(N log N) | O(N log N) | O(N²) | O(log N) | ❌ | — |

---

## 📚 Related Problems

- [ ] LeetCode #912 — Sort an Array (use merge/quick sort)
- [ ] LeetCode #75 — Sort Colors (Dutch National Flag — O(N))
- [ ] Striver Step 2 P02 — Bubble Sort
- [ ] Striver Step 2 P03 — Insertion Sort

---

## 🏆 Pattern Category

`Sorting` · `Arrays` · `In-Place`

---

## 🎯 Difficulty Analysis

**Rating:** Easy  
**Why:** The logic is straightforward. The interview value is in understanding *why* it's O(N²), *why* it's not stable, and *when* it has an edge over other sorts (fewest swaps).

---

## 📈 Progression Insight

**Harder variant:** Sort a nearly-sorted array → Insertion Sort is better (O(NK) for K-sorted)  
**Optimal:** For general sorting → Merge Sort (stable, O(N log N)) or Quick Sort (cache-friendly, O(N log N) avg)

---

## ⏱️ 30-Second Last-Minute Revision

> **Idea:** Pass `i`: find min in `arr[i..N-1]`, swap to `i`  
> **Time:** O(N²) always · **Space:** O(1) · **Stable:** No  
> **Unique advantage:** Only O(N) swaps total — fewest writes among simple sorts  
> **Watch out for:** Not stable; no best-case improvement
