# 🔥 Reverse Pairs

> **LeetCode #493** · **Difficulty:** Hard · **Step 3 — Arrays · P40**

---

## 🧠 Problem Understanding

**What is it asking?**
Count the number of **reverse pairs** in an array. A reverse pair is a pair `(i, j)` where `i < j` and `arr[i] > 2 * arr[j]`.

**Input:** `arr = [1, 3, 2, 3, 1]`
**Output:** `2`
Pairs: `(3,1)` at indices (1,4) → 3 > 2×1=2 ✅, and `(3,1)` at indices (3,4) → 3 > 2×1=2 ✅

**Input:** `arr = [2, 4, 3, 5, 1]`
**Output:** `3`
Pairs: (4,1), (2,1), (3,1) → all satisfy `arr[i] > 2 * arr[j]`

**Constraints:** 1 ≤ N ≤ 5×10⁴, values can be large → use `long long` for `2 * arr[j]`

**Key Observations:**
- Almost identical to Count Inversions (P39), but condition is `arr[i] > 2 * arr[j]` not `arr[i] > arr[j]`
- **CRITICAL DIFFERENCE:** Counting and merging must be **separated** here. In inversions, we counted during merge. For reverse pairs, the condition `arr[i] > 2*arr[j]` is NOT the same as the merge comparison `arr[i] > arr[j]`, so we must count BEFORE merging, then merge separately.

**Simple Example:**
```
arr = [2, 4, 3, 5, 1]
Reverse pairs where arr[i] > 2*arr[j]:
  (4,1): 4 > 2*1=2 ✅ (indices 1,4)
  (2,1): 2 > 2*1=2? NO, 2 is NOT > 2
  Wait, let me recheck...
  (2,1): 2 > 2×1=2 → 2 > 2 is FALSE
  (3,1): 3 > 2×1=2 ✅
  (5,1): 5 > 2×1=2 ✅
  (4,1): 4 > 2×1=2 ✅
  Count = 3 ✅
```

---

## 🥉 Brute Force Approach

### Idea
Check all pairs `(i, j)` with `i < j`. Count pairs where `arr[i] > 2 * arr[j]`.

### Algorithm
1. `count = 0`
2. For `i` from 0 to N-2:
3.   For `j` from i+1 to N-1:
4.     If `arr[i] > 2LL * arr[j]`: `count++`
5. Return `count`

### Complexity
- **Time:** O(N²)
- **Space:** O(1)

### C++ Code
```cpp
// BRUTE FORCE: O(N²) — check all pairs
long long reversePairs(vector<int>& nums) {
    long long count = 0;
    int n = nums.size();
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if ((long long)nums[i] > 2LL * nums[j]) count++;
    return count;
}
```

---

## 🥇 Optimal Approach — Modified Merge Sort (Count BEFORE Merge)

### Key Observation

> 💡 **The critical difference from Count Inversions:**
>
> In Count Inversions, the merge condition (`arr[i] > arr[j]`) and the inversion condition are the **same comparison**. So we can count during the merge.
>
> Here, the reverse pair condition is `arr[i] > 2 * arr[j]`, but the merge still uses `arr[i] <= arr[j]`. These are **different conditions** — an element might satisfy the reverse pair condition but not the sort order condition.
>
> **Solution:** Count reverse pairs first (using two pointers on sorted halves), THEN do the merge separately.

### Why Count First, Then Merge?

```
Left half (sorted):  [2, 4]
Right half (sorted): [1, 3]

Count step (two pointers, different condition arr[i] > 2*arr[j]):
  j=0 (right[j]=1): advance i while arr[i] > 2*1=2 → arr[0]=2 > 2? NO. i stays at 0.
  j=1 (right[j]=3): advance i while arr[i] > 2*3=6 → 2>6? NO, 4>6? NO. i stays at 0.
  Count = 0 pairs from this example

Merge step (separate, uses arr[i] <= arr[j] comparison):
  Normal merge of [2,4] and [1,3] → [1,2,3,4]
```

If we mixed counting and merging, the elements would be reordered before counting is complete, giving wrong results.

### Algorithm

**`countAndMerge(arr, left, mid, right)`:**
1. **Count phase:** Two pointers across sorted halves
   - For each `j` from `mid+1` to `right`:
     - Advance `i` while `arr[i] <= 2LL * arr[j]`
     - `count += (mid - i + 1)` elements in left half that form a pair with `arr[j]`
