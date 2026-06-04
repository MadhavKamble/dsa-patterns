# 🔥 Kadane's Algorithm — Maximum Subarray Sum

> **LeetCode #53** · **Difficulty:** Medium · **Step 3 — Arrays · P20 & P21**

---

## 🧠 Problem Understanding

**P20:** Find the maximum sum of a contiguous subarray.  
**P21:** Also return the actual subarray (start and end indices).

**Input:** `[-2,1,-3,4,-1,2,1,-5,4]` → **Output:** `6` (subarray `[4,-1,2,1]`)

**Key Observations:**
- Empty subarray not allowed (answer is the element itself if all negative)
- If all positive, answer is sum of entire array
- DP: `maxEndingHere[i] = max(arr[i], maxEndingHere[i-1] + arr[i])`

---

## 🥉 Brute Force
All subarrays. **Time:** O(N³) or O(N²) with prefix sums.

---

## 🥇 Optimal — Kadane's Algorithm

### Key Observation
> 💡 At each position, decide: extend the current subarray (add `arr[i]`) or start fresh from `arr[i]`.
>
> If `currentSum + arr[i] < arr[i]` → current sum is negative → discard it, start fresh.
>
> Equivalently: `currentSum = max(arr[i], currentSum + arr[i])`

### Algorithm (P20 — Sum only)
1. `maxSum = arr[0]`, `currentSum = arr[0]`
2. For `i` from 1 to N-1:
   - `currentSum = max(arr[i], currentSum + arr[i])`
   - `maxSum = max(maxSum, currentSum)`
3. Return `maxSum`

### Dry Run
`arr = [-2, 1, -3, 4, -1, 2, 1, -5, 4]`

| i | arr[i] | currentSum | maxSum |
|---|--------|------------|--------|
| 0 | -2 | -2 | -2 |
| 1 | 1 | max(1,-1)=**1** | 1 |
| 2 | -3 | max(-3,-2)=-2 | 1 |
| 3 | 4 | max(4,2)=**4** | 4 |
| 4 | -1 | max(-1,3)=**3** | 4 |
| 5 | 2 | max(2,5)=**5** | 5 |
| 6 | 1 | max(1,6)=**6** | **6** |
| 7 | -5 | max(-5,1)=1 | 6 |
| 8 | 4 | max(4,5)=5 | 6 |

**Output:** `6` ✅ (subarray `[4,-1,2,1]` at indices 3–6)

### Algorithm (P21 — With Indices)
Track `start`, `end`, `tempStart`:
- When starting fresh (`arr[i] > currentSum + arr[i]`): `tempStart = i`
- When updating `maxSum`: `start = tempStart`, `end = i`

### Complexity
- **Time:** O(N) · **Space:** O(1)

---

## 💻 Clean C++ Code

```cpp
/*
 * KADANE'S ALGORITHM
 *
 * DP insight: maxEndingHere[i] = max(arr[i], maxEndingHere[i-1] + arr[i])
 *   - If previous sum is negative, discard it (start fresh)
 *   - If positive, extend the current subarray
 *
 * Time O(N) | Space O(1)
 */
class Solution {
public:
    // P20: Maximum sum only
    int maxSubArray(vector<int>& nums) {
        int maxSum = nums[0];
        int currentSum = nums[0];

        for (int i = 1; i < nums.size(); i++) {
            currentSum = max(nums[i], currentSum + nums[i]);
            maxSum = max(maxSum, currentSum);
        }

        return maxSum;
    }

    // P21: Maximum sum + actual subarray indices
    tuple<int, int, int> maxSubArrayWithIndices(vector<int>& nums) {
        int maxSum = nums[0], currentSum = nums[0];
        int start = 0, end = 0, tempStart = 0;

        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] > currentSum + nums[i]) {
                currentSum = nums[i];
                tempStart = i;              // fresh start
            } else {
                currentSum += nums[i];
            }

            if (currentSum > maxSum) {
                maxSum = currentSum;
                start = tempStart;          // commit new start
                end = i;
            }
        }

        return {maxSum, start, end};
    }
};
```

---

## 🎤 Interview Explanation Script
> "Kadane's algorithm uses a DP observation: at each index, the maximum subarray ending here is either just `arr[i]` (start fresh) or `arr[i] + maxEndingHere[i-1]` (extend previous)."

> "The decision rule: if the running sum becomes negative, it can only drag down future sums — so we reset it to 0 (or to `arr[i]`). We track the global maximum throughout."

> "This is O(N) time, O(1) space — optimal since we must read every element."

> "For the subarray itself, I track `tempStart` whenever I start fresh, and commit it to `start` whenever I find a new global maximum."

---

## 🧾 Recall Line
> "Kadane: `currentSum = max(arr[i], currentSum + arr[i])`. Reset when negative drag. Track maxSum."

## 📝 Short Revision Notes
- DP recurrence: `dp[i] = max(arr[i], dp[i-1] + arr[i])`
- All negative array: answer is the maximum single element (Kadane handles this)
- All positive: answer is sum of full array
- Initialize `maxSum = arr[0]`, not `INT_MIN` or 0 (handles all-negative)
- Extension: circular subarray (LC 918) → max of Kadane's result vs (total - min subarray)

## ⚠️ Common Mistakes
❌ Initializing `maxSum = 0` — returns 0 for all-negative arrays (wrong)  
❌ Initializing `currentSum = 0` — same issue  
❌ Forgetting that we can start a new subarray at any position  

## 🔥 What Interviewer Is Testing
- Classic DP → greedy reduction
- Handling all-negative edge case
- Ability to extend to return indices

## 📚 Related Problems
- [ ] LeetCode #53 — Maximum Subarray (Kadane's)
- [ ] LeetCode #918 — Maximum Sum Circular Subarray
- [ ] LeetCode #152 — Maximum Product Subarray (P41 below)
- [ ] LeetCode #121 — Best Time to Buy and Sell Stock (similar idea)

## 🏆 Pattern Category
`Arrays` · `Dynamic Programming` · `Greedy` · `Kadane`

## ⏱️ 30-Second Revision
> `currentSum=arr[0], maxSum=arr[0]`. For i≥1: `currentSum=max(arr[i], currentSum+arr[i])`. `maxSum=max(maxSum, currentSum)`. Return maxSum.
