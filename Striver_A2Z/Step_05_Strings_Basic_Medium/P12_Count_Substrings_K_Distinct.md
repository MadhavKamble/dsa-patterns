# 🔥 Count Number of Substrings (Exactly K Distinct Characters)

> **GFG / LeetCode #992 (analog)** · **Difficulty:** Medium · **Step 5 — Strings · P12**

---

## 🧠 Problem Understanding

**What is it asking?**
Count the substrings that contain **exactly `k` distinct** characters.

**Input:** `s = "pqpqs"`, `k = 2` → **Output:** `7`
(the substrings: `pq, pqp, qp, qpq, pq, pqs`… → 7 with exactly 2 distinct)

**Key Observation:**
"Exactly k" is hard directly, but easy as a difference of two "at most" counts:
```
exactly(k) = atMost(k) − atMost(k−1)
```
`atMost(k)` is a classic **variable-size sliding window**.

---

## 🎯 Interview Progression

### 🥉 Brute Force — All Substrings

Enumerate every substring, count distinct with a set. **Time:** O(N²) (or O(N²·26)).

---

### 🥇 Optimal — atMost(k) − atMost(k−1) via Sliding Window

> 💡 `atMostKDistinct`: expand `right`, shrink `left` while distinct > k. Every step, all windows ending at `right` with ≤ k distinct number `right - left + 1`. Subtract the `k-1` version to isolate exactly `k`.

```cpp
class Solution {
public:
    int atMostKDistinct(string s,int k){
        int left=0,res=0;
        unordered_map<char,int> freq;
        for(int right=0;right<s.size();right++){
            freq[s[right]]++;
            while(freq.size()>k){
                freq[s[left]]--;
                if(freq[s[left]]==0) freq.erase(s[left]);
                left++;
            }
            res+=(right-left+1);
        }
        return res;
    }
    int countSubstrings(string s,int k){
        return atMostKDistinct(s,k)-atMostKDistinct(s,k-1);
    }
};
```

**Time:** O(N) per `atMost` → **O(N)** total · **Space:** O(k).

### Dry Run
`s = "pqpqs"`, `k = 2`

- `atMost(2)` counts all substrings with ≤ 2 distinct → 12.
- `atMost(1)` counts all substrings with ≤ 1 distinct → 5.
- `exactly(2) = 12 − 5 = 7` ✅

---

## 🧾 Recall Line *(10-Second Revision)*

> "exactly(k) = atMost(k) − atMost(k−1). atMost = sliding window, add `right−left+1` each step."

---

## 📝 Short Revision Notes

- The `atMost(k) − atMost(k−1)` trick converts a hard "exactly" into two easy "at most" windows.
- In `atMost`, `res += right - left + 1` counts every valid window ending at `right`.
- Erase a character from the map when its count hits 0 so `freq.size()` = distinct count.

---

## ⚠️ Common Mistakes

❌ Trying to count "exactly k" directly with one window (hard to maintain).
❌ Not erasing zero-count characters → `freq.size()` overcounts distinct.
❌ Forgetting the window contributes `right - left + 1`, not just 1.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "exactly k distinct", "substrings/subarrays with a distinct constraint" → **atMost(k) − atMost(k−1) sliding window**.

---

## 🏆 Pattern Category

`Strings` · `Sliding Window` · `Counting`

---

## ⏱️ 30-Second Last-Minute Revision

> **exactly(k) = atMost(k) − atMost(k−1).** Window adds `right−left+1`; shrink while distinct > k. `O(N)`.
