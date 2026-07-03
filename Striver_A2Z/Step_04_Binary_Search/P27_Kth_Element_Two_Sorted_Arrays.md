# 🔥 Kth Element of Two Sorted Arrays

> **GFG / LeetCode #4 (related)** · **Difficulty:** Hard · **Step 4 — Binary Search · P27**

---

## 🧠 Problem Understanding

**What is it asking?**
Given two sorted arrays, find the **Kth smallest** element of their merged order, in O(log(min(m, n))).

**Input:** `a = [2, 3, 6, 7, 9]`, `b = [1, 4, 8, 10]`, `k = 5` → **Output:** `6`
(merged `[1,2,3,4,6,7,8,9,10]`, 5th element is 6)

**Key Observation:**
Same **partition** idea as Median (P26), but the left side must hold exactly `k` elements. Once a valid partition puts `k` elements on the left, the answer is `max(l1, l2)`.

---

## 🎯 Interview Progression

### 🥉 Brute Force — Merge

Merge both arrays, return index `k-1`. **Time:** O(m+n) · **Space:** O(m+n).

### 🥈 Better — Two Pointers

Walk a merge, stop at the Kth element. **Time:** O(k) · **Space:** O(1).

---

### 🥇 Optimal — Binary Search on the Partition

> 💡 Left half size = `k`. Cut `mid1` from `a`, `mid2 = k - mid1` from `b`. The cut range is bounded: `low = max(0, k-n)`, `high = min(k, m)`. Valid partition (`l1<=r2 && l2<=r1`) → answer `max(l1, l2)`.

```cpp
class Solution {
public:
    int kthElement(vector<int>& a,vector<int>& b,int k){
        int m=a.size();
        int n=b.size();
        if(m>n) return kthElement(b,a,k);
        int left=k;
        int low=max(0,k-n),high=min(k,m);
        while(low<=high){
            int mid1=(low+high)>>1;
            int mid2=left-mid1;
            int l1=(mid1>0)?a[mid1-1]:INT_MIN;
            int l2=(mid2>0)?b[mid2-1]:INT_MIN;
            int r1=(mid1<m)?a[mid1]:INT_MAX;
            int r2=(mid2<n)?b[mid2]:INT_MAX;
            if(l1<=r2 && l2<=r1){
                return max(l1,l2);
            }else if(l1>r2){
                high=mid1-1;
            }else{
                low=mid1+1;
            }
        }
        return -1;
    }
};
```

**Time:** O(log(min(m, n))) · **Space:** O(1).

### Dry Run
`a = [2,3,6,7,9]`, `b = [1,4,8,10]`, `k = 5`; `low=max(0,5-4)=1`, `high=min(5,5)=5`

| mid1 | mid2 | l1 | r1 | l2 | r2 | Valid? |
|------|------|----|----|----|----|--------|
| 3 | 2 | a[2]=6 | a[3]=7 | b[1]=4 | b[2]=8 | 6≤8 ✅, 4≤7 ✅ → `max(6,4)=`**6** ✅ |

---

## 🧾 Recall Line *(10-Second Revision)*

> "Left size = k. `mid2=k-mid1`, cut range `[max(0,k-n), min(k,m)]`. Valid `l1<=r2 && l2<=r1` → `max(l1,l2)`."

---

## 📝 Short Revision Notes

- Same partition machinery as Median (P26); left half holds exactly `k` elements.
- Cut bounds: `low = max(0, k-n)` (can't leave more than `n` for `b`), `high = min(k, m)`.
- Sentinels: `INT_MIN` / `INT_MAX` at empty boundaries.
- Median is just this with `k = (m+n+1)/2` (plus even-total averaging).

---

## ⚠️ Common Mistakes

❌ Not clamping the cut range to `[max(0,k-n), min(k,m)]` → out-of-bounds cuts.
❌ Binary-searching the larger array.
❌ Forgetting the boundary sentinels.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "Kth smallest across two sorted arrays in log time" → **partition binary search with left size k**.

---

## 🏆 Pattern Category

`Binary Search` · `Two Arrays` · `Partition` · `Hard`

---

## ⏱️ 30-Second Last-Minute Revision

> **Partition smaller array, left size = k.** `mid2=k-mid1`, cut range `[max(0,k-n), min(k,m)]`. Valid `l1<=r2 && l2<=r1` → `max(l1,l2)`. `O(log min(m,n))`.
