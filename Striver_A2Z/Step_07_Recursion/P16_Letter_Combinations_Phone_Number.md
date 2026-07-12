# Letter Combinations of a Phone Number

> **LeetCode #17** · **Difficulty:** Medium · **Step 7 — Recursion · P16**

---

## 🧠 Problem Understanding

**What is it asking?**
Given a string of digits (2–9), return all possible letter combinations each digit could represent (phone keypad mapping). Return empty list if input is empty.

**Input:** `digits = "23"` → **Output:** `["ad","ae","af","bd","be","bf","cd","ce","cf"]`

**Key Observations:**
- At each digit, we have 3 or 4 letter choices (keypad mapping).
- Process one digit per recursion level → depth equals `digits.length()`.
- Each path through the tree corresponds to one complete combination.
- Total combinations = product of choices per digit (e.g. `"23"` → 3×3 = 9).

---

## 🥇 Recursive Digit-by-Digit Expansion

### Key Insight

> 💡 At index `idx`, look up the letters for `digits[idx]`, branch once per letter (appending it to the current string), then advance to `idx+1`. Base: when `idx == digits.size()`, push the complete string.

### Phone Keypad Mapping

```
combos[] = {"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"}
Index:       0    1    2      3     4     5     6     7      8     9
```

Digits 0 and 1 map to `""` — they produce no branches (not valid phone inputs per problem).

### Algorithm
1. **Base:** `idx == digits.size()` → push `s` (only if non-empty), return.
2. Look up `digit = digits[idx] - '0'`.
3. Loop over each letter in `combos[digit]`:
   - Recurse `func(idx+1, digits, s + letter, ...)`.

### C++ Code

```cpp
class Solution {
public:
    vector<string> letterCombinations(string digits){
        if(digits.empty()) return {};
        string combos[]={"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
        vector<string> ans;
        string s="";
        func(0,digits,s,ans,combos);
        return ans;
    }

    void func(int idx,string digits,string s,vector<string>& ans,string combos[]){
        if(idx==(int)digits.size()){
            ans.push_back(s);
            return;
        }
        int digit=digits[idx]-'0';
        for(int i=0;i<(int)combos[digit].size();i++){
            func(idx+1,digits,s+combos[digit][i],ans,combos);
        }
    }
};
```

**Time:** O(4^N × N) — N digits, up to 4 letters each, string copy O(N) per leaf
**Space:** O(N) recursion depth

### Why No Explicit Backtracking?

`s` is passed **by value** and extended with `s + combos[digit][i]` (creates a new string). Each recursive call gets its own copy — no `pop_back` needed. This is slightly less memory-efficient (copies string each call) but cleaner.

**Reference + backtrack alternative** (same result, O(1) copy per call):
```cpp
void func(int idx,string digits,string& s,vector<string>& ans,string combos[]){
    if(idx==(int)digits.size()){ ans.push_back(s); return; }
    int digit=digits[idx]-'0';
    for(char c:combos[digit]){
        s.push_back(c);
        func(idx+1,digits,s,ans,combos);
        s.pop_back();
    }
}
```

### Dry Run — `digits = "23"`

```
combos[2]="abc", combos[3]="def"

func(0, "23", "")
├── 'a' → func(1, "23", "a")
│   ├── 'd' → func(2, ..., "ad") → push "ad"
│   ├── 'e' → func(2, ..., "ae") → push "ae"
│   └── 'f' → func(2, ..., "af") → push "af"
├── 'b' → func(1, "23", "b")
│   ├── 'd' → push "bd"
│   ├── 'e' → push "be"
│   └── 'f' → push "bf"
└── 'c' → func(1, "23", "c")
    ├── 'd' → push "cd"
    ├── 'e' → push "ce"
    └── 'f' → push "cf"
```

**Output:** `["ad","ae","af","bd","be","bf","cd","ce","cf"]` ✓

---

## 🔄 Alternative — Iterative BFS

```cpp
vector<string> letterCombinations(string digits){
    if(digits.empty()) return {};
    string combos[]={"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
    vector<string> result={""};
    for(char d:digits){
        vector<string> next;
        for(string& curr:result)
            for(char c:combos[d-'0'])
                next.push_back(curr+c);
        result=next;
    }
    return result;
}
```

Builds combinations level by level. Same O(4^N × N) time.

---

## ⚠️ Edge Case

`digits = ""` → return `{}` (empty vector), **not** `[""]`.
The code's `if(digits.empty()) return {}` guard handles this. Without it, `func` hits the base case immediately and pushes empty string `""` — wrong answer.

---

## 🧾 Recall Line *(10-Second Revision)*

> "At each digit, loop over its mapped letters, append, recurse. Base: `idx==size → push`. Guard empty input → return `{}`. String by value = no explicit backtrack."

---

## 📝 Short Revision Notes

- The mapping array indexed by digit directly: `combos[digits[idx]-'0']`.
- Passing `string` by value is clean but copies on every call — for large inputs, use reference + push/pop.
- This pattern generalizes: "at each position, choose from a set of options and recurse" — the structure of any multi-level combinatorial problem.

---

## ⚠️ Common Mistakes

❌ Not handling empty `digits` — pushes `[""]` instead of `[]`.
❌ Using `digits` by reference in `func` but forgetting it shouldn't be modified.
❌ Wrong mapping index: forgetting `digits[idx] - '0'` to convert char to int.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "at each step, choose one from a set of options (per position)" → **loop over options at each index, recurse with `idx+1`, collect at base**.

---

## 🏆 Pattern Category

`Recursion` · `Backtracking` · `String Generation` · `Keypad / Mapping`

---

## ⏱️ 30-Second Last-Minute Revision

> `combos[]` maps digit→letters. At each `idx`, loop letters, `recurse(idx+1, s+letter)`. Base: `idx==size → push`. Guard: `digits.empty() → return {}`. **Time:** O(4^N × N).
