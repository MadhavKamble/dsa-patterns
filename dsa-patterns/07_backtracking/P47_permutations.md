# P47 — Permutations

## 1. First-Timer Explanation

### What Is It?
A **permutation** is an ordered arrangement of all (or some) elements. Unlike combinations (where [1,2] == [2,1]), permutations treat order as significant ([1,2] ≠ [2,1]). Backtracking generates permutations by tracking which elements are already used (via a `visited` boolean array) and trying every unused element at each position.

### Analogy
Arranging 3 books on a shelf. For the first position, you have 3 choices. After placing one, you have 2 choices for position 2. Then 1 for position 3. That's 3! = 6 arrangements. Backtracking = pick a book, recursively arrange the rest, then put the book back.

### Visual Walkthrough — Permutations([1,2,3])
```
dfs(current=[], used=[F,F,F])
├── pick 1, used=[T,F,F] → dfs([1], [T,F,F])
│   ├── pick 2, used=[T,T,F] → dfs([1,2], [T,T,F])
│   │   └── pick 3 → dfs([1,2,3]) → RECORD [1,2,3]
│   └── pick 3, used=[T,F,T] → dfs([1,3], [T,F,T])
│       └── pick 2 → RECORD [1,3,2]
├── pick 2 → ...
│   → RECORD [2,1,3], [2,3,1]
└── pick 3 → ...
    → RECORD [3,1,2], [3,2,1]
```

### Key Difference from Combinations
| | Combinations | Permutations |
|--|--|--|
| [1,2] and [2,1] | Same (1 result) | Different (2 results) |
| Duplicate prevention | `start` index | `visited` array |
| Depth meaning | subset size | position index |

### When to Use
- "All permutations of..."
- "All orderings of..."
- "Generate all arrangements"
- "Next permutation" (different algorithm — in-place)

### When NOT to Use
- Only counting → n! or formula
- Constraints make most permutations invalid → heavy pruning or DP better

### Common Mistakes
1. Using `start` index instead of `visited` array → misses permutations
2. Not unmarking `visited[i] = false` after backtracking
3. For duplicates: using wrong skip condition → still generates dups

---

## 2. Revision Card

**Recognition Signal:** "all permutations", "all orderings", "arrangements"

**Core Idea:** DFS with `visited[n]` boolean array. At each step, try each unvisited element. Mark visited, recurse, unmark. Record when current length equals n.

**Trigger Keywords:** permutations, orderings, arrangements, all sequences, rearrange

**Complexity:**
| Problem | Time | Space |
|---------|------|-------|
| All permutations | O(n! · n) | O(n) |
| Permutations II (dups) | O(n! · n) worst | O(n) |

---

## 3. Interview Tell Signs

- "All permutations" → visited array backtracking
- "All orderings that satisfy constraint" → permutation with pruning
- "Arrange tasks/items" → permutation
- "No two adjacent same" → reorganize string or permutation with validity check

---

## 4. C++ Template

```cpp
#include <vector>
#include <algorithm>
using namespace std;

// ── All Permutations (no duplicates) ─────────────────────────────────────────
vector<vector<int>> permute(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> res;
    vector<int> cur;
    vector<bool> used(n, false);
    
    function<void()> dfs = [&]() {
        if ((int)cur.size() == n) { res.push_back(cur); return; }
        for (int i = 0; i < n; i++) {
            if (used[i]) continue;
            used[i] = true;
            cur.push_back(nums[i]);
            dfs();
            cur.pop_back();
            used[i] = false;
        }
    };
    
    dfs();
    return res;
}

// ── Permutations II (with duplicate input) ───────────────────────────────────
vector<vector<int>> permuteUnique(vector<int>& nums) {
    sort(nums.begin(), nums.end()); // sort to group duplicates
    int n = nums.size();
    vector<vector<int>> res;
    vector<int> cur;
    vector<bool> used(n, false);
    
    function<void()> dfs = [&]() {
        if ((int)cur.size() == n) { res.push_back(cur); return; }
        for (int i = 0; i < n; i++) {
            if (used[i]) continue;
            // Skip: same value, previous copy not used (would generate same perm)
            if (i > 0 && nums[i] == nums[i-1] && !used[i-1]) continue;
            used[i] = true;
            cur.push_back(nums[i]);
            dfs();
            cur.pop_back();
            used[i] = false;
        }
    };
    
    dfs();
    return res;
}

// ── Swap-based permutation (in-place, more efficient) ────────────────────────
void permuteSwap(vector<int>& nums, int start, vector<vector<int>>& res) {
    if (start == (int)nums.size()) { res.push_back(nums); return; }
    for (int i = start; i < (int)nums.size(); i++) {
        swap(nums[start], nums[i]);
        permuteSwap(nums, start + 1, res);
        swap(nums[start], nums[i]); // backtrack
    }
}
```

