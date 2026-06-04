# 🔥 Find the Number That Appears Once (Others Appear Twice)

> **LeetCode #136** · **Difficulty:** Easy · **Step 3 — Arrays · P14**

---

## 🧠 Problem Understanding

Given an array where every element appears **twice** except one. Find that element.

**Input:** `[4,1,2,1,2]` → **Output:** `4`

**Key Observation:** XOR self-cancellation: `a ^ a = 0`, `a ^ 0 = a`. XOR all elements → pairs cancel → single element remains.

---

## 🥉 Brute Force
Hash map frequency count, return element with count=1. **Time:** O(N) · **Space:** O(N)

---

## 🥇 Optimal — XOR

### Key Observation
> 💡 `4^1^2^1^2 = 4^(1^1)^(2^2) = 4^0^0 = 4`  
> Order doesn't matter (XOR is commutative and associative). All pairs cancel.

### Complexity
- **Time:** O(N) · **Space:** O(1)

```cpp
/*
 * SINGLE NUMBER — XOR all elements, pairs cancel, lone element survives
 * Time O(N) | Space O(1)
 */
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int result = 0;
        for (int x : nums) result ^= x;
        return result;
    }
};
```

### Dry Run
`[4,1,2,1,2]`  
`0^4=4 → 4^1=5 → 5^2=7 → 7^1=6 → 6^2=4` → **4** ✅

---

## 🎤 Interview Explanation Script
> "XOR has two key properties: `a^a=0` and `a^0=a`. XOR-ing all elements, every duplicate pair cancels to 0, and only the single element remains. This is O(N) time, O(1) space — impossible to do better."

---

## 🧾 Recall Line
> "XOR all elements. Pairs cancel (`a^a=0`). Single survives (`a^0=a`)."

## 📝 Short Revision Notes
- XOR: commutative, associative, self-inverse
- Extension: two singles (LC 260) → XOR all, find rightmost set bit to split into two groups
- Extension: one element appears 3x, others 2x (LC 137) → bit counting per position

## ⚠️ Common Mistakes
❌ Sorting-based approach is O(N log N) — XOR is O(N)  
❌ Hash map works but O(N) space — XOR is optimal  
❌ For "appears 3 times" variant, XOR doesn't work directly

## 🔥 What Interviewer Is Testing
- XOR bit manipulation mastery
- Achieving O(1) space is the key goal

## 📚 Related Problems
- [ ] LeetCode #136 — Single Number
- [ ] LeetCode #137 — Single Number II (one appears 3x)
- [ ] LeetCode #260 — Single Number III (two singles)

## 🏆 Pattern Category
`Arrays` · `Bit Manipulation` · `XOR`

## ⏱️ 30-Second Revision
> `result=0`. XOR all elements. Pairs cancel, single remains. O(N)/O(1).
