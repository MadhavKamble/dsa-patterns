# 🔥 Quick Sort

> **Step 2 — Sorting Techniques · P07**  
> **Difficulty:** Medium · **LeetCode #912** (Sort an Array)

---

## 🧠 Problem Understanding

**What is it asking?**  
Sort an array using Quick Sort — a divide-and-conquer algorithm that selects a pivot, partitions around it, then recursively sorts both sides.

**Core Idea:** Place one element (pivot) in its exact final position so that all elements to its left are smaller and all to its right are larger. Then recursively sort left and right parts.

**Key Observations:**
- Pivot ends up in its correct sorted position after partition
- No merge step needed — sorting happens in-place during partition
- Average O(N log N), worst O(N²) (but rare with good pivot)
- Not stable, but cache-friendly and in-place → fastest in practice

---

## 🧩 Lomuto Partition Scheme

### Key Observation

> 💡 Pick `arr[high]` as pivot. Maintain pointer `i` at the "boundary" of elements ≤ pivot. When we find `arr[j] <= pivot`, expand the boundary by swapping `arr[++i]` with `arr[j]`. Finally, place pivot at `i+1`.

```
arr = [10, 80, 30, 90, 40, 50, 70], pivot = arr[6] = 70
i = -1 (nothing ≤ pivot yet)

j=0: arr[0]=10 ≤ 70 → i=0, swap(arr[0],arr[0]) → [10, 80, 30, 90, 40, 50, 70]
j=1: arr[1]=80 > 70 → skip
j=2: arr[2]=30 ≤ 70 → i=1, swap(arr[1],arr[2]) → [10, 30, 80, 90, 40, 50, 70]
j=3: arr[3]=90 > 70 → skip
j=4: arr[4]=40 ≤ 70 → i=2, swap(arr[2],arr[4]) → [10, 30, 40, 90, 80, 50, 70]
j=5: arr[5]=50 ≤ 70 → i=3, swap(arr[3],arr[5]) → [10, 30, 40, 50, 80, 90, 70]

Place pivot: swap(arr[i+1], arr[high]) = swap(arr[4], arr[6])
→ [10, 30, 40, 50, 70, 90, 80]
         ← ≤70 →  ^  ← >70 →
```
Pivot 70 is now at index 4 — its final sorted position. ✅

---

## 🥈 Hoare Partition Scheme (More Efficient)

### Key Observation

> 💡 Use two pointers converging from both ends. Left pointer finds elements > pivot, right pointer finds elements ≤ pivot. Swap them. Repeat until pointers cross.

Hoare scheme does fewer swaps than Lomuto on average and handles equal elements better.

```
arr = [3, 6, 8, 10, 1, 2, 1], pivot = arr[0] = 3
l = 0, r = 6

Move l right while arr[l] < pivot:  l stops at 1 (arr[1]=6 ≥ 3)
Move r left while arr[r] > pivot:   r stops at 6 (arr[6]=1 ≤ 3)
l(1) < r(6): swap(arr[1], arr[6]) → [3,1,8,10,1,2,6]

Move l right: l=2 (arr[2]=8 ≥ 3)
Move r left: r=5 (arr[5]=2 ≤ 3)
l(2) < r(5): swap(arr[2], arr[5]) → [3,1,2,10,1,8,6]

Move l right: l=3 (arr[3]=10 ≥ 3)
Move r left: r=4 (arr[4]=1 ≤ 3)
l(3) < r(4): swap(arr[3], arr[4]) → [3,1,2,1,10,8,6]

Move l right: l=4
Move r left: r=3
l(4) > r(3): STOP. Partition index = r = 3
```

---

## 🥇 Optimal — Quick Sort with Lomuto Partition

### Algorithm

**`quickSort(arr, low, high)`:**
1. If `low >= high`: return (base case)
2. `pivotIdx = partition(arr, low, high)`
3. `quickSort(arr, low, pivotIdx - 1)`
4. `quickSort(arr, pivotIdx + 1, high)`

**`partition(arr, low, high)`:**
1. `pivot = arr[high]`, `i = low - 1`
2. For `j` from `low` to `high-1`:
   - If `arr[j] <= pivot`: `i++`, swap `arr[i]` and `arr[j]`
3. Swap `arr[i+1]` and `arr[high]` (place pivot)
4. Return `i+1`

