# Pattern 04: In-place Array Modification

## Category
Two Pointers

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 26. Remove Duplicates from Sorted Array | Easy | https://leetcode.com/problems/remove-duplicates-from-sorted-array/ |
| 2 | 27. Remove Element | Easy | https://leetcode.com/problems/remove-element/ |
| 3 | 75. Sort Colors | Medium | https://leetcode.com/problems/sort-colors/ |
| 4 | 80. Remove Duplicates from Sorted Array II | Medium | https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/ |
| 5 | 283. Move Zeroes | Easy | https://leetcode.com/problems/move-zeroes/ |
| 6 | 443. String Compression | Medium | https://leetcode.com/problems/string-compression/ |
| 7 | 905. Sort Array By Parity | Easy | https://leetcode.com/problems/sort-array-by-parity/ |
| 8 | 2337. Move Pieces to Obtain a String | Medium | https://leetcode.com/problems/move-pieces-to-obtain-a-string/ |
| 9 | 2938. Separate Black and White Balls | Medium | https://leetcode.com/problems/separate-black-and-white-balls/ |

---

## 1. First-Timer Explanation

### What is this pattern?
You have an array and need to modify it in-place — no extra array — while maintaining some property (remove duplicates, filter values, partition by condition). The key is using two pointers:
- **Read pointer**: scans every element
- **Write pointer**: tracks the next valid position to write

When the read pointer finds an element that should stay, copy it to the write pointer's position and advance the write pointer. Elements behind the write pointer are "accepted"; elements between write and read are "overwritten/discarded."

### Real-World Analogy
You're watching a video and picking only the interesting frames to keep. One person (read) watches every frame, another (write) decides whether to keep it. If interesting, write copies it to the "keep" pile and advances. If not, read moves on but write doesn't. No extra storage — you're editing in-place.

### Visual Walkthrough
```
Remove duplicates from [1, 1, 2, 2, 3]:
  write=0  read=0  → always keep first element
  
  write=1  read=1  nums[1]=1 == nums[0]=1 → skip (don't write)
  write=1  read=2  nums[2]=2 != nums[0]=1 → write! nums[1]=2, write=2
  write=2  read=3  nums[3]=2 == nums[1]=2 → skip
  write=2  read=4  nums[4]=3 != nums[1]=2 → write! nums[2]=3, write=3

  Result (first 3 elements): [1, 2, 3], return 3
```

### When TO use this pattern
- Filter or compact an array in-place
- Remove specific values (duplicates, a target value, zeros)
- Partition array into two groups (evens first, zeros last)
- In-place string/array compression

### When NOT to use this pattern
- Need to preserve the original array
- Array is not the bottleneck (simple conditions → can use erase/remove)
- Problem needs stable relative ordering of BOTH groups (two-pointer partitioning may violate this for the "excluded" group)

### Common Beginner Mistakes
- **Comparing write-1 not read-1**: compare new element against `nums[write-1]` (last accepted), not `nums[read-1]`
- **Not handling empty array**: check size > 0 before accessing index 0
- **Sort Colors (DNF)**: don't advance `mid` after swapping with `hi` — the swapped element needs examination
- **Move Zeroes**: maintain relative order of non-zeros, then fill rest with zeros

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | In-place modification, filter/compact array, no extra space |
| Core Idea | Read pointer scans all; write pointer advances only on valid elements |
| Trigger Keywords | "in-place", "remove duplicates", "move zeros", "sort colors" |
| Avoid When | Original order of all elements must be preserved |
| Time Complexity | O(n) |
| Space Complexity | O(1) |

**Gotchas:**
- Write pointer starts at 1 (first element always kept) for duplicate problems
- Compare against `nums[write-1]` not `nums[read-1]`
- Dutch National Flag (sort colors): 3 pointers — lo, mid, hi

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"in-place"` + `"remove"` → read/write pointer pattern
- `"do not allocate extra space"` → no extra array
- `"sort colors"`, `"0s, 1s, 2s"` → Dutch National Flag 3-way partition
- `"move zeros to end"` → compact non-zeros to front, fill back with 0

### Constraint hints
- O(1) extra space constraint → must modify in-place
- Sorted array + remove duplicates → comparison against last written element

---

## 4. C++ Template

```cpp
/*
 * Pattern: In-place Array Modification (Read/Write Pointers)
 * Use when: filter/compact/partition array in-place
 * Time: O(n) | Space: O(1)
 */

