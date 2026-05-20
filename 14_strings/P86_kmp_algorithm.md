# P86 — KMP Pattern Matching

## 1. First-Timer Explanation

### What Is It?
**KMP (Knuth-Morris-Pratt)** finds all occurrences of a pattern `p` in a text `t` in O(n+m) time, avoiding the O(nm) of naive string search. The key insight: when a mismatch occurs, we don't restart from scratch — we use the **failure function** (also called `lps`: Longest Proper Prefix which is also Suffix) to know how far back to roll the pattern pointer.

### The Failure Function (LPS Array)
```
Pattern: a b a b c
lps:     0 0 1 2 0

lps[i] = length of longest proper prefix of pattern[0..i] that is also a suffix.

For "abab": "ab" is both a prefix and a suffix → lps[3] = 2
For "ababc": no prefix matches suffix → lps[4] = 0
```

### Visual Walkthrough — Matching
```
Text:    a b a b a b c a b
Pattern: a b a b c
                ^-- mismatch at i=4 in text, j=4 in pattern

lps[j-1] = lps[3] = 2 → set j = 2 (don't reset to 0!)
Pattern:     a b a b c
                 ^-- resume from j=2

Text continues: match at positions 2..6 ✓
```

### When to Use
- "Find pattern in text" → KMP in O(n+m)
- "Shortest period of a string" → use LPS: period = `n - lps[n-1]`
- "Repeated string pattern" → check if (s+s).find(s) != 0 or n/period is integer
- "String rotation" → is t a rotation of s? → find t in (s+s)

### Common Mistakes
1. LPS build: when mismatch at `lps[len-1]`, set `len = lps[len-1]` (NOT 0)
2. KMP search: after mismatch, `j = lps[j-1]` (NOT 0) unless `j == 0`
3. LPS is 0-indexed and has length m (same as pattern)
4. Overlap detection: when `j == m` (full match), next is `lps[j-1]`, not j=0

---

## 2. Revision Card

**Recognition Signal:** "find all occurrences of pattern", "shortest period", "string rotation"

**Core Idea:** Precompute LPS array in O(m). Use it during matching to skip redundant comparisons: on mismatch, `j = lps[j-1]`; on match, record position when `j == m`.

**Trigger Keywords:** pattern matching, KMP, failure function, LPS, substring search

**Complexity:** O(n+m) time, O(m) space

---

## 3. Interview Tell Signs

- "Find pattern in text without library" → KMP
- "Shortest repeating unit of a string" → LPS: `period = n - lps[n-1]`; if `n % period == 0`, string is periodic
- "Check if string is rotation of another" → `(s+s).contains(t)` or KMP on `s+s`
- "Minimum characters to add to front to make palindrome" → reverse + KMP
- "String matching in O(n+m)" → KMP or Z-algorithm (P88)

---

## 4. C++ Template

```cpp
#include <vector>
#include <string>
using namespace std;

// ── Build LPS (Failure Function) ──────────────────────────────────────────────
vector<int> buildLPS(const string& pat) {
    int m = pat.size();
    vector<int> lps(m, 0);
    int len = 0, i = 1;
    while (i < m) {
        if (pat[i] == pat[len]) { lps[i++] = ++len; }
        else if (len > 0) { len = lps[len-1]; } // don't advance i
        else { lps[i++] = 0; }
    }
    return lps;
}

// ── KMP Search ────────────────────────────────────────────────────────────────
vector<int> kmpSearch(const string& text, const string& pat) {
    int n = text.size(), m = pat.size();
    vector<int> lps = buildLPS(pat);
    vector<int> matches;
    int i = 0, j = 0; // i=text ptr, j=pattern ptr
    while (i < n) {
        if (text[i] == pat[j]) { i++; j++; }
        if (j == m) {
            matches.push_back(i - j); // match at position i-j
            j = lps[j-1];
        } else if (i < n && text[i] != pat[j]) {
            if (j > 0) j = lps[j-1];
            else i++;
        }
    }
    return matches;
}

// ── Shortest Period ────────────────────────────────────────────────────────────
int shortestPeriod(const string& s) {
    int n = s.size();
    vector<int> lps = buildLPS(s);
    int period = n - lps[n-1];
    return (n % period == 0) ? period : n; // n if not periodic
}
```

---

## 5. How to Present in Interview

