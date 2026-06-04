# 🔥 Largest Element in an Array

> **LeetCode #179** (variant) · **Difficulty:** Easy · **Step 3 — Arrays · P01**

---

## 🧠 Problem Understanding

Given an array of N integers, find the largest element.

**Input:** `arr = [3, 2, 1, 5, 6, 4]` → **Output:** `6`

**Key Observation:** Linear scan maintaining a running maximum suffices. Sorting is overkill.

---

## 🥉 Brute Force

Sort the array, return last element. **Time:** O(N log N) · **Space:** O(1)

---

## 🥇 Optimal — Linear Scan

### Algorithm
1. Initialize `maxVal = arr[0]`
2. For each `x` in array: `maxVal = max(maxVal, x)`
3. Return `maxVal`

### Dry Run
`arr = [3, 2, 1, 5, 6, 4]`

| i | arr[i] | maxVal |
|---|--------|--------|
| 0 | 3 | 3 |
| 1 | 2 | 3 |
| 2 | 1 | 3 |
| 3 | 5 | 5 |
| 4 | 6 | **6** |
| 5 | 4 | 6 |

**Output:** `6` ✅

### Complexity
- **Time:** O(N) · **Space:** O(1)

---

## 💻 Clean C++ Code

```cpp
/*
 * LARGEST ELEMENT: single linear scan tracking running max
 * Time O(N) | Space O(1)
 */
class Solution {
public:
    int largest(vector<int>& arr) {
        int maxVal = arr[0];
        for (int i = 1; i < arr.size(); i++)
            maxVal = max(maxVal, arr[i]);
        return maxVal;
    }
};
```

---

## 🧾 Recall Line
> "Initialize `maxVal = arr[0]`, update `maxVal = max(maxVal, arr[i])` each step."

## 📝 Short Revision Notes
- O(N) time, O(1) space — can't do better than O(N) (must inspect every element)
- Handle empty array edge case if required
- STL: `*max_element(arr.begin(), arr.end())`

## ⚠️ Common Mistakes
❌ Initializing `maxVal = 0` — fails for all-negative arrays  
❌ Sorting (unnecessary O(N log N))

## 🏆 Pattern Category
`Arrays` · `Linear Scan`

## ⏱️ 30-Second Revision
> Linear scan, `maxVal = arr[0]`, update each step. O(N)/O(1). STL: `*max_element`.
