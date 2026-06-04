# 🔥 Median of Two Sorted Arrays

> **LeetCode #4** · **Difficulty:** Hard · **Step 4 — P24 & P30**

---

## 🧠 Problem Understanding

Given two sorted arrays of sizes M and N, find the median of the combined sorted array in **O(log(M+N))**.

**Input:** `A=[1,3]`, `B=[2]` → **Output:** `2.0`  
**Input:** `A=[1,2]`, `B=[3,4]` → **Output:** `2.5`

**Why hard:** Can't simply merge (O(M+N) space). Must binary search on partition.

---

## 🥉 Brute Force
Merge and return middle. **Time:** O(M+N) · **Space:** O(M+N)

## 🥈 Better
Two pointers to find Kth element without merging. **Time:** O((M+N)/2) · **Space:** O(1)

---

## 🥇 Optimal — Binary Search on Partition

### Key Observation
> 💡 Find a partition of A and B such that:
> - Total left elements = `(M+N+1)/2`
> - `max(A_left) ≤ min(B_right)` AND `max(B_left) ≤ min(A_right)`
>
> If valid: median = `max(A_left, B_left)` for odd total, or `(max(A_left,B_left) + min(A_right,B_right))/2` for even total.

```
A: [   left_A   |   right_A   ]
B: [   left_B   |   right_B   ]

Valid partition: A_left ∪ B_left = smallest (M+N+1)/2 elements
```

### Algorithm
1. Ensure `m ≤ n` (binary search on smaller array)
2. Binary search `cut1` in A from `[0, m]`:
   - `cut2 = (m+n+1)/2 - cut1`
   - `l1=A[cut1-1]`, `l2=B[cut2-1]`, `r1=A[cut1]`, `r2=B[cut2]`
   - If `l1 > r2`: too many from A → `hi = cut1-1`
   - If `l2 > r1`: too few from A → `lo = cut1+1`
   - Else: valid partition → compute median

### Dry Run
`A=[1,2]`, `B=[3,4]`, M=2, N=2, half=2

| cut1 | cut2 | l1 | l2 | r1 | r2 | Valid? |
|------|------|----|----|----|-----|--------|
| 1 | 1 | A[0]=1 | B[0]=3 | A[1]=2 | B[1]=4 | l1=1≤r2=4 ✅, l2=3>r1=2 ❌ → lo=2 |
| 2 | 0 | A[1]=2 | -∞ | +∞ | B[0]=3 | l1=2≤r2=3 ✅, l2=-∞≤r1=+∞ ✅ |

Median = `(max(2,-∞) + min(+∞,3)) / 2 = (2+3)/2 = 2.5` ✅

### Complexity
- **Time:** O(log(min(M,N))) · **Space:** O(1)

---

## 💻 Clean C++ Code

```cpp
/*
 * MEDIAN OF TWO SORTED ARRAYS — binary search on partition
 *
 * IDEA: Partition A into cut1 elements, B into cut2 = half - cut1 elements.
 *       Find cut1 such that max(left) <= min(right) for both arrays.
 *
 * GUARDS: INT_MIN when cut=0 (empty left side), INT_MAX when cut=size (empty right)
 *
 * Total left side = (M+N+1)/2 — the +1 handles odd total correctly
 *
 * Time O(log min(M,N)) | Space O(1)
 */
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // ensure binary search on smaller array
        if (nums1.size() > nums2.size())
            return findMedianSortedArrays(nums2, nums1);

        int m = nums1.size(), n = nums2.size();
        int half = (m + n + 1) / 2;
        int lo = 0, hi = m;

        while (lo <= hi) {
            int cut1 = lo + (hi - lo) / 2;
            int cut2 = half - cut1;

            int l1 = (cut1 == 0) ? INT_MIN : nums1[cut1 - 1];
            int l2 = (cut2 == 0) ? INT_MIN : nums2[cut2 - 1];
            int r1 = (cut1 == m) ? INT_MAX : nums1[cut1];
            int r2 = (cut2 == n) ? INT_MAX : nums2[cut2];

            if (l1 <= r2 && l2 <= r1) {
                // valid partition found
                if ((m + n) % 2 == 1)
                    return max(l1, l2);                    // odd: median is max of left
                else
                    return (max(l1, l2) + min(r1, r2)) / 2.0;  // even: avg of middle two
            } else if (l1 > r2) {
                hi = cut1 - 1;     // too many from nums1
            } else {
                lo = cut1 + 1;     // too few from nums1
            }
        }
        return 0.0;
    }
};
```

---

## 🎤 Interview Explanation Script
> "Merging is O(M+N) space. For O(log(min(M,N))), I binary search on the partition of the smaller array."

> "I partition A into `cut1` elements and B into `cut2 = half - cut1` elements, where `half = (M+N+1)/2`. A valid partition means: the maximum of the left sides ≤ the minimum of the right sides."

> "I adjust `cut1` based on whether A's last left element exceeds B's first right element, or vice versa. INT_MIN and INT_MAX act as sentinels for empty sides."

> "For odd total: median is `max(l1, l2)`. For even: average of `max(l1,l2)` and `min(r1,r2)`."

---

## 🧾 Recall Line
> "Partition A into cut1, B into half-cut1. Valid: l1≤r2 && l2≤r1. Median = max(l1,l2) odd, avg of middle two for even."

## 📝 Short Revision Notes
- Always binary search on the **smaller** array
- `half = (M+N+1)/2` — the +1 handles odd totals (larger left side)
- Guards: `INT_MIN` when cut=0, `INT_MAX` when cut=size
- `l1 > r2` → too many from A → `hi = cut1-1`
- `l2 > r1` → too few from A → `lo = cut1+1`

## ⚠️ Common Mistakes
❌ Binary searching on larger array — correct but slower  
❌ Forgetting INT_MIN/INT_MAX guards → index out of bounds  
❌ `half = (m+n)/2` — off by one for odd totals  
❌ Integer overflow in `(max(l1,l2) + min(r1,r2))` — cast to double or handle carefully

## 🔥 What Interviewer Is Testing
- Most asked FAANG hard problem
- Partitioning concept, boundary guards
- Understanding odd vs even total handling

## 🏆 Pattern Category
`Binary Search` · `Two Arrays` · `Partition` · `Hard`

## ⏱️ 30-Second Revision
> BS on smaller array. `cut2 = half-cut1`. Valid: `l1≤r2 && l2≤r1`. l1>r2→hi--. l2>r1→lo++. Odd: `max(l1,l2)`. Even: `avg(max(l1,l2), min(r1,r2))`.
