# P46 — Subsets and Combinations

## 1. First-Timer Explanation

### What Is It?
**Subsets** enumerates all possible selections from a set (power set). **Combinations** enumerates all size-k selections. Both use backtracking: build the current selection incrementally, and when done (or at target size), record it. The key control: pass a `start` index so you only look forward, preventing duplicates from reordering.

### Analogy
Making a pizza: you have toppings [cheese, peppers, mushrooms]. You want all possible pizzas. Start with no toppings. Try adding cheese, then from cheese try adding peppers, etc. When you decide "done choosing," record the pizza. Then backtrack (remove cheese) and try starting from peppers. The `start` index ensures you never reconsider toppings you've already passed.

### Visual Walkthrough — Subsets([1,2,3])
```
dfs(start=0, current=[])
├── pick 1 → dfs(1, [1])
│   ├── pick 2 → dfs(2, [1,2])
│   │   ├── pick 3 → dfs(3, [1,2,3]) ← record [1,2,3]
│   │   └── done → record [1,2]
│   ├── pick 3 → dfs(3, [1,3]) ← record [1,3]
│   └── done → record [1]
├── pick 2 → dfs(2, [2])
│   ├── pick 3 → dfs(3, [2,3]) ← record [2,3]
│   └── done → record [2]
├── pick 3 → dfs(3, [3]) ← record [3]
└── done → record []

All subsets: [], [1], [1,2], [1,2,3], [1,3], [2], [2,3], [3]
```

### When to Use
- "Return all subsets / power set"
- "All combinations of size k"
- "All combinations that sum to target"
- "All ways to partition/pick elements"

### When NOT to Use
- Counting only (no need to enumerate) → math formula or DP
- Input has obvious duplicates → sort + skip duplicates variant

### Common Mistakes
1. Forgetting `start` index → generates permutations (not combinations)
2. Not copying `current` when recording → all records point to same list
3. Duplicate handling: forgetting `if i > start && nums[i] == nums[i-1] continue`
4. Off-by-one in base case for combinations

---

## 2. Revision Card

**Recognition Signal:** "all subsets", "all combinations", "sum equals target", "choose k elements"

**Core Idea:** DFS with `start` index. At each step, try each element from `start` to end, add to current, recurse with `start = i+1`, then remove. Record either at every node (subsets) or at target depth/sum (combinations).

**Trigger Keywords:** subsets, combinations, power set, all possible, choose

**Complexity:**
| Problem | Time | Space |
|---------|------|-------|
| Subsets | O(2^n · n) | O(n) |
| Combinations size k | O(C(n,k) · k) | O(k) |
| Combination Sum | O(2^n · n) | O(n) |

---

## 3. Interview Tell Signs

- "Return all subsets" → record at every dfs node, start index prevents duplicates
- "Combinations that sum to target" → add `remain` parameter, prune if remain < 0
- "Elements can repeat" → don't increment start after picking (unbounded)
- "Input has duplicates, no duplicate results" → sort + skip same element at same depth

---

## 4. C++ Template

```cpp
#include <vector>
#include <algorithm>
using namespace std;

// ── Subsets (no duplicates in input) ─────────────────────────────────────────
vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> res;
    vector<int> cur;
    
    function<void(int)> dfs = [&](int start) {
        res.push_back(cur); // record at every node
        for (int i = start; i < (int)nums.size(); i++) {
            cur.push_back(nums[i]);
            dfs(i + 1);
            cur.pop_back();
        }
    };
    
    dfs(0);
    return res;
}

// ── Subsets II (duplicates in input) ─────────────────────────────────────────
vector<vector<int>> subsetsWithDup(vector<int>& nums) {
    sort(nums.begin(), nums.end()); // MUST sort first
    vector<vector<int>> res;
    vector<int> cur;
    
    function<void(int)> dfs = [&](int start) {
        res.push_back(cur);
        for (int i = start; i < (int)nums.size(); i++) {
            if (i > start && nums[i] == nums[i-1]) continue; // skip dup at same level
            cur.push_back(nums[i]);
            dfs(i + 1);
            cur.pop_back();
        }
    };
    
    dfs(0);
    return res;
}

// ── Combination Sum (unlimited reuse) ────────────────────────────────────────
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> res;
    vector<int> cur;
    
    function<void(int, int)> dfs = [&](int start, int remain) {
        if (remain == 0) { res.push_back(cur); return; }
        for (int i = start; i < (int)candidates.size(); i++) {
            if (candidates[i] > remain) break; // pruning (sort candidates first)
            cur.push_back(candidates[i]);
            dfs(i, remain - candidates[i]); // i not i+1: can reuse
            cur.pop_back();
        }
    };
    
    sort(candidates.begin(), candidates.end());
    dfs(0, target);
    return res;
}
```

