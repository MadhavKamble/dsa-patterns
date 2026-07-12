# Combination Sum I

> **LeetCode #39** · **Difficulty:** Medium · **Step 7 — Recursion · P11**

---

## 🧠 Problem Understanding

**What is it asking?**
Given an array of distinct integers and a target, find all unique combinations where the chosen numbers sum to target. Each number may be used **unlimited times**.

**Input:** `candidates = [2,3,6,7], target = 7`
**Output:** `[[2,2,3],[7]]`

**Key Observations:**
- Each element can be reused → when we "include" an element, we stay at the **same index** instead of advancing.
- We never go back (only move forward or stay) → no duplicate combinations.
- Pruning: only attempt to include `arr[idx]` if `arr[idx] <= target` — if it already exceeds the remaining target, adding it is pointless.
- No explicit `visited` array needed — the forward-only movement guarantees uniqueness.

---

## 🥇 Recursive Include/Stay-or-Skip

### Key Insight

> 💡 The single change from P08/P09 (basic include/exclude): the "include" branch recurses with the **same `idx`** (not `idx+1`). This allows unlimited reuse of the same element. The "exclude" branch advances `idx+1` as usual.

### P08/P09 vs P11 — The One Difference

```
Standard include/exclude (P08, P09):
  include: recurse(idx+1, sum - arr[idx])    ← advance index
  exclude: recurse(idx+1, sum)

Combination Sum I (P11):
  include: recurse(idx, sum - arr[idx])      ← STAY at same index (reuse allowed)
  exclude: recurse(idx+1, sum)               ← advance to skip this element entirely
```

### Algorithm
1. **Base:** `idx == n` → if `target == 0`, push `ds` to `ans`; return.
2. **Include:** if `arr[idx] <= target` → push `arr[idx]`, recurse `(idx, target-arr[idx])`, pop back.
3. **Exclude:** recurse `(idx+1, target)`.

### C++ Code

```cpp
class Solution {
public:
    void findCombination(int idx,int target,vector<int>& arr,vector<vector<int>>& ans,vector<int>& ds){
        if(idx==arr.size()){
            if(target==0) ans.push_back(ds);
            return;
        }
        if(arr[idx]<=target){
            ds.push_back(arr[idx]);
            findCombination(idx,target-arr[idx],arr,ans,ds);
            ds.pop_back();
        }
        findCombination(idx+1,target,arr,ans,ds);
    }

    vector<vector<int>> combinationSum(vector<int>& candidates,int target){
        vector<vector<int>> ans;
        vector<int> ds;
        findCombination(0,target,candidates,ans,ds);
        return ans;
    }
};
```

**Time:** O(k × 2^t) where t = target/min(candidate), k = avg combination length
**Space:** O(target/min(candidate)) — max recursion depth

### Dry Run — `candidates=[2,3,6,7], target=7`

```
findCombination(0, 7, ds=[])
├── include 2 → findCombination(0, 5, ds=[2])
│   ├── include 2 → findCombination(0, 3, ds=[2,2])
│   │   ├── include 2 → findCombination(0, 1, ds=[2,2,2])
│   │   │   └── 2>1: skip include. exclude→(1,1)→(2,1)→(3,1)→(4,1): idx=n, 1≠0 return
│   │   └── exclude 2 → findCombination(1, 3, ds=[2,2])
│   │       ├── include 3 → findCombination(1, 0, ds=[2,2,3])
│   │       │   └── 3>0: skip. (2,0)→(3,0)→(4,0): idx=n, target=0 → ✓ push [2,2,3]
│   │       └── exclude 3 → findCombination(2,3,...) 6>3 skip; (3,3) 7>3 skip; (4,3) not 0
│   └── exclude 2 → findCombination(1, 5, ds=[2]) ... (no valid combo found)
└── exclude 2 → findCombination(1, 7, ds=[])
    ├── include 3 → findCombination(1, 4, ds=[3]) ... (no valid)
    ├── skip 3 → findCombination(2, 7, ds=[])
    │   ├── include 6 → (2,1,...) → fails
    │   └── skip 6 → findCombination(3, 7, ds=[])
    │       ├── include 7 → findCombination(3, 0, ds=[7])
    │       │   └── 7>0: skip. (4,0): idx=n, target=0 → ✓ push [7]
    │       └── skip 7 → (4,7): not 0 → return
```

**Output:** `[[2,2,3],[7]]` ✓

---

## 🔄 Alternative — Forward-only with `idx+1` in Include

Some implementations advance the index in the include branch and call the function differently:

```cpp
void solve(int idx,int target,vector<int>& arr,vector<vector<int>>& ans,vector<int>& curr){
    if(target==0){ ans.push_back(curr); return; }
    for(int i=idx;i<arr.size();i++){
        if(arr[i]>target) break;    // works only if candidates are sorted
        curr.push_back(arr[i]);
        solve(i,target-arr[i],arr,ans,curr);  // i not i+1: allows reuse
        curr.pop_back();
    }
}
```

Equivalent logic — loop-based. Requires sorting candidates to use `break` as pruning. User's two-branch recursion is cleaner and doesn't require sorting.

---

## 🔁 Combination Sum Family

| Problem | Reuse same element? | Duplicates in input? | Key difference |
|---|---|---|---|
| **P11 — Sum I** (LC 39) | ✅ yes | ❌ no | include → stay at `idx` |
| P12 — Sum II (LC 40) | ❌ no | ✅ yes | include → advance `idx+1`, skip duplicates |

---

## 🧾 Recall Line *(10-Second Revision)*

> "Include → stay at `idx` (reuse). Exclude → advance `idx+1`. Prune: only include if `arr[idx] <= target`. Base: `idx==n && target==0` → push."

---

## 📝 Short Revision Notes

- The only structural difference from basic include/exclude (P09): `idx` vs `idx+1` in the include branch.
- The pruning `if(arr[idx] <= target)` avoids negative target recursion — equivalent to `sum < 0` base case in P09.
- No sorting needed (unlike the loop-based alternative) — the two-branch form works regardless of order.
- `ds` passed by reference + `pop_back()` = backtracking. No extra memory per call.

---

## ⚠️ Common Mistakes

❌ Using `idx+1` in the include branch — prevents reuse, gives wrong answer.
❌ Missing the `arr[idx] <= target` guard — infinite recursion on positive elements (stays at same idx forever with target < 0).
❌ Pushing to `ans` inside the pruning condition — misses the case where target reaches 0 before the index reaches n (base case handles this).

---

## 🧠 Pattern Recognition Trigger

**When I see:** "combinations with repetition", "unlimited use of elements" → **include/exclude with `idx` (not `idx+1`) in the include branch**.

---

## 🏆 Pattern Category

`Recursion` · `Backtracking` · `Combination Sum` · `Unbounded`

---

## ⏱️ 30-Second Last-Minute Revision

> Include: `arr[idx]<=target → push, recurse(idx, target-arr[idx]), pop`. Exclude: `recurse(idx+1, target)`. Base: `idx==n → push if target==0`. Key: include stays at `idx` for reuse. **Time:** O(k × 2^t).
