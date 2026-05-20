# P88 — Z-Algorithm and String Preprocessing

## 1. First-Timer Explanation

### What Is It?
**Z-algorithm** computes for each position `i` in a string `s`, the length of the longest substring starting at `i` that matches a prefix of `s`. This Z-array enables O(n) pattern matching and is equivalent in power to KMP's failure function.

### How Z-Array Works
```
s = "aabxaab"
     0123456

Z[0] = len(s) by convention (or 0/undefined)
Z[1]: compare s[1..] vs s[0..]: 'a'=='a' → compare 'b' vs 'a' → stop. Z[1]=1
Z[2]: 'b'≠'a' → Z[2]=0
Z[3]: 'x'≠'a' → Z[3]=0
Z[4]: compare s[4..] vs s[0..]: 'a'=='a','a'=='a','b'=='b' → Z[4]=3
Z[5]: compare s[5..] vs s[0..]: 'a'=='a','b'=='b' → Z[5]=2
Z[6]: 'b'≠'a' → Z[6]=0

Z = [7, 1, 0, 0, 3, 2, 0]  (Z[0]=len by convention)
```

### Efficient Computation Using Z-Box
```
Maintain a "Z-box" [l, r] — the rightmost interval where s[l..r] = s[0..r-l].
For each i:
  If i is inside [l,r]: Z[i] >= min(Z[i-l], r-i+1)
    - If Z[i-l] < r-i+1: Z[i] = Z[i-l] (already known, no extension)
    - Else: extend from r+1 onward, update l=i, r=new_right
  If i > r: compare naively from scratch, update l=i, r=new_right
```

### Pattern Matching with Z-Algorithm
```
Build s = pattern + "$" + text ($ = separator not in alphabet)
Z[i] = len of match between s[i..] and s[0..] = pattern[0..]
If Z[i] == len(pattern): pattern found at position i - len(pattern) - 1 in text
```

### When to Use
- "String matching" → Z-algorithm (alternative to KMP)
- "Find all positions where pattern appears" → Z on pattern + $ + text
- "Count distinct substrings" → suffix array (related)
- "Periods and borders" → same as KMP

---

## 2. Revision Card

**Recognition Signal:** "prefix matching at each position", "Z-box", "pattern matching O(n)"

**Core Idea:** `Z[i]` = length of longest match between `s[i..]` and `s[0..]`. Use the Z-box `[l,r]` to avoid recomputation for positions within the box.

**Trigger Keywords:** Z-array, Z-function, prefix match, border, period

**Complexity:** O(n) time and space

---

## 3. Interview Tell Signs

- "Find all occurrences of pattern in text in O(n)" → Z-algorithm or KMP
- "Compute where each suffix matches the prefix" → Z-array
- "Is string s a prefix of string t?" → check Z[len(s)+1] in s+"$"+t
- "Palindrome check via prefix matching" → Z on s + "$" + reverse(s)

---

## 4. C++ Template

```cpp
#include <string>
#include <vector>
using namespace std;

// ── Build Z-Array ─────────────────────────────────────────────────────────────
vector<int> buildZ(const string& s) {
    int n = s.size();
    vector<int> z(n, 0);
    z[0] = n; // by convention
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r) { l = i; r = i + z[i]; }
    }
    return z;
}

// ── Pattern Matching with Z-Algorithm ────────────────────────────────────────
vector<int> zSearch(const string& text, const string& pat) {
    string s = pat + "$" + text;
    vector<int> z = buildZ(s);
    int m = pat.size();
    vector<int> matches;
    for (int i = m + 1; i < (int)s.size(); i++)
        if (z[i] == m) matches.push_back(i - m - 1); // position in text
    return matches;
}

// ── Shortest Period using Z-Array ─────────────────────────────────────────────
int shortestPeriodZ(const string& s) {
    int n = s.size();
    vector<int> z = buildZ(s);
    for (int i = 1; i < n; i++)
        if (z[i] + i == n && n % i == 0) return i; // period = i
    return n; // string itself is the shortest period
}
```

---

## 5. How to Present in Interview

**Verbal Script:**
> "I maintain a Z-box [l, r] — the rightmost matched interval. For position i, if i < r, I initialize Z[i] from the already-computed Z[i-l] (using the symmetry of the box). Then I extend naively from where the box ends. If the extension goes beyond r, I update l and r. This ensures each character is compared at most twice, giving O(n) total."

