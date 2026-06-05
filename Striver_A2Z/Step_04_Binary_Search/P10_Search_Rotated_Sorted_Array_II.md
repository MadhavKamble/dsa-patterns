# 🔥 Search in Rotated Sorted Array II (With Duplicates)

> **LeetCode #81** · **Difficulty:** Medium · **Step 4 — Binary Search · P10**

---

## 🧠 Problem Understanding

**What is it asking?**
Same as P09, but the array **may contain duplicates**. Return `true` if target exists, `false` otherwise.

**Input:** `nums = [2, 5, 6, 0, 0, 1, 2]`, `target = 0` → **Output:** `true`
**Input:** `nums = [2, 5, 6, 0, 0, 1, 2]`, `target = 3` → **Output:** `false`

**Key Observation:**
In P09, `arr[lo] <= arr[mid]` guaranteed the left half was sorted. But with duplicates, if `arr[lo] == arr[mid] == arr[hi]`, we **can't determine** which half is sorted.

**Example of ambiguity:**
```
[3, 1, 1] → arr[lo]=arr[mid]=arr[hi]=? Let's see:
arr[lo]=3, arr[mid]=1 → NOT equal, fine.

But: [1, 3, 1, 1, 1] → arr[lo]=1, arr[mid]=1
  Left half [1,3,1] is NOT sorted, but arr[lo]==arr[mid]
  We can't conclude left is sorted!
```

**Solution:** When `arr[lo] == arr[mid]` (or more precisely `arr[lo] == arr[mid] == arr[hi]`), simply shrink both ends: `lo++, hi--`. This sacrifices O(log N) guarantee but is still correct.

---

## 🥉 Brute Force Approach

Linear scan. **Time:** O(N) · **Space:** O(1)

---

## 🥇 Optimal Approach — Binary Search with Duplicate Handling

### Key Observation

> 💡 Add one extra case to P09's algorithm:
>
> **When `arr[lo] == arr[mid]`** (or `arr[lo] == arr[mid] == arr[hi]`):
> We can't determine which half is sorted. Safe action: `lo++, hi--` (shrink both ends by one). This skips the duplicate boundary elements.
>
> **Otherwise:** Same logic as P09 (check which half is sorted, check target range).

### Algorithm
1. `lo = 0`, `hi = N - 1`
2. While `lo <= hi`:
   - `mid = lo + (hi - lo) / 2`
   - If `arr[mid] == target`: return `true`
   - **New case:** If `arr[lo] == arr[mid] && arr[mid] == arr[hi]`: `lo++; hi--; continue`
   - If left half sorted (`arr[lo] <= arr[mid]`): standard left check
   - Else (right half sorted): standard right check
3. Return `false`

### Dry Run

**Input:** `arr = [2, 5, 6, 0, 0, 1, 2]`, `target = 0`

| lo | hi | mid | arr[mid] | arr[lo] | arr[hi] | Case | Action |
|----|-----|-----|----------|---------|---------|------|--------|
| 0 | 6 | 3 | 0 | 2 | 2 | arr[lo]=arr[hi]=2, arr[mid]=0 (not equal) | Left sorted: arr[0]=2≤arr[3]=0? ❌ → right sorted. 0 in (0,2]? ❌ → hi=2 |

Wait, `arr[lo]=2` and `arr[mid]=0`: `2 <= 0` is false → right half is sorted.
Right half: `arr[mid]=0 < target=0`? No. → `hi = mid - 1 = 2`

| lo | hi | mid | arr[mid] | Condition | Action |
|----|-----|-----|----------|-----------|--------|
| 0 | 2 | 1 | 5 | arr[0]=2≤arr[1]=5 → left sorted. 0 in [2,5)? ❌ | lo=2 |
| 2 | 2 | 2 | 6 | arr[2]=6≤arr[2]=6 → left sorted. 0 in [6,6)? ❌ | lo=3 |
| lo=3 > hi=2 → return `false`??? |

That's wrong — answer should be `true`. Let me retrace more carefully.

Actually the issue is my range check. Let me redo:

`arr = [2,5,6,0,0,1,2]`

| lo | hi | mid | arr[lo] | arr[mid] | arr[hi] | Action |
|----|-----|-----|---------|----------|---------|--------|
| 0 | 6 | 3 | 2 | 0 | 2 | arr[lo]==arr[hi]==2==arr[mid]? No. arr[lo]=2>arr[mid]=0 → right sorted. arr[mid]=0<target=0? No (0<0 false). → hi=2 |
| 0 | 2 | 1 | 2 | 5 | 6 | arr[lo]=2<=arr[mid]=5 → left sorted. target=0 in [2,5)? No. → lo=2 |
| 2 | 2 | 2 | 6 | 6 | 6 | arr[lo]==arr[mid]==arr[hi] → lo++,hi-- |
| lo=3>hi=1 → false? |

Still wrong! The issue is my implementation logic. Let me check LeetCode's accepted solution.

Actually the problem is that `0` appears at indices 3 and 4. Let me re-examine step 1:

lo=0, hi=6, mid=3. arr[mid]=0. 0 == target=0? **YES → return true immediately!**

