# 🔥 Count Digits

> **LeetCode #2520** · **Difficulty:** Easy · **Step 1 — Basic Maths · P13**

---

## 🧠 Problem Understanding

**What is it asking?**  
Given an integer `num`, return the count of digits in `num` that evenly divide `num`.

**Input:** An integer `num` (1 ≤ num ≤ 10⁹)  
**Output:** Count of digits d in num such that `num % d == 0`

**Key Observations:**
- A digit of 0 can never divide `num` — skip it (division by zero)
- The number itself has `floor(log10(N)) + 1` digits
- We only need to check each digit once

**Simple Example:**
```
Input:  num = 121
Digits: 1, 2, 1
121 % 1 = 0  ✅
121 % 2 = 1  ❌
121 % 1 = 0  ✅
Output: 2
```

---

## 🥉 Brute Force Approach

### Idea
Convert the number to a string, extract each digit as a character, convert back to int, and check divisibility.

### Intuition
Treating the number as a string gives us easy access to each digit character.

### Algorithm
1. Convert `num` to string
2. For each character in the string:
   - Convert char to digit: `d = c - '0'`
   - If `d != 0` and `num % d == 0`, increment count
3. Return count

### Complexity
- **Time:** O(log N) — number of digits = log₁₀(N)
- **Space:** O(log N) — string of digits

### C++ Code
```cpp
// BRUTE FORCE: String conversion approach
int countDigits(int num) {
    string s = to_string(num);   // convert number to string
    int count = 0;
    for (char c : s) {
        int d = c - '0';         // char digit → int digit
        if (d != 0 && num % d == 0)
            count++;
    }
    return count;
}
```

---

## 🥇 Optimal Approach

### Key Observation

> 💡 We can extract digits directly using `% 10` and `/ 10` — no string needed, saves space.

```
num = 121
121 % 10 = 1  → check 121 % 1 == 0 ✅
121 / 10 = 12
 12 % 10 = 2  → check 121 % 2 == 1 ❌
 12 / 10 = 1
  1 % 10 = 1  → check 121 % 1 == 0 ✅
  1 / 10 = 0  → stop
Answer: 2
```

### Intuition
Using arithmetic to extract digits avoids allocating a string. We keep dividing by 10 to "peel off" the last digit, checking each one for divisibility against the original number.

### Algorithm
1. Save original number (since we'll modify the copy)
2. While `n > 0`:
   - Extract last digit: `d = n % 10`
   - If `d != 0` and `num % d == 0`, increment count
   - Remove last digit: `n /= 10`
3. Return count

### Dry Run

**Input:** `num = 1248`

| Iteration | n | d = n%10 | num%d | Count |
|-----------|---|----------|-------|-------|
| Start | 1248 | — | — | 0 |
| 1 | 1248 | 8 | 1248%8 = 0 ✅ | 1 |
| 2 | 124 | 4 | 1248%4 = 0 ✅ | 2 |
| 3 | 12 | 2 | 1248%2 = 0 ✅ | 3 |
| 4 | 1 | 1 | 1248%1 = 0 ✅ | 4 |
| 5 | 0 | — | stop | 4 |

**Output:** `4`

### Complexity
- **Time:** O(log N) — number of digits
- **Space:** O(1) — no extra space

### Why is this optimal?
We can't do better than O(log N) because we must look at every digit at least once. The arithmetic approach achieves this with O(1) space versus the string approach's O(log N) space.

---

## 🎤 Interview Explanation Script

> "The brute force would be converting the number to a string and iterating over characters, but that costs O(log N) space."

> "The optimization comes from using modulo and integer division to extract digits arithmetically."

> "We observe that `num % 10` gives the last digit, and `num / 10` removes it."

> "We need to be careful about digit 0 — it would cause division by zero."

> "Hence we reduce space from O(log N) to O(1), keeping the same O(log N) time."

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * PROBLEM UNDERSTANDING:
 *   Given num, count how many of its digits evenly divide num.
 *
 * EDGE CASES:
 *   - Digit is 0: skip (division by zero)
 *   - Single digit number: just check if it divides itself (always yes unless 0)
 *
 * KEY OBSERVATION:
 *   Extract digits with % 10, remove with / 10. No string needed.
 *
 * COMPLEXITY: Time O(log N) | Space O(1)
 */

class Solution {
public:
    int countDigits(int num) {
        int count = 0;
        int n = num;

        while (n > 0) {
            int digit = n % 10;                        // extract last digit
            if (digit != 0 && num % digit == 0)        // skip 0, check divisibility
                count++;
            n /= 10;                                   // remove last digit
        }

        return count;
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "Extract each digit with `%10`, skip zero, check `num % digit == 0`."

---

## 📝 Short Revision Notes

- Extract digits: `d = n % 10`, then `n /= 10`
- Always skip digit `0` (division by zero)
- Test against original `num`, not the modified `n`
- Time: O(log N) — can't do better, must see every digit
- Space: O(1) — arithmetic beats string conversion
- Number of digits in N = `floor(log₁₀(N)) + 1`

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "for each digit of a number"
- "digit-level operation on an integer"
- "count/sum/check digits"

**I should think of:** Digit extraction via `% 10` and `/ 10` loop

---

## ⚠️ Common Mistakes

❌ Forgetting to skip digit `0` (causes runtime error / undefined behavior)  
❌ Using modified `n` instead of original `num` for divisibility check  
❌ Off-by-one: using `n >= 0` → processes an extra 0 iteration  
❌ Overflow: if num is negative, handle with `abs(num)` first  

---

## 🔥 What Interviewer Is Testing

- **Concept:** Digit extraction using arithmetic
- **Reasoning:** Can you avoid unnecessary data structures?
- **Optimization:** Space reduction from O(log N) → O(1)

---

## 🚀 Alternative Approaches

| Approach | Time | Space | When to use |
|----------|------|-------|-------------|
| Arithmetic (% 10) | O(log N) | O(1) | Always preferred |
| String conversion | O(log N) | O(log N) | When string manipulation needed anyway |

---

## 📚 Related Problems

- [ ] LeetCode #2520 — Count the Digits That Divide a Number
- [ ] LeetCode #1837 — Sum of Digits in Base K
- [ ] LeetCode #263 — Ugly Number (digit-based checking)
- [ ] Striver Step 1 P14 — Reverse a Number (same digit extraction pattern)

---

## 🏆 Pattern Category

`Math` · `Digit Extraction`

---

## 🎯 Difficulty Analysis

**Rating:** Easy

**Why:** Single loop, no data structures, straightforward digit extraction. The only trap is remembering to skip digit 0.

---

## 📈 Progression Insight

**Harder variant:** "Sum of digits that divide N" → same loop, return sum instead of count.  
**Even harder:** "Count digits that divide ALL numbers in an array" → check divisibility against all numbers.  
**LeetCode hard extension:** "Digit DP" problems where you count numbers ≤ N satisfying digit conditions.

---

## ⏱️ 30-Second Last-Minute Revision

> **Problem:** Count digits of `num` that divide `num`  
> **Approach:** Loop: `d = n%10`, skip if `d==0`, count if `num%d==0`, then `n/=10`  
> **Key trick:** Use original `num` for divisibility, modified `n` only to extract digits  
> **Time:** O(log N) | **Space:** O(1)  
> **Watch out for:** Digit 0 causes division by zero — must skip it
