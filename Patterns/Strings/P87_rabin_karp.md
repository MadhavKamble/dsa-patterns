# P87 — Rabin-Karp and String Hashing

## 1. First-Timer Explanation

### What Is It?
**Rabin-Karp** uses rolling hashes to find pattern occurrences in O(n+m) expected time. Instead of comparing characters one-by-one, it compares hash values. A **rolling hash** updates in O(1) by removing the contribution of the outgoing character and adding the incoming character.

### Rolling Hash Formula
```
Hash of string s[l..r]:
h = (s[l]*p^(r-l) + s[l+1]*p^(r-l-1) + ... + s[r]) % MOD

Slide window right (remove s[l], add s[r+1]):
h_new = (h - s[l] * p^(r-l)) * p + s[r+1]
h_new %= MOD

Where p = prime base (31 for lowercase letters), MOD = large prime
```

### Visual Walkthrough
```
Text: "abcabc", Pattern: "abc" (len=3)
Base p=31, for simplicity use simple hash: sum of ASCII

Window [0,2]: 'a'+'b'+'c' = 97+98+99 = 294
Window [1,3]: subtract 'a'=97, add 'c'=99: 294-97+99=296
Window [2,4]: subtract 'b'=98, add 'b'=98: 296-98+98=296 (hash collision? check)
Window [3,5]: subtract 'c'=99, add 'c'=99: 296 (another collision)

When hash matches, do character-by-character verification.
```

### When to Use
- "Find pattern in text" → Rabin-Karp (simpler to code than KMP)
- "Find all repeated substrings of length k" → sliding window hash
- "Longest duplicate substring" → binary search on length + rolling hash set
- "Find if two substrings are equal in O(1)" → precomputed polynomial hash

### Common Mistakes
1. Hash collision: always verify character-by-character on hash match
2. Negative modulo in C++: `(h % MOD + MOD) % MOD` to handle negative values
3. Using double for hash: imprecise; use `long long` with modular arithmetic
4. Power computation: precompute powers of base, not recomputed each time

---

## 2. Revision Card

**Recognition Signal:** "repeated substring", "longest duplicate", "find in O(n) with hash"

**Core Idea:** Polynomial rolling hash. Slide window: subtract outgoing × highest_power × base, multiply by base, add incoming. Verify on hash match.

**Trigger Keywords:** rolling hash, Rabin-Karp, polynomial hash, substring equality, duplicate

**Complexity:** O(n+m) expected (O(nm) worst case due to collisions, but rare)

---

## 3. Interview Tell Signs

- "Longest duplicate substring" → binary search on length + rolling hash
- "Check if two substrings are equal" → prefix hash: `h(l,r) = (pre[r+1] - pre[l]*pow[r-l+1]) % MOD`
- "Find all duplicate substrings of length k" → sliding window hash set
- "String matching without library" → Rabin-Karp (easier than KMP to remember)

---

## 4. C++ Template

```cpp
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

const long long MOD = 1e9 + 7, BASE = 31;

// ── Polynomial Hash (Prefix Hashes) ──────────────────────────────────────────
struct StringHash {
    vector<long long> h, pw;
    StringHash(const string& s) {
        int n = s.size();
        h.resize(n + 1, 0); pw.resize(n + 1, 1);
        for (int i = 0; i < n; i++) {
            h[i+1] = (h[i] * BASE + (s[i] - 'a' + 1)) % MOD;
            pw[i+1] = pw[i] * BASE % MOD;
        }
    }
    // Hash of s[l..r] inclusive (0-indexed)
    long long get(int l, int r) {
        return (h[r+1] - h[l] * pw[r-l+1] % MOD + MOD * 2) % MOD;
    }
};

// ── Rabin-Karp Search ─────────────────────────────────────────────────────────
vector<int> rabinKarp(const string& text, const string& pat) {
    int n = text.size(), m = pat.size();
    StringHash th(text), ph(pat);
    long long patHash = ph.get(0, m-1);
    vector<int> matches;
    for (int i = 0; i + m <= n; i++) {
        if (th.get(i, i+m-1) == patHash) {
            if (text.substr(i, m) == pat) // verify (avoid false positives)
                matches.push_back(i);
        }
    }
    return matches;
}

// ── Longest Duplicate Substring (Binary Search + Rolling Hash) ────────────────
string longestDupSubstring(string s) {
    int n = s.size();
    StringHash sh(s);
    int lo = 1, hi = n - 1, bestStart = -1, bestLen = 0;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        // Check if any duplicate substring of length mid exists
        unordered_set<long long> seen;
        bool found = false; int foundStart = -1;
        for (int i = 0; i + mid <= n; i++) {
            long long hv = sh.get(i, i + mid - 1);
            if (seen.count(hv)) {
                // Verify (optional: assume no collision for simplicity)
                found = true; foundStart = i; break;
            }
            seen.insert(hv);
        }
        if (found) { bestLen = mid; bestStart = foundStart; lo = mid + 1; }
        else hi = mid - 1;
    }
    return bestLen > 0 ? s.substr(bestStart, bestLen) : "";
}
```

