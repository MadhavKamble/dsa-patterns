# 🔥 Insertion Sort

> **Step 2 — Sorting Techniques · P03**  
> **Difficulty:** Easy · **LeetCode #147** (Insertion Sort List)

---

## 🧠 Problem Understanding

**What is it asking?**  
Sort an array using Insertion Sort — build the sorted portion one element at a time by inserting each new element into its correct position.

**Core Idea:** Like sorting playing cards in hand — pick one card at a time and insert it into the correct position among the already-sorted cards.

**Key Observations:**
- The left portion `arr[0..i]` is always sorted
- For each new element, shift larger elements right and insert current element
- Excellent for nearly-sorted data: O(NK) where K = max displacement
- Only O(N) swaps/shifts on nearly-sorted data

**Simple Example:**
```
arr = [12, 11, 13, 5, 6]
i=1: key=11, shift 12 right → [11,12,13,5,6]
i=2: key=13, 13>12 no shift → [11,12,13,5,6]
i=3: key=5,  shift 13,12,11 right → [5,11,12,13,6]
i=4: key=6,  shift 13,12,11 right → [5,6,11,12,13]
```

---

## 🥇 The Algorithm

### Key Observation

> 💡 At step `i`, elements `arr[0..i-1]` are sorted. Pick `arr[i]` as `key`.  
> Shift all elements in `arr[0..i-1]` that are greater than `key` one position right.  
> Insert `key` in the gap created.

```
Invariant: arr[0..i] is sorted at the end of iteration i.
```

### Algorithm
1. For `i` from `1` to `N-1`:
   - `key = arr[i]`
   - `j = i - 1`
   - While `j >= 0` and `arr[j] > key`:
     - `arr[j+1] = arr[j]` (shift right)
     - `j--`
   - `arr[j+1] = key` (insert)

### Dry Run

**Input:** `[8, 4, 1, 5, 9, 2]`

| i | key | j shifts | Array after insert |
|---|-----|----------|--------------------|
| 1 | 4 | shift 8 | **[4, 8**, 1, 5, 9, 2] |
| 2 | 1 | shift 8, shift 4 | **[1, 4, 8**, 5, 9, 2] |
| 3 | 5 | shift 8 | **[1, 4, 5, 8**, 9, 2] |
| 4 | 9 | no shifts | **[1, 4, 5, 8, 9**, 2] |
| 5 | 2 | shift 9,8,5,4 | **[1, 2, 4, 5, 8, 9]** |

**Output:** `[1, 2, 4, 5, 8, 9]` ✅

### Complexity
- **Time:** O(N²) worst, **O(N) best** (sorted input — inner while never executes)
- **Space:** O(1) in-place

### Why best case is O(N)?
If array is already sorted, `arr[j] > key` is never true → inner while loop runs 0 times → just N-1 iterations of outer loop.

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * INSERTION SORT
 *
 * IDEA: Build sorted portion left to right.
 *       For each element, shift larger sorted elements right, insert current.
 *
 * ANALOGY: Sorting playing cards — pick one, insert into correct position in hand.
 *
 * INVARIANT: arr[0..i] is sorted after processing index i.
 *
 * COMPLEXITY:
 *   Best (sorted): O(N) | Average/Worst: O(N²) | Space: O(1)
 *
 * STABLE: YES — equal elements never pass each other (strictly > comparison)
 * ADAPTIVE: YES — O(N + inversions), nearly-sorted input is very fast
 */

class Solution {
public:
    void insertionSort(vector<int>& arr) {
        int n = arr.size();

        for (int i = 1; i < n; i++) {
            int key = arr[i];    // element to be inserted into sorted portion
            int j = i - 1;

            // shift elements of arr[0..i-1] that are greater than key
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];   // shift right
                j--;
            }

            arr[j + 1] = key;          // insert key at correct position
        }
    }
};
```

---

## 🎤 Interview Explanation Script

> "Insertion Sort builds the sorted array one element at a time, from left to right."

> "At step `i`, I treat `arr[0..i-1]` as already sorted and `arr[i]` as the new card to insert. I shift all sorted elements greater than `arr[i]` one position right, then drop `arr[i]` into the gap."

> "Best case is O(N) — a sorted array never triggers the inner while loop. Worst case is O(N²) — reverse-sorted input shifts every element every time."

> "It's stable because we use strict `>` — equal elements are never moved past each other. It's also adaptive — nearly-sorted input runs much faster than random input."

> "In practice, Insertion Sort is often used for small subarrays (size ≤ 10–16) inside Timsort and Introsort."

---

## 🧾 Recall Line *(10-Second Revision)*

> "Pick `key=arr[i]`, shift `arr[j]>key` rightward, insert key at gap. O(N) best, O(N²) worst."

---

## 📝 Short Revision Notes

- Builds sorted prefix `arr[0..i]` by inserting `arr[i]` in correct position
- Inner loop: shift while `arr[j] > key` AND `j >= 0`
- **Stable** ✅ · **Adaptive** ✅ (faster on nearly-sorted)
- Best O(N) for sorted, Worst O(N²) for reverse-sorted
- Number of comparisons = number of inversions + N-1
- Preferred over Bubble/Selection for nearly-sorted data
- Used inside Timsort (Python's sort) for small subarrays

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "nearly sorted array" → Insertion Sort is O(NK)
- "online sorting" (sort stream one element at a time)
- "stable sort with O(1) space"
- Small N (< 16) as subroutine in hybrid sorts

**I should think of:** Insertion Sort

---

## ⚠️ Common Mistakes

❌ `while (j >= 0 && arr[j] > key)` → wrong order: check `j >= 0` FIRST (short-circuit prevents out-of-bounds)  
❌ Starting outer loop at `i=0` instead of `i=1` — first element is trivially sorted  
❌ Using `arr[j] >= key` → makes it unstable (unnecessary shifts of equal elements)  
❌ Assigning `arr[j+1] = key` inside the while loop instead of after  

---

## 🔥 What Interviewer Is Testing

- **Concept:** The insertion invariant
- **Optimization:** Why best case is O(N) (adaptive property)
- **Stability:** How strict comparison preserves stability

---

## 🚀 Insertion Sort vs. Shell Sort

**Shell Sort** is a generalization of Insertion Sort:
- Instead of shifting by 1, shift by gap `h` (h=5,3,1 in Shell's sequence)
- Reduces inversions rapidly, then final pass with h=1 (regular Insertion Sort) is nearly O(N)
- Complexity ~O(N^1.3) in practice

---

## 📚 Related Problems

- [ ] LeetCode #147 — Insertion Sort List (linked list version)
- [ ] LeetCode #912 — Sort an Array
- [ ] Striver Step 2 P06 — Recursive Insertion Sort
- [ ] Striver Step 2 P04 — Merge Sort (stable O(N log N) alternative)

---

## 🏆 Pattern Category

`Sorting` · `Arrays` · `In-Place` · `Stable` · `Adaptive`

---

## ⏱️ 30-Second Last-Minute Revision

> **Idea:** For each `i` from 1 to N-1: save `key=arr[i]`, shift `arr[j]>key` right, insert key  
> **Time:** O(N) best (sorted) · O(N²) worst · **Space:** O(1) · **Stable:** Yes  
> **Adaptive:** Inversions = work done — great for nearly-sorted data  
> **Watch out for:** Check `j >= 0` before `arr[j] > key` in while condition