Oh right, the first check! `arr[mid] == target` → return true right away. I forgot to check that first.

**Corrected dry run:**

| lo | hi | mid | arr[mid] | == target? | Action |
|----|-----|-----|----------|------------|--------|
| 0 | 6 | 3 | 0 | **0 == 0 ✅** | return `true` |

**Output:** `true` ✅

**Now for `target = 3` (not found):**

`arr = [2, 5, 6, 0, 0, 1, 2]`

| lo | hi | mid | arr[mid] | ==3? | arr[lo]=arr[mid]=arr[hi]? | Which half sorted? | Action |
|----|-----|-----|----------|------|--------------------------|-------------------|--------|
| 0 | 6 | 3 | 0 | ❌ | 2==0? No | right sorted (2>0): 3 in (0,2]? ❌ | hi=2 |
| 0 | 2 | 1 | 5 | ❌ | 2==5? No | left sorted (2≤5): 3 in [2,5)? ✅ | hi=0 |
| 0 | 0 | 0 | 2 | ❌ | — | left sorted (2≤2): 3 in [2,2)? ❌ | lo=1 |
| lo=1>hi=0 | | | | | | | return `false` ✅ |

### Complexity
- **Time:** O(log N) average, **O(N) worst case** (all duplicates like `[1,1,1,1,1]` finding non-existent element)
- **Space:** O(1)

---

## 🎤 Interview Explanation Script

> "P09 uses the fact that at least one half is always sorted. With duplicates, that guarantee breaks. When `arr[lo] == arr[mid]` (and equals `arr[hi]`), we can't tell which half is sorted."

> "The fix: in that ambiguous case, we just shrink both ends by one — `lo++, hi--`. This sacrifices our O(log N) guarantee in the worst case (e.g., all same elements, target absent → O(N)), but the algorithm remains correct."

> "All other cases from P09 remain the same. The worst case is O(N) when there are many duplicates, but the average case is still O(log N)."

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * SEARCH IN ROTATED SORTED ARRAY II (with duplicates)
 *
 * KEY DIFFERENCE FROM P09:
 *   When arr[lo] == arr[mid] (can't determine sorted half),
 *   shrink both ends: lo++, hi--.
 *
 * WORST CASE: O(N) for all-duplicate array with absent target.
 * AVERAGE: O(log N)
 *
 * COMPLEXITY: Time O(log N) avg, O(N) worst | Space O(1)
 */
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int lo = 0, hi = nums.size() - 1;

        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;

            if (nums[mid] == target) return true;

            // handle duplicates: can't determine sorted half
            if (nums[lo] == nums[mid] && nums[mid] == nums[hi]) {
                lo++; hi--;
                continue;
            }

            if (nums[lo] <= nums[mid]) {
                // left half is sorted
                if (nums[lo] <= target && target < nums[mid])
                    hi = mid - 1;
                else
                    lo = mid + 1;
            } else {
                // right half is sorted
                if (nums[mid] < target && target <= nums[hi])
                    lo = mid + 1;
                else
                    hi = mid - 1;
            }
        }

        return false;
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "Same as P09 + one extra case: `arr[lo]==arr[mid]==arr[hi]` → `lo++, hi--` (can't determine sorted half)."

---

## 📝 Short Revision Notes

- Only difference from P09: the `arr[lo]==arr[mid]==arr[hi]` duplicate case
- Duplicate case: can't tell which half is sorted → shrink both ends safely
- Worst case O(N): `[1,1,1,1,1]`, target=2 → every step shrinks by 1
- Returns `bool` (true/false) not index — can't guarantee unique index with duplicates
- P09 returns index, P10 returns bool — different return types

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "Rotated sorted array WITH duplicates"
- "Binary search, may have repeated elements"

**I should think of:** P09 + duplicate handling with `lo++, hi--`

---

## ⚠️ Common Mistakes

❌ Forgetting the duplicate case entirely → wrong answers for arrays like `[1,3,1,1,1]`  
❌ Only checking `arr[lo] == arr[mid]` without `arr[hi]` — may skip valid `lo++` cases  
❌ Claiming O(log N) worst case — it's O(N) with all duplicates  

---

## 🔥 What Interviewer Is Testing

- **Concept:** Why duplicates break the P09 guarantee
- **Reasoning:** What to do when can't determine sorted half
- **Trade-off:** O(log N) → O(N) worst case when handling duplicates

---

## 📚 Related Problems

- [ ] LeetCode #81 — Search in Rotated Sorted Array II
- [ ] LeetCode #33 — Search in Rotated Sorted Array (P09)
- [ ] LeetCode #153 — Find Minimum in Rotated Sorted Array (P11)

---

## 🏆 Pattern Category

`Binary Search` · `Rotated Array` · `Duplicates`

---

## ⏱️ 30-Second Last-Minute Revision

> **Extra case vs P09:** When `arr[lo]==arr[mid]==arr[hi]` → `lo++, hi--`.  
> All other logic identical to P09. Returns bool, not index.  
> **Worst case O(N)** with all duplicates. Average O(log N).