---

## 5. How to Present in Interview

**Verbal Script (Rolling Hash):**
> "I precompute prefix hashes: `h[i+1] = h[i] * BASE + char_value`. To get hash of substring `[l,r]`: `h[r+1] - h[l] * BASE^(r-l+1)`. This is O(1) per query after O(n) preprocessing. For Rabin-Karp, I compare pattern hash against each text window hash in O(1). On collision (same hash, possibly different strings), I verify character-by-character. Expected O(n+m) total."

**Checklist:**
- [ ] `+MOD*2` or `%MOD` carefully — C++ `%` can be negative for negative operands
- [ ] Always verify on hash match (avoid false positives)
- [ ] Use `long long` throughout (products can overflow `int`)
- [ ] Precompute power array: `pw[i] = BASE^i % MOD`
- [ ] For duplicates, use `unordered_set<long long>` to check previously seen hashes

---

## 6. Problems

### Problem 1: Implement strStr() with Rabin-Karp
**Difficulty:** Easy | **LC:** 28

```cpp
int strStr(string haystack, string needle) {
    int n=haystack.size(), m=needle.size();
    if (m==0) return 0; if (n<m) return -1;
    long long p=31, mod=1e9+7, ph=0, th=0, pw=1;
    for (int i=0;i<m;i++) {
        ph=(ph*p+(needle[i]-'a'+1))%mod;
        th=(th*p+(haystack[i]-'a'+1))%mod;
        if (i>0) pw=pw*p%mod;
    }
    if (ph==th&&haystack.substr(0,m)==needle) return 0;
    for (int i=1;i+m<=n;i++) {
        th=(th-pw*(haystack[i-1]-'a'+1)%mod+mod)*p%mod;
        th=(th+(haystack[i+m-1]-'a'+1))%mod;
        if (th==ph&&haystack.substr(i,m)==needle) return i;
    }
    return -1;
}
// Time: O(n+m) expected | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Longest Duplicate Substring
**Difficulty:** Hard | **LC:** 1044

```cpp
string longestDupSubstring(string s) {
    int n=s.size(); long long mod=1e9+7, base=31;
    // Binary search on answer length
    auto check=[&](int len)->int{
        long long h=0, pw=1;
        for (int i=0;i<len;i++) { h=(h*base+(s[i]-'a'+1))%mod; if(i>0) pw=pw*base%mod; }
        unordered_set<long long> seen; seen.insert(h);
        for (int i=1;i+len<=n;i++) {
            h=(h-(s[i-1]-'a'+1)*pw%mod+mod)*base%mod;
            h=(h+(s[i+len-1]-'a'+1))%mod;
            if (seen.count(h)) return i;
            seen.insert(h);
        }
        return -1;
    };
    int lo=1,hi=n-1,bestStart=-1,bestLen=0;
    while (lo<=hi) {
        int mid=lo+(hi-lo)/2;
        int pos=check(mid);
        if (pos!=-1) { bestStart=pos; bestLen=mid; lo=mid+1; }
        else hi=mid-1;
    }
    return bestLen>0?s.substr(bestStart,bestLen):"";
}
// Time: O(n log n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Find All Duplicate Substrings of Length K
**Difficulty:** Medium (custom)

```cpp
vector<string> findDuplicates(string s, int k) {
    int n=s.size(); if (n<k) return {};
    long long mod=1e9+7, base=31, pw=1, h=0;
    for (int i=0;i<k;i++) { h=(h*base+(s[i]-'a'+1))%mod; if(i>0) pw=pw*base%mod; }
    unordered_map<long long,int> seen; seen[h]=0;
    vector<string> res;
    for (int i=1;i+k<=n;i++) {
        h=(h-(s[i-1]-'a'+1)*pw%mod+mod)*base%mod;
        h=(h+(s[i+k-1]-'a'+1))%mod;
        if (seen.count(h)) res.push_back(s.substr(i,k));
        else seen[h]=i;
    }
    // Remove duplicates from res
    sort(res.begin(),res.end()); res.erase(unique(res.begin(),res.end()),res.end());
    return res;
}
// Time: O(n) expected | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Equal Substring Within Budget (Sliding Window + Hashing)
**Difficulty:** Medium | **LC:** 1208

```cpp
int equalSubstring(string s, string t, int maxCost) {
    int n=s.size(), lo=0, cost=0, res=0;
    for (int hi=0; hi<n; hi++) {
        cost+=abs(s[hi]-t[hi]);
        while (cost>maxCost) cost-=abs(s[lo]-t[lo++]);
        res=max(res,hi-lo+1);
    }
    return res;
}
// Time: O(n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Detect Capital
**Difficulty:** Easy | **LC:** 520

