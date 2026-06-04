# 🔥 Fibonacci Number

> **LeetCode #509** · **Difficulty:** Easy · **Step 1 — Basic Recursion · P28**

---

## 🧠 Problem Understanding

**What is it asking?**  
Given N, return the Nth Fibonacci number.

**Definition:**
```
F(0) = 0
F(1) = 1
F(N) = F(N-1) + F(N-2)   for N >= 2
```

**Input:** Integer N (0 ≤ N ≤ 30)  
**Output:** F(N)

**Sequence:** 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...

**Simple Example:**
```
N = 0 → 0
N = 1 → 1
N = 5 → F(4) + F(3) = 3 + 2 = 5
N = 10 → 55
```

---

## 🥉 Brute Force — Naive Recursion

### Idea
Directly implement the definition: `F(N) = F(N-1) + F(N-2)`.

### Problem: Exponential Time
```
         F(5)
        /    \
      F(4)   F(3)
      /  \   /  \
    F(3) F(2) F(2) F(1)
    / \
  F(2) F(1)
```
**F(3) is computed twice, F(2) three times.** This causes O(2ᴺ) time.

### Complexity
- **Time:** O(2ᴺ) — exponential, very bad
- **Space:** O(N) call stack depth

```cpp
// BRUTE: Naive recursion — DO NOT USE for N > 30 due to O(2^N)
int fib(int n) {
    if (n <= 1) return n;             // base cases: F(0)=0, F(1)=1
    return fib(n - 1) + fib(n - 2);  // overlapping subproblems!
}
```

---

## 🥈 Better — Memoization (Top-Down DP)

### Why improve?
Naive recursion recomputes F(k) multiple times. Cache the results.

### Idea
Store already-computed values in an array. Before computing, check if cached.

### Complexity
- **Time:** O(N) — each value computed once
- **Space:** O(N) — memo array + call stack

```cpp
// BETTER: Memoization (top-down DP)
int fibMemo(int n, vector<int>& memo) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];        // return cached result
    memo[n] = fibMemo(n-1, memo) + fibMemo(n-2, memo);
    return memo[n];
}

int fib(int n) {
    vector<int> memo(n + 1, -1);
    return fibMemo(n, memo);
}
```

---

## 🥇 Optimal — Iterative (Bottom-Up DP / Space-Optimized)

### Key Observation

> 💡 F(N) only depends on F(N-1) and F(N-2) — we only need the last two values, not the full array.

### Algorithm
1. Handle base cases: N=0 → 0, N=1 → 1
2. Use two variables `prev2=0, prev1=1`
3. For i from 2 to N: `curr = prev1 + prev2`, update `prev2=prev1, prev1=curr`
4. Return `prev1`

### Dry Run

**Input:** `N = 7`

| i | prev2 | prev1 | curr = prev1+prev2 |
|---|-------|-------|-------------------|
| — | 0 (F0) | 1 (F1) | — |
| 2 | 1 | 1 | 0+1=1 |
| 3 | 1 | 2 | 1+1=2 |
| 4 | 2 | 3 | 1+2=3 |
| 5 | 3 | 5 | 2+3=5 |
| 6 | 5 | 8 | 3+5=8 |
| 7 | 8 | 13 | 5+8=13 |

**Output:** `13` ✅  F(7) = 13

### Complexity
- **Time:** O(N)
- **Space:** O(1) — only two variables

### C++ Code
```cpp
/*
 * PROBLEM: Compute Nth Fibonacci number
 *
 * APPROACHES:
 *   Naive recursion: O(2^N) time — shows overlapping subproblems
 *   Memoization:    O(N) time, O(N) space
 *   Iterative DP:   O(N) time, O(N) space
 *   Space-optimized: O(N) time, O(1) space ← BEST
 *   Matrix expo:    O(log N) time, O(1) space ← advanced
 *
 * EDGE CASES: N=0 → 0, N=1 → 1
 *
 * COMPLEXITY: Time O(N) | Space O(1)
 */

class Solution {
public:
    // Space-optimized iterative — best for interviews
    int fib(int n) {
        if (n <= 1) return n;

        int prev2 = 0;   // F(0)
        int prev1 = 1;   // F(1)

        for (int i = 2; i <= n; i++) {
            int curr = prev1 + prev2;   // F(i) = F(i-1) + F(i-2)
            prev2 = prev1;              // slide window forward
            prev1 = curr;
        }

        return prev1;
    }
};
```

---

## 🚀 Bonus: O(log N) — Matrix Exponentiation

For very large N (e.g., N = 10¹⁸), we use matrix exponentiation:

```
[F(n+1)]   [1 1]^n   [F(1)]   [1 1]^n   [1]
[F(n)  ] = [1 0]   × [F(0)] = [1 0]   × [0]
```

Raise the matrix to power N using fast exponentiation → O(log N).

