# 🔥 Find the Nth Root of a Number

> **Striver / GFG** · **Difficulty:** Easy-Medium · **Step 4 — Binary Search · P15**

---

## 🧠 Problem Understanding

Find an integer `x` such that `x^n = m`. Return `x` if a perfect integer root exists, otherwise `-1`.

**Input:** `n = 3`, `m = 27` → **Output:** `3` (3³ = 27)
**Input:** `n = 4`, `m = 69` → **Output:** `-1` (no integer 4th root)

**Key Observation:**
`mid^n` is monotonically increasing in `mid`, so we **binary search on the answer** in `[1, m]`, comparing `mid^n` against `m`. The power is computed with an early break to avoid overflow.

---

## 🎯 Interview Progression

### 🥉 Brute Force — Linear

Try `i = 1, 2, 3, ...`, compute `i^n`; return `i` if it equals `m`, stop once it exceeds `m`. **Time:** O(m · n) worst.

---

### 🥇 Optimal — Binary Search on the Answer

> 💡 Search `[1, m]`. For each `mid`, compute `mid^n` but **break early once it exceeds `m`** (both for correctness and to avoid overflow). Then: `==m` → found; `<m` → go right; `>m` → go left.

```cpp
class Solution {
public:
    int nthRoot(int n,int m){
        int low=1,high=m;
        while(low<=high){
            int mid=(low+high)/2;
            long long ans=1;
            for(int i=0;i<n;i++){
                ans*=mid;
                if(ans>m) break;
            }
            if(ans==m) return mid;
            if(ans<m) low=mid+1;
            else high=mid-1;
        }
        return -1;
    }
};
```

**Time:** O(n · log m) · **Space:** O(1).

### Dry Run
`n = 3`, `m = 27`, search `[1, 27]`

| low | high | mid | mid³ | vs 27 | Action |
|-----|------|-----|------|-------|--------|
| 1 | 27 | 14 | >27 (break) | > | high=13 |
| 1 | 13 | 7 | >27 (break) | > | high=6 |
| 1 | 6 | 3 | 27 | == | **return 3** ✅ |

---

## 🧾 Recall Line *(10-Second Revision)*

> "BS `[1, m]`. Compute `mid^n` with early break on overflow. `==m` return mid, `<m` go right, `>m` go left. Else -1."

---

## 📝 Short Revision Notes

- Another "binary search on answer" problem — search space is `[1, m]`.
- Compute the power in `long long` and **break as soon as it exceeds `m`** — prevents overflow and needless work.
- Three-way branch on `mid^n` vs `m`: equal / less / greater.
- Return `-1` when no exact integer root exists.

---

## ⚠️ Common Mistakes

❌ Computing `mid^n` without the early break → overflow for large `mid`/`n`.
❌ Using `int` for the running product.
❌ Missing the `== m` exact-match check (returning a floor instead of `-1`).

---

## 🧠 Pattern Recognition Trigger

**When I see:** "nth root", "integer x with x^n = m" → **binary search on answer with a guarded power**.

---

## 🏆 Pattern Category

`Binary Search` · `Search Space` · `Math`

---

## ⏱️ 30-Second Last-Minute Revision

> **BS `[1, m]`.** Compute `mid^n` (break on overflow), compare to `m`: equal→answer, less→right, greater→left. `-1` if none. `O(n·log m)`.
