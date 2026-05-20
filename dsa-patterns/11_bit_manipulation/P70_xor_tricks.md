# P70 — XOR Tricks

## 1. First-Timer Explanation

### What Is It?
**XOR (exclusive OR)** is a bitwise operation with magical properties for finding unique elements, swapping without temp variables, and detecting differences. Its key properties:
- `a ^ a = 0` (XOR with itself = 0)
- `a ^ 0 = a` (XOR with 0 = identity)
- Commutative: `a ^ b = b ^ a`
- Associative: `(a ^ b) ^ c = a ^ (b ^ c)`

### Core Applications
1. **Single number in pairs:** XOR all elements → duplicates cancel, unique survives
2. **Two different numbers:** XOR all, use a set bit to partition elements
3. **Missing number:** XOR [0..n] with all array elements
4. **Swap without temp:** `a^=b; b^=a; a^=b;`
5. **Find bit differences:** Set bits in `a^b` tell you where they differ

### Visual Walkthrough — Single Number
```
nums = [4, 1, 2, 1, 2]

XOR all: 4 ^ 1 ^ 2 ^ 1 ^ 2
      = 4 ^ (1^1) ^ (2^2)
      = 4 ^ 0 ^ 0
      = 4 ✓

The pairs cancel (x^x=0), the single survives.
```

### Visual Walkthrough — Two Singles
```
nums = [1, 2, 1, 3, 2, 5]
XOR all = 3^5 = 011 ^ 101 = 110

A set bit in 110 = bit 1 (rightmost set bit: 110 & -110 = 010)
Partition by bit 1:
  Group A (bit 1 set): 2,3,2 → XOR = 3
  Group B (bit 1 not set): 1,1,5 → XOR = 5
Answer: [3, 5] ✓
```

### When to Use
- "Find the only element appearing once" → XOR all
- "Find two unique elements among pairs" → XOR + partition
- "Find missing number in [0..n]" → XOR [0..n] with array
- "Check if two numbers differ by exactly one bit" → `(a^b)` is power of 2

### Common Mistakes
1. Two singles: forgetting that the partition bit must come from `xor1 ^ xor2` (not arbitrary)
2. Missing number: XOR [0..n] and the array (not [1..n])
3. Swap using XOR: fails if `a` and `b` are the same variable/memory location

---

## 2. Revision Card

**Recognition Signal:** "find single in pairs", "missing number", "two unique elements"

**Core Idea:** XOR cancels pairs. Remaining XOR = answer (for single) or XOR of two answers (for two singles). Use rightmost set bit to partition for two-singles case.

**Trigger Keywords:** single number, appears once, XOR, missing, swap

**Complexity:** O(n) time, O(1) space always

---

## 3. Interview Tell Signs

- "All elements appear twice except one" → XOR all
- "All appear three times except one" → bit counting (not XOR)
- "Missing number from 0 to n" → XOR [0..n] ^ array elements
- "Two elements appear once, rest twice" → XOR then partition

---

## 4. C++ Template

```cpp
// ── Single Number ─────────────────────────────────────────────────────────────
int singleNumber(vector<int>& nums) {
    int res = 0;
    for (int x : nums) res ^= x;
    return res;
}

// ── Two Single Numbers ────────────────────────────────────────────────────────
vector<int> singleNumberIII(vector<int>& nums) {
    int xorAll = 0;
    for (int x : nums) xorAll ^= x;
    
    int bit = xorAll & (-xorAll); // rightmost set bit
    int a = 0, b = 0;
    for (int x : nums) {
        if (x & bit) a ^= x;
        else b ^= x;
    }
    return {a, b};
}

// ── Missing Number (0..n) ─────────────────────────────────────────────────────
int missingNumber(vector<int>& nums) {
    int n = nums.size(), res = n;
    for (int i = 0; i < n; i++) res ^= i ^ nums[i];
    return res;
}
```

---

## 5. How to Present in Interview

**Verbal Script:**
> "XOR has two key properties: x^x=0 (pairs cancel) and x^0=x (identity). So XOR-ing all elements leaves only the unique one — all duplicates cancel. For two unique elements: XOR all gives a^b. A set bit in a^b means a and b differ at that bit. I use that bit to partition all elements into two groups; each group XORs to one of the unique elements."

**Checklist:**
- [ ] State a^a=0 and a^0=a explicitly
- [ ] Single number: one pass XOR
- [ ] Two singles: XOR all → find partition bit → two-group XOR
- [ ] Rightmost set bit: `x & (-x)` or `x & (~x+1)`
- [ ] State O(n) time, O(1) space

---

## 6. Problems

### Problem 1: Single Number (All others appear twice)
**Difficulty:** Easy | **LC:** 136

```cpp
int singleNumber(vector<int>& nums) {
    int res = 0;
    for (int x : nums) res ^= x;
    return res;
}
// Time: O(n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Single Number II (All others appear three times)
**Difficulty:** Medium | **LC:** 137

**Approach:** Count each bit modulo 3. Bit is in the answer if count%3 != 0.

```cpp
int singleNumber(vector<int>& nums) {
    int ones = 0, twos = 0;
    for (int x : nums) {
        ones = (ones ^ x) & ~twos;
        twos = (twos ^ x) & ~ones;
    }
    return ones;
}
// Time: O(n) | Space: O(1)
// State machine: ones, twos track bits seen 1 or 2 times (mod 3)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Single Number III (Two unique numbers)
**Difficulty:** Medium | **LC:** 260

