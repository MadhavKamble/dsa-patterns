# 🔥 Armstrong Number

> **No direct LeetCode** (GFG classic) · **Difficulty:** Easy · **Step 1 — Basic Maths · P17**

---

## 🧠 Problem Understanding

**What is it asking?**  
Given a number N, check if it is an Armstrong number.

An **Armstrong number** (also called Narcissistic number) is a number that equals the sum of its own digits each raised to the power of the number of digits.

**Formula:** For a number with `d` digits: N = d₁ᵈ + d₂ᵈ + ... + dₙᵈ

**Input:** Integer N (1 ≤ N ≤ 10⁹)  
**Output:** `true` if Armstrong, `false` otherwise

**Examples:**
```
153 → 3 digits → 1³ + 5³ + 3³ = 1 + 125 + 27 = 153 ✅
370 → 3 digits → 3³ + 7³ + 0³ = 27 + 343 + 0 = 370 ✅
9474 → 4 digits → 9⁴ + 4⁴ + 7⁴ + 4⁴ = 6561+256+2401+256 = 9474 ✅
123 → 3 digits → 1³ + 2³ + 3³ = 1 + 8 + 27 = 36 ≠ 123 ❌
```

**All 3-digit Armstrong numbers:** 153, 370, 371, 407

---

## 🥉 Brute Force Approach

### Idea
Convert to string to count digits and extract each digit character.

### Algorithm
1. Convert N to string → length = number of digits `d`
2. For each character in string, convert to digit and add `digit^d` to sum
3. Return `sum == N`

### Complexity
- **Time:** O(log N) — processes each digit
- **Space:** O(log N) — string allocation

### C++ Code
```cpp
// BRUTE FORCE: String-based
bool isArmstrong(int n) {
    string s = to_string(n);
    int d = s.length();               // number of digits
    long long sum = 0;

    for (char c : s) {
        int digit = c - '0';
        sum += pow(digit, d);          // digit^d
    }

    return sum == n;
}
```

---

## 🥇 Optimal Approach

### Key Observation

> 💡 Count digits first with arithmetic (or `log10`), then extract digits with `% 10` — no string needed.

```
N = 153
Step 1: count digits → d = 3
Step 2: extract digits and sum:
  153 % 10 = 3 → 3³ = 27
  15  % 10 = 5 → 5³ = 125
  1   % 10 = 1 → 1³ = 1
  sum = 27 + 125 + 1 = 153 == N ✅
```

### Counting digits:
```cpp
int countDigits = (int)log10(n) + 1;   // fast, but floating point rounding risk
// OR safer:
int countDigits(int n) {
    int d = 0;
    while (n > 0) { d++; n /= 10; }
    return d;
}
```

### Algorithm
1. Count number of digits `d`
2. Save original number
3. While `n > 0`:
   - Extract digit: `digit = n % 10`
   - Add `digit^d` to sum
   - Remove digit: `n /= 10`
4. Return `sum == original`

### Dry Run

**Input:** `n = 9474`

Step 1: `d = 4`

| Iteration | n | digit = n%10 | digit⁴ | sum |
|-----------|---|--------------|--------|-----|
| 1 | 9474 | 4 | 256 | 256 |
| 2 | 947 | 7 | 2401 | 2657 |
| 3 | 94 | 4 | 256 | 2913 |
| 4 | 9 | 9 | 6561 | 9474 |
| 5 | 0 | — | stop | |

`sum = 9474 == n = 9474` → **true** ✅

### Complexity
- **Time:** O(log N) — one pass to count, one pass to compute
- **Space:** O(1)

### Implementation note on `pow()`
`pow(digit, d)` returns `double` — floating point precision can cause errors.  
Use integer power function instead:

```cpp
long long intPow(long long base, int exp) {
    long long result = 1;
    while (exp--) result *= base;
    return result;
}
```

---

## 🎤 Interview Explanation Script

> "The brute force converts to string to count digits and extract them — works but uses O(log N) space."

> "The optimization uses arithmetic: count digits with a loop, then extract digits with `% 10`."

> "One important detail: `pow(digit, d)` returns a double, which can have floating point errors. For correctness, use an integer power function."

