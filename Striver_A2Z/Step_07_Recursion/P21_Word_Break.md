# Word Break

> **LeetCode #139** · **Difficulty:** Medium · **Step 7 — Recursion · P21**

---

## 🧠 Problem Understanding

**What is it asking?**
Given string `s` and a dictionary `wordDict`, return `true` if `s` can be segmented into a space-separated sequence of dictionary words.

**Input:** `s = "leetcode", wordDict = ["leet","code"]` → `true`
**Input:** `s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]` → `false`

**Key Observations:**
- At each position `start`, try every possible prefix `s[start..end]`.
- If that prefix is in the dictionary, recurse for `s[end..]`.
- Base: `start == s.size()` → fully consumed → return true.
- Without memoization: 2^N states. With memoization: O(N²) — `memo[start]` caches whether `s[start..]` can be broken.

---

## 🥉 Recursive Without Memoization (TLE for large input)

```cpp
bool solve(string& s, unordered_set<string>& dict, int start) {
    if(start==(int)s.size()) return true;
    for(int end=start+1;end<=(int)s.size();end++){
        if(dict.count(s.substr(start,end-start)) && solve(s,dict,end))
            return true;
    }
    return false;
}
```

**Time:** O(2^N × N) · **Space:** O(N)

---

## 🥇 Recursive + Memoization

### Key Insight

> 💡 Same as Palindrome Partitioning (P17) — loop `end` from `start`, try each prefix. But here: if prefix is in dict AND the rest is solvable → return true. `memo[start]` prevents re-solving the same suffix.

### How It Connects to P17

```
Palindrome Partitioning (P17):        Word Break (P21):
  for end = start to n-1:               for end = start+1 to n:
    if isPalindrome(start, end):           if dict.has(s[start..end]):
      push substr                            if solve(end): return true
      recurse(end+1)                  return false (no valid break)
      pop
```

Same loop, different condition. Word Break returns first success (bool) instead of collecting all partitions.

### Algorithm
1. Build `unordered_set` from `wordDict` for O(1) lookup.
2. `solve(start, memo)`:
   - **Base:** `start == n` → return true.
   - If `memo[start] != -1` → return `memo[start]`.
   - Loop `end = start+1` to `n`: if `dict.has(s[start..end-start])` and `solve(end)` → `memo[start] = 1`, return true.
   - `memo[start] = 0`, return false.

### C++ Code

```cpp
class Solution {
public:
    bool wordBreak(string s,vector<string>& wordDict){
        unordered_set<string> dict(wordDict.begin(),wordDict.end());
        vector<int> memo(s.size(),-1);
        return solve(s,dict,0,memo);
    }

    bool solve(string& s,unordered_set<string>& dict,int start,vector<int>& memo){
        if(start==(int)s.size()) return true;
        if(memo[start]!=-1) return memo[start];
        for(int end=start+1;end<=(int)s.size();end++){
            if(dict.count(s.substr(start,end-start)) && solve(s,dict,end,memo)){
                return memo[start]=1;
            }
        }
        return memo[start]=0;
    }
};
```

**Time:** O(N² × N) = O(N³) — N² states, O(N) substr per state
**Space:** O(N) — memo array + recursion depth

### Dry Run — `s="leetcode", dict={"leet","code"}`

```
solve(0): try "l"→no, "le"→no, "lee"→no, "leet"→yes!
  solve(4): try "c"→no, "co"→no, "cod"→no, "code"→yes!
    solve(8): start==size → return true ✓
  return memo[4]=1, memo[0]=1 → return true
```

---

## 🔄 Bottom-Up DP Alternative

```cpp
bool wordBreak(string s,vector<string>& wordDict){
    unordered_set<string> dict(wordDict.begin(),wordDict.end());
    int n=s.size();
    vector<bool> dp(n+1,false);
    dp[0]=true;
    for(int i=1;i<=n;i++){
        for(int j=0;j<i;j++){
            if(dp[j] && dict.count(s.substr(j,i-j))){
                dp[i]=true;
                break;
            }
        }
    }
    return dp[n];
}
```

**Time:** O(N³) · **Space:** O(N)

---

## 🧾 Recall Line *(10-Second Revision)*

> "Loop end=start+1→n. If `dict.has(s[start..end])` and `solve(end)` → true. Base: start==n. Memoize on `start`. Same loop as palindrome partitioning."

---

## 📝 Short Revision Notes

- `unordered_set` gives O(1) lookup; `substr` is O(length) — the bottleneck.
- `memo[start]` stores whether `s[start..]` is breakable — only N unique states.
- Bottom-up DP (`dp[i]` = can reach index i) is equivalent and often cleaner.

---

## ⚠️ Common Mistakes

❌ Forgetting memoization — exponential without it.
❌ `dict.count(s.substr(start, end))` with wrong length — should be `end-start`.
❌ Not returning false at end of loop — falls through without explicitly returning false.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "partition string such that each part is in a dictionary" → **loop end=start+1→n, dict lookup, recurse(end), memoize on start**.

---

## 🏆 Pattern Category

`Recursion` · `Memoization` · `String` · `Dynamic Programming`

---

## ⏱️ 30-Second Last-Minute Revision

> `unordered_set` for O(1) lookup. For each `start`, try all `end`. If `substr` in dict and `solve(end)` → cache true. Base: `start==n→true`. **Time:** O(N³) | **Space:** O(N).
