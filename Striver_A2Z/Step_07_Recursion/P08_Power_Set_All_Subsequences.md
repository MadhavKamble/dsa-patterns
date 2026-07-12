# Power Set — Print All Subsequences of a String

> **LeetCode #78 variant** · **Difficulty:** Medium · **Step 7 — Recursion · P08**

---

## 🧠 Problem Understanding

**What is it asking?**
Generate all possible subsequences (subsets) of a string — including the empty string. A subsequence preserves relative order of characters but can skip any of them.

**Input:** `s = "abc"` → **Output:** `"" "a" "b" "ab" "c" "ac" "bc" "abc"` (2³ = 8 strings)

**Key Observations:**
- For each character, two choices: **include** it or **exclude** it.
- Total subsequences = 2^n (each char independently included/excluded).
- Two clean approaches: **bit masking** (iterative) and **include/exclude recursion**.

---

## 🥇 Approach 1 — Bit Mask (Iterative)

### Key Insight

> 💡 For n chars, there are 2^n possible bitmasks (0 to 2^n−1). Each mask represents a subset: if bit `i` is set, include `s[i]`.

```
mask 000 → ""
mask 001 → "a"  (bit 0 set)
mask 010 → "b"  (bit 1 set)
mask 011 → "ab"
mask 100 → "c"  (bit 2 set)
mask 101 → "ac"
mask 110 → "bc"
mask 111 → "abc"
```

### C++ Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> getSubsequences(string s){
        int n=s.size();
        int total=1<<n;
        vector<string> subsequences;
        for(int mask=0;mask<total;mask++){
            string subseq="";
            for(int i=0;i<n;i++){
                if(mask&(1<<i)){
                    subseq+=s[i];
                }
            }
            subsequences.push_back(subseq);
        }
        return subsequences;
    }
};
```

**Time:** O(2^n × n) · **Space:** O(2^n × n) for output

---

## 🥇 Approach 2 — Include/Exclude Recursion

### Key Insight

> 💡 At each index, branch into two paths: **exclude** `s[index]` (don't add, recurse forward) and **include** `s[index]` (add to current, recurse forward, then backtrack). Base case: index == n → store current.

### The Include/Exclude Tree for "ab"

```
helper(0, "")
├── exclude s[0]='a' → helper(1, "")
│   ├── exclude s[1]='b' → helper(2, "") → add ""
│   └── include s[1]='b' → helper(2, "b") → add "b"
└── include s[0]='a' → helper(1, "a")
    ├── exclude s[1]='b' → helper(2, "a") → add "a"
    └── include s[1]='b' → helper(2, "ab") → add "ab"
```

### C++ Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void helper(string& s,int index,string& current,vector<string>& result){
        if(index==(int)s.size()){
            result.push_back(current);
            return;
        }
        helper(s,index+1,current,result);
        current.push_back(s[index]);
        helper(s,index+1,current,result);
        current.pop_back();
    }

    vector<string> getSubsequences(string s){
        vector<string> result;
        string current="";
        helper(s,0,current,result);
        return result;
    }
};
```

**Time:** O(2^n × n) · **Space:** O(n) recursion depth (not counting output)

### Why `pop_back()` is Needed

- `current` is passed by reference — modifications persist across calls.
- After the "include" branch returns, we must undo the `push_back` so the "exclude" sibling at the parent level sees the correct state.
- This **backtracking** step is what makes the recursive approach memory-efficient: O(n) stack vs O(2^n × n) if you copy strings at each level.

---

## 🆚 Approach Comparison

| | Bit Mask | Include/Exclude Recursion |
|---|---|---|
| Style | Iterative | Recursive + Backtracking |
| Time | O(2^n × n) | O(2^n × n) |
| Space | O(1) extra | O(n) stack |
| Order | Lexicographic (by mask) | Exclude-first, then include |
| Intuition | Enumerate binary representations | Decision tree at each character |
| Extensibility | Fixed to subsets | Easy to add constraints (e.g., sum = K) |

**Use bit mask** for: simple generation, when you need lexicographic order.  
**Use recursion** for: when you need to add constraints (sum, length, no duplicates) — easier to prune.

---

## 🧾 Recall Line *(10-Second Revision)*

> "2^n subsets. Bit mask: each mask = subset (bit i set → include s[i]). Recursion: exclude then include at each index, `pop_back()` to backtrack. Both O(2^n × n)."

---

## 📝 Short Revision Notes

- `1 << n` gives 2^n — the total number of subsets.
- `mask & (1 << i)` checks if bit `i` is set in `mask`.
- In the recursive approach, **exclude comes before include** → empty string is generated first.
- The backtracking `pop_back()` is the recursive analog of the mask loop "not including a bit."
- Both approaches produce all 2^n subsequences; order differs.

---

## ⚠️ Common Mistakes

❌ Forgetting `pop_back()` in the recursive version — `current` grows forever.
❌ Using `current` by value instead of by reference — copies on every call, O(2^n × n) extra space.
❌ Bit mask: `mask < n` instead of `mask < (1 << n)` — only iterates n masks instead of 2^n.
❌ `i < total` when total should be `1 << n` not `n`.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "all subsets", "all subsequences", "power set" → **include/exclude at each index** or **bit mask 0 to 2^n−1**. Recursion scales better when constraints are added.

---

## 🏆 Pattern Category

`Recursion` · `Backtracking` · `Bit Manipulation` · `Subsets`

---

## ⏱️ 30-Second Last-Minute Revision

> For each char: include or exclude. Recursion: `helper(i+1)` (exclude), then `push+helper(i+1)+pop_back` (include). Bit mask: iterate masks 0→2^n, include s[i] if bit i set. Both O(2^n × n). Add backtrack constraint by pruning in the recursive version.
