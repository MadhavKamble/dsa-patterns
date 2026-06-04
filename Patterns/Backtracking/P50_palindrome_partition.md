# P50 — Palindrome Partitioning

## 1. First-Timer Explanation

### What Is It?
**Palindrome partitioning** is a classic backtracking + DP hybrid. The goal is to split a string into substrings where every part is a palindrome. We enumerate all valid splits using backtracking (try every possible cut point) and check palindrome validity using precomputed DP.

### Analogy
Cutting a ribbon into pieces, where every piece must read the same forwards and backwards. You try each cut position: if the piece so far is a valid palindrome, keep it and recurse on the rest. If not, don't cut there. Backtrack to try other cuts.

### Visual Walkthrough — "aab"
```
dfs(start=0, current=[])
├── cut at 1: "a" → palindrome → dfs(1, ["a"])
│   ├── cut at 2: "a" → palindrome → dfs(2, ["a","a"])
│   │   └── cut at 3: "b" → palindrome → RECORD ["a","a","b"]
│   └── cut at 3: "ab" → not palindrome, skip
└── cut at 2: "aa" → palindrome → dfs(2, ["aa"])
    └── cut at 3: "b" → palindrome → RECORD ["aa","b"]
└── cut at 3: "aab" → not palindrome, skip
```

### Palindrome Check Precomputation
Instead of checking `s[l..r]` in O(r-l+1) each time, precompute `isPalin[l][r]` in O(n²):
```
isPalin[i][i] = true
isPalin[i][i+1] = (s[i] == s[i+1])
isPalin[l][r] = (s[l] == s[r]) && isPalin[l+1][r-1]
```

### When to Use
- "Partition string into palindromes"
- "Minimum cuts to partition into palindromes" → DP
- "All palindromic partitions" → backtracking

### Common Mistakes
1. O(n) palindrome check inside backtracking → TLE; precompute instead
2. Not considering single-character partitions (every char is a palindrome)
3. For minimum cuts: don't enumerate all partitions; use 1D DP

---

## 2. Revision Card

**Recognition Signal:** "partition into palindromes", "split string where each part is palindrome"

**Core Idea:** Backtracking: try each cut `[start..i]`. If palindrome (precomputed), add to current, recurse from `i+1`. Record when `start == n`.

**Trigger Keywords:** palindrome, partition, split, cut, segment

**Complexity:**
| Problem | Time | Space |
|---------|------|-------|
| All partitions | O(n × 2^n) | O(n²) |
| Minimum cuts | O(n²) | O(n²) |

---

## 3. Interview Tell Signs

- "All ways to split string into palindromes" → backtracking + palindrome DP
- "Minimum cuts for palindrome partition" → pure DP (no backtracking)
- "Count palindromic substrings" → expand-from-center or DP

---

## 4. C++ Template

```cpp
#include <vector>
#include <string>
using namespace std;

vector<vector<string>> partition(string s) {
    int n = s.size();
    // Precompute isPalin[l][r]
    vector<vector<bool>> isPalin(n, vector<bool>(n, false));
    for (int i = 0; i < n; i++) isPalin[i][i] = true;
    for (int i = 0; i + 1 < n; i++) isPalin[i][i+1] = (s[i] == s[i+1]);
    for (int len = 3; len <= n; len++)
        for (int l = 0; l + len - 1 < n; l++) {
            int r = l + len - 1;
            isPalin[l][r] = (s[l] == s[r]) && isPalin[l+1][r-1];
        }
    
    vector<vector<string>> res;
    vector<string> cur;
    
    function<void(int)> dfs = [&](int start) {
        if (start == n) { res.push_back(cur); return; }
        for (int end = start; end < n; end++) {
            if (!isPalin[start][end]) continue;
            cur.push_back(s.substr(start, end - start + 1));
            dfs(end + 1);
            cur.pop_back();
        }
    };
    
    dfs(0);
    return res;
}
```

---

## 5. How to Present in Interview

**Verbal Script:**
> "I need to find all ways to split the string into palindromes. I'll precompute a 2D boolean table `isPalin[l][r]` in O(n²) so I can check any substring in O(1). Then I backtrack: try each possible end point for the current substring. If it's a palindrome, add it, recurse on the rest, and backtrack. Record when I've consumed the entire string."

**Checklist:**
- [ ] Precompute `isPalin` table — mention DP
- [ ] DFS: try all end positions from start
- [ ] Skip if not palindrome
- [ ] Record when start == n
- [ ] Mention minimum cuts uses 1D DP instead of backtracking

---

## 6. Problems

### Problem 1: Palindrome Partitioning (All Partitions)
**Difficulty:** Medium | **LC:** 131

