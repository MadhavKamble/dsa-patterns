# 🔥 Maximum Consecutive Ones

> **LeetCode #485** · **Difficulty:** Easy · **Step 3 — Arrays · P11**

---

## 🧠 Problem Understanding

Given a binary array, find the maximum number of consecutive 1s.

**Input:** `[1,1,0,1,1,1]` → **Output:** `3`

---

## 🥇 Optimal — Single Pass Counter

### Algorithm
1. `maxCount = 0`, `count = 0`
2. For each `x`:
   - If `x == 1`: `count++`, update `maxCount = max(maxCount, count)`
   - Else: `count = 0`
3. Return `maxCount`

### Dry Run
`[1,1,0,1,1,1]`

| i | x | count | maxCount |
|---|---|-------|---------|
| 0 | 1 | 1 | 1 |
| 1 | 1 | 2 | 2 |
| 2 | 0 | 0 | 2 |
| 3 | 1 | 1 | 2 |
| 4 | 1 | 2 | 2 |
| 5 | 1 | 3 | **3** |

**Output:** `3` ✅

### Complexity
- **Time:** O(N) · **Space:** O(1)

---

## 💻 Clean C++ Code

```cpp
/*
 * MAXIMUM CONSECUTIVE ONES
 * Running count of 1s, reset to 0 on seeing 0
 * Time O(N) | Space O(1)
 */
class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int maxCount = 0, count = 0;
        for (int x : nums) {
            count = (x == 1) ? count + 1 : 0;
            maxCount = max(maxCount, count);
        }
        return maxCount;
    }
};
```

---

## 🧾 Recall Line
> "Running counter: `count++` on 1, reset on 0, track max."

## 📝 Short Revision Notes
- Simple counter reset pattern
- Extension: allow flipping K zeros (LC 1004 — sliding window)
- All zeros → returns 0 ✅ ; all ones → returns N ✅

## ⚠️ Common Mistakes
❌ Forgetting to update `maxCount` before resetting `count`  
❌ Only checking `maxCount` at end — won't catch streak ending at last element

## 🏆 Pattern Category
`Arrays` · `Linear Scan` · `Sliding Window (simple)`

## ⏱️ 30-Second Revision
> For each x: `count = x==1 ? count+1 : 0`. `maxCount = max(maxCount, count)`. O(N)/O(1).
