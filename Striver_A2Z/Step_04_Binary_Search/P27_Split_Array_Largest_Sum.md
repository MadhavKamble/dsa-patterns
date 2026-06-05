# 🔥 Split Array — Largest Sum

> **LeetCode #410** · **Difficulty:** Hard · **Step 4 — Binary Search · P27**

---

## 🧠 Problem Understanding

**What is it asking?**
Given an integer array and integer `k`, split the array into `k` non-empty **contiguous subarrays** to **minimize the largest sum** among the k subarrays.

**Input:** `nums = [7, 2, 5, 10, 8]`, `k = 2` → **Output:** `18`
(Split [7,2,5,10] and [8] → max=24. OR [7,2,5] and [10,8] → max=18. OR [7,2] and [5,10,8] → max=23. Min of these is 18.)

**Input:** `nums = [1, 2, 3, 4, 5]`, `k = 2` → **Output:** `9` ([1,2,3,4] and [5] → max=10; [1,2,3] and [4,5] → max=9)

> **Note:** This is **identical** to the Book Allocation problem (Striver P26). The only difference is the variable name (k students vs k splits).

**Constraints:** `1 ≤ nums.length ≤ 1000`, `0 ≤ nums[i] ≤ 10⁶`, `1 ≤ k ≤ min(50, nums.length)`

---

## 🧠 How It Maps to Book Allocation

| Book Allocation | Split Array Largest Sum |
|----------------|------------------------|
| books = page counts | nums = subarray values |
| M students | k splits |
| max pages per student | largest sum of any subarray |
| minimize max pages | minimize largest sum |

They are **exactly the same problem** — same binary search approach, same greedy feasibility check.

---

## 🥇 Optimal Approach — Binary Search on Answer

### Key Observation

> 💡 Binary search on the maximum allowed sum per subarray.
>
> **Search space:** `[max(nums), sum(nums)]`
> - `lo = max(nums)`: each subarray must contain at least one element
> - `hi = sum(nums)`: the whole array as one subarray

### Algorithm
Same as P26. Find minimum `X` such that array can be split into ≤ k subarrays each with sum ≤ X.

### Complexity
- **Time:** O(N × log(sum(nums)))
- **Space:** O(1)

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * SPLIT ARRAY LARGEST SUM — binary search on largest sum
 *
 * IDENTICAL TO: Book Allocation (P26) / Capacity to Ship (P23)
 *
 * PROBLEM UNDERSTANDING:
 *   Split array into k subarrays. Minimize largest subarray sum.
 *
 * KEY OBSERVATION:
 *   Larger allowed sum → fewer splits needed (monotone).
 *   Binary search for minimum allowed sum where splits needed ≤ k.
 *
 * COMPLEXITY: Time O(N log sum) | Space O(1)
 */
class Solution {
private:
    int splitsNeeded(vector<int>& nums, long long maxSum) {
        int splits = 1;
        long long currentSum = 0;

        for (int x : nums) {
            if (currentSum + x > maxSum) {
                splits++;
                currentSum = 0;
            }
            currentSum += x;
        }
        return splits;
    }

public:
    int splitArray(vector<int>& nums, int k) {
        long long lo = *max_element(nums.begin(), nums.end());
        long long hi = accumulate(nums.begin(), nums.end(), 0LL);

        while (lo < hi) {
            long long mid = lo + (hi - lo) / 2;
            if (splitsNeeded(nums, mid) <= k)
                hi = mid;        // valid, minimize
            else
                lo = mid + 1;
        }

        return (int)lo;
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "Same as Book Allocation (P26). BS [max, sum]. Greedy splits count. ≤k → hi=mid. Else lo=mid+1."

---

## 📝 Short Revision Notes

- **Identical** to Book Allocation (P26) and very similar to Ship Packages (P23)
- The "minimize maximum" template: `lo < hi`, valid → `hi = mid`
- Key insight: splitting more subarrays = similar to allocating to more students
- LeetCode also has a DP approach: O(N² × k) time, O(N × k) space — binary search is far better

---

## ⚠️ Common Mistakes

❌ Not recognizing this as Book Allocation in disguise  
❌ Trying DP when binary search is much cleaner  

---

## 📚 Related Problems

- [ ] LeetCode #410 — Split Array Largest Sum
- [ ] GFG — Book Allocation (P26 — identical)
- [ ] LeetCode #1011 — Ship Packages (P23 — same template)
- [ ] LeetCode #875 — Koko Eating Bananas (P20 — same template)

---

## 🏆 Pattern Category

`Binary Search` · `Search Space` · `Greedy` · `Minimize Maximum`

---

## ⏱️ 30-Second Last-Minute Revision

> Identical to Book Allocation. BS [max(nums), sum(nums)]. Greedy splits count ≤ k → hi=mid. Else lo=mid+1.