---

## 5. How to Present in Interview

**Verbal Script:**
> "Permutations care about order, unlike combinations. So I can't use a start index to restrict choices — I need to track which elements are already used. My DFS tries every unused element at each position: mark used, add to current, recurse, then unmark and remove. When current length equals n, I record it. This gives all n! permutations in O(n! · n) time."

**Checklist:**
- [ ] Use `visited` array, NOT `start` index
- [ ] Backtrack both `cur.pop_back()` AND `used[i] = false`
- [ ] For duplicates: sort + `if i > 0 && nums[i] == nums[i-1] && !used[i-1] continue`
- [ ] Explain the dup-skip logic: prevents using two identical elements in same "slot" differently
- [ ] Mention O(n!) is unavoidable — must generate all

---

## 6. Problems

### Problem 1: Permutations
**Difficulty:** Medium | **LC:** 46

**Approach:** DFS with visited array. Record when length == n.

```cpp
vector<vector<int>> permute(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> res;
    vector<int> cur;
    vector<bool> used(n, false);
    function<void()> dfs = [&]() {
        if ((int)cur.size() == n) { res.push_back(cur); return; }
        for (int i = 0; i < n; i++) {
            if (used[i]) continue;
            used[i] = true; cur.push_back(nums[i]);
            dfs();
            cur.pop_back(); used[i] = false;
        }
    };
    dfs();
    return res;
}
// Time: O(n! * n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Permutations II (with duplicates)
**Difficulty:** Medium | **LC:** 47

**Approach:** Sort, then skip `nums[i] == nums[i-1] && !used[i-1]`.

```cpp
vector<vector<int>> permuteUnique(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    vector<vector<int>> res;
    vector<int> cur;
    vector<bool> used(n, false);
    function<void()> dfs = [&]() {
        if ((int)cur.size() == n) { res.push_back(cur); return; }
        for (int i = 0; i < n; i++) {
            if (used[i]) continue;
            if (i > 0 && nums[i] == nums[i-1] && !used[i-1]) continue;
            used[i] = true; cur.push_back(nums[i]);
            dfs();
            cur.pop_back(); used[i] = false;
        }
    };
    dfs();
    return res;
}
// Time: O(n! * n) worst | Space: O(n)
// Key: !used[i-1] ensures we always use the leftmost duplicate first
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Next Permutation
**Difficulty:** Medium | **LC:** 31

**Approach:** In-place. Find rightmost ascending pair (i, i+1). Swap nums[i] with the rightmost element > nums[i]. Reverse suffix after i.

```cpp
void nextPermutation(vector<int>& nums) {
    int n = nums.size(), i = n - 2;
    // find rightmost i where nums[i] < nums[i+1]
    while (i >= 0 && nums[i] >= nums[i+1]) i--;
    
    if (i >= 0) { // not last permutation
        int j = n - 1;
        while (nums[j] <= nums[i]) j--;
        swap(nums[i], nums[j]);
    }
    // reverse suffix after i
    reverse(nums.begin() + i + 1, nums.end());
}
// Time: O(n) | Space: O(1)
// Edge: [3,2,1] → already last permutation → becomes [1,2,3]
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Beautiful Arrangement
**Difficulty:** Medium | **LC:** 526

**Approach:** Permutation backtracking. At position `pos`, try numbers 1..n that aren't used AND satisfy (num % pos == 0 || pos % num == 0).

```cpp
int countArrangement(int n) {
    vector<bool> used(n + 1, false);
    int count = 0;
    function<void(int)> dfs = [&](int pos) {
        if (pos > n) { count++; return; }
        for (int num = 1; num <= n; num++) {
            if (!used[num] && (num % pos == 0 || pos % num == 0)) {
                used[num] = true;
                dfs(pos + 1);
                used[num] = false;
            }
        }
    };
    dfs(1);
    return count;
}
// Time: O(k) where k = valid arrangements | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Palindrome Permutation II
**Difficulty:** Medium | **LC:** 267

**Approach:** Count frequencies. At most one odd-count char. Backtrack on half the string.

