# Combination Sum III

> **LeetCode #216** · **Difficulty:** Medium · **Step 7 — Recursion · P15**

---

## 🧠 Problem Understanding

**What is it asking?**
Find all combinations of exactly `k` distinct digits from 1–9 that sum to `n`. Each digit used at most once.

**Input:** `k=3, n=7` → **Output:** `[[1,2,4]]`
**Input:** `k=3, n=9` → **Output:** `[[1,2,6],[1,3,5],[2,3,4]]`

**Key Observations:**
- Fixed pool: digits 1–9 only (distinct, no repetition).
- Two simultaneous constraints: exactly `k` numbers AND sum exactly `n`.
- Because pool is sorted (1→9), `break` works as a prune.
- No duplicate handling needed — pool is already distinct.

---

## 🥇 Recursive Backtracking

### Key Insight

> 💡 Loop from `start` to 9. For each digit `i ≤ target`, include it, recurse with `(i+1, k, target-i)`. Two base conditions: success = `size==k && target==0`; failure = `size>k || target<0`.

### Double Constraint Base Case

```cpp
if(ds.size()==k && target==0) { ans.push_back(ds); return; }  // SUCCESS
if(ds.size()>k  || target<0)  { return; }                     // FAILURE (prune)
```

Both conditions must be met simultaneously. Checking failure early prevents:
- Over-picking: `size > k` (already have enough numbers, stop).
- Over-spending: `target < 0` (already exceeded sum, stop).

### vs Combination Sum I & II

| | Sum I (P11) | Sum II (P12) | **Sum III (P15)** |
|---|---|---|---|
| Pool | candidates[] | candidates[] | digits 1–9 |
| Reuse | ✅ yes | ❌ no | ❌ no |
| Duplicates | ❌ no | ✅ yes | ❌ no |
| Size constraint | none | none | **exactly k** |
| Loop | idx to n-1 | idx to n-1 | start to 9 |
| Dup skip | no | `i>idx&&arr[i]==arr[i-1]` | not needed |

### Algorithm
1. **Base success:** `ds.size() == k && target == 0` → push, return.
2. **Base failure:** `ds.size() > k || target < 0` → return.
3. Loop `i = start` to `9`:
   - Prune: `if(i > target) break`.
   - Push `i`, recurse `(i+1, k, target-i)`, pop.

### C++ Code

```cpp
class Solution {
public:
    vector<vector<int>> combinationSum3(int k,int n){
        vector<vector<int>> ans;
        vector<int> curr;
        backtrack(1,k,n,curr,ans);
        return ans;
    }

    void backtrack(int start,int k,int target,vector<int>& ds,vector<vector<int>>& ans){
        if(ds.size()==k && target==0){
            ans.push_back(ds);
            return;
        }
        if(ds.size()>k || target<0) return;
        for(int i=start;i<=9;i++){
            if(i<=target){
                ds.push_back(i);
                backtrack(i+1,k,target-i,ds,ans);
                ds.pop_back();
            }else{
                break;
            }
        }
    }
};
```

**Time:** O(C(9,k) × k) — at most C(9,k) valid combinations · **Space:** O(k) recursion depth

### Dry Run — `k=3, n=7`

```
backtrack(1, 3, 7, [])
├── i=1: push 1, backtrack(2, 3, 6, [1])
│   ├── i=2: push 2, backtrack(3, 3, 4, [1,2])
│   │   ├── i=3: push 3, backtrack(4, 3, 1, [1,2,3])
│   │   │   └── i=4: 4>1 → break
│   │   │   ← size=3, target=1≠0 → return (not pushed)
│   │   ├── i=4: push 4, backtrack(5, 3, 0, [1,2,4])
│   │   │   └── size=3, target=0 → ✓ push [1,2,4]
│   │   ├── i=5: push 5, backtrack(6, 3, -1, [1,2,5])
│   │   │   └── target<0 → return
│   │   └── i=6: 6>4 → break
│   ├── i=3: push 3, backtrack(4, 3, 3, [1,3])
│   │   ├── i=4: 4>3 → break
│   │   ← size=2, loop done, returns
│   └── ...
└── ...
```

**Output:** `[[1,2,4]]` ✓

### Dry Run — `k=3, n=9`

Combinations found: `{1,2,6}` (1+2+6=9), `{1,3,5}` (1+3+5=9), `{2,3,4}` (2+3+4=9) ✓

---

## 🧾 Recall Line *(10-Second Revision)*

> "Loop 1→9. Include `i` if `i<=target`. Base success: `size==k && target==0`. Base fail: `size>k || target<0`. Recurse `i+1`. No dup handling — pool is distinct."

---

## 📝 Short Revision Notes

- `i<=target` as loop guard (with `break` on else) achieves the same pruning as the failure base case `target<0` — but the `target<0` base case is still needed for correctness since we enter the recursive call before checking.
- Start from `1`, loop to `9` — the fixed pool makes no sorting or dup-skip needed.
- `ds.size() > k` prune prevents wasting time when we've already over-picked.

---

## ⚠️ Common Mistakes

❌ Looping `i` up to `n` instead of `9` — pool is fixed 1–9.
❌ Using `i+1` as next start but forgetting `start` is passed to avoid reuse.
❌ Missing the `ds.size() > k` prune — explores dead branches needlessly.
❌ Combining both base cases into one — hard to read and error-prone.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "exactly k distinct numbers from 1–9 summing to n" → **loop 1→9, double constraint base case (size==k && target==0)**.

---

## 🏆 Pattern Category

`Recursion` · `Backtracking` · `Combination Sum` · `Fixed Pool`

---

## ⏱️ 30-Second Last-Minute Revision

> Loop `i` from `start` to 9. Prune `i>target → break`. Success: `size==k && target==0`. Fail: `size>k || target<0`. Recurse `(i+1, k, target-i)`. **Time:** O(C(9,k)×k).
