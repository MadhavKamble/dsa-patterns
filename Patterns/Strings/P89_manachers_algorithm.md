# P89 — Manacher's Algorithm (Palindromes)

## 1. First-Timer Explanation

### What Is It?
**Manacher's algorithm** finds the longest palindromic substring in O(n) time by computing `p[i]` = the radius of the longest palindrome centered at each position. Like the Z-algorithm, it uses a "current rightmost palindrome" to avoid recomputation.

### The Key Transformation
```
Insert '#' between characters (and at ends) to unify odd/even palindromes:
  "abba"  →  "#a#b#b#a#"   (length 2n+1)
  "aba"   →  "#a#b#a#"     (length 2n+1)

Now all palindromes are ODD-length in the transformed string.
p[i] = radius of palindrome centered at i in transformed string.
```

### Visual Walkthrough
```
s = "#a#b#b#a#"
     012345678

p[0]=0: '#' alone
p[1]=1: "a" (radius 1 = char 'a')
p[2]=0: '#'
p[3]=2: "#b#" (radius 2 = "bb" palindrome)... wait, center of "abba" is between b,b

Actually for "#a#b#b#a#":
i:     0 1 2 3 4 5 6 7 8
char:  # a # b # b # a #
p:     0 1 0 2 3 2 0 1 0

p[4]=3: the whole "abba" palindrome has radius 3 in transformed (=#a#b#b#a# centered at index 4 = '#' between b's)
p[4]=3 means palindrome radius 3 chars: "a#b#b#a" → corresponds to "abba" of length p[i]=3 → actual length = p[i]=3
```

### When to Use
- "Longest palindromic substring" → Manacher's O(n)
- "Count all palindromic substrings" → sum up radii (each radius contributes palindromes)
- "Expand around center" → O(n²) for simpler problems
- "Palindrome partition" → precompute isPalin[i][j] (DP in O(n²)) (P50)

### Common Mistakes
1. Transformation: use a character not in the string (like '#') as separator
2. p[i] in transformed string = actual palindrome length for even, (p[i]+1)/2 rounded for odd
3. When using the mirror: `mirror = 2*center - i`; `p[i] = min(right - i, p[mirror])`
4. Off-by-one in converting back to original string indices

---

## 2. Revision Card

**Recognition Signal:** "longest palindromic substring", "count palindromes", "O(n) palindrome"

**Core Idea:** Transform string with '#' separators. Maintain rightmost palindrome [center, right]. For each i: use mirror symmetry to initialize p[i], then expand.

**Trigger Keywords:** palindrome, Manacher, expand center, longest palindrome, O(n)

**Complexity:** O(n) time, O(n) space

---

## 3. Interview Tell Signs

- "Longest palindromic substring in O(n)" → Manacher's
- "Count total palindromic substrings" → either O(n²) expand or Manacher's
- "Longest palindromic subsequence" → DP (different — subsequence not substring)
- "Is this string a palindrome?" → two pointer from ends O(n)
- "Palindrome partition minimum cuts" → DP on isPalin array (P50)

---

## 4. C++ Template

