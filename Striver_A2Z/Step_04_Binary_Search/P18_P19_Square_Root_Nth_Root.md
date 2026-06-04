# 🔥 Square Root & Nth Root Using Binary Search

> **LeetCode #69** · **Difficulty:** Easy · **Step 4 — P18 & P19**

---

## 🧠 The "Binary Search on Answer Space" Pattern

> 💡 **Key Template:** When asked "find the minimum/maximum value X satisfying a condition," binary search on the answer X directly — not on array indices.

```
lo = minimum possible answer
hi = maximum possible answer
While lo < hi:
    mid = (lo + hi) / 2  (or +1 for upper bound flavor)
    if feasible(mid): hi = mid   (find minimum feasible)
    else: lo = mid + 1
```

---

# P18 — Square Root (Floor)

**Find `⌊√N⌋` without using `sqrt()`.**

### Algorithm
Binary search on answer: find largest `x` such that `x² ≤ N`.

```cpp
/*
 * INTEGER SQUARE ROOT — binary search on answer
 * Find largest x where x*x <= N
 * Time O(log N) | Space O(1)
 */
class Solution {
public:
    int mySqrt(int n) {
        if (n < 2) return n;
        int lo = 1, hi = n / 2;       // answer can't exceed n/2 for n>=4
        int ans = 1;

        while (lo <= hi) {
            long long mid = lo + (hi - lo) / 2;
            if (mid * mid <= n) {
                ans = mid;             // valid: store and try higher
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        return ans;
    }
};
```

### Dry Run
N = 10, lo=1, hi=5

| lo | hi | mid | mid² | ≤10? | ans |
|----|-----|-----|------|------|-----|
| 1 | 5 | 3 | 9 | ✅ | 3, lo=4 |
| 4 | 5 | 4 | 16 | ❌ | —, hi=3 |
| lo>hi → return **3** ✅ |

---

# P19 — Nth Root of a Number

**Find Nth root of M using binary search on integers. Return -1 if not perfect integer root.**

```cpp
/*
 * NTH ROOT — binary search on answer
 * Find integer x such that x^n = m
 * Time O(log M * N) | Space O(1)
 */
class Solution {
private:
    // computes base^exp carefully to detect overflow
    // returns: 1 if base^exp==m, 2 if > m, 0 if < m
    int check(long long base, int exp, long long m) {
        long long result = 1;
        for (int i = 0; i < exp; i++) {
            result *= base;
            if (result > m) return 2;   // overflow — too large
        }
        return (result == m) ? 1 : 0;
    }

public:
    int NthRoot(int n, long long m) {
        int lo = 1, hi = m;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            int status = check(mid, n, m);
            if (status == 1) return mid;
            else if (status == 2) hi = mid - 1;   // too large
            else lo = mid + 1;                     // too small
        }
        return -1;   // no integer nth root
    }
};
```

---

## 🧾 Recall Lines
> **Sqrt:** Binary search `[1, N/2]`. Store `ans=mid` when `mid²≤N`, `lo=mid+1`. Return ans.  
> **Nth root:** Binary search `[1, M]`. `check(mid, n, m)` → 1 if exact, 2 if overflow, 0 if under.

## 📝 Short Revision Notes
- Always use `long long` for mid*mid to avoid overflow
- `hi = n/2` for sqrt (valid for n≥4; handle n<2 separately)
- Nth root: early termination in power to detect overflow
- These problems establish the "binary search on answer" pattern used in P20–P29

## ⚠️ Common Mistakes
❌ `int mid = ...; mid * mid` → overflow for large N  
❌ `hi = n` for sqrt — works but slower; `n/2` tightens search space  
❌ For Nth root: not detecting overflow in power calculation

## 🏆 Pattern Category
`Binary Search` · `Search Space` · `Math`

## ⏱️ 30-Second Revision
> Sqrt: BS [1, n/2]. `mid²≤n` → store ans, lo++. Else hi--. Return ans.  
> Nth root: BS [1, m]. check if `mid^n==m`. Overflow guard in power loop.
