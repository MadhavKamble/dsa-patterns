# Recursive Implementation of atoi (String to Integer)

> **LeetCode #8** · **Difficulty:** Medium · **Step 7 — Recursion · P01**

---

## 🧠 Problem Understanding

**What is it asking?**
Convert a string to a 32-bit signed integer following these rules in order:
1. Skip leading whitespace.
2. Read optional `+` or `-` sign.
3. Read digits until a non-digit is hit.
4. Clamp to `[INT_MIN, INT_MAX]` on overflow.

**Input:** `s = "   -42abc"`
**Output:** `-42`

**Key Observations:**
- Pre-processing (spaces + sign) is iterative — only the digit-reading loop becomes recursion.
- State to carry through recursion: current index `i`, accumulated number `num`, `sign`.
- Overflow must be checked *before* multiplying — once you do `num*10+digit` on a `long long` the damage is done, but you'd miss the INT boundary. Check before the multiply.

---

## 🥉 Iterative (Standard) Approach

> The classic loop-based implementation — what most people write instinctively.

```cpp
class Solution {
public:
    int myAtoi(string s) {
        int i=0,n=s.size();
        while(i<n && s[i]==' ') i++;
        int sign=1;
        if(i<n && (s[i]=='+'||s[i]=='-')){
            if(s[i]=='-') sign=-1;
            i++;
        }
        long long num=0;
        while(i<n && isdigit(s[i])){
            int digit=s[i]-'0';
            if(num>(INT_MAX-digit)/10){
                return sign==1?INT_MAX:INT_MIN;
            }
            num=num*10+digit;
            i++;
        }
        return sign*num;
    }
};
```

**Time:** O(N) · **Space:** O(1)

---

## 🥇 Recursive Approach

> Same logic as the loop — but the `while` loop body becomes a recursive call. State (index, accumulator) travels as parameters instead of loop variables.

### Key Insight

> 💡 **Parameterized recursion:** carry `i`, `sign`, and `num` as arguments. Each call processes one digit and recurses on `i+1`. Base case = non-digit or end of string.

### How the Recursion Replaces the Loop

```
Iterative:                      Recursive equivalent:
──────────────────────────────────────────────────────
while(isdigit(s[i])) {          solve(s, i, sign, num):
  digit = s[i]-'0';               if !isdigit(s[i]) → return sign*num
  num = num*10 + digit;           digit = s[i]-'0'
  i++;                            num = num*10 + digit
}                                 return solve(s, i+1, sign, num)
```

### Overflow Check

We want to catch `num*10 + digit > INT_MAX` **before** doing the multiply:

```
num*10 + digit > INT_MAX
num > (INT_MAX - digit) / 10      ← rearranged
```

Integer division naturally floors, which means the check is exact:
- `digit=8, num=214748364` → `(2147483647-8)/10 = 214748363` → `214748364 > 214748363` ✓ overflow
- `digit=7, num=214748364` → `(2147483647-7)/10 = 214748364` → `214748364 > 214748364` ✗ → `2147483647` = INT_MAX exactly ✓

### Algorithm
1. `myAtoi`: skip spaces, read sign, call `solve(s, i, sign, 0)`.
2. `solve(s, i, sign, num)`:
   - **Base:** `i >= size` or `!isdigit(s[i])` → return `sign * num`.
   - Extract `digit = s[i] - '0'`.
   - Overflow check → return clamped value if needed.
   - Recurse: `solve(s, i+1, sign, num*10+digit)`.

### C++ Code

```cpp
class Solution {
public:
    int myAtoi(string s) {
        int i=0,n=s.size();
        while(i<n && s[i]==' ') i++;
        int sign=1;
        if(i<n && (s[i]=='+'||s[i]=='-')){
            if(s[i]=='-') sign=-1;
            i++;
        }
        return solve(s,i,sign,0);
    }

    int solve(string &s,int i,int sign,long long num){
        if(i>=(int)s.size() || !isdigit(s[i]))
            return sign*num;
        int digit=s[i]-'0';
        if(num>(INT_MAX-digit)/10){
            return sign==1?INT_MAX:INT_MIN;
        }
        return solve(s,i+1,sign,num*10+digit);
    }
};
```

**Time:** O(N) · **Space:** O(N) — call stack depth = number of digits (≤ 10 for 32-bit int, so practically O(1))

### Dry Run

**Input:** `s = "  -4193 with words"`

| Call | i | s[i] | num | digit | Action |
|------|---|------|-----|-------|--------|
| myAtoi | 0→2 | skip spaces | — | — | i=2, sign=-1, i=3 |
| solve(3,-1,0) | 3 | '4' | 0 | 4 | recurse with num=4 |
| solve(4,-1,4) | 4 | '1' | 4 | 1 | recurse with num=41 |
| solve(5,-1,41) | 5 | '9' | 41 | 9 | recurse with num=419 |
| solve(6,-1,419) | 6 | '3' | 419 | 3 | recurse with num=4193 |
| solve(7,-1,4193) | 7 | ' ' | 4193 | — | base: return -1*4193 = **-4193** |

---

## 🧾 Recall Line *(10-Second Revision)*

> "Skip spaces + sign iteratively, then recurse digit by digit carrying `(i, sign, num)`. Base = non-digit. Overflow check: `num > (INT_MAX - digit) / 10`."

---

## 📝 Short Revision Notes

- Pre-processing (spaces, sign) stays iterative — only the digit loop becomes recursive.
- Pass `string &s` by reference to avoid copying on every recursive call.
- `num` is `long long` to hold values up to `INT_MAX` during accumulation; the overflow check keeps the final `sign*num` within `int` range.
- The overflow formula `num > (INT_MAX-digit)/10` avoids any 64-bit overflow during the check itself.
- This is **tail recursion** — each call returns immediately after the recursive call → some compilers optimize it to a loop.

---

## ⚠️ Common Mistakes

❌ Checking overflow **after** `num*10+digit` — too late, already overflowed.
❌ Using `int` for `num` — overflows before you can detect it.
❌ Passing `string` by value — copies the whole string on every frame.
❌ Forgetting to handle the `+` sign (only checking `-`).
❌ Missing the cast `i >= (int)s.size()` when `i` is `int` and `size()` is `size_t` (unsigned) — causes UB on wrap-around.

---

## 🧠 Pattern Recognition Trigger

**When I see:** convert iterative digit-processing loop to recursion → **parameterized recursion with (index, accumulator) as parameters**.

---

## 🏆 Pattern Category

`Recursion` · `Parameterized Recursion` · `String Parsing` · `Overflow Handling`

---

## ⏱️ 30-Second Last-Minute Revision

> **Idea:** Replace `while(isdigit)` loop with recursive `solve(i, sign, num)`. Base = non-digit/end. Each call: extract digit, overflow-check (`num > (INT_MAX-d)/10`), recurse with `num*10+d`. **Time:** O(N) | **Space:** O(N) stack (≤10 frames in practice).
