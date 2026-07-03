# 🔥 Check if Two Strings are Anagrams

> **LeetCode #242** · **Difficulty:** Easy · **Step 5 — Strings · P07**

---

## 🧠 Problem Understanding

**What is it asking?**
Two strings are **anagrams** if one is a rearrangement of the other — same characters with the same counts.

**Input:** `s = "INTEGER"`, `t = "TEGERNI"` → **Output:** `true`
**Input:** `s = "rat"`, `t = "car"` → **Output:** `false`

**Key Observation:**
Different lengths → instantly not anagrams. Otherwise a single frequency array: **increment** for one string, **decrement** for the other; anagrams iff every count ends at 0.

---

## 🎯 Interview Progression

### 🥉 Brute Force — Sort & Compare

Sort both strings and check equality. **Time:** O(N log N).

---

### 🥇 Optimal — Frequency Count

> 💡 One `freq[26]`: `++` over `str1`, `--` over `str2`. All zeros at the end ⇒ anagrams.

```cpp
class Solution {
public:
    bool isAnagram(string str1,string str2){
        if(str1.length()!=str2.length()) return false;
        int freq[26]={0};
        for(int i=0;i<str1.length();i++){
            freq[str1[i]-'A']++;
        }
        for(int i=0;i<str2.length();i++){
            freq[str2[i]-'A']--;
        }
        for(int i=0;i<26;i++){
            if(freq[i]!=0) return false;
        }
        return true;
    }
};
```

**Time:** O(N) · **Space:** O(1) (fixed 26 array).

### Dry Run
`str1 = "INTEGER"`, `str2 = "TEGERNI"` — both have `{I,N,T,E,G,E,R}` with the same counts, so after `++` then `--` every bucket is 0 → **true** ✅

---

## 🧾 Recall Line *(10-Second Revision)*

> "Same length. `freq[26]`: ++ for s, -- for t. All zeros ⇒ anagram."

---

## 📝 Short Revision Notes

- This code offsets by `'A'` → assumes a **single case** (uppercase here). For lowercase use `'a'`; for mixed/general input use a `256`-size array.
- The increment/decrement trick avoids a second array and a comparison pass.
- Length mismatch is the cheap early exit.

---

## ⚠️ Common Mistakes

❌ Wrong offset for the input's case (`'A'` vs `'a'`).
❌ Skipping the length check → a prefix could zero out falsely.
❌ Assuming only letters when the input may contain digits/symbols (use 256 then).

---

## 🧠 Pattern Recognition Trigger

**When I see:** "anagram", "same characters rearranged", "permutation of letters" → **frequency count**.

---

## 🏆 Pattern Category

`Strings` · `Hashing` · `Frequency Count`

---

## ⏱️ 30-Second Last-Minute Revision

> **Same length + freq array (++ then --) all zero.** `O(N)`, O(1) space. Mind the case offset / use 256 for general input.
