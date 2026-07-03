# 🔥 Median of Two Sorted Arrays

> **LeetCode #4** · **Difficulty:** Hard · **Step 4 — Binary Search · P26**

---

## 🧠 Problem Understanding

**What is it asking?**
Given two sorted arrays, find the median of their combined sorted order in **O(log(min(m, n)))**.

**Input:** `nums1 = [1, 3]`, `nums2 = [2]` → **Output:** `2.0`
**Input:** `nums1 = [1, 2]`, `nums2 = [3, 4]` → **Output:** `2.5`

**Key Observation:**
Don't merge (that's O(m+n)). Instead **partition** both arrays so the left side holds the smallest `(m+n+1)/2` elements. A partition is valid when:
```
l1 <= r2  AND  l2 <= r1
```
Binary search the cut on the **smaller** array to find that valid partition.

---

## 🎯 Interview Progression

### 🥉 Brute Force — Merge

Merge fully, pick the middle. **Time:** O(m+n) · **Space:** O(m+n).

### 🥈 Better — Merge Without Storing (two pointers)

Walk to the middle counting elements. **Time:** O(m+n) · **Space:** O(1).

---

### 🥇 Optimal — Binary Search on the Partition

> 💡 Cut `nums1` into `mid1` elements, `nums2` into `mid2 = left - mid1`. Use `INT_MIN`/`INT_MAX` sentinels at the boundaries. Valid partition (`l1<=r2 && l2<=r1`): odd total → `max(l1,l2)`, even → `(max(l1,l2)+min(r1,r2))/2`.

```cpp
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1,vector<int>& nums2){
        int n1=nums1.size(),n2=nums2.size();
        if(n1>n2) return findMedianSortedArrays(nums2,nums1);
        int n=n1+n2;
        int left=(n1+n2+1)/2;
        int low=0,high=n1;
        while(low<=high){
            int mid1=(low+high)>>1;
            int mid2=left-mid1;
            int l1=INT_MIN,l2=INT_MIN,r1=INT_MAX,r2=INT_MAX;
            if(mid1<n1) r1=nums1[mid1];
            if(mid2<n2) r2=nums2[mid2];
            if(mid1-1>=0) l1=nums1[mid1-1];
            if(mid2-1>=0) l2=nums2[mid2-1];
            if(l1<=r2 && l2<=r1){
                if(n%2==1) return max(l1,l2);
                else return ((double)(max(l1,l2)+min(r1,r2)))/2.0;
            }else if(l1>r2){
                high=mid1-1;
            }else{
                low=mid1+1;
            }
        }
        return 0;
    }
};
```

**Time:** O(log(min(m, n))) · **Space:** O(1).

### Dry Run
`nums1 = [1, 2]`, `nums2 = [3, 4]`, `left = 2`, search cut on nums1 `[0, 2]`

| mid1 | mid2 | l1 | r1 | l2 | r2 | Valid? | Action |
|------|------|----|----|----|----|--------|--------|
| 1 | 1 | 1 | 2 | 3 | 4 | l2=3>r1=2 ❌ | low=2 |
| 2 | 0 | 2 | +∞ | −∞ | 3 | 2≤3 ✅, −∞≤+∞ ✅ | even → (max(2,−∞)+min(+∞,3))/2 = (2+3)/2 = **2.5** ✅ |

---

## 🧾 Recall Line *(10-Second Revision)*

> "BS cut on smaller array. `left=(m+n+1)/2`, `mid2=left-mid1`. Valid: `l1<=r2 && l2<=r1`. Odd→max(l1,l2), even→avg(max(l1,l2),min(r1,r2))."

---

## 📝 Short Revision Notes

- Always binary-search the **smaller** array (swap if `n1 > n2`).
- `left = (m+n+1)/2` — the `+1` puts the extra element on the left for odd totals.
- Sentinels: `INT_MIN` when a left side is empty, `INT_MAX` when a right side is empty.
- `l1 > r2` → too many from nums1 → `high = mid1-1`; else `low = mid1+1`.

---

## ⚠️ Common Mistakes

❌ Binary-searching the larger array → correct but slower / more edge cases.
❌ Missing the `INT_MIN`/`INT_MAX` sentinels → out-of-bounds.
❌ `(m+n)/2` instead of `(m+n+1)/2` → off-by-one for odd totals.
❌ Integer overflow / no `double` cast in the even-case average.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "median / order statistic across two sorted arrays in log time" → **binary search on the partition**.

---

## 🏆 Pattern Category

`Binary Search` · `Two Arrays` · `Partition` · `Hard`

---

## ⏱️ 30-Second Last-Minute Revision

> **Partition smaller array.** `left=(m+n+1)/2`, `mid2=left-mid1`, sentinels at edges. Valid `l1<=r2 && l2<=r1` → odd `max(l1,l2)`, even `avg(max(l1,l2),min(r1,r2))`. `O(log min(m,n))`.
