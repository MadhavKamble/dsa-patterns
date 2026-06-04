# 🔥 Second Largest Element in an Array (Without Sorting)

> **GFG Classic** · **Difficulty:** Easy · **Step 3 — Arrays · P02**

---

## 🧠 Problem Understanding

Find the second largest **distinct** element in an array in a single pass, without sorting.

**Input:** `[12, 35, 1, 10, 34, 1]` → **Output:** `34`  
**Edge case:** `[10, 10, 10]` → No second largest (all same), return -1

**Key Observation:** Track both `largest` and `secondLargest` in one pass. Update carefully to avoid duplicates.

---

## 🥉 Brute Force
Sort descending, scan for first element smaller than arr[0]. **Time:** O(N log N)

---

## 🥈 Better — Two Pass
Pass 1: find largest. Pass 2: find largest element < largest. **Time:** O(N), **Space:** O(1)

---

## 🥇 Optimal — Single Pass

### Key Observation
> 💡 Maintain `largest` and `secondLargest`. When you find a new largest, the old largest becomes a candidate for second largest.

### Algorithm
1. `largest = secondLargest = INT_MIN`
2. For each `x`:
   - If `x > largest`: `secondLargest = largest`, `largest = x`
   - Else if `x > secondLargest` and `x != largest`: `secondLargest = x`
3. Return `secondLargest` (or -1 if still INT_MIN)

### Dry Run
`arr = [12, 35, 1, 10, 34, 1]`

| x | largest | secondLargest |
|---|---------|---------------|
| 12 | 12 | -∞ |
| 35 | 35 | 12 |
| 1 | 35 | 12 |
| 10 | 35 | 12 |
| 34 | 35 | **34** |
| 1 | 35 | 34 |

**Output:** `34` ✅

### Complexity
- **Time:** O(N) · **Space:** O(1)

---

## 💻 Clean C++ Code

```cpp
/*
 * SECOND LARGEST: single pass tracking top-2 distinct values
 * Key: when new largest found, old largest → secondLargest candidate
 * Time O(N) | Space O(1)
 */
class Solution {
public:
    int secondLargest(vector<int>& arr) {
        int largest = INT_MIN, second = INT_MIN;

        for (int x : arr) {
            if (x > largest) {
                second = largest;    // old largest becomes second candidate
                largest = x;
            } else if (x > second && x != largest) {
                second = x;          // new second largest (distinct from largest)
            }
        }

        return (second == INT_MIN) ? -1 : second;
    }
};
```

---

## 🧾 Recall Line
> "Track `largest` and `second`. New largest: `second=largest, largest=x`. New second: `x>second && x!=largest`."

## 📝 Short Revision Notes
- Must track **distinct** second largest — `x != largest` condition is critical
- Initialize both to `INT_MIN`, not 0
- Return -1 if all elements are equal (second stays INT_MIN)
- Extension: Kth largest → use min-heap of size K

## ⚠️ Common Mistakes
❌ Not checking `x != largest` → duplicates become second largest  
❌ Initializing to 0 → fails for negative arrays  
❌ Forgetting two separate conditions for updating largest vs second

## 🏆 Pattern Category
`Arrays` · `Linear Scan` · `Two Variables`

## ⏱️ 30-Second Revision
> Single pass: if `x > largest` → `second=largest, largest=x`. Else if `x > second && x != largest` → `second=x`. Return second or -1.
