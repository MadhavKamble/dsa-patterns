# 🔥 Count Inversions

> **GFG Classic / LeetCode #315** (variant) · **Difficulty:** Hard · **Step 3 — Arrays · P39**

---

## 🧠 Problem Understanding

**What is it asking?**
Count the number of **inversions** in an array. A pair `(i, j)` is an inversion if `i < j` but `arr[i] > arr[j]`.

**Input:** `arr = [2, 4, 1, 3, 5]`
**Output:** `3`
Pairs: `(2,1)`, `(4,1)`, `(4,3)` → 3 inversions

**Input:** `arr = [5, 4, 3, 2, 1]` (fully reversed)
**Output:** `10` = N*(N-1)/2 (all pairs are inversions)

**Constraints:** 1 ≤ N ≤ 10⁵, values can be large → answer can be up to N*(N-1)/2 ≈ 5×10⁹ → use `long long`

**Key Observations:**
- Brute force: O(N²) — check all pairs
- Optimal: Modified Merge Sort — count inversions **while merging** sorted halves
- During merge: when we pick from right half (arr[j] < arr[i]), all remaining left half elements form inversions with arr[j]

**Simple Example:**
```
[2, 4, 1, 3, 5]
Inversions:
  (2,1): index 0,2 → 2>1 ✅
  (4,1): index 1,2 → 4>1 ✅
  (4,3): index 1,3 → 4>3 ✅
Count = 3
```

---

## 🥉 Brute Force Approach

### Idea
Check every pair `(i, j)` with `i < j`. Count pairs where `arr[i] > arr[j]`.

### Algorithm
1. `count = 0`
2. For `i` from 0 to N-2:
3.   For `j` from i+1 to N-1:
4.     If `arr[i] > arr[j]`: `count++`
5. Return `count`

### Complexity
- **Time:** O(N²)
- **Space:** O(1)

### C++ Code
```cpp
// BRUTE FORCE: check all pairs O(N²)
long long countInversions(vector<int>& arr) {
    long long count = 0;
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (arr[i] > arr[j]) count++;
    return count;
}
```

---

## 🥇 Optimal Approach — Modified Merge Sort

### Key Observation

> 💡 During the **merge step** of Merge Sort, when we pick an element from the **right half** at index `j` (because `arr[j] < arr[i]`), **all remaining elements in the left half** (from index `i` to `mid`) are greater than `arr[j]` (since the left half is sorted). Each of those forms an inversion with `arr[j]`.
>
> So instead of counting inversions from scratch, we count them **for free** during the merge.
>
> Number of inversions at this step = `(mid - i + 1)` where `i` is the current left pointer.

```
Left half (sorted): [1, 3, 5]    i=0
Right half (sorted): [2, 4]       j=0

Pick right[0]=2 < left[0]=1? No, 2 > 1, pick left[0]=1 first.
  ...
Pick left[1]=3 vs right[0]=2 → 2 < 3, pick right. 
  Inversions += (mid - i + 1) = (mid - 1 + 1) = 2  [3,5 > 2]
Pick left[1]=3 vs right[1]=4 → 3 < 4, pick left.
Pick left[2]=5 vs right[1]=4 → 4 < 5, pick right.
  Inversions += 1  [5 > 4]
```

### Algorithm

**`mergeCount(arr, left, mid, right)`:**
1. Merge left and right halves into temp
2. When `arr[j] < arr[i]` (taking from right):
   - `count += (mid - i + 1)` — all remaining left elements are greater
3. Return `count`

**`mergeSort(arr, left, right)`:**
1. If `left >= right`: return 0
2. `mid = (left + right) / 2`
3. `count = mergeSort(arr, left, mid) + mergeSort(arr, mid+1, right)`
4. `count += mergeCount(arr, left, mid, right)`
5. Return `count`

### Dry Run

**Input:** `arr = [2, 4, 1, 3, 5]`

```
mergeSort([2,4,1,3,5], 0, 4)
  mergeSort([2,4,1], 0, 2)
    mergeSort([2,4], 0, 1) → count=0 after merge → [2,4]
    mergeSort([1], 2, 2) → count=0
    mergeCount([2,4],[1]):
      i=0,j=2: arr[i]=2 > arr[j]=1 → count += (1-0+1) = 2, take 1
      i=0: take 2, then 4
    After merge: [1,2,4], count=2

  mergeSort([3,5], 3, 4) → count=0, sorted [3,5]

  mergeCount([1,2,4],[3,5]):
    i=0,j=3: 1 < 3, take 1
    i=1,j=3: 2 < 3, take 2
    i=2,j=3: 4 > 3 → count += (2-2+1) = 1, take 3
    i=2,j=4: 4 < 5, take 4, then 5
    count = 1

Total = 2 + 0 + 1 = 3 ✅
```

### Complexity
- **Time:** O(N log N) — Merge Sort with O(1) extra work per comparison
- **Space:** O(N) — temp array for merging

### Why is this optimal?
Any comparison-based inversion counting needs Ω(N log N) — same lower bound as sorting (sorting rearranges all inversions to 0). Merge Sort achieves this tightly.

---

## 🎤 Interview Explanation Script

> "The brute force checks all N(N-1)/2 pairs — O(N²). For N=10⁵, that's 5 billion operations — too slow."

> "The insight: during Merge Sort's merge step, when we pick an element from the right half because it's smaller than the current left element, we know that ALL remaining elements in the left half are also greater than it — because the left half is sorted. So instead of counting individual pairs, we add `mid - i + 1` to our inversion count in O(1) at that step."

