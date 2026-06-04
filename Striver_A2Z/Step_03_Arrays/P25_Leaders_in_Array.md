# 🔥 Leaders in an Array

> **GFG Classic** · **Difficulty:** Easy · **Step 3 — Arrays · P25**

---

## 🧠 Problem Understanding

An element is a **leader** if it is greater than all elements to its **right**. The rightmost element is always a leader.

**Input:** `[16, 17, 4, 3, 5, 2]` → **Output:** `[17, 5, 2]`

---

## 🥉 Brute Force
For each element, check all elements to its right. **Time:** O(N²)

---

## 🥇 Optimal — Scan from Right

### Key Observation
> 💡 Scan from right to left, tracking `maxRight` (max seen so far from right). If `arr[i] >= maxRight`, it's a leader. Update `maxRight`.

### Algorithm
1. `maxRight = arr[N-1]`, add to result
2. For `i` from N-2 down to 0:
   - If `arr[i] > maxRight`: it's a leader, add to result, `maxRight = arr[i]`
3. Reverse result (since we added right to left)

### Dry Run
`arr = [16, 17, 4, 3, 5, 2]`

| i | arr[i] | maxRight | Leader? |
|---|--------|----------|---------|
| 5 | 2 | 2 | ✅ (rightmost always) |
| 4 | 5 | 2 | ✅ 5>2, maxRight=5 |
| 3 | 3 | 5 | ❌ |
| 2 | 4 | 5 | ❌ |
| 1 | 17 | 5 | ✅ 17>5, maxRight=17 |
| 0 | 16 | 17 | ❌ |

**Result (reversed):** `[17, 5, 2]` ✅

### Complexity
- **Time:** O(N) · **Space:** O(1) extra (output not counted)

---

## 💻 Clean C++ Code

```cpp
/*
 * LEADERS IN ARRAY — scan right to left tracking running maximum
 * A leader is greater than ALL elements to its right
 * Time O(N) | Space O(1) extra
 */
class Solution {
public:
    vector<int> leaders(vector<int>& arr) {
        int n = arr.size();
        vector<int> result;
        int maxRight = arr[n - 1];
        result.push_back(maxRight);              // rightmost is always a leader

        for (int i = n - 2; i >= 0; i--) {
            if (arr[i] > maxRight) {
                maxRight = arr[i];
                result.push_back(arr[i]);
            }
        }

        reverse(result.begin(), result.end());   // restore left-to-right order
        return result;
    }
};
```

---

## 🧾 Recall Line
> "Scan right to left. Track `maxRight`. If `arr[i] > maxRight`, it's a leader, update maxRight."

## 📝 Short Revision Notes
- Rightmost element always a leader
- Right-to-left scan: O(N), single pass
- Leaders appear in decreasing order from right to left
- Reverse result at end to get left-to-right order
- If equal elements: `arr[i] >= maxRight` (depends on problem definition — usually strict `>`)

## ⚠️ Common Mistakes
❌ Scanning left to right and checking all right elements — O(N²)  
❌ Forgetting to reverse the result  
❌ `>=` vs `>` — must check exact problem definition

## 🏆 Pattern Category
`Arrays` · `Linear Scan` · `Right to Left`

## ⏱️ 30-Second Revision
> Scan right to left. `maxRight=arr[N-1]`. If `arr[i]>maxRight`: leader, update maxRight. Reverse result. O(N)/O(1).
