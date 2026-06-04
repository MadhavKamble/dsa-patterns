# 🔥 Check Palindrome (Number)

> **LeetCode #9** · **Difficulty:** Easy · **Step 1 — Basic Maths · P15**

---

## 🧠 Problem Understanding

**What is it asking?**  
Given an integer `x`, return `true` if `x` is a palindrome — reads the same forward and backward.

**Input:** Integer x (–2³¹ ≤ x ≤ 2³¹ – 1)  
**Output:** `true` if palindrome, `false` otherwise

**Key Observations:**
- All negative numbers are NOT palindromes (because of the `-` sign)
- Numbers ending in 0 (except 0 itself) are NOT palindromes (reversed would have leading zero)
- `0` is a palindrome
- Single digit numbers are always palindromes

**Simple Example:**
```
Input: x = 121 → "121" same forwards & backwards → true
Input: x = -121 → "-121" → "121-" → false
Input: x = 10 → "10" → "01" → false
```

---

## 🥉 Brute Force Approach

### Idea
Convert to string and use two-pointer technique to check if it's a palindrome.

### Algorithm
1. If `x < 0`, return false
2. Convert `x` to string `s`
3. Use two pointers `l=0, r=s.length()-1`
4. While `l < r`: if `s[l] != s[r]` return false; else `l++, r--`
5. Return true

### Complexity
- **Time:** O(log N) — length of number = log₁₀(N)
- **Space:** O(log N) — string allocation

### C++ Code
```cpp
// BRUTE FORCE: String + two pointers
bool isPalindrome(int x) {
    if (x < 0) return false;           // negatives never palindrome

    string s = to_string(x);           // convert to string
    int l = 0, r = s.length() - 1;

    while (l < r) {
        if (s[l] != s[r]) return false;
        l++; r--;
    }
    return true;
}
```

---

## 🥇 Optimal Approach

### Key Observation

> 💡 Only reverse the **second half** of the number and compare with the first half.  
> This avoids full reversal AND solves the overflow problem entirely.

```
x = 1221
First half: 12
Reversed second half: 12
12 == 12 → palindrome ✅

x = 12321 (odd digits)
Keep dividing until rev >= x:
  x=12321, rev=0  → rev=1,   x=1232
  x=1232,  rev=1  → rev=12,  x=123
  x=123,   rev=12 → rev=123, x=12   ← now rev >= x
For odd digits: x == rev/10 (drop middle digit)
12 == 123/10 = 12 ✅
```

### Algorithm
1. If `x < 0`, return false
2. If `x != 0` and `x % 10 == 0`, return false (trailing zero → leading zero after reverse)
3. Build reversed half: while `x > rev`, do `rev = rev*10 + x%10`, `x /= 10`
4. Return `x == rev` (even digits) OR `x == rev/10` (odd digits, drop middle)

### Dry Run

**Input:** `x = 1221`

| Step | x | rev | Condition x > rev? |
|------|---|-----|--------------------|
| Init | 1221 | 0 | 1221 > 0 ✅ continue |
| 1 | 122 | 1 | 122 > 1 ✅ continue |
| 2 | 12 | 12 | 12 > 12 ❌ stop |

`x == rev` → `12 == 12` → **true**

**Input:** `x = 12321`

| Step | x | rev | Condition x > rev? |
|------|---|-----|--------------------|
| Init | 12321 | 0 | ✅ |
| 1 | 1232 | 1 | ✅ |
| 2 | 123 | 12 | ✅ |
| 3 | 12 | 123 | ❌ stop |

`x == rev/10` → `12 == 123/10 = 12` → **true**

**Input:** `x = 1231`

| Step | x | rev | Condition? |
|------|---|-----|-----------|
| Init | 1231 | 0 | ✅ |
| 1 | 123 | 1 | ✅ |
| 2 | 12 | 13 | ❌ stop |

`x == rev` → `12 == 13` ❌ `x == rev/10` → `12 == 1` ❌ → **false**

### Complexity
- **Time:** O(log N) — only process half the digits
- **Space:** O(1) — no string or extra array

### Why is this optimal?
- No string allocation → O(1) space
- Only processes half the digits → constant factor improvement
- Naturally handles overflow (never reverses a number larger than the input)

---

## 🎤 Interview Explanation Script

> "The brute force converts the number to a string and checks palindrome with two pointers — simple, but O(log N) space."

> "The optimization comes from the insight that we only need to reverse half the digits."

