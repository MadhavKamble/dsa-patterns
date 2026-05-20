# P71 — Bit Counting and Powers of Two

## 1. First-Timer Explanation

### What Is It?
**Bit counting** problems count the number of set bits (1s) in numbers, detect powers of 2, or count bits for all numbers in a range. The key tricks:
- `n & (n-1)` removes the lowest set bit of n
- `n & (-n)` isolates the lowest set bit of n
- Power of 2: exactly one bit set → `n > 0 && (n & (n-1)) == 0`
- Popcount: Brian Kernighan's algorithm or DP with `dp[n] = dp[n >> 1] + (n & 1)`

### Brian Kernighan's Algorithm
```
Count set bits by repeatedly removing the lowest set bit:
n = 7 = 111
n & (n-1) = 111 & 110 = 110 (removed lowest bit) → count=1
n = 110
n & (n-1) = 110 & 101 = 100 → count=2
n = 100
n & (n-1) = 100 & 011 = 000 → count=3
n = 0, done. 7 has 3 set bits ✓
```

### Count Bits DP
```
dp[0] = 0
dp[n] = dp[n >> 1] + (n & 1)

n=5 (101): dp[5] = dp[2] + 1 = dp[1] + 0 + 1 = 1 + 1 = 2 ✓
n=6 (110): dp[6] = dp[3] + 0 = 2 + 0 = 2 ✓
n=7 (111): dp[7] = dp[3] + 1 = 2 + 1 = 3 ✓
```

### When to Use
- "Count set bits in a single number" → Brian Kernighan O(k) where k = set bits
- "Count bits for all n in [0..n]" → DP O(n)
- "Is n a power of 2?" → `n > 0 && (n & (n-1)) == 0`
- "Is n a power of 4?" → power of 2 AND set bit at even position: `n > 0 && (n & (n-1)) == 0 && (n & 0x55555555) != 0`

---

## 2. Revision Card

**Recognition Signal:** "count bits", "number of 1s", "power of 2/4", "hamming weight"

**Core Idea:**
- Single: `n & (n-1)` removes lowest set bit; count iterations
- Array [0..n]: `dp[i] = dp[i>>1] + (i&1)` (shift + LSB)
- Power of 2: exactly one set bit → `n & (n-1) == 0`

**Trigger Keywords:** set bits, Hamming weight, popcount, power of 2, counting bits

**Complexity:** O(k) per number (k=set bits), O(n) for [0..n] range

---

## 3. Interview Tell Signs

- "Hamming weight / number of 1-bits" → Brian Kernighan's
- "Count bits for all numbers 0 to n" → DP with right-shift
- "Check if power of 2" → `n & (n-1) == 0`
- "Two numbers: find count of bits that differ" → `popcount(a ^ b)`
- "Number of flips to convert a to b" → `popcount(a ^ b)`

---

## 4. C++ Template

```cpp
#include <vector>
using namespace std;

// ── Hamming Weight (count set bits in n) ─────────────────────────────────────
int hammingWeight(uint32_t n) {
    int count = 0;
    while (n) { n &= (n - 1); count++; } // remove lowest set bit
    return count;
}

// ── Count Bits for [0..n] in O(n) ────────────────────────────────────────────
vector<int> countBits(int n) {
    vector<int> dp(n + 1, 0);
    for (int i = 1; i <= n; i++)
        dp[i] = dp[i >> 1] + (i & 1); // dp[i/2] + LSB
    return dp;
}

// ── Power of Two ──────────────────────────────────────────────────────────────
bool isPowerOfTwo(int n) { return n > 0 && (n & (n-1)) == 0; }

// ── Power of Four ─────────────────────────────────────────────────────────────
bool isPowerOfFour(int n) {
    return n > 0 && (n & (n-1)) == 0 && (n & 0x55555555) != 0;
    // 0x55555555 = 01010101...01: checks set bit is at even position (0,2,4,...)
}

// ── Hamming Distance (bits that differ) ──────────────────────────────────────
int hammingDistance(int x, int y) {
    int diff = x ^ y;
    int count = 0;
    while (diff) { diff &= (diff-1); count++; }
    return count;
}
```

---

## 5. How to Present in Interview

**Verbal Script (Count Bits DP):**
> "For all numbers [0..n]: `dp[i] = dp[i/2] + (i & 1)`. If I right-shift i by 1, I get i/2 which has already been computed. The lowest bit (LSB) is either 0 or 1. So the bit count of i = bit count of i/2 + whether i is odd. This DP builds from 0 to n in O(n) total."

**Checklist:**
- [ ] Single number: Brian Kernighan O(k)
- [ ] Range [0..n]: DP with `dp[i>>1] + (i&1)`
- [ ] Power of 2: `n > 0 && (n & (n-1)) == 0`
- [ ] Hamming distance: `popcount(a ^ b)`
- [ ] Built-in: `__builtin_popcount(n)` in C++

---

## 6. Problems

### Problem 1: Number of 1 Bits (Hamming Weight)
**Difficulty:** Easy | **LC:** 191

