# Pattern 41: Memoization / Top-Down DP

## Category
Dynamic Programming

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 509. Fibonacci Number | Easy | https://leetcode.com/problems/fibonacci-number/ |
| 2 | 576. Out of Boundary Paths | Medium | https://leetcode.com/problems/out-of-boundary-paths/ |
| 3 | 688. Knight Probability in Chessboard | Medium | https://leetcode.com/problems/knight-probability-in-chessboard/ |
| 4 | 1406. Stone Game III | Hard | https://leetcode.com/problems/stone-game-iii/ |
| 5 | 1671. Minimum Number of Removals to Make Mountain Array | Hard | https://leetcode.com/problems/minimum-number-of-removals-to-make-mountain-array/ |

---

## 1. First-Timer Explanation

### What is this pattern?
**Memoization (top-down DP)** is the recursive approach to DP: define the recurrence naturally as a function, then cache results to avoid recomputation. It's the alternative to bottom-up tabulation.

**When to prefer top-down over bottom-up:**
- Natural recursive structure is cleaner (scramble string, game theory)
- Not all subproblems need to be computed (sparse dependency graph)
- Problem has complex state that's easier to express recursively
- You want to write the solution quickly and optimize later

**The pattern:**
1. Write the brute-force recursive solution
2. Add memoization: `if (memo[state] != -1) return memo[state]`
3. Return `memo[state] = computed_value`

**State encoding:**
- Simple: `memo[i]` or `memo[i][j]`
- Complex: `unordered_map<string, int>` or `unordered_map<long long, int>` with encoding

### Visual Walkthrough
```
Fibonacci with memoization:
fib(5) → fib(4) + fib(3)
  fib(4) → fib(3) + fib(2)
    fib(3) → fib(2) + fib(1)
      fib(2) → fib(1) + fib(0) = 1+0 = 1, memo[2]=1
      fib(1) = 1, memo[1]=1
    fib(3) = 1+1=2, memo[3]=2
    fib(2) → CACHED → return 1
  fib(4) = 2+1=3, memo[4]=3
  fib(3) → CACHED → return 2
fib(5) = 3+2=5

Without memo: 15 calls. With memo: 9 calls (each unique state computed once)

Out of Boundary Paths: from (r,c) with N steps, how many paths go out of m×n grid?
dp(r, c, N) = sum of dp(nr, nc, N-1) for each adjacent cell (nr, nc)
If out of bounds, return 1 (found one path). If N=0, return 0 (ran out of steps)
Memoize on (r, c, N).
```

### When TO use this pattern
- Natural recursive structure with overlapping subproblems
- Complex state that's hard to iterate bottom-up
- Sparse subproblem space (many states never visited)
- Game theory / minimax problems
- Path counting with constraints

### When NOT to use this pattern
- Simple linear DP (bottom-up is cleaner)
- Stack overflow risk (deep recursion, very large n)
- Iteration order matters for space optimization

### Common Beginner Mistakes
- **Initialize memo to -1, not 0**: if 0 is a valid answer, you need a sentinel like -1 or INT_MIN
- **Memoize ALL states**: if you return early without computing, you skip the memo store
- **Modular arithmetic**: when counting paths mod p, don't store negative values in memo
- **State encoding**: ensure your hash key uniquely identifies the state

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | Recursive structure, overlapping subproblems, complex state |
| Core Idea | Write recursion first; add `if memo[state]: return memo[state]`; cache before returning |
| Trigger Keywords | Same as DP — any "count/min/max with optimal substructure" |
| Avoid When | Simple linear/2D DP (bottom-up cleaner), risk of stack overflow |
| Time Complexity | O(states × work per state) — same as bottom-up |
| Space Complexity | O(states) for memo + O(depth) for call stack |

**Gotchas:**
- Sentinel must differ from all valid answers; use -1 if answers are non-negative
- For count-mod-p: use a separate `computed[]` boolean array, not the value itself
- Top-down can be slower by constant due to function call overhead vs tabulation

