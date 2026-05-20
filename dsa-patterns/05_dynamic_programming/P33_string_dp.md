# Pattern 33: String DP (Palindrome, Subsequence, Matching)

## Category
Dynamic Programming

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 5. Longest Palindromic Substring | Medium | https://leetcode.com/problems/longest-palindromic-substring/ |
| 2 | 10. Regular Expression Matching | Hard | https://leetcode.com/problems/regular-expression-matching/ |
| 3 | 44. Wildcard Matching | Hard | https://leetcode.com/problems/wildcard-matching/ |
| 4 | 115. Distinct Subsequences | Hard | https://leetcode.com/problems/distinct-subsequences/ |
| 5 | 139. Word Break | Medium | https://leetcode.com/problems/word-break/ |
| 6 | 140. Word Break II | Hard | https://leetcode.com/problems/word-break-ii/ |
| 7 | 516. Longest Palindromic Subsequence | Medium | https://leetcode.com/problems/longest-palindromic-subsequence/ |
| 8 | 647. Palindromic Substrings | Medium | https://leetcode.com/problems/palindromic-substrings/ |

---

## 1. First-Timer Explanation

### What is this pattern?
String DP problems apply dynamic programming where the state represents positions within one or two strings. Common categories:

**Palindrome DP:**
- Expand from center (P06 pattern) for substrings
- `dp[l][r]` = true if s[l..r] is a palindrome
- Or: `dp[l][r]` = longest palindromic subsequence in s[l..r]

**Pattern Matching:**
- `dp[i][j]` = true if first i chars of text match first j chars of pattern
- `'?'` matches any single character
- `'*'` matches any sequence (including empty)
- `'.'` in regex matches any single char
- `'*'` in regex means "zero or more of the preceding element"

**Subsequence Counting:**
- `dp[i][j]` = count of ways s[0..i-1] contains t[0..j-1] as subsequence
- Match: `dp[i][j] = dp[i-1][j-1] + dp[i-1][j]` (use or skip s[i-1])
- No match: `dp[i][j] = dp[i-1][j]` (skip s[i-1])

**Word Break:**
- `dp[i]` = can we segment s[0..i-1] using dictionary?
- Check all splits: `dp[i] = OR(dp[j] && s[j..i-1] in dict)`

### Visual Walkthrough
```
Word Break: s="leetcode", dict=["leet","code"]
dp[0] = true (empty string)
dp[4]: check splits j=0: s[0..3]="leet" in dict → dp[4] = dp[0] && true = true
dp[8]: check j=4: s[4..7]="code" in dict → dp[8] = dp[4] && true = true ✓

Wildcard Matching: s="adceb", p="*a*b"
dp[i][j] = does s[0..i-1] match p[0..j-1]?
'*' matches zero chars: dp[i][j] = dp[i][j-1]  (skip the *)
'*' matches one more: dp[i][j] = dp[i-1][j]    (consume s[i-1])
Match or '?': dp[i][j] = dp[i-1][j-1]
```

### When TO use this pattern
- String pattern matching with wildcards/regex
- Count/find palindromes (substrings or subsequences)
- Check if string can be segmented using a dictionary
- Count distinct subsequences of one string in another
- Longest palindromic subsequence

### When NOT to use this pattern
- Simple substring search → KMP or two-pointer
- Exact string matching → direct comparison
- No repeated subproblems → just iterate

### Common Beginner Mistakes
- **Regex `*` ≠ Wildcard `*`**: regex `*` means "zero or more of preceding"; wildcard `*` matches any sequence
- **Word Break**: check ALL possible splits j, not just last word
- **Distinct Subsequences**: when s[i]==t[j], both using and skipping s[i] count
- **Palindromic Substrings**: O(n²) expand-from-center is often simpler than 2D DP

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | "word break", "regex matching", "palindrome", "distinct subsequences" |
| Core Idea | dp on string positions; handle special chars (*/?) carefully |
| Trigger Keywords | "word break", "segmentation", "match pattern", "palindrome", "subsequence count" |
| Avoid When | Simple matching (no wildcards), no overlapping subproblems |
| Time Complexity | O(n²) to O(m×n) |
| Space Complexity | O(n) to O(m×n) |

