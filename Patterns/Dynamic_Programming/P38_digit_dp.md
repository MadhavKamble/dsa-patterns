# Pattern 38: Digit DP

## Category
Dynamic Programming

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 233. Number of Digit One | Hard | https://leetcode.com/problems/number-of-digit-one/ |
| 2 | 357. Count Numbers with Unique Digits | Medium | https://leetcode.com/problems/count-numbers-with-unique-digits/ |
| 3 | 600. Non-negative Integers without Consecutive Ones | Hard | https://leetcode.com/problems/non-negative-integers-without-consecutive-ones/ |
| 4 | 902. Numbers At Most N Given Digit Set | Hard | https://leetcode.com/problems/numbers-at-most-n-given-digit-set/ |
| 5 | 1012. Numbers With Repeated Digits | Hard | https://leetcode.com/problems/numbers-with-repeated-digits/ |

---

## 1. First-Timer Explanation

### What is this pattern?
**Digit DP** counts numbers in a range [1, N] satisfying some property by constructing the number **digit by digit** while tracking whether we're still "tight" with the upper bound.

**The key insight**: instead of checking each number individually (O(N) — too slow for large N), build numbers digit by digit and use memoization.

**State variables:**
- `pos` — current digit position (0 = leftmost)
- `tight` — are we still constrained by the upper bound? (if true, current digit can't exceed N's digit at this position)
- Problem-specific state (sum of digits so far, count of specific digit, last digit used, etc.)

**Template pattern:**
```
count(pos, tight, extra_state):
  if pos == len: return isValid(extra_state)
  limit = (tight ? N[pos] : 9)
  for d = 0 to limit:
    newTight = tight && (d == limit)
    count += count(pos+1, newTight, update(extra_state, d))
```

**Leading zero handling**: often need a `started` flag — if not started, a '0' digit doesn't count.

### Visual Walkthrough
```
Count numbers in [1, 25] with digit sum ≤ 5:

N = 25 → digits = [2, 5]

count(pos=0, tight=true, sum=0):
  digit=0: tight=false → count(1, false, 0) → all 1-9 with sum≤5 → {1,2,3,4,5}
  digit=1: tight=false → count(1, false, 1) → {10,11,12,13,14} (sum+d≤5)
  digit=2: tight=true  → count(1, true, 2)
    digit=0: tight=false → ... →{20} (sum 2+0=2)
    digit=1: tight=false → ... →{21} (sum 3)
    digit=2: tight=false → ... →{22} (sum 4)
    digit=3: tight=false → ... →{23} (sum 5)
    digit=4: tight=false → ... →{24} (sum 6 > 5 ✗)
    digit=5: tight=true  → ... →{25} (sum 7 > 5 ✗)
```

### When TO use this pattern
- "Count numbers in [0, N] satisfying property on their digits"
- Property: digit sum, specific digit count, no consecutive same digit, unique digits
- Property that depends on digit composition, not arithmetic value
- Range [L, R] → solve as f(R) - f(L-1)

### When NOT to use this pattern
- Property depends on arithmetic (divisibility by specific number → different state)
- N is small enough to iterate directly
- No digit-based constraints