> "This piggybacks inversion counting onto Merge Sort, giving O(N log N) with no additional asymptotic cost. The answer can be up to N(N-1)/2 ≈ 5×10⁹ for N=10⁵, so we use `long long`."

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * COUNT INVERSIONS — Modified Merge Sort
 *
 * PROBLEM UNDERSTANDING:
 *   Count pairs (i,j) where i < j but arr[i] > arr[j].
 *
 * KEY OBSERVATION:
 *   During merge: when right[j] < left[i], ALL of left[i..mid] > right[j].
 *   Count += (mid - i + 1) at that moment.
 *
 * CRITICAL: Use long long — answer can be ~N²/2 ≈ 5×10⁹ for N=10⁵.
 *
 * COMPLEXITY: Time O(N log N) | Space O(N)
 */
class Solution {
private:
    long long merge(vector<int>& arr, int left, int mid, int right) {
        vector<int> temp;
        long long count = 0;
        int i = left, j = mid + 1;

        while (i <= mid && j <= right) {
            if (arr[i] <= arr[j]) {
                temp.push_back(arr[i++]);
            } else {
                // arr[j] < arr[i]: all of arr[i..mid] form inversions with arr[j]
                count += (mid - i + 1);
                temp.push_back(arr[j++]);
            }
        }

        while (i <= mid)  temp.push_back(arr[i++]);
        while (j <= right) temp.push_back(arr[j++]);

        // copy sorted elements back
        for (int k = 0; k < (int)temp.size(); k++)
            arr[left + k] = temp[k];

        return count;
    }

    long long mergeSort(vector<int>& arr, int left, int right) {
        if (left >= right) return 0;   // base case

        int mid = left + (right - left) / 2;
        long long count = 0;

        count += mergeSort(arr, left, mid);           // count in left half
        count += mergeSort(arr, mid + 1, right);      // count in right half
        count += merge(arr, left, mid, right);        // count across halves

        return count;
    }

public:
    long long inversionCount(vector<int>& arr) {
        return mergeSort(arr, 0, arr.size() - 1);
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "Merge sort: when right[j] < left[i], `count += (mid - i + 1)`. All remaining left elements are inversions with right[j]."

---

## 📝 Short Revision Notes

- Inversions = pairs `(i,j)` where `i < j` and `arr[i] > arr[j]`
- Modified merge sort: count when taking from right half
- `count += (mid - i + 1)` — key line
- Use `long long` — max inversions = N(N-1)/2 ≈ 5×10⁹ for N=10⁵
- **IMPORTANT:** Count before sorting (the merge step sorts AND counts simultaneously)
- Fully sorted: 0 inversions. Reverse sorted: N(N-1)/2 inversions.

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "Count inversions", "how many swaps to sort"
- "number of (i,j) pairs with i<j but arr[i]>arr[j]"
- "merge sort variant"

**I should think of:** Modified Merge Sort — count during merge step

---

## ⚠️ Common Mistakes

❌ Using `int` for count → overflow for N ≥ ~65,000  
❌ Counting after sorting (array is already sorted — no inversions visible)  
❌ `count += (mid - i)` instead of `(mid - i + 1)` — off-by-one  
❌ Not copying temp back to arr — next merge step sees unsorted data  

---

## 🔥 What Interviewer Is Testing

- **Concept:** Piggybacking counting onto an existing algorithm (Merge Sort)
- **Reasoning:** Why `mid - i + 1` is the correct count at each step
- **Details:** Long long overflow, base case, temp array copy-back

---

## 🚀 Alternative Approaches

| Approach | Time | Space | Notes |
|----------|------|-------|-------|
| Modified Merge Sort | O(N log N) | O(N) | Optimal |
| BIT/Fenwick Tree | O(N log N) | O(N) | Alternative O(N log N), processes left-to-right |
| Brute force | O(N²) | O(1) | Too slow for N > 10⁴ |

---

## 📚 Related Problems

- [ ] LeetCode #315 — Count of Smaller Numbers After Self
- [ ] LeetCode #493 — Reverse Pairs (P40 — similar merge sort approach)
- [ ] GFG — Count Inversions
- [ ] Striver Step 2 P04 — Merge Sort (prerequisite)

---

## 🏆 Pattern Category

`Arrays` · `Divide and Conquer` · `Merge Sort` · `Counting`

---

## 🎯 Difficulty Analysis

**Rating:** Hard

**Why challenging:** The insight — piggyback counting onto merge sort — requires understanding merge sort's invariants deeply. The `mid - i + 1` formula and the long long requirement are subtle. Common misconception: "count after sorting" doesn't work.

---

## 📈 Progression Insight

**Harder variant:** LeetCode #493 Reverse Pairs — condition is `arr[i] > 2 * arr[j]`. The counting MUST happen before the merge (sorted order required for counting, then merge separately).

**Even harder:** LeetCode #315 — Count of Smaller Numbers After Self → same idea, but return an array of counts.

**Advanced:** BIT/Fenwick Tree approach — process elements left-to-right, for each element query how many previous elements were larger. O(N log N), O(N) space.

---

## ⏱️ 30-Second Last-Minute Revision

> **Problem:** Count pairs (i,j) with i<j and arr[i]>arr[j]  
> **Approach:** Merge sort. During merge: when right[j] < left[i], `count += (mid - i + 1)`.  
> **Key trick:** All left[i..mid] are greater than right[j] because left is sorted  
> **Time:** O(N log N) | **Space:** O(N)  
> **Watch out for:** Long long for count; `mid - i + 1` not `mid - i`
