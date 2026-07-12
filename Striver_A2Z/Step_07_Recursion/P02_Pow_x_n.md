# Pow(x, n)

> **LeetCode #50** · **Difficulty:** Medium · **Step 7 — Recursion · P02**

---

## 🧠 Problem Understanding

**What is it asking?**
Implement `pow(x, n)` — raise `x` to the power `n` where `n` can be negative.

**Input:** `x = 2.0, n = 10` → **Output:** `1024.0`
**Input:** `x = 2.0, n = -2` → **Output:** `0.25`

**Key Observations:**
- Naïve: multiply `x` by itself `n` times → O(N). TLEs for n up to 2³¹−1.
- `x^n = (x^(n/2))^2` — compute half-power once, square it → halves the problem each step.
- Negative `n`: `x^(-n) = (1/x)^n`. Invert x, negate n before recursing.
- Must use `long` for n: `INT_MIN = −2147483648` and `−INT_MIN` overflows `int`.

---

## 🥉 Brute Force — Linear Multiplication

```cpp
double myPow(double x,int n){
    long N=n;
    if(N<0){ x=1/x; N=-N; }
    double result=1.0;
    for(long i=0;i<N;i++) result*=x;
    return result;
}
```

**Time:** O(N) · **Space:** O(1) — TLE for large N.

---

## 🥇 Optimal — Binary Exponentiation (Fast Power)

### Key Insight

> 💡 `x^n = (x^(n/2))^2`. Compute the sub-result **once** and square it. Odd n: one extra multiply by x. This halves the exponent every call → O(log N).

```
x^10 = (x^5)^2
x^5  = (x^2)^2 · x      ← odd
x^2  = (x^1)^2
x^1  = (x^0)^2 · x      ← odd
x^0  = 1                ← base case
```

### Algorithm
1. `myPow`: if `n < 0`, set `x = 1/x`, `N = -N` (using `long`). Call `helper(x, N)`.
2. `helper(x, n)`:
   - **Base:** `n == 0` → return `1`.
   - `half = helper(x, n/2)`
   - Even: return `half * half`. Odd: return `half * half * x`.

### C++ Code

```cpp
class Solution {
public:
    double helper(double x,long n){
        if(n==0) return 1;
        double half=helper(x,n/2);
        if(n%2==0) return half*half;
        else return half*half*x;
    }

    double myPow(double x,int n){
        long N=n;
        if(n<0){
            x=1/x;
            N=-N;
        }
        return helper(x,N);
    }
};
```

**Time:** O(log N) · **Space:** O(log N) — recursion depth

### Dry Run — `x=2.0, n=10`

| Call | n | half | n%2 | Returns |
|------|---|------|-----|---------|
| helper(2,10) | 10 | helper(2,5) | 0 | half*half |
| helper(2,5) | 5 | helper(2,2) | 1 | half*half*2 |
| helper(2,2) | 2 | helper(2,1) | 0 | half*half |
| helper(2,1) | 1 | helper(2,0) | 1 | half*half*2 |
| helper(2,0) | 0 | — | — | **1** |

Unwind: 1 → 2 → 4 → 32 → **1024** ✓

---

## 🔄 Iterative Variant — O(1) Space

```cpp
double myPow(double x,int n){
    long N=n;
    if(N<0){ x=1/x; N=-N; }
    double result=1.0;
    while(N>0){
        if(N%2==1) result*=x;
        x*=x;
        N/=2;
    }
    return result;
}
```

**Time:** O(log N) · **Space:** O(1)

Same idea: process each bit of N from LSB; multiply result by x when bit is set; always square x.

---

## 🧾 Recall Line *(10-Second Revision)*

> "`x^n = (x^(n/2))^2`. Store half, square it, multiply x once more if odd. Negative n → invert x. Use `long` for INT_MIN safety."

---

## 📝 Short Revision Notes

- Store `helper(x, n/2)` in `half` and reuse it — calling it twice would undo the O(log N) advantage.
- `long N=n` is non-negotiable: `INT_MIN` negation overflows `int`.
- The recursive and iterative versions are exact equivalents; iterative just avoids stack frames.

---

## ⚠️ Common Mistakes

❌ Writing `helper(x,n/2)*helper(x,n/2)` instead of storing in `half` — makes it O(N).
❌ Using `int n` in helper — INT_MIN negation overflows.
❌ Forgetting to handle odd case — wrong answer for all odd exponents.
❌ Not handling negative `n` before the recursive call.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "raise to power efficiently", "modular exponentiation" → `half = f(x, n/2)`, return `half*half` or `half*half*x`.

---

## 🏆 Pattern Category

`Recursion` · `Divide and Conquer` · `Binary Exponentiation` · `Math`

---

## ⏱️ 30-Second Last-Minute Revision

> `x^n = (x^(n/2))^2`. Store half once, square it, ×x if odd. Neg n → invert x, `long` for INT_MIN. **Time:** O(log N) | **Space:** O(log N) recursive / O(1) iterative.
