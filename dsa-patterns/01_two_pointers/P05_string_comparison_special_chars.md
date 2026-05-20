# Pattern 05: String Comparison with Special Characters

## Category
Two Pointers

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 844. Backspace String Compare | Easy | https://leetcode.com/problems/backspace-string-compare/ |
| 2 | 1598. Crawler Log Folder | Easy | https://leetcode.com/problems/crawler-log-folder/ |
| 3 | 2390. Removing Stars From a String | Medium | https://leetcode.com/problems/removing-stars-from-a-string/ |

---

## 1. First-Timer Explanation

### What is this pattern?
Some string problems involve "special" characters that cancel, undo, or navigate previous characters (backspace '#', stars '*', '../' folder navigation). The naive approach builds a stack or new string — O(n) space. The optimized approach uses two pointers scanning from right to left, "lazily" skipping characters that would be canceled.

For backspace comparison: instead of processing both strings and comparing, scan both from the right. When you hit a backspace character, count how many real characters to skip forward.

### Real-World Analogy
You're reading a text message with typos corrected by "delete" key presses. Instead of replaying the entire editing session, you read the final message backward — every backspace tells you to skip the next valid character you'd have read.

### Visual Walkthrough
```
Compare "ab#c" and "ad#c" with right-to-left two-pointer:

"ab#c"  pointer starts at index 3 (c)
"ad#c"  pointer starts at index 3 (c)

Step 1: Both point to 'c' → match, both pointers go left
  i=2 (string1), j=2 (string2)

Step 2: string1[2]='#' → backspace! skip=1, i=1
  string1[1]='b' → skip it (skip-- = 0), i=0
  i=0: 'a' — valid character

  string2[2]='#' → backspace! skip=1, j=1
  string2[1]='d' → skip it (skip-- = 0), j=0
  j=0: 'a' — valid character

  Compare: 'a' == 'a' → match, continue

Step 3: both exhausted → strings are EQUAL
```

### When TO use this pattern
- Compare strings with backspace/delete characters
- Simplify path strings (../.. navigation)
- Remove characters that "cancel" adjacent characters (stars remove nearest non-star)

### When NOT to use this pattern
- Stack approach is cleaner and stack space is acceptable
- Complex multi-character cancellation rules (stack is clearer)
- Forward processing needed (building result from left to right)

