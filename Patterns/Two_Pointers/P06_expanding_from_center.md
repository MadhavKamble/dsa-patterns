# Pattern 06: Expanding From Center

## Category
Two Pointers

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 5. Longest Palindromic Substring | Medium | https://leetcode.com/problems/longest-palindromic-substring/ |
| 2 | 647. Palindromic Substrings | Medium | https://leetcode.com/problems/palindromic-substrings/ |

---

## 1. First-Timer Explanation

### What is this pattern?
A palindrome reads the same from both ends. The key insight: every palindrome has a CENTER. If you fix the center and expand outward as long as characters match, you find the longest palindrome centered there.

There are two types of centers:
- **Odd-length**: single character center (e.g., "aba" → center at 'b')
- **Even-length**: two-character center (e.g., "abba" → center between 'b' and 'b')

Try each possible center, expand as far as possible, track the longest. Total: O(n) centers × O(n) expansion = O(n²), but O(1) space (vs Manacher's O(n) which is O(n) time but harder to code).

### Real-World Analogy
You have a row of paint cans. Two painters start from the same spot and walk outward in opposite directions, painting identical colors. As long as both paint the same color, the symmetrical segment is a palindrome. They stop when colors differ. You try starting from every possible spot.

### Visual Walkthrough
```
String: "racecar"
Indices:  0 1 2 3 4 5 6
Chars:    r a c e c a r

Center at index 3 (odd, 'e'):
  Expand: s[2]='c' == s[4]='c' ✓
  Expand: s[1]='a' == s[5]='a' ✓
  Expand: s[0]='r' == s[6]='r' ✓
  Expand: l=-1 out of bounds → STOP
  Palindrome: "racecar", length 7

Center at index 2 (odd, 'c'):
  Expand: s[1]='a' != s[3]='e' ✗ → STOP
  Just "c", length 1

Center between index 2 and 3 (even):
  s[2]='c' != s[3]='e' → STOP immediately, length 0
```

### When TO use this pattern
- Find longest palindromic substring
- Count total palindromic substrings
- Any problem requiring "expand from center" logic

### When NOT to use this pattern
- Palindrome check of entire string → use two converging pointers O(n)
- Need O(n) time → use Manacher's algorithm
- Palindrome partitioning → use DP

### Common Beginner Mistakes
- **Forgetting even-length centers**: only checking odd centers misses "abba" type palindromes
- **Off-by-one in length**: length = r - l - 1 (because we stop when s[l] != s[r])
- **Start position**: start = l + 1 (since l has already gone one past the palindrome boundary)
- **Counting**: for counting palindromes, add 1 for each successful expansion step

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | "longest palindromic substring", "count palindromic substrings" |
| Core Idea | For each center, expand outward while characters match |
| Trigger Keywords | "palindrome", "substring" (not subsequence!), "expand" |
| Avoid When | Palindrome subsequence (use DP), entire string check (converging pointers) |
| Time Complexity | O(n²) |
| Space Complexity | O(1) |

**Gotchas:**
- Always try BOTH odd (i,i) and even (i,i+1) centers for each index
- Result start = l+1, length = r-l-1 after while loop terminates
- "Palindromic substring" ≠ "Palindromic subsequence" — this pattern handles substrings

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"longest palindromic SUBSTRING"` → expanding from center (O(n²)) or Manacher (O(n))
- `"count palindromic substrings"` → same pattern, count per expansion step
- `"palindrome"` + constraints n ≤ 1000 → O(n²) is fine

### Constraint hints
- n ≤ 1000 → O(n²) expanding from center works
- n ≤ 10^5 → need Manacher's O(n) or careful DP
- "substring" not "subsequence" → expanding from center (not LCS-based DP)

---

## 4. C++ Template

```cpp
/*
 * Pattern: Expanding From Center
 * Use when: longest/count palindromic substrings
 * Time: O(n²) | Space: O(1)
 */

// Helper: expand from center (l, r) and return palindrome length
int expand(const string& s, int l, int r) {
    while (l >= 0 && r < (int)s.size() && s[l] == s[r]) {
        l--; r++;
    }
    // when loop exits: s[l] != s[r] or out of bounds
    // actual palindrome is s[l+1..r-1], length = r-l-1
    return r - l - 1;
}

string longestPalindrome(string s) {
    int start = 0, maxLen = 1;

    for (int i = 0; i < (int)s.size(); i++) {
        int odd  = expand(s, i, i);      // odd-length: single center
        int even = expand(s, i, i + 1); // even-length: double center

        int best = max(odd, even);
        if (best > maxLen) {
            maxLen = best;
            start = i - (best - 1) / 2;  // compute start from center
        }
    }
    return s.substr(start, maxLen);
}

int countPalindromes(string s) {
    int count = 0;

    auto countExpand = [&](int l, int r) {
        while (l >= 0 && r < (int)s.size() && s[l] == s[r]) {
            count++;  // each successful expansion = one more palindrome
            l--; r++;
        }
    };

    for (int i = 0; i < (int)s.size(); i++) {
        countExpand(i, i);      // odd
        countExpand(i, i + 1); // even
    }
    return count;
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"A palindrome is symmetric around a center. For each possible center in the string, I expand outward as long as characters match. There are 2n-1 possible centers — n single-char centers for odd palindromes and n-1 two-char centers for even palindromes. Each expansion takes O(n), giving O(n²) total, O(1) space. For O(n) there's Manacher's algorithm but the code is complex."

### Interview Flow Checklist
- [ ] Clarify: substring vs subsequence?
- [ ] Mention DP alternative (O(n²) time and space)
- [ ] Explain center expansion approach
- [ ] Note: BOTH odd and even centers
- [ ] Code expand helper, then use it
- [ ] Dry run

---

## 6. Problems

---

### Problem 1: 5. Longest Palindromic Substring
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/longest-palindromic-substring/
**Why this pattern fits:** Longest palindromic SUBSTRING → try all centers and expand

**Optimal C++ Solution:**
```cpp
// Longest Palindromic Substring
// Approach: expand from each center (odd + even)
// Time: O(n²) | Space: O(1)

string longestPalindrome(string s) {
    int n = s.size();
    int start = 0, maxLen = 1;

    auto expand = [&](int l, int r) {
        while (l >= 0 && r < n && s[l] == s[r]) { l--; r++; }
        // palindrome is s[l+1..r-1], length = r-l-1
        if (r - l - 1 > maxLen) {
            maxLen = r - l - 1;
            start = l + 1;
        }
    };

    for (int i = 0; i < n; i++) {
        expand(i, i);      // odd-length palindrome
        expand(i, i + 1); // even-length palindrome
    }
    return s.substr(start, maxLen);
}
```

**Complexity Analysis:**
- Time: O(n²) — n centers × n expansion
- Space: O(1)

**Edge Cases:**
- [ ] Single character → return it
- [ ] All same characters "aaaa" → whole string is palindrome
- [ ] No palindrome longer than 1 → return first character

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 647. Palindromic Substrings
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/palindromic-substrings/
**Why this pattern fits:** Count ALL palindromic substrings → each successful expansion step is +1 palindrome

**Optimal C++ Solution:**
```cpp
// Palindromic Substrings — count all
// Time: O(n²) | Space: O(1)

int countSubstrings(string s) {
    int count = 0;
    int n = s.size();

    auto expand = [&](int l, int r) {
        while (l >= 0 && r < n && s[l] == s[r]) {
            count++;  // each valid expansion is one palindrome
            l--; r++;
        }
    };

    for (int i = 0; i < n; i++) {
        expand(i, i);      // odd centers
        expand(i, i + 1); // even centers
    }
    return count;
}
```

**Complexity Analysis:**
- Time: O(n²)
- Space: O(1)

**Edge Cases:**
- [ ] Single character → count = 1
- [ ] All same characters "aaa" → 1+2+3 = 6 palindromes

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> Find the shortest palindrome you can create by adding characters to the FRONT of a string.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** KMP / Palindrome check (not center expansion directly)
**Reason:** This is LC 214. Find the longest palindromic prefix: reverse the string, concatenate with '#', apply KMP failure function to find the longest prefix that's also a suffix. Add the non-palindrome suffix (reversed) to the front.
</details>

---

**Drill 2:**
> Given a string, find all distinct palindromic substrings.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Expanding From Center + hash set
**Reason:** Expand from each center, add each found palindrome to a set. Return set size for count, or the set itself for distinct palindromes.
</details>

---

**Drill 3:**
> Given a number as a string, how many palindromic numbers can you form by rearranging its digits?

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Combinatorics, not expanding from center
**Reason:** A palindrome can be formed iff at most one digit has odd frequency. Count arrangements of half the string on one side, multiply by 2 (mirror), handle middle digit separately.
</details>

---

**Drill 4:**
> Find the minimum cuts needed to partition a string so that every partition is a palindrome.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** DP (Palindrome Partitioning II — LC 132)
**Reason:** Precompute isPalin[i][j] using center expansion, then use 1D DP: minCuts[i] = minimum cuts for s[0..i]. This combines center expansion (for palindrome check) with DP (for optimization).
</details>

---

**Drill 5:**
> Given a 2D grid of characters, find the largest square sub-grid that is a palindrome when read in any direction.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** 2D extension of center expansion (complex)
**Reason:** This is a non-standard problem. Would require checking palindrome property in all 4 directions from each cell, combined with a size-constraint binary search. Not a direct center-expansion problem.
</details>

---

## 8. Complexity Cheatsheet

| Variant | Time | Space | Why |
|---------|------|-------|-----|
| Longest palindrome (center expand) | O(n²) | O(1) | n centers × n expand |
| Count palindromes (center expand) | O(n²) | O(1) | n centers × n expand |
| Longest palindrome (Manacher) | O(n) | O(n) | Linear scan with memory |
| Longest palindrome (DP) | O(n²) | O(n²) | Fill 2D table |

---

## 9. Common Follow-up Questions

1. Can you do longest palindrome in O(n)? (Yes — Manacher's algorithm, but complex to implement in interviews)
2. What about longest palindromic SUBSEQUENCE? (Different problem — use LCS DP: LPS(s) = LCS(s, reverse(s)))
3. How many palindromes of length exactly k exist in a string? (DP or center expansion with length filter)
4. What if the string has Unicode? (Same algorithm, just use string indices correctly)

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| DP | Palindrome partition, count palindrome substrings | 132. Palindrome Partitioning II |
| KMP | Find shortest palindrome (add to front) | 214. Shortest Palindrome |
| Backtracking | Generate all palindrome partitions | 131. Palindrome Partitioning |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