```cpp
int hammingWeight(uint32_t n) {
    int count = 0;
    while (n) { n &= n-1; count++; }
    return count;
    // Alternative: return __builtin_popcount(n);
}
// Time: O(k) k=set bits ≤ 32 | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Counting Bits
**Difficulty:** Easy | **LC:** 338

```cpp
vector<int> countBits(int n) {
    vector<int> dp(n+1);
    for (int i = 1; i <= n; i++) dp[i] = dp[i>>1] + (i&1);
    return dp;
}
// Time: O(n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Power of Two
**Difficulty:** Easy | **LC:** 231

```cpp
bool isPowerOfTwo(int n) { return n > 0 && (n & (n-1)) == 0; }
// Time: O(1) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Hamming Distance
**Difficulty:** Easy | **LC:** 461

```cpp
int hammingDistance(int x, int y) {
    return __builtin_popcount(x ^ y);
}
// Time: O(1) | Space: O(1)
// Or: int d=x^y, count=0; while(d){d&=d-1;count++;} return count;
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Total Hamming Distance
**Difficulty:** Medium | **LC:** 477

**Approach:** For each bit position, count ones and zeros. Pairs = ones × zeros.

```cpp
int totalHammingDistance(vector<int>& nums) {
    int total = 0, n = nums.size();
    for (int bit = 0; bit < 32; bit++) {
        int ones = 0;
        for (int x : nums) ones += (x >> bit) & 1;
        total += ones * (n - ones); // pairs differing at this bit
    }
    return total;
}
// Time: O(32n) = O(n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: Reverse Bits
**Difficulty:** Easy | **LC:** 190

```cpp
uint32_t reverseBits(uint32_t n) {
    uint32_t res = 0;
    for (int i = 0; i < 32; i++) {
        res = (res << 1) | (n & 1);
        n >>= 1;
    }
    return res;
}
// Time: O(32) = O(1) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** What does `n & (n-1)` do? Show for n=12 (1100).
<details><summary>Reveal</summary>
Removes the lowest set bit. n=12=1100. n-1=1011. n&(n-1)=1100&1011=1000. The lowest set bit (the '1' at position 2) is removed. Result: 8=1000.
</details>

**Drill 2:** Count bits for [0..7] using DP. Fill the table.
<details><summary>Reveal</summary>
dp[0]=0. dp[1]=dp[0]+1=1. dp[2]=dp[1]+0=1. dp[3]=dp[1]+1=2. dp[4]=dp[2]+0=1. dp[5]=dp[2]+1=2. dp[6]=dp[3]+0=2. dp[7]=dp[3]+1=3. Table: [0,1,1,2,1,2,2,3].
</details>

**Drill 3:** Is 1024 a power of two? Verify with the formula.
<details><summary>Reveal</summary>
1024 = 2^10 = 10000000000. n>0: yes. n&(n-1) = 1024 & 1023 = 10000000000 & 01111111111 = 0. Yes, power of 2. ✓
</details>

**Drill 4:** Total Hamming distance for [4,14,2]. For bit 1, how many pairs differ?
<details><summary>Reveal</summary>
4=100, 14=1110, 2=010. Bit 1 (value 2): 4 has 0, 14 has 1, 2 has 1. Ones=2, zeros=1. Pairs differing = 2×1=2. (Pairs: (4,14) and (2,14) differ at bit 1; (4,2) don't.) ✓
</details>

**Drill 5:** Reverse bits of 43261596 = 00000010100101000001111010011100.
<details><summary>Reveal</summary>
Read bits right to left: 00111001011110000010100101000000 = 964176192. (This is a standard LC 190 problem — the key insight is reading each LSB of n and making it the MSB of result by left-shifting result and right-shifting n.)
</details>

---

## 8. Complexity Cheatsheet

| Operation | Time | Space | C++ Built-in |
|-----------|------|-------|------|
| Count set bits (single) | O(k) | O(1) | `__builtin_popcount(n)` |
| Count bits [0..n] | O(n) | O(n) | — |
| Power of 2 check | O(1) | O(1) | — |
| Hamming distance | O(1) | O(1) | `__builtin_popcount(a^b)` |
| Reverse bits | O(32) | O(1) | — |
| Total Hamming distance | O(32n) | O(1) | — |

---

## 9. Common Follow-up Questions

**Q: Fastest way to count set bits in C++?**
A: `__builtin_popcount(n)` compiles to a single `POPCNT` hardware instruction on modern CPUs.

**Q: Count set bits from 1 to n without computing each separately?**
A: Mathematical approach using bit position analysis. For each bit position k, count complete groups of 2^(k+1) and partial group. O(log n) formula.

**Q: What if you need the POSITION of the highest set bit?**
A: `31 - __builtin_clz(n)` (count leading zeros). Or loop from bit 31 downward.

---

## 10. Cross-Pattern Connections

- **P70 (XOR Tricks):** XOR tells WHERE bits differ; this counts HOW MANY bits differ
- **P72 (Bit Tricks):** Masking and shifting operations build on these fundamentals
- **P36 (Bitmask DP):** Bit counting used to check state cardinality
- **P58 (Greedy Math):** Integer properties related to bit structure
