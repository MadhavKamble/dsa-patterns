# Combination Sum II

> **LeetCode #40** · **Difficulty:** Medium · **Step 7 — Recursion · P12**

---

## 🧠 Problem Understanding

**What is it asking?**
Given a collection of integers (may have duplicates) and a target, find all unique combinations that sum to target. Each number may only be used **once**.

**Input:** `candidates = [10,1,2,7,6,1,5], target = 8`
**Output:** `[[1,1,6],[1,2,5],[1,7],[2,6]]`

**Key Observations:**
- Input can have duplicates → must avoid duplicate combinations in output.
- Each element used at most once → advance `i+1` in recursive call (unlike Sum I which stayed at `idx`).
- Sort first → enables both duplicate-skipping and early `break` pruning.
- Duplicate skipping: at the **same recursion level**, if `arr[i] == arr[i-1]` and `i > idx`, skip — we've already explored this value at this level.

---

## 🥇 Recursive with Loop + Duplicate Skip

### Key Insight

> 💡 Sort the array. Then loop from `idx` to end. The critical guard: `if(i > idx && arr[i] == arr[i-1]) continue` — this prevents trying the same value **at the same level** more than once. At a deeper level, the same value can be tried again (it's a different slot).

### Why `i > idx` and Not `i > 0`?

```
candidates = [1,1,2], target = 3

Level 0 (idx=0): loop i=0,1,2
  i=0: arr[0]=1, try it → recurse with [1] from idx=1
  i=1: arr[1]=1 == arr[0]=1, and i=1 > idx=0 → SKIP
        (already explored "starting with 1" at this level)
  i=2: arr[2]=2, try it → recurse with [2] from idx=3 → not sum to 3

Level 1 (idx=1, already included arr[0]=1): loop i=1,2
  i=1: arr[1]=1, i=1 == idx=1 → NOT skipped (first time at this level)
       try 1 → ds=[1,1], recurse with idx=2, target=1
  i=2: arr[2]=2, i=2>idx=1, arr[2]=2 ≠ arr[1]=1 → try 2 → ds=[1,2], target=0 → push [1,2]
```

So `i > idx` ensures we only skip **repeated** picks at the **same level**, not across levels.

### P11 vs P12 — Side-by-Side

```
Combination Sum I (unbounded, no duplicates in input):
  findCombination(idx, ...)
    if arr[idx] <= target:
      include: recurse(idx, target-arr[idx])    ← stay at idx
    exclude:   recurse(idx+1, target)

Combination Sum II (each once, duplicates in input):
  findCombination(idx, ...)
    for i = idx to n-1:
      if i>idx && arr[i]==arr[i-1]: continue   ← skip dup at same level
      if arr[i] > target: break                ← sorted → safe to exit
      include: recurse(i+1, target-arr[i])     ← advance i+1 (no reuse)
      (backtrack)
```

### Algorithm
1. Sort `candidates`.
2. **Base:** `target == 0` → push `ds`, return.
3. Loop `i` from `idx` to `n-1`:
   - Skip: `if(i > idx && arr[i] == arr[i-1]) continue`.
   - Prune: `if(arr[i] > target) break`.
   - Include: push `arr[i]`, recurse `(i+1, target-arr[i])`, pop.

### C++ Code

```cpp
class Solution {
public:
    void findCombination(int idx,int target,vector<int>& arr,vector<vector<int>>& ans,vector<int>& ds){
        if(target==0){
            ans.push_back(ds);
            return;
        }
        for(int i=idx;i<arr.size();i++){
            if(i>idx && arr[i]==arr[i-1]) continue;
            if(arr[i]>target) break;
            ds.push_back(arr[i]);
            findCombination(i+1,target-arr[i],arr,ans,ds);
            ds.pop_back();
        }
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates,int target){
        sort(candidates.begin(),candidates.end());
        vector<vector<int>> ans;
        vector<int> ds;
        findCombination(0,target,candidates,ans,ds);
        return ans;
    }
};
```

**Time:** O(2^N) worst case · **Space:** O(N) recursion depth

### Dry Run — `candidates=[1,1,2,5,6,7,10], target=8`

After sort: `[1,1,2,5,6,7,10]`

```
findCombination(0, 8, [])
├── i=0: arr[0]=1, push 1, recurse(1, 7, [1])
│   ├── i=1: arr[1]=1, push 1, recurse(2, 6, [1,1])
│   │   ├── i=2: arr[2]=2, push 2, recurse(3, 4, [1,1,2])
│   │   │   └── i=3: 5>4 → break
│   │   ├── i=3: arr[3]=5, push 5, recurse(4, 1, [1,1,5])
│   │   │   └── 6>1 → break
│   │   └── i=4: arr[4]=6 → push, recurse(5,0,[1,1,6]) → target=0 ✓ push [1,1,6]
│   ├── i=2: arr[2]=2, push 2, recurse(3, 5, [1,2])
│   │   ├── i=3: arr[3]=5, recurse(4,0,[1,2,5]) → ✓ push [1,2,5]
│   │   └── i=4: 6>5 → break
│   ├── i=3: arr[3]=5, push 5, recurse(4,2,[1,5]) → 6>2 break
│   ├── i=4: arr[4]=6, recurse(5,1,[1,6]) → 7>1 break
│   └── i=5: arr[5]=7, recurse(6,0,[1,7]) → ✓ push [1,7]
├── i=1: arr[1]=1 == arr[0]=1, i=1>idx=0 → SKIP
├── i=2: arr[2]=2, push 2, recurse(3, 6, [2])
│   ├── i=3: 5 ≤ 6, recurse(4,1,[2,5]) → break
│   └── i=4: arr[4]=6, recurse(5,0,[2,6]) → ✓ push [2,6]
├── i=3: arr[3]=5, recurse(4,3,[5]) → 6>3 break
├── i=4: arr[4]=6, recurse(5,2,[6]) → 7>2 break
├── i=5: arr[5]=7, recurse(6,1,[7]) → 10>1 break
└── i=6: arr[6]=10 > 8 → break
```

**Output:** `[[1,1,6],[1,2,5],[1,7],[2,6]]` ✓

---

## 🔁 Combination Sum Family — Full Comparison

| | Sum I (LC 39) | Sum II (LC 40) |
|---|---|---|
| Input | distinct | may have duplicates |
| Reuse element | ✅ unlimited | ❌ once only |
| Recurse with | `idx` (same) | `i+1` (next) |
| Dup skipping | not needed | `i>idx && arr[i]==arr[i-1]` |
| Sort required | no | ✅ yes (for dup skip + break) |
| Base check | `idx==n && target==0` | `target==0` (before loop) |

---

## 🧾 Recall Line *(10-Second Revision)*

> "Sort. Loop i=idx to n. Skip: `i>idx && arr[i]==arr[i-1]`. Break: `arr[i]>target`. Recurse with `i+1` (no reuse). Base: `target==0` → push."

---

## 📝 Short Revision Notes

- The dup-skip condition `i > idx` is the trickiest part — it blocks same-value reuse at the **same level** but allows it at **deeper levels** (when recursion starts fresh from a new `idx`).
- Sorting is mandatory: without it, `arr[i] == arr[i-1]` check doesn't catch all duplicates, and `break` on `arr[i] > target` is unsafe.
- `break` (not `continue`) when `arr[i] > target` — sorted means all subsequent elements are also too large.

---

## ⚠️ Common Mistakes

❌ Writing `i > 0` instead of `i > idx` — wrongly skips elements that could be used at deeper levels.
❌ Using `continue` instead of `break` when `arr[i] > target` — slower but still correct; `break` is the optimization.
❌ Forgetting to sort — duplicate skipping and break pruning both depend on sorted order.
❌ Using `idx` (not `i+1`) in the recursive call — allows element reuse, turning it into Sum I.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "unique combinations, duplicates in input, each element once" → **sort + loop + `i>idx && arr[i]==arr[i-1]` skip + recurse with `i+1`**.

---

## 🏆 Pattern Category

`Recursion` · `Backtracking` · `Combination Sum` · `Duplicate Handling`

---

## ⏱️ 30-Second Last-Minute Revision

> Sort. Loop i=idx→n. Skip dup: `i>idx&&arr[i]==arr[i-1]`. Prune: `arr[i]>target→break`. Include: push, `recurse(i+1, target-arr[i])`, pop. Base: `target==0→push`. Key: `i>idx` (not `i>0`) and `i+1` (not `idx`). **Time:** O(2^N).
