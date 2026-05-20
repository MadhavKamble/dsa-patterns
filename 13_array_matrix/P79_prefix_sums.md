# P79 — Prefix Sums

## 1. First-Timer Explanation

### What Is It?
**Prefix sum** (cumulative sum) converts a range query from O(n) to O(1) after O(n) preprocessing. The idea: `prefix[i]` = sum of `arr[0..i-1]`. Then `sum(l, r)` = `prefix[r+1] - prefix[l]`.

### Visual Walkthrough
```
arr:    [2, 4, 1, 3, 5]
prefix: [0, 2, 6, 7, 10, 15]   (prefix[0]=0, prefix[i] = prefix[i-1] + arr[i-1])

Sum of arr[1..3] = prefix[4] - prefix[1] = 10 - 2 = 8 ✓ (4+1+3=8)
Sum of arr[0..4] = prefix[5] - prefix[0] = 15 - 0 = 15 ✓
```

### Subarray Sum Equals K
```
Count subarrays with sum = k.
For each i: check if (runningSum - k) was seen before.
If prefix[i] - prefix[j] = k, then prefix[j] = prefix[i] - k.
Use hash map: count[prefix] = number of times this prefix sum appeared.
Start: count[0] = 1 (empty prefix has sum 0).
```

### Prefix Sum for Subarray Minimum/Maximum
```
The key equation: range_sum(l, r) = prefix[r+1] - prefix[l]
This means any range query can be answered in O(1) after O(n) build.
```

### When to Use
- "Sum of elements in range [l, r]" → prefix sum
- "Count subarrays with sum = k" → prefix sum + hash map
- "Subarray sum divisible by k" → prefix sum mod k + hash map
- "Longest subarray with sum ≤ k" → prefix + sliding window or binary search
- "2D range sum query" → 2D prefix sum (P83)

### Common Mistakes
1. Off-by-one: `prefix[i]` = sum of first `i` elements (1-indexed helps avoid confusion)
2. Count subarrays: always initialize `count[0] = 1` before the loop
3. Divisibility by k: `((prefix % k) + k) % k` handles negative modulo in C++
4. Not realizing the problem is a prefix sum problem (hidden as "range" or "subarray" queries)

---

## 2. Revision Card

**Recognition Signal:** "subarray sum", "range sum query", "number of subarrays with sum = k"

**Core Idea:** `prefix[i] = prefix[i-1] + arr[i]`. Range sum `[l,r] = prefix[r+1] - prefix[l]`. For counting: `res += count[prefix - k]`, then `count[prefix]++`.

**Trigger Keywords:** range sum, subarray sum, cumulative, prefix, count subarrays

**Complexity:** O(n) build, O(1) query for simple range sums; O(n) for counting with hash map

---

## 3. Interview Tell Signs

- "Range sum query (immutable)" → precompute prefix sum, answer in O(1)
- "Count subarrays with sum exactly k" → prefix + `unordered_map<int,int>`
- "Subarrays with sum divisible by k" → prefix mod k + hash map
- "Continuous subarray sum" (sum divisible by k) → same mod trick
- "Find pivot index" → leftSum == totalSum - leftSum - arr[i]
- "Product of array except self" → prefix product from left + suffix product from right

---

## 4. C++ Template

```cpp
#include <vector>
#include <unordered_map>
using namespace std;

// ── Build Prefix Sum ──────────────────────────────────────────────────────────
vector<int> buildPrefix(vector<int>& arr) {
    int n = arr.size();
    vector<int> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) prefix[i+1] = prefix[i] + arr[i];
    return prefix;
    // Range sum [l, r]: prefix[r+1] - prefix[l]
}

// ── Subarray Sum Equals K ─────────────────────────────────────────────────────
int subarraySum(vector<int>& nums, int k) {
    unordered_map<int,int> count;
    count[0] = 1; // empty prefix
    int runSum = 0, res = 0;
    for (int x : nums) {
        runSum += x;
        res += count[runSum - k]; // count subarrays ending here with sum k
        count[runSum]++;
    }
    return res;
}

// ── Subarray Sum Divisible by K ───────────────────────────────────────────────
int subarraysDivByK(vector<int>& nums, int k) {
    unordered_map<int,int> count;
    count[0] = 1;
    int runSum = 0, res = 0;
    for (int x : nums) {
        runSum += x;
        int mod = ((runSum % k) + k) % k; // normalize to [0, k-1]
        res += count[mod];
        count[mod]++;
    }
    return res;
}

// ── Range Sum Query (Immutable) ───────────────────────────────────────────────
class NumArray {
    vector<int> prefix;
public:
    NumArray(vector<int>& nums) {
        int n = nums.size();
        prefix.resize(n + 1, 0);
        for (int i = 0; i < n; i++) prefix[i+1] = prefix[i] + nums[i];
    }
    int sumRange(int l, int r) { return prefix[r+1] - prefix[l]; }
};
```

