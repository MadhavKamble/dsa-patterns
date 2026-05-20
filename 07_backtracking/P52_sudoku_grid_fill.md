# P52 — Grid Fill and Constraint Satisfaction

## 1. First-Timer Explanation

### What Is It?
**Grid fill / constraint satisfaction** backtracking fills a grid cell by cell, checking constraints at each step. The canonical examples are Sudoku (9×9 with row/col/box constraints) and crossword-style fill problems. The key insight: **fail fast** — check validity before recursing, not after.

### Analogy
Filling a crossword puzzle: you place letters one by one, checking every cross-word still makes valid words. When stuck (no valid letter for a cell), erase and backtrack. The "constraint check" is the crossword dictionary; "fail fast" means checking as soon as you place, not after filling everything.

### Core Techniques

**1. Find Next Empty Cell First**
```cpp
for (int r = 0; r < 9; r++)
    for (int c = 0; c < 9; c++)
        if (board[r][c] == '.') { /* fill this cell */ }
```

**2. Pre-built Constraint Sets**
Instead of scanning rows/cols/boxes per attempt:
```cpp
bool rowUsed[9][10], colUsed[9][10], boxUsed[9][10];
// O(1) validity check
```

**3. Constraint Propagation (MRV Heuristic)**
Pick the cell with the FEWEST valid choices first. Drastically reduces backtracking.

### When to Use
- "Solve Sudoku" / "valid Sudoku"
- "Fill crossword"
- "Color graph with k colors" (coloring = constraint fill)
- "Latin squares"

### Common Mistakes
1. Checking validity by scanning (O(n)) instead of maintaining sets (O(1))
2. Not restoring constraint sets when backtracking
3. Not returning `true` when a valid fill is found (for find-any-solution problems)

---

## 2. Revision Card

**Recognition Signal:** "fill grid with constraints", "solve puzzle", "valid placement"

**Core Idea:** Find next empty cell. Try each valid value. Update constraint sets. Recurse. Undo on backtrack. Return true when grid is full.

**Trigger Keywords:** Sudoku, fill, valid, constraint, grid, place

**Complexity:** O(k^(empty cells)) where k = number of choices per cell

---

## 3. Interview Tell Signs

- "Solve Sudoku" → classic grid fill
- "Valid Sudoku" → validation only, no backtracking
- "Map coloring" / "graph k-coloring" → backtracking on nodes
- "N×N Latin square" → similar to Sudoku without box constraint

---

## 4. C++ Template

```cpp
#include <vector>
using namespace std;

// ── Sudoku Solver with Bitset Constraints ────────────────────────────────────
class SudokuSolver {
    bool rowUsed[9][10] = {}, colUsed[9][10] = {}, boxUsed[9][10] = {};
    
    int boxIdx(int r, int c) { return (r/3)*3 + c/3; }
    
    bool canPlace(int r, int c, int d) {
        return !rowUsed[r][d] && !colUsed[c][d] && !boxUsed[boxIdx(r,c)][d];
    }
    
    void place(vector<vector<char>>& board, int r, int c, char d, bool val) {
        int digit = d - '0';
        rowUsed[r][digit] = colUsed[c][digit] = boxUsed[boxIdx(r,c)][digit] = val;
        board[r][c] = val ? d : '.';
    }
    
public:
    bool solve(vector<vector<char>>& board) {
        for (int r = 0; r < 9; r++)
            for (int c = 0; c < 9; c++)
                if (board[r][c] != '.')
                    place(board, r, c, board[r][c], true);
        
        return dfs(board);
    }
    
    bool dfs(vector<vector<char>>& board) {
        for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++) {
                if (board[r][c] != '.') continue;
                for (char d = '1'; d <= '9'; d++) {
                    if (!canPlace(r, c, d)) continue;
                    place(board, r, c, d, true);
                    if (dfs(board)) return true;
                    place(board, r, c, '.', false);
                    board[r][c] = '.'; // explicit restore
                }
                return false; // no digit works
            }
        }
        return true; // all cells filled
    }
};
```

---

## 5. How to Present in Interview