**Gotchas:**
- Regex `*`: dp[i][j] = dp[i][j-2] (zero of prev) OR (match prev) dp[i-1][j]
- Wildcard `*`: dp[i][j] = dp[i][j-1] OR dp[i-1][j]
- Distinct subsequences: on match, BOTH use-it and skip-it count
- Word Break: trie or hash set for O(L) membership check; O(n²) total

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"word break"` / `"segment string using dictionary"` → Word Break DP
- `"regular expression"` with `.` and `*` → Regex Matching DP
- `"wildcard"` with `?` and `*` → Wildcard Matching DP
- `"count distinct subsequences"` → 2D count DP
- `"longest palindromic subsequence"` → interval DP or LCS trick
- `"palindromic substrings"` → expand from center or 2D boolean DP

---

## 4. C++ Template

```cpp
/*
 * Pattern: String DP
 * Time: O(n^2) to O(m*n) | Space: O(n) to O(m*n)
 */

// WORD BREAK
bool wordBreak(string s, vector<string>& wordDict) {
    unordered_set<string> dict(wordDict.begin(), wordDict.end());
    int n = s.size();
    vector<bool> dp(n+1, false);
    dp[0] = true;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < i; j++)
            if (dp[j] && dict.count(s.substr(j, i-j))) { dp[i] = true; break; }
    return dp[n];
}

// WILDCARD MATCHING (? = any char, * = any sequence)
bool isMatch_wildcard(string s, string p) {
    int m = s.size(), n = p.size();
    vector<vector<bool>> dp(m+1, vector<bool>(n+1, false));
    dp[0][0] = true;
    for (int j = 1; j <= n; j++) dp[0][j] = dp[0][j-1] && p[j-1]=='*';
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++) {
            if (p[j-1] == '*')
                dp[i][j] = dp[i][j-1] || dp[i-1][j];  // * matches empty or one more
            else
                dp[i][j] = dp[i-1][j-1] && (p[j-1]=='?' || s[i-1]==p[j-1]);
        }
    return dp[m][n];
}

// DISTINCT SUBSEQUENCES: count ways s contains t as subsequence
int numDistinct(string s, string t) {
    int m = s.size(), n = t.size();
    vector<vector<long long>> dp(m+1, vector<long long>(n+1, 0));
    for (int i = 0; i <= m; i++) dp[i][0] = 1;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++) {
            dp[i][j] = dp[i-1][j];  // skip s[i-1]
            if (s[i-1] == t[j-1]) dp[i][j] += dp[i-1][j-1];  // use s[i-1]
        }
    return dp[m][n];
}

