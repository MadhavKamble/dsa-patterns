# Pattern 36: Bitmask DP

## Category
Dynamic Programming

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 464. Can I Win | Medium | https://leetcode.com/problems/can-i-win/ |
| 2 | 526. Beautiful Arrangement | Medium | https://leetcode.com/problems/beautiful-arrangement/ |
| 3 | 698. Partition to K Equal Sum Subsets | Medium | https://leetcode.com/problems/partition-to-k-equal-sum-subsets/ |
| 4 | 847. Shortest Path Visiting All Nodes | Hard | https://leetcode.com/problems/shortest-path-visiting-all-nodes/ |
| 5 | 1125. Smallest Sufficient Team | Hard | https://leetcode.com/problems/smallest-sufficient-team/ |
| 6 | 1349. Maximum Students Taking Exam | Hard | https://leetcode.com/problems/maximum-students-taking-exam/ |

---

## 1. First-Timer Explanation

### What is this pattern?
**Bitmask DP** uses a bitmask (integer) to represent a set of elements — each bit position corresponds to one element (1 = included, 0 = not included). This allows representing all 2^n subsets as integers and using them as DP state.

**When to use**: when n ≤ 20 (usually ≤ 15 in practice) and the problem requires tracking which subset of items has been processed.

**Core bit operations:**
```
mask | (1 << i)   → add element i to set
mask & ~(1 << i)  → remove element i from set
mask & (1 << i)   → check if element i is in set
(mask >> i) & 1   → bit at position i
__builtin_popcount(mask) → count of set bits
(1 << n) - 1      → full mask (all n elements selected)
```

**Template**: `dp[mask]` = optimal value when the set of processed elements is `mask`.

### Visual Walkthrough
```
Beautiful Arrangement: n=3, positions 1,2,3, numbers 1,2,3
Valid: nums[pos] % pos == 0 OR pos % nums[pos] == 0

Bitmask: bit i = number (i+1) has been placed
mask=000 (binary) = nothing placed

dp[001] = placements ending with 1 placed (num=1 at pos=1):
  1%1=0 ✓ → dp[001] = 1

dp[010] = num=2 placed (must go to pos=1):
  2%1=0 ✓ → dp[010] = 1

dp[011] = nums 1,2 placed (pos 1 and 2):
  place 2 at pos 2: 2%2=0 ✓ AND num 1 must go to pos 1: 1%1=0 ✓
  → dp[011] = sum of valid arrangements

... Continue for all masks up to 111 (=7)
dp[111] = answer
```

### When TO use this pattern
- Track which subset of n ≤ 20 items has been processed
- Assignment problems (assign items to positions)
- Traveling Salesman Problem (TSP) — track visited cities
- Shortest path visiting all nodes (BFS + bitmask state)
- Partition into subsets with constraints

### When NOT to use this pattern
- n > 20 (2^20 = 1M states, 2^25 = 33M — too slow)
- Items are not discrete/identifiable — use regular DP
- Simple combinatorics — bitmask overkill

### Common Beginner Mistakes
- **Check if bit is set**: `mask & (1 << i)` — don't forget the parentheses around `1 << i`
- **Off by one**: elements 0-indexed or 1-indexed? Be consistent
- **Iterating unset bits**: `for i: if !(mask & (1<<i)) → try adding i`
- **BFS + bitmask**: state = (node, visited_mask); mark visited when enqueuing

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | n ≤ 20, "visit all nodes", "assign to positions", "which subset", "partition k groups" |
| Core Idea | Represent subset as bitmask integer; dp[mask] = optimal for that subset |
| Trigger Keywords | "all nodes visited", "assign numbers", "partition K subsets", "smallest team with skills" |
| Avoid When | n > 20, items not discrete, simpler DP exists |
| Time Complexity | O(2^n × n) typically |
| Space Complexity | O(2^n) |