**Verbal Script:**
> "I'll scan the grid left-to-right, top-to-bottom for the first empty cell. I try digits 1-9, checking validity in O(1) using three boolean arrays: one per row, one per column, one per 3×3 box (indexed by (row/3)*3 + col/3). If a digit is valid, I place it, update the arrays, recurse. If the recursive call succeeds, return true. Otherwise, undo and try the next digit. If none work, return false (triggers backtracking)."

**Checklist:**
- [ ] Initialize constraint sets from pre-filled cells
- [ ] O(1) validity check using boolean arrays
- [ ] Place + mark → recurse → unplace + unmark on backtrack
- [ ] Return false when no digit works (propagates backtrack)
- [ ] Return true when all cells filled

---

## 6. Problems

### Problem 1: Sudoku Solver
**Difficulty:** Hard | **LC:** 37

```cpp
void solveSudoku(vector<vector<char>>& board) {
    bool row[9][10]={}, col[9][10]={}, box[9][10]={};
    // Initialize from pre-filled
    for (int r = 0; r < 9; r++)
        for (int c = 0; c < 9; c++)
            if (board[r][c] != '.') {
                int d = board[r][c]-'0', b=(r/3)*3+c/3;
                row[r][d]=col[c][d]=box[b][d]=true;
            }
    
    function<bool()> solve = [&]() -> bool {
        for (int r = 0; r < 9; r++) for (int c = 0; c < 9; c++) {
            if (board[r][c] != '.') continue;
            int b = (r/3)*3+c/3;
            for (int d = 1; d <= 9; d++) {
                if (row[r][d]||col[c][d]||box[b][d]) continue;
                board[r][c]='0'+d; row[r][d]=col[c][d]=box[b][d]=true;
                if (solve()) return true;
                board[r][c]='.'; row[r][d]=col[c][d]=box[b][d]=false;
            }
            return false;
        }
        return true;
    };
    solve();
}
// Time: O(9^81) theoretical, heavily pruned | Space: O(81)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: Valid Sudoku
**Difficulty:** Medium | **LC:** 36

**Approach:** Validation only. Check each row, column, and box for duplicates.

```cpp
bool isValidSudoku(vector<vector<char>>& board) {
    bool row[9][9]={}, col[9][9]={}, box[9][9]={};
    for (int r = 0; r < 9; r++) for (int c = 0; c < 9; c++) {
        if (board[r][c] == '.') continue;
        int d = board[r][c]-'1', b=(r/3)*3+c/3;
        if (row[r][d]||col[c][d]||box[b][d]) return false;
        row[r][d]=col[c][d]=box[b][d]=true;
    }
    return true;
}
// Time: O(81) = O(1) | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Graph Coloring (M-Coloring Problem)
**Difficulty:** Medium (classical)

**Approach:** Assign color to each vertex. Check no adjacent vertex has same color. Backtrack if stuck.

```cpp
bool graphColoring(vector<vector<int>>& adj, int n, int m) {
    vector<int> color(n, 0);
    
    function<bool(int)> dfs = [&](int v) -> bool {
        if (v == n) return true;
        for (int c = 1; c <= m; c++) {
            bool safe = true;
            for (int u : adj[v]) if (color[u] == c) { safe = false; break; }
            if (!safe) continue;
            color[v] = c;
            if (dfs(v + 1)) return true;
            color[v] = 0;
        }
        return false;
    };
    
    return dfs(0);
}
// Time: O(m^n) | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Zuma Game
**Difficulty:** Hard | **LC:** 488

**Approach:** Backtracking + memoization. At each step, try inserting 1-2 balls to eliminate runs.

```cpp
int findMinStep(string board, string hand) {
    unordered_map<string, int> cnt;
    for (char c : hand) cnt[string(1,c)]++;
    
    // Remove consecutive groups of 3+
    auto clean = [](string s) {
        bool changed = true;
        while (changed) {
            changed = false;
            for (int i = 0; i < (int)s.size(); ) {
                int j = i;
                while (j < (int)s.size() && s[j] == s[i]) j++;
                if (j - i >= 3) { s.erase(i, j-i); changed = true; }
                else i = j;
            }
        }
        return s;
    };
    
    unordered_map<string, int> memo;
    function<int(string, unordered_map<string,int>&)> dfs =
        [&](string board, unordered_map<string,int>& hand) -> int {
        if (board.empty()) return 0;
        string key = board;
        for (auto& [c,f] : hand) key += c + to_string(f);
        if (memo.count(key)) return memo[key];
        
        int res = INT_MAX;
        for (int i = 0; i < (int)board.size(); ) {
            int j = i;
            while (j < (int)board.size() && board[j] == board[i]) j++;
            int need = 3 - (j - i);
            string color(1, board[i]);
            if (hand.count(color) && hand[color] >= need) {
                hand[color] -= need;
                string next = clean(board.substr(0,i) + board.substr(j));
                int sub = dfs(next, hand);
                if (sub != INT_MAX) res = min(res, sub + need);
                hand[color] += need;
            }
            i = j;
        }
        return memo[key] = res;
    };
    
    int ans = dfs(board, cnt);
    return ans == INT_MAX ? -1 : ans;
}
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** In Sudoku solver, why does returning `false` from the inner loop trigger backtracking?
<details><summary>Reveal</summary>
When no digit 1-9 works for the current empty cell, the function returns false. The caller (the previous recursive call) sees false, undoes its last placement (backtracks), and tries the next digit. This propagates until a valid configuration is found or all possibilities are exhausted.
</details>

