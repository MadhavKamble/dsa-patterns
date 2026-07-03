# 🔥 Kth Missing Positive Number

> **LeetCode #1539** · **Difficulty:** Easy · **Step 4 — Binary Search · P20**

---

## 🧠 Problem Understanding

**What is it asking?**
Given a **strictly increasing** array of positive integers, find the **Kth missing** positive number.

**Input:** `arr = [2, 3, 4, 7, 11]`, `k = 5` → **Output:** `9` (missing: 1,5,6,8,9,10,... → 5th is 9)
**Input:** `arr = [1, 2, 3, 4]`, `k = 2` → **Output:** `6` (missing: 5,6,... → 2nd is 6)

**Key Observation:**
At index `i`, the array *should* read `1, 2, ..., (i+1)` if nothing were missing. So the count of missing numbers up to `arr[i]` is:
```
missing = arr[i] - (i + 1)
```
This is monotonically non-decreasing → binary-searchable.

---

## 🎯 Interview Progression

### 🥉 Brute Force — Linear Walk

Walk the array; while `arr[i] <= k`, the k-th missing shifts right by one (`k++`). Answer is `k` at the end. **Time:** O(n).

```cpp
int findKthPositive(vector<int>& arr,int k){
    for(int i=0;i<arr.size();i++){
        if(arr[i]<=k) k++;
        else break;
    }
    return k;
}
```

---

### 🥇 Optimal — Binary Search on Index

> 💡 Find the **smallest index** where `missing = arr[mid] - (mid+1) >= k`. After the loop, `low` positions us just past enough missing numbers, and the answer is `low + k`.

```cpp
class Solution {
public:
    int findKthPositive(vector<int>& arr,int k){
        int low=0,high=arr.size()-1;
        while(low<=high){
            int mid=low+(high-low)/2;
            int missing=arr[mid]-(mid+1);
            if(missing<k){
                low=mid+1;
            }else{
                high=mid-1;
            }
        }
        return low+k;
    }
};
```

**Time:** O(log N) · **Space:** O(1).

### Dry Run
`arr = [2, 3, 4, 7, 11]`, `k = 5`

| low | high | mid | arr[mid] | missing = arr[mid]-(mid+1) | <5? | Action |
|-----|------|-----|----------|----------------------------|-----|--------|
| 0 | 4 | 2 | 4 | 4-3 = 1 | ✅ | low=3 |
| 3 | 4 | 3 | 7 | 7-4 = 3 | ✅ | low=4 |
| 4 | 4 | 4 | 11 | 11-5 = 6 | ❌ | high=3 |
| 4 | 3 | — | — | — | — | stop |

**Answer:** `low + k = 4 + 5 = 9` ✅

---

## 🧾 Recall Line *(10-Second Revision)*

> "`missing = arr[mid] - (mid+1)`. Find first index with `missing >= k`. Answer = `low + k`."

---

## 📝 Short Revision Notes

- Missing count up to index `i`: `arr[i] - (i + 1)`.
- We binary-search the **index** (not a value); the answer is derived as `low + k`.
- Why `low + k`: after the loop, `low` elements sit before the answer, and `k` more missing numbers push it up.
- Handles "all missing before the array" (e.g. `k` small vs `arr[0]` large) naturally.

---

## ⚠️ Common Mistakes

❌ Off-by-one in `missing = arr[i] - (i+1)` (using `i` instead of `i+1`).
❌ Returning `high + k` or `arr[low] - something` instead of `low + k`.
❌ Trying to binary-search the value directly instead of the index.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "kth missing number in a sorted/strictly-increasing array" → **binary search on index using `arr[i]-(i+1)`**.

---

## 🏆 Pattern Category

`Binary Search` · `Missing Count` · `Index Search`

---

## ⏱️ 30-Second Last-Minute Revision

> **`missing = arr[mid]-(mid+1)`.** Find first index with `missing >= k` (`low`). Answer = `low + k`. `O(log N)`.
