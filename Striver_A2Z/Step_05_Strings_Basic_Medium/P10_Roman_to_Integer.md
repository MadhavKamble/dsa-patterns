# 🔥 Roman to Integer

> **LeetCode #13** · **Difficulty:** Easy · **Step 5 — Strings · P10**

---

## 🧠 Problem Understanding

**What is it asking?**
Convert a Roman numeral string to its integer value.

**Input:** `s = "III"` → **Output:** `3`
**Input:** `s = "MCMXCIV"` → **Output:** `1994` (M=1000, CM=900, XC=90, IV=4)

**Key Observation:**
Usually add each numeral's value. But when a **smaller** numeral precedes a **larger** one (`IV`, `IX`, `XL`, `XC`, `CD`, `CM`), it means subtraction. So: compare each symbol with the next — if it's smaller, subtract it; otherwise add it.

---

## 🎯 Interview Progression

### 🥇 Optimal — Compare with the Next Symbol

> 💡 Map symbols to values. For each `i` (except the last), subtract if `value(s[i]) < value(s[i+1])`, else add. Add the last symbol at the end.

```cpp
class Solution {
public:
    int romanToInt(string s){
        int res=0;
        unordered_map<char,int> roman={
            {'I',1},{'V',5},{'X',10},
            {'L',50},{'C',100},{'D',500},{'M',1000}
        };
        for(int i=0;i<s.size()-1;i++){
            if(roman[s[i]]<roman[s[i+1]]){
                res-=roman[s[i]];
            }else{
                res+=roman[s[i]];
            }
        }
        return res+roman[s.back()];
    }
};
```

**Time:** O(N) · **Space:** O(1) (fixed map).

### Dry Run
`s = "MCMXCIV"`

| i | s[i] | s[i+1] | compare | contribution | res |
|---|------|--------|---------|--------------|-----|
| 0 | M(1000) | C(100) | ≥ | +1000 | 1000 |
| 1 | C(100) | M(1000) | < | −100 | 900 |
| 2 | M(1000) | X(10) | ≥ | +1000 | 1900 |
| 3 | X(10) | C(100) | < | −10 | 1890 |
| 4 | C(100) | I(1) | ≥ | +100 | 1990 |
| 5 | I(1) | V(5) | < | −1 | 1989 |
| last | V(5) | — | — | +5 | **1994** ✅ |

---

## 🧾 Recall Line *(10-Second Revision)*

> "If `value(s[i]) < value(s[i+1])` subtract, else add. Add the last symbol."

---

## 📝 Short Revision Notes

- Only 6 subtractive combos exist; the "smaller before larger" rule captures all of them.
- Loop runs to `s.size()-1`; the last character is always added.
- Alternative: iterate left-to-right adding values, subtracting `2×prev` whenever you detect a subtractive pair.

---

## ⚠️ Common Mistakes

❌ Adding everything and ignoring subtractive pairs.
❌ `s.size()-1` underflow for an empty string (Roman inputs are non-empty, but guard if needed).
❌ Off-by-one: forgetting to add the final symbol.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "Roman numeral to integer", "subtractive notation" → **compare each symbol with the next**.

---

## 🏆 Pattern Category

`Strings` · `Hashing` · `Simulation`

---

## ⏱️ 30-Second Last-Minute Revision

> **Smaller-before-larger ⇒ subtract, else add; add the last.** `O(N)`.
