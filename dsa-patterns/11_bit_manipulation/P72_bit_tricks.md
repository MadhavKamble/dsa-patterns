# P72 — Bit Masking and Advanced Tricks

## 1. First-Timer Explanation

### What Is It?
**Bit masking** uses bitwise operations to manipulate specific bits efficiently. Common operations:
- **Set bit k:** `n | (1 << k)`
- **Clear bit k:** `n & ~(1 << k)`
- **Toggle bit k:** `n ^ (1 << k)`
- **Check bit k:** `(n >> k) & 1`
- **Clear all bits from k to 0:** `n & ~((1 << (k+1)) - 1)`

**Advanced tricks:**
- **Two's complement:** `~n + 1 = -n` (useful in many formulas)
- **Divide by 2:** `n >> 1`
- **Multiply by 2:** `n << 1`
- **Check odd/even:** `n & 1`
- **Swap two bits at positions i,j:** complex masking

### Visual — Sum of All Subsets of Array using Bitmask
```
arr = [1, 2, 3], n=3
Subsets encoded as bits: 000, 001, 010, 011, 100, 101, 110, 111
For mask=101 (binary) → pick arr[0]=1, arr[2]=3 → sum=4

Total sum of all subset sums: each element appears in 2^(n-1) subsets
ans = (arr[0]+arr[1]+arr[2]) * 2^(n-1) = 6 * 4 = 24
```

### When to Use
- "Enumerate all subsets" → bitmask from 0 to 2^n-1
- "Set/clear/toggle specific bits" → bit manipulation
- "Check if subset is valid" → bitmask DP (P36)
- "Pack multiple flags into one integer" → bitmask

### Common Mistakes
1. Forgetting parentheses: `1 << k & n` is wrong; `(1 << k) & n` is right
2. Signed vs unsigned: right shift of negative number is implementation-defined in C++; use `unsigned` or `>>>`
3. Overflow: `1 << 31` overflows int; use `1LL << 31`

---

## 2. Revision Card

**Recognition Signal:** "subset enumeration", "bit manipulation", "flags in integer", "check specific bit"

**Core Idea:** Each bit position = one boolean flag. Combine with OR, check with AND, toggle with XOR, clear with AND NOT.

**Trigger Keywords:** bitmask, subset, flags, encode state, bit set/clear/toggle

**Complexity:** O(1) for single operations; O(2^n) for full subset enumeration

---

## 3. Interview Tell Signs

- "Enumerate all subsets of n elements" → for mask 0..2^n-1
- "State with n boolean flags" → bitmask integer
- "n ≤ 20, find optimal subset" → bitmask DP
- "Compact encoding of multiple properties" → bitmask

---

## 4. C++ Template

```cpp
// ── Bit Operations Reference ──────────────────────────────────────────────────
int n, k;
// Set bit k:      n |= (1 << k)
// Clear bit k:    n &= ~(1 << k)
// Toggle bit k:   n ^= (1 << k)
// Check bit k:    bool set = (n >> k) & 1
// Get LSB:        n & (-n)  or  n & (~n + 1)
// Remove LSB:     n & (n - 1)
// Check power 2:  n && !(n & (n-1))

// ── Enumerate All Subsets of [0..n-1] ────────────────────────────────────────
void enumerateSubsets(int n) {
    for (int mask = 0; mask < (1 << n); mask++) {
        vector<int> subset;
        for (int i = 0; i < n; i++)
            if (mask & (1 << i)) subset.push_back(i);
        // process subset
    }
}

// ── Enumerate All Subsets of a Specific Mask ──────────────────────────────────
void submasksOf(int mask) {
    for (int sub = mask; sub > 0; sub = (sub - 1) & mask)
        ; // process sub
    // Also process sub=0 if needed
}
// Total work: O(3^n) — each element is in/out/not-in-parent-mask
```

---

## 5. How to Present in Interview

**Verbal Script:**
> "I'll use a bitmask where bit i represents whether element i is included. Iterating mask from 0 to 2^n-1 enumerates all 2^n subsets. For each mask, `(mask >> i) & 1` checks if element i is in the subset. This is O(n × 2^n) total, feasible for n ≤ 20."

**Checklist:**
- [ ] State n ≤ 20 constraint for bitmask enumeration
- [ ] Use `1 << i` not `2^i` in code
- [ ] Handle `1LL << i` for i ≥ 31
- [ ] Enumerate subsets of a mask: `sub = (sub-1) & mask`
- [ ] Total submask enumeration: O(3^n) amortized

---

## 6. Problems

### Problem 1: Sum of All Subset XOR Totals
**Difficulty:** Easy | **LC:** 1863

```cpp
int subsetXORSum(vector<int>& nums) {
    int n = nums.size(), total = 0;
    for (int mask = 1; mask < (1<<n); mask++) {
        int xorVal = 0;
        for (int i = 0; i < n; i++)
            if (mask & (1<<i)) xorVal ^= nums[i];
        total += xorVal;
    }
    return total;
    // O(n * 2^n), or O(n): each bit contributes sum * 2^(n-1)
}
// Time: O(n * 2^n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Maximum XOR of Two Numbers in an Array
**Difficulty:** Medium | **LC:** 421

**Approach:** Build Trie of bit representations. For each number, greedily choose the opposite bit to maximize XOR.

```cpp
int findMaximumXOR(vector<int>& nums) {
    int maxXOR = 0, mask = 0;
    for (int i = 30; i >= 0; i--) {
        mask |= (1 << i);
        unordered_set<int> prefixes;
        for (int n : nums) prefixes.insert(n & mask);
        
        int candidate = maxXOR | (1 << i);
        for (int p : prefixes)
            if (prefixes.count(candidate ^ p)) { maxXOR = candidate; break; }
    }
    return maxXOR;
}
// Time: O(32n) = O(n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Bitwise AND of Numbers Range
**Difficulty:** Medium | **LC:** 201