```cpp
// Matrix multiplication helper
typedef vector<vector<long long>> Matrix;

Matrix multiply(Matrix& A, Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

Matrix matpow(Matrix M, long long p) {
    Matrix result = {{1,0},{0,1}};  // identity matrix
    while (p > 0) {
        if (p & 1) result = multiply(result, M);
        M = multiply(M, M);
        p >>= 1;
    }
    return result;
}

long long fibFast(long long n) {
    if (n <= 1) return n;
    Matrix M = {{1,1},{1,0}};
    Matrix result = matpow(M, n);
    return result[0][1];
}
// Time O(log N), Space O(1)
```

---

## 🎤 Interview Explanation Script

> "The naive recursive solution directly implements the definition but recomputes subproblems — for example F(3) is calculated 3 times for F(6). This gives O(2ᴺ) time."

> "The first optimization is memoization — cache results to ensure each F(k) is computed only once, giving O(N) time and O(N) space."

> "But we observe that F(N) only depends on the last two values. So we can drop the cache and use just two variables, reducing space to O(1)."

> "For very large N, matrix exponentiation gives O(log N) time — but for N ≤ 30 as on LeetCode, the iterative O(N) solution is more than sufficient."

---

## 🧾 Recall Line *(10-Second Revision)*

> "Two variables `a=0, b=1`. Loop: `c=a+b, a=b, b=c`. Return `b`."

---

## 📝 Short Revision Notes

- Naive recursion = O(2ᴺ) due to overlapping subproblems
- Memoization = top-down DP, O(N) time + O(N) space
- Bottom-up iterative DP = O(N) time + O(N) space
- Space-optimized = O(N) time + O(1) space (only 2 vars needed)
- Matrix exponentiation = O(log N) for very large N
- Fibonacci is the **canonical example** of DP (overlapping + optimal substructure)

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "each value depends on previous two"
- "number of ways to climb stairs" (same recurrence!)
- "tiling problems" (often reduce to Fibonacci)

**I should think of:** Fibonacci recurrence → space-optimized DP with 2 variables

---

## ⚠️ Common Mistakes

❌ Using naive recursion in interview — O(2ᴺ) is immediately wrong for large N  
❌ Forgetting base cases: F(0)=0, not F(0)=1  
❌ Not recognizing "Climbing Stairs" (LC 70) as identical to Fibonacci  
❌ Using `int` for large N → overflow (F(50) > INT_MAX)  

---

## 🔥 What Interviewer Is Testing

- **Concept:** Recognizing overlapping subproblems
- **Reasoning:** Memoization → iterative DP progression
- **Optimization:** Space from O(N) → O(1) by observing dependency structure

---

## 🚀 All Approaches Compared

| Approach | Time | Space | Notes |
|----------|------|-------|-------|
| Naive recursion | O(2ᴺ) | O(N) | Never use |
| Memoization | O(N) | O(N) | Top-down DP |
| Iterative DP (array) | O(N) | O(N) | Bottom-up DP |
| Space-optimized | O(N) | O(1) | Best for interviews |
| Matrix exponentiation | O(log N) | O(1) | For very large N |
| Closed form (Binet's) | O(1) | O(1) | Floating point imprecision |

---

## 📚 Related Problems

- [ ] LeetCode #509 — Fibonacci Number
- [ ] LeetCode #70 — Climbing Stairs (identical recurrence!)
- [ ] LeetCode #1137 — N-th Tribonacci Number (3-way recurrence)
- [ ] LeetCode #746 — Min Cost Climbing Stairs
- [ ] Striver Step 16 — DP (Fibonacci is the gateway problem)

---

## 🏆 Pattern Category

`Recursion` · `Dynamic Programming` · `Math`

---

## 🎯 Difficulty Analysis

**Rating:** Easy (but conceptually rich)

**Why challenging:** The problem is easy; the point is understanding WHY naive recursion is wrong and HOW to improve it — this is the foundation of DP thinking.

---

## 📈 Progression Insight

**Climbing Stairs (LC 70):** "N steps, can take 1 or 2 at a time — how many ways?" → Identical to Fibonacci  
**Tribonacci (LC 1137):** F(N) = F(N-1) + F(N-2) + F(N-3) → extend to 3 variables  
**Matrix expo:** For F(10¹⁸) → O(log N) unavoidable  
**DP generalization:** Any problem where answer = sum of last k answers → use sliding window of k variables

---

## ⏱️ 30-Second Last-Minute Revision

> **Problem:** Find Nth Fibonacci number  
> **Approach:** `prev2=0, prev1=1`. Loop i=2 to N: `curr=prev1+prev2, prev2=prev1, prev1=curr`. Return `prev1`.  
> **Key trick:** Only last 2 values needed → O(1) space  
> **Time:** O(N) | **Space:** O(1)  
> **Watch out for:** Naive recursion is O(2ᴺ) — always mention DP; F(0)=0 not 1
