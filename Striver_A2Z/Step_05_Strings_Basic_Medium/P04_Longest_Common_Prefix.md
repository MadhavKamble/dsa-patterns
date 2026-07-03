# 🔥 Longest Common Prefix

> **LeetCode #14** · **Difficulty:** Easy · **Step 5 — Strings · P04**

---

## 🧠 Problem Understanding

**What is it asking?**
Find the longest string that is a **prefix of every** string in the array. Return `""` if there's none.

**Input:** `["interview","internet","internal","interval"]` → **Output:** `"inter"`
**Input:** `["dog","racecar","car"]` → **Output:** `""`

**Key Observation:**
After **sorting** lexicographically, only the **first** and **last** strings can disagree the earliest — the common prefix of just those two is the common prefix of the whole set.

---

## 🎯 Interview Progression

### 🥉 Brute Force — Vertical Scan

Compare character `i` across all strings; stop at the first mismatch or shortest string. **Time:** O(N·M) (N strings, M chars).

---

### 🥇 Optimal — Sort, Compare First & Last

> 💡 Sort the array. The lexicographically smallest (`first`) and largest (`last`) bracket the whole set, so their shared prefix is the answer.

```cpp
class Solution {
public:
    string longestCommonPrefix(vector<string>& str){
        if(str.empty()) return "";
        sort(str.begin(),str.end());
        string first=str[0];
        string last=str[str.size()-1];
        string ans="";
        int minLength=min(first.size(),last.size());
        for(int i=0;i<minLength;i++){
            if(first[i]!=last[i]) break;
            ans+=first[i];
        }
        return ans;
    }
};
```

**Time:** O(N·M·log N) (sort) · **Space:** O(1) extra.

### Dry Run
`["interview","internet","internal","interval"]` → sorted `["internal","internet","interval","interview"]`

- `first = "internal"`, `last = "interview"`.
- Match `i-n-t-e-r`, then `first[5]='n'` vs `last[5]='v'` → break.

**Output:** `"inter"` ✅

---

## 🧾 Recall Line *(10-Second Revision)*

> "Sort. Common prefix of first & last sorted strings = LCP of all."

---

## 📝 Short Revision Notes

- Sorting groups the most-different strings at the two ends → comparing them suffices.
- Compare only up to `min(first.size(), last.size())`.
- Vertical scan (no sort) is O(N·M) and often preferred when N is huge; the sort version is shorter to write.

---

## ⚠️ Common Mistakes

❌ Comparing beyond the shorter string's length → out of bounds.
❌ Forgetting the empty-array guard.
❌ Assuming the first string is the shortest — must bound by `min` of first & last.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "common prefix across many strings" → **sort + compare extremes** (or vertical scan).

---

## 🏆 Pattern Category

`Strings` · `Sorting`

---

## ⏱️ 30-Second Last-Minute Revision

> **Sort, compare first & last.** Match chars until they differ; that's the LCP. `O(N·M·log N)`.
