# Count Good Numbers

> **LeetCode #1922** · **Difficulty:** Medium · **Step 7 — Recursion · P03**

---

## 🧠 Problem Understanding

**What is it asking?**
A digit string is "good" if every even-indexed digit is even (0,2,4,6,8) and every odd-indexed digit is prime (2,3,5,7). Count how many good digit strings of length `n` exist. Return answer modulo 10⁹+7.

**Input:** `n = 4` → **Output:** `400`
**Input:** `n = 1` → **Output:** `5`

**Key Observations:**
- Even positions (0, 2, 4, ...): 5 choices each (0,2,4,6,8).
- Odd positions (1, 3, 5, ...): 4 choices each (2,3,5,7).
- Choices at each position are **independent** → multiply them.
- Even position count = `ceil(n/2)` = `(n+1)/2`.
- Odd position count = `floor(n/2)` = `n/2`.
- Answer = `5^evenCount × 4^oddCount % MOD`.
- n can be up to 10¹⁵ → need fast (binary) exponentiation.

**Simple Example:**
```
n=4: positions 0,1,2,3
  even positions: 0,2 → 5 × 5 = 25 ways
  odd  positions: 1,3 → 4 × 4 = 16 ways
  total: 25 × 16 = 400
```

---

## 🥉 Brute Force

Generate all strings of length n and check each — O(10^n). Completely infeasible.

---

## 🥇 Optimal — Math + Modular Binary Exponentiation

### Key Insight

> 💡 Positions are independent, so total = (choices at even positions) × (choices at odd positions) = 5^evenCount × 4^oddCount. Since n ≤ 10¹⁵, compute powers with binary exponentiation under MOD.

### Why Modular Exponentiation?

`evenCount` can be up to ~5×10¹⁴. Computing `5^(5×10^14)` naively is impossible. Binary exponentiation cuts it to O(log n) steps with modular reduction at each step to keep numbers small.

### Algorithm
1. `evenCount = (n+1)/2`, `oddCount = n/2`.
2. `evenWays = power(5, evenCount)`.
3. `oddWays = power(4, oddCount)`.
4. Return `(evenWays * oddWays) % MOD`.

`power(x, n)` — iterative binary exponentiation:
- While `n > 0`: if LSB is 1 → `result = result*x % MOD`. Square x: `x = x*x % MOD`. Shift: `n >>= 1`.

### C++ Code

```cpp
class Solution {
public:
    static const long long MOD=1e9+7;

    long long power(long long x,long long n){
        long long result=1;
        while(n>0){
            if(n&1) result=(result*x)%MOD;
            x=(x*x)%MOD;
            n>>=1;
        }
        return result;
    }

    int countGoodNumbers(long long n){
        long long evenCount=(n+1)/2;
        long long oddCount=n/2;
        long long evenWays=power(5,evenCount);
        long long oddWays=power(4,oddCount);
        return (evenWays*oddWays)%MOD;
    }
};
```

**Time:** O(log N) · **Space:** O(1)

### Dry Run — `n = 4`

```
evenCount = (4+1)/2 = 2
oddCount  = 4/2     = 2

power(5, 2):
  n=2 (10₂): n&1=0 → skip result; x=25; n=1
  n=1 (01₂): n&1=1 → result=25; x=625; n=0
  → 25

power(4, 2):
  n=2: n&1=0; x=16; n=1
  n=1: n&1=1 → result=16; n=0
  → 16

answer = (25 * 16) % MOD = 400 ✓
```

### Dry Run — `n = 1`

```
evenCount = (1+1)/2 = 1
oddCount  = 1/2     = 0

power(5,1) = 5
power(4,0) = 1   ← result stays 1, loop never enters with n=0

answer = 5 * 1 = 5 ✓
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "Even positions → 5 choices, odd → 4 choices. Answer = `5^ceil(n/2) × 4^floor(n/2) % MOD`. Use binary exponentiation (`n&1`, `x*=x`, `n>>=1`) since n up to 10¹⁵."

---

## 📝 Short Revision Notes

- `evenCount = (n+1)/2` works for both even and odd n without branching.
- `n&1` (bitwise AND) checks odd faster than `n%2`; same result for positive n.
- `n>>=1` is `n = n/2` — shifts right, processing next bit.
- Always apply `%MOD` **after each multiplication** to keep intermediate values within `long long`.
- `power(x, 0)` correctly returns 1 — the while loop body never runs.

---

## ⚠️ Common Mistakes

❌ Forgetting `%MOD` inside the power loop — intermediate `x*x` overflows `long long`.
❌ Using `int` return type naively — `evenWays*oddWays` can exceed `int` before the final `%MOD`.
❌ Off-by-one: using `n/2` for even count instead of `(n+1)/2`.
❌ Not applying `%MOD` to the final `evenWays*oddWays` product.

---

## 🧠 Pattern Recognition Trigger

**When I see:** large exponent + modular result → **binary exponentiation with `%MOD` at every step**.

---

## 🏆 Pattern Category

`Recursion` · `Math` · `Modular Arithmetic` · `Binary Exponentiation`

---

## ⏱️ 30-Second Last-Minute Revision

> Even positions: 5 choices. Odd positions: 4 choices. Answer = `5^((n+1)/2) × 4^(n/2) % MOD`. Binary exp: `n&1` check, `x*=x`, `n>>=1`, apply `%MOD` every step. **Time:** O(log N).