**Checklist:**
- [ ] Initialize `l = 0, r = 0` before the loop
- [ ] When `i < r`: `z[i] = min(r - i, z[i - l])`
- [ ] Always try to extend: `while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++`
- [ ] Update box: `if (i + z[i] > r) { l = i; r = i + z[i]; }`
- [ ] For matching: separator prevents Z values from crossing boundary

---

## 6. Problems

### Problem 1: Implement strStr() with Z-Algorithm
**Difficulty:** Easy | **LC:** 28

```cpp
int strStr(string haystack, string needle) {
    if (needle.empty()) return 0;
    string s = needle + "#" + haystack;
    int n=s.size(), m=needle.size();
    vector<int> z(n,0); z[0]=n;
    for (int i=1,l=0,r=0;i<n;i++) {
        if (i<r) z[i]=min(r-i,z[i-l]);
        while (i+z[i]<n&&s[z[i]]==s[i+z[i]]) z[i]++;
        if (i+z[i]>r){l=i;r=i+z[i];}
        if (z[i]==m) return i-m-1;
    }
    return -1;
}
// Time: O(n+m) | Space: O(n+m)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Count Occurrences of Pattern
**Difficulty:** Medium (custom)

```cpp
int countOccurrences(string text, string pat) {
    string s = pat + "#" + text;
    int n=s.size(), m=pat.size(), cnt=0;
    vector<int> z(n,0); z[0]=n;
    for (int i=1,l=0,r=0;i<n;i++) {
        if (i<r) z[i]=min(r-i,z[i-l]);
        while (i+z[i]<n&&s[z[i]]==s[i+z[i]]) z[i]++;
        if (i+z[i]>r){l=i;r=i+z[i];}
        if (z[i]==(int)m) cnt++;
    }
    return cnt;
}
// Time: O(n+m) | Space: O(n+m)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Repeated Substring Pattern (Z-version)
**Difficulty:** Easy | **LC:** 459

```cpp
bool repeatedSubstringPattern(string s) {
    int n=s.size();
    vector<int> z(n,0); z[0]=n;
    for (int i=1,l=0,r=0;i<n;i++) {
        if (i<r) z[i]=min(r-i,z[i-l]);
        while (i+z[i]<n&&s[z[i]]==s[i+z[i]]) z[i]++;
        if (i+z[i]>r){l=i;r=i+z[i];}
        if (z[i]+i==n&&n%i==0) return true; // period = i
    }
    return false;
}
// Time: O(n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Longest Common Prefix of Two Strings Using Z
**Difficulty:** Easy (custom)

```cpp
int longestCommonPrefix(const string& a, const string& b) {
    string s = a + "#" + b;
    vector<int> z = buildZ(s);
    return z[a.size() + 1]; // Z value at start of b in combined string
}
// Time: O(n+m) | Space: O(n+m)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Number of Ways to Split a String
**Difficulty:** Medium | **LC:** 1573

```cpp
int numWays(string s) {
    long long ones=count(s.begin(),s.end(),'1'), n=s.size(), MOD=1e9+7;
    if (ones%3!=0) return 0;
    if (ones==0) return (n-1)*(n-2)/2%MOD;
    long long target=ones/3;
    long long cnt1=0,cnt2=0,first=-1,second=-1,third=-1,fourth=-1;
    for (int i=0;i<n;i++) {
        if (s[i]=='1') {
            if (++cnt1==target) first=i;
            if (cnt1==target+1) second=i;
            if (cnt1==2*target) third=i;
            if (cnt1==2*target+1) fourth=i;
        }
    }
    return (long long)(second-first)*(fourth-third)%MOD;
}
// Time: O(n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: Longest Substring Without Repeating Characters
**Difficulty:** Medium | **LC:** 3

```cpp
int lengthOfLongestSubstring(string s) {
    unordered_map<char,int> last; int lo=0, res=0;
    for (int hi=0; hi<(int)s.size(); hi++) {
        if (last.count(s[hi])&&last[s[hi]]>=lo) lo=last[s[hi]]+1;
        last[s[hi]]=hi;
        res=max(res,hi-lo+1);
    }
    return res;
}
// Time: O(n) | Space: O(1) (at most 128 ASCII chars)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** Compute Z-array for "aabcaab".
<details><summary>Reveal</summary>
Z[0]=7. i=1: l=0,r=0. i>r: compare s[1]='a' vs s[0]='a'→Z[1]=1. s[1+1]='b'≠s[1]='a'→stop. Z[1]=1. l=1,r=2. i=2: i<r? 2<2? No. compare s[2]='b' vs s[0]='a'→Z[2]=0. i=3: compare 'c' vs 'a'→Z[3]=0. i=4: compare s[4]='a' vs s[0]='a','a'vs'a','b'vs'b'→3. s[7] out of bounds. Z[4]=3. l=4,r=7. i=5: i<r=7. Z[5]=min(7-5,Z[5-4])=min(2,Z[1])=min(2,1)=1. Extend: s[5+1]='b' vs s[1]='a'→no. Z[5]=1. 5+1=6≤7, no update. i=6: i<r. Z[6]=min(7-6,Z[6-4])=min(1,Z[2])=min(1,0)=0. Extend: s[6]='b' vs s[0]='a'→no. Z[6]=0. Z=[7,1,0,0,3,1,0].
</details>

