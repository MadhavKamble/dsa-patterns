# 🔥 Reverse Words in a String

> **LeetCode #151** · **Difficulty:** Medium · **Step 5 — Strings · P02**

---

## 🧠 Problem Understanding

**What is it asking?**
Reverse the **order of words**. Collapse multiple spaces and trim leading/trailing spaces — the output has words separated by a single space.

**Input:** `s = " amazing coding skills "` → **Output:** `"skills coding amazing"`
**Input:** `s = "the sky is blue"` → **Output:** `"blue is the sky"`

**Key Observation:**
Scan from the **right**. Skip spaces, capture each word by its `[start, end]` bounds, and append words left-to-right into the result — that naturally reverses their order while normalizing spaces.

---

## 🎯 Interview Progression

### 🥉 Brute Force — Split & Reverse

Split on spaces into a list, reverse the list, join with single spaces. **Time:** O(N) · **Space:** O(N).

---

### 🥇 Optimal — Right-to-Left Scan

> 💡 Walk `i` from the end. Skip trailing spaces, mark `end`, walk back over the word, then `substr` it. Prepend a separator only when the result already has content — that handles spacing automatically.

```cpp
class Solution {
public:
    string reverseWords(string s){
        string result="";
        int i=s.size()-1;
        while(i>=0){
            while(i>=0 && s[i]==' ') i--;
            if(i<0) break;
            int end=i;
            while(i>=0 && s[i]!=' ') i--;
            string word=s.substr(i+1,end-i);
            if(!result.empty()) result+=" ";
            result+=word;
        }
        return result;
    }
};
```

**Time:** O(N) · **Space:** O(N).

### Dry Run
`s = " amazing coding skills "` (trailing space first)

| Step | i skips to | word `[i+1, end]` | result |
|------|-----------|-------------------|--------|
| 1 | end=14 (`skills`) | "skills" | `skills` |
| 2 | end=8 (`coding`) | "coding" | `skills coding` |
| 3 | end=1 (`amazing`) | "amazing" | `skills coding amazing` |
| 4 | i<0 | — | done |

**Output:** `"skills coding amazing"` ✅

---

## 🧾 Recall Line *(10-Second Revision)*

> "Scan from right: skip spaces → mark end → walk over word → substr. Add ' ' only if result non-empty."

---

## 📝 Short Revision Notes

- `substr(i+1, end - i)` — length is `end - (i+1) + 1 = end - i`.
- Adding the separator conditionally (`!result.empty()`) trims and single-spaces automatically.
- Handles leading, trailing, and multiple internal spaces without a separate cleanup pass.

---

## ⚠️ Common Mistakes

❌ Off-by-one in the `substr` length (`end - i` is correct here).
❌ Adding a trailing/leading space by unconditionally appending `" "`.
❌ Not skipping consecutive spaces → empty words in the output.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "reverse word order", "normalize spaces" → **two-pointer word extraction from the right**.

---

## 🏆 Pattern Category

`Strings` · `Two Pointers` · `Parsing`

---

## ⏱️ 30-Second Last-Minute Revision

> **Right-to-left.** Skip spaces, grab word by bounds, `substr`, append with a leading space only when result is non-empty. `O(N)`.
