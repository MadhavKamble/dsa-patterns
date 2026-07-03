# 🔥 Remove Outermost Parentheses

> **LeetCode #1021** · **Difficulty:** Easy · **Step 5 — Strings · P01**

---

## 🧠 Problem Understanding

**What is it asking?**
A valid parentheses string decomposes into **primitive** pieces. Remove the **outermost** pair of every primitive and concatenate the rest.

**Input:** `s = "(()())(())"` → **Output:** `"()()()"`
**Input:** `s = "(()())(())(()(()))"` → **Output:** `"()()()()(())"`

**Key Observation:**
Track the nesting **level**. The outermost `(` (level goes 0→1) and its matching `)` (level goes 1→0) are the ones to drop; everything strictly **inside** (level ≥ 1) is kept.

---

## 🎯 Interview Progression

### 🥇 Optimal — Depth Counter

> 💡 Keep a running `level`. On `(`: append only if already inside (`level>0`), then increment. On `)`: decrement first, then append only if still inside (`level>0`). This drops exactly the outer pair of each primitive.

```cpp
class Solution {
public:
    string removeOuterParentheses(string s){
        string result="";
        int level=0;
        for(char ch:s){
            if(ch=='('){
                if(level>0) result+=ch;
                level++;
            }else if(ch==')'){
                level--;
                if(level>0) result+=ch;
            }
        }
        return result;
    }
};
```

**Time:** O(N) · **Space:** O(N) for the result.

### Dry Run
`s = "(()())(())"`

| ch | level before | append? | result |
|----|--------------|---------|--------|
| ( | 0 | no (outer) → level=1 | `` |
| ( | 1 | yes → level=2 | `(` |
| ) | 2 | level=1, yes | `()` |
| ( | 1 | yes → level=2 | `()(` |
| ) | 2 | level=1, yes | `()()` |
| ) | 1 | level=0, no (outer) | `()()` |
| ( | 0 | no → level=1 | `()()` |
| ( | 1 | yes → level=2 | `()()(` |
| ) | 2 | level=1, yes | `()()()` |
| ) | 1 | level=0, no | `()()()` |

**Output:** `"()()()"` ✅

---

## 🧾 Recall Line *(10-Second Revision)*

> "Track level. `(`: append if level>0 then `level++`. `)`: `level--` then append if level>0. Outer pair dropped."

---

## 📝 Short Revision Notes

- The **order matters**: for `(` increment *after* the check; for `)` decrement *before* the check.
- A character is kept iff the current depth is ≥ 1 (strictly inside a primitive).
- Input is guaranteed valid, so `level` never goes negative unexpectedly.

---

## ⚠️ Common Mistakes

❌ Incrementing/decrementing before/after the append check in the wrong order → keeps or drops the wrong bracket.
❌ Appending when `level == 0` → leaves the outer parentheses in.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "valid parentheses", "primitive decomposition", "remove outer layer" → **depth/level counter**.

---

## 🏆 Pattern Category

`Strings` · `Stack/Depth Counter`

---

## ⏱️ 30-Second Last-Minute Revision

> **Depth counter.** `(` → append if depth>0, then depth++. `)` → depth--, then append if depth>0. `O(N)`.
