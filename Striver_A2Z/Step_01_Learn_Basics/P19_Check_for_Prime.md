# 🔥 Check for Prime

> **LeetCode #866** (variant) · **Difficulty:** Easy · **Step 1 — Basic Maths · P19**

---

## 🧠 Problem Understanding

**What is it asking?**  
Given a number N, determine if it is a prime number.

A **prime number** is a natural number greater than 1 that has no positive divisors other than 1 and itself.

**Input:** Integer N (1 ≤ N ≤ 10⁹)  
**Output:** `true` if prime, `false` otherwise

**Key Observations:**
- Numbers ≤ 1 are NOT prime (by definition)
- 2 is the only even prime
- All even numbers > 2 are NOT prime
- If N has no divisor in [2, √N], it's prime
- Any composite number N must have a factor ≤ √N

**Simple Example:**
```
N = 13 → no divisors in [2,3] (√13 ≈ 3.6) → Prime ✅
N = 12 → 12 % 2 = 0 → Not Prime ❌
N = 1  → Not Prime (by definition) ❌
N = 2  → Prime ✅
```

---

## 🥉 Brute Force Approach

### Idea
Check if any number from 2 to N-1 divides N.

### Algorithm
1. If N ≤ 1, return false
2. For i from 2 to N-1: if `N % i == 0`, return false
3. Return true

### Complexity
- **Time:** O(N)
- **Space:** O(1)

### C++ Code
```cpp
// BRUTE FORCE: Check all from 2 to N-1
bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i < n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}
```

---

## 🥈 Better Approach

### Why improve?
O(N) is too slow for N = 10⁹. Checking up to N/2 is only 2× faster — still O(N).

### Idea
Check only up to √N. Any composite N must have at least one factor ≤ √N.

**Proof:** If N = a × b and both a > √N and b > √N, then a × b > N — contradiction. So at least one factor ≤ √N.

### Algorithm
1. If N ≤ 1, return false
2. For i from 2 to √N: if `N % i == 0`, return false
3. Return true

### Complexity
- **Time:** O(√N)
- **Space:** O(1)

### C++ Code
```cpp
// BETTER: Loop to sqrt(N)
bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; (long long)i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}
```

---

## 🥇 Optimal Approach

### Key Observation

> 💡 **Optimization 1:** Skip even numbers after checking 2 → half the iterations.  
> 💡 **Optimization 2:** All primes > 3 are of the form `6k ± 1`. Check only those.

**Why 6k ± 1?**  
Among any 6 consecutive integers, only 2 can be prime:
- 6k+0: divisible by 6
- 6k+1: possibly prime ✅
- 6k+2: divisible by 2
- 6k+3: divisible by 3
- 6k+4: divisible by 2
- 6k+5: possibly prime ✅ (= 6(k+1)-1)

So after checking 2 and 3, only check numbers of form 6k±1.

```
For N=97:
Check 2 → 97%2≠0
Check 3 → 97%3≠0
6k-1: 5, 11, 17, 23, 29, 31...  (√97 ≈ 9.8)
Check 5 → 97%5≠0
Check 7 → 97%7≠0
Next would be 11 > √97 → stop → PRIME ✅
```

### Algorithm
1. If N ≤ 1, return false
2. If N ≤ 3, return true
3. If N % 2 == 0 or N % 3 == 0, return false
4. For i from 5 to √N, step 6: check `i` and `i+2`
5. If none divide N, return true

### Dry Run

**Input:** `n = 49`

| Step | Check | Result |
|------|-------|--------|
| n > 1? | 49 > 1 | ✅ |
| n ≤ 3? | 49 > 3 | continue |
| n%2==0? | 49%2=1 | ❌ not divisible |
| n%3==0? | 49%3=1 | ❌ not divisible |
| i=5: n%5 | 49%5=4 | ❌ |
| i=5: n%(5+2)=n%7 | 49%7=0 | ✅ divisible! → **false** |

**Output:** `false` (49 = 7 × 7)

**Input:** `n = 37`

| Step | Check | Result |
|------|-------|--------|
| n > 1? | ✅ | |
| n%2? n%3? | 37%2=1, 37%3=1 | not divisible |
| i=5: 37%5=2, 37%7=2 | ❌ | |
| Next i=11, 11² = 121 > 37 → stop | | |

**Output:** `true` ✅

### Complexity
- **Time:** O(√N / 3) ≈ O(√N) — checks only 1/3 of candidates
- **Space:** O(1)

---

## 🎤 Interview Explanation Script

> "The brute force checks all numbers from 2 to N — that's O(N), far too slow for N = 10⁹."

> "The first optimization: any composite N must have a factor ≤ √N, so we only need to check up to √N — O(√N)."