```cpp
vector<vector<string>> partition(string s) {
    int n = s.size();
    vector<vector<bool>> dp(n, vector<bool>(n, false));
    for (int i = n-1; i >= 0; i--)
        for (int j = i; j < n; j++)
            dp[i][j] = (s[i] == s[j]) && (j - i < 2 || dp[i+1][j-1]);
    
    vector<vector<string>> res;
    vector<string> cur;
    function<void(int)> dfs = [&](int start) {
        if (start == n) { res.push_back(cur); return; }
        for (int end = start; end < n; end++) {
            if (!dp[start][end]) continue;
            cur.push_back(s.substr(start, end-start+1));
            dfs(end + 1);
            cur.pop_back();
        }
    };
    dfs(0);
    return res;
}
// Time: O(n * 2^n) | Space: O(n^2)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Palindrome Partitioning II (Minimum Cuts)
**Difficulty:** Hard | **LC:** 132

**Approach:** DP. `minCut[i]` = minimum cuts for `s[0..i]`. Transition: for each j ≤ i, if `s[j..i]` is palindrome, `minCut[i] = min(minCut[i], minCut[j-1] + 1)`.

```cpp
int minCut(string s) {
    int n = s.size();
    // Precompute palindrome table
    vector<vector<bool>> dp(n, vector<bool>(n, false));
    for (int i = n-1; i >= 0; i--)
        for (int j = i; j < n; j++)
            dp[i][j] = (s[i] == s[j]) && (j - i < 2 || dp[i+1][j-1]);
    
    vector<int> cuts(n, INT_MAX);
    for (int i = 0; i < n; i++) {
        if (dp[0][i]) { cuts[i] = 0; continue; } // whole prefix is palindrome
        for (int j = 1; j <= i; j++)
            if (dp[j][i])
                cuts[i] = min(cuts[i], cuts[j-1] + 1);
    }
    return cuts[n-1];
}
// Time: O(n^2) | Space: O(n^2)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Longest Palindromic Substring
**Difficulty:** Medium | **LC:** 5

**Approach:** Expand from center. For each center (n centers for odd, n-1 for even), expand outward.

```cpp
string longestPalindrome(string s) {
    int n = s.size(), start = 0, maxLen = 1;
    
    auto expand = [&](int l, int r) {
        while (l >= 0 && r < n && s[l] == s[r]) { l--; r++; }
        if (r - l - 1 > maxLen) { maxLen = r - l - 1; start = l + 1; }
    };
    
    for (int i = 0; i < n; i++) {
        expand(i, i);   // odd length
        expand(i, i+1); // even length
    }
    return s.substr(start, maxLen);
}
// Time: O(n^2) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Count Palindromic Substrings
**Difficulty:** Medium | **LC:** 647

**Approach:** Expand from each center, count valid palindromes.

```cpp
int countSubstrings(string s) {
    int n = s.size(), count = 0;
    auto expand = [&](int l, int r) {
        while (l >= 0 && r < n && s[l] == s[r]) { count++; l--; r++; }
    };
    for (int i = 0; i < n; i++) { expand(i,i); expand(i,i+1); }
    return count;
}
// Time: O(n^2) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** For palindrome partitioning, why precompute `isPalin` instead of checking inline?
<details><summary>Reveal</summary>
Inline check is O(n) per substring. With O(n²) calls in backtracking, total becomes O(n³). Precomputing takes O(n²) once, making each check O(1), reducing total to O(n × 2^n) — a big improvement for the palindrome check part.
</details>

**Drill 2:** Minimum cuts: why is backtracking too slow and DP needed?
<details><summary>Reveal</summary>
Backtracking explores all 2^n partitions. Minimum cuts DP reduces this to O(n²): `cuts[i] = min(cuts[j-1] + 1) for all j where s[j..i] is palindrome`. No need to enumerate all valid partitions — just track the minimum.
</details>

**Drill 3:** What's the `dp[i][j]` recurrence for palindrome detection?
<details><summary>Reveal</summary>
`dp[i][j] = (s[i] == s[j]) && (j - i < 2 || dp[i+1][j-1])`. Base cases: single char always true; two chars if equal. Must fill from short to long (or bottom-right to top-left) to ensure `dp[i+1][j-1]` is computed first.
</details>

**Drill 4:** String "racecar". List all palindromic substrings.
<details><summary>Reveal</summary>
Single chars: r,a,c,e,c,a,r (7). Two chars: none equal adjacent. Multi: "aceca" (pos 1-5), "racecar" (0-6), "cec" (2-4). Total: 10. Check with expand-from-center.
</details>

**Drill 5:** For "aab", the minimum cuts answer is 1. Verify with DP.
<details><summary>Reveal</summary>
cuts[0]="a" palindrome → 0. cuts[1]="aa" palindrome → 0. cuts[2]="aab" not palindrome; check j=1: "b" palindrome, cuts[0]+1=1; j=2: "ab" not palindrome. cuts[2]=1. ✓
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Space |
|---------|------|-------|
| All palindromic partitions | O(n × 2^n) | O(n²) |
| Minimum cuts | O(n²) | O(n²) |
| Longest palindromic substring | O(n²) | O(1) |
| Count palindromic substrings | O(n²) | O(1) |
| Manacher's algorithm (all) | O(n) | O(n) |

---

## 9. Common Follow-up Questions

**Q: Can you find the longest palindromic substring in O(n)?**
A: Yes — Manacher's algorithm. Uses a "mirror" trick with a center and radius array. O(n) time, O(n) space.

**Q: Palindrome partitioning with k parts exactly?**
A: Add parameter `partsLeft` to DFS. Prune when remaining string can't yield `partsLeft` palindromes.

**Q: Stream of characters — maintain longest palindrome?**
A: Hard. No known O(1) update. Offline approaches (Palindrome Tree / Eertree) handle this in O(n) total for all updates.

---

## 10. Cross-Pattern Connections

- **P33 (String DP):** Palindrome DP is core string DP; LPS is in P33
- **P46 (Subsets):** Same backtracking skeleton; palindrome validity = combination constraint
- **P35 (Interval DP):** Palindrome checks fill an interval DP table; similar structure
- **P86 (String Matching):** Manacher's is an advanced string algorithm for palindromes
