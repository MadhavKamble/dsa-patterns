# P92 — Advanced String Patterns

## 1. First-Timer Explanation

### What Is It?
**Advanced string** problems apply dynamic programming, stack-based parsing, or multi-step string manipulation. Key patterns: edit distance (alignment DP), string compression (run-length), regular expression matching, wildcard matching, and string interleaving.

### Edit Distance (Levenshtein)
```
dp[i][j] = min operations to convert s[0..i-1] to t[0..j-1]
Base: dp[i][0]=i (delete i chars), dp[0][j]=j (insert j chars)

If s[i-1]==t[j-1]: dp[i][j] = dp[i-1][j-1]  (no operation needed)
Else:              dp[i][j] = 1 + min(
                     dp[i-1][j],   // delete from s
                     dp[i][j-1],   // insert into s (delete from t)
                     dp[i-1][j-1]  // replace
                   )
```

### Wildcard Matching
```
'?' matches any single character
'*' matches any sequence (including empty)

dp[i][j] = true if pattern[0..i-1] matches text[0..j-1]
If p[i-1]=='*': dp[i][j] = dp[i-1][j] (use *) || dp[i][j-1] (extend *)
If p[i-1]=='?' or matches: dp[i][j] = dp[i-1][j-1]
```

### When to Use
- "Edit distance / Levenshtein" → alignment DP
- "Wildcard/Regex matching" → 2D DP with special state transitions
- "String interleaving" → 2D DP (is s3 interleaving of s1, s2?)
- "Longest common subsequence" → classic DP
- "String compression" → greedy run-length

### Common Mistakes
1. Edit distance: `dp[0][j]=j` and `dp[i][0]=i` (base cases)
2. Wildcard `*`: `dp[i][j] = dp[i-1][j] || dp[i][j-1]` (empty or extend)
3. Regex `.`: matches exactly one; `*` in regex means "zero or more of preceding"
4. Interleaving: `dp[i][j]` uses `s3[i+j-1]`, not `s3[i]` or `s3[j]`

---

## 2. Revision Card

**Recognition Signal:** "edit distance", "wildcard match", "interleaving strings", "regex match"

**Core Idea:** 2D DP where `dp[i][j]` represents a relationship between prefixes of two strings. Base cases initialize row/column 0. Transition depends on equality or wildcard rules.

**Trigger Keywords:** edit distance, Levenshtein, wildcard, regex, interleave, LCS

**Complexity:** O(m×n) time and space; O(n) space with rolling array optimization

---

## 3. Interview Tell Signs

- "Minimum edit distance" → Levenshtein DP
- "Does pattern match with ? and *" → wildcard DP
- "Does pattern match with . and *" → regex DP (slightly different: * means 0+ of preceding)
- "Longest common subsequence" → `dp[i][j] = dp[i-1][j-1]+1 if match, else max(dp[i-1][j], dp[i][j-1])`
- "Interleaving strings" → 2D DP with character choice
- "String compression" → count consecutive characters

---

## 4. C++ Template

