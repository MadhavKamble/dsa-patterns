# P73 — Integer Operations and Number Theory

## 1. First-Timer Explanation

### What Is It?
**Integer operation** problems use mathematical properties of integers — divisibility, modular arithmetic, prime factorization — to solve problems efficiently without brute force enumeration.

### Key Techniques
1. **GCD/LCM:** Euclidean algorithm in O(log min(a,b))
2. **Modular arithmetic:** `(a + b) % m = ((a % m) + (b % m)) % m`
3. **Fast power:** `a^b mod m` in O(log b) via repeated squaring
4. **Sieve of Eratosthenes:** All primes up to n in O(n log log n)
5. **Integer square root:** Binary search or Newton's method

### GCD Euclidean Algorithm
```
gcd(48, 18):
48 = 2×18 + 12  → gcd(18, 12)
18 = 1×12 + 6   → gcd(12, 6)
12 = 2×6 + 0    → gcd = 6 ✓

Code: gcd(a, b) = b == 0 ? a : gcd(b, a % b)
```

### Fast Modular Exponentiation
```
3^13 mod 1000007:
13 in binary = 1101
3^1 = 3
3^2 = 9
3^4 = 81
3^8 = 6561

3^13 = 3^8 * 3^4 * 3^1 = 6561 * 81 * 3 mod 1000007 = answer
```

### When to Use
- "GCD of multiple numbers" → reduce pairwise
- "LCM(a,b) = a/gcd(a,b) * b"
- "a^b mod m" → fast power
- "All primes up to N" → sieve
- "Count factors of n" → trial division O(√n)

---

## 2. Revision Card

**Recognition Signal:** "GCD", "prime", "modular", "divisible", "factorial mod"

**Core Idea:** Use mathematical properties to reduce O(n) or O(n²) to O(log n) or O(√n).

**Trigger Keywords:** GCD, LCM, prime, sieve, modular, power, divisor, factor

**Complexity:**
| Operation | Time |
|-----------|------|
| GCD | O(log min(a,b)) |
| LCM | O(log min(a,b)) |
| Fast power a^b mod m | O(log b) |
| Sieve of Eratosthenes | O(n log log n) |
| Prime factorization | O(√n) |

---

## 3. Interview Tell Signs

- "Find GCD of array" → reduce with `__gcd(a,b)` or `gcd` from `<numeric>`
- "a^b mod p" with large b → fast power
- "Count primes up to n" → sieve
- "Minimum/maximum LCM/GCD of pairs" → sort + adjacent pairs
- "Number of divisors of n" → O(√n) count

---

## 4. C++ Template

```cpp
#include <numeric>
#include <vector>
using namespace std;

// ── GCD and LCM ───────────────────────────────────────────────────────────────
long long gcd(long long a, long long b) { return b == 0 ? a : gcd(b, a % b); }
long long lcm(long long a, long long b) { return a / gcd(a, b) * b; }
// C++17: std::gcd, std::lcm from <numeric>

// ── Fast Power (a^b mod m) ────────────────────────────────────────────────────
long long powMod(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

// ── Sieve of Eratosthenes ─────────────────────────────────────────────────────
vector<bool> sieve(int n) {
    vector<bool> isPrime(n+1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= n; i++)
        if (isPrime[i])
            for (int j = i*i; j <= n; j += i) isPrime[j] = false;
    return isPrime;
}

// ── Count Divisors of n ───────────────────────────────────────────────────────
int countDivisors(int n) {
    int count = 0;
    for (int i = 1; (long long)i*i <= n; i++) {
        if (n % i == 0) { count++; if (i != n/i) count++; }
    }
    return count;
}
```

---

## 5. How to Present in Interview

**Verbal Script (Fast Power):**
> "To compute a^b mod m: use repeated squaring. If b is odd, multiply result by current base, then divide b by 2. Always square the base. Each step halves b, giving O(log b) multiplications. All intermediate values are taken mod m to prevent overflow."

**Checklist:**
- [ ] GCD: recursive Euclidean, or use `std::gcd` in C++17
- [ ] LCM: `a / gcd(a,b) * b` (divide first to avoid overflow)
- [ ] Fast power: bit-by-bit, O(log b)
- [ ] Sieve: start inner loop at i² (not 2i)
- [ ] Modular arithmetic: apply mod after every multiplication

---

## 6. Problems

### Problem 1: Count Primes
**Difficulty:** Medium | **LC:** 204

```cpp
int countPrimes(int n) {
    if (n < 2) return 0;
    vector<bool> isPrime(n, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; (long long)i*i < n; i++)
        if (isPrime[i])
            for (int j = i*i; j < n; j += i) isPrime[j] = false;
    return count(isPrime.begin(), isPrime.end(), true);
}
// Time: O(n log log n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Pow(x, n)
**Difficulty:** Medium | **LC:** 50

```cpp
double myPow(double x, int n) {
    long long exp = n;
    if (exp < 0) { x = 1.0/x; exp = -exp; }
    double result = 1;
    while (exp) {
        if (exp & 1) result *= x;
        x *= x;
        exp >>= 1;
    }
    return result;
}
// Time: O(log n) | Space: O(1)
// Handle n = INT_MIN: use long long for exp
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Ugly Number II (nth Ugly Number)
**Difficulty:** Medium | **LC:** 264

