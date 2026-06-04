# 🔥 Reverse a Number

> **LeetCode #7** · **Difficulty:** Medium · **Step 1 — Basic Maths · P14**

---

## 🧠 Problem Understanding

**What is it asking?**  
Given a 32-bit signed integer `x`, return `x` with its digits reversed. If reversing causes overflow, return `0`.

**Input:** 32-bit signed integer x (–2³¹ ≤ x ≤ 2³¹ – 1)  
**Output:** Reversed integer, or 0 if result overflows 32-bit range

**Key Observations:**
- Negative numbers: `-123` reverses to `-321` (sign preserved)
- Overflow check: result must stay in [-2³¹, 2³¹-1] = [-2147483648, 2147483647]
- Trailing zeros become leading zeros and disappear: `120 → 21`

**Simple Example:**
```
Input:  x = 1234
Output: 4321

Input:  x = -1234
Output: -4321

Input:  x = 1200
Output: 21   (trailing zeros dropped naturally)
```

---

## 🥉 Brute Force Approach

### Idea
Convert to string, reverse the string, handle sign, convert back to int with overflow check.

### Algorithm
1. Note the sign, work with `abs(x)`
2. Convert to string and reverse it
3. Convert back to `long long`
4. Check if within 32-bit range
5. Re-apply sign and return

### Complexity
- **Time:** O(log N) — number of digits
- **Space:** O(log N) — string allocation

### C++ Code
```cpp
// BRUTE FORCE: String reversal
int reverse(int x) {
    string s = to_string(abs(x));        // convert absolute value to string
    std::reverse(s.begin(), s.end());    // reverse the string
    long long result = stoll(s);         // convert back to number

    if (x < 0) result = -result;         // restore sign

    // overflow check for 32-bit int
    if (result > INT_MAX || result < INT_MIN) return 0;
    return (int)result;
}
```

---

## 🥇 Optimal Approach

### Key Observation

> 💡 Build the reversed number mathematically:
> - Extract last digit: `d = x % 10`
> - Shift reversed number left: `rev = rev * 10 + d`
> - Remove last digit: `x /= 10`
> - Check overflow **before** multiplying

```
x = 1234
Step 1: d = 4, rev = 0*10 + 4 = 4,    x = 123
Step 2: d = 3, rev = 4*10 + 3 = 43,   x = 12
Step 3: d = 2, rev = 43*10 + 2 = 432, x = 1
Step 4: d = 1, rev = 432*10 + 1 = 4321, x = 0
Answer: 4321
```

### Overflow Check Strategy
Before doing `rev = rev * 10 + d`, check:
- If `rev > INT_MAX / 10` → next step overflows
- If `rev == INT_MAX / 10` and `d > 7` → overflows (INT_MAX ends in 7)
- Similarly for negative side (INT_MIN ends in 8)

### Algorithm
1. Initialize `rev = 0`
2. While `x != 0`:
   - Extract digit: `d = x % 10`
   - Overflow check: if `rev > INT_MAX/10` or `rev < INT_MIN/10` → return 0
   - Update: `rev = rev * 10 + d`
   - Remove digit: `x /= 10`
3. Return `rev`

### Dry Run

**Input:** `x = -1230`

| Step | x | d = x%10 | rev = rev*10+d | Note |
|------|---|-----------|----------------|------|
| Init | -1230 | — | 0 | |
| 1 | -1230 | 0 | 0 | trailing zero drops |
| 2 | -123 | -3 | -3 | |
| 3 | -12 | -2 | -32 | |
| 4 | -1 | -1 | -321 | |
| 5 | 0 | — | stop | |

**Output:** `-321`

> In C++, `%` for negative numbers returns negative remainder: `-123 % 10 = -3`. This is fine — the sign propagates correctly.

### Complexity
- **Time:** O(log N)
- **Space:** O(1)

---

## 🎤 Interview Explanation Script

> "The brute force converts to string and reverses it, but that uses O(log N) space."

> "The optimization comes from building the reversed number digit by digit using arithmetic — `rev = rev * 10 + (x % 10)`."

> "The tricky part is overflow. We can't just use `long long` and check at the end — the problem says we're limited to 32-bit. So before each `rev * 10`, we check if `rev > INT_MAX / 10`."

> "For negative numbers, C++ `%` operator returns negative remainders, which naturally handles the sign."

