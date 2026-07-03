# 🔥 String to Integer (atoi)

> **LeetCode #8** · **Difficulty:** Medium · **Step 5 — Strings · P11**

---

## 🧠 Problem Understanding

**What is it asking?**
Implement `atoi`: (1) skip leading spaces, (2) read an optional `+`/`-`, (3) read consecutive digits, stopping at the first non-digit, and (4) **clamp** the result to the 32-bit signed range `[-2^31, 2^31 − 1]`.

**Input:** `s = "  -12345"` → **Output:** `-12345`
**Input:** `s = "words 42"` → **Output:** `0` (starts with a non-digit)
**Input:** `s = "91234567890123"` → **Output:** `2147483647` (overflow → INT_MAX)

**Key Observation:**
Parse in phases — spaces, sign, digits — then guard overflow **during** accumulation (use a wider type and clamp as soon as the signed value crosses a boundary).

---

## 🎯 Interview Progression

### 🥇 Optimal — Phased Parse with Overflow Clamp

> 💡 Skip spaces, capture the sign, then accumulate digits in a `long long`. After each digit, if `sign*num` reaches/exceeds the 32-bit limits, return the clamped bound immediately.

```cpp
class Solution {
public:
    int helper(const string& s,int i,long long num,int sign){
        if(i>=s.size() || !isdigit(s[i]))
            return (int)(sign*num);
        num=num*10+(s[i]-'0');
        if(sign*num<=INT_MIN) return INT_MIN;
        if(sign*num>=INT_MAX) return INT_MAX;
        return helper(s,i+1,num,sign);
    }
    int myAtoi(string s){
        int i=0;
        while(i<s.size() && s[i]==' ') i++;
        int sign=1;
        if(i<s.size() && (s[i]=='+' || s[i]=='-')){
            sign=(s[i]=='-')?-1:1;
            i++;
        }
        return helper(s,i,0,sign);
    }
};
```

**Time:** O(N) · **Space:** O(N) recursion stack (O(1) if written iteratively).

### Dry Run
`s = "  -12345"`

- Skip 2 spaces → `i=2`.
- `s[2]='-'` → `sign=-1`, `i=3`.
- Accumulate `1,2,3,4,5` → `num=12345`; `sign*num = -12345`, within range.
- Next char out of bounds → return `(int)(-1 * 12345) = -12345` ✅

---

## 🎤 Interview Explanation Script

> "I handle it in phases: skip whitespace, read an optional sign, then digits. I accumulate in a `long long` and after every digit check whether the signed value has hit the 32-bit limits — if so I return the clamped bound right away, which avoids overflow. Parsing stops at the first non-digit."

---

## 🧾 Recall Line *(10-Second Revision)*

> "Skip spaces → sign → digits into long long → clamp to INT_MIN/INT_MAX during accumulation."

---

## 📝 Short Revision Notes

- Order is strict: **spaces, then one sign, then digits** — a sign after digits is invalid.
- Accumulate in a wider type (`long long`) and clamp *as you go*, before it overflows `int`.
- Stop at the first non-digit; no trailing parse.
- `(sign*num <= INT_MIN)` / `(>= INT_MAX)` compares the signed running value against the bounds.

---

## ⚠️ Common Mistakes

❌ Overflowing `int` before the clamp check — use `long long`.
❌ Accepting multiple signs or a sign not immediately before digits.
❌ Forgetting to skip leading spaces, or trying to skip trailing content.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "parse an integer from text", "atoi", "clamp to 32-bit" → **phased parse + overflow guard**.

---

## 🏆 Pattern Category

`Strings` · `Parsing` · `Simulation`

---

## ⏱️ 30-Second Last-Minute Revision

> **Spaces → sign → digits (long long) → clamp to [INT_MIN, INT_MAX].** Stop at first non-digit. `O(N)`.
