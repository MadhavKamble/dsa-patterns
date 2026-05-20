# P82 — Prefix Product and Array Tricks

## 1. First-Timer Explanation

### What Is It?
**Prefix product** problems compute products of subarrays or array elements excluding specific indices. The core trick: build a left-product array and a right-product array, then combine them. This avoids division and handles zeros gracefully.

### Product of Array Except Self
```
arr = [1, 2, 3, 4]

Left products (product of all elements to the LEFT of i):
left  = [1, 1, 2, 6]   (left[0]=1 by convention)

Right products (product of all to the RIGHT of i):
right = [24, 12, 4, 1]  (right[n-1]=1 by convention)

Result[i] = left[i] * right[i]:
= [1*24, 1*12, 2*4, 6*1] = [24, 12, 8, 6] ✓
```

### Maximum Product Subarray
```
Key insight: negative × negative = positive; zero resets.
Track both max and min at each position (min can become max after multiplying by negative).

arr = [2, -3, -2, 4]
i=0: maxP=2, minP=2
i=1: maxP=max(-3, 2*-3, 2*-3)=max(-3,-6,-6)=-3; minP=-6
i=2: maxP=max(-2, -3*-2, -6*-2)=max(-2,6,12)=12; minP=min(-2,-6,-12)=-12
Hmm, recalculate: maxP=max(nums[i], maxP*nums[i], minP*nums[i])
i=2: max(-2, -3*-2=6, -6*-2=12)=12. Answer: 12 ✓
```

### When to Use
- "Product of array except self" → left-product × right-product
- "Maximum product subarray" → track max AND min (negatives flip sign)
- "Subarray product less than k" → sliding window with product
- "Maximum product of three numbers" → sort, compare max3 vs max×min×min

### Common Mistakes
1. Product of array except self: start with left-pass building running product, then right-pass multiplies into same array
2. Max product subarray: must swap max and min when `nums[i] < 0` or just compute all three candidates
3. Product less than k: shrink left pointer while `product >= k`, not `product > k`

---

## 2. Revision Card

**Recognition Signal:** "product except self", "maximum product subarray", "product less than k"

**Core Idea:** Left pass builds cumulative left products; right pass (in reverse) multiplies cumulative right products into result. For max product: track both max and min prefix products.

**Trigger Keywords:** product, except self, maximum product, subarray product

**Complexity:** O(n) time, O(1) space (for product except self — store in output array)

---

## 3. Interview Tell Signs

- "Product of all elements except nums[i]" → left × right pass without division
- "Max product contiguous subarray" → track maxP, minP at each index
- "Number of subarrays with product < k" → sliding window
- "Can't use division" → confirms prefix product approach
- "Zeros in array" → product approach handles zeros naturally (left/right pass)

---

## 4. C++ Template

```cpp
#include <vector>
#include <algorithm>
using namespace std;

// ── Product of Array Except Self ──────────────────────────────────────────────
vector<int> productExceptSelf(vector<int>& nums) {
    int n = nums.size();
    vector<int> res(n, 1);
    // Left pass: res[i] = product of nums[0..i-1]
    for (int i = 1; i < n; i++) res[i] = res[i-1] * nums[i-1];
    // Right pass: multiply by product of nums[i+1..n-1]
    int right = 1;
    for (int i = n-1; i >= 0; i--) { res[i] *= right; right *= nums[i]; }
    return res;
}

// ── Maximum Product Subarray ──────────────────────────────────────────────────
int maxProduct(vector<int>& nums) {
    int maxP = nums[0], minP = nums[0], res = nums[0];
    for (int i = 1; i < (int)nums.size(); i++) {
        if (nums[i] < 0) swap(maxP, minP); // negative flips max and min
        maxP = max(nums[i], maxP * nums[i]);
        minP = min(nums[i], minP * nums[i]);
        res = max(res, maxP);
    }
    return res;
}

// ── Number of Subarrays with Product Less Than K ──────────────────────────────
int numSubarrayProductLessThanK(vector<int>& nums, int k) {
    if (k <= 1) return 0;
    int product = 1, left = 0, count = 0;
    for (int right = 0; right < (int)nums.size(); right++) {
        product *= nums[right];
        while (product >= k) product /= nums[left++];
        count += right - left + 1; // all subarrays ending at right with product < k
    }
    return count;
}

// ── Maximum Product of Three Numbers ─────────────────────────────────────────
int maximumProduct(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    // Either the three largest, or the largest plus the two smallest (negatives)
    return max(nums[n-1]*nums[n-2]*nums[n-3], nums[n-1]*nums[0]*nums[1]);
}
```

---

## 5. How to Present in Interview

