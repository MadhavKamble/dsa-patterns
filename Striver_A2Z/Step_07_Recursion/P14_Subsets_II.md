# Subsets II

> **LeetCode #90** · **Difficulty:** Medium · **Step 7 — Recursion · P14**

---

## 🧠 Problem Understanding

**What is it asking?**
Given an integer array (may have duplicates), return all possible unique subsets (power set). No duplicate subsets in output.

**Input:** `nums = [1,2,2]`
**Output:** `[[],[1],[1,2],[1,2,2],[2],[2,2]]`

**Key Observations:**
- Same duplicate-skip logic as Combination Sum II (P12): sort + `i > idx && nums[i] == nums[i-1]`.
- Key structural difference from P12: push `current` at the **start of every call**, not just at base — this collects every prefix as a valid subset.
- No target, no size limit — all subset sizes from 0 to n are valid.

---

## 🥇 Recursive Backtracking with Loop

### Key Insight

> 💡 Push `current` to result **immediately on entry** — this captures subsets of all sizes including empty. Then loop forward from `idx`, skip duplicates at the same level, recurse with `i+1`.

### vs LC 78 Subsets (no duplicates)

```
LC 78 (no duplicates):
  backtrack(idx):
    push current          ← collect every partial set
    for i = idx to n-1:
      push nums[i]
      backtrack(i+1)
      pop

LC 90 Subsets II (with duplicates):
  backtrack(idx):
    push current          ← same
    for i = idx to n-1:
      if i>idx && nums[i]==nums[i-1]: continue   ← duplicate guard added
      push nums[i]
      backtrack(i+1)
      pop
```

The only difference from LC 78 is the one `continue` line for duplicate skipping.

### vs Combination Sum II (P12)

| | P12 Combination Sum II | P14 Subsets II |
|---|---|---|
| Collect at | base case (`target==0`) | **every entry** |
| Has target | ✅ yes | ❌ no |
| Has size limit | ❌ no | ❌ no |
| Dup skip | `i>idx && arr[i]==arr[i-1]` | same |

Same loop + dup-skip skeleton, different collection point.

### Algorithm
1. Sort `nums`.
2. `backtrack(idx)`:
   - Push `current` to `result` (captures current subset).
   - Loop `i` from `idx` to `n-1`:
     - Skip: `if(i > idx && nums[i] == nums[i-1]) continue`.
     - Push `nums[i]`, recurse `(i+1)`, pop.

### C++ Code

```cpp
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums){
        sort(nums.begin(),nums.end());
        vector<vector<int>> result;
        vector<int> curr;
        backtrack(0,nums,curr,result);
        return result;
    }

    void backtrack(int idx,vector<int>& nums,vector<int>& current,vector<vector<int>>& result){
        result.push_back(current);
        for(int i=idx;i<nums.size();i++){
            if(i>idx && nums[i]==nums[i-1]) continue;
            current.push_back(nums[i]);
            backtrack(i+1,nums,current,result);
            current.pop_back();
        }
    }
};
```

**Time:** O(2^N × N) · **Space:** O(N) recursion depth

### Dry Run — `nums=[1,2,2]`

After sort: `[1,2,2]`

```
backtrack(0, curr=[])
  push [] ✓
  i=0: nums[0]=1, push 1, backtrack(1, curr=[1])
    push [1] ✓
    i=1: nums[1]=2, push 2, backtrack(2, curr=[1,2])
      push [1,2] ✓
      i=2: nums[2]=2, i=2>idx=2? No (2>2 false) → try it
            push 2, backtrack(3, curr=[1,2,2])
              push [1,2,2] ✓
              loop: i=3, 3>=3=n → done
            pop 2
      i=3: done
    pop 2
    i=2: nums[2]=2 == nums[1]=2, i=2>idx=1 → SKIP
  pop 1
  i=1: nums[1]=2, push 2, backtrack(2, curr=[2])
    push [2] ✓
    i=2: nums[2]=2, i=2>idx=2? No → try it
          push 2, backtrack(3, curr=[2,2])
            push [2,2] ✓
            loop done
          pop 2
  pop 2
  i=2: nums[2]=2 == nums[1]=2, i=2>idx=0 → SKIP
```

**Output:** `[[],[1],[1,2],[1,2,2],[2],[2,2]]` ✓ (6 subsets)

---

## 🧾 Recall Line *(10-Second Revision)*

> "Sort. Push `current` on entry (captures every subset). Loop i=idx→n, skip `i>idx && nums[i]==nums[i-1]`, recurse `i+1`, pop. No target/size limit."

---

## 📝 Short Revision Notes

- "Push on entry" vs "push at base": collecting at entry captures ALL subsets (including empty and partial). Collecting at base would only capture complete/full subsets.
- The empty subset `[]` is collected at the very first call before any element is added.
- `i > idx` (not `i > 0`) — same reasoning as P12: allow same-value elements at deeper levels.

---

## ⚠️ Common Mistakes

❌ Collecting at the end / in a base case — misses all intermediate subsets.
❌ `i > 0` instead of `i > idx` — wrongly blocks elements at deeper recursion levels.
❌ Forgetting to sort — duplicate detection `nums[i]==nums[i-1]` only works on sorted input.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "all unique subsets with duplicates" → **sort + push-on-entry + loop + `i>idx` dup skip + recurse `i+1`**.

---

## 🏆 Pattern Category

`Recursion` · `Backtracking` · `Subsets` · `Duplicate Handling`

---

## ⏱️ 30-Second Last-Minute Revision

> Sort. Push `current` immediately on entry. Loop i=idx→n: skip `i>idx&&nums[i]==nums[i-1]`, push, `recurse(i+1)`, pop. **Time:** O(2^N × N).