**Verbal Script (LPS Build):**
> "I build the LPS array with two pointers: `len` (length of current matching prefix-suffix) and `i` (position being processed). If `pat[i] == pat[len]`, extend: `lps[i] = ++len`. Otherwise, if `len > 0`, fall back: `len = lps[len-1]`. If `len == 0`, set `lps[i] = 0`. This is O(m) because `len` increases at most once per iteration and decreases by at least 1 per fallback (bounded by total increases)."

**Verbal Script (KMP Search):**
> "Two pointers: `i` for text, `j` for pattern. On match, advance both. When `j == m`, record match, then `j = lps[j-1]` to continue searching for overlapping matches. On mismatch: if `j > 0`, fall back `j = lps[j-1]`; else advance `i`."

**Checklist:**
- [ ] LPS fallback: `len = lps[len-1]` not `len = 0`
- [ ] KMP: after full match `j == m`, use `lps[j-1]` not `j = 0`
- [ ] KMP: when `j == 0` and mismatch, advance `i` (don't fall back)
- [ ] Period: `n - lps[n-1]`; check `n % period == 0` for true periodicity

---

## 6. Problems

### Problem 1: Find the Index of the First Occurrence in a String
**Difficulty:** Easy | **LC:** 28

```cpp
int strStr(string haystack, string needle) {
    int n=haystack.size(), m=needle.size();
    if (m==0) return 0;
    vector<int> lps(m,0);
    for (int i=1,len=0; i<m;) {
        if (needle[i]==needle[len]) lps[i++]=++len;
        else if (len>0) len=lps[len-1];
        else lps[i++]=0;
    }
    for (int i=0,j=0; i<n;) {
        if (haystack[i]==needle[j]) {i++;j++;}
        if (j==m) return i-j;
        else if (i<n&&haystack[i]!=needle[j]) {if(j>0) j=lps[j-1]; else i++;}
    }
    return -1;
}
// Time: O(n+m) | Space: O(m)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Repeated Substring Pattern
**Difficulty:** Easy | **LC:** 459

```cpp
bool repeatedSubstringPattern(string s) {
    int n=s.size();
    vector<int> lps(n,0);
    for (int i=1,len=0; i<n;) {
        if (s[i]==s[len]) lps[i++]=++len;
        else if (len>0) len=lps[len-1];
        else lps[i++]=0;
    }
    int period=n-lps[n-1];
    return period!=n && n%period==0;
}
// Time: O(n) | Space: O(n)
// Alternative: find s in (s+s)[1..2n-2] (exclude first and last chars)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Shortest Palindrome (Add to Front)
**Difficulty:** Hard | **LC:** 214

**Approach:** Find longest palindromic prefix using KMP. Append reverse of remaining suffix.

```cpp
string shortestPalindrome(string s) {
    string rev = string(s.rbegin(), s.rend());
    string t = s + "#" + rev; // # prevents overlap between s and rev
    int n = t.size();
    vector<int> lps(n, 0);
    for (int i=1,len=0; i<n;) {
        if (t[i]==t[len]) lps[i++]=++len;
        else if (len>0) len=lps[len-1];
        else lps[i++]=0;
    }
    // lps[n-1] = length of longest palindromic prefix of s
    int palindromePrefixLen = lps[n-1];
    string suffix = s.substr(palindromePrefixLen);
    reverse(suffix.begin(), suffix.end());
    return suffix + s;
}
// Time: O(n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Rotate String
**Difficulty:** Easy | **LC:** 796

```cpp
bool rotateString(string s, string goal) {
    if (s.size() != goal.size()) return false;
    return (s + s).find(goal) != string::npos;
    // KMP version: search for goal in s+s in O(n) instead of find's O(n²)
}
// Time: O(n) with KMP | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Count Occurrences of Anagram
**Difficulty:** Medium | **LC:** 438 (Find All Anagrams)

**Approach:** Sliding window with character frequency (not KMP, but related string matching).

```cpp
vector<int> findAnagrams(string s, string p) {
    vector<int> freq(26,0), window(26,0);
    for (char c:p) freq[c-'a']++;
    int k=p.size(); vector<int> res;
    for (int i=0; i<(int)s.size(); i++) {
        window[s[i]-'a']++;
        if (i>=k) window[s[i-k]-'a']--;
        if (window==freq) res.push_back(i-k+1);
    }
    return res;
}
// Time: O(n) | Space: O(1) (fixed 26-size arrays)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: Minimum Window Substring
**Difficulty:** Hard | **LC:** 76

```cpp
string minWindow(string s, string t) {
    vector<int> need(128,0); int missing=t.size();
    for (char c:t) need[c]++;
    int lo=0, hi=0, start=0, minLen=INT_MAX;
    while (hi<(int)s.size()) {
        if (need[s[hi++]]-- > 0) missing--;
        while (missing==0) {
            if (hi-lo<minLen) { minLen=hi-lo; start=lo; }
            if (need[s[lo++]]++ == 0) missing++;
        }
    }
    return minLen==INT_MAX ? "" : s.substr(start,minLen);
}
// Time: O(n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** Build LPS for "aabaab".
<details><summary>Reveal</summary>
i=1,len=0: 'a'=='a'→lps[1]=1,len=1,i=2. i=2,len=1: 'b'≠'a'→len=lps[0]=0. 'b'≠'a'(len=0)→lps[2]=0,i=3. i=3,len=0: 'a'=='a'→lps[3]=1,len=1,i=4. i=4,len=1: 'a'=='a'→lps[4]=2,len=2,i=5. i=5,len=2: 'b'=='b'→lps[5]=3,len=3,i=6. LPS=[0,1,0,1,2,3].
</details>

**Drill 2:** Is "abababab" periodic? What is the period?
<details><summary>Reveal</summary>
Build LPS for "abababab" (n=8). The pattern "ab" repeats. lps[7]=6 (longest prefix-suffix "ababab"). period=8-6=2. n%period=8%2=0 → periodic with period 2 (unit="ab") ✓.
</details>

**Drill 3:** Shortest palindrome for "aacecaaa". What is the LPS approach?
<details><summary>Reveal</summary>
s="aacecaaa", rev="aaacecaa". t="aacecaaa#aaacecaa". Build LPS for t. The last LPS value = length of longest palindromic prefix of s. "aacecaa" is a palindrome (length 7). So palindromePrefixLen=7. Suffix=s[7]="a". Reversed="a". Answer="a"+"aacecaaa"="aaacecaaa".
</details>

**Drill 4:** KMP search for "ab" in "ababab". How many matches and at what indices?
<details><summary>Reveal</summary>
LPS for "ab"=[0,0]. i=0,j=0: 'a'=='a'→i=1,j=1. 'b'=='b'→i=2,j=2. j==m=2: match at 0. j=lps[1]=0. i=2,j=0: 'a'=='a'→i=3,j=1. 'b'=='b'→i=4,j=2. j==2: match at 2. j=0. i=4,j=0: 'a'→i=5,j=1. 'b'→i=6,j=2. j==2: match at 4. Matches at [0,2,4] ✓.
</details>

**Drill 5:** Why is the LPS fallback `len = lps[len-1]` instead of `len = 0`?
<details><summary>Reveal</summary>
When a mismatch occurs at position `len` in the pattern, we know that `pat[0..len-1]` matched so far. The LPS value `lps[len-1]` tells us the length of the longest proper prefix of `pat[0..len-1]` that is also a suffix. This means we can "slide" the pattern to align this prefix-suffix and resume from there — skipping work already proven to match. Setting `len=0` would discard this information and is overly conservative.
</details>

---

## 8. Complexity Cheatsheet

| Operation | Time | Space |
|-----------|------|-------|
| Build LPS | O(m) | O(m) |
| KMP search | O(n + m) | O(m) |
| Repeated substring check | O(n) | O(n) |
| Shortest palindrome | O(n) | O(n) |
| Rotate string check | O(n) | O(n) |

---

## 9. Common Follow-up Questions

**Q: What is the difference between KMP and Boyer-Moore?**
A: KMP uses a failure function to avoid re-comparing prefix matches; it scans left-to-right and is always O(n+m). Boyer-Moore uses bad-character and good-suffix heuristics, scanning right-to-left within the pattern, and has O(n/m) best case (sub-linear) but O(nm) worst case without good-suffix rule.

**Q: Can KMP handle multiple patterns?**
A: For multiple patterns, use Aho-Corasick (builds a trie with failure links — a generalization of KMP). It processes all patterns in O(total_pattern_length + n + matches).

**Q: How do you find the minimum rotations to make string s equal to string t?**
A: Find the position of t in s+s using KMP. The position is the number of rotations needed.

---

## 10. Cross-Pattern Connections

- **P87 (Rabin-Karp):** Alternative string matching using hash; easier to implement, probabilistic
- **P88 (Z-Algorithm):** Computes Z-array instead of LPS; equivalent power, different form
- **P93 (Trie):** Aho-Corasick extends KMP to multiple patterns using a trie with failure links
- **P90 (Anagram):** Sliding window frequency matching is the anagram pattern; KMP is exact matching