```cpp
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// ── Manacher's Algorithm ──────────────────────────────────────────────────────
// Returns p[i] array for transformed string "#a#b#..." 
// p[i] = radius of palindrome at i in transformed string
vector<int> manacher(const string& s) {
    string t = "#";
    for (char c : s) { t += c; t += '#'; }
    int n = t.size();
    vector<int> p(n, 0);
    int center = 0, right = 0;
    for (int i = 0; i < n; i++) {
        if (i < right) {
            int mirror = 2 * center - i;
            p[i] = min(right - i, p[mirror]);
        }
        // Try to expand
        while (i - p[i] - 1 >= 0 && i + p[i] + 1 < n && t[i - p[i] - 1] == t[i + p[i] + 1])
            p[i]++;
        // Update rightmost palindrome
        if (i + p[i] > right) { center = i; right = i + p[i]; }
    }
    return p;
}

// ── Longest Palindromic Substring ────────────────────────────────────────────
string longestPalindrome(string s) {
    vector<int> p = manacher(s);
    int maxLen = 0, maxCenter = 0;
    for (int i = 0; i < (int)p.size(); i++) {
        if (p[i] > maxLen) { maxLen = p[i]; maxCenter = i; }
    }
    // Convert back: original start = (maxCenter - maxLen) / 2
    int start = (maxCenter - maxLen) / 2;
    return s.substr(start, maxLen);
}

// ── Count Palindromic Substrings ─────────────────────────────────────────────
int countSubstrings(string s) {
    vector<int> p = manacher(s);
    int count = 0;
    for (int pi : p) count += (pi + 1) / 2; // each radius contributes ceil(p[i]/2)+... 
    // Actually: each position contributes floor(p[i]/2) odd-length + ceiling palindromes
    // Simpler: total = sum((p[i]+1)/2) for the transformed string positions
    return count;
}

// ── Expand Around Center (O(n²), easier to code) ─────────────────────────────
int expandAroundCenter(const string& s, int l, int r) {
    while (l >= 0 && r < (int)s.size() && s[l] == s[r]) { l--; r++; }
    return r - l - 1; // length of palindrome
}

string longestPalindromeSimple(string s) {
    int n = s.size(), start = 0, maxLen = 1;
    for (int i = 0; i < n; i++) {
        int odd = expandAroundCenter(s, i, i);
        int even = expandAroundCenter(s, i, i+1);
        int len = max(odd, even);
        if (len > maxLen) { maxLen = len; start = i - (len-1)/2; }
    }
    return s.substr(start, maxLen);
}
```

---

## 5. How to Present in Interview

**Verbal Script (Expand Around Center, O(n²)):**
> "For each position i, expand outward in both directions while characters match. Do this for odd-length palindromes (center at i) and even-length (center between i and i+1). Track the longest. O(n) centers × O(n) expansion = O(n²) time, O(1) space."

