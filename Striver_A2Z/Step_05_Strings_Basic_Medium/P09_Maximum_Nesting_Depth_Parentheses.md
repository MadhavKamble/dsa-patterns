# 🔥 Maximum Nesting Depth of the Parentheses

> **LeetCode #1614** · **Difficulty:** Easy · **Step 5 — Strings · P09**

---

## 🧠 Problem Understanding

**What is it asking?**
Given a **valid parentheses expression** (with digits/operators mixed in), return the maximum nesting depth of the parentheses.

**Input:** `s = "(1+(2*3)+((8)/4))+1"` → **Output:** `3`
**Input:** `s = "1+(2*3)/(2-1)"` → **Output:** `1`

**Key Observation:**
Running counter: `(` increases depth, `)` decreases it. The answer is the maximum value the counter reaches.

---

## 🎯 Interview Progression

### 🥇 Optimal — Running Depth Counter

> 💡 Track `p`. On `(` → `p++`; on `)` → `p--`; after each step update `ans = max(ans, p)`. Non-bracket characters are ignored.

```cpp
class Solution {
public:
    int maxDepth(string s){
        int p=0;
        int ans=0;
        for(char x:s){
            if(x=='(') p++;
            else if(x==')') p--;
            ans=max(ans,p);
        }
        return ans;
    }
};
```

**Time:** O(N) · **Space:** O(1).

### Dry Run
`s = "(1+(2*3)+((8)/4))+1"`

| Segment | depth `p` | max so far |
|---------|-----------|-----------|
| `(` | 1 | 1 |
| `(2*3)` | up to 2 | 2 |
| `((8)` | up to 3 | **3** |
| rest | ≤3, closes to 0 | 3 |

**Output:** `3` ✅

---

## 🧾 Recall Line *(10-Second Revision)*

> "`(` → depth++, `)` → depth--; answer = max depth reached."

---

## 📝 Short Revision Notes

- No stack needed — a single integer counter suffices for a *valid* expression.
- Update the max **after** incrementing so an opening bracket is counted.
- Non-parenthesis characters don't affect depth.

---

## ⚠️ Common Mistakes

❌ Using a stack (overkill) when a counter works.
❌ Updating `ans` only on `(` but forgetting it must reflect the current live depth (still fine here, but track consistently).

---

## 🧠 Pattern Recognition Trigger

**When I see:** "nesting depth", "balanced parentheses depth" → **running counter, track the max**.

---

## 🏆 Pattern Category

`Strings` · `Counter` · `Parentheses`

---

## ⏱️ 30-Second Last-Minute Revision

> **Counter:** `(` ++, `)` --, `ans = max(ans, depth)`. `O(N)`, O(1) space.
