# 🔥 Isomorphic Strings

> **LeetCode #205** · **Difficulty:** Easy · **Step 5 — Strings · P05**

---

## 🧠 Problem Understanding

**What is it asking?**
Two strings are **isomorphic** if characters of `s` can be replaced to get `t` with a **consistent one-to-one mapping** — no two characters map to the same character, and each maps to exactly one.

**Input:** `s = "egg"`, `t = "add"` → **Output:** `true`
**Input:** `s = "paper"`, `t = "title"` → **Output:** `true`
**Input:** `s = "foo"`, `t = "bar"` → **Output:** `false`

**Key Observation:**
At each index, the **last-seen position** of `s[i]` and of `t[i]` must match. If they've appeared before, they must have appeared *together at the same index*; if one is new, both must be new.

---

## 🎯 Interview Progression

### 🥇 Optimal — Last-Seen Index Fingerprint

> 💡 Store, for each character, the **last index + 1** it appeared at (in `m1` for `s`, `m2` for `t`). If `m1[s[i]] != m2[t[i]]`, the mapping is inconsistent → not isomorphic. (Using `index+1` lets `0` mean "unseen".)

```cpp
class Solution {
public:
    bool isomorphicString(string s,string t){
        int m1[256]={0},m2[256]={0};
        int n=s.size();
        for(int i=0;i<n;++i){
            if(m1[s[i]]!=m2[t[i]]) return false;
            m1[s[i]]=i+1;
            m2[t[i]]=i+1;
        }
        return true;
    }
};
```

**Time:** O(N) · **Space:** O(1) (fixed 256-size arrays).

### Dry Run
`s = "paper"`, `t = "title"`

| i | s[i] | t[i] | m1[s[i]] | m2[t[i]] | equal? | update |
|---|------|------|----------|----------|--------|--------|
| 0 | p | t | 0 | 0 | ✅ | m1[p]=1, m2[t]=1 |
| 1 | a | i | 0 | 0 | ✅ | m1[a]=2, m2[i]=2 |
| 2 | p | t | 1 | 1 | ✅ | m1[p]=3, m2[t]=3 |
| 3 | e | l | 0 | 0 | ✅ | m1[e]=4, m2[l]=4 |
| 4 | r | e | 0 | 0 | ✅ | m1[r]=5, m2[e]=5 |

**Output:** `true` ✅

---

## 🧾 Recall Line *(10-Second Revision)*

> "Store last-seen index+1 of each char in both strings. If `m1[s[i]] != m2[t[i]]` → false."

---

## 📝 Short Revision Notes

- `index + 1` so an unseen character reads `0` (distinct from index 0).
- Checking both directions in one comparison enforces the **bijection** (rules out two chars mapping to one).
- Alternative: two hash maps `s→t` and `t→s`, verifying consistency both ways.
- Assumes equal lengths (guaranteed by the problem).

---

## ⚠️ Common Mistakes

❌ Mapping only `s→t` (one direction) → misses cases like `"ab" → "aa"`.
❌ Storing the raw index `0` without the `+1` offset → confuses "unseen" with "index 0".
❌ Using `char` as a negative array index (use `unsigned`/256-size array; fine for ASCII here).

---

## 🧠 Pattern Recognition Trigger

**When I see:** "consistent character mapping", "one-to-one replacement", "pattern match" → **paired last-seen fingerprint / two maps**.

---

## 🏆 Pattern Category

`Strings` · `Hashing` · `Mapping`

---

## ⏱️ 30-Second Last-Minute Revision

> **Last-seen index+1 in both strings must always agree.** `m1[s[i]] != m2[t[i]]` → false. Enforces bijection. `O(N)`.