// LONGEST PALINDROMIC SUBSEQUENCE
int longestPalindromeSubseq(string s) {
    // LCS(s, reverse(s))
    string rev = s; reverse(rev.begin(), rev.end());
    int n = s.size();
    vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            if (s[i-1] == rev[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
            else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    return dp[n][n];
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"For Word Break, I'll define dp[i] as 'can the first i characters of s be segmented using the dictionary.' For each position i, I try all possible last words by checking substrings s[j..i-1] in the dictionary. If dp[j] is true and s[j..i-1] is in the dictionary, then dp[i] is true."

"For Wildcard Matching, dp[i][j] means 'do the first i chars of s match the first j chars of pattern.' The tricky case is `*`: it can match zero characters (dp[i][j-1]) or extend a match to one more character from s (dp[i-1][j])."

### Interview Flow Checklist
- [ ] Define dp state clearly (positions in each string)
- [ ] Set base cases (empty string matches)
- [ ] Handle special characters carefully (*, ?, .)
- [ ] Fill table and return answer at dp[m][n]
- [ ] Consider space optimization if asked

---

## 6. Problems

---

### Problem 1: 139. Word Break
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/word-break/
**Optimal C++ Solution:**
```cpp
bool wordBreak(string s, vector<string>& wordDict) {
    unordered_set<string> dict(wordDict.begin(), wordDict.end());
    int n = s.size();
    vector<bool> dp(n+1, false);
    dp[0] = true;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < i && !dp[i]; j++)
            if (dp[j] && dict.count(s.substr(j, i-j))) dp[i] = true;
    return dp[n];
}
```
**Edge Cases:** [ ] Empty string (true), [ ] Word not in dict, [ ] Single character word

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 44. Wildcard Matching
**Difficulty:** Hard
**Leetcode:** https://leetcode.com/problems/wildcard-matching/
**Optimal C++ Solution:**
```cpp
bool isMatch(string s, string p) {
    int m = s.size(), n = p.size();
    vector<vector<bool>> dp(m+1, vector<bool>(n+1, false));
    dp[0][0] = true;
    for (int j = 1; j <= n; j++) dp[0][j] = dp[0][j-1] && p[j-1]=='*';
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++) {
            if (p[j-1] == '*')  dp[i][j] = dp[i][j-1] || dp[i-1][j];
            else dp[i][j] = dp[i-1][j-1] && (p[j-1]=='?' || s[i-1]==p[j-1]);
        }
    return dp[m][n];
}
```
**Edge Cases:** [ ] Pattern is just "*" (matches everything), [ ] Empty string with empty pattern

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 3: 10. Regular Expression Matching
**Difficulty:** Hard
**Leetcode:** https://leetcode.com/problems/regular-expression-matching/
**Why this pattern fits:** Regex `*` means zero-or-more of preceding char — different from wildcard

**Optimal C++ Solution:**
```cpp
bool isMatch(string s, string p) {
    int m = s.size(), n = p.size();
    vector<vector<bool>> dp(m+1, vector<bool>(n+1, false));
    dp[0][0] = true;
    // patterns like "a*b*" can match empty string
    for (int j = 2; j <= n; j++) dp[0][j] = dp[0][j-2] && p[j-1]=='*';
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++) {
            if (p[j-1] == '*') {
                dp[i][j] = dp[i][j-2];  // zero occurrences of p[j-2]
                if (p[j-2]=='.' || p[j-2]==s[i-1])
                    dp[i][j] = dp[i][j] || dp[i-1][j];  // one more occurrence
            } else if (p[j-1]=='.' || p[j-1]==s[i-1]) {
                dp[i][j] = dp[i-1][j-1];
            }
        }
    return dp[m][n];
}
```
**Edge Cases:** [ ] Pattern ".*" matches everything, [ ] "a*" matches zero or more a's

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 4: 115. Distinct Subsequences
**Difficulty:** Hard
**Leetcode:** https://leetcode.com/problems/distinct-subsequences/
**Optimal C++ Solution:**
```cpp
int numDistinct(string s, string t) {
    int m = s.size(), n = t.size();
    vector<vector<long long>> dp(m+1, vector<long long>(n+1, 0));
    for (int i = 0; i <= m; i++) dp[i][0] = 1;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++) {
            dp[i][j] = dp[i-1][j];
            if (s[i-1] == t[j-1]) dp[i][j] += dp[i-1][j-1];
        }
    return (int)dp[m][n];
}
```
**Edge Cases:** [ ] t longer than s (return 0), [ ] t empty (return 1)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 5: 516. Longest Palindromic Subsequence
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/longest-palindromic-subsequence/
**Optimal C++ Solution:**
```cpp
int longestPalindromeSubseq(string s) {
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) dp[i][i] = 1;
    for (int len = 2; len <= n; len++) {
        for (int l = 0; l + len - 1 < n; l++) {
            int r = l + len - 1;
            if (s[l] == s[r]) dp[l][r] = dp[l+1][r-1] + 2;
            else dp[l][r] = max(dp[l+1][r], dp[l][r-1]);
        }
    }
    return dp[0][n-1];
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 6: 647. Palindromic Substrings
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/palindromic-substrings/
**Why this pattern fits:** Count all palindromic substrings — expand from center or 2D DP

**Optimal C++ Solution:**
```cpp
int countSubstrings(string s) {
    int n = s.size(), count = 0;
    for (int center = 0; center < 2*n-1; center++) {
        int l = center / 2, r = l + center % 2;
        while (l >= 0 && r < n && s[l] == s[r]) {
            count++; l--; r++;
        }
    }
    return count;
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> Given a string, find the minimum number of cuts to partition it into palindromic substrings.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** DP with palindrome precomputation
**Reason:** Precompute isPalin[l][r] with expand-from-center. Then dp[i] = min cuts for s[0..i]. dp[i] = min(dp[j-1] + 1) for all j where s[j..i] is palindrome. Or: dp[i] = 0 if s[0..i] is palindrome. O(n²) total. LC 132.
</details>

---

**Drill 2:**
> Check if a string can be split into exactly two palindromes.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Palindrome check + iteration
**Reason:** Precompute isPalin[l][r] (expand from center or 2D DP). Then iterate split point i: check isPalin[0][i] && isPalin[i+1][n-1]. O(n²) precompute, O(n) split check. Simple application of palindrome DP building block.
</details>

---

**Drill 3:**
> You have a pattern string with letters and digits. Each digit d means "repeat the previous letter d times." Match this expanded pattern against a target string.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** String expansion + matching (not DP typically)
**Reason:** First expand the pattern string (or match on-the-fly). If the digit is a single variable (unknown repeat count), this becomes a regex-like matching problem → DP. If digits are literal, expand and compare directly. Depends on whether digits are known or represent unknowns.
</details>

---

**Drill 4:**
> Count the number of distinct substrings of a string.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Suffix Array or Trie (not DP)
**Reason:** Using a suffix array: build suffix array, compute LCP array. Distinct substrings = n*(n+1)/2 - sum(LCP). Or use a Trie: insert all suffixes, count nodes. O(n log n) with suffix array, O(n²) with Trie. DP is not the natural approach here.
</details>

---

**Drill 5:**
> You have a wordlist and a sentence. Find all possible ways to insert spaces to create valid sentences using only words from the wordlist.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Word Break II (DFS + memoization)
**Reason:** dp[i] = list of all valid segmentations of s[i..n-1]. Memoize to avoid recomputation. For each position i, try all words starting at i. Concatenate results recursively. LC 140. Exponential output makes this harder to optimize beyond memoized DFS.
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Space | Notes |
|---------|------|-------|-------|
| Word Break | O(n² × L) | O(n) | L = avg word length |
| Wildcard Matching | O(m×n) | O(m×n) → O(n) | |
| Regex Matching | O(m×n) | O(m×n) → O(n) | Trickier base cases |
| Distinct Subsequences | O(m×n) | O(m×n) → O(n) | Long long for large counts |
| LPS (interval DP) | O(n²) | O(n²) | Or use LCS trick |
| Palindromic Substrings | O(n²) | O(1) | Expand from center |

---

## 9. Common Follow-up Questions

1. Word Break with backtracking to return all sentences? (LC 140 — add memoized DFS on top; dp[i] stores all valid ways to segment s[i..n-1])
2. Regex with `+` (one or more)? (Similar to `*` but dp[i][j] can't skip the char — must match at least once)
3. How is Wildcard `*` different from Regex `*`? (Wildcard: `*` alone matches any sequence. Regex: `*` applies to preceding element, repeating it 0+ times. Completely different semantics)
4. Palindrome partitioning minimum cuts in O(n)? (Manacher's algorithm + DP can achieve O(n) but is very complex; standard O(n²) is interview-acceptable)

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| Expand from Center | Palindrome substrings (simpler than 2D DP) | 647. Palindromic Substrings |
| LCS | LPS = LCS(s, reverse(s)) | 516. LPS |
| 2D DP | Matching two strings character by character | 44, 10, 72 |
| Trie | Word Break with many words (faster lookup) | 139. Word Break optimization |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