```cpp
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// ── Edit Distance ─────────────────────────────────────────────────────────────
int minDistance(string s, string t) {
    int m = s.size(), n = t.size();
    vector<vector<int>> dp(m+1, vector<int>(n+1));
    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int j = 0; j <= n; j++) dp[0][j] = j;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            dp[i][j] = s[i-1]==t[j-1] ? dp[i-1][j-1]
                      : 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
    return dp[m][n];
}

// ── Wildcard Matching ─────────────────────────────────────────────────────────
bool isMatch(string s, string p) {
    int m = s.size(), n = p.size();
    vector<vector<bool>> dp(m+1, vector<bool>(n+1, false));
    dp[0][0] = true;
    for (int j = 1; j <= n; j++) dp[0][j] = p[j-1]=='*' && dp[0][j-1];
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++) {
            if (p[j-1] == '*') dp[i][j] = dp[i-1][j] || dp[i][j-1]; // match 1+ or 0
            else dp[i][j] = dp[i-1][j-1] && (p[j-1]=='?' || p[j-1]==s[i-1]);
        }
    return dp[m][n];
}

// ── Regular Expression Matching (. and *) ─────────────────────────────────────
bool isMatchRegex(string s, string p) {
    int m = s.size(), n = p.size();
    vector<vector<bool>> dp(m+1, vector<bool>(n+1, false));
    dp[0][0] = true;
    for (int j = 2; j <= n; j++) dp[0][j] = p[j-1]=='*' && dp[0][j-2];
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++) {
            if (p[j-1] == '*') {
                dp[i][j] = dp[i][j-2] // use * as zero occurrences
                    || (dp[i-1][j] && (p[j-2]=='.' || p[j-2]==s[i-1])); // use * as one more
            } else {
                dp[i][j] = dp[i-1][j-1] && (p[j-1]=='.' || p[j-1]==s[i-1]);
            }
        }
    return dp[m][n];
}

// ── Interleaving Strings ──────────────────────────────────────────────────────
bool isInterleave(string s1, string s2, string s3) {
    int m=s1.size(), n=s2.size();
    if (m+n != (int)s3.size()) return false;
    vector<vector<bool>> dp(m+1, vector<bool>(n+1, false));
    dp[0][0] = true;
    for (int i=1;i<=m;i++) dp[i][0]=dp[i-1][0]&&s1[i-1]==s3[i-1];
    for (int j=1;j<=n;j++) dp[0][j]=dp[0][j-1]&&s2[j-1]==s3[j-1];
    for (int i=1;i<=m;i++) for (int j=1;j<=n;j++)
        dp[i][j]=(dp[i-1][j]&&s1[i-1]==s3[i+j-1])||(dp[i][j-1]&&s2[j-1]==s3[i+j-1]);
    return dp[m][n];
}
```

---

## 5. How to Present in Interview

**Verbal Script (Edit Distance):**
> "2D DP. `dp[i][j]` = edit distance between `s[0..i-1]` and `t[0..j-1]`. Base cases: `dp[i][0]=i`, `dp[0][j]=j`. Transition: if characters match, copy diagonal. Otherwise, 1 + minimum of delete (from s), insert (into s), or replace."

**Verbal Script (Wildcard/Regex):**
> "For wildcard `*`: `dp[i][j] = dp[i-1][j]` (match one more char with `*`) OR `dp[i][j-1]` (use `*` as empty). For regex `.*`: check if the preceding char (p[j-2]) matches s[i-1], and if so, use `dp[i-1][j]`; or use `*` as zero occurrences → `dp[i][j-2]`."

**Checklist:**
- [ ] Edit distance: base cases dp[i][0]=i, dp[0][j]=j
- [ ] Wildcard *: `dp[0][j]` init: all `*`s at start match empty string (dp[0][j]=dp[0][j-1])
- [ ] Regex `.*`: `dp[0][j] = dp[0][j-2]` when p[j-1]=='*'
- [ ] Interleaving: use `s3[i+j-1]` (combined position)
- [ ] Space optimization: use 1D rolling array when only previous row needed

---

## 6. Problems

### Problem 1: Edit Distance
**Difficulty:** Hard | **LC:** 72

```cpp
int minDistance(string s, string t) {
    int m=s.size(),n=t.size();
    vector<vector<int>> dp(m+1,vector<int>(n+1));
    for(int i=0;i<=m;i++) dp[i][0]=i;
    for(int j=0;j<=n;j++) dp[0][j]=j;
    for(int i=1;i<=m;i++) for(int j=1;j<=n;j++)
        dp[i][j]=s[i-1]==t[j-1]?dp[i-1][j-1]:1+min({dp[i-1][j],dp[i][j-1],dp[i-1][j-1]});
    return dp[m][n];
}
// Time: O(m*n) | Space: O(m*n); optimize to O(n) with rolling row
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Wildcard Matching
**Difficulty:** Hard | **LC:** 44

```cpp
bool isMatch(string s, string p) {
    int m=s.size(),n=p.size();
    vector<vector<bool>> dp(m+1,vector<bool>(n+1,false));
    dp[0][0]=true;
    for(int j=1;j<=n;j++) dp[0][j]=p[j-1]=='*'&&dp[0][j-1];
    for(int i=1;i<=m;i++) for(int j=1;j<=n;j++) {
        if(p[j-1]=='*') dp[i][j]=dp[i-1][j]||dp[i][j-1];
        else dp[i][j]=dp[i-1][j-1]&&(p[j-1]=='?'||p[j-1]==s[i-1]);
    }
    return dp[m][n];
}
// Time: O(m*n) | Space: O(m*n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Regular Expression Matching
**Difficulty:** Hard | **LC:** 10

