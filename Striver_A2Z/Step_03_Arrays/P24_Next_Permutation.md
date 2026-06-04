# 🔥 Next Permutation

> **LeetCode #31** · **Difficulty:** Medium · **Step 3 — Arrays · P24**

---

## 🧠 Problem Understanding

Given a permutation, rearrange it into the **lexicographically next** greater permutation. If none exists (descending order), wrap to smallest (ascending order). Do it **in-place**.

**Input:** `[1,2,3]` → `[1,3,2]`  
**Input:** `[3,2,1]` → `[1,2,3]` (wraps)  
**Input:** `[1,1,5]` → `[1,5,1]`

---

## 🥉 Brute Force
Generate all permutations, find current, return next. **Time:** O(N! × N)

---

## 🥇 Optimal — 3-Step Algorithm

### Key Observation
> 💡 To find the next permutation:
> 1. Find the rightmost **dip**: index `i` where `arr[i] < arr[i+1]` (scanning right to left)
> 2. Find the smallest element to the right of `i` that is **greater** than `arr[i]` → index `j`
> 3. Swap `arr[i]` and `arr[j]`, then **reverse** the suffix `arr[i+1..N-1]`

**Why reverse suffix?** The suffix after position `i` was in descending order (why we stopped at `i`). After swap, it's still "mostly" descending. Reversing it gives the smallest possible arrangement for that suffix.

### Algorithm
1. Find largest index `i` such that `arr[i] < arr[i+1]` (from right to left)
2. If no such `i` → entire array is descending → reverse all, return
3. Find largest index `j > i` such that `arr[i] < arr[j]`
4. Swap `arr[i]` and `arr[j]`
5. Reverse `arr[i+1..N-1]`

### Dry Run
`arr = [2, 1, 5, 4, 3, 0, 0]`

**Step 1:** Find dip from right: `arr[1]=1 < arr[2]=5` → `i=1`

**Step 2:** Find smallest > arr[1]=1 in `arr[2..6]=[5,4,3,0,0]`:  
Scan right to left for first element > 1: `arr[5]=0` no, `arr[6]=0` no, `arr[4]=3` yes, `arr[3]=4` yes, `arr[2]=5` yes... take the rightmost (smallest greater) = index `j=4` (value 3)

Actually: largest `j > i` such that `arr[j] > arr[i]` → rightmost element > 1 = index 4 (val=3)

**Step 3:** Swap `arr[1]` and `arr[4]`: `[2, 3, 5, 4, 1, 0, 0]`

**Step 4:** Reverse `arr[2..6]`: `[5,4,1,0,0]` → `[0,0,1,4,5]`

**Result:** `[2, 3, 0, 0, 1, 4, 5]` ✅

### Complexity
- **Time:** O(N) · **Space:** O(1)

---

## 💻 Clean C++ Code

```cpp
/*
 * NEXT PERMUTATION — 3-step algorithm
 *
 * STEP 1: Find rightmost dip (arr[i] < arr[i+1], scanning right to left)
 * STEP 2: Find rightmost element > arr[i] to its right
 * STEP 3: Swap them, then reverse the suffix after i
 *
 * EDGE CASE: Entire array descending → just reverse all (wraps to smallest)
 *
 * Time O(N) | Space O(1)
 */
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();

        // step 1: find rightmost dip
        int i = n - 2;
        while (i >= 0 && nums[i] >= nums[i + 1]) i--;

        if (i >= 0) {
            // step 2: find rightmost element just greater than nums[i]
            int j = n - 1;
            while (nums[j] <= nums[i]) j--;

            // step 3a: swap
            swap(nums[i], nums[j]);
        }

        // step 3b: reverse suffix (descending → ascending = smallest arrangement)
        reverse(nums.begin() + i + 1, nums.end());
    }
};
```

---

## 🎤 Interview Explanation Script
> "To find the next permutation, I need to make the smallest possible increase."

> "Step 1: Find the rightmost index `i` where `arr[i] < arr[i+1]` — this is the pivot, the rightmost position where we can increase."

> "Step 2: Find the smallest element to the right of `i` that's greater than `arr[i]` — that's the rightmost such element (the suffix was descending)."

> "Step 3: Swap them, then reverse the suffix. The suffix was descending before the swap; reversing it gives the smallest possible arrangement for that part."

> "If no pivot exists, the whole array is descending — we just reverse it to get the smallest permutation."

---

## 🧾 Recall Line
> "Find rightmost dip `i`. Find rightmost element > arr[i] at `j`. Swap(i,j). Reverse suffix after i."

## 📝 Short Revision Notes
- 3 steps: find dip, find swap target, swap + reverse suffix
- Dip scan: `while i>=0 && arr[i] >= arr[i+1]: i--`
- Swap target: rightmost element > arr[i] (not just any)
- No dip → descending → just reverse all
- Why rightmost swap target? Gives smallest increment

## ⚠️ Common Mistakes
❌ Forgetting to handle "no dip" case (descending array)  
❌ Finding first element > arr[i] instead of rightmost → not the smallest increment  
❌ Reversing from `i` instead of `i+1`

## 🔥 What Interviewer Is Testing
- Lexicographic ordering intuition
- Why the 3-step process gives the correct next permutation

## 📚 Related Problems
- [ ] LeetCode #31 — Next Permutation
- [ ] LeetCode #46 — Permutations
- [ ] LeetCode #60 — Permutation Sequence (Kth permutation)

## 🏆 Pattern Category
`Arrays` · `Two Pointers` · `Greedy`

## ⏱️ 30-Second Revision
> Find rightmost `arr[i] < arr[i+1]`. Find rightmost `arr[j] > arr[i]`. Swap. Reverse from i+1. If no i, reverse all. O(N)/O(1).