### Common Beginner Mistakes
- **Right-to-left not left-to-right**: the cancellation goes backward (backspace removes what's BEFORE it)
- **Count skips properly**: each '#' adds 1 to skip count; each non-# decrements skip count if > 0
- **Don't stop early**: exhaust skip count before declaring a valid character
- **Crawler logs**: only pop when folder is non-root (depth > 0)

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | String with backspace/delete/cancel characters, O(1) space required |
| Core Idea | Scan right-to-left, track how many chars to skip due to cancellations |
| Trigger Keywords | "backspace", "#", "stars remove non-star", "folder navigation" |
| Avoid When | O(n) space is acceptable (stack is simpler and clearer) |
| Time Complexity | O(n) |
| Space Complexity | O(1) for two-pointer approach |

**Gotchas:**
- Right-to-left: backspace affects characters to the LEFT, so scan from right
- The skip counter tracks pending cancellations not yet consumed
- Two-string comparison: advance BOTH pointers independently (each has its own skip counter)

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"backspace character '#'"` → right-to-left two pointers
- `"stars remove the closest non-star"` → stack or right-to-left pointer
- `"../", "./"` in folder paths → stack-based path simplification

### Constraint hints
- O(1) space constraint → can't use stack → right-to-left pointers
- Two strings to compare with modifiers → parallel pointer approach

---

## 4. C++ Template

```cpp
/*
 * Pattern: String Comparison with Special Characters
 * Use when: strings with backspace/cancel chars, O(1) space
 * Time: O(n) | Space: O(1)
 */

// Find next valid character position scanning right-to-left
int nextValid(const string& s, int i) {
    int skip = 0;
    while (i >= 0) {
        if (s[i] == '#') { skip++; i--; }
        else if (skip > 0) { skip--; i--; }
        else break;  // found valid character
    }
    return i;  // -1 if exhausted
}

bool backspaceCompare(string s, string t) {
    int i = s.size() - 1, j = t.size() - 1;

    while (i >= 0 || j >= 0) {
        i = nextValid(s, i);
        j = nextValid(t, j);

        if (i < 0 && j < 0) return true;   // both exhausted: equal
        if (i < 0 || j < 0) return false;  // one exhausted: unequal
        if (s[i] != t[j]) return false;    // chars differ: unequal

        i--; j--;  // matched: move both left
    }
    return true;
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"The '#' represents backspace, which deletes the previous character. One approach is to build the final string using a stack — O(n) space.
For O(1) space: scan both strings from right to left simultaneously. Maintain a skip counter for each string: '#' increments skip; a normal character decrements skip if > 0 (meaning it's canceled), or it's a valid character for comparison.
Advance both pointers to their next valid characters and compare."

### Interview Flow Checklist
- [ ] Mention stack approach first (O(n) space)
- [ ] Explain O(1) optimization: right-to-left scan
- [ ] Code the `nextValid` helper
- [ ] Handle both-exhausted and one-exhausted cases
- [ ] Dry run on the given example

---

## 6. Problems

---

### Problem 1: 844. Backspace String Compare
**Difficulty:** Easy
**Leetcode:** https://leetcode.com/problems/backspace-string-compare/
**Why this pattern fits:** Compare two strings with '#' as backspace, O(1) space → right-to-left pointers

**Optimal C++ Solution:**
```cpp
// Backspace String Compare
// Time: O(n+m) | Space: O(1)

bool backspaceCompare(string s, string t) {
    int i = s.size() - 1, j = t.size() - 1;
    int skipS = 0, skipT = 0;

    while (i >= 0 || j >= 0) {
        // advance i to next valid char in s
        while (i >= 0) {
            if (s[i] == '#') { skipS++; i--; }
            else if (skipS > 0) { skipS--; i--; }
            else break;
        }
        // advance j to next valid char in t
        while (j >= 0) {
            if (t[j] == '#') { skipT++; j--; }
            else if (skipT > 0) { skipT--; j--; }
            else break;
        }

        if (i >= 0 && j >= 0 && s[i] != t[j]) return false;
        if ((i >= 0) != (j >= 0)) return false;  // one exhausted, other not

        i--; j--;
    }
    return true;
}
```

**Edge Cases:**
- [ ] String of only backspaces ("###") → results in empty string
- [ ] More backspaces than characters ("a#b#c#") → still valid
- [ ] One string empty after processing, other not

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 2390. Removing Stars From a String
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/removing-stars-from-a-string/
**Why this pattern fits:** Stars cancel the nearest non-star to the left → stack simulation

**Problem Summary:**
Given a string with '*' characters. Each '*' removes the nearest non-'*' character to its left. Return the resulting string.

**Approach Walkthrough:**
1. This is naturally a stack problem (forward direction)
2. When encountering a letter: push onto stack
3. When encountering '*': pop from stack (removes nearest non-star)
4. Build result from stack

**Optimal C++ Solution:**
```cpp
// Removing Stars From a String
// Time: O(n) | Space: O(n) for stack

string removeStars(string s) {
    string stk;  // use string as stack (faster than actual stack)

    for (char c : s) {
        if (c == '*') {
            stk.pop_back();  // remove nearest non-star
        } else {
            stk.push_back(c);
        }
    }
    return stk;
}
```

**Edge Cases:**
- [ ] No stars → return original
- [ ] Stars at the beginning (problem guarantees valid input)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 3: 1598. Crawler Log Folder
**Difficulty:** Easy
**Leetcode:** https://leetcode.com/problems/crawler-log-folder/
**Why this pattern fits:** Track depth as stack counter; "../" decrements, "./" stays, folder name increments

**Problem Summary:**
Given a list of folder navigation commands, find minimum operations to return to the main folder.

**Optimal C++ Solution:**
```cpp
// Crawler Log Folder
// Time: O(n * L) where L = avg log length | Space: O(1)

int minOperations(vector<string>& logs) {
    int depth = 0;

    for (const string& log : logs) {
        if (log == "../") {
            depth = max(0, depth - 1);  // go up (can't go above root)
        } else if (log == "./") {
            // stay in current folder: depth unchanged
        } else {
            depth++;  // go into subfolder
        }
    }
    return depth;  // depth = number of "../" needed to return to root
}
```

**Edge Cases:**
- [ ] Already at root and "../" command → depth stays 0
- [ ] No navigation commands → return 0

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> Given a string of '(' and ')' where some are marked as 'invalid', remove the minimum to make it valid. How do you find which ones to keep?

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Stack / Two-pointer scan
**Reason:** Forward scan with a count of unmatched '('. Then backward scan for unmatched ')'. The ones marked invalid are the excess. Related to LC 1249.
</details>

---

**Drill 2:**
> Two file paths are given as strings with possible ".." navigation. Are they pointing to the same file?

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Stack-based path simplification
**Reason:** Simplify both paths independently using a stack (push folder names, pop on ".."), then compare resulting stacks/strings. LC 71 (Simplify Path) covers the simplification part.
</details>

---

**Drill 3:**
> Given a string, every letter 'X' deletes the first occurrence of 'Y' to its left. Return the final string.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Stack (like star removal)
**Reason:** Maintain a stack. On 'X': if top of stack is 'Y', pop it (and don't push 'X'). Otherwise push 'X'. On other chars: push as normal. This handles the "nearest to the left" deletion.
</details>

---

**Drill 4:**
> Compare two typed text outputs where '^' represents deleting the previous word (not character). O(1) space.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Right-to-left two pointers (extended backspace compare)
**Reason:** Same as backspace compare but skip logic now needs to skip entire words when '^' is encountered. The right-to-left scan still works; just adjust what "skip" means.
</details>

---

**Drill 5:**
> A stream of directory commands is given. Return whether you'll ever be at depth ≥ K at any point during navigation.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Crawler Log Folder variant
**Reason:** Track depth with a counter (increment on folder entry, decrement on "../"). Track maximum depth reached. Simple O(n) scan.
</details>

---

## 8. Complexity Cheatsheet

| Variant | Time | Space | Why |
|---------|------|-------|-----|
| Backspace Compare (stack) | O(n+m) | O(n+m) | Build both processed strings |
| Backspace Compare (pointers) | O(n+m) | O(1) | Right-to-left scan |
| Removing Stars (stack) | O(n) | O(n) | Single pass with string-as-stack |
| Crawler Log | O(n·L) | O(1) | Single scan, depth counter |

---

## 9. Common Follow-up Questions

1. What if '#' can appear multiple times in a row? (Skip counter handles it naturally — each '#' adds 1 to skip)
2. What if the backspace could delete TWO characters? (Increment skip by 2 per backspace)
3. Can you solve backspace compare without the right-to-left trick? (Yes — build final strings using stacks, then compare. Simpler code, O(n) space)
4. What if the order of operations matters more? (Stack is cleaner for complex multi-step operations)

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| Stack | Natural forward-processing version | Remove Stars, Simplify Path |
| Valid Parentheses | When special chars are brackets | Min Remove to Make Valid |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