### Dry Run

**Input:** `[5, 3, 8, 4, 2]`

**partition(0,4), pivot=arr[4]=2, i=-1:**

| j | arr[j] | ≤ pivot? | i | swap | Array |
|---|--------|----------|---|------|-------|
| 0 | 5 | ❌ | -1 | — | [5,3,8,4,2] |
| 1 | 3 | ❌ | -1 | — | [5,3,8,4,2] |
| 2 | 8 | ❌ | -1 | — | [5,3,8,4,2] |
| 3 | 4 | ❌ | -1 | — | [5,3,8,4,2] |

Place pivot: swap(arr[0], arr[4]) → **[2**, 3, 8, 4, **5]**, pivotIdx=0

**Recurse left:** quickSort([],0,-1) → base  
**Recurse right:** quickSort([3,8,4,5], 1, 4)

**partition(1,4), pivot=arr[4]=5, i=0:**

| j | arr[j] | ≤ pivot? | Action |
|---|--------|----------|--------|
| 1 | 3 | ✅ | i=1, swap(arr[1],arr[1]) |
| 2 | 8 | ❌ | — |
| 3 | 4 | ✅ | i=2, swap(arr[2],arr[3]) → [2,3,4,8,5] |

Place pivot: swap(arr[3],arr[4]) → [2,3,4,**5**,8], pivotIdx=3

Continue recursively... **Final: [2, 3, 4, 5, 8]** ✅

### Complexity

| Case | Time | When |
|------|------|------|
| Best | O(N log N) | Pivot always splits evenly |
| Average | O(N log N) | Random pivot |
| Worst | O(N²) | Already sorted, pivot = min/max |

- **Space:** O(log N) call stack (average), O(N) worst case

### Worst Case: Already Sorted Array
```
[1,2,3,4,5] with last element as pivot:
Partition produces: [] and [2,3,4,5] → N-1 elements on one side!
Recurrence: T(N) = T(N-1) + N → O(N²)
```

**Fix:** Random pivot or median-of-three pivot selection.

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * QUICK SORT (Lomuto Partition)
 *
 * IDEA: Place pivot in its correct sorted position.
 *       Recurse on left (< pivot) and right (> pivot) subarrays.
 *
 * PIVOT CHOICE: Last element (Lomuto) — simple but O(N²) on sorted arrays.
 *               Random pivot: add swap(arr[rand()%(high-low+1)+low], arr[high]) before partition.
 *               Median-of-three: better practical performance.
 *
 * COMPLEXITY: Time O(N log N) avg, O(N²) worst | Space O(log N) avg call stack
 * STABLE: NO | IN-PLACE: YES
 */

class Solution {
private:
    int partition(vector<int>& arr, int low, int high) {
        int pivot = arr[high];     // last element as pivot
        int i = low - 1;           // boundary of ≤ pivot region

        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                i++;
                swap(arr[i], arr[j]);   // expand ≤ pivot region
            }
        }

        swap(arr[i + 1], arr[high]);    // place pivot in correct position
        return i + 1;                   // pivot's final index
    }

    void quickSort(vector<int>& arr, int low, int high) {
        if (low >= high) return;         // base case: 0 or 1 element

        int pivotIdx = partition(arr, low, high);

        quickSort(arr, low, pivotIdx - 1);    // sort left of pivot
        quickSort(arr, pivotIdx + 1, high);   // sort right of pivot
    }