```cpp
bool isMatch(string s, string p) {
    int m=s.size(),n=p.size();
    vector<vector<bool>> dp(m+1,vector<bool>(n+1,false));
    dp[0][0]=true;
    for(int j=2;j<=n;j++) dp[0][j]=p[j-1]=='*'&&dp[0][j-2];
    for(int i=1;i<=m;i++) for(int j=1;j<=n;j++) {
        if(p[j-1]=='*')
            dp[i][j]=dp[i][j-2]||(dp[i-1][j]&&(p[j-2]=='.'||p[j-2]==s[i-1]));
        else
            dp[i][j]=dp[i-1][j-1]&&(p[j-1]=='.'||p[j-1]==s[i-1]);
    }
    return dp[m][n];
}
// Time: O(m*n) | Space: O(m*n)
// KEY DIFFERENCE from wildcard: '*' refers to preceding char, not standalone
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Interleaving String
**Difficulty:** Medium | **LC:** 97

```cpp
bool isInterleave(string s1, string s2, string s3) {
    int m=s1.size(),n=s2.size();
    if(m+n!=(int)s3.size()) return false;
    vector<vector<bool>> dp(m+1,vector<bool>(n+1,false));
    dp[0][0]=true;
    for(int i=1;i<=m;i++) dp[i][0]=dp[i-1][0]&&s1[i-1]==s3[i-1];
    for(int j=1;j<=n;j++) dp[0][j]=dp[0][j-1]&&s2[j-1]==s3[j-1];
    for(int i=1;i<=m;i++) for(int j=1;j<=n;j++)
        dp[i][j]=(dp[i-1][j]&&s1[i-1]==s3[i+j-1])||(dp[i][j-1]&&s2[j-1]==s3[i+j-1]);
    return dp[m][n];
}
// Time: O(m*n) | Space: O(m*n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: String Compression
**Difficulty:** Medium | **LC:** 443

```cpp
int compress(vector<char>& chars) {
    int write=0, i=0, n=chars.size();
    while (i<n) {
        char c=chars[i]; int cnt=0;
        while (i<n&&chars[i]==c){i++;cnt++;}
        chars[write++]=c;
        if (cnt>1) { string s=to_string(cnt); for(char d:s) chars[write++]=d; }
    }
    return write;
}
// Time: O(n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: Decode String
**Difficulty:** Medium | **LC:** 394

```cpp
string decodeString(string s) {
    stack<pair<string,int>> stk; // (current_string, repeat_count)
    string cur; int num=0;
    for (char c:s) {
        if (isdigit(c)) num=num*10+(c-'0');
        else if (c=='[') { stk.push({cur,num}); cur=""; num=0; }
        else if (c==']') {
            auto [prev,k]=stk.top(); stk.pop();
            string rep="";
            for(int i=0;i<k;i++) rep+=cur;
            cur=prev+rep;
        } else cur+=c;
    }
    return cur;
}
// Time: O(n * max_repeat) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** Edit distance between "horse" and "ros". Fill dp[1][1] and dp[2][2].
<details><summary>Reveal</summary>
dp[0]=[0,1,2,3]. dp[1][0]=1. dp[1][1]: s[0]='h'≠t[0]='r' → 1+min(dp[0][1]=1,dp[1][0]=1,dp[0][0]=0)=1. dp[2][0]=2. dp[2][1]: s[1]='o',t[0]='r'. ≠ → 1+min(dp[1][1]=1,dp[2][0]=2,dp[1][0]=1)=2. dp[2][2]: s[1]='o',t[1]='o'. == → dp[1][1]=1. dp[2][2]=1.
</details>