---

## 3. Interview Tell Signs

### Keywords in problem statement
- Any DP problem can use memoization; prefer when state is complex or problem is recursive
- `"out of boundary paths"` → memoize (r, c, steps_remaining)
- `"knight probability"` → memoize (r, c, moves_remaining)
- `"stone game"` → game theory, natural to express recursively
- `"number of ways"` with complex constraints → top-down often cleaner

---

## 4. C++ Template

```cpp
/*
 * Pattern: Top-Down DP (Memoization)
 * Time: O(states * work_per_state) | Space: O(states)
 */

// GENERAL MEMOIZATION TEMPLATE (2D state)
unordered_map<int, int> memo;

int encode(int a, int b, int maxB) { return a * (maxB + 1) + b; }

int dp(int a, int b, /* other params */ int n) {
    if (/* base case */) return 0;
    int key = encode(a, b, n);
    if (memo.count(key)) return memo[key];
    int res = 0;
    // transitions...
    return memo[key] = res;
}

// OUT OF BOUNDARY PATHS
int findPaths(int m, int n, int maxMove, int startRow, int startCol) {
    const int MOD = 1e9 + 7;
    vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(maxMove+1, -1)));
    function<int(int,int,int)> dfs = [&](int r, int c, int moves) -> int {
        if (r<0||r>=m||c<0||c>=n) return 1;  // went out
        if (moves == 0) return 0;             // out of moves
        if (dp[r][c][moves] != -1) return dp[r][c][moves];
        long long res = 0;
        res += dfs(r+1,c,moves-1); res += dfs(r-1,c,moves-1);
        res += dfs(r,c+1,moves-1); res += dfs(r,c-1,moves-1);
        return dp[r][c][moves] = res % MOD;
    };
    return dfs(startRow, startCol, maxMove);
}

// KNIGHT PROBABILITY (floating point memo)
double knightProbability(int n, int k, int row, int col) {
    vector<vector<vector<double>>> dp(k+1, vector<vector<double>>(n, vector<double>(n, -1)));
    int moves[8][2] = {{2,1},{2,-1},{-2,1},{-2,-1},{1,2},{1,-2},{-1,2},{-1,-2}};
    function<double(int,int,int)> dfs = [&](int r, int c, int rem) -> double {
        if (r<0||r>=n||c<0||c>=n) return 0;
        if (rem == 0) return 1;
        if (dp[rem][r][c] >= 0) return dp[rem][r][c];
        double prob = 0;
        for (auto& m : moves) prob += dfs(r+m[0], c+m[1], rem-1) / 8.0;
        return dp[rem][r][c] = prob;
    };
    return dfs(row, col, k);
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"I'll use memoized recursion — top-down DP. I define `dp(r, c, moves)` as the number of paths that go out of bounds from position (r,c) with `moves` steps remaining. The base cases are: if (r,c) is out of bounds, return 1 (we've found a path out); if moves=0, return 0 (no more moves, failed to exit). For each call, I try all 4 directions and sum the results. I memoize on (r, c, moves) to avoid recomputation — there are O(m × n × maxMove) unique states, each computed in O(1) after the recursive calls."

### Interview Flow Checklist
- [ ] Define the recursive function signature and what it returns
- [ ] Write base cases (when does recursion stop?)
- [ ] Write the recurrence (how to compute from smaller subproblems)
- [ ] Add memoization: check memo before computing, store result before returning
- [ ] Ensure memo sentinel (-1) differs from all valid return values
- [ ] Return the top-level call result

---

## 6. Problems

---

### Problem 1: 576. Out of Boundary Paths
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/out-of-boundary-paths/
**Optimal C++ Solution:**
```cpp
int findPaths(int m, int n, int maxMove, int startRow, int startCol) {
    const int MOD = 1e9 + 7;
    vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(maxMove+1, -1)));
    function<long long(int,int,int)> dfs = [&](int r, int c, int moves) -> long long {
        if (r<0||r>=m||c<0||c>=n) return 1;
        if (moves == 0) return 0;
        if (dp[r][c][moves] != -1) return dp[r][c][moves];
        long long res = (dfs(r+1,c,moves-1) + dfs(r-1,c,moves-1) +
                         dfs(r,c+1,moves-1) + dfs(r,c-1,moves-1)) % MOD;
        return dp[r][c][moves] = res;
    };
    return dfs(startRow, startCol, maxMove);
}
```
**Edge Cases:** [ ] maxMove=0 and cell is inside (return 0), [ ] n=1 (single cell)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 688. Knight Probability in Chessboard
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/knight-probability-in-chessboard/
**Optimal C++ Solution:**
```cpp
double knightProbability(int n, int k, int row, int col) {
    vector<vector<vector<double>>> dp(k+1, vector<vector<double>>(n, vector<double>(n, -1)));
    int moves[8][2] = {{2,1},{2,-1},{-2,1},{-2,-1},{1,2},{1,-2},{-1,2},{-1,-2}};
    function<double(int,int,int)> dfs = [&](int r, int c, int rem) -> double {
        if (r<0||r>=n||c<0||c>=n) return 0;
        if (rem == 0) return 1;
        if (dp[rem][r][c] >= 0) return dp[rem][r][c];
        double prob = 0;
        for (auto& m : moves) prob += dfs(r+m[0], c+m[1], rem-1) / 8.0;
        return dp[rem][r][c] = prob;
    };
    return dfs(row, col, k);
}
```
**Edge Cases:** [ ] k=0 (knight stays in place, prob=1), [ ] Very small board

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 3: 1406. Stone Game III
**Difficulty:** Hard
**Leetcode:** https://leetcode.com/problems/stone-game-iii/
**Why this pattern fits:** Game theory — recursion with memo; player picks 1, 2, or 3 stones

**Optimal C++ Solution:**
```cpp
string stoneGameIII(vector<int>& stoneValue) {
    int n = stoneValue.size();
    vector<int> dp(n+1, INT_MIN);
    dp[n] = 0;
    for (int i = n-1; i >= 0; i--) {
        int take = 0;
        for (int k = 1; k <= 3 && i+k-1 < n; k++) {
            take += stoneValue[i+k-1];
            dp[i] = max(dp[i], take - dp[i+k]);
        }
    }
    if (dp[0] > 0) return "Alice";
    if (dp[0] < 0) return "Bob";
    return "Tie";
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 4: 1671. Minimum Number of Removals to Make Mountain Array
**Difficulty:** Hard
**Leetcode:** https://leetcode.com/problems/minimum-number-of-removals-to-make-mountain-array/
**Why this pattern fits:** LIS from left + LIS from right; combine for mountain; minimize removals

**Optimal C++ Solution:**
```cpp
int minimumMountainRemovals(vector<int>& nums) {
    int n = nums.size();
    // LIS ending at i (from left)
    vector<int> lis(n, 1);
    for (int i = 1; i < n; i++)
        for (int j = 0; j < i; j++)
            if (nums[j] < nums[i]) lis[i] = max(lis[i], lis[j]+1);
    // LIS starting from i (from right = LDS from i)
    vector<int> lds(n, 1);
    for (int i = n-2; i >= 0; i--)
        for (int j = i+1; j < n; j++)
            if (nums[j] < nums[i]) lds[i] = max(lds[i], lds[j]+1);
    // Mountain peak at i: lis[i] >= 2 and lds[i] >= 2 (both sides have at least one element)
    int maxMountain = 0;
    for (int i = 1; i < n-1; i++)
        if (lis[i] > 1 && lds[i] > 1)
            maxMountain = max(maxMountain, lis[i] + lds[i] - 1);
    return n - maxMountain;
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> A frog starts at position 0 and can jump to positions that are multiples of some step sizes. Count the number of ways to reach position N.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Top-down DP with memoization
**Reason:** dp(pos) = number of ways to reach N from pos. For each valid step size s, dp(pos) += dp(pos + s) if pos+s ≤ N. Base case: dp(N) = 1. Memoize dp(pos). This is Climbing Stairs generalized to arbitrary step sizes.
</details>

---

**Drill 2:**
> You're playing a game on a graph. From each node you can move to any connected node. A player wins if they move to a node the opponent can't move from. Find the winning strategy.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Game theory DP (Cat and Mouse style)
**Reason:** State = (my_pos, opponent_pos, whose_turn). dp(state) = can current player win? Base cases: if I'm at a dead end → lose. dp(state) = OR over moves of NOT dp(opponent_state). Memoize on state. This is the minimax DP, simplified for two-player graph games.
</details>

---

**Drill 3:**
> Count the number of valid decode ways for a numeric string (A=1, B=2, ..., Z=26).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** 1D memoized DP (or bottom-up)
**Reason:** dp(i) = number of ways to decode s[i..n-1]. Try taking 1 digit (s[i]) if it's 1-9: dp(i) += dp(i+1). Try taking 2 digits (s[i..i+1]) if it's 10-26: dp(i) += dp(i+2). Base case: dp(n) = 1. Memoize or do bottom-up. LC 91.
</details>

---

**Drill 4:**
> You have a 2D grid where some cells have positive values and others are negative. Find the minimum initial health to traverse from top-left to bottom-right, reaching each cell with health > 0 at all times.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** DP from bottom-right to top-left (reverse memoization)
**Reason:** dp[r][c] = minimum health needed to enter (r,c) and reach the exit. dp[rows-1][cols-1] = max(1, 1-grid[r][c]). For other cells: dp[r][c] = max(1, min(dp[r+1][c], dp[r][c+1]) - grid[r][c]). Fill bottom-right to top-left. LC 174.
</details>

---

**Drill 5:**
> Count ways to tile a 2×n grid with 2×1 dominoes.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** 1D DP (Fibonacci-like)
**Reason:** dp[n] = ways to tile 2×n. Place domino vertically in column n: remaining is 2×(n-1) → dp[n-1]. Place two dominoes horizontally in columns n-1,n: remaining is 2×(n-2) → dp[n-2]. So dp[n] = dp[n-1] + dp[n-2] (Fibonacci). dp[0]=1, dp[1]=1. LC 509 variant.
</details>

---

## 8. Complexity Cheatsheet

| Problem | States | Work/State | Total |
|---------|--------|------------|-------|
| Out of Boundary | O(m×n×maxMove) | O(1) | O(m×n×maxMove) |
| Knight Probability | O(n²×k) | O(1) | O(n²×k) |
| Stone Game III | O(n) | O(1) | O(n) |
| Mountain Removals | O(n) for LIS | O(n) | O(n²) |
| Fibonacci | O(n) | O(1) | O(n) |

---

## 9. Common Follow-up Questions

1. When to use top-down vs bottom-up? (Top-down: complex state, natural recursion, sparse subproblems. Bottom-up: linear DP, space optimization possible, no stack overflow risk)
2. How to handle circular dependencies in memoization? (They shouldn't exist in pure DP — if present, the problem has cycles and needs a different approach. Use DFS cycle detection first)
3. Stack overflow for deep recursion? (Convert to iterative bottom-up, or use explicit stack with loop. For Python: sys.setrecursionlimit; for C++: risk is lower but exists)
4. Can you always convert top-down to bottom-up? (Yes — any memoized recursion can be rewritten as tabulation. The challenge is finding the correct fill order and handling all dependencies)

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| All DP patterns | Top-down is alternative formulation | Any DP problem |
| Game Theory | Minimax with memoization | 1406. Stone Game III |
| DFS | Top-down DP on DAG/tree | 329. LIP (P40) |
| Complex State | When state encodes many variables | Bitmask DP top-down |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
