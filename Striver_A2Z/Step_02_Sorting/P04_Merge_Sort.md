# 🔥 Merge Sort

> **Step 2 — Sorting Techniques · P04**  
> **Difficulty:** Medium · **LeetCode #912** (Sort an Array)

---

## 🧠 Problem Understanding

**What is it asking?**  
Sort an array using Merge Sort — a divide-and-conquer algorithm that splits, sorts recursively, and merges.

**Core Idea:** Split array in half, recursively sort both halves, then merge the two sorted halves into one sorted array.

**Key Observations:**
- Always O(N log N) — no worst-case degradation
- Stable sort — equal elements maintain relative order
- Requires O(N) extra space for the merge step
- The foundation of external sorting (sorting data larger than RAM)

**Simple Example:**
```
[38, 27, 43, 3, 9, 82, 10]
         ↓ split
[38,27,43,3]   [9,82,10]
      ↓               ↓
[38,27] [43,3]   [9,82] [10]
   ↓       ↓       ↓
[27,38] [3,43]  [9,82]  [10]
         ↓ merge
    [3,27,38,43]   [9,10,82]
              ↓ merge
       [3,9,10,27,38,43,82]
```

---

## 🥇 The Algorithm

### Key Observation

> 💡 **Divide:** Split at midpoint. **Conquer:** Recursively sort left and right halves. **Combine:** Merge two sorted halves using two pointers.

**The Merge step is the heart:** Two sorted arrays can be merged in O(N) using two pointers — compare heads, take the smaller one.

### Algorithm

**`mergeSort(arr, l, r)`:**
1. If `l >= r`: return (base case — single element)
2. `mid = (l + r) / 2`
3. `mergeSort(arr, l, mid)`
4. `mergeSort(arr, mid+1, r)`
5. `merge(arr, l, mid, r)`

**`merge(arr, l, mid, r)`:**
1. Create temp array
2. Two pointers `i=l, j=mid+1`
3. While both pointers valid: copy smaller element to temp
4. Copy remaining elements from either half
5. Copy temp back to arr[l..r]

### Dry Run — Merge Step

**Merging:** `[3, 27, 38, 43]` and `[9, 10, 82]`

| i (left) | j (right) | Comparison | temp |
|----------|-----------|------------|------|
| 3 | 9 | 3 < 9, take left | [3] |
| 27 | 9 | 9 < 27, take right | [3,9] |
| 27 | 10 | 10 < 27, take right | [3,9,10] |
| 27 | 82 | 27 < 82, take left | [3,9,10,27] |
| 38 | 82 | 38 < 82, take left | [3,9,10,27,38] |
| 43 | 82 | 43 < 82, take left | [3,9,10,27,38,43] |
| done | 82 | right remaining | [3,9,10,27,38,43,82] |

**Result:** `[3, 9, 10, 27, 38, 43, 82]` ✅

### Complexity
- **Time:** O(N log N) always — log N levels of recursion, O(N) merge at each level
- **Space:** O(N) auxiliary array + O(log N) call stack

### Recurrence
```
T(N) = 2T(N/2) + O(N)
By Master Theorem (Case 2): T(N) = O(N log N)
```

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * MERGE SORT
 *
 * PARADIGM: Divide and Conquer
 * IDEA: Split → sort halves recursively → merge sorted halves
 *
 * COMPLEXITY: Time O(N log N) always | Space O(N) for temp array
 * STABLE: YES | NOT in-place (requires O(N) extra space)
 *
 * USE WHEN: need guaranteed O(N log N), stable sort, or external sorting
 */

class Solution {
private:
    void merge(vector<int>& arr, int l, int mid, int r) {
        vector<int> temp;
        int i = l, j = mid + 1;

        // merge two sorted halves into temp
        while (i <= mid && j <= r) {
            if (arr[i] <= arr[j])     // <= preserves stability
                temp.push_back(arr[i++]);
            else
                temp.push_back(arr[j++]);
        }

        // copy remaining left elements
        while (i <= mid) temp.push_back(arr[i++]);

        // copy remaining right elements
        while (j <= r)   temp.push_back(arr[j++]);

        // write merged result back to original array
        for (int k = 0; k < (int)temp.size(); k++)
            arr[l + k] = temp[k];
    }