**Drill 2:** What's the box index formula for Sudoku?
<details><summary>Reveal</summary>
`box_idx = (row/3)*3 + (col/3)`. Boxes 0-8 map as: top-left 3×3 = box 0, top-middle = box 1, ..., bottom-right = box 8. The formula groups rows 0-2, 3-5, 6-8 by dividing by 3.
</details>

**Drill 3:** Graph coloring: n=3 nodes in a triangle (complete graph K3). Minimum colors needed?
<details><summary>Reveal</summary>
3. Each node is adjacent to both others. First node: any color. Second: different from first. Third: different from both → needs a third color. Chromatic number of K3 = 3.
</details>

**Drill 4:** What makes the Sudoku constraint sets O(1) better than scanning?
<details><summary>Reveal</summary>
Scanning the row to check if digit d is valid: O(9) per check. With boolean array `row[r][d]`, it's O(1). For 81 cells × 9 digits = 729 checks per fill, this matters. Also, sets are updated incrementally — O(1) to mark/unmark — vs O(9) to scan after each placement.
</details>

**Drill 5:** What is the MRV (Minimum Remaining Values) heuristic in Sudoku?
<details><summary>Reveal</summary>
Instead of filling cells left-to-right, pick the empty cell with the fewest valid digit choices. A cell with only 1 valid digit must be filled that way — no branching. This dramatically reduces the search tree (from ~O(9^81) to much smaller in practice).
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Space |
|---------|------|-------|
| Valid Sudoku | O(1) (fixed 81 cells) | O(1) |
| Sudoku Solver | O(9^81) theoretical | O(1) |
| Graph k-coloring | O(k^n) | O(n) |
| N-Queens (related) | O(N!) | O(N) |

---

## 9. Common Follow-up Questions

**Q: How would you speed up Sudoku with constraint propagation?**
A: After placing a digit, eliminate it from candidates in the same row, column, and box. If any cell has 0 candidates, return false immediately. If a cell has exactly 1 candidate, place it and propagate again. This is "arc consistency" / "naked singles" from Sudoku theory.

**Q: Is graph k-coloring NP-complete?**
A: For k ≥ 3, yes. For k = 1, trivial (no edges). For k = 2, bipartite check (polynomial).

**Q: Dancing Links / Algorithm X?**
A: Knuth's exact cover algorithm solves Sudoku, N-Queens, and similar in very competitive time. Represents the problem as a binary matrix; Dancing Links is an efficient doubly-linked list implementation.

---

## 10. Cross-Pattern Connections

- **P48 (N-Queens):** Same constraint backtracking structure
- **P49 (Word Search):** Grid backtracking with mark/restore
- **P20 (Cycle Detection/Bipartite):** 2-coloring = bipartite check
- **P21 (Topological Sort):** Scheduling with constraints; different constraint structure
