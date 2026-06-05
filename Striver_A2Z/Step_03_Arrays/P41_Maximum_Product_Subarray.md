# 🔥 Maximum Product Subarray

> **LeetCode #152** · **Difficulty:** Medium · **Step 3 — Arrays · P41**

---

## 🧠 Problem Understanding

**What is it asking?**
Find the contiguous subarray with the **maximum product** and return that product.

**Input:** `nums = [2, 3, -2, 4]` → **Output:** `6` (subarray `[2, 3]`)
**Input:** `nums = [-2, 0, -1]` → **Output:** `0`
**Input:** `nums = [-2, 3, -4]` → **Output:** `24` (full array: -2×3×-4=24)

**Constraints:** 1 ≤ N ≤ 2×10⁴, values in [-10, 10]

**Key Observations:**
- Unlike Maximum Subarray Sum (Kadane's), a negative number can flip the maximum to minimum and vice versa
- A negative × negative = positive → a previously minimum product can become maximum
- We need to track BOTH `maxProduct` and `minProduct` at each position
- Zero resets both (fresh start)

**Simple Example:**
```
nums = [-2, 3, -4]
At index 0: max=-2, min=-2
At index 1: max=max(3, 3*(-2), 3*(-2))=3, min=min(3, -6)=-6
At index 2: max=max(-4, -4*3, -4*(-6))=max(-4,-12,24)=24
                  ↑ the negative flipped min→max!
Answer: 24
```

---

## 🥉 Brute Force Approach

### Idea
Check all subarrays. For each, compute the product. Track the maximum.

### Algorithm
1. `maxProd = INT_MIN`
2. For `i` from 0 to N-1:
3.   `prod = 1`
4.   For `j` from i to N-1:
5.     `prod *= nums[j]`
6.     `maxProd = max(maxProd, prod)`
7. Return `maxProd`

### Complexity
- **Time:** O(N²)
- **Space:** O(1)

### C++ Code
```cpp
// BRUTE FORCE: all subarrays O(N²)
int maxProduct(vector<int>& nums) {
    int maxProd = INT_MIN;
    int n = nums.size();
    for (int i = 0; i < n; i++) {
        int prod = 1;
        for (int j = i; j < n; j++) {
            prod *= nums[j];
            maxProd = max(maxProd, prod);
        }
    }
    return maxProd;
}
```

---

## 🥈 Better Approach — Track Max and Min

### Key Observation

> 💡 At every position, the maximum product subarray ending here is one of:
> 1. `nums[i]` alone (start fresh)
> 2. `prevMax * nums[i]` (extend max subarray)
> 3. `prevMin * nums[i]` (a negative flips min → max)
>
> Similarly for minimum (we need it because negatives can turn minimum into maximum).

### Algorithm
1. `maxProd = nums[0]`, `minProd = nums[0]`, `result = nums[0]`
2. For `i` from 1 to N-1:
   - `tempMax = max({nums[i], maxProd * nums[i], minProd * nums[i]})`
   - `minProd = min({nums[i], maxProd * nums[i], minProd * nums[i]})` (use old maxProd!)
   - `maxProd = tempMax`
   - `result = max(result, maxProd)`
3. Return `result`

### Dry Run

**Input:** `nums = [2, 3, -2, 4]`

| i | nums[i] | maxProd | minProd | result |
|---|---------|---------|---------|--------|
| 0 | 2 | 2 | 2 | 2 |
| 1 | 3 | max(3, 6, 6)=**6** | min(3, 6, 6)=3 | 6 |
| 2 | -2 | max(-2, -12, -6)=**-2** | min(-2, -12, -6)=-12 | 6 |
| 3 | 4 | max(4, -8, -48)=**4** | min(4, -8, -48)=-48 | 6 |

**Output:** `6` ✅ (subarray `[2, 3]`)

**Input:** `nums = [-2, 3, -4]`

| i | nums[i] | maxProd | minProd | result |
|---|---------|---------|---------|--------|
| 0 | -2 | -2 | -2 | -2 |
| 1 | 3 | max(3, -6, -6)=**3** | min(3, -6, -6)=-6 | 3 |
| 2 | -4 | max(-4, -12, **24**)=24 | min(-4, -12, 24)=-12 | **24** |

**Output:** `24` ✅ (negative × negative = positive!)

### Complexity
- **Time:** O(N) · **Space:** O(1)

---

## 🥇 Optimal Approach — Prefix/Suffix Products

### Key Observation

> 💡 The maximum product subarray is either:
> - A prefix (starts from index 0) or
> - A suffix (ends at index N-1), or
> - A product that "skips" a zero
>
> Traversing forward, reset running product to 1 on zero (or when it becomes 0). Similarly traverse backward. Maximum of all non-zero products found during both traversals is the answer.
>
> **Why this works:** Any negative-count subarray becomes positive when extended to include an even number of negatives. The forward and backward passes capture all possible products.

### Algorithm
1. `result = INT_MIN`, `prefix = 1`, `suffix = 1`
2. For `i` from 0 to N-1:
   - If `prefix == 0`: `prefix = 1`
   - If `suffix == 0`: `suffix = 1`
   - `prefix *= nums[i]`
   - `suffix *= nums[N-1-i]`
   - `result = max({result, prefix, suffix})`
3. Return `result`

### Dry Run

**Input:** `nums = [2, 3, -2, 4]`

| i | nums[i] | prefix | nums[N-1-i] | suffix | result |
|---|---------|--------|-------------|--------|--------|
| 0 | 2 | 2 | 4 | 4 | 4 |
| 1 | 3 | 6 | -2 | -8 | 6 |
| 2 | -2 | -12 | 3 | -24 | 6 |
| 3 | 4 | -48 | 2 | -48 | 6 |

**Output:** `6` ✅

This approach is slightly simpler to code but the "track max and min" approach is more standard in interviews.

---

## 🎤 Interview Explanation Script

> "Unlike maximum subarray sum, we can't just reset when the product goes negative — because a negative might pair with a future negative to give a large positive."

> "The key insight: at every position, we need to track both the maximum and minimum products ending here. A negative number can flip the minimum into the maximum."

> "At each step, the new maximum is the best of: starting fresh at this element, extending the previous max (if nums[i] positive), or extending the previous min (if nums[i] negative — flips it to positive). Same logic for new minimum. We must save `maxProd` before updating `minProd` since `minProd` uses the old `maxProd`."

> "Edge cases: zero resets both max and min to the current element (which becomes `nums[i]` in the `max/min(nums[i], ...)` formula)."

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * MAXIMUM PRODUCT SUBARRAY
 *
 * PROBLEM UNDERSTANDING:
 *   Find contiguous subarray with maximum product.
 *
 * KEY OBSERVATION:
 *   Negatives can flip max→min and min→max.
 *   Track BOTH maxProd and minProd ending at current index.
 *   Use tempMax to avoid using updated maxProd when computing minProd.
 *
 * EDGE CASES:
 *   - All negative even count: product of all is positive (max)
 *   - All negative odd count: product excluding first or last is max
 *   - Contains 0: resets product (handled by nums[i] alone in max/min formula)
 *   - Single element: return that element
 *
 * COMPLEXITY: Time O(N) | Space O(1)
 */
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int maxProd = nums[0];
        int minProd = nums[0];
        int result = nums[0];

        for (int i = 1; i < nums.size(); i++) {
            // tempMax: avoid using updated maxProd when computing new minProd
            int tempMax = max({nums[i], maxProd * nums[i], minProd * nums[i]});
            minProd = min({nums[i], maxProd * nums[i], minProd * nums[i]});
            maxProd = tempMax;

            result = max(result, maxProd);
        }

        return result;
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "Track `maxProd` AND `minProd`. New max = `max(nums[i], maxProd*nums[i], minProd*nums[i])`. Save old max before updating min."

---

## 📝 Short Revision Notes

- Key difference from Kadane: need BOTH max and min (negatives flip signs)
- Save `tempMax` before updating `minProd` — uses old `maxProd`
- `nums[i]` alone in the `max/min` formula handles zeros and starting fresh
- Initialize both `maxProd = minProd = result = nums[0]` (handles single element)
- Prefix/suffix approach also O(N)/O(1) — simpler code, same complexity
- With zeros: formula handles automatically (multiplying by 0 gives 0, which loses to `nums[i]`)

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "Maximum product subarray"
- "Product with negatives"
- "Subarray optimization with sign flipping"

**I should think of:** Track max AND min simultaneously (sign flip problem)

---

## ⚠️ Common Mistakes

❌ Only tracking `maxProd` (Kadane's style) — misses negative-flip optimization  
❌ Using updated `maxProd` when computing `minProd` — use `tempMax` or compute both before updating  
❌ Initializing `result = 0` — misses arrays with all negatives (e.g., `[-3]` → answer is `-3`)  
❌ Resetting on zero like `if nums[i]==0: reset` — the formula handles zeros automatically  

---

## 🔥 What Interviewer Is Testing

- **Concept:** Why tracking minimum is necessary for maximum product
- **Reasoning:** Sign flip: negative × negative = positive
- **Detail:** Order of updates (tempMax before updating minProd)

---

## 🚀 Alternative Approaches

| Approach | Time | Space | Notes |
|----------|------|-------|-------|
| Track max+min | O(N) | O(1) | Standard interview answer |
| Prefix+suffix products | O(N) | O(1) | Cleaner code, same complexity |
| Brute force | O(N²) | O(1) | Too slow |

**Prefix/Suffix alternative:**
```cpp
int maxProduct(vector<int>& nums) {
    int n = nums.size(), result = INT_MIN;
    int prefix = 1, suffix = 1;
    for (int i = 0; i < n; i++) {
        prefix = (prefix == 0 ? 1 : prefix) * nums[i];
        suffix = (suffix == 0 ? 1 : suffix) * nums[n-1-i];
        result = max({result, prefix, suffix});
    }
    return result;
}
```

---

## 📚 Related Problems

- [ ] LeetCode #152 — Maximum Product Subarray
- [ ] LeetCode #53 — Maximum Subarray (Kadane's — easier, no sign flip)
- [ ] LeetCode #238 — Product of Array Except Self (related prefix/suffix products)
- [ ] LeetCode #628 — Maximum Product of Three Numbers

---

## 🏆 Pattern Category

`Arrays` · `Dynamic Programming` · `Greedy`

---

## 🎯 Difficulty Analysis

**Rating:** Medium

**Why challenging:** Kadane's algorithm for sum doesn't transfer directly — the negative-flip property requires tracking both max and min. The order of updates (tempMax before minProd) is an easy implementation mistake.

---

## 📈 Progression Insight

**Simpler version:** LC #53 Maximum Subarray — no sign flips, standard Kadane's

**Follow-up:** What if you could remove one element? → O(N) with extra DP tracking

**Harder:** Maximum product of K non-overlapping subarrays → DP with multiple states

---

## ⏱️ 30-Second Last-Minute Revision

> **Problem:** Maximum product of contiguous subarray  
> **Approach:** Track `maxProd` and `minProd`. Each step: `tempMax = max(nums[i], max*nums[i], min*nums[i])`. `minProd = min(...)`. `maxProd = tempMax`.  
> **Key trick:** Save old max as `tempMax` before computing new min  
> **Time:** O(N) | **Space:** O(1)  
> **Watch out for:** Need BOTH max and min — negatives flip signs