**Approach:** The common prefix of all numbers in [m,n] in binary. Right-shift both until equal.

```cpp
int rangeBitwiseAnd(int m, int n) {
    int shift = 0;
    while (m != n) { m >>= 1; n >>= 1; shift++; }
    return m << shift;
}
// Time: O(log n) | Space: O(1)
// Key: AND of range = common prefix (differing bits always AND to 0 somewhere in range)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Largest Combination with Bitwise AND Greater Than Zero
**Difficulty:** Medium | **LC:** 2275

**Approach:** For each bit position, count how many candidates have that bit set. Max count = answer.

```cpp
int largestCombination(vector<int>& candidates) {
    int maxCount = 0;
    for (int bit = 0; bit < 24; bit++) {
        int count = 0;
        for (int c : candidates) if ((c >> bit) & 1) count++;
        maxCount = max(maxCount, count);
    }
    return maxCount;
}
// Time: O(24n) = O(n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Number Complement
**Difficulty:** Easy | **LC:** 476

```cpp
int findComplement(int num) {
    int bits = 0, temp = num;
    while (temp) { bits++; temp >>= 1; }
    int mask = (1 << bits) - 1; // all 1s up to highest set bit
    return num ^ mask;
}
// Time: O(log n) | Space: O(1)
// XOR with all-1s mask flips all relevant bits
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: Divide Two Integers (Bit Manipulation)
**Difficulty:** Medium | **LC:** 29

**Approach:** Use bit shifting to find how many times divisor fits into dividend.

```cpp
int divide(int dividend, int divisor) {
    if (dividend == INT_MIN && divisor == -1) return INT_MAX;
    long a = abs((long)dividend), b = abs((long)divisor);
    int sign = (dividend < 0) ^ (divisor < 0) ? -1 : 1;
    long result = 0;
    while (a >= b) {
        long temp = b, multiple = 1;
        while (a >= (temp << 1)) { temp <<= 1; multiple <<= 1; }
        a -= temp;
        result += multiple;
    }
    return sign * result;
}
// Time: O(log^2 n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** Set bit 3 of n=5 (101). What's the result?
<details><summary>Reveal</summary>
n | (1<<3) = 00000101 | 00001000 = 00001101 = 13.
</details>

**Drill 2:** Clear bit 2 of n=7 (111). What's the result?
<details><summary>Reveal</summary>
n & ~(1<<2) = 00000111 & ~00000100 = 00000111 & 11111011 = 00000011 = 3.
</details>

**Drill 3:** Bitwise AND of range [5,7] = [101, 110, 111]. What's the result?
<details><summary>Reveal</summary>
5=101, 6=110, 7=111. 5&6&7=101&110=100, 100&111=100=4. Common prefix is "1" (top bit), then "00" → 100=4. Using right-shift: m=5,n=7, shift=0. m≠n: m=2,n=3,shift=1. m≠n: m=1,n=1,shift=2. m==n=1. Return 1<<2=4 ✓.
</details>

**Drill 4:** How many subsets of {1,2,3,4} (n=4) are there? How many submasks of 1010?
<details><summary>Reveal</summary>
Total subsets: 2^4=16. Submasks of 1010: subsets of {bit1, bit3} = {00,01,10,11} relative to those positions = 4 submasks: 0000, 0010, 1000, 1010.
</details>

**Drill 5:** Complement of 5 (101) should be 010=2. Apply the formula.
<details><summary>Reveal</summary>
bits = 3 (5 has 3 binary digits). mask = (1<<3)-1 = 7 = 111. 5 ^ 7 = 101 ^ 111 = 010 = 2 ✓.
</details>

---

## 8. Complexity Cheatsheet

| Operation | Time | Notes |
|-----------|------|-------|
| Single bit op (set/clear/toggle/check) | O(1) | Constant |
| Enumerate all subsets | O(n × 2^n) | n ≤ 20 |
| Enumerate submasks of mask | O(3^n) total | Per element: in/out/excluded |
| Maximum XOR (linear) | O(32n) | Trie approach |
| Bitwise AND of range | O(log n) | Common prefix |

---

## 9. Common Follow-up Questions

**Q: Why is submask enumeration O(3^n)?**
A: For each of the n bit positions, it appears in one of 3 states: (1) set in mask and set in submask, (2) set in mask and not in submask, (3) not set in mask. 3^n total combinations.

**Q: What are the limits for bitmask DP?**
A: n ≤ 20 for 2^n states (2^20 ≈ 10^6). n ≤ 24 if just iterating. Beyond that, need different approaches.

**Q: Tricks for fast subset sum?**
A: SOS (Sum over Subsets) DP computes sum for ALL subsets in O(n × 2^n) with O(2^n) space.

---

## 10. Cross-Pattern Connections

- **P70 (XOR):** XOR is a special case of bit manipulation
- **P71 (Bit Counting):** Counting operations built on these primitives
- **P36 (Bitmask DP):** Uses bitmask to encode states in DP
- **P46 (Subsets):** Bitmask is the iterative/implicit subset enumeration