**Verbal Script (Product Except Self):**
> "Two passes. In the first (left-to-right), I build a running product of all elements to the left: `res[i]` starts as 1, and each iteration multiplies in the previous element. In the second (right-to-left), I maintain a `right` running product, multiply it into `res[i]`, then update `right` by multiplying in `nums[i]`. The result contains left[i] × right[i] for each i. O(n) time, O(1) extra space."

**Verbal Script (Max Product Subarray):**
> "Track both maxP and minP ending at each index. When the next element is negative, a large negative minP becomes the best candidate for maxP. So before updating, if `nums[i] < 0` I swap maxP and minP. Then `maxP = max(nums[i], maxP * nums[i])`, taking `nums[i]` alone in case extending is worse (resets)."

**Checklist:**
- [ ] Product except self: left pass fills res, right pass multiplies into res with running right variable
- [ ] Max product: swap maxP/minP when `nums[i] < 0`
- [ ] Product < k: k=0 or k=1 returns 0 (no positive product < 1 with positive nums)
- [ ] Count subarrays: `count += right - left + 1` (all subarrays [left..right], [left+1..right], ..., [right..right])

---

## 6. Problems

### Problem 1: Product of Array Except Self
**Difficulty:** Medium | **LC:** 238

```cpp
vector<int> productExceptSelf(vector<int>& nums) {
    int n = nums.size();
    vector<int> res(n, 1);
    for (int i = 1; i < n; i++) res[i] = res[i-1] * nums[i-1];
    int right = 1;
    for (int i = n-1; i >= 0; i--) { res[i] *= right; right *= nums[i]; }
    return res;
}
// Time: O(n) | Space: O(1) extra (output not counted)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Maximum Product Subarray
**Difficulty:** Medium | **LC:** 152

```cpp
int maxProduct(vector<int>& nums) {
    int maxP=nums[0], minP=nums[0], res=nums[0];
    for (int i=1; i<(int)nums.size(); i++) {
        if (nums[i]<0) swap(maxP, minP);
        maxP = max(nums[i], maxP*nums[i]);
        minP = min(nums[i], minP*nums[i]);
        res = max(res, maxP);
    }
    return res;
}
// Time: O(n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Subarray Product Less Than K
**Difficulty:** Medium | **LC:** 713

```cpp
int numSubarrayProductLessThanK(vector<int>& nums, int k) {
    if (k <= 1) return 0;
    int prod = 1, lo = 0, cnt = 0;
    for (int hi = 0; hi < (int)nums.size(); hi++) {
        prod *= nums[hi];
        while (prod >= k) prod /= nums[lo++];
        cnt += hi - lo + 1;
    }
    return cnt;
}
// Time: O(n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Maximum Product of Three Numbers
**Difficulty:** Easy | **LC:** 628

```cpp
int maximumProduct(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    return max(nums[n-1]*nums[n-2]*nums[n-3], nums[n-1]*nums[0]*nums[1]);
}
// Time: O(n log n) | Space: O(1)
// O(n) alternative: track top3 max and bottom2 min in one pass
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Maximum Score from Performing Multiplication Operations
**Difficulty:** Hard | **LC:** 1770

**Approach:** 2D DP. `dp[i][j]` = max score after i operations where j chosen from left (i-j from right).

```cpp
int maximumScore(vector<int>& nums, vector<int>& mult) {
    int n = nums.size(), m = mult.size();
    vector<vector<int>> dp(m+1, vector<int>(m+1, INT_MIN));
    dp[0][0] = 0;
    for (int op = 0; op < m; op++) {
        for (int left = 0; left <= op; left++) {
            int right = op - left;
            if (dp[op][left] == INT_MIN) continue;
            // Pick from left
            dp[op+1][left+1] = max(dp[op+1][left+1], dp[op][left] + mult[op]*nums[left]);
            // Pick from right
            dp[op+1][left] = max(dp[op+1][left], dp[op][left] + mult[op]*nums[n-1-right]);
        }
    }
    int res = INT_MIN;
    for (int left = 0; left <= m; left++) res = max(res, dp[m][left]);
    return res;
}
// Time: O(m²) | Space: O(m²)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: Minimum Operations to Make Array Equal
**Difficulty:** Medium | **LC:** 1551

**Approach:** Math insight: sum of even-indexed elements vs odd-indexed in the target array.

```cpp
int minOperations(int n) {
    // Target: [1,3,5,...,2n-1]. Sum of left half (1..n-1 step 2) vs right half.
    // Number of ops = sum(target right half) - sum(initial right half)
    // Simplifies to: n/2 * (n/2) for even n; (n/2)*(n/2+1)/2... Actually:
    return (n * n) / 4;
}
// Time: O(1) | Space: O(1)
// Mathematical derivation: ops = n/2 * ceil(n/2) / 2
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** Product of array except self for [1,2,3,4]. Show left-pass and right-pass values.
<details><summary>Reveal</summary>
Left pass: res=[1,1,2,6]. (res[0]=1, res[1]=res[0]*nums[0]=1, res[2]=res[1]*nums[1]=2, res[3]=res[2]*nums[2]=6). Right pass: right=1. i=3: res[3]*=1=6, right*=4=4. i=2: res[2]*=4=8, right*=3=12. i=1: res[1]*=12=12, right*=2=24. i=0: res[0]*=24=24. Result: [24,12,8,6] ✓.
</details>

