# Generate Binary Strings without Consecutive 1's

> **GFG / Striver** · **Difficulty:** Medium · **Step 7 — Recursion · P06**

---

## 🧠 Problem Understanding

**What is it asking?**
Generate all binary strings of length `n` such that no two consecutive characters are `'1'`.

**Input:** `n = 3`
**Output:** `000 001 010 100 101`

**Key Observations:**
- `'0'` can always be appended — it never creates a consecutive-1 violation.
- `'1'` can only be appended if the previous character is not `'1'`.
- This is a classic recursive branching with constraint problem.
- Total valid strings = Fibonacci(n+2): for n=1→2, n=2→3, n=3→5, n=4→8, ...

---

## 🥇 Recursive Approach

### Key Insight

> 💡 At each position, always try `'0'`. Try `'1'` only if `curr` is empty or `curr.back() != '1'`. Recurse until `curr.length() == n`.

### Algorithm
1. **Base:** `curr.length() == n` → push to result, return.
2. **Branch 0:** `generate(n, curr+"0", result)` — always valid.
3. **Branch 1:** if `curr.empty() || curr.back() != '1'` → `generate(n, curr+"1", result)`.

### C++ Code

```cpp
#include <bits/stdc++.h>
using namespace std;

void generate(int n,string curr,vector<string>& result){
    if(curr.length()==(size_t)n){
        result.push_back(curr);
        return;
    }
    generate(n,curr+"0",result);
    if(curr.empty() || curr.back()!='1'){
        generate(n,curr+"1",result);
    }
}

int main(){
    int n=3;
    vector<string> result;
    generate(n,"",result);
    for(string& s:result) cout<<s<<" ";
    cout<<endl;
    return 0;
}
```

**Time:** O(Fib(n+2) × n) — number of valid strings × string length
**Space:** O(n) — recursion depth (not counting output)

### Dry Run — `n = 3`

```
generate(3, "")
├── generate(3, "0")
│   ├── generate(3, "00")
│   │   ├── generate(3, "000") → ✓ add "000"
│   │   └── generate(3, "001") → ✓ add "001"
│   └── generate(3, "01")
│       ├── generate(3, "010") → ✓ add "010"
│       └── generate(3, "011") → back='1' → skip '1' branch
│           → only: generate(3, "010") already done
│           wait — "01" back='1'? No, back='1' only for "11"
```

Wait — `"01".back() = '1'` → so from `"01"` we cannot add another `'1'`.
```
generate(3, "")
├── "0" → "00" → "000" ✓, "001" ✓
│        → "01" → "010" ✓  (can't add '1' since back='1')
└── "1" → "10" → "100" ✓, "101" ✓
         → "11" → can't add '1' (back='1'), so only:
                  "110" ✓   ← wait, "11" has back='1' so no '1' branch
```

Wait, `"1".back() = '1'`, so from `""` we add `"1"`, then from `"1"` we can only add `"0"` (not `"1"`). Let me redo:
```
"" → "0", "1"
"0" → "00", "01"
"1" → "10"          (back='1', skip '1')
"00" → "000" ✓, "001" ✓
"01" → "010" ✓      (back='1', skip '1')
"10" → "100" ✓, "101" ✓
```
Output: `000 001 010 100 101` ✓ (5 strings for n=3)

---

## 🔄 Alternative — Iterative with Bit Mask

Only valid if you want generation order control (not required here):
```cpp
// Just generate all 2^n strings and filter — O(2^n * n), wasteful
```
Not worth it — the recursive approach is both cleaner and more efficient.

---

## 🧾 Recall Line *(10-Second Revision)*

> "Always add '0'. Add '1' only if `curr.empty() || curr.back() != '1'`. Recurse until length n. Count = Fibonacci(n+2)."

---

## 📝 Short Revision Notes

- `curr.back()` on an empty string is UB — always check `curr.empty()` first.
- `curr.length() == n` comparison: `length()` returns `size_t` (unsigned); compare with cast `(size_t)n` or just use `(int)curr.length() == n`.
- The constraint "no consecutive 1s" is purely a branching guard, not post-filtering.

---

## ⚠️ Common Mistakes

❌ Checking `curr.back() != '1'` without first checking `curr.empty()` → UB on empty string.
❌ Forgetting to try `'0'` unconditionally — `'0'` is always safe.
❌ Post-filtering all 2^n strings instead of pruning during recursion — wastes work.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "generate strings with constraint on adjacent characters" → **branching recursion with guard on `curr.back()`**.

---

## 🏆 Pattern Category

`Recursion` · `Backtracking` · `String Generation`

---

## ⏱️ 30-Second Last-Minute Revision

> Always branch '0'. Branch '1' only if `curr.empty() || curr.back() != '1'`. Base: length==n, push result. Count = Fib(n+2). **Time:** O(Fib(n)×n) | **Space:** O(n) stack.