> "We can further optimize using the fact that all primes greater than 3 are of the form 6k ± 1. Every other number is divisible by 2 or 3. So after checking 2 and 3, we step by 6 and check i and i+2."

> "This reduces the constant factor by ~3×, giving O(√N/3) — practically faster though asymptotically the same."

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * PROBLEM UNDERSTANDING:
 *   Check if N is prime (divisible only by 1 and itself).
 *
 * EDGE CASES:
 *   - N <= 1: not prime
 *   - N == 2 or N == 3: prime
 *   - N even: not prime (except 2)
 *   - Overflow: use (long long)i*i <= n
 *
 * KEY OBSERVATION:
 *   All primes > 3 are of form 6k±1. After checking 2 and 3,
 *   iterate i=5,11,17,... (step 6) and check i and i+2.
 *
 * COMPLEXITY: Time O(√N) | Space O(1)
 */

class Solution {
public:
    bool isPrime(int n) {
        if (n <= 1) return false;     // 0, 1 not prime
        if (n <= 3) return true;      // 2, 3 are prime
        if (n % 2 == 0 || n % 3 == 0)
            return false;             // eliminate multiples of 2 and 3

        // check only numbers of form 6k±1
        for (int i = 5; (long long)i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0)
                return false;
        }

        return true;
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "Check 2,3 specially. Then loop i=5,11,17,... (step 6), check i and i+2 up to √N."

---

## 📝 Short Revision Notes

- N ≤ 1 → false; N ≤ 3 → true
- N%2==0 or N%3==0 (and N>3) → false
- All primes > 3 have form 6k±1
- Loop i=5 to √N, step 6: check i and i+2
- Overflow: `(long long)i*i <= n`
- Basic √N check is always acceptable in interviews; 6k±1 is a bonus
- For multiple queries: use Sieve of Eratosthenes O(N log log N)

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "is prime"
- "prime factorization"
- "count primes up to N"
- "smallest prime factor"

**I should think of:**
- Single check → O(√N) trial division
- Multiple queries → Sieve of Eratosthenes
- Very large N → Miller-Rabin probabilistic test

---

## ⚠️ Common Mistakes

❌ Looping to N-1 instead of √N → O(N) TLE  
❌ Forgetting edge cases: N=0, N=1, N=2, N=3  
❌ `i*i <= n` overflows for large n → use `(long long)i*i`  
❌ Off-by-one: using `i*i < n` misses `i*i == n` case (e.g., N=9, i=3)  
❌ Starting loop from 1 → 1 divides everything, always returns false  

---

## 🔥 What Interviewer Is Testing

- **Concept:** √N optimization for primality
- **Reasoning:** Why checking to √N is sufficient (factor pair argument)
- **Optimization:** 6k±1 trick and Sieve knowledge

---

## 🚀 Alternative Approaches

| Approach | Time | Space | When to use |
|----------|------|-------|-------------|
| 6k±1 trial division | O(√N) | O(1) | Single query |
| Basic √N trial division | O(√N) | O(1) | Simple interview answer |
| Sieve of Eratosthenes | O(N log log N) | O(N) | Multiple queries up to N |
| Miller-Rabin | O(k log² N) | O(1) | Very large N (cryptography) |

---

## 📚 Related Problems

- [ ] LeetCode #204 — Count Primes (Sieve of Eratosthenes)
- [ ] LeetCode #231 — Power of Two (similar divisibility check)
- [ ] LeetCode #866 — Prime Palindrome
- [ ] LeetCode #1175 — Prime Arrangements
- [ ] Striver Step 1 P18 — Print All Divisors (same √N principle)

---

## 🏆 Pattern Category

`Math` · `Number Theory` · `Square Root Trick`

---

## 🎯 Difficulty Analysis

**Rating:** Easy

**Why:** The √N idea is the key insight. The 6k±1 optimization shows deeper understanding — bonus points in interviews.

---

## 📈 Progression Insight

**Harder variant:** Count all primes less than N → Sieve of Eratosthenes  
**Even harder:** Smallest prime factor of each number in [1, N] → linear sieve  
**Advanced:** Prime factorization of N → repeatedly find smallest prime factor  
**Competitive:** Miller-Rabin for primality of 64-bit numbers

---

## ⏱️ 30-Second Last-Minute Revision

> **Problem:** Is N prime?  
> **Approach:** Return false if N≤1. Return true if N≤3. Check N%2 and N%3. Then loop i=5 to √N (step 6), check i and i+2.  
> **Key trick:** All primes > 3 are 6k±1; check only those candidates  
> **Time:** O(√N) | **Space:** O(1)  
> **Watch out for:** Edge cases (0,1,2,3); `(long long)i*i` for overflow
