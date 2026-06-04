# 🔥 GCD or HCF (Greatest Common Divisor)

> **LeetCode #1979** (variant) · **Difficulty:** Easy · **Step 1 — Basic Maths · P16**

---

## 🧠 Problem Understanding

**What is it asking?**  
Given two integers `a` and `b`, find their Greatest Common Divisor (GCD) — the largest integer that divides both `a` and `b` without a remainder.

GCD is also called HCF (Highest Common Factor).

**Input:** Two integers a, b (1 ≤ a, b ≤ 10⁹)  
**Output:** GCD(a, b)

**Key Observations:**
- GCD(a, 0) = a (base case)
- GCD(a, b) = GCD(b, a % b) — Euclidean algorithm
- GCD(a, b) × LCM(a, b) = a × b

**Simple Example:**
```
a = 12, b = 8
Divisors of 12: 1, 2, 3, 4, 6, 12
Divisors of 8:  1, 2, 4, 8
Common: 1, 2, 4
GCD = 4
```

---

## 🥉 Brute Force Approach

### Idea
Find all common divisors of both numbers, return the largest.

### Algorithm
1. Loop from 1 to `min(a, b)`
2. For each `i`, if both `a % i == 0` and `b % i == 0`, update answer
3. Return the answer

### Complexity
- **Time:** O(min(a, b))
- **Space:** O(1)

### C++ Code
```cpp
// BRUTE FORCE: Check all numbers up to min(a,b)
int gcd(int a, int b) {
    int ans = 1;
    for (int i = 1; i <= min(a, b); i++) {
        if (a % i == 0 && b % i == 0)
            ans = i;         // keep updating — last valid one is the largest
    }
    return ans;
}
```

---

## 🥈 Better Approach

### Why improve brute force?
O(min(a,b)) is too slow for a, b up to 10⁹. We need something logarithmic.

### Idea
Use the fact that GCD(a, b) = GCD(b, a % b). Loop until remainder is 0.

### Intuition
If `d` divides both `a` and `b`, it also divides `a - b`, and more generally `a mod b`. So the GCD of the original pair equals the GCD of `(b, a mod b)`. This reduces the numbers quickly — the smaller number at least halves every 2 iterations.

### Algorithm
1. While `b != 0`:
   - `temp = b`
   - `b = a % b`
   - `a = temp`
2. Return `a`

### Complexity
- **Time:** O(log(min(a, b)))
- **Space:** O(1) iterative / O(log(min(a,b))) recursive (call stack)

### C++ Code
```cpp
// BETTER: Euclidean algorithm (iterative)
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
```

---

## 🥇 Optimal Approach

### Key Observation

> 💡 The Euclidean Algorithm is already optimal: O(log(min(a,b))).  
> In C++17, `__gcd(a, b)` is built-in. In C++17 STL: `std::gcd(a, b)` from `<numeric>`.

**Proof of O(log N):** After two steps, `a` is replaced by `a mod b`, which is less than `a/2`. So the value of `a` halves every 2 steps → O(log a) steps total.

**Recursive form (elegant):**
```cpp
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}
```

### Dry Run

**Input:** `a = 48, b = 18`

| Step | a | b | a % b |
|------|---|---|-------|
| 1 | 48 | 18 | 48 % 18 = 12 |
| 2 | 18 | 12 | 18 % 12 = 6 |
| 3 | 12 | 6 | 12 % 6 = 0 |
| 4 | 6 | 0 | → stop |

**GCD = 6** ✅

**Verify:** 48 = 6×8, 18 = 6×3 ✓

### Deriving LCM from GCD
```
LCM(a, b) = (a / GCD(a, b)) * b
```
Note: Divide first to avoid overflow: `(a/gcd) * b` not `a*b/gcd`

### Complexity
- **Time:** O(log(min(a, b)))
- **Space:** O(1) iterative

---

## 🎤 Interview Explanation Script

> "The brute force loops from 1 to min(a, b) checking for common divisors — that's O(min(a,b)) which is too slow for inputs up to 10⁹."

> "The optimization comes from Euclid's insight: GCD(a, b) = GCD(b, a mod b). If d divides both a and b, it also divides a mod b."

> "We observe that the modulo operation reduces the numbers rapidly — the value at least halves every two steps."

> "Hence we reduce from O(N) to O(log N), which handles 10⁹ easily."

