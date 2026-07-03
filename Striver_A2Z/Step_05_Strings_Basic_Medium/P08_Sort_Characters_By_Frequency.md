# 🔥 Sort Characters by Frequency

> **LeetCode #451 (variant)** · **Difficulty:** Medium · **Step 5 — Strings · P08**

---

## 🧠 Problem Understanding

**What is it asking?**
Order characters by **decreasing frequency**. This version returns the **distinct characters** in that order (ties broken by character ascending).

**Input:** `s = "tree"` → **Output:** `['e','r','t']` (e appears 2×; r, t once each → tie broken alphabetically)

> **LeetCode #451 variant:** returns a *string* with each character repeated by its count, e.g. `"eert"`. Same counting; only the output assembly differs (see notes).

**Key Observation:**
Count with a fixed `26`-array of `(frequency, char)` pairs, then sort by `(freq desc, char asc)`.

---

## 🎯 Interview Progression

### 🥉 Brute Force — Map + Sort Entries

Hash-map counts, dump to a vector, sort by frequency. **Time:** O(N + K log K).

---

### 🥇 Optimal — Fixed Pair Array + Comparator

> 💡 Store `(count, char)` per letter, sort with a custom comparator (higher frequency first, then smaller character), and emit the ones with nonzero count.

```cpp
class Solution {
public:
    static bool comparator(pair<int,char> p1,pair<int,char> p2){
        if(p1.first>p2.first) return true;
        if(p1.first<p2.first) return false;
        return p1.second<p2.second;
    }
    vector<char> frequencySort(string& s){
        pair<int,char> freq[26];
        for(int i=0;i<26;i++){
            freq[i]={0,i+'a'};
        }
        for(char ch:s){
            freq[ch-'a'].first++;
        }
        sort(freq,freq+26,comparator);
        vector<char> ans;
        for(int i=0;i<26;i++){
            if(freq[i].first>0) ans.push_back(freq[i].second);
        }
        return ans;
    }
};
```

**Time:** O(N + 26 log 26) = O(N) · **Space:** O(1) (fixed 26 array).

### Dry Run
`s = "tree"` → counts `t:1, r:1, e:2`.

Sorted by `(freq desc, char asc)`: `(2,'e'), (1,'r'), (1,'t'), (0,...)`.
Emit nonzero → `['e','r','t']` ✅

---

## 🧾 Recall Line *(10-Second Revision)*

> "Count into (freq,char) pairs. Sort freq desc, char asc. Emit nonzero."

---

## 📝 Short Revision Notes

- Comparator: `freq` **descending**, char **ascending** on ties.
- Initialize each bucket with its own character (`i + 'a'`) so the char survives sorting.
- **LC #451 output:** to build the repeated string, append each character `freq` times instead of once:
  ```cpp
  string res; for(auto& p:freq) res.append(p.first, p.second);
  ```
- Lowercase-only here; extend to 256 buckets for general characters.

---

## ⚠️ Common Mistakes

❌ Forgetting the tie-break → unstable/ambiguous ordering.
❌ Losing the character identity after sorting (store it in the pair).
❌ Confusing this (distinct chars) with LC #451 (repeated chars).

---

## 🧠 Pattern Recognition Trigger

**When I see:** "sort by frequency", "most frequent characters first" → **count + sort (freq, char) pairs**.

---

## 🏆 Pattern Category

`Strings` · `Frequency Count` · `Sorting`

---

## ⏱️ 30-Second Last-Minute Revision

> **(freq, char) per letter → sort freq↓ char↑ → emit.** Distinct chars here; append×count for the LC #451 string. `O(N)`.
