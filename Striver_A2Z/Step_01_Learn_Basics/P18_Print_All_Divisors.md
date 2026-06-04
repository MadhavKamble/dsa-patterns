# 🔥 Print All Divisors

> **GFG Classic** · **Difficulty:** Easy · **Step 1 — Basic Maths · P18**

---

## 🧠 Problem Understanding

**What is it asking?**  
Given a number N, print all divisors of N in sorted order.

A **divisor** of N is any integer d (1 ≤ d ≤ N) such that `N % d == 0`.

**Input:** Integer N (1 ≤ N ≤ 10⁹)  
**Output:** All divisors of N, sorted in ascending order

**Key Observations:**
- 1 and N are always divisors
- Divisors come in pairs: if d divides N, then N/d also divides N
- All divisors ≤ √N have a corresponding pair ≥ √N
- We only need to check up to √N

**Simple Example:**
```
N = 36
Divisors: 1, 2, 3, 4, 6, 9, 12, 18, 36
Pairs: (1,36), (2,18), (3,12), (4,9), (6,6) ← 6 is √36
```

---

## 🥉 Brute Force Approach

### Idea
Loop from 1 to N, check if each i divides N.

### Intuition
Every divisor is in range [1, N], so checking all of them guarantees we find them all.

### Algorithm
1. For i from 1 to N:
   - If `N % i == 0`, add i to result
2. Return result (already sorted since we iterate in order)

### Complexity
- **Time:** O(N)
- **Space:** O(number of divisors) — approximately O(N^(1/3)) on average

### C++ Code
```cpp
// BRUTE FORCE: Loop from 1 to N
vector<int> getDivisors(int n) {
    vector<int> divisors;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0)
            divisors.push_back(i);
    }
    return divisors;    // naturally sorted
}
```

---

## 🥈 Better Approach

### Why improve brute force?
O(N) is too slow for N up to 10⁹ (10⁹ operations → TLE). We need O(√N).

### Idea
For every divisor i ≤ √N, N/i is also a divisor. So loop only up to √N and collect both.

### Intuition
Divisors come in symmetric pairs around √N. If i × j = N (i ≤ j), then both i and j are divisors. We find both by checking up to √N.

```
N = 36, √36 = 6
i=1: divisors 1 and 36
i=2: divisors 2 and 18
i=3: divisors 3 and 12
i=4: divisors 4 and 9
i=6: divisors 6 and 6 (same — √36 exactly, add only once)
```

### Algorithm
1. For i from 1 to √N:
   - If `N % i == 0`:
     - Add `i`
     - If `i != N/i`, also add `N/i`
2. Sort the result
3. Return

### Complexity
- **Time:** O(√N) + O(d log d) for sorting (d = number of divisors)
- **Space:** O(d)

### C++ Code
```cpp
// BETTER: Loop up to sqrt(N), collect pairs
vector<int> getDivisors(int n) {
    vector<int> divisors;
    for (int i = 1; (long long)i * i <= n; i++) {
        if (n % i == 0) {
            divisors.push_back(i);
            if (i != n / i)             // avoid duplicate for perfect squares
                divisors.push_back(n / i);
        }
    }
    sort(divisors.begin(), divisors.end());
    return divisors;
}
```

---

## 🥇 Optimal Approach

### Key Observation

> 💡 We can avoid sorting altogether: collect small divisors in one pass (already sorted), collect large divisors in a separate vector (reverse sorted), then merge.

```
N = 36
Small (i ≤ √N): 1, 2, 3, 4, 6
Large (N/i):    36, 18, 12, 9  (collected in order of increasing i, so decreasing value)

Reverse large: 9, 12, 18, 36
Concatenate: 1, 2, 3, 4, 6, 9, 12, 18, 36 → sorted! ✅
```

### Algorithm
1. Loop i from 1 to √N:
   - If `N % i == 0`:
     - Push `i` to `small`
     - If `i != N/i`, push `N/i` to `large`
2. Reverse `large`
3. Return `small + large`

### Dry Run

**Input:** `N = 12`

`√12 ≈ 3.46`, so loop i = 1, 2, 3

| i | N%i==0? | small | large |
|---|---------|-------|-------|
| 1 | ✅ (12%1=0) | [1] | [12] |
| 2 | ✅ (12%2=0) | [1,2] | [12,6] |
| 3 | ✅ (12%3=0) | [1,2,3] | [12,6,4] |

Reverse large: [4, 6, 12]  
Result: [1, 2, 3, 4, 6, 12] ✅

### Complexity
- **Time:** O(√N) — no sort needed
- **Space:** O(d) — output storage

### Why is this optimal?
We can't do better than O(√N) to find all divisors because we must check all potential divisors up to √N. The merge trick eliminates the O(d log d) sort.

---

## 🎤 Interview Explanation Script

