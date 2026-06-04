# 🔥 Linear Search

> **GFG Classic** · **Difficulty:** Easy · **Step 3 — Arrays · P08**

---

## 🧠 Problem Understanding

Given an array and a target, return the index of target in the array. Return -1 if not found.

**Input:** `arr = [2, 3, 4, 10, 40]`, `target = 10` → **Output:** `3`

**Key Observation:** For unsorted arrays, linear search is the only option — O(N). For sorted arrays, Binary Search gives O(log N).

---

## 🥇 Optimal — Linear Scan

```cpp
/*
 * LINEAR SEARCH: scan each element, return index on match
 * Time O(N) | Space O(1)
 * Use when: unsorted array, or small N
 */
class Solution {
public:
    int linearSearch(vector<int>& arr, int target) {
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] == target)
                return i;
        }
        return -1;
    }
};
```

**Dry Run:** `arr=[2,3,4,10,40]`, target=10

| i | arr[i] | Match? |
|---|--------|--------|
| 0 | 2 | ❌ |
| 1 | 3 | ❌ |
| 2 | 4 | ❌ |
| 3 | 10 | ✅ → return 3 |

**Complexity:** Time O(N) · Space O(1)

---

## 🧾 Recall Line
> "Scan left to right, return index on match, -1 if exhausted."

## 📝 Short Revision Notes
- Unsorted → Linear O(N); Sorted → Binary O(log N)
- Best case O(1) (target at index 0), Average O(N/2), Worst O(N)
- STL: `find(arr.begin(), arr.end(), target)` returns iterator

## ⚠️ Common Mistakes
❌ Using on sorted array when Binary Search was expected  
❌ Returning `false` instead of `-1` when not found

## 🏆 Pattern Category
`Arrays` · `Linear Scan` · `Search`

## ⏱️ 30-Second Revision
> Scan each element. Return index if match, -1 if not found. O(N)/O(1).