    void mergeSort(vector<int>& arr, int l, int r) {
        if (l >= r) return;                    // base case: 0 or 1 element

        int mid = l + (r - l) / 2;            // avoid overflow: not (l+r)/2

        mergeSort(arr, l, mid);                // sort left half
        mergeSort(arr, mid + 1, r);            // sort right half
        merge(arr, l, mid, r);                 // merge sorted halves
    }

public:
    vector<int> sortArray(vector<int>& nums) {
        mergeSort(nums, 0, nums.size() - 1);
        return nums;
    }
};
```

---

## 🎤 Interview Explanation Script

> "Merge Sort is a divide-and-conquer algorithm. I split the array at the midpoint, recursively sort both halves, then merge the two sorted halves."

> "The key insight is that merging two sorted arrays is O(N) using two pointers — compare the front elements, take the smaller one."

> "The recursion has log N levels (we halve each time), and each level does O(N) work in total. So time is O(N log N) always — no worst case degradation."

> "It's stable because in the merge step, when elements are equal I always take from the left half first (`<=` comparison)."

> "The tradeoff: it requires O(N) extra space for the temp array. If space is critical, Quick Sort is preferred."

> "Mid calculation: `l + (r-l)/2` instead of `(l+r)/2` to avoid integer overflow when l+r > INT_MAX."

---

## 🧾 Recall Line *(10-Second Revision)*

> "Split at mid, recurse both halves, merge with two pointers. O(N log N) always. O(N) space."

---

## 📝 Short Revision Notes

- Recurrence: T(N) = 2T(N/2) + N → O(N log N) by Master Theorem
- Stable ✅ (use `<=` in merge, not `<`)
- Space: O(N) for merge temp array + O(log N) call stack
- Base case: `l >= r` (single element or empty)
- `mid = l + (r-l)/2` prevents overflow
- Used in: Python's Timsort (hybrid with Insertion), Java's Arrays.sort for objects
- Preferred over Quick Sort when: stable sort required, or worst-case O(N log N) needed

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "count inversions in array" → modified Merge Sort (count during merge)
- "sort linked list" → Merge Sort (no random access needed)
- "stable sort required"
- "external sort" (data too large for RAM)

**I should think of:** Merge Sort

---

## ⚠️ Common Mistakes

❌ `mid = (l + r) / 2` → overflow for large indices; use `l + (r-l)/2`  
❌ Using `<` instead of `<=` in merge → unstable sort  
❌ Base case `l == r` instead of `l >= r` → misses empty subarrays  
❌ Forgetting to copy temp back to original array  
❌ Creating temp array globally instead of inside merge — causes issues with recursive calls  

---

## 🔥 What Interviewer Is Testing

- **Concept:** Divide and conquer paradigm
- **Reasoning:** Why O(N log N) via recurrence / Master Theorem
- **Details:** Stability, overflow-safe mid, space complexity
- **Extensions:** Count inversions (crucial follow-up)

---

## 🚀 Important Extension: Count Inversions

**Problem:** Count pairs `(i,j)` where `i < j` but `arr[i] > arr[j]`.

**Key insight:** During the merge step, when we take from the right half (arr[j] < arr[i]), all remaining left half elements (arr[i..mid]) form inversions with arr[j].

```cpp
// Inside merge, count inversions:
if (arr[i] <= arr[j]) {
    temp.push_back(arr[i++]);
} else {
    inversions += (mid - i + 1);   // all remaining left elements are inversions
    temp.push_back(arr[j++]);
}
```

This gives count inversions in O(N log N) — a very common interview follow-up!

---

## 📚 Related Problems

- [ ] LeetCode #912 — Sort an Array
- [ ] LeetCode #148 — Sort List (Merge Sort on linked list)
- [ ] LeetCode #315 — Count of Smaller Numbers After Self (merge sort variant)
- [ ] LeetCode #493 — Reverse Pairs (merge sort counting)
- [ ] Striver Step 2 P07 — Quick Sort

---

## 🏆 Pattern Category

`Sorting` · `Divide and Conquer` · `Stable` · `Recursion`

---

## 🎯 Difficulty Analysis

**Rating:** Medium  
**Why:** The split is trivial; the merge step requires careful index management. The overflow-safe mid, stability, and inversion-count extension make it a rich interview topic.

---

## 📈 Progression Insight

**Count inversions:** Modify merge to count right-takes → O(N log N)  
**Sort linked list (LC 148):** Find middle with slow/fast pointers, then merge sort  
**External sort:** Use K-way merge for files larger than RAM  
**Bottom-up merge sort:** Avoid recursion — iterate with increasing merge sizes (2, 4, 8, ...)

---

## ⏱️ 30-Second Last-Minute Revision

> **Idea:** Split at `mid = l+(r-l)/2`. Recurse left and right. Merge with two pointers (take smaller).  
> **Time:** O(N log N) always · **Space:** O(N) · **Stable:** Yes  
> **Key trick:** `<=` in merge for stability; copy temp back after merge  
> **Watch out for:** Overflow-safe mid; base case `l >= r`