**Gotchas:**
- Always check `mask & (1 << i)` with parentheses
- BFS + bitmask: start with ALL nodes as sources (not just one); state = (node, mask)
- Smallest sufficient team: mask = skill set; dp[mask] = min team size
- Partition K subsets: try adding each unused element to current bucket

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"visit all nodes"` in a graph → BFS + bitmask state (n ≤ 12 for this)
- `"partition into K equal sum subsets"` → bitmask DP
- `"beautiful arrangement"` (placement with constraints) → bitmask DP
- `"can I win"` game with n ≤ 20 integers → bitmask + memoization
- `"smallest team covering all skills"` → bitmask DP over skills set

---

## 4. C++ Template

```cpp
/*
 * Pattern: Bitmask DP
 * Time: O(2^n * n) | Space: O(2^n)
 */

// BEAUTIFUL ARRANGEMENT (count valid assignments)
int countArrangement(int n) {
    vector<int> dp(1 << n, 0);
    dp[0] = 1;
    for (int mask = 0; mask < (1 << n); mask++) {
        int pos = __builtin_popcount(mask) + 1;  // current position to fill
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) continue;  // already placed
            int num = i + 1;
            if (num % pos == 0 || pos % num == 0) {
                dp[mask | (1 << i)] += dp[mask];
            }
        }
    }
    return dp[(1 << n) - 1];
}

// BITMASK DP — GENERAL TSP STYLE
// dp[mask][i] = optimal value having visited set 'mask', currently at i
int bitmaskDP(int n, vector<vector<int>>& cost) {
    int full = (1 << n) - 1;
    vector<vector<int>> dp(1 << n, vector<int>(n, INT_MAX));
    dp[1][0] = 0;  // start at node 0
    for (int mask = 1; mask <= full; mask++) {
        for (int u = 0; u < n; u++) {
            if (!(mask & (1 << u)) || dp[mask][u] == INT_MAX) continue;
            for (int v = 0; v < n; v++) {
                if (mask & (1 << v)) continue;
                int nextMask = mask | (1 << v);
                dp[nextMask][v] = min(dp[nextMask][v], dp[mask][u] + cost[u][v]);
            }
        }
    }
    int ans = INT_MAX;
    for (int u = 1; u < n; u++)
        if (dp[full][u] != INT_MAX)
            ans = min(ans, dp[full][u] + cost[u][0]);
    return ans;
}

