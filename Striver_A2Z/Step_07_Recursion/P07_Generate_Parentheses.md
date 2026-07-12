# Generate Parentheses

> **LeetCode #22** · **Difficulty:** Medium · **Step 7 — Recursion · P07**

---

## 🧠 Problem Understanding

**What is it asking?**
Given `n`, generate all combinations of `n` pairs of well-formed (valid) parentheses.

**Input:** `n = 3` → **Output:** `["((()))","(()())","(())()","()(())","()()()"]`

**Key Observations:**
- A valid string has exactly `n` `'('` and `n` `')'`.
- At any point, `open` = count of `'('` added so far, `close` = count of `')'` added.
- Can add `'('` as long as `open < n`.
- Can add `')'` as long as `close < open` (can't close more than you've opened).
- These two guards automatically ensure validity — no post-filtering needed.

---

## 🥉 Brute Force

Generate all 2^(2n) strings of `(` and `)`, filter valid ones. O(2^(2n) × n). Very slow.

---

## 🥇 Recursive Backtracking

### Key Insight

> 💡 Two rules: `open < n` → add `'('`. `close < open` → add `')'`. Base: `curr.length() == 2n`. These rules prune all invalid paths at the source.

### Why `close < open`?

- `close < open` means we have more open brackets than close — safe to close one.
- `close == open` means fully balanced so far — must open a new one (or we're done).
- `close > open` would mean more `)` than `(` — invalid, never allowed.

### Algorithm
1. **Base:** `curr.length() == 2*n` → push `curr`, return.
2. **Add '(':** if `open < n` → recurse with `open+1`.
3. **Add ')':** if `close < open` → recurse with `close+1`.

### C++ Code

```cpp
class Solution {
public:
    vector<string> generateParenthesis(int n){
        vector<string> res;
        backtrack("",0,0,n,res);
        return res;
    }

    void backtrack(string curr,int open,int close,int n,vector<string>& res){
        if(curr.length()==2*(size_t)n){
            res.push_back(curr);
            return;
        }
        if(open<n) backtrack(curr+'(',open+1,close,n,res);
        if(close<open) backtrack(curr+')',open,close+1,n,res);
    }
};
```

**Time:** O(4^n / √n) — Catalan number C(n) counts valid strings, each of length 2n
**Space:** O(n) recursion depth (not counting output)

### Dry Run — `n = 2`

```
backtrack("", 0, 0)
├── add '(' → backtrack("(", 1, 0)
│   ├── add '(' → backtrack("((", 2, 0)
│   │   └── add ')' → backtrack("(()", 2, 1)
│   │       └── add ')' → backtrack("(())", 2, 2) → length=4=2*2 ✓ add "(())"
│   └── add ')' → backtrack("()", 1, 1)
│       └── add '(' → backtrack("()(", 2, 1)
│           └── add ')' → backtrack("()()", 2, 2) → ✓ add "()()"
```

Output: `["(())", "()()"]` ✓

### Decision Tree for n=3

```
Each node: (curr, open, close)
Rule: left child adds '(' if open<3, right child adds ')' if close<open
Valid strings appear at depth 6 (length == 2*3 == 6)
Total valid = C(3) = 5 strings
```

---

## 🔄 Comparison with Generate Binary Strings

| | Binary Strings No 11 | Generate Parentheses |
|---|---|---|
| Branch A | always add '0' | add '(' if open < n |
| Branch B | add '1' if back≠'1' | add ')' if close < open |
| Base case | length == n | length == 2n |
| State | `curr.back()` | `open`, `close` counters |

Both are **constrained generation** via recursive branching. The constraint is just expressed differently.

---

## 🧾 Recall Line *(10-Second Revision)*

> "Two rules: add `'('` if `open < n`; add `')'` if `close < open`. Base: length == 2n. No post-filtering — rules prune at the source."

---

## 📝 Short Revision Notes

- `close < open` is the key invariant: ensures we never close before opening.
- When `open == close == n`, both branches are blocked → only the base case fires.
- Passing `curr` by value (not reference) avoids the need for explicit backtrack pop.
- If you pass `curr` by reference for efficiency, you must `curr.pop_back()` after each recursive call.

---

## ⚠️ Common Mistakes

❌ Condition `close <= open` instead of `close < open` — allows adding `)` when balanced, producing invalid strings like `"()" + ")"`.
❌ Missing the `open < n` guard — can generate strings with too many `'('`.
❌ Base condition `curr.length() == n` instead of `2*n` — returns half-formed strings.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "generate all valid/well-formed combinations with balance constraint" → **two-branch recursion with open/close counters**, add one branch if count < limit, other branch if count < other count.

---

## 🏆 Pattern Category

`Recursion` · `Backtracking` · `String Generation` · `Catalan Numbers`

---

## ⏱️ 30-Second Last-Minute Revision

> Add `'('` if `open<n`, add `')'` if `close<open`. Base: `length==2n`. Catalan(n) valid strings. **Time:** O(4^n/√n) | **Space:** O(n) depth.