2. **Merge phase:** Standard merge into temp, copy back
3. Return `count`

**Why two pointers work for counting:**
Left and right halves are both sorted. As `arr[j]` increases, the threshold `2*arr[j]` increases, so the number of valid `arr[i]` values can only grow. The left pointer `i` only moves forward — O(N) total across all j.

### Dry Run

**Input:** `arr = [1, 3, 2, 3, 1]`

After recursive sorting of halves, consider merge of `[1, 3]` and `[1, 2, 3]`:

**Count phase:**
- `i` starts at 0 (points to left half start)
- j=2 (arr[j]=1): advance i while `arr[i] <= 2*1=2` → arr[0]=1 ≤ 2 → i=1; arr[1]=3 > 2 → stop. count += (mid-1+1) = (0-1+1) = 0
- Wait, let me be more careful with indices...

Let me trace the full recursion:

```
mergeSort([1,3,2,3,1], 0, 4)
  mergeSort([1,3,2], 0, 2)
    mergeSort([1,3], 0, 1) → count=0, sorted [1,3]
    mergeSort([2], 2, 2) → count=0
    countAndMerge([1,3], [2]):
      Count: j=2(val=2): i starts at 0. arr[0]=1 ≤ 2*2=4 → i=1. arr[1]=3 ≤ 4 → i=2. i>mid(1). count+=0.
      Merge: [1,2,3]
    Total so far: 0

  mergeSort([3,1], 3, 4)
    mergeSort([3], 3, 3) → count=0
    mergeSort([1], 4, 4) → count=0
    countAndMerge([3], [1]):
      Count: j=4(val=1): arr[3]=3 > 2*1=2 → count += (3-3+1) = 1
      Merge: [1,3]
    Total: 1

  countAndMerge([1,2,3], [1,3]):
    Count: 
      j=3(val=1): advance i while arr[i] ≤ 2*1=2: arr[0]=1≤2 i=1, arr[1]=2≤2 i=2, arr[2]=3>2 stop. count += (2-2+1)=1
      j=4(val=3): advance i while arr[i] ≤ 2*3=6: arr[2]=3≤6 i=3. i>mid(2). stop. count += 0
    Merge: [1,1,2,3,3]
    Count from this step: 1
  
Total = 0 + 1 + 1 = 2 ✅
```

### Complexity
- **Time:** O(N log N)
- **Space:** O(N)

---

## 🎤 Interview Explanation Script

> "The brute force checks all pairs in O(N²)."

> "I use modified Merge Sort, but there's a critical difference from Count Inversions. In inversions, the counting condition and the merge comparison are the same. Here they're different: we merge using `arr[i] <= arr[j]`, but we count using `arr[i] > 2*arr[j]`."

> "If I count during the merge, the elements get reordered while I'm still counting — wrong results. So I **count first, then merge separately**."

> "For counting: with both halves sorted, I use two pointers. For each `j` in the right half, I advance pointer `i` in the left half while `arr[i] <= 2*arr[j]`. When `i` stops, `mid - i + 1` left elements form reverse pairs with `arr[j]`. Since `arr[j]` increases as j grows, `i` only moves forward — O(N) across all j values."

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * REVERSE PAIRS — Modified Merge Sort
 *
 * PROBLEM UNDERSTANDING:
 *   Count pairs (i,j) where i<j and arr[i] > 2*arr[j]
 *
 * CRITICAL DIFFERENCE from Count Inversions:
 *   Reverse pair condition (arr[i] > 2*arr[j]) ≠ merge condition (arr[i] > arr[j])
 *   → Must COUNT FIRST, then MERGE SEPARATELY
 *
 * COUNTING: Two pointers on sorted halves. For each j, advance i while arr[i] <= 2*arr[j].
 *   count += (mid - i + 1) when arr[i] > 2*arr[j]
 *
 * EDGE CASES:
 *   - Overflow: 2*arr[j] → use 2LL*arr[j] or long long
 *
 * COMPLEXITY: Time O(N log N) | Space O(N)
 */
