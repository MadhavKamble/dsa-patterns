# 🔥 Sum of First N Numbers

> **Step 1 — Basic Recursion · P24**

---

## 🧠 Problem Understanding

**What is it asking?**  
Find the sum of the first N natural numbers: 1 + 2 + 3 + ... + N.

**Input:** Integer N (1 ≤ N ≤ 10⁵)  
**Output:** Sum = N(N+1)/2

**Simple Example:**
```
N = 5 → 1 + 2 + 3 + 4 + 5 = 15
```

---

## 🥉 Brute Force — Iterative Loop

```cpp
int sumN(int n) {
    int sum = 0;
    for (int i = 1; i <= n; i++) sum += i;
    return sum;
}
// Time O(N), Space O(1)
```

---

## 🥈 Better — Recursive

### Intuition
sum(N) = N + sum(N-1)  
Base case: sum(0) = 0

### Dry Run (N=4)
```
sum(4) = 4 + sum(3)
           = 4 + 3 + sum(2)
                    = 4 + 3 + 2 + sum(1)
                               = 4 + 3 + 2 + 1 + sum(0)
                                                  = 0
Result: 10
```

```cpp
/*
 * RECURSIVE: sum(N) = N + sum(N-1)
 * Base case: sum(0) = 0
 * Time O(N) | Space O(N) call stack
 */
int sumN(int n) {
    if (n == 0) return 0;          // base case
    return n + sumN(n - 1);        // recursive case
}
```

---

## 🥇 Optimal — Mathematical Formula

### Key Observation

> 💡 **Gauss's formula:** Sum of first N numbers = N × (N+1) / 2

**Proof:** Pair up terms: (1+N) + (2+(N-1)) + ... = N/2 pairs, each summing to N+1.

```cpp
/*
 * OPTIMAL: Gauss formula — O(1) time and space
 * Use long long to prevent overflow for large N
 */
long long sumN(long long n) {
    return n * (n + 1) / 2;
}
```

### Complexity
- **Time:** O(1)
- **Space:** O(1)

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * PROBLEM: Sum of first N natural numbers
 *
 * THREE APPROACHES:
 *   Brute:     Loop O(N) | O(1)
 *   Recursive: f(n) = n + f(n-1) | O(N) | O(N)
 *   Optimal:   n*(n+1)/2 | O(1) | O(1)
 *
 * EDGE CASES:
 *   - N=0: return 0
 *   - Large N: use long long (N=10^5 → sum ~ 5*10^9, exceeds INT_MAX)
 */

class Solution {
public:
    // Optimal
    long long sumOfFirstN(long long n) {
        return n * (n + 1) / 2;
    }

    // Recursive (for learning recursion)
    long long sumRecursive(long long n) {
        if (n == 0) return 0;
        return n + sumRecursive(n - 1);
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "Gauss formula: `N*(N+1)/2`. Recursive: `f(n) = n + f(n-1)`, base `f(0)=0`."

---

## 📝 Short Revision Notes

- Formula: N(N+1)/2 — always O(1), prefer this
- Recursive: `f(n) = n + f(n-1)`, base `f(0) = 0`
- Overflow: N=10⁵ → sum ≈ 5×10⁹ → use `long long`
- N=10⁶ → sum ≈ 5×10¹¹ → definitely needs `long long`
- Recursion teaches the pattern, but formula is the interview answer

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- Sum of arithmetic series
- "sum of 1 to N"

**I should think of:** Gauss formula N(N+1)/2, or prefix sums for arrays

---

## ⚠️ Common Mistakes

❌ Integer overflow: `int n = 100000; return n*(n+1)/2;` → overflows  
❌ Deep recursion: N=10⁵ recursive calls → stack overflow  
❌ Base case missing in recursion → infinite loop  

---

## 🔥 What Interviewer Is Testing

- **Concept:** Gauss formula vs recursion understanding
- **Reasoning:** When to use formula over recursion
- **Optimization:** O(N) → O(1) via mathematical insight

---

## 📚 Related Problems

- [ ] LeetCode #2180 — Count Integers With Even Digit Sum
- [ ] LeetCode #1281 — Subtract the Product and Sum of Digits
- [ ] Striver P25 — Factorial (same recursion structure)

---

## 🏆 Pattern Category

`Math` · `Recursion` · `Series Formula`

---

## ⏱️ 30-Second Last-Minute Revision

> **Problem:** Sum of 1 to N  
> **Optimal:** `N*(N+1)/2` — O(1)  
> **Recursive:** `f(n) = n + f(n-1)`, `f(0) = 0`  
> **Watch out for:** Overflow — use `long long` for N > ~65000