**Verbal Script (Manacher's, O(n)):**
> "Insert '#' between characters to unify odd/even. Maintain the rightmost palindrome [center, right]. For each i: if i is within [center, right], initialize p[i] from the mirror position (same as Z-algorithm trick). Then expand. If the new palindrome extends beyond right, update center and right. O(n) total because right only moves forward."

**Checklist:**
- [ ] Transformation: `"#" + s[0] + "#" + s[1] + "#" + ... + s[n-1] + "#"`
- [ ] Mirror: `2*center - i`
- [ ] Initialize: `p[i] = min(right - i, p[mirror])` when `i < right`
- [ ] Expand: check bounds before accessing `t[i-p[i]-1]` and `t[i+p[i]+1]`
- [ ] Convert back: original start = `(center - radius) / 2`

---

## 6. Problems

### Problem 1: Longest Palindromic Substring
**Difficulty:** Medium | **LC:** 5

```cpp
string longestPalindrome(string s) {
    int n=s.size(), start=0, maxLen=1;
    auto expand=[&](int l,int r)->int{
        while(l>=0&&r<n&&s[l]==s[r]){l--;r++;}
        return r-l-1;
    };
    for (int i=0;i<n;i++) {
        int odd=expand(i,i), even=expand(i,i+1);
        int len=max(odd,even);
        if (len>maxLen) { maxLen=len; start=i-(len-1)/2; }
    }
    return s.substr(start,maxLen);
}
// Time: O(n²) | Space: O(1)
// Manacher's: O(n) — see template above
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Palindromic Substrings (Count)
**Difficulty:** Medium | **LC:** 647

```cpp
int countSubstrings(string s) {
    int n=s.size(), cnt=0;
    auto expand=[&](int l,int r){ while(l>=0&&r<n&&s[l]==s[r]){cnt++;l--;r++;} };
    for (int i=0;i<n;i++) { expand(i,i); expand(i,i+1); }
    return cnt;
}
// Time: O(n²) | Space: O(1)
// Each successful expansion = one additional palindromic substring
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Longest Palindromic Subsequence
**Difficulty:** Medium | **LC:** 516

**Approach:** DP — not Manacher's (subsequence ≠ substring). `dp[i][j] = longest palindromic subsequence in s[i..j]`.

```cpp
int longestPalindromeSubseq(string s) {
    int n=s.size();
    vector<vector<int>> dp(n,vector<int>(n,1));
    for (int len=2;len<=n;len++) {
        for (int i=0;i+len-1<n;i++) {
            int j=i+len-1;
            if (s[i]==s[j]) dp[i][j]=dp[i+1][j-1]+2;
            else dp[i][j]=max(dp[i+1][j],dp[i][j-1]);
        }
    }
    return dp[0][n-1];
}
// Time: O(n²) | Space: O(n²)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Valid Palindrome II (Allow One Deletion)
**Difficulty:** Easy | **LC:** 680

```cpp
bool validPalindrome(string s) {
    int l=0, r=s.size()-1;
    auto isPalin=[&](int lo,int hi){
        while(lo<hi) if(s[lo++]!=s[hi--]) return false;
        return true;
    };
    while (l<r) {
        if (s[l]!=s[r]) return isPalin(l+1,r)||isPalin(l,r-1);
        l++; r--;
    }
    return true;
}
// Time: O(n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Minimum Number of Moves to Make Palindrome
**Difficulty:** Hard | **LC:** 2193

**Approach:** Greedy — repeatedly bring the leftmost unmatched character's partner from the right.

```cpp
int minMovesToMakePalindrome(string s) {
    int n=s.size(), moves=0;
    while (s.size()>1) {
        int i=0, j=s.size()-1;
        if (s[i]==s[j]) { s.erase(j,1); s.erase(i,1); }
        else {
            // Find partner of s[j] from left
            int k=s.size()-2;
            while (s[k]!=s[j]) k--;
            if (k==0) { // s[j] has no partner, move to center
                moves++;
                // rotate s[0] to middle (but just continue)
                s.erase(0,1); // treat as middle
                continue;
            }
            // Move s[k] to position 1 (adjacent to s[j])
            moves+=s.size()-1-k-1; // k to rightmost inner
            s.erase(k,1); s.erase(s.size()-1,1);
        }
    }
    return moves;
}
// Time: O(n²) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: Palindrome Pairs
**Difficulty:** Hard | **LC:** 336

**Approach:** For each word, check if (reverse of word == another word), and if prefix/suffix of word's reverse is a palindrome that matches another word.

```cpp
vector<vector<int>> palindromePairs(vector<string>& words) {
    unordered_map<string,int> mp;
    for (int i=0;i<(int)words.size();i++) mp[words[i]]=i;
    auto isPalin=[](const string& s,int l,int r)->bool{
        while(l<r) if(s[l++]!=s[r--]) return false; return true;
    };
    vector<vector<int>> res;
    for (int i=0;i<(int)words.size();i++) {
        string rev=words[i]; reverse(rev.begin(),rev.end());
        // Case 1: whole word matches
        if (mp.count(rev)&&mp[rev]!=i) res.push_back({i,mp[rev]});
        // Case 2: prefix of rev is a palindrome, suffix matches another word
        for (int k=1;k<(int)words[i].size();k++) {
            if (isPalin(rev,0,k-1)&&mp.count(rev.substr(k)))
                res.push_back({mp[rev.substr(k)],i});
            if (isPalin(rev,k,rev.size()-1)&&mp.count(rev.substr(0,k)))
                res.push_back({i,mp[rev.substr(0,k)]});
        }
    }
    // Remove duplicates
    sort(res.begin(),res.end()); res.erase(unique(res.begin(),res.end()),res.end());
    return res;
}
// Time: O(n * k²) k=avg word len | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** Run Manacher's (transformed) on "aba". What is the transformed string and p-array?
<details><summary>Reveal</summary>
t="#a#b#a#" (length 7). p=[0,1,0,3,0,1,0]. p[3]=3 because the entire "aba" is a palindrome (radius 3 in transformed = length 3 in original). Original start = (3-3)/2=0, length=3. Longest palindrome = "aba" ✓.
</details>

**Drill 2:** For "abba", what is the longest palindrome using expand around center?
<details><summary>Reveal</summary>
Centers: i=0 odd: 'a' alone (1). i=0 even: s[0]='a',s[1]='b'→no (0). i=1 odd: 'b',expand: 'a'≠'b'→1. i=1 even: s[1]='b',s[2]='b'→match,expand: s[0]='a',s[3]='a'→match,expand: l=-1→stop. Length=4. i=2 odd: 'b' alone (1). i=2 even: 'b','a'→no. i=3 odd: 'a' alone. Max=4, start=1-(4-1)/2=1-1=0... wait even palindrome of length 4: start=i-(len-1)/2=1-(3)/2=1-1=0? Let me recalculate. For even expansion from (1,2): r-l-1 = (4-(-1)-1)=4. start = i - (len-1)/2 = 1 - 3/2 = 1-1=0. s.substr(0,4)="abba" ✓.
</details>

**Drill 3:** Count palindromic substrings in "aaa". Trace the expand calls.
<details><summary>Reveal</summary>
i=0 odd: expand(0,0). 'a': cnt=1. expand l=-1→stop. i=0 even: expand(0,1). 'a'=='a': cnt=2 (for "aa"). expand(-1,2)→stop. i=1 odd: expand(1,1). 'a': cnt=3. expand(0,2): 'a'=='a': cnt=4 (for "aaa"). expand(-1,3)→stop. i=1 even: expand(1,2). 'a'=='a': cnt=5 ("aa" again). expand(0,3)→out of bounds or 'a'? s[0]=='a',s[3]? n=3,3≥n→stop. i=2 odd: expand(2,2). cnt=6. i=2 even: expand(2,3)→3≥n→stop. Total=6 ✓ (a,a,a,aa,aa,aaa).
</details>

**Drill 4:** Longest palindromic subsequence in "bbbab". What's dp[0][4]?
<details><summary>Reveal</summary>
dp[i][j] for all i: dp[i][i]=1. Length 2: dp[0][1]: s[0]='b'==s[1]='b'→dp[0][1]=2. dp[1][2]=2, dp[2][3]=2, dp[3][4]:s[3]='a'≠s[4]='b'→max(dp[4][4],dp[3][3])=1. Length 3: dp[0][2]: 'b'==s[2]='b'→dp[1][1]+2=3. dp[1][3]:'b'≠'a'→max(dp[2][3],dp[1][2])=2. dp[2][4]:'b'==s[4]='b'→dp[3][3]+2=3. Length 4: dp[0][3]:'b'≠'a'→max(dp[1][3],dp[0][2])=max(2,3)=3. dp[1][4]:'b'==s[4]='b'→dp[2][3]+2=4. Length 5: dp[0][4]:'b'==s[4]='b'→dp[1][3]+2=4. Answer: 4 ✓ ("bbbb" using indices 0,1,2,4).
</details>

**Drill 5:** Valid palindrome II for "abca". At what mismatch do we branch?
<details><summary>Reveal</summary>
l=0,r=3: s[0]='a'==s[3]='a'→match. l=1,r=2. s[1]='b'≠s[2]='c'→mismatch. Try isPalin(2,2)="c"→true. OR isPalin(1,1)="b"→true. Actually try isPalin(l+1,r)=isPalin(2,2)="c"→one char→true. Return true. (Remove 'b' or 'c' to get "aca" or "aba"—both palindromes) ✓.
</details>

---

## 8. Complexity Cheatsheet

| Operation | Time | Space |
|-----------|------|-------|
| Expand around center (all) | O(n²) | O(1) |
| Manacher's algorithm | O(n) | O(n) |
| Count palindromic substrings | O(n²) or O(n) | O(1) or O(n) |
| Longest palindromic subsequence | O(n²) | O(n²) |
| Valid palindrome II | O(n) | O(1) |

---

## 9. Common Follow-up Questions

**Q: Difference between palindromic substring and subsequence?**
A: Substring must be contiguous (Manacher's O(n)). Subsequence can skip characters (DP O(n²)). For the subsequence version, `lps[i][j]` = longest palindromic subsequence in `s[i..j]`.

**Q: Count palindromic substrings in O(n)?**
A: Using Manacher's p-array: for each center i in the transformed string, there are `(p[i]+1)/2` palindromic substrings of the original string centered there (odd-length) or p[i]/2 (even-length). But the expand-center O(n²) approach is cleaner and sufficient for most interviews.

**Q: Can Manacher's handle 2D palindromes?**
A: No direct extension. For 2D palindromes (palindromic matrices), different DP approaches are needed.

---

## 10. Cross-Pattern Connections

- **P50 (Palindrome Partition):** Uses isPalin[i][j] DP (O(n²)) which can be computed from expand-around-center
- **P88 (Z-Algorithm):** Manacher's uses the same "rightmost extent" trick as Z-algorithm
- **P86 (KMP):** Palindrome = string that equals its reverse; KMP on `s + "#" + reverse(s)` finds palindromic prefixes
- **P30 (1D DP):** Palindromic subsequence is a 2D DP on intervals
