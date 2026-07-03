# 🔥 Largest Odd Number in a String

> **LeetCode #1903** · **Difficulty:** Easy · **Step 5 — Strings · P03**

---

## 🧠 Problem Understanding

**What is it asking?**
Given a string of digits, return the **largest-valued odd number** that is a **non-empty prefix substring ending at some index** (you may only trim from the right). Return `""` if no odd number exists.

**Input:** `s = "52"` → **Output:** `"5"`
**Input:** `s = "4206"` → **Output:** `""` (no odd digit)
**Input:** `s = "35427"` → **Output:** `"35427"` (last digit already odd)

**Key Observation:**
A number is odd iff its **last digit** is odd. To keep the value largest, extend as far **right** as possible — so find the **rightmost odd digit**; the answer is the prefix ending there (after trimming leading zeros).

---

## 🎯 Interview Progression

### 🥇 Optimal — Find the Rightmost Odd Digit

> 💡 Scan from the right for the first odd digit (index `ind`). The answer is `s[0..ind]`, minus any leading zeros.

```cpp
class Solution {
public:
    string largeOddNum(string& s){
        int ind=-1;
        int i;
        for(i=s.length()-1;i>=0;i--){
            if((s[i]-'0')%2==1){
                ind=i;
                break;
            }
        }
        i=0;
        while(i<=ind && s[i]=='0') i++;
        return s.substr(i,ind-i+1);
    }
};
```

**Time:** O(N) · **Space:** O(1) (excluding the output).

### Dry Run
`s = "504"`

- Scan right→left: `4`(even), `0`(even), `5`(odd) → `ind = 0`.
- Skip leading zeros up to `ind`: `i=0`, `s[0]='5'` ≠ '0' → stop.
- `substr(0, 0-0+1) = substr(0,1) = "5"`.

**Output:** `"5"` ✅

---

## 🧾 Recall Line *(10-Second Revision)*

> "Odd ⟺ last digit odd. Find rightmost odd digit `ind`; trim leading zeros; return prefix `s[i..ind]`."

---

## 📝 Short Revision Notes

- Only the **last digit's parity** decides oddness → extend as far right as possible for the max value.
- If no odd digit exists, `ind` stays `-1` → `substr` returns `""` (the `while` doesn't run since `i<=ind` is false).
- Trim leading zeros so `"0005"` → `"5"`, not `"0005"`.

---

## ⚠️ Common Mistakes

❌ Scanning left-to-right for the first odd digit → gives a shorter (smaller) number.
❌ Forgetting to strip leading zeros.
❌ Not handling the all-even case (`""`).

---

## 🧠 Pattern Recognition Trigger

**When I see:** "largest odd number", "trim from the right", "parity of last digit" → **rightmost-odd-digit scan**.

---

## 🏆 Pattern Category

`Strings` · `Greedy` · `Digits`

---

## ⏱️ 30-Second Last-Minute Revision

> **Odd ⟺ last digit odd.** Find rightmost odd digit, strip leading zeros, return that prefix. `O(N)`.
