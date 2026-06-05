# 🔥 Find the Smallest Divisor Given a Threshold

> **LeetCode #1283** · **Difficulty:** Medium · **Step 4 — Binary Search · P22**

---

## 🧠 Problem Understanding

**What is it asking?**
Given an integer array `nums` and a threshold, find the **smallest positive divisor** `d` such that the sum of `ceil(nums[i] / d)` for all i is ≤ threshold.

**Input:** `nums = [1, 2, 5, 9]`, `threshold = 6` → **Output:** `5`
**Input:** `nums = [44, 22, 33, 11, 1]`, `threshold = 5` → **Output:** `44`

**Constraints:** `1 ≤ nums.length ≤ 5×10⁴`, `1 ≤ threshold ≤ 10⁶`, `1 ≤ nums[i] ≤ 10⁶`

**Key Observations:**
- Larger divisor → smaller ceil values → smaller sum (monotone ↓ as divisor ↑)
- Search space: divisor ∈ [1, max(nums)]
- `d=1`: sum = Σnums[i] (could exceed threshold). `d=max(nums)`: every term is ≤ 2, so sum ≤ 2N ≤ threshold is likely

**Simple Example:**
```
nums=[1,2,5,9], threshold=6
d=1: ⌈1/1⌉+⌈2/1⌉+⌈5/1⌉+⌈9/1⌉ = 1+2+5+9=17 > 6 ✗
d=5: ⌈1/5⌉+⌈2/5⌉+⌈5/5⌉+⌈9/5⌉ = 1+1+1+2=5 ≤ 6 ✓
d=4: ⌈1/4⌉+⌈2/4⌉+⌈5/4⌉+⌈9/4⌉ = 1+1+2+3=7 > 6 ✗
Min valid d = 5
```

---

## 🥉 Brute Force Approach

### Idea
Try every divisor from 1 to max(nums). Return the first one where sum ≤ threshold.

### Complexity
- **Time:** O(N × max(nums)) — too slow
- **Space:** O(1)

---

## 🥇 Optimal Approach — Binary Search on Divisor

### Key Observation

> 💡 As divisor increases, the sum decreases (monotone). Binary search for the **minimum divisor** that makes the sum ≤ threshold.
>
> **Search space:** [1, max(nums)]

### Algorithm
1. `lo = 1`, `hi = max(nums)`
2. While `lo < hi`:
   - `mid = lo + (hi - lo) / 2`
   - `sum = Σ ceil(nums[i] / mid)` for all i
   - If `sum <= threshold`: `hi = mid` (valid, try smaller)
   - Else: `lo = mid + 1` (too large, need bigger divisor)
3. Return `lo`

### Dry Run

**Input:** `nums = [1, 2, 5, 9]`, `threshold = 6`
`lo = 1`, `hi = 9`

| lo | hi | mid | Sum = Σceil(x/mid) | ≤6? | Action |
|----|-----|-----|--------------------|-----|--------|
| 1 | 9 | 5 | 1+1+1+2=5 | ✅ | hi=5 |
| 1 | 5 | 3 | 1+1+2+3=7 | ❌ | lo=4 |
| 4 | 5 | 4 | 1+1+2+3=7 | ❌ | lo=5 |
| lo=5==hi=5 → **return 5** ✅ |

### Complexity
- **Time:** O(N × log(max(nums)))
- **Space:** O(1)

---

## 🎤 Interview Explanation Script

> "A larger divisor produces smaller ceil values, so the sum decreases as the divisor grows — monotone property."

> "I binary search for the minimum divisor in [1, max(nums)]. For each candidate divisor, I compute `Σceil(x/d)` in O(N). If the sum is ≤ threshold, I try smaller; otherwise I need a bigger divisor."

> "The ceil formula in integers: `ceil(a/b) = (a + b - 1) / b`."

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * FIND SMALLEST DIVISOR — binary search on divisor value
 *
 * KEY OBSERVATION:
 *   Larger divisor → smaller sum (monotone decreasing).
 *   Binary search in [1, max(nums)] for minimum valid divisor.
 *
 * FEASIBILITY: sum of ceil(nums[i]/d) <= threshold
 *   ceil(a/b) = (a + b - 1) / b
 *
 * COMPLEXITY: Time O(N log max_val) | Space O(1)
 */
class Solution {
private:
    long long computeSum(vector<int>& nums, int divisor) {
        long long sum = 0;
        for (int x : nums)
            sum += (x + divisor - 1) / divisor;   // ceil(x/divisor)
        return sum;
    }

public:
    int smallestDivisor(vector<int>& nums, int threshold) {
        int lo = 1;
        int hi = *max_element(nums.begin(), nums.end());

        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (computeSum(nums, mid) <= threshold)
                hi = mid;        // valid divisor, try smaller
            else
                lo = mid + 1;    // sum too large, need bigger divisor
        }

        return lo;
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "BS [1, max(nums)]. Sum = Σceil(x/d). Sum≤threshold → `hi=mid`. Else `lo=mid+1`. Return lo."

---

## 📝 Short Revision Notes

- `ceil(a/b) = (a+b-1)/b` in integer arithmetic
- Larger divisor → smaller sum → monotone property
- Search space: [1, max(nums)]
- Always valid at `d = max(nums)`: every ceil ≤ 2, so sum ≤ 2N ≤ threshold (threshold ≥ N guaranteed)

---

## ⚠️ Common Mistakes

❌ `hi = sum(nums)` instead of `max(nums)` — valid but unnecessarily large search space  
❌ `sum = Σfloor(x/d)` — should be ceil, not floor  
❌ Using `int` for sum — can overflow (N=5×10⁴, each term up to 10⁶ → sum up to 5×10¹⁰)  

---

## 📚 Related Problems

- [ ] LeetCode #1283 — Find the Smallest Divisor Given a Threshold
- [ ] LeetCode #875 — Koko Eating Bananas (P20 — same template)
- [ ] LeetCode #1011 — Capacity to Ship Packages (P23)

---

## 🏆 Pattern Category

`Binary Search` · `Search Space` · `Greedy Feasibility`

---

## ⏱️ 30-Second Last-Minute Revision

> BS [1, max(nums)]. `ceil(x/d) = (x+d-1)/d`. Sum≤threshold → `hi=mid`. Else `lo=mid+1`. Return lo.
