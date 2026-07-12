# 🗂️ Recursion — Master Revision Sheet (Step 7, P01–P24)

> **One-stop revision.** Each entry = 📖 **Problem** (what's asked + tiny example) + 🧾 **Recall** (the trigger) + 🔧 **Algorithm/idea** + ⚠️ **Trap**.
> Go top-to-bottom the night before an interview; every recursion problem in this step is here.

---

## ⚡ 60-Second Index

| # | Problem | LC | Pattern | Time / Space |
|---|---------|----|---------|--------------|
| P01 | Recursive atoi | 8 | Parameterized tail recursion | O(N) / O(N) |
| P02 | Pow(x, n) | 50 | Binary exponentiation | O(log N) / O(log N) |
| P03 | Count Good Numbers | 1922 | Math + modular binary exp | O(log N) / O(1) |
| P04 | Sort Stack | GFG | Two-function recursive (peel+insert) | O(N²) / O(N) |
| P05 | Reverse Stack | GFG | Two-function recursive (peel+insertAtBottom) | O(N²) / O(N) |
| P06 | Binary Strings No 11 | GFG | Constrained string generation | O(Fib(n)×n) / O(n) |
| P07 | Generate Parentheses | 22 | Open/close counter guards | O(4^n/√n) / O(n) |
| P08 | Power Set | 78 | Include/exclude OR bitmask | O(2^N×N) / O(N) |
| P09 | Count Subsequences Sum K | GFG | Include/exclude → count (+) | O(2^N) / O(N) |
| P10 | Check Subsequence Sum K | GFG | Include/exclude → exists (\|\|) | O(2^N) / O(N) |
| P11 | Combination Sum I | 39 | Backtrack loop, stay at idx (reuse) | O(k×2^t) / O(t) |
| P12 | Combination Sum II | 40 | Backtrack loop, i+1, dup skip | O(2^N) / O(N) |
| P13 | Subset Sums I | GFG | Include/exclude, carry sum as int | O(2^N×N) / O(N) |
| P14 | Subsets II | 90 | Push-on-entry + dup skip | O(2^N×N) / O(N) |
| P15 | Combination Sum III | 216 | Fixed pool 1–9, double base case | O(C(9,k)×k) / O(k) |
| P16 | Letter Combinations | 17 | Digit→letters map, recurse idx+1 | O(4^N×N) / O(N) |
| P17 | Palindrome Partitioning | 131 | Partition loop + isPalin check | O(2^N×N) / O(N) |
| P18 | Word Search | 79 | DFS + in-place '#' mark + restore | O(M×N×4^L) / O(L) |
| P19 | N-Queens | 51 | Column-by-column + 3 hash arrays | O(N!) / O(N) |
| P20 | Rat in a Maze | GFG | DFS + visited[][] + D/L/R/U order | O(4^N²) / O(N²) |
| P21 | Word Break | 139 | Partition loop + dict lookup + memo | O(N³) / O(N) |
| P22 | M Coloring Problem | GFG | Node-by-node, try 1→M colors | O(M^N×N) / O(N) |
| P23 | Sudoku Solver | 37 | Find '.' + try '1'→'9' + row/col/box valid | O(9^empty) / O(1) |
| P24 | Expression Add Operators | 282 | DFS on splits + mul trick (last_operand) | O(N×4^N) / O(N) |

---

## 🧩 Pattern Toolbox (techniques that repeat)

- **Include/Exclude** (P08–P10, P13): two branches at each index — take or skip. Base case determines return: 1/0 for count, true/false for check, push for print. Combine with `+` / `||` / collect accordingly.
- **Backtracking loop** (P11–P17): `for i=idx; push arr[i]; recurse(i+1); pop`. Use `i` (not `i+1`) to allow unlimited reuse (P11). Use `i > idx && arr[i]==arr[i-1]` to skip dups (P12, P14).
- **Push-on-entry vs push-at-base**: collecting at entry = all subsets including partial (P14). Collecting at base = only complete combinations (P11, P12, P17).
- **In-place mark + restore** (P18, P20): mark cell `'#'` or `visited=1` BEFORE recursing, unmark AFTER all directions tried. The restore IS the backtrack.
- **Binary exponentiation** (P02, P03): `half=f(n/2); half*half [×x if odd]`. Compute once, reuse — calling twice undoes the O(log N) gain.
- **Two-function stack recursion** (P04, P05): `peel` function (main) + `reinsert` helper. Helper tunnels through the stack, restores elements on way up.
- **Hash arrays for O(1) conflict** (P19): `leftRow[r]`, `lowerDiag[r+c]`, `upperDiag[n-1+c-r]`. Diagonal key derivation: `row+col` is constant along ↙; `col-row` is constant along ↖.
- **Last-operand tracking** (P24): carry `last_operand` to undo multiplication — `val - last + last * curr`. After `-c`: `last = -c` for chained multiply.

---

## 📒 Problem-by-Problem

### P01 — Recursive atoi  ·  O(N)/O(N)
- 📖 **Problem:** Convert a string to integer recursively — skip spaces, read sign, then recurse digit-by-digit. `"   -42abc"` → `-42`.
- 🧾 **Recall:** Replace `while(isdigit)` loop with `solve(i+1, sign, num*10+digit)`. Check overflow BEFORE multiplying: `num > (INT_MAX - digit) / 10`.
- 🔧 **Algorithm:** `myAtoi`: skip spaces, read sign, call `solve(i, sign, 0)`. `solve`: base = non-digit/end → `sign*num`. Digit: overflow check → recurse with `num*10+digit`.
- ⚠️ Pass `string&` (reference) — not by value, avoids copying on every frame. Pass `num` as `long long`. Use `(size_t)` cast when comparing index to `s.size()`.

### P02 — Pow(x, n)  ·  O(log N)/O(log N)
- 📖 **Problem:** Implement `pow(x, n)` efficiently. `x=2.0, n=10` → `1024.0`. `n=-2` → `0.25`.
- 🧾 **Recall:** `half = helper(x, n/2)`. Even: `half*half`. Odd: `half*half*x`. Negative: invert x and negate N (using `long`).
- 🔧 **Algorithm:** `myPow`: if `n<0`, `x=1/x`, `N=-N` (as `long`). Call `helper(x, N)`. `helper`: base `n==0→1`. Compute `half` once, return `half*half` or `half*half*x`.
- ⚠️ `long N=n` is non-negotiable — `INT_MIN` negation overflows `int`. Calling `helper(x,n/2)` TWICE defeats the O(log N) purpose.

### P03 — Count Good Numbers  ·  O(log N)/O(1)
- 📖 **Problem:** Count strings of length n where even positions have even digits and odd positions have prime digits. Answer mod 10⁹+7. `n=4` → `400`.
- 🧾 **Recall:** Even positions (0,2,4…): 5 choices. Odd (1,3,5…): 4 choices. Answer = `5^⌈n/2⌉ × 4^⌊n/2⌋ % MOD`. Use binary exp for n up to 10¹⁵.
- 🔧 **Algorithm:** `evenCount=(n+1)/2`, `oddCount=n/2`. `power(x,n)`: `while(n>0){ if(n&1) res=(res*x)%MOD; x=(x*x)%MOD; n>>=1; }`.
- ⚠️ `%MOD` after every multiplication inside the loop. Final `evenWays*oddWays` also needs `%MOD`. `n&1` is faster than `n%2`.

### P04 — Sort Stack using Recursion  ·  O(N²)/O(N)
- 📖 **Problem:** Sort a stack (largest on top) using only recursion — no loops, no extra data structure. `[4,1,3,2]` → `[1,2,3,4]` (top=4).
- 🧾 **Recall:** `sortStack` = peel top → sort rest → `insert(top)`. `insert` = if empty or `top ≤ temp` push; else pop top, recurse deeper, push top back.
- 🔧 **Algorithm:** `sortStack(s)`: if not empty → `temp=pop`, `sortStack(s)`, `insert(s,temp)`. `insert(s,temp)`: if `s.empty() || s.top()<=temp` → `push(temp)`; else `val=pop`, `insert(s,temp)`, `push(val)`.
- ⚠️ Condition is `<=` not `<` — equal elements must not infinitely recurse. Check `s.empty()` BEFORE `s.top()` in the combined condition.

### P05 — Reverse Stack using Recursion  ·  O(N²)/O(N)
- 📖 **Problem:** Reverse a stack using only recursion — no extra DS. `[4,1,3,2]` (top=2) → `[2,3,1,4]` (top=4).
- 🧾 **Recall:** `reverseStack` = peel top → reverse rest → `insertAtBottom(top)`. `insertAtBottom` = pop all, push val, restore all.
- 🔧 **Algorithm:** `reverseStack(st)`: if not empty → `topVal=pop`, `reverseStack(st)`, `insertAtBottom(st,topVal)`. `insertAtBottom(st,val)`: if `st.empty()` → `push(val)`; else `topVal=pop`, `insertAtBottom(st,val)`, `push(topVal)`.
- ⚠️ Mirror of P04 — only the helper changes. Forgetting `push(topVal)` in `insertAtBottom` drops elements.

### P06 — Binary Strings without Consecutive 1s  ·  O(Fib(n)×n)/O(n)
- 📖 **Problem:** Generate all binary strings of length n with no two consecutive `'1'`s. `n=3` → `000 001 010 100 101`.
- 🧾 **Recall:** Always branch `'0'`. Branch `'1'` only if `curr.empty() || curr.back() != '1'`. Base: `curr.length() == n`.
- 🔧 **Algorithm:** `generate(n, curr, result)`: if `len==n → push`. Call `generate(n, curr+"0")`. If `curr.empty() || curr.back()!='1'` → call `generate(n, curr+"1")`.
- ⚠️ Check `curr.empty()` before `curr.back()` — calling `back()` on empty string is UB.

### P07 — Generate Parentheses  ·  O(4^n/√n)/O(n)
- 📖 **Problem:** Generate all valid combinations of n pairs of parentheses. `n=3` → 5 strings.
- 🧾 **Recall:** Two rules: add `'('` if `open < n`; add `')'` if `close < open`. Base: `len == 2n`.
- 🔧 **Algorithm:** `backtrack(curr, open, close, n, res)`: base `len==2n → push`. If `open<n` → recurse `+('(', open+1)`. If `close<open` → recurse `+(')', close+1)`.
- ⚠️ `close < open` (not `<=`) — at balance point must open, not close. Count is Catalan(n).

### P08 — Power Set / All Subsequences  ·  O(2^N×N)/O(N)
- 📖 **Problem:** Generate all subsequences (including empty) of a string. `"abc"` → 8 strings.
- 🧾 **Recall:** **Include/exclude:** at each index, exclude (recurse) then include (push, recurse, pop_back). OR **bitmask**: for each mask `0 → 2^n-1`, include char if bit `i` set.
- 🔧 **Algorithm (recursion):** `helper(s, idx, curr, result)`: base `idx==n → push curr`. `helper(idx+1, curr)` (exclude). `curr.push_back(s[idx]); helper(idx+1, curr); curr.pop_back()` (include).
- ⚠️ Exclude branch comes BEFORE include → empty string generated first. `curr` must be passed by reference with `pop_back` for O(N) space — by value copies entire string each call.

### P09 — Count Subsequences with Sum K  ·  O(2^N)/O(N)
- 📖 **Problem:** Count how many subsequences of the array sum to K. `[1,2,3,4,5], K=5` → 3 (`{1,4},{2,3},{5}`).
- 🧾 **Recall:** Include/exclude tree. Check `sum==0 → return 1` FIRST. Then `sum<0 || ind==n → return 0`. Combine with `+`.
- 🔧 **Algorithm:** `func(ind, sum)`: if `sum==0 → 1`. if `sum<0 || ind==n → 0`. return `func(ind+1, sum-arr[ind]) + func(ind+1, sum)`.
- ⚠️ `sum==0` before `ind==n` — enables early exit for positive arrays (remaining elements can only increase sum). Remove `sum<0` prune for arrays with negative elements.

### P10 — Check if Subsequence with Sum K Exists  ·  O(2^N)/O(N)
- 📖 **Problem:** Does any subsequence sum to K? `[1,2,3,4], K=5` → true.
- 🧾 **Recall:** Same tree as P09. Base `ind==n → return sum==0`. Combine with `||` (not `|`) for short-circuit.
- 🔧 **Algorithm:** `func(ind, sum)`: if `ind==n → sum==0`. return `func(ind+1, sum-arr[ind]) || func(ind+1, sum)`.
- ⚠️ `|` (bitwise OR) evaluates both branches always — use `||` to stop on first found. Optionally add `sum<0 → return false` early exit for positive arrays.

### P11 — Combination Sum I  ·  O(k×2^t)/O(t)
- 📖 **Problem:** All combinations from distinct candidates that sum to target; each number usable unlimited times. `[2,3,6,7], t=7` → `[[2,2,3],[7]]`.
- 🧾 **Recall:** Include: `arr[idx] ≤ target → push, recurse(idx, target-arr[idx]), pop`. Exclude: `recurse(idx+1, target)`. Key: recurse with `idx` (same) to allow reuse.
- 🔧 **Algorithm:** `findCombination(idx, target, arr, ans, ds)`: base `idx==n && target==0 → push ds`. If `arr[idx]<=target`: push, `recurse(idx, target-arr[idx])`, pop. Always: `recurse(idx+1, target)`.
- ⚠️ `idx` (not `idx+1`) in the include branch is the ONLY structural difference from P08. `arr[idx]<=target` guard prevents infinite recursion from a repeating element.

### P12 — Combination Sum II  ·  O(2^N)/O(N)
- 📖 **Problem:** Array may have duplicates; each element used at most once; return unique combinations summing to target. Sort + dup skip required. `[10,1,2,7,6,1,5], t=8` → `[[1,1,6],[1,2,5],[1,7],[2,6]]`.
- 🧾 **Recall:** Sort. `for i=idx to n-1`: skip `i>idx && arr[i]==arr[i-1]`. Break `arr[i]>target`. Push, `recurse(i+1, target-arr[i])`, pop.
- 🔧 **Algorithm:** Sort. `findCombination(idx, target)`: base `target==0 → push`. Loop i=idx→n: skip dup; break on `arr[i]>target`; push `arr[i]`; recurse `(i+1, target-arr[i])`; pop.
- ⚠️ `i > idx` NOT `i > 0` — allows using same value at deeper recursion levels. `break` not `continue` when `arr[i]>target` (sorted → all remaining also too large).

### P13 — Subset Sums I  ·  O(2^N×N)/O(N)
- 📖 **Problem:** Find the sum of every possible subset. Return sorted. `[5,2,1]` → `[0,1,2,3,5,6,7,8]`.
- 🧾 **Recall:** Include/exclude but carry sum as an `int` parameter. Base `idx==n → push currentSum`. No `pop_back` needed — int passed by value.
- 🔧 **Algorithm:** `findSums(idx, currentSum)`: if `idx==n → push currentSum`. `findSums(idx+1, currentSum+arr[idx])`. `findSums(idx+1, currentSum)`. Sort result.
- ⚠️ `currentSum` by value = no backtrack needed. If passed by reference, you'd need `+=` and `-=` like a vector element.

### P14 — Subsets II  ·  O(2^N×N)/O(N)
- 📖 **Problem:** Array with duplicates — return all unique subsets. `[1,2,2]` → 6 subsets including `[1,2,2]`.
- 🧾 **Recall:** Sort. Push `current` to result **on entry** (every prefix is a valid subset). Loop i=idx→n: skip `i>idx && nums[i]==nums[i-1]`; push; `recurse(i+1)`; pop.
- 🔧 **Algorithm:** `backtrack(idx)`: `result.push_back(current)` (this line is what changes vs P12). Loop with same dup skip and `i+1`.
- ⚠️ "Push on entry" not "push at base" — difference from LC 78 (no dups) is just the one dup-skip `continue` line. `i > idx` same rule as P12.

### P15 — Combination Sum III  ·  O(C(9,k)×k)/O(k)
- 📖 **Problem:** Find all k-number combinations from digits 1–9 summing to n, each digit once. `k=3, n=7` → `[[1,2,4]]`.
- 🧾 **Recall:** Loop `i=start to 9`. Success: `ds.size()==k && target==0`. Fail: `ds.size()>k || target<0`. If `i<=target`: push, recurse `(i+1,k,target-i)`, pop. Else: `break`.
- 🔧 **Algorithm:** `backtrack(start, k, target, ds, ans)`: check success, check fail. Loop i=start→9: if `i<=target` → push/recurse/pop; else break.
- ⚠️ Fixed pool 1–9 — loop to `9`, not to `n-1`. Two separate base cases: success AND failure. Failure prune `size>k` avoids over-picking even if target not hit.

### P16 — Letter Combinations of Phone Number  ·  O(4^N×N)/O(N)
- 📖 **Problem:** Given digit string (2–9), return all letter combinations from phone keypad. `"23"` → 9 strings.
- 🧾 **Recall:** `combos[digit-'0']` maps digit to letters. At each `idx`, loop over letters, recurse with `idx+1`. Base `idx==size → push`. Guard `digits.empty() → return {}`.
- 🔧 **Algorithm:** `func(idx, digits, s, ans, combos)`: base `idx==size → push s`. `digit=digits[idx]-'0'`. For each char in `combos[digit]`: `func(idx+1, digits, s+char, ans, combos)`.
- ⚠️ Without empty guard, `digits=""` pushes `""` instead of returning `{}`. Passing `s` by value avoids explicit backtrack — each call has its own copy.

### P17 — Palindrome Partitioning  ·  O(2^N×N)/O(N)
- 📖 **Problem:** Partition string so every substring is a palindrome; return all partitionings. `"aab"` → `[["a","a","b"],["aa","b"]]`.
- 🧾 **Recall:** Loop `end=start→n`. If `isPalindrome(start,end)`: push `substr(start, end-start+1)`, `recurse(end+1)`, pop. Base `start==n → push curr`.
- 🔧 **Algorithm:** Same loop skeleton as P12 (Combination Sum II) but condition is `isPalin` not dup-check. `isPalindrome(s,l,r)`: two-pointer.
- ⚠️ `s.substr(start, end-start+1)` — length is `end-start+1`, NOT `end`. Optimize: precompute `dp[i][j]` in O(N²) for O(1) palindrome checks.

### P18 — Word Search  ·  O(M×N×4^L)/O(L)
- 📖 **Problem:** Find if a word exists in a grid of characters using adjacent cells (up/down/left/right), each cell at most once. `board` with "ABCCED" → `true`.
- 🧾 **Recall:** DFS from every cell matching `word[0]`. In `dfs(i,j,idx)`: base `idx==len→true`. Guard OOB or `board[i][j]!=word[idx]`. Mark `'#'`, explore 4 dirs with `idx+1`, restore, return found.
- 🔧 **Algorithm:** Outer loop tries all start cells. `dfs`: `char temp=board[i][j]; board[i][j]='#'; bool found=dfs(4 dirs); board[i][j]=temp; return found`.
- ⚠️ Mark before the 4-dir OR, not after — without it a cell can revisit itself. `||` short-circuits — stops exploring once any direction returns true.

### P19 — N-Queens  ·  O(N!)/O(N)
- 📖 **Problem:** Place N non-attacking queens on N×N board. Return all solutions. `n=4` → 2 solutions.
- 🧾 **Recall:** One queen per column. **Optimal:** `leftRow[row]`, `lowerDiag[row+col]`, `upperDiag[n-1+col-row]` — O(1) conflict check. Mark all 3, recurse col+1, unmark 3.
- 🔧 **Algorithm:** `solve(col)`: base `col==n → push board`. For each row: if all 3 arrays are 0 → place queen, mark, recurse, unmark, reset.
- ⚠️ Array size for diagonals is `2n-1` (not n). `upperDiag[n-1+col-row]` not `n+col-row`. Forgetting to reset any of the 3 arrays = wrong subsequent placements.

### P20 — Rat in a Maze  ·  O(4^N²)/O(N²)
- 📖 **Problem:** Find all paths from `(0,0)` to `(n-1,n-1)` in a binary grid, using D/L/R/U. Return paths in lexicographic order.
- 🧾 **Recall:** `isSafe`: in-bounds + `maze[x][y]==1` + `visited[x][y]==0`. Mark `visited=1`, try D/L/R/U, unmark `visited=0`. Base: reach `(n-1,n-1) → push path`.
- 🔧 **Algorithm:** `solve(x,y,path)`: base `x==n-1&&y==n-1 → push`. `visited[x][y]=1`. Try 4 dirs in D/L/R/U order (gives lex output). `visited[x][y]=0`.
- ⚠️ D/L/R/U order — `'D'<'L'<'R'<'U'` alphabetically — naturally produces lex order without extra sort. Guard `maze[0][0]==1` before starting.

### P21 — Word Break  ·  O(N³)/O(N)
- 📖 **Problem:** Can string `s` be segmented into dictionary words? `s="leetcode", dict=["leet","code"]` → true.
- 🧾 **Recall:** Loop `end=start+1→n`. If `dict.has(s[start..end])` and `solve(end)` → true. Base `start==n → true`. Memoize on `start` (N unique states).
- 🔧 **Algorithm:** Build `unordered_set`. `solve(start, memo)`: base `start==n → true`. Check `memo[start]`. Loop end=start+1→n: `dict.count(substr) && solve(end) → memo[start]=1`. `memo[start]=0`.
- ⚠️ Same partition-loop structure as P17 — condition is `dict.count` instead of `isPalindrome`. Without memoization: exponential. `substr(start, end-start)` length is `end-start`.

### P22 — M Coloring Problem  ·  O(M^N×N)/O(N)
- 📖 **Problem:** Can an undirected graph be colored with at most M colors so no two adjacent nodes share a color? `N=4, M=3, 5 edges` → true.
- 🧾 **Recall:** Node by node. Try colors 1→M. `isSafe`: no adjacent node (in graph) has the same color. Assign, recurse(node+1), backtrack (color=0). Base `node==N → true`.
- 🔧 **Algorithm:** `solve(node)`: base `node==N→true`. Loop i=1→m: `isSafe(node,i)` → `color[node]=i`; if `solve(node+1)→true`; `color[node]=0`. Return false.
- ⚠️ Colors start from 1 — 0 means "unassigned", avoids false conflicts. Must reset `color[node]=0` after failed recursion.

### P23 — Sudoku Solver  ·  O(9^empty)/O(1)
- 📖 **Problem:** Fill a 9×9 Sudoku board (`.` = empty) so every row, column, and 3×3 box has digits 1–9 exactly once.
- 🧾 **Recall:** Find first `'.'`. Try `'1'→'9'`. `isValid`: scan row + scan col + scan 3×3 box (start `3*(row/3), 3*(col/3)`). Place, recurse → if false: `board[i][j]='.'` (backtrack). No `'.'` found → return true.
- 🔧 **Algorithm:** `solveSudoku()`: nested loop finds first `'.'`. Try each char: if `isValid → place, recurse`. If recursion false → `board[i][j]='.'`. If no char works → `return false`. If loop completes → `return true`.
- ⚠️ `return false` inside the `if(board[i][j]=='.')` block triggers parent backtrack. Box indices: `3*(row/3)` not `row/3`.

### P24 — Expression Add Operators  ·  O(N×4^N)/O(N)
- 📖 **Problem:** Insert `+`, `-`, `*` between digits to get expressions evaluating to target. `"123", t=6` → `["1+2+3","1*2*3"]`.
- 🧾 **Recall:** DFS on all number-splits from `start`. First number: no operator. Else: try `+`, `-`, `*`. **Mul trick:** `new_val = val - last + last*cur; new_last = last*cur`. After `-c`: `last = -c`.
- 🔧 **Algorithm:** `dfs(start, val, last, expr)`: base `start==n && val==target → push`. Loop i=start→n: leading zero guard (`i>start && num[start]=='0' → return`). Extract `curr_num`. `+`: `(val+cur, +cur)`. `-`: `(val-cur, -cur)`. `*`: `(val-last+last*cur, last*cur)`.
- ⚠️ Leading zero: `return` (not `continue`) — prunes entire branch. Use `long long` throughout. First number case (`start==0`) must be handled separately to avoid inserting an operator at the front.

---

## 🗂️ Key Comparison Tables

### Combination Sum Family

| | Sum I (P11) | Sum II (P12) | Sum III (P15) |
|---|---|---|---|
| Pool | candidates[] | candidates[] (sort first) | digits 1–9 |
| Reuse | ✅ yes | ❌ no | ❌ no |
| Dups in input | ❌ no | ✅ yes | ❌ no |
| Recurse with | `idx` (same) | `i+1` | `i+1` |
| Dup skip | — | `i>idx && arr[i]==arr[i-1]` | — |
| Extra constraint | none | none | `size == k` |

### Include/Exclude Variants

| Goal | Return | Base on success | Combine |
|------|--------|-----------------|---------|
| Print all (P08) | void | push to result | — |
| Count (P09) | int | return 1 | `+` |
| Check (P10) | bool | return true | `||` |

### Grid DFS

| | Word Search (P18) | Rat in Maze (P20) |
|---|---|---|
| Mark | in-place `'#'` | `visited[][]` array |
| Restore | `board[i][j]=temp` | `visited[x][y]=0` |
| Goal | match word characters | reach destination |
| Collect | bool return | path string |

---

## ⚠️ Top Traps

| Trap | Bites at |
|------|----------|
| `i > 0` instead of `i > idx` for dup skip | P12, P14 — wrongly blocks elements at deeper levels |
| `idx` instead of `i+1` in recurse | P12 — accidentally allows reuse |
| `|` instead of `||` | P10 — no short-circuit |
| Leading zero `continue` not `return` | P24 — still tries longer numbers |
| Missing `pop_back()` | Any backtracking — state leaks between iterations |
| `sum < 0` prune on negative arrays | P09/P10 — incorrect pruning |
| `int` for large exponent/operand | P02, P24 — overflow; use `long`/`long long` |
| Mark visited after recurse | P18/P20 — cell revisits itself in same path |
| `sum==0` checked after `ind==n` | P09 — loses early-exit optimization |
| Empty `digits` not guarded | P16 — returns `[""]` instead of `[]` |
