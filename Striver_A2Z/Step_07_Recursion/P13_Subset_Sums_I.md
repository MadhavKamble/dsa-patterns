# Subset Sums I

> **GFG** · **Difficulty:** Easy · **Step 7 — Recursion · P13**

---

## 🧠 Problem Understanding

**What is it asking?**
Given an array, find the sum of all possible subsets. Return the list of sums in sorted order.

**Input:** `arr = [5,2,1]`
**Output:** `[0,1,2,3,5,6,7,8]`

**Key Observations:**
- 2^n subsets for an array of size n → 2^3 = 8 sums here.
- Same include/exclude tree as P08–P10, but instead of tracking the subset itself, we track the **running sum**.
- No actual subset stored — only the cumulative sum passed down as a parameter.
- Sort the result at the end.

---

## 🥇 Include/Exclude Recursion (Parameterized)

### Key Insight

> 💡 Standard include/exclude but carry `currentSum` as a parameter instead of a `ds` vector. At the base case (all elements processed), push `currentSum` to results. No backtracking needed — sum is passed by value, not modified in-place.

### vs P08 (Power Set)

```
P08 (Power Set — tracks subset):
  helper(idx, curr[]):
    base: push curr[]
    include: push arr[idx], recurse(idx+1), pop_back   ← backtrack on vector
    exclude: recurse(idx+1)

P13 (Subset Sums — tracks sum):
  findSums(idx, currentSum):
    base: push currentSum
    include: recurse(idx+1, currentSum + arr[idx])     ← no backtrack needed (int param)
    exclude: recurse(idx+1, currentSum)
```

No `pop_back` needed here because `currentSum` is passed by value — each recursive call gets its own copy of the integer.

### Algorithm
1. **Base:** `index == n` → push `currentSum`, return.
2. **Include:** `findSums(index+1, currentSum+arr[index], ...)`.
3. **Exclude:** `findSums(index+1, currentSum, ...)`.
4. Sort the result.

### C++ Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void findSums(int index,int currentSum,vector<int>& arr,vector<int>& sums){
        if(index==(int)arr.size()){
            sums.push_back(currentSum);
            return;
        }
        findSums(index+1,currentSum+arr[index],arr,sums);
        findSums(index+1,currentSum,arr,sums);
    }

    vector<int> subsetSums(vector<int>& arr){
        vector<int> sums;
        findSums(0,0,arr,sums);
        sort(sums.begin(),sums.end());
        return sums;
    }
};
```

**Time:** O(2^N + 2^N log 2^N) = O(2^N × N) · **Space:** O(N) recursion depth

### Dry Run — `arr=[5,2,1]`

```
findSums(0, 0)
├── include 5 → findSums(1, 5)
│   ├── include 2 → findSums(2, 7)
│   │   ├── include 1 → findSums(3, 8) → push 8
│   │   └── exclude 1 → findSums(3, 7) → push 7
│   └── exclude 2 → findSums(2, 5)
│       ├── include 1 → findSums(3, 6) → push 6
│       └── exclude 1 → findSums(3, 5) → push 5
└── exclude 5 → findSums(1, 0)
    ├── include 2 → findSums(2, 2)
    │   ├── include 1 → findSums(3, 3) → push 3
    │   └── exclude 1 → findSums(3, 2) → push 2
    └── exclude 2 → findSums(2, 0)
        ├── include 1 → findSums(3, 1) → push 1
        └── exclude 1 → findSums(3, 0) → push 0
```

Before sort: `[8,7,6,5,3,2,1,0]`
After sort: `[0,1,2,3,5,6,7,8]` ✓

---

## 🧾 Recall Line *(10-Second Revision)*

> "Include/exclude but carry sum as int param (no backtrack needed). Base: push sum. Sort result at end. O(2^N × N)."

---

## 📝 Short Revision Notes

- Passing `currentSum` as an int (by value) means no cleanup/backtracking — each call has its own copy.
- If you instead used `int& currentSum`, you'd need `currentSum += arr[idx]` before and `currentSum -= arr[idx]` after — same extra work as vector pop_back.
- Always generates exactly 2^n sums — one per leaf of the recursion tree.

---

## ⚠️ Common Mistakes

❌ Forgetting to sort the result — problem asks for sorted order.
❌ Pushing `currentSum` inside the loop/condition instead of strictly at the base — duplicates or misses values.
❌ Thinking backtracking is needed — it's not, because the sum is passed by value.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "all subset sums" → **include/exclude with integer param**, push at base, sort result.

---

## 🏆 Pattern Category

`Recursion` · `Subsets` · `Include/Exclude`

---

## ⏱️ 30-Second Last-Minute Revision

> Include: `recurse(idx+1, sum+arr[idx])`. Exclude: `recurse(idx+1, sum)`. Base: `idx==n → push sum`. Sort result. No backtrack — int param is by value. **Time:** O(2^N × N).
