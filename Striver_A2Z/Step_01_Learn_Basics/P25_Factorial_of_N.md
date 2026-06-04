# 🔥 Factorial of N

> **Step 1 — Basic Recursion · P25**

---

## 🧠 Problem Understanding

**What is it asking?**  
Find N! = 1 × 2 × 3 × ... × N.

**Input:** Integer N (0 ≤ N ≤ 20 for long long range)  
**Output:** N!

**Key Observations:**
- 0! = 1 (by definition)
- N! grows extremely fast: 20! = 2,432,902,008,176,640,000 (fits in `long long`), 21! overflows
- N! = N × (N-1)!

**Simple Example:**
```
5! = 5 × 4 × 3 × 2 × 1 = 120
0! = 1
1! = 1
```

---

## 🥉 Brute Force — Iterative

```cpp
long long factorial(int n) {
    long long result = 1;
    for (int i = 2; i <= n; i++) result *= i;
    return result;
}
// Time O(N), Space O(1)
```

---

## 🥇 Optimal — Recursive

### Key Observation

> 💡 Factorial has perfect recursive structure: `f(n) = n * f(n-1)`, `f(0) = 1`

### Dry Run (N=5)
```
f(5) = 5 * f(4)
            = 5 * 4 * f(3)
                      = 5 * 4 * 3 * f(2)
                                   = 5 * 4 * 3 * 2 * f(1)
                                                     = 5*4*3*2*1*f(0)
                                                                  = 1
Result: 120
```

### Call Stack (builds up, then unwinds)
```
PUSH: f(5) → f(4) → f(3) → f(2) → f(1) → f(0) [base]
POP:  f(0)=1 → f(1)=1 → f(2)=2 → f(3)=6 → f(4)=24 → f(5)=120
```

### Complexity
- **Time:** O(N)
- **Space:** O(N) — call stack depth

### C++ Code
```cpp
/*
 * PROBLEM: N! = N * (N-1) * ... * 1
 *
 * BASE CASE: 0! = 1
 * RECURSIVE: f(n) = n * f(n-1)
 *
 * OVERFLOW: long long holds up to 20! — beyond that use BigInteger
 *
 * COMPLEXITY: Time O(N) | Space O(N)
 */

class Solution {
public:
    // Recursive
    long long factorial(int n) {
        if (n == 0 || n == 1) return 1;   // base case
        return (long long)n * factorial(n - 1);
    }

    // Iterative (preferred in production — no stack overflow risk)
    long long factorialIterative(int n) {
        long long result = 1;
        for (int i = 2; i <= n; i++) result *= i;
        return result;
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "`f(n) = n * f(n-1)`, base `f(0) = 1`. Iterative preferred for N > 10⁴."

---

## 📝 Short Revision Notes

- Base case: `f(0) = f(1) = 1`
- Recursive: `f(n) = n * f(n-1)` — classic example of recursion
- Overflow: `long long` holds up to 20! (≈2.4×10¹⁸)
- For N > 20, need BigInteger / Python's arbitrary precision
- Iterative is preferred in production (no stack overflow for large N)
- Tail recursion: `factorial(n, acc)` with accumulator avoids stack buildup (but C++ doesn't guarantee TCO)

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "number of permutations"
- "nPr, nCr calculations" (use factorial)
- "trailing zeros in N!" → count factors of 5

**I should think of:** Factorial recursion / iterative

---

## ⚠️ Common Mistakes

❌ Base case only for `n==0` but not `n==1` — still works but bad practice  
❌ Using `int` instead of `long long` — overflows at 13!  
❌ Deep recursion for large N → stack overflow  
❌ Forgetting `(long long)n * factorial(n-1)` cast — if factorial returns int, silent overflow  

---

## 🔥 What Interviewer Is Testing

- **Concept:** Classic recursion pattern
- **Reasoning:** Base case identification, overflow awareness
- **Optimization:** When to choose iterative over recursive

---

## 🚀 Alternative Approaches

| Approach | Time | Space | Notes |
|----------|------|-------|-------|
| Recursive | O(N) | O(N) | Classic, teaches recursion |
| Iterative | O(N) | O(1) | Production preferred |
| Tail recursive | O(N) | O(1) with TCO | Elegant but C++ TCO not guaranteed |

---

## 📚 Related Problems

- [ ] LeetCode #172 — Factorial Trailing Zeroes (count factors of 5)
- [ ] LeetCode #793 — Preimage Size of Factorial Zeroes Function
- [ ] LeetCode #62 — Unique Paths (uses factorials via combinations)
- [ ] Striver P24 — Sum of N (same recursion structure)
- [ ] Striver P28 — Fibonacci (multi-branch recursion next step)

---

## 🏆 Pattern Category

`Math` · `Recursion` · `Number Theory`

---

## ⏱️ 30-Second Last-Minute Revision

> **Problem:** Compute N!  
> **Recursive:** `f(n) = n * f(n-1)`, base `f(0) = 1`  
> **Iterative:** Loop 2 to N, multiply into result  
> **Time:** O(N) | **Space:** O(N) recursive, O(1) iterative  
> **Watch out for:** Overflow after 20! — use `long long`; prefer iterative for large N