---

## 5. How to Present in Interview

**Verbal Script:**
> "For subsets, I use backtracking with a start index. At each DFS call, I record the current selection (it's a valid subset at any size). Then I try adding each element from `start` onwards, recurse with `start = i+1` to avoid reuse, and backtrack. For combination sum with reuse, I recurse with `i` instead of `i+1`. For duplicate inputs, I sort first and skip same element at the same recursion level."

**Checklist:**
- [ ] Establish what gets recorded (every node vs leaf only)
- [ ] Does order matter? (combinations: no → use start; permutations: yes → use visited)
- [ ] Can elements repeat in output? (sort + skip)
- [ ] Can same element be used multiple times? (i vs i+1)
- [ ] Add pruning if target sum given

---

## 6. Problems

### Problem 1: Subsets
**Difficulty:** Medium | **LC:** 78

**Approach:** DFS, record at every call. `start` prevents duplicates.

```cpp
vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> res;
    vector<int> cur;
    function<void(int)> dfs = [&](int start) {
        res.push_back(cur);
        for (int i = start; i < (int)nums.size(); i++) {
            cur.push_back(nums[i]);
            dfs(i + 1);
            cur.pop_back();
        }
    };
    dfs(0);
    return res;
}
// Time: O(2^n * n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Subsets II (with duplicates)
**Difficulty:** Medium | **LC:** 90

**Approach:** Sort first. At each level, skip if `i > start && nums[i] == nums[i-1]`.

```cpp
vector<vector<int>> subsetsWithDup(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> res;
    vector<int> cur;
    function<void(int)> dfs = [&](int start) {
        res.push_back(cur);
        for (int i = start; i < (int)nums.size(); i++) {
            if (i > start && nums[i] == nums[i-1]) continue;
            cur.push_back(nums[i]);
            dfs(i + 1);
            cur.pop_back();
        }
    };
    dfs(0);
    return res;
}
// Time: O(2^n * n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Combination Sum (unlimited reuse)
**Difficulty:** Medium | **LC:** 39

**Approach:** Sort candidates. Recurse with same `i` (reuse allowed). Prune if candidate > remain.

```cpp
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    sort(candidates.begin(), candidates.end());
    vector<vector<int>> res;
    vector<int> cur;
    function<void(int, int)> dfs = [&](int start, int remain) {
        if (remain == 0) { res.push_back(cur); return; }
        for (int i = start; i < (int)candidates.size(); i++) {
            if (candidates[i] > remain) break;
            cur.push_back(candidates[i]);
            dfs(i, remain - candidates[i]); // reuse allowed
            cur.pop_back();
        }
    };
    dfs(0, target);
    return res;
}
// Time: O(2^(target/min)) worst | Space: O(target/min)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Combination Sum II (each used once, no dup results)
**Difficulty:** Medium | **LC:** 40

**Approach:** Sort. Each element used at most once (i+1 in recursion). Skip duplicates at same level.

```cpp
vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    sort(candidates.begin(), candidates.end());
    vector<vector<int>> res;
    vector<int> cur;
    function<void(int, int)> dfs = [&](int start, int remain) {
        if (remain == 0) { res.push_back(cur); return; }
        for (int i = start; i < (int)candidates.size(); i++) {
            if (candidates[i] > remain) break;
            if (i > start && candidates[i] == candidates[i-1]) continue; // skip dup
            cur.push_back(candidates[i]);
            dfs(i + 1, remain - candidates[i]); // no reuse
            cur.pop_back();
        }
    };
    dfs(0, target);
    return res;
}
// Time: O(2^n * n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Combinations (choose k from 1..n)
**Difficulty:** Medium | **LC:** 77

**Approach:** Standard combination DFS. Record when current size equals k.