> "Hence space drops from O(log N) to O(1)."

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * PROBLEM UNDERSTANDING:
 *   Reverse digits of a 32-bit int. Return 0 on overflow.
 *
 * EDGE CASES:
 *   - Negative numbers: handled by C++ negative modulo
 *   - Trailing zeros: naturally disappear (0 * 10 = 0, adds nothing)
 *   - Overflow: check BEFORE multiplying, not after
 *
 * KEY OBSERVATION:
 *   rev = rev * 10 + (x % 10) builds reversed number.
 *   Overflow check: rev > INT_MAX/10 means next step will overflow.
 *
 * COMPLEXITY: Time O(log N) | Space O(1)
 */

class Solution {
public:
    int reverse(int x) {
        int rev = 0;

        while (x != 0) {
            int digit = x % 10;       // extract last digit (negative for negative x)
            x /= 10;                  // remove last digit

            // overflow check BEFORE updating rev
            if (rev > INT_MAX / 10 || (rev == INT_MAX / 10 && digit > 7))
                return 0;
            if (rev < INT_MIN / 10 || (rev == INT_MIN / 10 && digit < -8))
                return 0;

            rev = rev * 10 + digit;   // build reversed number
        }

        return rev;
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "Extract last digit with `%10`, build reversed with `rev*10+d`, overflow check before multiply."

---

## 📝 Short Revision Notes

- Core loop: `d = x%10`, `rev = rev*10 + d`, `x /= 10`
- Negative numbers: C++ `%` gives negative remainder → sign propagates automatically
- Overflow check: `rev > INT_MAX/10` before any `rev * 10`
- Trailing zeros: disappear naturally (prefix zero = just 0)
- INT_MAX = 2147483647 (ends in 7), INT_MIN = -2147483648 (ends in 8)
- Time O(log N), Space O(1)

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "reverse digits"
- "extract digits one by one"
- "digit manipulation without string"

**I should think of:** `% 10` to extract, `/ 10` to remove, `* 10` to shift

---

## ⚠️ Common Mistakes

❌ Forgetting overflow check → runtime error or wrong answer  
❌ Checking overflow AFTER multiplying (too late — already overflowed)  
❌ Handling negative sign separately instead of letting `%` do it naturally  
❌ Using `long long` without actually checking — LeetCode problem requires 32-bit aware solution  
❌ `while (x > 0)` — misses negative numbers; use `while (x != 0)`  

---

## 🔥 What Interviewer Is Testing

- **Concept:** Digit extraction and number building
- **Reasoning:** Edge case handling (overflow, negatives, trailing zeros)
- **Optimization:** O(1) space over string approach

---

## 🚀 Alternative Approaches

| Approach | Time | Space | When to use |
|----------|------|-------|-------------|
| Arithmetic (optimal) | O(log N) | O(1) | Always |
| String reversal | O(log N) | O(log N) | Simpler code, acceptable in interview |
| Long long intermediate | O(log N) | O(1) | Simpler overflow check, but technically uses extra range |

---

## 📚 Related Problems

- [ ] LeetCode #7 — Reverse Integer
- [ ] LeetCode #9 — Palindrome Number (uses same reverse logic)
- [ ] LeetCode #8 — String to Integer (atoi) (overflow handling)
- [ ] Striver Step 1 P13 — Count Digits (same digit extraction pattern)
- [ ] Striver Step 1 P15 — Check Palindrome (reverse and compare)

---

## 🏆 Pattern Category

`Math` · `Digit Extraction` · `Overflow Handling`

---

## 🎯 Difficulty Analysis

**Rating:** Medium (on LeetCode)

**Why challenging:** The arithmetic is simple, but overflow handling is the real test. Most candidates forget to check overflow before multiplying, or handle it incorrectly.

---

## 📈 Progression Insight

**Harder variant:** Reverse a number in base K (not base 10)  
**Even harder:** Reverse only the digits that satisfy a condition  
**Related hard:** Palindrome partitioning with digit manipulation  

---

## ⏱️ 30-Second Last-Minute Revision

> **Problem:** Reverse digits of integer x, return 0 if overflow  
> **Approach:** `while x!=0: d=x%10, overflow-check, rev=rev*10+d, x/=10`  
> **Key trick:** Check `rev > INT_MAX/10` BEFORE `rev*10`, not after  
> **Time:** O(log N) | **Space:** O(1)  
> **Watch out for:** Overflow check must precede multiplication; negatives handled by C++ `%`
