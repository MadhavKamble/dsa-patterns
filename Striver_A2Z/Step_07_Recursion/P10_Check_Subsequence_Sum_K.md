# Check if Subsequence with Sum K Exists

> **GFG / Striver** · **Difficulty:** Easy · **Step 7 — Recursion · P10**

---

## 🧠 Problem Understanding

**What is it asking?**
Given an array and a target, return `true` if any subsequence sums to exactly the target.

**Input:** `nums = [1,2,3,4], target = 5` → **Output:** `true` (e.g. `{1,4}` or `{2,3}`)

**Key Observations:**
- Same include/exclude tree as P09 — just change what you return and how you combine.
- As soon as one valid subsequence is found, return `true` immediately (short-circuit).
- Use `||` not `|` — `||` short-circuits, `|` evaluates both branches always.

---

## 🥇 Include/Exclude Recursion

### Key Insight

> 💡 Identical structure to counting (P09). Only difference: base case returns `true/false`, and branches combine with `||` (short-circuit) instead of `+`.

### Base Case Difference from P09

```cpp
// P09 Count version
if (sum == 0) return 1;
if (sum < 0 || ind == n) return 0;

// P10 Check version (user's code)
if (ind == n) return sum == 0;
// ↑ Combines both checks into one line — correct but slightly less efficient
//   (doesn't prune sum < 0 early for positive arrays)
```

The user's code merges the two base cases: when `ind == n`, return whether `sum == 0`. This is correct but misses the `sum < 0` pruning that P09 uses. For positive arrays, adding the `sum < 0` early exit would prune faster.

### `|` vs `||` — Critical Difference

```cpp
// User's code uses bitwise OR — both branches always run:
return func(ind+1, sum-nums[ind], nums) | func(ind+1, sum, nums);

// Better: logical OR — stops as soon as first true is found:
return func(ind+1, sum-nums[ind], nums) || func(ind+1, sum, nums);
```

For a boolean check, `||` is correct and faster. `|` gives the same answer (true|false = true) but wastes time computing the second branch even after the first returns true.

### C++ Code (User's + Optimized Note)

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    bool func(int ind,int sum,vector<int>& nums){
        if(ind==(int)nums.size()) return sum==0;
        return func(ind+1,sum-nums[ind],nums) || func(ind+1,sum,nums);
    }

public:
    bool checkSubsequenceSum(vector<int>& nums,int target){
        return func(0,target,nums);
    }
};

int main(){
    Solution sol;
    vector<int> nums={1,2,3,4};
    int target=5;
    cout<<sol.checkSubsequenceSum(nums,target)<<endl;
    return 0;
}
```

**Time:** O(2^N) worst case, but `||` short-circuits on first found · **Space:** O(N)

### With Positive-Array Pruning (Stronger Version)

```cpp
bool func(int ind,int sum,vector<int>& nums){
    if(sum==0) return true;
    if(sum<0 || ind==(int)nums.size()) return false;
    return func(ind+1,sum-nums[ind],nums) || func(ind+1,sum,nums);
}
```

---

## 🔁 The Three-Problem Progression (P08→P09→P10)

```
             Include/Exclude Tree
                   /          \
           include s[i]    exclude s[i]

P08 (Print all):    collect into result[]       (void, gather)
P09 (Count K):      return 1/0, combine with +  (int)
P10 (Check K):      return T/F, combine with || (bool, short-circuit)
```

**Key rule:**
- Count → combine with `+`
- Check → combine with `||` (short-circuit)
- Print → don't combine, just collect at base

---

## 🧾 Recall Line *(10-Second Revision)*

> "Same include/exclude tree as count, but return bool and combine with `||` not `+`. Base: `ind==n → sum==0`. Add `sum<0` early exit for positive arrays."

---

## 📝 Short Revision Notes

- `|` vs `||`: always use `||` for boolean existence checks — short-circuit is free optimization.
- The user's single base case `if(ind == n) return sum == 0` is elegant but misses positive-array pruning.
- This pattern extends to: "does any path in a tree satisfy property X" → always `||` combinations.

---

## ⚠️ Common Mistakes

❌ Using `|` instead of `||` — no short-circuit, explores full tree even after finding answer.
❌ Forgetting `sum < 0` pruning for positive arrays — doesn't affect correctness but doubles work.
❌ Returning `sum <= 0` instead of `sum == 0` at base — returns true for overshoot.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "does any subsequence/path satisfy X" → **include/exclude + `||` combination**, return bool at base.

---

## 🏆 Pattern Category

`Recursion` · `Backtracking` · `Subsequences` · `Existence Check`

---

## ⏱️ 30-Second Last-Minute Revision

> Base: `ind==n → sum==0`. Combine with `||` (not `|`). Optional: `sum==0→true`, `sum<0→false` for early exit. **Time:** O(2^N) worst / faster with short-circuit | **Space:** O(N).