```cpp
vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> res;
    vector<int> cur;
    function<void(int)> dfs = [&](int start) {
        if ((int)cur.size() == k) { res.push_back(cur); return; }
        // pruning: need k-cur.size() more elements, so start ≤ n-(k-cur.size())+1
        for (int i = start; i <= n - (k - (int)cur.size()) + 1; i++) {
            cur.push_back(i);
            dfs(i + 1);
            cur.pop_back();
        }
    };
    dfs(1);
    return res;
}
// Time: O(C(n,k) * k) | Space: O(k)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: Letter Combinations of a Phone Number
**Difficulty:** Medium | **LC:** 17

**Approach:** For each digit, try all mapped letters. Base case: index == digits.size() → record.

```cpp
vector<string> letterCombinations(string digits) {
    if (digits.empty()) return {};
    string mp[] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> res;
    string cur;
    function<void(int)> dfs = [&](int idx) {
        if (idx == (int)digits.size()) { res.push_back(cur); return; }
        for (char c : mp[digits[idx] - '0']) {
            cur += c;
            dfs(idx + 1);
            cur.pop_back();
        }
    };
    dfs(0);
    return res;
}
// Time: O(4^n * n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** "All subsets" vs "All subsets that sum to X" — what changes in the code?
<details><summary>Reveal</summary>
Subsets: record at every DFS node. Sum to X: add `remain` parameter; only record when remain==0; prune when remain < 0 or element > remain.
</details>

**Drill 2:** Input [1,1,2]. How many unique subsets? What's the dedup rule?
<details><summary>Reveal</summary>
Sort → [1,1,2]. Unique subsets: [], [1], [1,1], [1,1,2], [1,2], [2] = 6. Rule: at each recursion level, if nums[i] == nums[i-1] AND i > start, skip. This skips same element at same depth but allows it at different depths.
</details>

**Drill 3:** Combination sum: candidates=[2,3,6,7], target=7. What's the difference between recursing with `i` vs `i+1`?
<details><summary>Reveal</summary>
`i`: can reuse same element → [2,2,3] is valid. `i+1`: each element used at most once → only [7] and [3,4] (if 4 existed). LC 39 uses `i` (reuse); LC 40 uses `i+1`.
</details>

**Drill 4:** Why do we need to sort before the dedup check `nums[i] == nums[i-1]`?
<details><summary>Reveal</summary>
If unsorted, duplicates might not be adjacent, so the check would miss them. Sorting guarantees all equal values are consecutive, making the skip condition correct.
</details>

**Drill 5:** Combinations(n=5, k=3). The pruning `i <= n-(k-cur.size())+1` — explain it.
<details><summary>Reveal</summary>
If we still need m = k-cur.size() more elements, and we're at position i, we need at least m elements remaining: n-i+1 >= m → i <= n-m+1. So we can prune the loop when i exceeds n-(k-cur.size())+1. Reduces constant factor significantly.
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Combinations Count |
|---------|------|--------------------|
| All subsets of n | O(2^n · n) | 2^n |
| Combinations C(n,k) | O(C(n,k) · k) | C(n,k) |
| Combination sum (reuse) | O(2^(t/min) · n) | varies |
| Phone letter combos | O(4^n · n) | up to 4^n |

---

## 9. Common Follow-up Questions

**Q: Can you solve subsets without backtracking?**
A: Yes — bit manipulation. For n elements, iterate 0 to 2^n-1. Each bit in the number decides include/exclude. O(2^n · n) same complexity.

**Q: How do you count distinct subsets without enumerating?**
A: For set with no duplicates: 2^n. With duplicates: group equal elements, each group of size k contributes k+1 choices. Multiply.

**Q: Combination sum but with at most k elements?**
A: Add depth parameter to DFS, prune when cur.size() == k.

**Q: What's the iterative version of subsets?**
A: Start with result=[[]], iterate through nums. For each element, for each existing subset, create a new subset with element added. O(2^n) iterations.

---

## 10. Cross-Pattern Connections

- **P47 (Permutations):** No `start` index; use `visited[]` instead; order matters
- **P48 (N-Queens/Constraint):** Backtracking with validity check before recursing
- **P32 (Knapsack DP):** Count subset sums → DP; enumerate → backtracking
- **P36 (Bitmask DP):** Bitmask encodes subset membership; alternative for small n
- **P53 (Greedy):** When only the optimal subset/combination is needed, greedy beats backtracking
