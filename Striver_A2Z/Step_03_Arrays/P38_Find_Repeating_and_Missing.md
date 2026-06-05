# 🔥 Find the Repeating and Missing Number

> **GFG Classic** · **Difficulty:** Hard · **Step 3 — Arrays · P38**

---

## 🧠 Problem Understanding

**What is it asking?**
Given an array of N integers where each number from 1 to N appears exactly once **except**: one number appears **twice** (repeating) and one number is **missing**. Find both.

**Input:** `arr = [3, 1, 3]` (N=3)
**Output:** `repeating = 3`, `missing = 2`

**Input:** `arr = [4, 3, 6, 2, 1, 1]` (N=6)
**Output:** `repeating = 1`, `missing = 5`

**Constraints:** Array has exactly N elements, one repeated, one missing, rest appear once.

**Key Observations:**
- Sum of 1..N = N(N+1)/2 → `sum(arr) - expected_sum = repeating - missing` ... (equation 1)
- Sum of squares: `sumSq(arr) - N(N+1)(2N+1)/6 = repeating² - missing²` ... (equation 2)
- From both equations, we can solve for the exact values

**Simple Example:**
```
arr = [3, 1, 3], N = 3
Expected: {1, 2, 3}
Sum: 3+1+3=7, expected 6 → diff1 = 7-6 = 1 → R-M = 1
SumSq: 9+1+9=19, expected 14 → diff2 = 19-14 = 5 → R²-M² = 5
R+M = diff2/diff1 = 5/1 = 5
R = (1+5)/2 = 3, M = 3-1 = 2 ✅
```

---

## 🥉 Brute Force Approach

### Idea
Use a frequency array. Scan for the element with count 2 (repeating) and count 0 (missing).

### Algorithm
1. Create `freq[1..N]` initialized to 0
2. For each `x` in array: `freq[x]++`
3. For `i` from 1 to N:
   - If `freq[i] == 2`: `repeating = i`
   - If `freq[i] == 0`: `missing = i`

### Complexity
- **Time:** O(N)
- **Space:** O(N) — frequency array

### C++ Code
```cpp
// BRUTE FORCE: frequency count
pair<int,int> findTwoElement(vector<int>& arr, int n) {
    vector<int> freq(n + 1, 0);
    for (int x : arr) freq[x]++;
    int rep = -1, miss = -1;
    for (int i = 1; i <= n; i++) {
        if (freq[i] == 2) rep = i;
        if (freq[i] == 0) miss = i;
    }
    return {rep, miss};
}
```

---

## 🥈 Better Approach — XOR

### Idea
XOR of all array elements with XOR of 1..N. The result is `R XOR M`. Then find a set bit to split numbers into two groups, find R and M from each group.

### Algorithm
1. `xorAll = 0`
2. XOR all array elements and all of 1..N: `xorAll = R XOR M`
3. Find rightmost set bit of `xorAll`
4. Partition arr and 1..N into two groups based on that bit
5. XOR each group → gives R and M
6. Verify which is repeating and which is missing by counting

### Complexity
- **Time:** O(N)
- **Space:** O(1)

---

## 🥇 Optimal Approach — Mathematics (Sum + Sum of Squares)

### Key Observation

> 💡 Let R = repeating, M = missing.
>
> **Equation 1:** `sum(arr) - N(N+1)/2 = R - M` ... call this `d1`
>
> **Equation 2:** `sumSq(arr) - N(N+1)(2N+1)/6 = R² - M²` ... call this `d2`
>
> Since `d2 = (R-M)(R+M) = d1 × (R+M)`:
> → `R + M = d2 / d1`
>
> Now solve:
> - `R = (d1 + (R+M)) / 2`
> - `M = R - d1`

This gives O(N) time, O(1) space, and no XOR complexity.

### Algorithm
1. Compute `sumArr` and `sumSqArr` in one pass
2. `d1 = sumArr - N*(N+1)/2`
3. `d2 = sumSqArr - (long long)N*(N+1)*(2*N+1)/6`
4. `sumRM = d2 / d1` (R + M)
5. `R = (d1 + sumRM) / 2`
6. `M = sumRM - R`

### Dry Run

**Input:** `arr = [4, 3, 6, 2, 1, 1]`, N=6

```
sumArr = 4+3+6+2+1+1 = 17
expectedSum = 6*7/2 = 21
d1 = 17 - 21 = -4 → R - M = -4 (M is larger!)

sumSqArr = 16+9+36+4+1+1 = 67
expectedSumSq = 6*7*13/6 = 91
d2 = 67 - 91 = -24 → R² - M² = -24

sumRM = d2/d1 = -24/(-4) = 6 → R + M = 6

R = (d1 + sumRM)/2 = (-4 + 6)/2 = 2/2 = 1
M = sumRM - R = 6 - 1 = 5
```

**Output:** Repeating = 1, Missing = 5 ✅

### Complexity
- **Time:** O(N) — single pass for sums
- **Space:** O(1)

### Why is this optimal?
We need to read every element at least once → Ω(N) lower bound. This achieves exactly O(N) with O(1) space.

---

## 🎤 Interview Explanation Script

> "The brute force uses a frequency array — O(N) time and space. We can improve to O(1) space."

> "The mathematical approach sets up two equations. Let R be the repeating number, M the missing. The difference between the actual sum and expected sum gives us `R - M`. The difference of squared sums gives `R² - M²`, which factors as `(R-M)(R+M)`. Dividing gives `R + M`. Then simple algebra gives R and M individually."

