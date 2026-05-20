# P91 — Rolling Hash and String Applications

## 1. First-Timer Explanation

### What Is It?
**Rolling hash** computes hashes of fixed-size windows incrementally: instead of recomputing from scratch, it removes the leftmost character's contribution and adds the new rightmost character in O(1). This enables O(n) solutions to problems that would otherwise require O(n·k) per-window comparisons.

### Rolling Hash Formula (Polynomial)
```
Window [l, r] hash using base B and modulus MOD:
h = s[l]*B^(k-1) + s[l+1]*B^(k-2) + ... + s[r]*B^0

Slide: remove s[l], add s[r+1]:
h_new = (h - s[l] * B^(k-1)) * B + s[r+1]

All operations modulo MOD to prevent overflow.
```

### Double Hashing to Reduce Collisions
```
Use two independent (base, mod) pairs:
  (B1=31, M1=10^9+7) and (B2=37, M2=10^9+9)
Collision probability drops from ~1/M to ~1/(M1*M2) ≈ 10^-18
```

### When to Use
- "Longest repeated substring" → binary search + rolling hash
- "Find if string A contains a permutation of B" → fixed-window rolling hash (see P90)
- "Count distinct substrings" → rolling hash + set
- "Longest common substring of two strings" → binary search + rolling hash on both
- "Plagiarism detection" or "near-duplicate detection" → rolling hash

### Common Mistakes
1. Not adding MOD before taking % to handle negative values: `(h - val + MOD) % MOD`
2. Forgetting to precompute `pow[k-1]` — recomputing it each slide is O(k)
3. Using `int` instead of `long long` — products overflow
4. Off-by-one in window boundaries when sliding

---

## 2. Revision Card

**Recognition Signal:** "repeated substring", "longest common substring", "distinct substrings"

**Core Idea:** Hash window in O(1) per slide. `h_new = (h - s[l]*pw[k-1]) * B + s[r+1]`. Binary search on window length, hash set for seen windows.

**Trigger Keywords:** rolling hash, window hash, slide, repeated, common substring

**Complexity:** O(n log n) for binary search + rolling hash; O(n) for single-pass

---

## 3. Interview Tell Signs

- "Longest repeated/duplicate substring" → binary search on length + rolling hash set
- "Longest common substring of S and T" → binary search + check if any window of length mid in S matches any window in T
- "Count distinct substrings of length k" → rolling hash set, count unique hashes
- "All repeated substrings" → rolling hash set, collect collisions

---

## 4. C++ Template

```cpp
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

const long long B1 = 31, M1 = 1e9+7;
const long long B2 = 37, M2 = 1e9+9;

// ── Single-Pass Rolling Hash ──────────────────────────────────────────────────
// Returns set of hashes of all windows of length k in s
unordered_set<long long> windowHashes(const string& s, int k) {
    int n = s.size();
    long long h = 0, pw = 1;
    unordered_set<long long> seen;
    for (int i = 0; i < k; i++) { h = (h*B1 + (s[i]-'a'+1)) % M1; if(i>0) pw=pw*B1%M1; }
    seen.insert(h);
    for (int i = k; i < n; i++) {
        h = (h - (s[i-k]-'a'+1)*pw%M1 + M1) * B1 % M1;
        h = (h + (s[i]-'a'+1)) % M1;
        seen.insert(h);
    }
    return seen;
}

// ── Longest Common Substring ──────────────────────────────────────────────────
string longestCommonSubstring(const string& a, const string& b) {
    int lo = 0, hi = min(a.size(), b.size()), bestLen = 0, bestPos = 0;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        auto hashesA = windowHashes(a, mid);
        // Check if any window of b of length mid has same hash
        int n = b.size();
        long long h = 0, pw = 1;
        for (int i = 0; i < mid; i++) { h=(h*B1+(b[i]-'a'+1))%M1; if(i>0) pw=pw*B1%M1; }
        bool found = hashesA.count(h);
        for (int i = mid; i < n && !found; i++) {
            h=(h-(b[i-mid]-'a'+1)*pw%M1+M1)*B1%M1;
            h=(h+(b[i]-'a'+1))%M1;
            found = hashesA.count(h);
        }
        if (found) { bestLen = mid; bestPos = /* find actual position */ 0; lo = mid + 1; }
        else hi = mid - 1;
    }
    return a.substr(bestPos, bestLen); // simplified; need actual position tracking
}

// ── Count Distinct Substrings of Length K ─────────────────────────────────────
int countDistinctSubstrings(const string& s, int k) {
    return windowHashes(s, k).size();
}
```

---

## 5. How to Present in Interview

