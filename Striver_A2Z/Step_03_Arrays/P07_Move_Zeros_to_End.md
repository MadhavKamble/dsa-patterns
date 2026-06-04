# 🔥 Move Zeros to End

> **LeetCode #283** · **Difficulty:** Easy · **Step 3 — Arrays · P07**

---

## 🧠 Problem Understanding

Move all 0s to the end of the array while maintaining the relative order of non-zero elements. Do it **in-place**.

**Input:** `[0,1,0,3,12]` → **Output:** `[1,3,12,0,0]`

**Key Observation:** Two pointers — write pointer for non-zeros, read pointer scanning forward. Same pattern as Remove Duplicates.

---

## 🥉 Brute Force
Collect non-zeros in temp array, fill remaining with zeros. **Time:** O(N) · **Space:** O(N)

---

## 🥇 Optimal — Two Pointers (Snowball)

### Key Observation
> 💡 Keep a write pointer `j` pointing to the next position to place a non-zero. Scan `i`. When `arr[i] != 0`, place at `arr[j]` and advance `j`. Fill remaining with 0.

### Algorithm
1. `j = 0` (next position for non-zero element)
2. For `i` from 0 to N-1:
   - If `arr[i] != 0`: `arr[j++] = arr[i]`
3. Fill `arr[j..N-1]` with 0

### Dry Run
`arr = [0, 1, 0, 3, 12]`

| i | arr[i] | Action | j | arr |
|---|--------|--------|---|-----|
| 0 | 0 | skip | 0 | [0,1,0,3,12] |
| 1 | 1 | write | 1 | [1,1,0,3,12] |
| 2 | 0 | skip | 1 | [1,1,0,3,12] |
| 3 | 3 | write | 2 | [1,3,0,3,12] |
| 4 | 12 | write | 3 | [1,3,12,3,12] |
Fill [3..4] with 0 → **[1,3,12,0,0]** ✅

### Complexity
- **Time:** O(N) · **Space:** O(1)

**Swap variant** (fewer writes, same complexity):
```cpp
// swap approach — maintains relative order too
int j = 0;
for (int i = 0; i < n; i++)
    if (arr[i] != 0) swap(arr[i], arr[j++]);
```

---

## 💻 Clean C++ Code

```cpp
/*
 * MOVE ZEROS TO END
 * Two pointers: j = write position for non-zeros
 * Scan i: when arr[i] != 0, swap with arr[j], advance j
 * Time O(N) | Space O(1)
 */
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int j = 0;                           // next write position for non-zero

        // move all non-zeros to front (maintains order)
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != 0)
                swap(nums[i], nums[j++]);    // swap keeps non-zeros in order
        }
        // zeros are now naturally at the end
    }
};
```

---

## 🧾 Recall Line
> "Write pointer `j=0`. Scan: if `arr[i]!=0`, swap(`arr[i]`,`arr[j++]`). Zeros fill end automatically."

## 📝 Short Revision Notes
- Two pointers: same pattern as LC #27 Remove Element, LC #26 Remove Duplicates
- Swap variant avoids second pass to fill zeros
- Relative order of non-zeros is preserved
- Extension: move all negative numbers to front (same pattern)

## ⚠️ Common Mistakes
❌ Using extra array (violates in-place requirement)  
❌ Not preserving order of non-zero elements

## 🏆 Pattern Category
`Arrays` · `Two Pointers` · `In-Place`

## ⏱️ 30-Second Revision
> `j=0`. For each i: if `nums[i]!=0`, `swap(nums[i], nums[j++])`. O(N)/O(1).