> "One critical detail: use `long long` throughout. For N up to 10⁵, the sum of squares can reach around 10¹⁵ which overflows `int`. The division `d2/d1` is guaranteed to be exact since both differences come from integer arithmetic."

> "The XOR approach is also O(N)/O(1) but requires more careful handling of the partition step. The math approach is cleaner to explain in an interview."

---

## 💻 Clean C++ Interview Code

```cpp
/*
 * FIND REPEATING AND MISSING NUMBER — Math (Sum + Sum of Squares)
 *
 * PROBLEM UNDERSTANDING:
 *   Array [1..N] with one element repeated (R) and one missing (M).
 *
 * EQUATIONS:
 *   d1 = sumArr - N(N+1)/2        = R - M
 *   d2 = sumSqArr - N(N+1)(2N+1)/6 = R² - M² = (R-M)(R+M)
 *   → R+M = d2/d1
 *   → R = (d1 + R+M)/2, M = (R+M) - R
 *
 * EDGE CASES:
 *   - d2/d1 division is always exact (integer math)
 *   - Use long long to prevent overflow
 *
 * COMPLEXITY: Time O(N) | Space O(1)
 */
class Solution {
public:
    pair<int, int> findTwoElement(vector<int>& arr, int n) {
        long long sumArr = 0, sumSqArr = 0;

        for (int x : arr) {
            sumArr += x;
            sumSqArr += (long long)x * x;
        }

        long long expectedSum   = (long long)n * (n + 1) / 2;
        long long expectedSumSq = (long long)n * (n + 1) * (2 * n + 1) / 6;

        long long d1 = sumArr - expectedSum;         // R - M
        long long d2 = sumSqArr - expectedSumSq;     // R² - M²

        long long sumRM = d2 / d1;                   // R + M (exact division)

        long long R = (d1 + sumRM) / 2;              // repeating
        long long M = sumRM - R;                     // missing

        return {(int)R, (int)M};
    }
};
```

---

## 🧾 Recall Line *(10-Second Revision)*

> "d1 = sumArr - N(N+1)/2 = R-M. d2 = sumSqArr - expected = R²-M². R+M = d2/d1. Solve for R and M."

---

## 📝 Short Revision Notes

- `d1 = R - M`, `d2 = R² - M² = d1 × (R+M)` → `R+M = d2/d1`
- `R = (d1 + (R+M)) / 2`, `M = (R+M) - R`
- Always `long long` for sums — overflow for N ≈ 10⁵
- Formula for sum of squares: `N*(N+1)*(2N+1)/6`
- Division `d2/d1` is exact (guaranteed by the math)
- XOR approach also valid: O(N)/O(1), but trickier to implement

---

## 🧠 Pattern Recognition Trigger

**When I see:**
- "Find repeating and missing in [1..N]"
- "One extra, one missing in array with range constraint"

**I should think of:** Math equations (sum + sum of squares) or XOR approach

---

## ⚠️ Common Mistakes

❌ Using `int` instead of `long long` — sum of squares overflows for large N  
❌ `N*(N+1)*(2*N+1)/6` — integer overflow if `N > ~1000` without casting first  
❌ Forgetting that d1 can be negative (M > R) — handled automatically by algebra  
❌ XOR approach: not verifying which of the two XOR groups is repeating vs missing  

---

## 🔥 What Interviewer Is Testing

- **Concept:** Setting up and solving a system of two equations
- **Reasoning:** Why sum-of-squares gives a second independent equation
- **Detail:** Long long overflow awareness

---

## 🚀 Alternative Approaches

| Approach | Time | Space | Notes |
|----------|------|-------|-------|
| Math (sum + sumSq) | O(N) | O(1) | Clean, recommended |
| XOR | O(N) | O(1) | No overflow risk, trickier |
| Frequency array | O(N) | O(N) | Simple but extra space |
| Index marking (negation) | O(N) | O(1) | Destructive (modifies input) |

**Index marking approach** (modifies input but O(1) space):
```cpp
// Mark visited: negate arr[|x|-1] for each x
// Positive → missing, visited twice → repeating
```

---

## 📚 Related Problems

- [ ] GFG — Find the Repeating and Missing Number
- [ ] LeetCode #287 — Find the Duplicate Number (only repeating)
- [ ] LeetCode #268 — Missing Number (only missing)
- [ ] Striver Step 3 P14 — Number appearing once (XOR pattern)

---

## 🏆 Pattern Category

`Arrays` · `Math` · `Number Theory`

---

## 🎯 Difficulty Analysis

**Rating:** Hard

**Why challenging:** Constructing the two-equation system is the key insight. The overflow trap with long long is a common interview trip-up. Recognizing that sum-of-squares provides a second independent equation is non-obvious.

---

## 📈 Progression Insight

**Harder variant:** Find K repeating numbers in [1..N] → Polynomial approach with Newton's identities

**Pattern application:** The "two equations from two unknowns" technique appears in: competitive programming counting problems, number theory modular equations

---

## ⏱️ 30-Second Last-Minute Revision

> **Problem:** Find repeating R and missing M in array of [1..N]  
> **Approach:** `d1 = sumArr - N(N+1)/2`. `d2 = sumSqArr - N(N+1)(2N+1)/6`. `R+M = d2/d1`. `R = (d1+R+M)/2`. `M = R+M - R`.  
> **Key trick:** Long long for all calculations; d2/d1 is always exact  
> **Time:** O(N) | **Space:** O(1)  
> **Watch out for:** Overflow — cast to `long long` before multiplying