**Verbal Script:**
> "Rolling hash lets me compute each window's hash in O(1) by maintaining the hash incrementally: remove the leftmost character's contribution (`h -= s[l] * B^(k-1)`) and add the new rightmost character. I keep track of all seen hashes in a set. To find the longest repeated substring, I binary search on the length and check if any hash appears twice. O(n log n) total."

**Checklist:**
- [ ] Precompute `pw = B^(k-1) % MOD` before the sliding loop
- [ ] `+MOD` before `%` to prevent negative values
- [ ] Use `long long` for all intermediate values
- [ ] Verify hash matches with character comparison to avoid false positives
- [ ] For critical applications, use double hashing

---

## 6. Problems

### Problem 1: Longest Duplicate Substring
**Difficulty:** Hard | **LC:** 1044

```cpp
string longestDupSubstring(string s) {
    int n=s.size(); long long mod=1e9+7,base=31;
    auto check=[&](int len)->int{
        long long h=0,pw=1;
        for(int i=0;i<len;i++){h=(h*base+(s[i]-'a'+1))%mod;if(i>0)pw=pw*base%mod;}
        unordered_set<long long> seen; seen.insert(h);
        for(int i=1;i+len<=n;i++){
            h=(h-(s[i-1]-'a'+1)*pw%mod+mod)*base%mod;
            h=(h+(s[i+len-1]-'a'+1))%mod;
            if(seen.count(h)) return i;
            seen.insert(h);
        }
        return -1;
    };
    int lo=1,hi=n-1,bestStart=-1,bestLen=0;
    while(lo<=hi){int mid=lo+(hi-lo)/2,pos=check(mid);if(pos!=-1){bestStart=pos;bestLen=mid;lo=mid+1;}else hi=mid-1;}
    return bestLen?s.substr(bestStart,bestLen):"";
}
// Time: O(n log n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Distinct Echo Substrings
**Difficulty:** Hard | **LC:** 1316

**Approach:** Check if substring of length 2k is an echo: first half == second half.

```cpp
int distinctEchoSubstrings(string text) {
    int n=text.size(); long long mod=1e9+7, base=31;
    // Precompute prefix hashes
    vector<long long> h(n+1,0),pw(n+1,1);
    for(int i=0;i<n;i++){h[i+1]=(h[i]*base+(text[i]-'a'+1))%mod; pw[i+1]=pw[i]*base%mod;}
    auto getHash=[&](int l,int r)->long long{
        return(h[r+1]-h[l]*pw[r-l+1]%mod+mod*2)%mod;
    };
    unordered_set<long long> seen;
    int res=0;
    for(int len=1;len*2<=n;len++){
        for(int i=0;i+2*len-1<n;i++){
            if(getHash(i,i+len-1)==getHash(i+len,i+2*len-1)){
                long long key=getHash(i,i+2*len-1);
                if(!seen.count(key)){seen.insert(key);res++;}
            }
        }
    }
    return res;
}
// Time: O(n²) | Space: O(n²)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Check if Two String Arrays are Equivalent
**Difficulty:** Easy | **LC:** 1662

```cpp
bool arrayStringsAreEqual(vector<string>& w1, vector<string>& w2) {
    string a="",b="";
    for(auto& s:w1) a+=s;
    for(auto& s:w2) b+=s;
    return a==b;
}
// Time: O(n) | Space: O(n)
// Alternative: use two indices (i1,j1) into w1[i1][j1], compare character by character
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Count Number of Homogenous Substrings
**Difficulty:** Medium | **LC:** 1759

```cpp
int countHomogenous(string s) {
    long long res=0, cnt=1, mod=1e9+7;
    for(int i=1;i<(int)s.size();i++){
        if(s[i]==s[i-1]) cnt++;
        else cnt=1;
        res=(res+cnt)%mod;
    }
    return (res+1)%mod; // +1 for the first character
}
// Actually: count runs. For run of length k, it contributes k*(k+1)/2 substrings.
// Time: O(n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Longest Happy Prefix
**Difficulty:** Hard | **LC:** 1392

**Approach:** Uses KMP LPS to find longest prefix which is also suffix (border) — same as LPS.