### Common Beginner Mistakes
- **Tight constraint**: when tight=false, you can use any digit 0-9; memoize `count(pos, tight, state)`
- **Leading zeros**: if the first digit is 0, it's a shorter number — handle with `started` flag or adjust
- **Return type**: sometimes count of valid numbers, sometimes sum of digits across all numbers
- **Memoization**: only memoize when tight=false (tight=true states aren't reused much)

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | "count numbers in [1,N] with digit property", "how many X-digit numbers satisfy..." |
| Core Idea | Build digit by digit; track whether still bounded by N (tight flag); memoize |
| Trigger Keywords | "numbers with unique digits", "count digit ones", "no consecutive ones" |
| Avoid When | N small enough for direct iteration, non-digit property |
| Time Complexity | O(log N × states) |
| Space Complexity | O(log N × states) for memoization table |

**Gotchas:**
- Memoize `(pos, tight=false, extra_state)` — tight=true states branch only once so no real reuse
- Leading zeros: a number like "007" is really "7" — need `started` flag to handle properly
- Range query: f(R) - f(L-1) where f(x) = count in [0, x]

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"numbers with digit sum ≤ k"` → digit DP
- `"count digit 1 in all numbers from 1 to N"` → digit DP or combinatorics
- `"numbers without consecutive ones in binary"` → digit DP on binary representation
- `"unique digits"` → digit DP tracking used digits (bitmask)
- `"at most N given digit set"` → digit DP

---

## 4. C++ Template

```cpp
/*
 * Pattern: Digit DP
 * Time: O(log(N) * states) | Space: O(log(N) * states)
 */

// COUNT NUMBERS WITH UNIQUE DIGITS up to n digits
int countNumbersWithUniqueDigits(int n) {
    if (n == 0) return 1;
    // dp approach: for each length, count permutations of unique digits
    int count = 10;  // all 1-digit numbers
    int uniqueDigits = 9, availableDigits = 9;
    for (int i = 2; i <= n && availableDigits > 0; i++) {
        uniqueDigits *= availableDigits--;
        count += uniqueDigits;
    }
    return count;
}

// GENERAL DIGIT DP TEMPLATE (count numbers in [1, N] with property)
string N_str;
int memo[12][2][/* extra state dims */1];  // adjust size

int digitDP(int pos, bool tight, int extraState) {
    if (pos == (int)N_str.size()) {
        return /* isValid(extraState) ? 1 : 0 */1;
    }
    if (memo[pos][tight][extraState] != -1) return memo[pos][tight][extraState];
    int limit = tight ? (N_str[pos]-'0') : 9;
    int res = 0;
    for (int d = 0; d <= limit; d++) {
        bool newTight = tight && (d == limit);
        int newExtra = /* update(extraState, d) */extraState;
        res += digitDP(pos+1, newTight, newExtra);
    }
    return memo[pos][tight][extraState] = res;
}

// USAGE:
int countInRange(int N) {
    N_str = to_string(N);
    memset(memo, -1, sizeof(memo));
    return digitDP(0, true, /* initial state */0);
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"I'll use digit DP. I build the number position by position, tracking a 'tight' flag: if tight is true, the current digit can't exceed the corresponding digit of N. Once I place a digit smaller than N's digit at that position, tight becomes false for all subsequent positions — meaning I can use any digit from 0 to 9. This structure naturally handles the upper bound constraint. I memoize on (position, tight, extra_state) to avoid recomputing the same sub-problems."

### Interview Flow Checklist
- [ ] Convert N to string (for easy digit access)
- [ ] Define what extra state is needed (digit sum, last digit, used digits bitmask, etc.)
- [ ] Write recursive function with (pos, tight, extra_state)
- [ ] Base case: pos == length → check if valid, return 1 or 0
- [ ] Loop digits 0 to limit (limit = N[pos] if tight, else 9)
- [ ] Recurse with (pos+1, tight && d == limit, updated_extra)
- [ ] Memoize; return answer

---

## 6. Problems

---

### Problem 1: 357. Count Numbers with Unique Digits
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/count-numbers-with-unique-digits/
**Why this pattern fits:** Count numbers 0 to 10^n with no repeated digits

**Optimal C++ Solution (combinatorics):**
```cpp
int countNumbersWithUniqueDigits(int n) {
    if (n == 0) return 1;
    int count = 10;
    int avail = 9, unique = 9;
    for (int len = 2; len <= n && avail > 0; len++) {
        unique *= avail--;
        count += unique;
    }
    return count;
}
```
**Edge Cases:** [ ] n=0 (only number is 0), [ ] n=10+ (no new unique 11-digit numbers)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 233. Number of Digit One
**Difficulty:** Hard
**Leetcode:** https://leetcode.com/problems/number-of-digit-one/
**Why this pattern fits:** Count total 1s in all numbers from 1 to n

**Optimal C++ Solution (combinatorics):**
```cpp
int countDigitOne(int n) {
    long long count = 0;
    for (long long factor = 1; factor <= n; factor *= 10) {
        long long divider = factor * 10;
        count += (n / divider) * factor;
        count += min((long long)factor, max(0LL, n % divider - factor + 1));
    }
    return (int)count;
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 3: 600. Non-negative Integers without Consecutive Ones
**Difficulty:** Hard
**Leetcode:** https://leetcode.com/problems/non-negative-integers-without-consecutive-ones/
**Why this pattern fits:** Binary digit DP — track last bit to prevent consecutive 1s

**Optimal C++ Solution:**
```cpp
int findIntegers(int n) {
    string s = bitset<32>(n).to_string();
    s = s.substr(s.find('1'));  // strip leading zeros
    int m = s.size();
    // dp[i][j] = numbers of length i ending with bit j with no consecutive 1s
    // Use Fibonacci-like approach
    vector<int> dp(m+1, 0);
    dp[1] = 1;  // 1-bit: "0" or "1" → 2 but we count differently
    // Alternative: direct digit DP
    int prev = 0, count = 0;
    for (int i = 0; i < m; i++) {
        // Fibonacci for "how many m-i digit strings with no consecutive 1s"
        // fib[k] = numbers of k-bit strings starting from 0 with no consecutive 1s
        int bits = m - i;
        int a = 1, b = 2;
        for (int j = 2; j < bits; j++) { int c = a+b; a=b; b=c; }
        if (s[i] == '1') {
            count += (bits == 1) ? 1 : a;
            if (prev == 1) break;  // consecutive 1s in n itself
            prev = 1;
        } else prev = 0;
        if (i == m-1) count++;  // n itself is valid
    }
    return count;
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 4: 902. Numbers At Most N Given Digit Set
**Difficulty:** Hard
**Leetcode:** https://leetcode.com/problems/numbers-at-most-n-given-digit-set/
**Why this pattern fits:** Count numbers ≤ N using only digits from the given set

**Optimal C++ Solution:**
```cpp
int atMostNGivenDigitSet(vector<string>& digits, int n) {
    string s = to_string(n);
    int m = s.size(), d = digits.size(), count = 0;
    // count numbers with fewer digits
    for (int len = 1; len < m; len++) {
        count += pow(d, len);  // d choices per position, no tight constraint
    }
    // count numbers with exactly m digits
    for (int i = 0; i < m; i++) {
        // count digits in set that are less than s[i]
        int smaller = 0;
        for (string& dg : digits) if (dg[0] < s[i]) smaller++;
        count += smaller * (int)pow(d, m-i-1);
        // check if s[i] itself is in the set
        bool found = false;
        for (string& dg : digits) if (dg[0] == s[i]) found = true;
        if (!found) break;  // can't match n's prefix further
        if (i == m-1) count++;  // n itself is valid
    }
    return count;
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 5: 1012. Numbers With Repeated Digits
**Difficulty:** Hard
**Leetcode:** https://leetcode.com/problems/numbers-with-repeated-digits/
**Why this pattern fits:** Count numbers in [1,N] with at least one repeated digit = N - count_unique_digit_numbers

**Optimal C++ Solution:**
```cpp
int numDupDigitsAtMostN(int n) {
    // Count = N - (count of numbers ≤ N with all unique digits)
    string s = to_string(n+1);  // +1 to make range [0, n]
    int m = s.size(), ans = 0;

    // Count unique-digit numbers with fewer digits than m
    for (int len = 1; len < m; len++) {
        int ways = 9;  // first digit: 1-9
        for (int i = 1; i < len; i++) ways *= (10 - i);
        ans += ways;
    }

    // Count unique-digit numbers with exactly m digits, ≤ n+1
    set<int> seen;
    for (int i = 0; i < m; i++) {
        int d = s[i] - '0';
        int start = (i == 0) ? 1 : 0;  // first digit can't be 0
        // count available digits less than d not yet seen
        for (int j = start; j < d; j++)
            if (!seen.count(j)) {
                int ways = 1;
                for (int k = i+1; k < m; k++) ways *= (10 - (int)seen.size() - 1 - (k - i - 1));
                ans += ways;
            }
        if (seen.count(d)) break;  // s[0..i] has repeated digit → stop
        seen.insert(d);
        if (i == m-1) ans++;  // n+1 itself has unique digits
    }
    return n - ans;
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> Count numbers from 1 to N whose digits sum to a prime number.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Digit DP with digit sum as extra state
**Reason:** State = (pos, tight, digit_sum_so_far). At base case, check if digit_sum is prime. Precompute primes up to 9*max_digits (≈ 9*10=90) with sieve. Memoize on (pos, tight, digit_sum). O(log N × max_sum) time.
</details>

---

**Drill 2:**
> Count numbers in [L, R] that are divisible by 7 and have no digit 0.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Digit DP with remainder as extra state
**Reason:** State = (pos, tight, remainder_mod_7). Disallow digit 0 (skip d=0 in loop). At base case, valid if remainder == 0. f(R) - f(L-1) for range. O(log N × 7) time.
</details>

---

**Drill 3:**
> Count palindromic numbers in [1, N].

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Digit DP with half-built palindrome tracking
**Reason:** For a number of length L, the first ceil(L/2) digits determine the palindrome. Generate all possible first halves, mirror them, check if ≤ N. Or: digit DP tracking the first half and whether we've become smaller than N's first half. O(sqrt(N)) numbers to check (at most O(10^(L/2)) palindromes of each length).
</details>

---

**Drill 4:**
> Count numbers in [1, N] where each digit is strictly greater than the previous one (monotone increasing digits).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Digit DP with last digit as extra state
**Reason:** State = (pos, tight, last_digit). At each step, current digit must be > last_digit. Loop d from (last_digit+1) to limit. O(log N × 10) time. This is actually also solvable with combinatorics (choosing k digits from {0..9} in order), but digit DP is more general.
</details>

---

**Drill 5:**
> Find the total sum of all numbers from 1 to N.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Mathematics (not digit DP)
**Reason:** Sum of 1 to N = N*(N+1)/2. Digit DP is overkill here. However, "find the sum of a specific digit across all numbers from 1 to N" IS a digit DP problem (e.g., sum of all digit-1s in LC 233 variant).
</details>

---

## 8. Complexity Cheatsheet

| Variant | Time | Space | States |
|---------|------|-------|--------|
| Count unique digit numbers | O(n) | O(1) | combinatorics, no DP |
| General digit DP | O(log(N) × S) | O(log(N) × S) | S = extra state size |
| Digit sum ≤ k | O(log(N) × 9×log(N)) | O(log(N) × 9×log(N)) | sum up to 9×digits |
| Divisibility by k | O(log(N) × k) | O(log(N) × k) | remainder mod k |
| Unique digits (bitmask) | O(log(N) × 2^10) | O(log(N) × 2^10) | bitmask of used digits |

---

## 9. Common Follow-up Questions

1. What if we need count in range [L, R]? (f(R) - f(L-1). Write f(N) = count in [0, N], then answer = f(R) - f(L-1))
2. How to handle leading zeros? (Use a `started` flag: if not yet started, a '0' digit is skipped, not counted as a leading zero. Or use separate counting for numbers with fewer digits)
3. When is digit DP overkill? (When the property is trivial to compute mathematically (sum 1 to N), or when N is small enough to iterate, or when there's a closed-form formula)
4. Can digit DP find the actual number satisfying a property? (Yes — set a target count and use the DP to identify which digit to place at each position, greedily building the number)

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| Combinatorics | Some digit DP has closed-form | 357. Unique Digits |
| Bitmask | Track which digits have been used | 1012. Repeated Digits |
| Fibonacci-style DP | Binary constraints (no consecutive 1s) | 600. Consecutive Ones |
| Sieve of Eratosthenes | Precompute primes for digit sum check | Prime digit sum variant |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