// REMOVE DUPLICATES (sorted array)
int removeDuplicates(vector<int>& nums) {
    if (nums.empty()) return 0;
    int write = 1;  // first element always kept

    for (int read = 1; read < (int)nums.size(); read++) {
        if (nums[read] != nums[write - 1]) {  // compare with LAST WRITTEN
            nums[write++] = nums[read];
        }
    }
    return write;
}

// MOVE ZEROES (maintain order of non-zeros)
void moveZeroes(vector<int>& nums) {
    int write = 0;
    for (int read = 0; read < (int)nums.size(); read++) {
        if (nums[read] != 0) nums[write++] = nums[read];
    }
    while (write < (int)nums.size()) nums[write++] = 0;
}

// SORT COLORS — Dutch National Flag
void sortColors(vector<int>& nums) {
    int lo = 0, mid = 0, hi = nums.size() - 1;
    while (mid <= hi) {
        if      (nums[mid] == 0) { swap(nums[lo++], nums[mid++]); }
        else if (nums[mid] == 1) { mid++; }
        else                     { swap(nums[mid], nums[hi--]); }
        // DON'T advance mid after swap with hi
    }
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"The problem asks me to modify the array in-place without extra space.
The key insight is using two pointers: one reads every element, another writes only valid elements.
Elements before write are the valid result; elements at and after write will be overwritten.
This gives O(n) time and O(1) space."

### Interview Flow Checklist
- [ ] Confirm: "can I modify the array in-place?"
- [ ] Define what "valid" means for this problem
- [ ] Initialize write pointer
- [ ] Code the read loop with conditional write
- [ ] Handle post-loop cleanup (fill zeros, etc.)
- [ ] Return write pointer as new length

---

## 6. Problems

---

### Problem 1: 26. Remove Duplicates from Sorted Array
**Difficulty:** Easy
**Leetcode:** https://leetcode.com/problems/remove-duplicates-from-sorted-array/
**Why this pattern fits:** Sorted array → duplicates are adjacent → read/write pointers with last-written comparison

**Optimal C++ Solution:**
```cpp
// Remove Duplicates from Sorted Array
// Time: O(n) | Space: O(1)

int removeDuplicates(vector<int>& nums) {
    if (nums.empty()) return 0;
    int write = 1;

    for (int read = 1; read < (int)nums.size(); read++) {
        if (nums[read] != nums[write - 1]) {
            nums[write++] = nums[read];
        }
    }
    return write;
}
```

**Edge Cases:**
- [ ] Empty array
- [ ] All duplicates [1,1,1,1]
- [ ] No duplicates [1,2,3,4]

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 283. Move Zeroes
**Difficulty:** Easy
**Leetcode:** https://leetcode.com/problems/move-zeroes/
**Why this pattern fits:** Compact non-zeros to front (read/write), then fill rest with zeros

**Optimal C++ Solution:**
```cpp
// Move Zeroes
// Time: O(n) | Space: O(1)

void moveZeroes(vector<int>& nums) {
    int write = 0;

    // Phase 1: move all non-zeros to front
    for (int read = 0; read < (int)nums.size(); read++) {
        if (nums[read] != 0) nums[write++] = nums[read];
    }
    // Phase 2: fill remaining positions with 0
    while (write < (int)nums.size()) nums[write++] = 0;
}
```

**Edge Cases:**
- [ ] All zeros
- [ ] No zeros
- [ ] Single element

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 3: 75. Sort Colors (Dutch National Flag)
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/sort-colors/
**Why this pattern fits:** 3-way partition in one pass — Dutch National Flag algorithm

**Optimal C++ Solution:**
```cpp
// Sort Colors — Dutch National Flag
// Time: O(n) | Space: O(1)

void sortColors(vector<int>& nums) {
    int lo = 0, mid = 0, hi = nums.size() - 1;

    while (mid <= hi) {
        if (nums[mid] == 0) {
            swap(nums[lo++], nums[mid++]);  // 0: send to front
        } else if (nums[mid] == 1) {
            mid++;                           // 1: in place
        } else {
            swap(nums[mid], nums[hi--]);    // 2: send to back
            // don't increment mid: swapped element needs checking
        }
    }
}
```

**Edge Cases:**
- [ ] All same color
- [ ] Already sorted
- [ ] Only two colors

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 4: 80. Remove Duplicates from Sorted Array II
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/
**Why this pattern fits:** Same as P26 but allow at most 2 copies — compare against nums[write-2]

**Optimal C++ Solution:**
```cpp
// Remove Duplicates II (allow up to 2 copies)
// Time: O(n) | Space: O(1)

int removeDuplicates(vector<int>& nums) {
    if (nums.size() <= 2) return nums.size();
    int write = 2;  // first two elements always kept

    for (int read = 2; read < (int)nums.size(); read++) {
        // allow if different from what was written 2 positions ago
        if (nums[read] != nums[write - 2]) {
            nums[write++] = nums[read];
        }
    }
    return write;
}
```

**Edge Cases:**
- [ ] Array of length 1 or 2 (return as-is)
- [ ] All same element [1,1,1,1] → [1,1], return 2

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> Given a sorted array, remove all elements equal to a target value in-place. Return new length.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** In-place Array Modification — Read/Write Pointers
**Reason:** Read pointer scans all; write only advances when nums[read] != target. Same as "Remove Element" (LC 27).
</details>

---

**Drill 2:**
> Given an array, move all even numbers to the front and all odd numbers to the back, maintaining relative order of each group.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** In-place Array Modification (Read/Write Pointers)
**Reason:** Two-pass approach: first pass writes evens (read/write), then fill rest with odds. For stable partition maintaining relative order of BOTH groups, two-pass is needed; simple swap would lose odd order.
</details>

---

**Drill 3:**
> Compress a string: "aaabbc" → "a3b2c1". Do it in-place on a character array.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** In-place Array Modification
**Reason:** Use read/write pointers. Read groups consecutive same characters, write the character and count (as digits if count > 1) to the write position. LC 443.
</details>

---

**Drill 4:**
> Given a sorted array of 0s and 1s, move all 0s to front without extra space.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** In-place — Read/Write or Dutch National Flag (2-way)
**Reason:** Simple 2-way partition. Write pointer writes 0s as they're found; then fill rest with 1s. Or converging: lo at start (next 0 position), hi at end (next 1 position), swap until they cross.
</details>

---

**Drill 5:**
> In a sorted array, keep only elements that appear at most k times. Do it in-place.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** In-place Array Modification
**Reason:** Generalization of "Remove Duplicates II". Compare nums[read] with nums[write-k]: if different, write it. Works for any k. For k=1: write-1 comparison. For k=2: write-2 comparison. For k=∞: always write (no removal).
</details>

---

## 8. Complexity Cheatsheet

| Variant | Time | Space | Why |
|---------|------|-------|-----|
| Remove duplicates I/II | O(n) | O(1) | Single read pass |
| Remove element | O(n) | O(1) | Single read pass |
| Move zeroes | O(n) | O(1) | Two-phase single scan |
| Sort Colors (DNF) | O(n) | O(1) | Three-pointer single pass |
| Sort Array By Parity | O(n) | O(1) | Two-pointer partition |

---

## 9. Common Follow-up Questions

1. What if the array is unsorted but you still need to remove duplicates? (Use hash set — O(n) space, O(n) time)
2. Can Sort Colors be done with two passes instead of one? (Yes: first pass count each color; second pass fill. But Dutch National Flag is better — one pass)
3. What if there are k distinct values to partition into? (k-1 pivots needed; generalization of Dutch National Flag)
4. "Remove duplicates" — what happens to elements after the returned length? (Don't matter — problem only evaluates first `write` elements)

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| Sorting | When array is unsorted and we need sorted behavior first | Sort before removing duplicates |
| Sliding Window | When we need to track "at most K duplicates" in a window | Contains Duplicate II |
| Cyclic Sort | When array is [1..n] and we want to find missing/duplicates | Find All Duplicates in Array |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
