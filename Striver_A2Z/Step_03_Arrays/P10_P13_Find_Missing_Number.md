# 🔥 Find Missing Number in an Array

> **LeetCode #268** · **Difficulty:** Easy · **Step 3 — Arrays · P10 & P13**

---

## 🧠 Problem Understanding

Given an array of N-1 distinct integers in range `[1, N]`, find the missing number.

**Input:** `[1, 2, 4, 6, 3, 7, 8]`, N=8 → **Output:** `5`

**Key Observations:**
- Sum of 1 to N = N*(N+1)/2. Sum of array = total - missing.
- XOR approach: XOR all 1..N with all array elements → remaining is the missing.

---

## 🥉 Brute Force
Sort array, scan for gap. **Time:** O(N log N)

---

## 🥈 Better — Sum Formula

### Idea
`missing = (1+2+...+N) - sum(arr) = N*(N+1)/2 - sum(arr)`

### Complexity
- **Time:** O(N) · **Space:** O(1)
- **Overflow risk:** Use `long long` for large N

```cpp
int missingNumber(vector<int>& nums) {
    long long n = nums.size() + 1;           // or nums.size() if 0..N
    long long expected = n * (n + 1) / 2;
    long long actual = 0;
    for (int x : nums) actual += x;
    return (int)(expected - actual);
}
```

---

## 🥇 Optimal — XOR

### Key Observation
> 💡 XOR is self-inverse: `a ^ a = 0`, `a ^ 0 = a`. XOR all numbers 1..N with all array elements. Pairs cancel → missing number remains.

```
XOR 1..N = 1^2^3^4^...^N
XOR arr   = 1^2^...^(missing-1)^(missing+1)^...^N
Together  = missing (all others cancel)
```

### Dry Run
`arr=[1,2,4,5,3]`, N=5 (missing=??)

XOR all 1..5: `1^2^3^4^5 = 1`  
XOR arr: `1^2^4^5^3 = 5`  
Combined: `1^5 = 4` → missing = **4** ✅ (Wait, let me recheck: 1^2^3^4^5 XOR 1^2^3^5 = 4 ✅)

### Complexity
- **Time:** O(N) · **Space:** O(1)
- **No overflow** — safe for any N

```cpp
/*
 * FIND MISSING NUMBER — XOR approach
 * XOR of 1..N with all array elements → missing survives
 * Time O(N) | Space O(1) | No overflow
 */
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        int xorAll = 0;

        // XOR all numbers 1..n
        for (int i = 1; i <= n; i++) xorAll ^= i;

        // XOR all array elements
        for (int x : nums) xorAll ^= x;

        return xorAll;        // missing number remains
    }
};
```

---

## 🎤 Interview Explanation Script
> "Sum formula is simple: expected sum minus actual sum gives the missing number. But for large N, the sum can overflow even `long long`."

> "The XOR approach avoids overflow entirely. XOR has a key property: `a^a=0`. XOR all numbers 1 to N with all array elements — every number present cancels itself out, leaving only the missing number."

---

## 🧾 Recall Line
> "XOR all 1..N with all arr elements → missing survives. No overflow. O(N)/O(1)."

## 📝 Short Revision Notes
- Sum method: `N*(N+1)/2 - sum(arr)` — simple but watch overflow
- XOR method: no overflow, same O(N)/O(1) — preferred
- LC 268: array is `[0..N]` with one missing — adjust: XOR all 0..N
- Extension: find two missing numbers → use sum + sum-of-squares equations

## ⚠️ Common Mistakes
❌ Integer overflow in sum approach for large N — use `long long`  
❌ XOR: confusing range — should XOR 1..N not 0..N-1 (check problem statement)

## 🔥 What Interviewer Is Testing
- Multiple approaches (sum, XOR) and when each is preferred
- Overflow awareness

## 📚 Related Problems
- [ ] LeetCode #268 — Missing Number
- [ ] LeetCode #287 — Find the Duplicate Number
- [ ] Striver P14 — Number appearing once (XOR pattern)

## 🏆 Pattern Category
`Arrays` · `Math` · `XOR` · `Bit Manipulation`

## ⏱️ 30-Second Revision
> Sum: `N*(N+1)/2 - sum(arr)`. XOR: `xorAll = XOR(1..N) ^ XOR(arr)`. Both O(N)/O(1). XOR has no overflow.