// BFS + BITMASK (shortest path visiting all nodes)
int shortestPathLength(vector<vector<int>>& graph) {
    int n = graph.size(), full = (1 << n) - 1;
    vector<vector<bool>> vis(1 << n, vector<bool>(n, false));
    queue<tuple<int,int,int>> q;  // (dist, node, mask)
    for (int i = 0; i < n; i++) {
        q.push({0, i, 1 << i});
        vis[1<<i][i] = true;
    }
    while (!q.empty()) {
        auto [d, u, mask] = q.front(); q.pop();
        if (mask == full) return d;
        for (int v : graph[u]) {
            int nm = mask | (1 << v);
            if (!vis[nm][v]) { vis[nm][v] = true; q.push({d+1, v, nm}); }
        }
    }
    return 0;
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"Since n is small (≤ 20), I can represent each subset of elements as a bitmask. dp[mask] stores the optimal result when exactly the elements represented by the bits in 'mask' have been processed. For each mask, I try adding each unset bit (element not yet used) and transition to the next state. This gives O(2^n × n) time, which is feasible for n ≤ 20."

### Interview Flow Checklist
- [ ] Verify n ≤ 20 (bitmask is feasible)
- [ ] Define what bits represent (element selected, city visited, etc.)
- [ ] Define dp[mask] precisely
- [ ] For each state: iterate unset bits (elements not yet processed)
- [ ] Set base case (empty mask = 0 or single-element masks)
- [ ] Return dp[(1<<n)-1] (all elements processed)

---

## 6. Problems

---

### Problem 1: 526. Beautiful Arrangement
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/beautiful-arrangement/
**Optimal C++ Solution:**
```cpp
int countArrangement(int n) {
    vector<int> dp(1 << n, 0);
    dp[0] = 1;
    for (int mask = 0; mask < (1 << n); mask++) {
        if (!dp[mask]) continue;
        int pos = __builtin_popcount(mask) + 1;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) continue;
            int num = i + 1;
            if (num % pos == 0 || pos % num == 0)
                dp[mask | (1 << i)] += dp[mask];
        }
    }
    return dp[(1 << n) - 1];
}
```
**Edge Cases:** [ ] n=1 (always 1 arrangement)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 847. Shortest Path Visiting All Nodes
**Difficulty:** Hard
**Leetcode:** https://leetcode.com/problems/shortest-path-visiting-all-nodes/
**Why this pattern fits:** BFS with state (node, visited_mask); multi-source from all nodes

**Optimal C++ Solution:**
```cpp
int shortestPathLength(vector<vector<int>>& graph) {
    int n = graph.size(), full = (1 << n) - 1;
    vector<vector<bool>> vis(1 << n, vector<bool>(n, false));
    queue<tuple<int,int,int>> q;
    for (int i = 0; i < n; i++) {
        q.push({0, i, 1 << i}); vis[1<<i][i] = true;
    }
    while (!q.empty()) {
        auto [d, u, mask] = q.front(); q.pop();
        if (mask == full) return d;
        for (int v : graph[u]) {
            int nm = mask | (1 << v);
            if (!vis[nm][v]) { vis[nm][v] = true; q.push({d+1, v, nm}); }
        }
    }
    return 0;
}
```
**Edge Cases:** [ ] Single node (return 0), [ ] All nodes connected

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 3: 698. Partition to K Equal Sum Subsets
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/partition-to-k-equal-sum-subsets/
**Why this pattern fits:** Track which elements have been used via bitmask

**Optimal C++ Solution:**
```cpp
bool canPartitionKSubsets(vector<int>& nums, int k) {
    int sum = accumulate(nums.begin(), nums.end(), 0);
    if (sum % k) return false;
    int target = sum / k, n = nums.size();
    vector<int> dp(1 << n, -1);
    dp[0] = 0;
    sort(nums.rbegin(), nums.rend());  // prune: larger first
    for (int mask = 0; mask < (1 << n); mask++) {
        if (dp[mask] == -1) continue;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) continue;
            int next = mask | (1 << i);
            if (dp[next] != -1) continue;
            int cur = (dp[mask] + nums[i]) % target;
            if (dp[mask] + nums[i] <= target) {
                dp[next] = cur;
            }
        }
    }
    return dp[(1 << n) - 1] == 0;
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 4: 1125. Smallest Sufficient Team
**Difficulty:** Hard
**Leetcode:** https://leetcode.com/problems/smallest-sufficient-team/
**Why this pattern fits:** Cover all required skills (skill set = bitmask); minimize team size

**Optimal C++ Solution:**
```cpp
vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {
    int n = req_skills.size();
    unordered_map<string, int> skillIdx;
    for (int i = 0; i < n; i++) skillIdx[req_skills[i]] = i;

    int full = (1 << n) - 1;
    vector<vector<int>> dp(full+1);  // dp[mask] = team covering skills in mask
    dp[0] = {};
    for (int i = 0; i < (int)people.size(); i++) {
        int skillMask = 0;
        for (string& s : people[i]) if (skillIdx.count(s)) skillMask |= (1 << skillIdx[s]);
        for (int mask = full; mask >= 0; mask--) {
            if (dp[mask].empty() && mask != 0) continue;
            int newMask = mask | skillMask;
            if (dp[newMask].empty() || dp[newMask].size() > dp[mask].size() + 1) {
                dp[newMask] = dp[mask];
                dp[newMask].push_back(i);
            }
        }
    }
    return dp[full];
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> You have n light switches (n ≤ 20). Each switch can be ON or OFF. You know which combinations of switches, when all ON simultaneously, cause a short circuit. Find the maximum number of switches you can turn ON.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Bitmask enumeration
**Reason:** Enumerate all 2^n subsets of switches being ON. For each subset (bitmask), check if any forbidden combination is a sub-bitmask of it. The maximum popcount among valid subsets is the answer. O(2^n × forbidden_count).
</details>

---

**Drill 2:**
> Assign n jobs to n workers such that each worker gets exactly one job and no worker is assigned a job they can't do. Count the number of valid assignments.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Bitmask DP (matching count)
**Reason:** dp[mask] = number of ways to assign jobs to workers where 'mask' represents which workers have been assigned. At stage popcount(mask)+1-th job assignment, try assigning to each unassigned worker. This counts all valid perfect matchings. O(2^n × n).
</details>

---

**Drill 3:**
> In a graph, find the minimum number of colors to color all nodes such that no two adjacent nodes share a color (chromatic number for small n).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Bitmask DP with independent sets
**Reason:** Precompute all independent sets (subsets with no edges between them). dp[mask] = min colors to color exactly the nodes in mask. dp[mask] = min over all independent subsets S ⊆ mask of (dp[mask^S] + 1). O(3^n) time (subset enumeration). Feasible for n ≤ 20.
</details>

---

**Drill 4:**
> Given n tasks with deadlines and rewards, find the maximum reward you can earn by completing tasks on time (each task takes 1 day).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Greedy (not bitmask DP)
**Reason:** This is the classic job scheduling problem. Greedy: sort by reward descending; for each job, schedule it as late as possible before its deadline (find latest free slot). O(n log n + n × max_deadline). Bitmask would be O(2^n × n) — much slower and unnecessary here.
</details>

---

**Drill 5:**
> Cover a set of required features using products from a catalog. Each product covers a subset of features. Find the minimum cost to cover all features.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Bitmask DP (set cover)
**Reason:** Set cover is NP-hard in general, but with few features (m ≤ 20), bitmask DP works. dp[mask] = min cost to cover skills in mask. For each product with skill mask pm: dp[mask | pm] = min(dp[mask | pm], dp[mask] + cost). O(2^m × products). LC 1125 is exactly this.
</details>

---

## 8. Complexity Cheatsheet

| Variant | Time | Space | Max n |
|---------|------|-------|-------|
| Standard bitmask DP | O(2^n × n) | O(2^n) | ≤ 20 |
| TSP bitmask DP | O(2^n × n²) | O(2^n × n) | ≤ 15 |
| BFS + bitmask | O(2^n × n × E) | O(2^n × n) | ≤ 12 |
| Subset enumeration | O(3^n) | O(2^n) | ≤ 20 |

---

## 9. Common Follow-up Questions

1. What's the maximum n for bitmask DP? (Practical limit: n ≤ 20 for O(2^n × n) with reasonable constant. n ≤ 15 for O(2^n × n²). Beyond that, other approaches needed)
2. How to enumerate all subsets of a given mask? (Use `sub = mask; while sub > 0: process sub; sub = (sub-1) & mask`. This visits all submasks in O(3^n) total for all masks)
3. Bitmask vs DP with sets? (Bitmask is more efficient — O(1) bit operations vs set operations. Bitmask states fit in int/long long; set-based DP needs hash maps)
4. Can you print the actual set of items chosen? (Yes — backtrack through dp table: from dp[full], find which element was last added (i where dp[full ^ (1<<i)] is a valid predecessor), continue backward)

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| BFS | Shortest path + which nodes visited | 847. All Nodes Visited |
| DFS + Memoization | Game theory with bitmask state | 464. Can I Win |
| Greedy | Sometimes replaces bitmask for assignment | Job scheduling |
| Subset Enumeration | O(3^n) sub-mask DP | Set cover, chromatic number |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
