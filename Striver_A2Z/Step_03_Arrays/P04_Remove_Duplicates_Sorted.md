# 🔥 Remove Duplicates from Sorted Array

> **LeetCode #26** · **Difficulty:** Easy · **Step 3 — Arrays · P04**

---

## 🧠 Problem Understanding

Given a **sorted** array, remove duplicates **in-place** so each element appears only once. Return the count of unique elements.

**Input:** `[0,0,1,1,1,2,2,3,3,4]` → **Output:** `5`, array = `[0,1,2,3,4,_,_,_,_,_]`

**Key Observation:** Since sorted, duplicates are adjacent. Two pointers: `i` writes uniques, `j` reads ahead.

---

## 🥉 Brute Force
Use a set to collect unique elements, copy back. **Time:** O(N log N) · **Space:** O(N)

---

## 🥇 Optimal — Two Pointers

### Key Observation
> 💡 Pointer `i` marks the last written unique position. Pointer `j` scans forward. When `arr[j] != arr[i]`, write `arr[j]` to `arr[i+1]`.

### Algorithm
1. If array empty, return 0
2. `i = 0` (write pointer — last unique position)
3. For `j` from 1 to N-1:
   - If `arr[j] != arr[i]`: `i++`, `arr[i] = arr[j]`
4. Return `i + 1`

### Dry Run
`arr = [0,0,1,1,1,2,2,3,3,4]`

| j | arr[j] | arr[i] | Different? | i | arr after write |
|---|--------|--------|------------|---|-----------------|
| 1 | 0 | 0 | ❌ | 0 | — |
| 2 | 1 | 0 | ✅ | 1 | `[0,1,...]` |
| 3 | 1 | 1 | ❌ | 1 | — |
| 4 | 1 | 1 | ❌ | 1 | — |
| 5 | 2 | 1 | ✅ | 2 | `[0,1,2,...]` |
| 6 | 2 | 2 | ❌ | 2 | — |
| 7 | 3 | 2 | ✅ | 3 | `[0,1,2,3,...]` |
| 8 | 3 | 3 | ❌ | 3 | — |
| 9 | 4 | 3 | ✅ | 4 | `[0,1,2,3,4,...]` |

**Return:** `i+1 = 5` ✅

### Complexity
- **Time:** O(N) · **Space:** O(1)

---

## 💻 Clean C++ Code

```cpp
/*
 * REMOVE DUPLICATES FROM SORTED ARRAY
 * Two pointers: i = write position, j = read position
 * When arr[j] != arr[i], copy arr[j] to arr[++i]
 * Time O(N) | Space O(1)
 */
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) return 0;

        int i = 0;                          // write pointer (last unique index)

        for (int j = 1; j < nums.size(); j++) {
            if (nums[j] != nums[i]) {       // found a new unique element
                i++;
                nums[i] = nums[j];          // write it to next position
            }
        }

        return i + 1;                       // count of unique elements
    }
};
```

---

## 🎤 Interview Explanation Script
> "Since the array is sorted, duplicates are adjacent. I use two pointers: `i` as the write position and `j` scanning forward. Whenever `arr[j]` differs from `arr[i]`, I've found a new unique — I advance `i` and copy `arr[j]` there. This runs in O(N) time and O(1) space."

---

## 🧾 Recall Line
> "`i=0` write pointer. For `j` from 1: if `arr[j]!=arr[i]`, write to `arr[++i]`. Return `i+1`."

## 📝 Short Revision Notes
- Works only on **sorted** array (duplicates adjacent)
- For unsorted array: use `unordered_set` O(N) space
- Extension: allow at most K duplicates (LC 80) → check `arr[j] != arr[i-k+1]`
- `i` starts at 0 (first element is always unique)
- Return value is `i + 1` (count), not `i`

## ⚠️ Common Mistakes
❌ Starting `j` at 0 — comparing element with itself  
❌ Returning `i` instead of `i+1`  
❌ Applying this to unsorted array — must sort first or use set  

## 🔥 What Interviewer Is Testing
- Two-pointer in-place modification pattern
- Understanding why sorted order is necessary

## 🚀 Related Problems
- [ ] LeetCode #26 — Remove Duplicates from Sorted Array
- [ ] LeetCode #80 — Remove Duplicates II (allow at most 2)
- [ ] LeetCode #27 — Remove Element

## 🏆 Pattern Category
`Arrays` · `Two Pointers` · `In-Place`

## ⏱️ 30-Second Revision
> `i=0`. Scan `j=1` to end. If `arr[j]!=arr[i]`: `arr[++i]=arr[j]`. Return `i+1`. O(N)/O(1). Needs sorted input.
