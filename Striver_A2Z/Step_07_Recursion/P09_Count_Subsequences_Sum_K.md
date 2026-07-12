# Count all Subsequences with Sum K

> **GFG / Striver** · **Difficulty:** Medium · **Step 7 — Recursion · P09**

---

## 🧠 Problem Understanding

**What is it asking?**
Given an array of positive integers and a target `k`, count how many subsequences have elements summing to exactly `k`.

**Input:** `nums = [1,2,3,4,5], target = 5`
**Output:** `3` → `{1,4}`, `{2,3}`, `{5}`

**Key Observations:**
- Same include/exclude tree as P08 (Power Set), but instead of collecting strings we count paths that hit sum=0.
- Since all elements are positive, if `sum < 0` we can prune — no future element can bring it back.
- Check `sum == 0` **before** `ind == nums.size()` — this acts as an early-exit optimization for positive arrays (remaining elements would only increase sum).

---

## 🥇 Include/Exclude Recursion

### Key Insight

> 💡 Same tree as generating all subsequences. The only difference: at the base case, return `1` if sum reached exactly 0, else `0`. Accumulate counts with `+` on the way back up.

### Base Case Order Matters

```
if sum == 0  → return 1   ← check this FIRST (early exit for positive arrays)
if sum < 0   → return 0   ← overshot, prune this branch
if ind == n  → return 0   ← ran out of elements without hitting 0
```

Why check `sum == 0` before index check? For positive arrays, if sum is already 0 at some index `i < n`, every remaining element can only increase the sum — so including any of them would overshoot. The only valid continuation is "exclude all remaining" which is 1 path. Returning 1 immediately skips 2^(n-i) redundant recursive calls.

### Algorithm
1. **Base:** `sum == 0` → return 1. `sum < 0 || ind == n` → return 0.
2. **Include:** recurse with `(ind+1, sum - nums[ind])`.
3. **Exclude:** recurse with `(ind+1, sum)`.
4. Return `include_count + exclude_count`.

### C++ Code

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    int func(int ind,int sum,vector<int>& nums){
        if(sum==0) return 1;
        if(sum<0 || ind==(int)nums.size()) return 0;
        return func(ind+1,sum-nums[ind],nums)+func(ind+1,sum,nums);
    }

public:
    int countSubsequenceWithTargetSum(vector<int>& nums,int target){
        return func(0,target,nums);
    }
};

int main(){
    Solution sol;
    vector<int> nums={1,2,3,4,5};
    int target=5;
    cout<<sol.countSubsequenceWithTargetSum(nums,target)<<endl;
    return 0;
}
```

**Time:** O(2^N) · **Space:** O(N) — recursion depth

### Dry Run — `nums=[1,2,3], target=3`

```
func(0, 3)
├── include 1 → func(1, 2)
│   ├── include 2 → func(2, 0) → sum=0 ✓ return 1
│   └── exclude 2 → func(2, 2)
│       ├── include 3 → func(3, -1) → sum<0 return 0
│       └── exclude 3 → func(3, 2) → ind=3=size return 0
│       → 0
│   → 1 + 0 = 1
└── exclude 1 → func(1, 3)
    ├── include 2 → func(2, 1)
    │   ├── include 3 → func(3, -2) → return 0
    │   └── exclude 3 → func(3, 1) → return 0
    │   → 0
    └── exclude 2 → func(2, 3)
        ├── include 3 → func(3, 0) → sum=0 ✓ return 1
        └── exclude 3 → func(3, 3) → return 0
        → 1
    → 0 + 1 = 1
→ 1 + 1 = 2
```

Subsequences: `{1,2}` and `{3}` → count = 2 ✓

---

## 🔁 Progression: Print → Count → Check

| Goal | Return type | Base case on sum=0 | Combines with |
|---|---|---|---|
| Print all (P08) | void | collect into result | — |
| **Count (P09)** | int | return 1 | `+` |
| Check exists (P10) | bool | return true | `\|\|` |

The tree structure is identical — only the base case value and combination operator change.

---

## 🧾 Recall Line *(10-Second Revision)*

> "Include/exclude tree. Base: `sum==0 → 1`, `sum<0 || ind==n → 0`. Return include + exclude. `sum==0` checked first for positive-array pruning."

---

## 📝 Short Revision Notes

- For arrays with negative numbers or zeros: remove `sum < 0` pruning and only use `ind == n` as the base — `sum == 0` early exit would also be wrong (more elements could cancel).
- `sum == 0` before `ind == n` — order is intentional and matters for efficiency.
- The recursion explores 2^N paths in the worst case, one for each subsequence.

---

## ⚠️ Common Mistakes

❌ Putting `ind == n` check before `sum == 0` — misses the early exit optimization.
❌ Using `sum <= 0` instead of `sum == 0` for the success base case — counts overshoot cases.
❌ Applying positive-array pruning (`sum < 0`) to arrays that can contain negative numbers.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "count subsequences/subsets with property" → **include/exclude recursion, return 1 at success, 0 at failure, combine with `+`**.

---

## 🏆 Pattern Category

`Recursion` · `Backtracking` · `Subsequences` · `Count Pattern`

---

## ⏱️ 30-Second Last-Minute Revision

> Include/exclude tree. Base: `sum==0→1`, `sum<0||end→0`. Return `include+exclude`. Check sum==0 first for early exit. **Time:** O(2^N) | **Space:** O(N).