public:
    vector<int> sortArray(vector<int>& nums) {
        // randomize pivot to avoid O(N²) worst case
        srand(time(nullptr));
        quickSort(nums, 0, nums.size() - 1);
        return nums;
    }
};
```

---

## 🎤 Interview Explanation Script

> "Quick Sort picks a pivot element and partitions the array around it — everything smaller goes left, everything larger goes right. The pivot ends up in its exact final sorted position."

> "I use Lomuto's partition scheme: pick the last element as pivot, maintain a pointer `i` at the boundary of elements ≤ pivot, scan with `j`, and swap whenever `arr[j] ≤ pivot`."

> "After partition, I recursively sort the left and right subarrays. No merge step needed — the partition itself does the work."

> "Average time is O(N log N). The worst case is O(N²) when the pivot is always the smallest or largest — like on an already-sorted array. Randomizing the pivot prevents this."

> "It's not stable, but it's in-place with O(log N) average stack space, making it faster in practice than Merge Sort due to cache locality."

---

## 🧾 Recall Line *(10-Second Revision)*

> "Partition: pivot goes to final position, left ≤ pivot, right > pivot. Recurse both sides. Random pivot avoids O(N²)."

---

## 📝 Short Revision Notes

- Lomuto: `pivot=arr[high]`, `i=low-1`, swap when `arr[j]<=pivot`, place pivot at `i+1`
- Not stable — equal elements may be reordered
- In-place: O(1) extra space (only call stack)
- Worst case O(N²): sorted array + last-element pivot → use random pivot
- Average O(N log N): random pivot, expected O(log N) depth
- Used in: C++ `std::sort` (Introsort = QuickSort + HeapSort + InsertionSort)

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "sort in-place, space-efficient"
- "kth largest/smallest element" → QuickSelect (partition without full recursion)
- "Dutch National Flag" (3-way partition variant)

**I should think of:** Quick Sort / QuickSelect / 3-way partition

---

## ⚠️ Common Mistakes

❌ Pivot always = last element on sorted input → O(N²); always mention randomization  
❌ `low >= high` base case missing → stack overflow on empty subarrays  
❌ Forgetting to swap `arr[i+1]` with `arr[high]` at end of partition  
❌ Claiming Quick Sort is stable — it is **NOT**  
❌ `partition(arr, low, pivotIdx)` instead of `partition(arr, low, pivotIdx-1)` → infinite recursion  

---

## 🔥 What Interviewer Is Testing

- **Concept:** In-place partitioning and pivot placement
- **Reasoning:** Worst-case analysis and how to avoid it (random pivot)
- **Extension:** QuickSelect for Kth largest in O(N) average

---

## 🚀 Extension: QuickSelect (Kth Smallest/Largest)

**Problem:** Find Kth smallest element without fully sorting.

**Key insight:** After partition, pivot is at index `p`. 
- If `k == p`: we found it
- If `k < p`: recurse only left
- If `k > p`: recurse only right

```cpp
int quickSelect(vector<int>& arr, int low, int high, int k) {
    if (low == high) return arr[low];

    int p = partition(arr, low, high);

    if (k == p) return arr[p];
    else if (k < p) return quickSelect(arr, low, p - 1, k);
    else return quickSelect(arr, p + 1, high, k);
}
// Average O(N), Worst O(N²) — LeetCode #215
```

---

## 📚 Related Problems

- [ ] LeetCode #912 — Sort an Array
- [ ] LeetCode #215 — Kth Largest Element (QuickSelect)
- [ ] LeetCode #75 — Sort Colors (3-way partition / Dutch National Flag)
- [ ] LeetCode #347 — Top K Frequent Elements
- [ ] Striver Step 2 P04 — Merge Sort (stable, O(N log N) guaranteed)

---

## 🏆 Pattern Category

`Sorting` · `Divide and Conquer` · `In-Place` · `Partitioning`

---

## 🎯 Difficulty Analysis

**Rating:** Medium  
**Why:** The partition logic is subtle (off-by-one errors are common). Worst case analysis and pivot selection strategies are important interview discussion points.

---

## 📈 Progression Insight

**QuickSelect:** Find Kth smallest in O(N) average by only recursing on one side  
**3-way partition:** Handle duplicates efficiently — `arr[i] < pivot`, `arr[i] == pivot`, `arr[i] > pivot` (Dutch National Flag)  
**Introsort:** C++ std::sort — QuickSort with HeapSort fallback when depth > 2logN  
**Dual-pivot QuickSort:** Java's Arrays.sort for primitives — two pivots, three partitions

---

## ⏱️ 30-Second Last-Minute Revision

> **Idea:** Partition puts pivot in final position (left ≤ pivot, right > pivot). Recurse both sides.  
> **Lomuto:** `pivot=arr[high]`, `i=low-1`, scan j: if `arr[j]<=pivot` then `swap(arr[++i],arr[j])`. Place pivot at `i+1`.  
> **Time:** O(N log N) avg, O(N²) worst · **Space:** O(log N) · **Stable:** No  
> **Watch out for:** Use random pivot; base case `low >= high`
