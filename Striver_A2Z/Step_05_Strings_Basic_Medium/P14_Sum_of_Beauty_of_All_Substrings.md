# 🔥 Sum of Beauty of All Substrings

> **LeetCode #1781** · **Difficulty:** Medium · **Step 5 — Strings · P14**

---

## 🧠 Problem Understanding

**What is it asking?**
The **beauty** of a string = (highest character frequency) − (lowest character frequency). Return the **sum of beauty over all substrings**.

**Input:** `s = "aabcb"` → **Output:** `5`
**Input:** `s = "xyx"` → **Output:** `1` (only `"xyx"` has beauty `2−1=1`; all others are 0)

**Key Observation:**
Fix a left endpoint `i` and grow the substring to the right, maintaining a frequency map **incrementally**. For each substring add `maxFreq − minFreq`.

---

## 🎯 Interview Progression

### 🥉 Brute Force — Recount Each Substring

For every substring, build a fresh frequency map and scan. **Time:** O(N³).

---

### 🥇 Optimal — Incremental Frequency per Start Index

> 💡 Outer loop fixes `i`; inner loop extends `j`, incrementing `freq[s[j]]`. Each step, scan the (≤26) frequencies for min & max and add the difference.

```cpp
class Solution {
public:
    int beautySum(string s){
        int n=s.length();
        int sum=0;
        for(int i=0;i<n;i++){
            unordered_map<char,int> freq;
            for(int j=i;j<n;j++){
                freq[s[j]]++;
                int maxi=INT_MIN;
                int mini=INT_MAX;
                for(auto it:freq){
                    mini=min(mini,it.second);
                    maxi=max(maxi,it.second);
                }
                sum+=(maxi-mini);
            }
        }
        return sum;
    }
};
```

**Time:** O(N² · 26) ≈ O(N²) · **Space:** O(26).

### Dry Run
`s = "xyx"`

| substring | freqs | max − min | +sum |
|-----------|-------|-----------|------|
| x, y, x | single char | 0 | 0 |
| xy, yx | 1,1 | 0 | 0 |
| xyx | x:2, y:1 | 2−1 = 1 | **1** |

**Output:** `1` ✅

---

## 🧾 Recall Line *(10-Second Revision)*

> "For each start i, extend j, keep freq. Add `maxFreq − minFreq` for every substring."

---

## 📝 Short Revision Notes

- Reuse the frequency map across the inner loop — don't rebuild it per substring.
- Min/max scan is over at most 26 entries → effectively constant per step.
- Single-character (and all-uniform-frequency) substrings contribute 0.

---

## ⚠️ Common Mistakes

❌ Rebuilding the frequency map for every substring → O(N³).
❌ Scanning min over **all 26** letters including zero counts (only count present characters).
❌ Integer types — the sum can be large but fits in `int` for typical constraints; use `long long` if bounds are big.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "over all substrings", "max freq − min freq", "beauty sum" → **fix start + incremental frequency**.

---

## 🏆 Pattern Category

`Strings` · `Frequency Count` · `All Substrings`

---

## ⏱️ 30-Second Last-Minute Revision

> **Fix i, extend j, maintain freq; add max−min each step.** `O(N²·26)`.