```cpp
bool detectCapitalUse(string word) {
    int caps = count_if(word.begin(), word.end(), ::isupper);
    return caps==0 || caps==(int)word.size() || (caps==1 && isupper(word[0]));
}
// Time: O(n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: Sum of Beauty of All Substrings
**Difficulty:** Medium | **LC:** 1781

**Approach:** For each substring, compute max_freq - min_freq of characters.

```cpp
int beautySum(string s) {
    int n=s.size(), res=0;
    for (int i=0;i<n;i++) {
        vector<int> freq(26,0);
        for (int j=i;j<n;j++) {
            freq[s[j]-'a']++;
            int mx=*max_element(freq.begin(),freq.end());
            int mn=INT_MAX;
            for (int f:freq) if(f>0) mn=min(mn,f);
            res+=mx-mn;
        }
    }
    return res;
}
// Time: O(n² * 26) = O(n²) | Space: O(26) = O(1)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** Rolling hash: hash of "abc" with base=31. Compute step by step.
<details><summary>Reveal</summary>
h[0]=0. h[1]=(0*31+('a'-'a'+1))=1. h[2]=(1*31+('b'-'a'+1))=1*31+2=33. h[3]=(33*31+('c'-'a'+1))=1023+3=1026. Hash of "abc"=1026.
</details>

**Drill 2:** Given prefix hash h=["","a","ab","abc"], what is hash of "b" (index 1)?
<details><summary>Reveal</summary>
get(1,1) = (h[2] - h[1]*pw[1]) % MOD. pw[1]=31. = (33 - 1*31) % MOD = 2. And 'b'-'a'+1=2 ✓.
</details>

**Drill 3:** Why do we multiply h[l] by `pw[r-l+1]` (power of length) in the substring hash formula?
<details><summary>Reveal</summary>
The prefix hash `h[r+1]` encodes characters from position 0 to r, where character at position 0 is multiplied by BASE^r. The prefix hash `h[l]` encodes characters from 0 to l-1, where character at position 0 is multiplied by BASE^(l-1). To subtract out h[l]'s contribution from h[r+1], we need to shift h[l] up by `r-l+1` positions (multiply by BASE^(r-l+1)) so the base exponents align and cancel correctly.
</details>

**Drill 4:** Longest duplicate substring in "banana". Binary search: what does check(3) return?
<details><summary>Reveal</summary>
Length 3 substrings: "ban"(0), "ana"(1), "nan"(2), "ana"(3), "na"... wait len=3: "ban","ana","nan","ana". At i=3, substring "ana" has same hash as i=1 "ana". check(3) returns 3 (position 3). Binary search continues with lo=4. check(4): "bana","anan","nana","ana"... No duplicates of length 4. hi=3. Result: bestLen=3, bestStart=3 or 1, s.substr(...)="ana" ✓.
</details>

**Drill 5:** What is a "hash collision" and why do we verify on match?
<details><summary>Reveal</summary>
A hash collision is when two different strings have the same hash value. This happens because the hash function maps many strings to a finite range (0 to MOD-1). When the pattern hash equals a window hash, the strings might still differ. Character-by-character verification catches these false positives. Using two independent hashes (double hashing) reduces collision probability to ~1/MOD² ≈ 10^-18, making verification optional in practice.
</details>

---

## 8. Complexity Cheatsheet

| Operation | Time | Space |
|-----------|------|-------|
| Build prefix hash | O(n) | O(n) |
| Get substring hash | O(1) | O(1) |
| Rabin-Karp search | O(n+m) expected | O(n) |
| Longest duplicate (binary search) | O(n log n) | O(n) |
| Check all duplicates of length k | O(n) expected | O(n) |

---

## 9. Common Follow-up Questions

**Q: Can you use double hashing to eliminate false positives?**
A: Yes — maintain two independent hash values with different bases and moduli. A collision in both is astronomically unlikely (probability ≈ 1/MOD₁/MOD₂). This effectively eliminates the need for character-by-character verification.

**Q: Why is Rabin-Karp preferred over KMP in some settings?**
A: Rabin-Karp is simpler to implement and naturally extends to 2D pattern matching (matching a 2D submatrix in a 2D matrix), where KMP has no straightforward 2D analog.

**Q: What base should you use for the rolling hash?**
A: A prime larger than the alphabet size. For lowercase letters (26 chars): base=31 or 37. For uppercase+lowercase (52 chars): base=53. For ASCII (128 chars): base=131.

---

## 10. Cross-Pattern Connections

- **P86 (KMP):** Both solve string matching; KMP is deterministic O(n+m), Rabin-Karp is probabilistic
- **P88 (Z-Algorithm):** Another O(n) exact string matching approach
- **P91 (Rolling Hash):** Same rolling hash technique extended to more complex problems
- **P61 (Binary Search on Answer):** Longest duplicate uses binary search on length + hash check