class Solution {
private:
    long long countAndMerge(vector<int>& arr, int left, int mid, int right) {
        long long count = 0;

        // COUNT PHASE: two pointers (separate from merge — different comparison)
        int j = mid + 1;
        for (int i = left; i <= mid; i++) {
            // advance j while arr[j] * 2 < arr[i]
            while (j <= right && (long long)arr[i] > 2LL * arr[j])
                j++;
            // all elements arr[mid+1..j-1] form reverse pairs with arr[i]
            count += (j - (mid + 1));
        }

        // MERGE PHASE: standard merge (separate from counting)
        vector<int> temp;
        int i = left, jj = mid + 1;
        while (i <= mid && jj <= right)
            temp.push_back(arr[i] <= arr[jj] ? arr[i++] : arr[jj++]);
        while (i <= mid)  temp.push_back(arr[i++]);
        while (jj <= right) temp.push_back(arr[jj++]);

        for (int k = 0; k < (int)temp.size(); k++)
            arr[left + k] = temp[k];

        return count;
    }

    long long mergeSort(vector<int>& arr, int left, int right) {
        if (left >= right) return 0;

        int mid = left + (right - left) / 2;
        long long count = 0;

        count += mergeSort(arr, left, mid);
        count += mergeSort(arr, mid + 1, right);
        count += countAndMerge(arr, left, mid, right);

        return count;
    }

public:
    int reversePairs(vector<int>& nums) {
        return (int)mergeSort(nums, 0, nums.size() - 1);
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "Count FIRST (two pointers: advance j while `arr[i] > 2*arr[j]`), THEN merge separately. Different conditions!"

---

## 📝 Short Revision Notes

- Key difference from P39 Count Inversions: **count before merge, not during**
- Count uses `arr[i] > 2*arr[j]`; merge uses `arr[i] <= arr[j]` — different!
- Two pointer count: for each `i`, advance `j` while condition holds; `count += j - (mid+1)`
- OR: for each `j`, advance `i` while `arr[i] > 2*arr[j]`; `count += (mid - i + 1)`
- Overflow: `2LL * arr[j]` — values can overflow `int` when doubled
- Both count and merge are O(N) per level → O(N log N) total

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "Count pairs with condition `arr[i] > k*arr[j]`"
- "Reverse pairs", "important reverse pairs"
- "Merge sort counting variant"

**I should think of:** Modified Merge Sort with **separate** count and merge phases

---

## ⚠️ Common Mistakes

❌ Counting during the merge (like in Count Inversions) → wrong answer — conditions differ  
❌ `2 * arr[j]` overflow for large values → use `2LL * arr[j]`  
❌ Confusing `count += (j - mid - 1)` vs `count += (j - (mid + 1))` — same thing, just be consistent  
❌ Not advancing `j` monotonically — `j` should never reset within the counting loop  

---

## 🔥 What Interviewer Is Testing

- **Concept:** Recognizing that counting and merging must be separated when conditions differ
- **Reasoning:** Why the same merge sort structure doesn't directly apply
- **Detail:** Two-pointer monotonicity proof for O(N) counting

---

## 🚀 Alternative Approaches

| Approach | Time | Space | Notes |
|----------|------|-------|-------|
| Modified Merge Sort | O(N log N) | O(N) | Optimal |
| BIT/Fenwick Tree | O(N log N) | O(N) | Process with coordinate compression |
| Brute force | O(N²) | O(1) | Too slow |

---

## 📚 Related Problems

- [ ] LeetCode #493 — Reverse Pairs
- [ ] GFG — Count Inversions (P39 — simpler version, count during merge)
- [ ] LeetCode #315 — Count of Smaller Numbers After Self
- [ ] LeetCode #327 — Count of Range Sum (harder variant)

---

## 🏆 Pattern Category

`Arrays` · `Divide and Conquer` · `Merge Sort` · `Two Pointers`

---

## 🎯 Difficulty Analysis

**Rating:** Hard

**Why challenging:** The distinction between this and Count Inversions is subtle but critical. Mixing count-during-merge gives wrong results. Recognizing when to separate the two operations is the core insight.

---

## 📈 Progression Insight

**Easier version:** Count Inversions (P39) — same pattern, but count during merge is valid

**Harder:** LeetCode #327 Count of Range Sum — apply same ideas to prefix sums with a range condition

---

## ⏱️ 30-Second Last-Minute Revision

> **Problem:** Count pairs (i,j) with i<j and arr[i] > 2*arr[j]  
> **Key insight:** Count BEFORE merge (conditions are different from merge comparison)  
> **Count:** For each i in left, advance j while `arr[i] > 2LL*arr[j]`. `count += j-(mid+1)`.  
> **Time:** O(N log N) | **Space:** O(N)  
> **Watch out for:** 2LL overflow; do NOT count during merge like in inversions