**Drill 2:** Wildcard match "aa" with "a*". Trace dp[2][2].
<details><summary>Reveal</summary>
s="aa",p="a*". dp[0][0]=T. dp[0][1]:p[0]='a'≠'*'→F. dp[0][2]:p[1]='*'→dp[0][1]=F→F. dp[1][0]=F. dp[1][1]: p[0]='a'==s[0]='a',dp[0][0]=T→T. dp[1][2]: p[1]='*'→dp[0][2]=F or dp[1][1]=T→T. dp[2][0]=F. dp[2][1]: p[0]='a'==s[1]='a',dp[1][0]=F→F. dp[2][2]: p[1]='*'→dp[1][2]=T or (dp[2][1]=F)→T. Match=true ✓.
</details>

**Drill 3:** Regex match "aa" with "a*". How does `.*` differ from wildcard `*`?
<details><summary>Reveal</summary>
In regex, `*` means "zero or more of PRECEDING character/group". So "a*" means "zero or more 'a's". dp[0][2]: p[1]='*' → dp[0][j-2]=dp[0][0]=T → dp[0][2]=T. This is the key difference: in regex, `*` at j means look at p[j-2] (the preceding element), while in wildcard, `*` is standalone. For "aa" vs "a*": dp[2][2]→p[1]='*': dp[2][0]=F, OR dp[1][2]&&p[0]='a'==s[1]='a': dp[1][2]→p[1]='*':dp[1][0]=F OR dp[0][2]=T&&(p[0]='a'==s[0]='a'):T. So dp[1][2]=T. dp[2][2]=T ✓.
</details>

**Drill 4:** Is "aab" an interleaving of "ab" and "a"? Trace dp.
<details><summary>Reveal</summary>
s1="ab",s2="a",s3="aab". m=2,n=1,m+n=3=|s3|. dp[0][0]=T. dp[1][0]:s1[0]='a'==s3[0]='a',dp[0][0]=T→T. dp[2][0]:s1[1]='b',s3[1]='a'→F. dp[0][1]:s2[0]='a'==s3[0]='a',dp[0][0]=T→T. dp[1][1]:s1[0]='a'==s3[1]='a',dp[0][1]=T→T OR s2[0]='a'==s3[1]='a',dp[1][0]=T→T→T. dp[2][1]:s1[1]='b'==s3[2]='b',dp[1][1]=T→T. True ✓.
</details>

**Drill 5:** Decode string "3[a2[c]]". Trace the stack.
<details><summary>Reveal</summary>
num=3. '[': push("",3), cur="",num=0. 'a': cur="a". num=2. '[': push("a",2), cur="",num=0. 'c': cur="c". ']': pop("a",2). rep="c"*2="cc". cur="a"+"cc"="acc". ']': pop("",3). rep="acc"*3="accaccacc". cur=""+"accaccacc"="accaccacc". Result: "accaccacc" ✓.
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Space |
|---------|------|-------|
| Edit distance | O(m×n) | O(m×n) → O(n) rolling |
| Wildcard matching | O(m×n) | O(m×n) |
| Regex matching | O(m×n) | O(m×n) |
| Interleaving strings | O(m×n) | O(m×n) → O(n) |
| String compression | O(n) | O(1) |
| Decode string | O(n × max_repeat) | O(n) |

---

## 9. Common Follow-up Questions

**Q: How to optimize edit distance to O(n) space?**
A: Use a 1D array. Process row by row, keeping track of `prev` (the diagonal `dp[i-1][j-1]`). `prev = dp[j-1]` before update; after update, `dp[j]` becomes the new value.

**Q: What's the relationship between LCS and edit distance?**
A: `editDist(s, t) = m + n - 2*LCS(s, t)` when only insertions and deletions are allowed (not replacements). With replacements, edit distance ≤ m + n - LCS.

**Q: Can wildcard matching handle more complex patterns?**
A: For arbitrary regular expressions (including groups, alternation), use a proper NFA/DFA construction. The DP approach works for the restricted set of `.` and `*` (or `?` and `*`).

---

## 10. Cross-Pattern Connections

- **P30 (1D DP):** Edit distance is a classic 2D DP extending 1D DP principles
- **P33 (String DP):** LCS, LCS variations are direct predecessors
- **P65 (Expression Evaluation):** Decode string uses the same stack-based approach
- **P86 (KMP):** Pattern matching; KMP is for exact match, regex/wildcard for flexible match