> "The sum is compared against the original number — so we must save the original before modifying it."

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * PROBLEM UNDERSTANDING:
 *   N is Armstrong if sum of (each digit ^ number_of_digits) == N
 *
 * EDGE CASES:
 *   - Single digit: always Armstrong (n = n^1)
 *   - 0: 0^1 = 0, so 0 is Armstrong
 *   - Use integer pow to avoid floating point errors
 *
 * KEY OBSERVATION:
 *   Count digits first, then extract each digit and accumulate digit^d.
 *
 * COMPLEXITY: Time O(log N) | Space O(1)
 */

class Solution {
private:
    // Integer power to avoid floating point issues
    long long intPow(long long base, int exp) {
        long long result = 1;
        while (exp-- > 0) result *= base;
        return result;
    }

    int countDigits(int n) {
        int d = 0;
        while (n > 0) { d++; n /= 10; }
        return d;
    }

public:
    bool isArmstrong(int n) {
        int d = countDigits(n);        // number of digits
        long long sum = 0;
        int temp = n;

        while (temp > 0) {
            int digit = temp % 10;             // extract last digit
            sum += intPow(digit, d);            // add digit^d
            temp /= 10;                        // remove last digit
        }

        return sum == n;
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "Count digits d, then sum each digit raised to power d, compare to original."

---

## 📝 Short Revision Notes

- Armstrong: N = Σ(digitᵢ^d) where d = number of digits
- Count digits: loop dividing by 10, or `(int)log10(n)+1`
- Avoid `pow()` — use integer power (floating point errors)
- Always save original N before digit extraction loop
- All single-digit numbers are Armstrong (trivially)
- Known Armstrong numbers ≤ 1000: 1,2,3,4,5,6,7,8,9,153,370,371,407

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "digit-level property check"
- "sum of digit powers"
- "narcissistic / perfect digit to power"

**I should think of:** Digit extraction loop + power computation

---

## ⚠️ Common Mistakes

❌ Using `pow(digit, d)` directly → floating point precision errors for large numbers  
❌ Forgetting to save original N (comparing modified n to sum)  
❌ Counting digits with `log10` carelessly → `log10(100)` = 2.0 exactly, but floating point can give 1.9999...  
❌ Not using `long long` for sum → sum of 9⁹ × 9 digits = 387420489 × 9 ≈ 3.5B > INT_MAX  

---

## 🔥 What Interviewer Is Testing

- **Concept:** Digit extraction, power computation
- **Reasoning:** Avoiding floating point pitfalls
- **Optimization:** O(1) space over string approach

---

## 🚀 Alternative Approaches

| Approach | Time | Space | Notes |
|----------|------|-------|-------|
| Arithmetic (optimal) | O(log N) | O(1) | Preferred |
| String-based | O(log N) | O(log N) | Simpler but extra space |

---

## 📚 Related Problems

- [ ] LeetCode #202 — Happy Number (same digit-power-sum pattern)
- [ ] LeetCode #263 — Ugly Number (digit-based check)
- [ ] GFG — Armstrong Numbers in a Range
- [ ] Striver Step 1 P13 — Count Digits
- [ ] Striver Step 1 P18 — Print All Divisors

---

## 🏆 Pattern Category

`Math` · `Digit Extraction` · `Number Properties`

---

## 🎯 Difficulty Analysis

**Rating:** Easy

**Why:** Straightforward once you know the definition. The only real trap is floating point with `pow()`.

---

## 📈 Progression Insight

**Harder variant:** Print all Armstrong numbers in range [1, N]  
**Related:** LeetCode 202 Happy Number — same concept, different sum formula  
**Advanced:** Find Armstrong numbers of any base b (not just base 10)

---

## ⏱️ 30-Second Last-Minute Revision

> **Problem:** Is N an Armstrong number?  
> **Approach:** Count digits `d`. Sum each digit raised to `d`. Compare sum to original N.  
> **Key trick:** Use integer power, not `pow()` — floating point errors  
> **Time:** O(log N) | **Space:** O(1)  
> **Watch out for:** Save original N before modifying; use `long long` for sum