```cpp
vector<int> singleNumber(vector<int>& nums) {
    int xorAll = 0;
    for (int x : nums) xorAll ^= x;
    int bit = xorAll & (-xorAll); // rightmost differing bit
    int a = 0, b = 0;
    for (int x : nums) {
        if (x & bit) a ^= x;
        else b ^= x;
    }
    return {a, b};
}
// Time: O(n) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Missing Number
**Difficulty:** Easy | **LC:** 268

```cpp
int missingNumber(vector<int>& nums) {
    int n = nums.size(), res = n;
    for (int i = 0; i < n; i++) res ^= i ^ nums[i];
    return res;
}
// Time: O(n) | Space: O(1)
// Alternatively: n*(n+1)/2 - sum(nums)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Find the Difference (Two Strings)
**Difficulty:** Easy | **LC:** 389

```cpp
char findTheDifference(string s, string t) {
    char res = 0;
    for (char c : s) res ^= c;
    for (char c : t) res ^= c;
    return res;
}
// Time: O(n) | Space: O(1)
// Characters in s cancel, extra char in t survives
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: XOR Queries of a Subarray
**Difficulty:** Medium | **LC:** 1310

**Approach:** Prefix XOR. `xor[l..r] = prefix[r+1] ^ prefix[l]`.

```cpp
vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
    int n = arr.size();
    vector<int> prefix(n+1, 0);
    for (int i = 0; i < n; i++) prefix[i+1] = prefix[i] ^ arr[i];
    vector<int> res;
    for (auto& q : queries) res.push_back(prefix[q[1]+1] ^ prefix[q[0]]);
    return res;
}
// Time: O(n + q) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** nums=[1,1,2,2,3,3,4,5,5]. XOR all. What's the result?
<details><summary>Reveal</summary>
Pairs: 1^1=0, 2^2=0, 3^3=0, 5^5=0. Remaining: 4. XOR all = 4. ✓
</details>

**Drill 2:** Single Number II: all appear 3 times except one. Why can't you just XOR?
<details><summary>Reveal</summary>
XOR cancels pairs (mod 2). If a number appears 3 times: 3 mod 2 = 1, so it wouldn't cancel — you'd get wrong answers. You need to count each bit mod 3. The state machine (ones, twos) tracks this without counting arrays.
</details>

**Drill 3:** Two singles: xorAll = 6 (110 in binary). What's the partition bit?
<details><summary>Reveal</summary>
Rightmost set bit of 6 = 6 & (-6) = 110 & 010 = 010 = 2. Partition: elements with bit 1 set (value & 2 != 0) in one group, rest in other. XOR each group gives one of the two unique elements.
</details>

**Drill 4:** Missing number in [0,1,2,4] (n=5, range 0..5). Apply the XOR method.
<details><summary>Reveal</summary>
Wait, n=4 here (4 elements). Range is [0..4]. res = 4. XOR with i and nums[i]: i=0: res ^= 0^0=0. i=1: res ^= 1^1=0. i=2: res ^= 2^2=0. i=3: res ^= 3^4 = 7. res = 4^7 = 3. Answer: 3. ✓
</details>

**Drill 5:** XOR subarray query: arr=[1,3,4,8], query=[0,2]. How?
<details><summary>Reveal</summary>
prefix=[0,1,1^3=2,2^4=6,6^8=14]. Query [0,2]: prefix[3] ^ prefix[0] = 6 ^ 0 = 6. Verify: 1^3^4 = 6 ✓.
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Space |
|---------|------|-------|
| Single Number | O(n) | O(1) |
| Single Number II (×3) | O(n) | O(1) |
| Single Number III (two) | O(n) | O(1) |
| Missing Number | O(n) | O(1) |
| XOR Subarray Query | O(n+q) | O(n) |

---

## 9. Common Follow-up Questions

**Q: Appears k times except one: general approach?**
A: Count each bit modulo k. If bit count % k != 0, that bit is in the unique element. O(32n) = O(n) time, O(1) space.

**Q: Two missing numbers from [1..n]?**
A: Same as "two single numbers" — XOR [1..n] with array elements gives XOR of the two missing numbers. Then partition.

**Q: Find the duplicate using XOR?**
A: If array contains [1..n] with one duplicate: XOR [1..n] with array gives `duplicate ^ original_missing`. Need extra info to separate them. Sum approach (arithmetic) is simpler for this case.

---

## 10. Cross-Pattern Connections

- **P71 (Bit Counting):** XOR tells you WHERE bits differ; counting tells you HOW MANY bits differ
- **P72 (Bit Tricks):** Masking, shifting, other bit ops complement XOR
- **P58 (Greedy Math):** Matrix toggle problems use XOR
- **P79 (Prefix Sums):** XOR subarray queries use prefix XOR (analogous to prefix sum)