---

## 5. How to Present in Interview

**Verbal Script (Subarray Sum = K):**
> "Build a running prefix sum. At each position, check how many previous prefix sums equal `runningSum - k`. If `prefix[j] = runningSum - k`, then the subarray from j to current has sum k. Use a hash map to count prefix sums seen so far. Initialize count[0]=1 for the case where the subarray starts at index 0."

**Checklist:**
- [ ] Prefix array is size `n+1` with `prefix[0] = 0`
- [ ] Range sum `[l,r] = prefix[r+1] - prefix[l]`
- [ ] Count subarrays: `res += count[runSum - k]` BEFORE `count[runSum]++`
- [ ] Divisibility: normalize mod with `((x % k) + k) % k`
- [ ] Always initialize `count[0] = 1`

---

## 6. Problems

### Problem 1: Range Sum Query — Immutable
**Difficulty:** Easy | **LC:** 303

```cpp
class NumArray {
    vector<int> pre;
public:
    NumArray(vector<int>& nums) {
        pre.resize(nums.size()+1, 0);
        for (int i = 0; i < (int)nums.size(); i++) pre[i+1] = pre[i] + nums[i];
    }
    int sumRange(int l, int r) { return pre[r+1] - pre[l]; }
};
// Time: O(n) build, O(1) query | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Subarray Sum Equals K
**Difficulty:** Medium | **LC:** 560

```cpp
int subarraySum(vector<int>& nums, int k) {
    unordered_map<int,int> cnt; cnt[0]=1;
    int sum=0, res=0;
    for (int x:nums) { sum+=x; res+=cnt[sum-k]; cnt[sum]++; }
    return res;
}
// Time: O(n) | Space: O(n)
// Key: cnt[0]=1 handles subarrays starting from index 0
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Continuous Subarray Sum (Divisible by K)
**Difficulty:** Medium | **LC:** 523

```cpp
bool checkSubarraySum(vector<int>& nums, int k) {
    unordered_map<int,int> seen; seen[0]=-1; // remainder→first index
    int sum=0;
    for (int i=0; i<(int)nums.size(); i++) {
        sum = (sum + nums[i]) % k;
        if (seen.count(sum)) {
            if (i - seen[sum] >= 2) return true;
        } else seen[sum] = i;
    }
    return false;
}
// Time: O(n) | Space: O(k)
// Need length ≥ 2: check i - seen[mod] >= 2
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Find Pivot Index
**Difficulty:** Easy | **LC:** 724

```cpp
int pivotIndex(vector<int>& nums) {
    int total = 0;
    for (int x : nums) total += x;
    int left = 0;
    for (int i = 0; i < (int)nums.size(); i++) {
        if (left == total - left - nums[i]) return i;
        left += nums[i];
    }
    return -1;
}
// Time: O(n) | Space: O(1)
// Pivot: leftSum == rightSum → leftSum == total - leftSum - nums[i]
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Number of Subarrays with Bounded Maximum
**Difficulty:** Medium | **LC:** 795

**Approach:** `count(left, right) = count(0, right) - count(0, left-1)`. Count subarrays with max ≤ bound.