**Drill 2:** Z-search for pattern "ab" in text "ababab". What combined string and which positions are matches?
<details><summary>Reveal</summary>
s="ab#ababab" (length 9). m=2. Z[0]=9. For i≥3 (text part): Z[3]=2 (i-m-1=0 → match), Z[5]=2 (pos 2), Z[7]=2 (pos 4). Matches at [0,2,4] ✓.
</details>

**Drill 3:** Repeated substring for "abab". Z-array at i=2?
<details><summary>Reveal</summary>
s="abab". i=2: compare s[2]='a' vs s[0]='a', s[3]='b' vs s[1]='b' → Z[2]=2. Check: z[2]+2=4=n and 4%2=0 → periodic with period 2. Returns true ✓.
</details>

**Drill 4:** How does the Z-box [l,r] guarantee O(n) overall time?
<details><summary>Reveal</summary>
The box [l,r] represents the rightmost matched interval seen so far. When extending naively, r increases. Since r only increases (never decreases), and r is bounded by n, the total number of naive comparisons across all positions is O(n). For positions inside the box, we use precomputed values without new comparisons. Combined, each character is examined at most twice → O(n).
</details>

**Drill 5:** Z-algorithm vs KMP: when would you choose one over the other?
<details><summary>Reveal</summary>
Both are O(n+m). Z-algorithm is often easier to understand and implement (cleaner code), and the Z-array has a more intuitive meaning (length of prefix match). KMP's failure function (LPS) is more useful for period/border analysis. In an interview setting, Z-algorithm is slightly simpler to code from scratch. KMP is more common in textbooks and competitive programming. Choose based on familiarity.
</details>

---

## 8. Complexity Cheatsheet

| Operation | Time | Space |
|-----------|------|-------|
| Build Z-array | O(n) | O(n) |
| Z-algorithm search | O(n+m) | O(n+m) |
| Shortest period | O(n) | O(n) |
| Common prefix of two strings | O(n+m) | O(n+m) |

---

## 9. Common Follow-up Questions

**Q: Can Z-algorithm be used for bidirectional matching (palindromes)?**
A: For palindrome-related prefix matching: build Z on `s + "$" + reverse(s)`. Then `Z[i]` in the reversed part gives the length of the palindromic prefix matching. But Manacher's algorithm (P89) is more direct for palindrome problems.

**Q: How does Z-array relate to the suffix array?**
A: The suffix array is a sorted array of all suffixes. Z-values are related to the LCP (Longest Common Prefix) array. Specifically, Z[i] gives the longest common prefix between the suffix starting at i and the string itself. The LCP array of the suffix array can be computed from Z-values.

**Q: What is a "border" of a string?**
A: A proper prefix that is also a proper suffix. For "abab", "ab" is a border. `lps[n-1]` (KMP) and Z-values where `Z[i] + i == n` both identify borders.

---

## 10. Cross-Pattern Connections

- **P86 (KMP):** Equivalent power; LPS and Z-array encode the same information differently
- **P87 (Rabin-Karp):** Alternative hash-based O(n) matching; probabilistic vs deterministic
- **P89 (Manacher's):** Palindrome-specific preprocessing, related Z-like technique
- **P93 (Trie):** Aho-Corasick extends Z-algorithm's idea to multiple pattern matching on a trie