```cpp
vector<string> generatePalindromes(string s) {
    unordered_map<char,int> cnt;
    for (char c : s) cnt[c]++;
    
    string half, mid;
    for (auto& [c, f] : cnt) {
        if (f % 2 == 1) { mid += c; if (mid.size() > 1) return {}; }
        half += string(f / 2, c);
    }
    
    sort(half.begin(), half.end());
    vector<string> res;
    do {
        res.push_back(half + mid + string(half.rbegin(), half.rend()));
    } while (next_permutation(half.begin(), half.end()));
    return res;
}
// Time: O((n/2)!) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: K-th Permutation Sequence
**Difficulty:** Hard | **LC:** 60

**Approach:** Math + greedy. At each position, determine which digit goes there based on k and factorial.

```cpp
string getPermutation(int n, int k) {
    vector<int> digits;
    int fact = 1;
    for (int i = 1; i <= n; i++) { digits.push_back(i); fact *= i; }
    
    k--; // 0-indexed
    string res;
    for (int i = n; i >= 1; i--) {
        fact /= i;
        int idx = k / fact;
        res += to_string(digits[idx]);
        digits.erase(digits.begin() + idx);
        k %= fact;
    }
    return res;
}
// Time: O(n^2) due to erase | Space: O(n)
// Key: don't enumerate all — use factorial number system
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** "All arrangements of [1,2,3]" → permutations or combinations?
<details><summary>Reveal</summary>
Permutations — order matters. [1,2,3] ≠ [3,2,1]. Use visited array, not start index. Count = 3! = 6.
</details>

**Drill 2:** Why does the duplicate skip condition use `!used[i-1]` instead of `used[i-1]`?
<details><summary>Reveal</summary>
We want to enforce that equal elements are always used in left-to-right order. If nums[i] == nums[i-1] and nums[i-1] is NOT currently used (in the current path), then using nums[i] now would create a duplicate of a future branch where nums[i-1] gets used. The `!used[i-1]` condition prevents this.
</details>

**Drill 3:** Permutations using swap: what's the advantage over visited array?
<details><summary>Reveal</summary>
No extra space for visited array or current list. Modifies in-place. Less memory, slightly faster. Downside: output may not be in lexicographic order.
</details>

**Drill 4:** K-th permutation of [1,2,3,4]. What's the 9th permutation (1-indexed)?
<details><summary>Reveal</summary>
k=8 (0-indexed). n=4, fact starts at 4!=24. Position 0: fact=3!=6, idx=8/6=1 → digit 2, k=8%6=2. Position 1: fact=2, idx=2/2=1 → digit 3, k=0. Position 2: fact=1, idx=0 → digit 1. Position 3: digit 4. Answer: 2314.
</details>

**Drill 5:** Beautiful Arrangement. Why is backtracking feasible here when n can be up to 15?
<details><summary>Reveal</summary>
The divisibility constraint heavily prunes the search tree. Most positions have few valid choices, making the actual explored states far less than 15!. The problem guarantees a solution exists, so pruning is effective.
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Space | Notes |
|---------|------|-------|-------|
| All permutations | O(n! × n) | O(n) | n! results, each of length n |
| Next permutation | O(n) | O(1) | In-place |
| Kth permutation | O(n²) | O(n) | Avoid generating all |
| Permutations II | O(n! × n) worst | O(n) | Pruning reduces constant |

---

## 9. Common Follow-up Questions

**Q: How do you generate permutations iteratively?**
A: Use `next_permutation` from `<algorithm>` (in-place, O(n)). Or use Heap's algorithm for all permutations in O(n!) total.

**Q: Memory-efficient permutation generation?**
A: Swap-based in-place backtracking — reuses original array, O(n) extra stack space.

**Q: How to generate permutations of a string with repeated characters?**
A: Sort string, use `next_permutation` in a loop until it wraps. Or backtracking with same duplicate-skip logic.

**Q: What's the relationship between permutations and factorial number system?**
A: Each permutation corresponds to a unique number in the factorial number system. This lets you directly compute the Kth permutation without generating all others.

---

## 10. Cross-Pattern Connections

- **P46 (Subsets/Combinations):** Combinations use `start` to avoid order; permutations use `visited` to allow any order
- **P48 (N-Queens):** Permutation-like placement with constraint checking
- **P36 (Bitmask DP):** Bitmask tracks which elements used — same idea as `visited[]` but encoded as integer for DP
- **P53 (Greedy):** When any valid ordering works (not all), greedy finds one without backtracking
- **P60 (Kth Permutation LC):** Math approach — skip enumeration using factorial number system
