# 🔥 Check if the Array is Sorted

> **LeetCode #1752** (variant) · **Difficulty:** Easy · **Step 3 — Arrays · P03**

---

## 🧠 Problem Understanding

Given an array, check if it is sorted in **non-decreasing order** (ascending, allowing duplicates).

**Input:** `[1, 2, 3, 4, 5]` → `true` | `[1, 3, 2, 4]` → `false`

---

## 🥇 Optimal — Single Pass

### Algorithm
For each adjacent pair `(arr[i], arr[i+1])`, if `arr[i] > arr[i+1]` → not sorted. Return false.

### Dry Run
`arr = [1, 3, 2, 4]`

| i | arr[i] | arr[i+1] | arr[i] > arr[i+1]? |
|---|--------|----------|---------------------|
| 0 | 1 | 3 | ❌ |
| 1 | 3 | 2 | ✅ → return **false** |

### Complexity
- **Time:** O(N) · **Space:** O(1)

---

## 💻 Clean C++ Code

```cpp
/*
 * CHECK SORTED: verify each adjacent pair is non-decreasing
 * Time O(N) | Space O(1)
 */
class Solution {
public:
    bool isSorted(vector<int>& arr) {
        for (int i = 0; i < (int)arr.size() - 1; i++) {
            if (arr[i] > arr[i + 1])
                return false;        // violation found
        }
        return true;
    }
};
```

---

## 🧾 Recall Line
> "Check adjacent pairs: if any `arr[i] > arr[i+1]`, return false."

## 📝 Short Revision Notes
- Check adjacent pairs — O(N), can't do better (must verify every pair)
- Non-decreasing: allows `arr[i] == arr[i+1]` (use strict `>`)
- Strictly increasing: use `>=`
- Edge: single element or empty → always sorted
- Used as subroutine in: Insertion Sort, Nearly-sorted detection

## ⚠️ Common Mistakes
❌ `arr[i] >= arr[i+1]` for non-decreasing check — too strict, fails on `[1,1,2]`  
❌ Loop to `N` instead of `N-1` — out-of-bounds on `arr[i+1]`

## 🏆 Pattern Category
`Arrays` · `Linear Scan`

## ⏱️ 30-Second Revision
> Loop `i` to `N-2`: if `arr[i] > arr[i+1]` return false. Else return true. O(N)/O(1).
