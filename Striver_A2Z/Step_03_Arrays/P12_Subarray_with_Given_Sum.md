# 🔥 Subarray with Given Sum (Positive Elements)

> **GFG Classic** · **Difficulty:** Easy-Medium · **Step 3 — Arrays · P12**

---

## 🧠 Problem Understanding

Given an array of **non-negative** integers and a target sum `S`, find a contiguous subarray that sums to `S`. Return its start and end indices (1-indexed), or `[-1]` if not found.

**Input:** `arr=[1,2,3,7,5]`, S=12 → **Output:** `[2,4]` (subarray `[2,3,7]`)

**Key Observation:** Since all elements are non-negative, a sliding window works. Expanding window increases sum, shrinking decreases — monotone property enables two pointers.

---

## 🥉 Brute Force
Check all subarrays O(N²). Try each `(i,j)` pair.

---

## 🥇 Optimal — Sliding Window (Variable Size)

### Key Observation
> 💡 Non-negative elements → sum is monotone as window grows. If sum > S, shrink from left. If sum < S, expand right. If sum == S, found it.

### Algorithm
1. `start=0, sum=0`
2. For `end` from 0 to N-1:
   - `sum += arr[end]`
   - While `sum > S` and `start <= end`: `sum -= arr[start++]`
   - If `sum == S`: return `[start+1, end+1]`
3. Return `[-1]`

### Dry Run
`arr=[1,2,3,7,5]`, S=12

| end | arr[end] | sum | start | Action |
|-----|----------|-----|-------|--------|
| 0 | 1 | 1 | 0 | sum<12 |
| 1 | 2 | 3 | 0 | sum<12 |
| 2 | 3 | 6 | 0 | sum<12 |
| 3 | 7 | 13 | 0 | 13>12: shrink → sum=12, start=1 |
| 3 | — | 12 | 1 | **sum==12** → return [2,4] |

**Output:** `[2, 4]` (1-indexed) ✅

### Complexity
- **Time:** O(N) · **Space:** O(1)

---

## 💻 Clean C++ Code

```cpp
/*
 * SUBARRAY WITH GIVEN SUM (non-negative elements)
 * Sliding window: expand right, shrink left when sum exceeds S
 * Works ONLY for non-negative arrays (monotone window property)
 * Time O(N) | Space O(1)
 */
class Solution {
public:
    vector<int> subarrayWithSum(vector<int>& arr, long long S) {
        int n = arr.size();
        long long sum = 0;
        int start = 0;

        for (int end = 0; end < n; end++) {
            sum += arr[end];

            // shrink window from left while sum > S
            while (sum > S && start <= end)
                sum -= arr[start++];

            if (sum == S)
                return {start + 1, end + 1};   // 1-indexed
        }

        return {-1};
    }
};
```

**For arrays with negatives** → use prefix sum + hash map (see P34: Largest Subarray with 0 Sum pattern):
```cpp
// When negatives present: prefix sum approach
unordered_map<long long, int> prefixIdx;
prefixIdx[0] = -1;
long long prefix = 0;
for (int i = 0; i < n; i++) {
    prefix += arr[i];
    if (prefixIdx.count(prefix - S))
        return {prefixIdx[prefix - S] + 2, i + 1};
    if (!prefixIdx.count(prefix))
        prefixIdx[prefix] = i;
}
```

---

## 🎤 Interview Explanation Script
> "For non-negative arrays, I use a sliding window. The key insight is that adding elements only increases the sum — so if the sum exceeds S, shrinking the window from the left will decrease it. This gives O(N) time."

> "But if the array has negative elements, this monotone property breaks. Then I'd use prefix sums with a hash map: I look for a prefix at index j such that `prefix[i] - prefix[j] = S`."

---

## 🧾 Recall Line
> "Sliding window: expand right, shrink left when `sum>S`. Works only for non-negative arrays."

## 📝 Short Revision Notes
- Sliding window only valid for **non-negative** elements
- For negatives: prefix sum + hash map → O(N) time, O(N) space
- Return 1-indexed in GFG, 0-indexed in LeetCode

## ⚠️ Common Mistakes
❌ Applying sliding window to arrays with negative numbers  
❌ Off-by-one: returning 0-indexed vs 1-indexed

## 🏆 Pattern Category
`Arrays` · `Sliding Window` · `Two Pointers`

## ⏱️ 30-Second Revision
> Non-negative only: sliding window, expand right, shrink left when sum>S. O(N)/O(1).  
> With negatives: prefix sum + hash map. O(N)/O(N).