> "A useful extension: LCM(a, b) = (a / GCD(a, b)) * b. Divide before multiplying to prevent overflow."

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * PROBLEM UNDERSTANDING:
 *   Find largest integer that divides both a and b.
 *
 * EDGE CASES:
 *   - GCD(a, 0) = a
 *   - GCD(0, b) = b
 *   - GCD(1, n) = 1 (always)
 *   - a == b: GCD = a
 *
 * KEY OBSERVATION:
 *   Euclidean: GCD(a,b) = GCD(b, a%b). Reduces problem size by ~half every 2 steps.
 *
 * COMPLEXITY: Time O(log(min(a,b))) | Space O(1)
 */

class Solution {
public:
    // Iterative Euclidean — preferred in interviews (no stack overflow risk)
    int gcd(int a, int b) {
        while (b != 0) {
            a = a % b;     // reduce a
            swap(a, b);    // b becomes new a, remainder becomes new b
        }
        return a;
    }

    // Recursive version (concise, elegant)
    int gcdRecursive(int a, int b) {
        return b == 0 ? a : gcdRecursive(b, a % b);
    }

    // LCM using GCD (avoids overflow by dividing first)
    long long lcm(long long a, long long b) {
        return (a / gcd(a, b)) * b;
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "Euclidean: `while b!=0 → (a,b) = (b, a%b)`. Return a."

---

## 📝 Short Revision Notes

- GCD(a, b) = GCD(b, a%b) — Euclid's theorem
- Base case: GCD(a, 0) = a
- Time: O(log(min(a,b))) — value halves every 2 steps
- LCM = `(a / gcd(a,b)) * b` — divide first to prevent overflow
- C++17: `#include <numeric>` → `std::gcd(a, b)`, `std::lcm(a, b)`
- GCD of array: repeatedly apply gcd to pairs

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "common divisor", "HCF", "GCD"
- "coprime numbers" (GCD = 1)
- "LCM" (use GCD to compute)
- "simplify a fraction"

**I should think of:** Euclidean Algorithm

---

## ⚠️ Common Mistakes

❌ Using `a % b` when `b` could be 0 → always ensure `b != 0` first  
❌ Computing LCM as `a * b / gcd` → `a * b` overflows for large inputs; use `(a / gcd) * b`  
❌ Brute force loop for large inputs → O(10⁹) → TLE  
❌ Forgetting GCD is commutative: GCD(a, b) = GCD(b, a)  

---

## 🔥 What Interviewer Is Testing

- **Concept:** Euclidean algorithm and why it works
- **Reasoning:** Understanding the mathematical invariant (GCD doesn't change under modulo)
- **Optimization:** O(log N) vs O(N), overflow-safe LCM

---

## 🚀 Alternative Approaches

| Approach | Time | Space | When to use |
|----------|------|-------|-------------|
| Euclidean iterative | O(log N) | O(1) | Always preferred |
| Euclidean recursive | O(log N) | O(log N) | Elegant, but stack space |
| Brute force | O(min(a,b)) | O(1) | Only for very small inputs |
| Binary GCD (Stein's) | O(log N) | O(1) | When division is expensive (embedded systems) |

---

## 📚 Related Problems

- [ ] LeetCode #1979 — Find Greatest Common Divisor of Array
- [ ] LeetCode #2447 — Number of Subarrays With GCD Equal to K
- [ ] LeetCode #858 — Mirror Reflection (uses LCM)
- [ ] LeetCode #365 — Water and Jug Problem (uses GCD)
- [ ] Striver Step 1 P17 — Armstrong Number

---

## 🏆 Pattern Category

`Math` · `Number Theory` · `Euclidean Algorithm`

---

## 🎯 Difficulty Analysis

**Rating:** Easy

**Why:** The algorithm is elegant and short. The challenge is knowing the Euclidean theorem and its proof, and the LCM overflow trap.

---

## 📈 Progression Insight

**Harder variant:** GCD of an array → fold GCD across all elements: `gcd(gcd(gcd(a[0], a[1]), a[2]), ...)`  
**Even harder:** Number of pairs (i,j) in array with GCD = k  
**Advanced:** Extended Euclidean Algorithm → find x, y such that `ax + by = gcd(a,b)` (used in modular inverse)

---

## ⏱️ 30-Second Last-Minute Revision

> **Problem:** Find GCD(a, b)  
> **Approach:** `while(b!=0): a=a%b, swap(a,b); return a`  
> **Key trick:** GCD(a,b) = GCD(b, a%b) — modulo preserves GCD  
> **Time:** O(log N) | **Space:** O(1)  
> **Watch out for:** LCM overflow — use `(a/gcd)*b` not `a*b/gcd`
