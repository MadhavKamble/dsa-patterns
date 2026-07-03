# 🔥 Longest Palindromic Substring

> **LeetCode #5** · **Difficulty:** Medium · **Step 5 — Strings · P13**

---

## 🧠 Problem Understanding

**What is it asking?**
Return the **longest contiguous substring** that reads the same forwards and backwards.

**Input:** `s = "babad"` → **Output:** `"bab"` (or `"aba"`)
**Input:** `s = "cbbd"` → **Output:** `"bb"`

**Key Observation:**
Every palindrome has a **center**. There are `2n-1` centers (each character for odd-length palindromes, each gap for even-length). Expand outward from each center while the two sides match.

---

## 🎯 Interview Progression

### 🥉 Brute Force — Check All Substrings

Test every substring for palindromicity. **Time:** O(N³).

### 🥈 Better — DP Table

`dp[i][j]` = is `s[i..j]` a palindrome. **Time:** O(N²) · **Space:** O(N²).

---

### 🥇 Optimal — Expand Around Center

> 💡 For each index, expand an **odd** center `(i, i)` and an **even** center `(i, i+1)`. Keep the longest palindrome found. O(N²) time but O(1) space.

```cpp
class Solution {
public:
    string expand(int i,int j,string s){
        int left=i;
        int right=j;
        while(left>=0 && right<s.size() && s[left]==s[right]){
            left--;
            right++;
        }
        return s.substr(left+1,right-left-1);
    }
    string longestPalindrome(string s){
        string ans="";
        for(int i=0;i<s.size();i++){
            string odd=expand(i,i,s);
            if(odd.size()>ans.size()){
                ans=odd;
            }
            string even=expand(i,i+1,s);
            if(even.size()>ans.size()){
                ans=even;
            }
        }
        return ans;
    }
};
```

**Time:** O(N²) · **Space:** O(1) (excluding output).

### Dry Run
`s = "babad"`

| center | expands to | length |
|--------|-----------|--------|
| odd @1 (`a`) | `bab` | 3 |
| odd @2 (`b`) | `aba` | 3 |
| others | ≤ 1 | — |

**Output:** `"bab"` (first max) ✅

---

## 🧾 Recall Line *(10-Second Revision)*

> "Expand around each center — odd `(i,i)` and even `(i,i+1)`. Keep the longest."

---

## 📝 Short Revision Notes

- `2n-1` centers: `n` single-character (odd) + `n-1` gaps (even).
- After the loop, the palindrome is `s.substr(left+1, right-left-1)` (the last valid bounds are one step inside).
- O(N²)/O(1) is the interview-standard answer; Manacher's gives O(N) but is rarely required.

---

## ⚠️ Common Mistakes

❌ Handling only odd centers → misses even-length palindromes like `"bb"`.
❌ Off-by-one in the final `substr` bounds (`left+1`, length `right-left-1`).
❌ Comparing lengths incorrectly and returning a shorter palindrome.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "longest palindromic substring", "palindrome centered somewhere" → **expand around center**.

---

## 🏆 Pattern Category

`Strings` · `Palindrome` · `Two Pointers (Expand)`

---

## ⏱️ 30-Second Last-Minute Revision

> **Expand around all `2n-1` centers** (odd + even). Track the longest. `O(N²)` time, `O(1)` space.