> "The brute force loops from 1 to N and checks each value — that's O(N), too slow for N up to 10⁹."

> "The key insight is that divisors come in pairs: if d divides N, so does N/d. And since d × (N/d) = N, one of them is always ≤ √N."

> "So we only need to loop up to √N, collecting both d and N/d at each step."

> "To get sorted output without an explicit sort, I collect small divisors in one list and large divisors (in reverse order) in another, then reverse the large list and concatenate."

> "This gives O(√N) time and O(1) extra space beyond the output."

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * PROBLEM UNDERSTANDING:
 *   Print all divisors of N in sorted order.
 *
 * EDGE CASES:
 *   - N = 1: only divisor is 1
 *   - Perfect square: √N is a divisor, add only once
 *   - Use (long long)i*i <= n to avoid overflow when i is large
 *
 * KEY OBSERVATION:
 *   Divisors come in pairs (d, N/d). Check only up to √N.
 *   Avoid sort: collect small divisors forward, large divisors reverse, then merge.
 *
 * COMPLEXITY: Time O(√N) | Space O(d) for output
 */

class Solution {
public:
    vector<int> printDivisors(int n) {
        vector<int> small, large;

        for (int i = 1; (long long)i * i <= n; i++) {
            if (n % i == 0) {
                small.push_back(i);           // small divisor
                if (i != n / i)
                    large.push_back(n / i);   // paired large divisor
            }
        }

        // large is currently in descending order — reverse it
        reverse(large.begin(), large.end());

        // merge: small (ascending) + reversed large (ascending)
        for (int x : large) small.push_back(x);

        return small;
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "Loop to √N, collect pairs (i, N/i). Reverse large half and append for sorted output."

---

## 📝 Short Revision Notes

- Divisors come in pairs: d and N/d — check only to √N
- Perfect square: when `i == N/i`, add only once
- Avoid overflow: use `(long long)i*i <= n` or `i <= sqrt(n)` (but sqrt is imprecise)
- Avoid sort: small divisors are already sorted; large divisors just need reversing
- Time O(√N), Space O(d) output only
- Number of divisors of N is typically O(N^(1/3)) on average

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "print all divisors"
- "count divisors"
- "factorize number"
- "is perfect number?" (sum of divisors = N)

**I should think of:** Loop to √N, collect pairs

---

## ⚠️ Common Mistakes

❌ Looping to N instead of √N → O(N) TLE for large inputs  
❌ Adding duplicate at perfect square: `i == N/i` → must add only once  
❌ Overflow: `i * i <= n` overflows when n is near INT_MAX; use `(long long)i*i`  
❌ Forgetting to sort when using the pair approach (or not using the merge trick)  

---

## 🔥 What Interviewer Is Testing

- **Concept:** Divisor pairs and √N optimization
- **Reasoning:** Avoiding redundant work, overflow awareness
- **Optimization:** O(N) → O(√N), and eliminating the sort

---

## 🚀 Alternative Approaches

| Approach | Time | Space | Notes |
|----------|------|-------|-------|
| Loop to √N + reverse merge | O(√N) | O(d) | Optimal — no sort |
| Loop to √N + sort | O(√N + d log d) | O(d) | Simpler, slightly slower |
| Brute force to N | O(N) | O(d) | Too slow for N ~ 10⁹ |

---

## 📚 Related Problems

- [ ] LeetCode #204 — Count Primes (Sieve — related to divisors)
- [ ] LeetCode #507 — Perfect Number (sum of divisors == N)
- [ ] LeetCode #1362 — Closest Divisors
- [ ] GFG — Sum of Divisors
- [ ] Striver Step 1 P19 — Check for Prime (also uses √N idea)

---

## 🏆 Pattern Category

`Math` · `Number Theory` · `Square Root Trick`

---

## 🎯 Difficulty Analysis

**Rating:** Easy-Medium

**Why:** The √N insight is non-obvious. Overflow with `i*i` and perfect square deduplication are common trip-ups.

---

## 📈 Progression Insight

**Harder variant:** Count divisors for all numbers in [1, N] → Sieve of Eratosthenes approach  
**Related:** Sum of divisors, product of divisors  
**Advanced:** Highly composite numbers, number of divisors formula using prime factorization: if N = p₁^a₁ × p₂^a₂ × ..., then d(N) = (a₁+1)(a₂+1)...

---

## ⏱️ 30-Second Last-Minute Revision

> **Problem:** Print all divisors of N in sorted order  
> **Approach:** Loop i from 1 to √N. If `N%i==0`, collect i (small) and N/i (large, if different). Reverse large and append to small.  
> **Key trick:** Pairs (d, N/d) → only check to √N; merge trick avoids sorting  
> **Time:** O(√N) | **Space:** O(d)  
> **Watch out for:** `(long long)i*i <= n` for overflow; add i==N/i only once