> "We observe that when the reversed half meets or exceeds the remaining half, we've processed enough."

> "For even-digit numbers, we check `x == rev`. For odd-digit numbers, the middle digit doesn't matter, so we check `x == rev / 10`."

> "Special cases: negatives are always false, and numbers ending in 0 (except 0 itself) are always false."

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * PROBLEM UNDERSTANDING:
 *   Check if integer x reads same forwards and backwards.
 *
 * EDGE CASES:
 *   - x < 0: never palindrome (has '-' sign)
 *   - x % 10 == 0 and x != 0: trailing zero means leading zero after reverse → not palindrome
 *   - x == 0: palindrome
 *   - Single digit: always palindrome
 *
 * KEY OBSERVATION:
 *   Reverse only second half. Stop when rev >= x.
 *   Even digits: x == rev. Odd digits: x == rev/10 (drop middle digit).
 *
 * COMPLEXITY: Time O(log N) | Space O(1)
 */

class Solution {
public:
    bool isPalindrome(int x) {
        // negative numbers and numbers ending in 0 (except 0) can't be palindromes
        if (x < 0 || (x % 10 == 0 && x != 0))
            return false;

        int rev = 0;
        // reverse only the second half
        while (x > rev) {
            rev = rev * 10 + x % 10;
            x /= 10;
        }

        // even digits: x == rev
        // odd digits: x == rev/10 (middle digit is in rev, discard it)
        return x == rev || x == rev / 10;
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "Reverse half the number; stop when `rev >= x`; check `x == rev` or `x == rev/10`."

---

## 📝 Short Revision Notes

- Negative → always false; ends in 0 (not zero) → always false
- Only reverse the second half of digits
- Stop condition: `x > rev` (when this becomes false, we've done half)
- Even digit count: `x == rev`
- Odd digit count: `x == rev/10` (middle digit is irrelevant)
- Time O(log N), Space O(1)
- This approach also avoids integer overflow from full reversal

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "palindrome check" on a number
- "compare front and back halves"

**I should think of:** Reverse half + meet-in-middle comparison

---

## ⚠️ Common Mistakes

❌ Forgetting the `x % 10 == 0 && x != 0` edge case → 10, 100, etc. would incorrectly pass  
❌ Reversing the full number → risk of overflow for large palindromes  
❌ Using `while (x > 0)` instead of `while (x > rev)` → reverses full number  
❌ Not handling odd-digit numbers → missing the `rev/10` check  

---

## 🔥 What Interviewer Is Testing

- **Concept:** Number palindrome without string conversion
- **Reasoning:** Edge case identification (negative, trailing zero)
- **Optimization:** Half-reversal insight to avoid overflow

---

## 🚀 Alternative Approaches

| Approach | Time | Space | When to use |
|----------|------|-------|-------------|
| Half-reverse (optimal) | O(log N) | O(1) | Always |
| String + two pointers | O(log N) | O(log N) | When string operations are already needed |
| Full reverse + compare | O(log N) | O(1) | Simpler but overflow risk |

---

## 📚 Related Problems

- [ ] LeetCode #9 — Palindrome Number
- [ ] LeetCode #125 — Valid Palindrome (string version)
- [ ] LeetCode #234 — Palindrome Linked List
- [ ] LeetCode #516 — Longest Palindromic Subsequence (DP)
- [ ] Striver Step 1 P14 — Reverse a Number (related technique)

---

## 🏆 Pattern Category

`Math` · `Two Pointers (conceptual)` · `Digit Extraction`

---

## 🎯 Difficulty Analysis

**Rating:** Easy

**Why:** Straightforward once you know the edge cases. The half-reversal trick elevates it to a good interview question.

---

## 📈 Progression Insight

**Harder variant:** Is a string palindrome? (LeetCode 125 — ignore non-alphanumeric)  
**Even harder:** Find longest palindromic substring (LeetCode 5 — expand around center)  
**Follow-up:** How would you handle a `BigInteger` that doesn't fit in any primitive type?

---

## ⏱️ 30-Second Last-Minute Revision

> **Problem:** Is integer x a palindrome?  
> **Approach:** Reject negatives & trailing zeros. Reverse second half until `rev >= x`. Check `x==rev` or `x==rev/10`  
> **Key trick:** Half-reversal avoids overflow and string allocation  
> **Time:** O(log N) | **Space:** O(1)  
> **Watch out for:** `x%10==0 && x!=0` edge case (e.g., 10, 100 are NOT palindromes)
