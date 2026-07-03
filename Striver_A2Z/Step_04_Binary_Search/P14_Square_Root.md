# 🔥 Find the Square Root of a Number (Floor)

> **LeetCode #69** · **Difficulty:** Easy · **Step 4 — Binary Search · P14**

---

## 🧠 The "Binary Search on Answer" Pattern

> 💡 When asked for the min/max value `x` satisfying a monotonic condition, **binary search on the answer value** — not on array indices. Here the answer is `⌊√x⌋`, and the condition `mid*mid <= x` is monotonic (true for small `mid`, false past the root).

---

## 🧠 Problem Understanding

Return `⌊√x⌋` (floor of the square root) without using `sqrt()`.

**Input:** `x = 8` → **Output:** `2` (since 2²=4 ≤ 8 < 9=3²)
**Input:** `x = 16` → **Output:** `4`

---

## 🎯 Interview Progression

### 🥉 Brute Force — Linear

Loop `i` from 1 upward while `i*i <= x`; answer is the last such `i`. **Time:** O(√x).

---

### 🥇 Optimal — Binary Search on the Answer

> 💡 Search `[1, x/2]` for the largest `mid` with `mid*mid <= x`. On a valid `mid`, record it and go right; otherwise go left.

```cpp
class Solution {
public:
    int mySqrt(int x){
        if(x<2) return x;
        int left=1,right=x/2,ans=0;
        while(left<=right){
            long long mid=left+(right-left)/2;
            if(mid*mid<=x){
                ans=mid;
                left=mid+1;
            }else{
                right=mid-1;
            }
        }
        return ans;
    }
};
```

**Time:** O(log x) · **Space:** O(1).

### Dry Run
`x = 8`, search `[1, 4]`

| left | right | mid | mid² | ≤8? | ans | Action |
|------|-------|-----|------|-----|-----|--------|
| 1 | 4 | 2 | 4 | ✅ | 2 | left=3 |
| 3 | 4 | 3 | 9 | ❌ | 2 | right=2 |
| 3 | 2 | — | — | — | 2 | left>right → **return 2** ✅ |

---

## 🧾 Recall Line *(10-Second Revision)*

> "Largest `mid` with `mid*mid <= x`. Valid → `ans=mid, left=mid+1`. Else `right=mid-1`. Use `long long` for `mid*mid`."

---

## 📝 Short Revision Notes

- Classic "binary search on answer" — the answer is a value, not an index.
- Use `long long mid` so `mid*mid` doesn't overflow `int`.
- `x < 2` returns `x` directly (0→0, 1→1); search space `[1, x/2]` for `x ≥ 2`.
- On a valid `mid`, store it and push right to maximize the floor.

---

## ⚠️ Common Mistakes

❌ Computing `mid*mid` in `int` → overflow for large `x`.
❌ Returning `left`/`right` instead of the stored `ans`.
❌ Forgetting the `x < 2` base case.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "floor of square root", "largest value with value² ≤ x" → **binary search on the answer**.

---

## 🏆 Pattern Category

`Binary Search` · `Search Space` · `Math`

---

## ⏱️ 30-Second Last-Minute Revision

> **BS on answer `[1, x/2]`.** `mid*mid<=x` → store `ans`, go right; else go left. `long long` for the product. `O(log x)`.