```cpp
string longestPrefix(string s) {
    int n=s.size();
    vector<int> lps(n,0);
    for(int i=1,len=0;i<n;){
        if(s[i]==s[len]) lps[i++]=++len;
        else if(len>0) len=lps[len-1];
        else lps[i++]=0;
    }
    return s.substr(0,lps[n-1]);
}
// Time: O(n) | Space: O(n)
// lps[n-1] = length of longest border (prefix = suffix)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: Find the Longest Substring Containing Vowels in Even Counts
**Difficulty:** Medium | **LC:** 1371

**Approach:** XOR-based bitmask for vowel parity. Same prefix XOR trick as subarray sum.

```cpp
int findTheLongestSubstring(string s) {
    string vowels = "aeiou";
    unordered_map<int,int> seen; seen[0]=-1;
    int mask=0, res=0;
    for(int i=0;i<(int)s.size();i++){
        for(int v=0;v<5;v++) if(s[i]==vowels[v]) mask^=(1<<v);
        if(seen.count(mask)) res=max(res,i-seen[mask]);
        else seen[mask]=i;
    }
    return res;
}
// Time: O(n) | Space: O(2^5)=O(1)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** Roll hash of "abcd" with base=10, window k=2. Show h after each slide.
<details><summary>Reveal</summary>
h("ab")=(0*10+1)*10+2=12. pw=10 (base^(k-1)=10^1=10). Slide to "bc": h=(12-1*10)*10+3=(12-10)*10+3=2*10+3=23. Slide to "cd": h=(23-2*10)*10+4=(3)*10+4=34. Hashes: [12,23,34] corresponding to "ab","bc","cd".
</details>

**Drill 2:** Longest duplicate substring in "banana". At length 3, what is the hash set and is there a collision?
<details><summary>Reveal</summary>
Substrings of length 3: "ban","ana","nan","ana". Hashes computed: h("ban")=some value, h("ana")=some value, h("nan")=different, then h("ana") again → same hash as "ana". Collision detected at position 3. check(3) returns 3. Binary search continues with lo=4. Length 4: "bana","anan","nana" — no repeats. hi=3. bestLen=3, s.substr(3,3)="ana" ✓.
</details>

**Drill 3:** Longest substring with all vowels in even count for "eleetminicoworoep". What is the initial mask?
<details><summary>Reveal</summary>
mask starts at 0 (all vowels have even count = 0). seen={0:-1}. We toggle bits as we encounter vowels. The trick is: two positions with the same mask means all vowels between them have even total count. If we see mask=0 again, the whole prefix has even vowel counts (possibly the longest substring). Answer for this input is 13.
</details>

**Drill 4:** Why does double hashing drastically reduce collision probability?
<details><summary>Reveal</summary>
For a single hash with MOD=10^9+7, probability of collision for any two distinct strings is ≈ 1/MOD ≈ 10^-9. With double hashing (two independent bases and mods), a collision requires BOTH hashes to match simultaneously. Probability ≈ 1/(M1*M2) ≈ 1/(10^9 * 10^9) ≈ 10^-18. For n substrings, expected false positives ≈ n²/M. With n=10^5: single hash has ~10^10/10^9=10 expected collisions; double hash has ~10^10/10^18=10^-8 expected collisions (essentially zero).
</details>

**Drill 5:** Longest happy prefix for "level". LPS walk.
<details><summary>Reveal</summary>
s="level" (n=5). i=1,len=0: 'e'≠'l'→lps[1]=0,i=2. i=2,len=0: 'v'≠'l'→lps[2]=0,i=3. i=3,len=0: 'e'≠'l'→lps[3]=0,i=4. i=4,len=0: 'l'=='l'→lps[4]=1,len=1,i=5. Done. lps[4]=1. Longest happy prefix = s.substr(0,1)="l" ✓ (prefix "l" equals suffix "l" in "level").
</details>

---

## 8. Complexity Cheatsheet

| Operation | Time | Space |
|-----------|------|-------|
| Build rolling hash (one window) | O(k) | O(1) |
| Slide hash one step | O(1) | O(1) |
| All windows of length k | O(n) | O(n) |
| Longest duplicate (binary search) | O(n log n) | O(n) |
| Longest common substring | O((n+m) log min(n,m)) | O(n) |

---

## 9. Common Follow-up Questions

**Q: How do you avoid false positives in rolling hash?**
A: When hashes match, verify with character-by-character comparison O(k). Or use double hashing to make collisions astronomically unlikely. In competitive programming, double hashing without verification is common.

**Q: Can rolling hash handle updates (character changes)?**
A: Not directly — rolling hash is designed for sliding windows, not arbitrary updates. For updates, use a Fenwick tree of hash contributions.

**Q: What about 2D rolling hash (matrix pattern matching)?**
A: Hash each row with 1D rolling hash, then hash the column of row-hashes. Two nested rolling hashes give O(1) hash per submatrix after O(nm) preprocessing.

---

## 10. Cross-Pattern Connections

- **P87 (Rabin-Karp):** Rolling hash is the core of Rabin-Karp algorithm
- **P79 (Prefix Sums):** Prefix polynomial hash is the multiplicative analog of prefix sum
- **P61 (Binary Search on Answer):** Binary search on window length + hash check
- **P90 (Anagram):** Fixed-window frequency matching is the non-hash alternative to rolling hash
