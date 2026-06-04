# 🔥 Bubble Sort

> **Step 2 — Sorting Techniques · P02**  
> **Difficulty:** Easy · **LeetCode #912** (Sort an Array)

---

## 🧠 Problem Understanding

**What is it asking?**  
Sort an array using Bubble Sort — repeatedly compare adjacent elements and swap if out of order.

**Core Idea:** In each pass, the largest unsorted element "bubbles up" to its correct position at the end.

**Key Observations:**
- After pass `i`, the last `i+1` elements are in their final sorted positions
- Can detect a sorted array early: if no swaps happen in a pass → array is already sorted
- The only simple sort with a genuine O(N) best case (with the early exit optimization)

**Simple Example:**
```
arr = [5, 4, 3, 2, 1]
Pass 1: compare pairs → [4,3,2,1,5]  (5 bubbles to end)
Pass 2: compare pairs → [3,2,1,4,5]  (4 bubbles to pos 3)
Pass 3: compare pairs → [2,1,3,4,5]
Pass 4: compare pairs → [1,2,3,4,5]
```

---

## 🥉 Brute Force (No Optimization)

### Algorithm
1. For `i` from `0` to `N-2`:
   - For `j` from `0` to `N-2-i`:
     - If `arr[j] > arr[j+1]`: swap them

### Complexity
- **Time:** O(N²) always · **Space:** O(1)

```cpp
void bubbleSortBrute(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}
```

---

## 🥇 Optimal — With Early Exit (Best Case O(N))

### Key Observation

> 💡 If a complete pass happens with **zero swaps**, the array is already sorted. Stop early.  
> This gives O(N) on an already-sorted array.

### Algorithm
1. For `i` from `0` to `N-2`:
   - Set `swapped = false`
   - For `j` from `0` to `N-2-i`:
     - If `arr[j] > arr[j+1]`: swap, set `swapped = true`
   - If `!swapped`: break (array is sorted)

### Dry Run

**Input:** `[64, 34, 25, 12, 22, 11, 90]`

| Pass i | Key swaps | Array after | Swapped? |
|--------|-----------|-------------|----------|
| 0 | 90 bubbles to end | [34,25,12,22,11,64,**90**] | ✅ |
| 1 | 64 bubbles to pos 5 | [25,12,22,11,34,**64**,90] | ✅ |
| 2 | 34 bubbles to pos 4 | [12,22,11,25,**34**,64,90] | ✅ |
| 3 | 25 bubbles to pos 3 | [12,11,22,**25**,34,64,90] | ✅ |
| 4 | 22 bubbles to pos 2 | [11,12,**22**,25,34,64,90] | ✅ |
| 5 | no swap needed | [11,**12**,22,25,34,64,90] | ❌ → break |

**Output:** `[11, 12, 22, 25, 34, 64, 90]` ✅

**Already sorted input: `[1,2,3,4,5]`**
- Pass 0: no swaps → `swapped=false` → break immediately
- **Total: O(N) comparisons only**

### Complexity
- **Time:** O(N²) worst/average, **O(N) best** (sorted input with early exit)
- **Space:** O(1)

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * BUBBLE SORT (OPTIMIZED)
 *
 * IDEA: Each pass bubbles the largest unsorted element to its final position.
 *       If no swap in a full pass → array is sorted → stop early.
 *
 * INVARIANT: After pass i, arr[N-1-i..N-1] is sorted and finalized.
 *
 * COMPLEXITY:
 *   Worst/Average: O(N²) | Best (sorted): O(N) | Space: O(1)
 *
 * STABLE: YES — equal elements are never swapped (strict > comparison)
 */

class Solution {
public:
    void bubbleSort(vector<int>& arr) {
        int n = arr.size();

        for (int i = 0; i < n - 1; i++) {
            bool swapped = false;                    // early exit flag

            // bubble largest in arr[0..n-1-i] to position n-1-i
            for (int j = 0; j < n - 1 - i; j++) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            }

            if (!swapped) break;                     // already sorted
        }
    }
};
```

---

## 🎤 Interview Explanation Script

> "Bubble Sort works by repeatedly comparing adjacent elements and swapping them if they're in the wrong order. The largest element bubbles to the end in each pass."

> "The naive version is always O(N²). The key optimization is an early exit: if we complete a pass with zero swaps, the array is already sorted — we stop. This gives O(N) best case."

> "It's stable because we only swap when `arr[j] > arr[j+1]` — equal elements are never moved past each other."

> "Worst case is O(N²) — reverse sorted input — and it uses O(1) space."

---

## 🧾 Recall Line *(10-Second Revision)*

> "Adjacent swaps, largest bubbles up each pass. `swapped` flag → O(N) best case on sorted input."

---

## 📝 Short Revision Notes

- Inner loop range shrinks each pass: `j < N-1-i` (last `i` elements already sorted)
- Early exit: `bool swapped`; if no swap in full pass → break
- **Stable** ✅ (only swap strict `>`, never `>=`)
- Best: O(N), Average/Worst: O(N²), Space: O(1)
- Most swaps among simple sorts: O(N²) swaps in worst case
- Good for: nearly-sorted data (O(NK) where K = max displacement)

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "detect if array is sorted" → Bubble Sort with early exit shows it in O(N)
- "adjacent element comparisons"
- "stable, in-place sort for small/nearly-sorted data"

**I should think of:** Bubble Sort with `swapped` optimization

---

## ⚠️ Common Mistakes

❌ Inner loop: `j < N-1` instead of `j < N-1-i` — redundant comparisons  
❌ Forgetting `swapped` flag → losing the O(N) best case, defeats a key interview talking point  
❌ Using `>=` in comparison → makes it unstable (equal elements get unnecessarily swapped)  
❌ Outer loop to `N` instead of `N-1` — last element is trivially in place  

---

## 🔥 What Interviewer Is Testing

- **Concept:** Adjacent swaps and the bubble-up invariant
- **Optimization:** Early exit `swapped` flag for O(N) best case
- **Stability:** Why it's stable and why that matters

---

## 🚀 Comparison with Other Sorts

| Sort | Best | Average | Worst | Space | Stable |
|------|------|---------|-------|-------|--------|
| **Bubble** | **O(N)** | O(N²) | O(N²) | O(1) | ✅ |
| Selection | O(N²) | O(N²) | O(N²) | O(1) | ❌ |
| Insertion | O(N) | O(N²) | O(N²) | O(1) | ✅ |

---

## 📚 Related Problems

- [ ] LeetCode #912 — Sort an Array
- [ ] Striver Step 2 P01 — Selection Sort
- [ ] Striver Step 2 P05 — Recursive Bubble Sort
- [ ] Striver Step 2 P03 — Insertion Sort (also O(N) best case, but faster in practice)

---

## 🏆 Pattern Category

`Sorting` · `Arrays` · `In-Place` · `Stable`

---

## ⏱️ 30-Second Last-Minute Revision

> **Idea:** Each pass: compare adj pairs, swap if `arr[j] > arr[j+1]`. Largest bubbles to end.  
> **Optimize:** `bool swapped = false` each pass; if no swap → break  
> **Time:** O(N) best, O(N²) worst · **Space:** O(1) · **Stable:** Yes  
> **Watch out for:** Inner loop bound is `N-1-i`, not `N-1`