```cpp
int numSubarrayBoundedMax(vector<int>& nums, int left, int right) {
    auto count = [&](int bound) {
        int res = 0, cur = 0;
        for (int x : nums) {
            cur = (x <= bound) ? cur + 1 : 0;
            res += cur;
        }
        return res;
    };
    return count(right) - count(left - 1);
}
// Time: O(n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: Minimum Size Subarray Sum
**Difficulty:** Medium | **LC:** 209

**Approach:** Sliding window OR prefix sum + binary search. Sliding window is O(n).

```cpp
int minSubArrayLen(int target, vector<int>& nums) {
    int n = nums.size(), lo = 0, sum = 0, res = INT_MAX;
    for (int hi = 0; hi < n; hi++) {
        sum += nums[hi];
        while (sum >= target) {
            res = min(res, hi - lo + 1);
            sum -= nums[lo++];
        }
    }
    return res == INT_MAX ? 0 : res;
}
// Time: O(n) | Space: O(1)
// Binary search version: O(n log n) using prefix sum + lower_bound
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** Build prefix sum for [3,1,4,1,5]. What is sum of [1..3] (0-indexed)?
<details><summary>Reveal</summary>
prefix = [0, 3, 4, 8, 9, 14]. sum([1..3]) = prefix[4] - prefix[1] = 9 - 3 = 6. (1+4+1=6) ✓.
</details>

**Drill 2:** Count subarrays with sum=2 in [1,1,1]. Trace the hash map.
<details><summary>Reveal</summary>
cnt={0:1}. i=0: sum=1. cnt[1-2]=cnt[-1]=0. res=0. cnt={0:1,1:1}. i=1: sum=2. cnt[2-2]=cnt[0]=1. res=1. cnt={0:1,1:1,2:1}. i=2: sum=3. cnt[3-2]=cnt[1]=1. res=2. cnt={0:1,1:1,2:1,3:1}. Answer: 2 (subarrays [1,1] at indices [0,1] and [1,2]) ✓.
</details>

**Drill 3:** Check if [23,2,4,6,7] has a subarray sum divisible by 6. Mod at each step?
<details><summary>Reveal</summary>
k=6. seen={0:-1}. i=0: sum=23, mod=23%6=5. Not seen. seen={0:-1,5:0}. i=1: sum=25, mod=25%6=1. Not seen. seen[1]=1. i=2: sum=29, mod=29%6=5. Seen! i-seen[5]=2-0=2≥2 → return true. (Subarray [2,4] has sum=6, divisible by 6) ✓.
</details>

**Drill 4:** Find pivot index of [1,7,3,6,5,6]. What is the total sum and pivot?
<details><summary>Reveal</summary>
total = 1+7+3+6+5+6 = 28. i=0: left=0, right=28-0-1=27. 0≠27. i=1: left=1, right=28-1-7=20. 1≠20. i=2: left=8, right=28-8-3=17. 8≠17. i=3: left=11, right=28-11-6=11. 11=11 ✓. Pivot=3.
</details>

**Drill 5:** Why must we check `cnt[0] = 1` before the loop starts?
<details><summary>Reveal</summary>
If the subarray starting from index 0 has sum exactly k (e.g., nums=[1,2], k=3), then at index 1, runSum=3, and we look up cnt[3-3]=cnt[0]. Without the initial cnt[0]=1, this lookup returns 0 and we miss the valid subarray. The `cnt[0]=1` represents the "empty prefix before index 0" with sum 0.
</details>

---

## 8. Complexity Cheatsheet

| Operation | Time | Space |
|-----------|------|-------|
| Build prefix sum | O(n) | O(n) |
| Range sum query | O(1) | O(1) |
| Count subarrays sum = k | O(n) | O(n) |
| Count subarrays divisible by k | O(n) | O(k) |
| Find pivot index | O(n) | O(1) |
| Minimum size subarray sum | O(n) | O(1) |

---

## 9. Common Follow-up Questions

**Q: What if values can be negative (for subarray sum = k)?**
A: The hash map approach handles negative values naturally — prefix sums can repeat, and we count all occurrences. Sliding window does NOT work with negative values.

**Q: Can you do range SUM updates efficiently?**
A: Not with static prefix sum — an update requires rebuilding. Use a Fenwick Tree (BIT, P98) for O(log n) point updates and range queries.

**Q: What is the longest subarray with sum ≤ k (all positive)?**
A: Sliding window: expand right, shrink left when sum > k. O(n). For mixed signs, use prefix sum + monotone deque.

---

## 10. Cross-Pattern Connections

- **P80 (Difference Arrays):** Complement to prefix sum — difference array for range updates
- **P83 (2D Prefix Sum):** Extends to 2D range queries
- **P98 (Fenwick Tree):** Supports both updates and queries in O(log n)
- **P02 (Sliding Window):** Sliding window is a two-pointer prefix sum variant
- **P82 (Prefix Product):** Same idea applied to products instead of sums