**Drill 2:** Max product subarray for [2,-3,-2,4]. Trace maxP, minP.
<details><summary>Reveal</summary>
i=0: maxP=2, minP=2, res=2. i=1 (nums=-3<0, swap): maxP=2→2, minP=2→2 (after swap maxP=minP=2). Now maxP=max(-3,2*-3)=max(-3,-6)=-3, minP=min(-3,2*-3)=min(-3,-6)=-6. res=max(2,-3)=2. i=2 (nums=-2<0, swap maxP=-6,minP=-3): maxP=max(-2,-6*-2)=max(-2,12)=12, minP=min(-2,-3*-2)=min(-2,-6)=-6. res=12. i=3 (nums=4>0, no swap): maxP=max(4,12*4)=48, minP=min(4,-6*4)=-24. res=48. Answer: 48... Wait let me recheck: [2,-3,-2,4]: 2*(-3)*(-2)*4=48 ✓.
</details>

**Drill 3:** Count subarrays with product < 10 in [10,5,2,6]. At right=2 (val=2), what is count added?
<details><summary>Reveal</summary>
right=0 (val=10): prod=10≥10, lo=1. prod=10/10=1<10. cnt+=0-1+1=0. right=1 (val=5): prod=1*5=5<10. cnt+=1-1+1=1. right=2 (val=2): prod=5*2=10≥10, lo=2. prod=10/5=2<10. cnt+=2-2+1=1. (Subarray [2]). Total so far: 2.
</details>

**Drill 4:** Maximum product of three from [-1,-2,-3,4]. What are the two candidates?
<details><summary>Reveal</summary>
Sorted: [-3,-2,-1,4]. Candidate 1 (top 3): (-1)*(-2)*4=8? No: nums[3]*nums[2]*nums[1] = 4*(-1)*(-2)=8. Candidate 2 (top 1 + bottom 2): 4*(-3)*(-2)=24. max(8,24)=24 ✓. (All three negatives: (-3)*(-2)*(-1)=-6, not a candidate since we include the largest which is 4.)
</details>

**Drill 5:** Why does swapping maxP and minP before the update work correctly for negative numbers?
<details><summary>Reveal</summary>
When nums[i] < 0, multiplying flips the sign of maxP and minP. The old maxP (positive) × negative = large negative (new candidate for minP). The old minP (most negative) × negative = large positive (new candidate for maxP). By swapping BEFORE computing, the `maxP * nums[i]` in the max formula now uses the old minP (which after swap becomes maxP), capturing the best positive result from the old minimum.
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Space |
|---------|------|-------|
| Product except self | O(n) | O(1) |
| Max product subarray | O(n) | O(1) |
| Subarray product < k | O(n) | O(1) |
| Max product of three | O(n log n) / O(n) | O(1) |
| Max score (2D DP) | O(m²) | O(m²) |

---

## 9. Common Follow-up Questions

**Q: Product of array except self — handle zeros?**
A: The left-right pass naturally handles zeros. If nums[i]=0, then left[i]=product of non-zero elements to left, right[i]=product to right. res[i]=0 only if there's another zero. For the zero index itself, res[i]=product of all other elements (possibly 0 if another zero exists).

**Q: Max product subarray — alternative to swap trick?**
A: `maxP = max({nums[i], maxP * nums[i], minP * nums[i]})`. And similarly for minP. The three-way max avoids the need to swap. The swap trick is equivalent but more elegant.

**Q: Why does the sliding window work for subarray product < k?**
A: All elements are positive (problem constraint), so the product is monotonically non-decreasing as the window expands and non-increasing as it shrinks. This monotonicity is required for the two-pointer / sliding window technique.

---

## 10. Cross-Pattern Connections

- **P79 (Prefix Sums):** Prefix product is the multiplicative analog; same left-right pass technique
- **P02 (Sliding Window):** Product < k is a sliding window variant
- **P30 (1D DP):** Max product subarray is a DP problem tracking multiple states
- **P81 (Matrix):** Product operations extend to matrix chains (matrix chain multiplication problem)
