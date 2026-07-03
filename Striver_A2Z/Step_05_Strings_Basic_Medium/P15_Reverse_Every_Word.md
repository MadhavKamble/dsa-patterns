# 🔥 Reverse Every Word in a String

> **LeetCode #151** · **Difficulty:** Medium · **Step 5 — Strings · P15**

> **Same problem & code as [P02 Reverse Words in a String](P02_Reverse_Words_in_String.md)** — Striver lists it again at the end of Step 5. Full treatment (dry run, traps, alternatives) is in P02; this entry is a quick pointer.

---

## 🧠 Problem Understanding

Reverse the **order of words**, collapsing extra spaces and trimming the ends.

**Input:** `" amazing coding skills "` → **Output:** `"skills coding amazing"`

---

## 🥇 Optimal — Right-to-Left Word Scan

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

---

## 🧾 Recall Line *(10-Second Revision)*

> "Scan from right: skip spaces → grab word by bounds → append with single space. (= P02.)"

---

## 📝 Short Revision Notes

- Identical to P02 — see it for the full dry run, common mistakes, and the split-and-reverse alternative.
- Conditional separator (`!result.empty()`) auto-trims and single-spaces.

---

## 🏆 Pattern Category

`Strings` · `Two Pointers` · `Parsing`

---

## ⏱️ 30-Second Last-Minute Revision

> **Right-to-left word extraction, append with single spaces.** Same as P02. `O(N)`.
