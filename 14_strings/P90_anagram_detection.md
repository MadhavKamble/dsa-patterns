# P90 — Anagram Detection and Frequency Patterns

## 1. First-Timer Explanation

### What Is It?
**Anagram problems** involve checking if two strings have the same character frequencies, or finding all anagram occurrences of a pattern in text. The core tool is a **frequency array** (size 26 for lowercase) or **hash map**. Sliding window + frequency comparison is the key algorithmic technique.

### Fixed Window Frequency Match
```
Pattern "ab" in text "cbaebabacd":
freq_p = [1,1,0,...] (a:1, b:1)
Window [0,2)='cb': freq_w=[0,1,0,...,1,0] (b:1,c:1)
Slide: remove 'c', add 'a': freq_w=[1,1,0,...] == freq_p → match at 0
Slide: remove 'b', add 'e': no match
...etc
```

### Frequency Trick: Count Matches
```
Instead of comparing two 26-element arrays each window slide,
maintain a 'matches' counter:
- When freq_w[c] becomes equal to freq_p[c]: matches++
- When freq_w[c] was equal and now changes: matches--
- When matches == 26: all frequencies match → anagram found
```

### When to Use
- "Find all anagrams of p in s" → sliding window of size len(p)
- "Group anagrams" → sort each string as key, or frequency tuple as key
- "Valid anagram" → frequency comparison
- "Minimum window containing all characters" → variable-size sliding window
- "Check if strings are isomorphic" → bijective character mapping

### Common Mistakes
1. Case sensitivity: lowercase vs uppercase; usually lowercase only
2. Sliding window: when adding, always update matches AFTER incrementing; when removing, BEFORE decrementing
3. Group anagrams key: sorted string is the canonical form
4. Minimum window: use `count` for missing characters, not direct frequency comparison

---

## 2. Revision Card

**Recognition Signal:** "anagram", "permutation in string", "group anagrams", "same characters"

**Core Idea:** Fixed-size sliding window with 26-element frequency arrays. Maintain a `matches` counter (increments/decrements as characters enter/exit window). `matches == 26` signals an anagram.

**Trigger Keywords:** anagram, permutation, rearrange, frequency, group

**Complexity:** O(n) time, O(1) space (fixed 26-char alphabet)

---

## 3. Interview Tell Signs

- "All anagram positions of p in s" → sliding window size len(p), compare freq arrays
- "Group strings by anagram" → sort each string → same key if anagram
- "Check if permutation of p exists in s" → same as find anagram
- "Minimum characters to type" → character frequency
- "Isomorphic strings" → bijective mapping check with two maps
- "Word pattern" → map words to pattern symbols

---

## 4. C++ Template

```cpp
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

// ── Find All Anagrams ─────────────────────────────────────────────────────────
vector<int> findAnagrams(string s, string p) {
    vector<int> fp(26, 0), fw(26, 0);
    for (char c : p) fp[c-'a']++;
    int k = p.size(), matches = 0, n = s.size();
    // Initialize window
    for (int i = 0; i < k && i < n; i++) fw[s[i]-'a']++;
    for (int i = 0; i < 26; i++) if (fp[i] == fw[i]) matches++;
    vector<int> res;
    if (matches == 26) res.push_back(0);
    for (int i = k; i < n; i++) {
        // Add s[i]
        int add = s[i]-'a';
        if (fw[add] == fp[add]) matches--;
        fw[add]++;
        if (fw[add] == fp[add]) matches++;
        // Remove s[i-k]
        int rem = s[i-k]-'a';
        if (fw[rem] == fp[rem]) matches--;
        fw[rem]--;
        if (fw[rem] == fp[rem]) matches++;
        if (matches == 26) res.push_back(i - k + 1);
    }
    return res;
}

// ── Group Anagrams ────────────────────────────────────────────────────────────
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> groups;
    for (auto& s : strs) {
        string key = s; sort(key.begin(), key.end());
        groups[key].push_back(s);
    }
    vector<vector<string>> res;
    for (auto& [_, v] : groups) res.push_back(v);
    return res;
}

// ── Valid Anagram ─────────────────────────────────────────────────────────────
bool isAnagram(string s, string t) {
    if (s.size() != t.size()) return false;
    vector<int> freq(26, 0);
    for (char c : s) freq[c-'a']++;
    for (char c : t) { if (--freq[c-'a'] < 0) return false; }
    return true;
}

// ── Isomorphic Strings ────────────────────────────────────────────────────────
bool isIsomorphic(string s, string t) {
    unordered_map<char,char> st, ts;
    for (int i = 0; i < (int)s.size(); i++) {
        if (st.count(s[i]) && st[s[i]] != t[i]) return false;
        if (ts.count(t[i]) && ts[t[i]] != s[i]) return false;
        st[s[i]] = t[i]; ts[t[i]] = s[i];
    }
    return true;
}
```

