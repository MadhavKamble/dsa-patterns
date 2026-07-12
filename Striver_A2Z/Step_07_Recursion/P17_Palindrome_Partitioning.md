# Palindrome Partitioning

> **LeetCode #131** · **Difficulty:** Medium · **Step 7 — Recursion · P17**

---

## 🧠 Problem Understanding

**What is it asking?**
Partition a string `s` such that every substring in the partition is a palindrome. Return all possible palindrome partitioning.

**Input:** `s = "aab"` → **Output:** `[["a","a","b"],["aa","b"]]`
**Input:** `s = "a"`  → **Output:** `[["a"]]`

**Key Observations:**
- At each position `start`, try every possible prefix `s[start..end]`.
- If that prefix is a palindrome, include it, recurse for the rest `s[end+1..]`.
- Base case: `start == s.size()` → we've consumed the entire string, push `curr`.
- This is the standard backtracking loop pattern (like Combination Sum II / Subsets II), but the "include" condition is isPalindrome instead of a sum/dup check.

---

## 🥇 Backtracking with Palindrome Check

### Key Insight

> 💡 Fix a `start` index. Try every `end` from `start` to `n-1`. If `s[start..end]` is a palindrome, add it to `curr`, recurse with `start = end+1`, then backtrack (`pop_back`).

### How It Connects to Previous Problems

```
Combination Sum II (P12):        Palindrome Partitioning (P17):
  for i = idx to n-1:              for end = start to n-1:
    if dup: skip                      if isPalindrome(start, end):
    push arr[i]                         push s[start..end]
    recurse(i+1)                        recurse(end+1)
    pop                                 pop
```

Same loop skeleton — just a different inclusion condition.

### Algorithm
1. `backtrack(start, s, curr, ans)`:
   - **Base:** `start == s.size()` → push `curr`, return.
   - Loop `end = start` to `s.size()-1`:
     - If `isPalindrome(s, start, end)`: push `s.substr(start, end-start+1)`, recurse `(end+1)`, pop.
2. `isPalindrome(s, l, r)`: two-pointer check.

### C++ Code

```cpp
class Solution {
public:
    vector<vector<string>> partition(string s){
        vector<vector<string>> ans;
        vector<string> curr;
        backtrack(0,s,curr,ans);
        return ans;
    }

    void backtrack(int start,string& s,vector<string>& curr,vector<vector<string>>& ans){
        if(start==(int)s.size()){
            ans.push_back(curr);
            return;
        }
        for(int end=start;end<(int)s.size();end++){
            if(isPalindrome(s,start,end)){
                curr.push_back(s.substr(start,end-start+1));
                backtrack(end+1,s,curr,ans);
                curr.pop_back();
            }
        }
    }

    bool isPalindrome(string& s,int l,int r){
        while(l<r){
            if(s[l]!=s[r]) return false;
            l++; r--;
        }
        return true;
    }
};
```

**Time:** O(2^N × N) — 2^N possible partitions, O(N) palindrome check per substring
**Space:** O(N) recursion depth

### Dry Run — `s = "aab"`

```
backtrack(0, "aab", curr=[])
  end=0: "a" isPalin? yes → push "a", backtrack(1, curr=["a"])
    end=1: "a" isPalin? yes → push "a", backtrack(2, curr=["a","a"])
      end=2: "b" isPalin? yes → push "b", backtrack(3, curr=["a","a","b"])
        start=3==size → push ["a","a","b"] ✓
      pop "b"
    pop "a"
    end=2: "ab" isPalin? no (a≠b) → skip
  pop "a"
  end=1: "aa" isPalin? yes → push "aa", backtrack(2, curr=["aa"])
    end=2: "b" isPalin? yes → push "b", backtrack(3, curr=["aa","b"])
      start=3==size → push ["aa","b"] ✓
    pop "b"
  pop "aa"
  end=2: "aab" isPalin? no (a≠b) → skip
```

**Output:** `[["a","a","b"],["aa","b"]]` ✓

---

## 🔋 Optimized — DP Precompute isPalindrome

For large strings, recomputing palindrome check O(N) in each call is wasteful. Precompute a 2D table `dp[i][j] = true if s[i..j] is palindrome` in O(N²), then each check is O(1).

```cpp
// Precompute
vector<vector<bool>> dp(n, vector<bool>(n,false));
for(int i=n-1;i>=0;i--){
    for(int j=i;j<n;j++){
        if(s[i]==s[j] && (j-i<=2 || dp[i+1][j-1]))
            dp[i][j]=true;
    }
}
// Use dp[start][end] instead of isPalindrome call
```

**With DP:** O(N² + 2^N × N) time, O(N²) space for the table.

---

## 🧾 Recall Line *(10-Second Revision)*

> "Loop end=start→n. If `s[start..end]` palindrome: push, recurse(end+1), pop. Base: start==n → push curr. Same loop as Combination Sum II, condition = isPalindrome."

---

## 📝 Short Revision Notes

- `s.substr(start, end-start+1)` — length is `end-start+1`, not `end`.
- Every single character is trivially a palindrome — the loop always has at least one valid branch.
- The DP optimization matters for long strings but the backtracking structure is identical.

---

## ⚠️ Common Mistakes

❌ `s.substr(start, end)` instead of `s.substr(start, end-start+1)` — wrong length.
❌ Recursing with `start` instead of `end+1` — infinite loop.
❌ Not popping `curr` after recursion — carries over to next iteration.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "partition string such that each part satisfies property X" → **loop end=start→n, check property, push substr, recurse(end+1), pop**.

---

## 🏆 Pattern Category

`Recursion` · `Backtracking` · `String` · `Palindrome`

---

## ⏱️ 30-Second Last-Minute Revision

> Loop `end=start→n`. If `isPalindrome(start,end)`: push `substr`, `recurse(end+1)`, pop. Base: `start==n → push curr`. Optimize: DP table for O(1) palindrome checks. **Time:** O(2^N × N).
