# 🔥 Kth Element of Two Sorted Arrays

> **GFG + LeetCode #4** (related) · **Difficulty:** Hard · **Step 4 — P13 & P31**

---

## 🧠 Problem Understanding

Given two sorted arrays of sizes M and N, find the **Kth smallest element** in their merged sorted order.

**Input:** `A=[2,3,6,7,9]`, `B=[1,4,8,10]`, K=5 → **Output:** `6`

---

## 🥉 Brute Force
Merge both arrays, return index K-1. **Time:** O(M+N) · **Space:** O(M+N)

## 🥈 Better — Two Pointers
Use merge step without storing, stop at Kth. **Time:** O(K) · **Space:** O(1)

---

## 🥇 Optimal — Binary Search

### Key Observation
> 💡 Partition A into `cut1` elements and B into `cut2 = K - cut1` elements. The Kth element is the maximum of the smaller parts if the partition is valid.
> Valid partition: `A[cut1-1] <= B[cut2]` and `B[cut2-1] <= A[cut1]`

### Algorithm
1. Binary search on the smaller array (A), `cut1` from `max(0, K-n)` to `min(K, m)`
2. `cut2 = K - cut1`
3. Check validity: `l1=A[cut1-1], l2=B[cut2-1], r1=A[cut1], r2=B[cut2]`
4. If `l1 <= r2` and `l2 <= r1`: answer = `max(l1, l2)`
5. If `l1 > r2`: `hi = cut1 - 1` (too many from A)
6. Else: `lo = cut1 + 1`

### Complexity
- **Time:** O(log(min(M,N))) · **Space:** O(1)

```cpp
/*
 * KTH ELEMENT OF TWO SORTED ARRAYS — binary search on partition
 *
 * Partition A[0..cut1-1] + B[0..cut2-1] = K elements
 * Valid if max of left partition <= min of right partition
 *
 * Time O(log min(M,N)) | Space O(1)
 */
class Solution {
public:
    int kthElement(vector<int>& A, vector<int>& B, int K) {
        int m = A.size(), n = B.size();
        if (m > n) return kthElement(B, A, K);   // binary search on smaller

        int lo = max(0, K - n), hi = min(K, m);

        while (lo <= hi) {
            int cut1 = lo + (hi - lo) / 2;
            int cut2 = K - cut1;

            int l1 = (cut1 == 0) ? INT_MIN : A[cut1 - 1];
            int l2 = (cut2 == 0) ? INT_MIN : B[cut2 - 1];
            int r1 = (cut1 == m) ? INT_MAX : A[cut1];
            int r2 = (cut2 == n) ? INT_MAX : B[cut2];

            if (l1 <= r2 && l2 <= r1)
                return max(l1, l2);          // found valid partition
            else if (l1 > r2)
                hi = cut1 - 1;               // too many from A
            else
                lo = cut1 + 1;               // too few from A
        }
        return -1;
    }
};
```

### Dry Run
`A=[2,3,6,7,9]`, `B=[1,4,8,10]`, K=5

lo=max(0,5-4)=1, hi=min(5,5)=5

| cut1 | cut2 | l1 | l2 | r1 | r2 | Valid? |
|------|------|----|----|----|----|--------|
| 3 | 2 | A[2]=6 | B[1]=4 | A[3]=7 | B[2]=8 | l1=6≤r2=8 ✅, l2=4≤r1=7 ✅ → return max(6,4)=**6** ✅ |

---

## 🧾 Recall Line
> "Partition: `cut1` from A, `cut2=K-cut1` from B. Valid: `l1≤r2 && l2≤r1`. Answer: `max(l1, l2)`."

## 📝 Short Revision Notes
- Binary search on smaller array for efficiency
- Guards: `INT_MIN` when cut=0, `INT_MAX` when cut=size
- Same technique solves **Median of Two Sorted Arrays** (K = (M+N+1)/2)
- `lo = max(0, K-n)`: can't take more from A than exists, can't leave negative for B

## ⚠️ Common Mistakes
❌ Not handling edge case when cut1=0 or cut2=0 (INT_MIN guard)  
❌ Not handling cut1=m or cut2=n (INT_MAX guard)  
❌ Binary searching on larger array (wastes time)

## 🏆 Pattern Category
`Binary Search` · `Two Arrays` · `Partition`

## ⏱️ 30-Second Revision
> Partition A into cut1, B into K-cut1. Binary search cut1. Valid: l1≤r2 && l2≤r1 → return max(l1,l2). Guards: INT_MIN/INT_MAX at boundaries.