**Approach:** Three pointers for multiples of 2, 3, 5. Always pick the minimum.

```cpp
int nthUglyNumber(int n) {
    vector<int> ugly(n);
    ugly[0] = 1;
    int i2 = 0, i3 = 0, i5 = 0;
    for (int i = 1; i < n; i++) {
        int next2 = ugly[i2] * 2, next3 = ugly[i3] * 3, next5 = ugly[i5] * 5;
        ugly[i] = min({next2, next3, next5});
        if (ugly[i] == next2) i2++;
        if (ugly[i] == next3) i3++;
        if (ugly[i] == next5) i5++;
    }
    return ugly[n-1];
}
// Time: O(n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: GCD of Strings
**Difficulty:** Easy | **LC:** 1071

**Approach:** GCD string divides both → gcd length divides both lengths. Check: if s+t == t+s, GCD string exists.

```cpp
string gcdOfStrings(string str1, string str2) {
    if (str1 + str2 != str2 + str1) return "";
    int g = __gcd((int)str1.size(), (int)str2.size());
    return str1.substr(0, g);
}
// Time: O(n+m) for string comparison | Space: O(n+m)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Factorial Trailing Zeroes
**Difficulty:** Medium | **LC:** 172

**Approach:** Count factors of 5 (each 5 pairs with a 2 to make 10). Count: n/5 + n/25 + n/125 + ...

```cpp
int trailingZeroes(int n) {
    int count = 0;
    while (n >= 5) { n /= 5; count += n; }
    return count;
}
// Time: O(log n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: Excel Sheet Column Title
**Difficulty:** Easy | **LC:** 168

**Approach:** Base-26 but with A=1..Z=26 (no zero). Convert by decrementing before modding.

```cpp
string convertToTitle(int columnNumber) {
    string res;
    while (columnNumber > 0) {
        columnNumber--; // make it 0-indexed
        res += (char)('A' + columnNumber % 26);
        columnNumber /= 26;
    }
    reverse(res.begin(), res.end());
    return res;
}
// Time: O(log n) | Space: O(log n)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** gcd(48, 36). Apply Euclidean algorithm.
<details><summary>Reveal</summary>
gcd(48,36): 48=1×36+12 → gcd(36,12). 36=3×12+0 → gcd=12. Answer: 12. lcm(48,36) = 48/12*36 = 4*36 = 144.
</details>

**Drill 2:** 2^10 mod 1000. Use fast power.
<details><summary>Reveal</summary>
exp=10=1010. base=2, result=1. bit0=0: result=1, base=4. bit1=1: result=4, base=16. bit2=0: result=4, base=256. bit3=1: result=4*256=1024%1000=24, base=256²=65536%1000=536. Answer: 24.
</details>

**Drill 3:** Sieve: why start inner loop at i² (not i×2)?
<details><summary>Reveal</summary>
All composites of i less than i² have already been marked by a smaller prime factor. For example, 4×3=12 is already marked by prime 2 when i=2. Starting at i² avoids redundant work. Proof: any composite j = i×k where k < i must have a prime factor p ≤ k < i, so j was already marked when we processed p.
</details>

**Drill 4:** Trailing zeroes in 100!. Apply the formula.
<details><summary>Reveal</summary>
100/5=20. 20/5=4. 4/5=0. Total: 20+4=24 trailing zeroes. (There are 24 factors of 5 in 100!, each paired with a factor of 2 to give a trailing zero.)
</details>

**Drill 5:** Column title for 28. Trace the algorithm.
<details><summary>Reveal</summary>
28→27: 27%26=1 → 'A'+1='B', 27/26=1. 1→0: 0%26=0 → 'A'+0='A', 0/26=0. res="BA" reversed="AB". Answer: "AB". (26=Z, 27=AA, 28=AB ✓)
</details>

---

## 8. Complexity Cheatsheet

| Algorithm | Time | Space |
|-----------|------|-------|
| GCD (Euclidean) | O(log min(a,b)) | O(1) |
| LCM | O(log min(a,b)) | O(1) |
| Fast Power | O(log b) | O(1) |
| Sieve of Eratosthenes | O(n log log n) | O(n) |
| Factorization (trial) | O(√n) | O(log n) |
| Count divisors | O(√n) | O(1) |

---

## 9. Common Follow-up Questions

**Q: Modular inverse of a (mod p)?**
A: If p is prime: `a^(p-2) mod p` (Fermat's little theorem). Or extended Euclidean algorithm for general moduli.

**Q: Chinese Remainder Theorem?**
A: Find x such that x ≡ r₁ mod m₁ and x ≡ r₂ mod m₂. Use CRT formula when gcd(m₁,m₂)=1.

**Q: Is there a faster sieve?**
A: Linear sieve runs in O(n) by marking each composite exactly once. More complex to implement.

---

## 10. Cross-Pattern Connections

- **P71 (Bit Counting):** `__builtin_popcount` is integer operation; complement here
- **P70 (XOR):** Both are integer manipulation; XOR for cancellation, math for structure
- **P30 (1D DP):** Ugly numbers use DP with mathematical insight
- **P58 (Greedy Math):** Integer break uses mathematical properties of 3 and 2