---

## 5. How to Present in Interview

**Verbal Script (Find All Anagrams):**
> "Sliding window of size len(p). I maintain two frequency arrays and a `matches` count (number of character positions where the two arrays agree). When I add a character to the window, I check if it was previously matching (decrement) and if it's now matching (increment). Same for removal. When matches == 26, the window is an anagram."

**Verbal Script (Group Anagrams):**
> "Sort each string to get its canonical form — all anagrams sort to the same string. Use this sorted string as a hash map key. Each key maps to all strings with that character set."

**Checklist:**
- [ ] Initialize full first window before the sliding step
- [ ] Update matches CORRECTLY: decrement if was equal, increment if now equal
- [ ] Frequency array size 26 (lowercase); adjust for uppercase or full ASCII
- [ ] Group anagrams: sort string as key; or use frequency array as key
- [ ] Isomorphic: need two maps (both directions)

---

## 6. Problems

### Problem 1: Valid Anagram
**Difficulty:** Easy | **LC:** 242

```cpp
bool isAnagram(string s, string t) {
    if (s.size()!=t.size()) return false;
    vector<int> f(26,0);
    for (char c:s) f[c-'a']++;
    for (char c:t) if(--f[c-'a']<0) return false;
    return true;
}
// Time: O(n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Find All Anagrams in a String
**Difficulty:** Medium | **LC:** 438

```cpp
vector<int> findAnagrams(string s, string p) {
    vector<int> fp(26,0),fw(26,0); int matches=0,k=p.size(),n=s.size();
    for (char c:p) fp[c-'a']++;
    for (int i=0;i<k&&i<n;i++) fw[s[i]-'a']++;
    for (int i=0;i<26;i++) if(fp[i]==fw[i]) matches++;
    vector<int> res; if(matches==26) res.push_back(0);
    for (int i=k;i<n;i++) {
        int a=s[i]-'a'; if(fw[a]==fp[a]) matches--; fw[a]++; if(fw[a]==fp[a]) matches++;
        int r=s[i-k]-'a'; if(fw[r]==fp[r]) matches--; fw[r]--; if(fw[r]==fp[r]) matches++;
        if(matches==26) res.push_back(i-k+1);
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

### Problem 3: Group Anagrams
**Difficulty:** Medium | **LC:** 49

```cpp
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string,vector<string>> mp;
    for (auto& s:strs) { string k=s; sort(k.begin(),k.end()); mp[k].push_back(s); }
    vector<vector<string>> res;
    for (auto& [_,v]:mp) res.push_back(v);
    return res;
}
// Time: O(n*k*log k) k=avg string len | Space: O(nk)
// O(nk) alternative: use frequency count as key
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Isomorphic Strings
**Difficulty:** Easy | **LC:** 205

```cpp
bool isIsomorphic(string s, string t) {
    unordered_map<char,char> st,ts;
    for (int i=0;i<(int)s.size();i++) {
        if(st.count(s[i])&&st[s[i]]!=t[i]) return false;
        if(ts.count(t[i])&&ts[t[i]]!=s[i]) return false;
        st[s[i]]=t[i]; ts[t[i]]=s[i];
    }
    return true;
}
// Time: O(n) | Space: O(1) — at most 128 ASCII chars in each map
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Word Pattern
**Difficulty:** Easy | **LC:** 290

```cpp
bool wordPattern(string pattern, string s) {
    istringstream iss(s); vector<string> words;
    string w; while(iss>>w) words.push_back(w);
    if (pattern.size()!=words.size()) return false;
    unordered_map<char,string> cw; unordered_map<string,char> wc;
    for (int i=0;i<(int)pattern.size();i++) {
        char c=pattern[i]; string& wd=words[i];
        if(cw.count(c)&&cw[c]!=wd) return false;
        if(wc.count(wd)&&wc[wd]!=c) return false;
        cw[c]=wd; wc[wd]=c;
    }
    return true;
}
// Time: O(n) | Space: O(n)
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
    int lo=0,hi=0,start=0,minLen=INT_MAX;
    while (hi<(int)s.size()) {
        if (need[s[hi++]]-->0) missing--;
        while (!missing) {
            if (hi-lo<minLen) {minLen=hi-lo;start=lo;}
            if (need[s[lo++]]++==0) missing++;
        }
    }
    return minLen==INT_MAX?"":(s.substr(start,minLen));
}
// Time: O(n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** Find anagrams of "ab" in "eidbaooo". Initial window and first slide?
<details><summary>Reveal</summary>
fp[a]=1,fp[b]=1,others=0. Window "ei": fw[e]=1,fw[i]=1. matches: only positions where both=0 agree → 24 matches. 24≠26. Slide to "id": remove 'e'(was fw[e]=1,fp[e]=0→they were unequal→no change to matches), fw[e]=0 (now equal →matches++→25). Add 'd': fw[d]=0=fp[d]=0→matches++ →26? Wait: before add d: fp[d]=0,fw[d]=0→matches would be 26? No, remove i first. This is getting complex — matches tracks all 26 chars. Key point: "ba" at index 3 is first anagram at position 3.
</details>

**Drill 2:** Group anagrams for ["eat","tea","tan","ate","nat","bat"]. What are the groups?
<details><summary>Reveal</summary>
Sorted keys: "eat"→"aet", "tea"→"aet", "tan"→"ant", "ate"→"aet", "nat"→"ant", "bat"→"abt". Groups: "aet"→[eat,tea,ate], "ant"→[tan,nat], "abt"→[bat]. Three groups ✓.
</details>

**Drill 3:** Is "egg" isomorphic to "add"? Trace both maps.
<details><summary>Reveal</summary>
i=0: c='e',w='a'. st={e:a},ts={a:e}. i=1: c='g',w='d'. st={e:a,g:d},ts={a:e,d:g}. i=2: c='g',w='d'. st[g]=d==w='d' ✓. ts[d]=g==c='g' ✓. Return true ✓. ("egg"↔"add": e→a, g→d).
</details>

**Drill 4:** Minimum window of "ADOBECODEBANC" containing "ABC". Trace the missing counter.
<details><summary>Reveal</summary>
need[A]=1,need[B]=1,need[C]=1. missing=3. Expand: A→missing=2. D,O,B→missing=1. E,C→missing=0. Window "ADOBEC"[0..5]. Shrink: remove A→missing=1. lo=1. Expand: O→nothing. D,E,B→missing=0. Window "DOBECODEBA N C"... This is long to trace fully. The key insight: when missing==0, record window and try to shrink. Answer is "BANC" (len 4).
</details>

**Drill 5:** Why does `matches` count 26 even for characters with 0 frequency?
<details><summary>Reveal</summary>
For characters not in the pattern, `fp[c]=0`. Initially, `fw[c]=0` for all characters not yet in the window. So `fp[c]==fw[c]==0` → those positions match. As we add characters, if a non-pattern character enters the window, `fw[c]` becomes 1 ≠ 0 = fp[c], and matches decrements. So matches=26 requires ALL 26 frequencies to agree — including the "zero-count" characters matching zero.
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Space |
|---------|------|-------|
| Valid anagram | O(n) | O(1) |
| Find all anagrams | O(n) | O(1) |
| Group anagrams | O(n * k log k) | O(nk) |
| Isomorphic strings | O(n) | O(1) |
| Word pattern | O(n) | O(n) |
| Minimum window substring | O(n) | O(1) |

---

## 9. Common Follow-up Questions

**Q: Find all anagrams when strings contain uppercase and lowercase?**
A: Use a size-52 or size-128 frequency array. `c - 'A'` for uppercase (0-25), `c - 'a' + 26` for lowercase (26-51).

**Q: Can you group anagrams without sorting?**
A: Yes — use frequency count as key: e.g., build a string of 26 counts separated by '#': "1#0#0#...#1#...". This is O(n*k) instead of O(n*k*log k).

**Q: What is the difference between anagram and subsequence?**
A: An anagram is a rearrangement of ALL characters (same multiset). A subsequence is a subset of characters in order. Anagram = same frequency; subsequence = order-preserving subset.

---

## 10. Cross-Pattern Connections

- **P02 (Sliding Window):** Anagram detection IS a sliding window problem
- **P86 (KMP):** Exact string matching; anagram = frequency matching
- **P79 (Prefix Sums):** Frequency arrays are a form of prefix counting
- **P66 (Frequency Stack):** Frequency tracking is a general pattern across many problems
