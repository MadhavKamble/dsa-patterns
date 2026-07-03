# 🔥 Rotate String

> **LeetCode #796** · **Difficulty:** Easy · **Step 5 — Strings · P06**

---

## 🧠 Problem Understanding

**What is it asking?**
Return `true` if `goal` can be obtained by rotating `s` some number of times (shifting the leftmost character to the end).

**Input:** `s = "abcde"`, `goal = "cdeab"` → **Output:** `true`
**Input:** `s = "abcde"`, `goal = "abced"` → **Output:** `false`

**Key Observation:**
Every rotation of `s` is a substring of `s + s`. So `goal` is a rotation iff it has the same length **and** appears inside `s + s`.

---

## 🎯 Interview Progression

### 🥉 Brute Force — Try Every Rotation

Rotate `s` by 1 up to `n` times, comparing to `goal` each time. **Time:** O(N²).

---

### 🥇 Optimal — String Doubling

> 💡 Concatenate `s + s`; it contains all `n` rotations as substrings. Check `find(goal)`.

```cpp
class Solution {
public:
    bool rotateString(string& s,string& goal){
        if(s.length()!=goal.length()) return false;
        string doubledS=s+s;
        return doubledS.find(goal)!=string::npos;
    }
};
```

**Time:** O(N²) with naive `find` (O(N) with KMP) · **Space:** O(N).

### Dry Run
`s = "rotation"`, `goal = "tionrota"`

- Lengths equal (8 == 8).
- `doubledS = "rotationrotation"`.
- `find("tionrota")` → found at index 4 → **true** ✅

---

## 🧾 Recall Line *(10-Second Revision)*

> "goal is a rotation ⟺ same length AND `goal` is a substring of `s + s`."

---

## 📝 Short Revision Notes

- The length check is essential — otherwise a shorter `goal` could accidentally match.
- `s + s` holds every rotation because rotating slides a window of length `n` across it.
- `string::find` returns `string::npos` when not found.

---

## ⚠️ Common Mistakes

❌ Skipping the length check → false positives.
❌ Building `s + s` but comparing with `==` instead of substring search.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "is it a rotation of", "cyclic shift equals" → **check substring of the doubled string**.

---

## 🏆 Pattern Category

`Strings` · `Rotation` · `Substring Search`

---

## ⏱️ 30-Second Last-Minute Revision

> **Rotation ⟺ same length & `goal` ⊂ `s+s`.** One `find` call. `O(N)` with KMP.
