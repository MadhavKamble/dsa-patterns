# P48 — N-Queens and Constraint Backtracking

## 1. First-Timer Explanation

### What Is It?
**Constraint backtracking** places elements one by one, checking constraints before each placement. If a constraint is violated, we skip that choice (pruning). N-Queens is the canonical example: place N queens on an N×N board so no two queens share a row, column, or diagonal.

### Analogy
Imagine placing N aggressive dogs (that attack each other) in an N-row building, one per floor, one per apartment. Each floor has N apartments. You go floor by floor: pick an apartment for the floor's dog, check it doesn't attack any dog above (same column, same diagonal). If no conflict, go to the next floor. If no apartment works, go back (backtrack) and move the dog above.

### Visual Walkthrough — N=4
```
Row 0: try col 0 → place Q at (0,0)
Row 1: try col 0 → same col, skip
       try col 1 → diagonal of (0,0), skip
       try col 2 → OK, place Q at (1,2)
Row 2: try col 0 → diagonal of (1,2), skip
       try col 1 → OK, place Q at (2,1)? No: diagonal of (0,0)? (2-0=2, 1-0=1) not equal → safe; but (2-1=1, 2-1=1) diagonal! Skip.
       try col 3 → diagonal of (1,2)? (2-1=1, 3-2=1) yes → skip
       → backtrack!
...

One solution for N=4: . Q . .
                       . . . Q
                       Q . . .
                       . . Q .
```

### Checking Diagonals Efficiently
Instead of scanning all queens, track sets:
- `cols`: which columns are occupied
- `diag1`: which "\" diagonals (row - col = constant)
- `diag2`: which "/" diagonals (row + col = constant)

### When to Use
- Placement problems with constraints
- "N-Queens", "Sudoku", "Word Search"
- Constraint satisfaction problems (CSP)
- "Count valid arrangements under rules"

### When NOT to Use
- Simple combination/permutation problems → P46/P47 simpler templates
- Counting only → sometimes DP is faster

### Common Mistakes
1. Scanning entire board for conflicts instead of using sets (slow)
2. Forgetting to remove from sets when backtracking
3. Board representation: string per row is clean for N-Queens output

---

## 2. Revision Card

**Recognition Signal:** "place N items with constraints", "valid configuration", "constraint satisfaction"

**Core Idea:** Backtracking row by row. Before placing, check if position is valid (using constraint sets). If valid: place, mark, recurse, unmark, remove.

**Trigger Keywords:** N-Queens, Sudoku, valid placement, constraint, no two, safe

**Complexity:**
| Problem | Time | Space |
|---------|------|-------|
| N-Queens | O(N!) | O(N) |
| N-Queens count only | O(N!) | O(N) |
| Sudoku solver | O(9^81) worst (but heavily pruned) | O(1) |

---

## 3. Interview Tell Signs

- "Place N items so no two conflict" → N-Queens pattern
- "Fill a grid satisfying constraints" → Sudoku-style backtracking
- "Return all valid configurations" → backtracking, record at base case
- "How many ways" → same backtracking, count++ instead of record

---

## 4. C++ Template

```cpp
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

// ── N-Queens ─────────────────────────────────────────────────────────────────
vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> res;
    vector<string> board(n, string(n, '.'));
    unordered_set<int> cols, diag1, diag2; // diag1: r-c, diag2: r+c
    
    function<void(int)> dfs = [&](int row) {
        if (row == n) { res.push_back(board); return; }
        for (int col = 0; col < n; col++) {
            if (cols.count(col) || diag1.count(row-col) || diag2.count(row+col)) continue;
            // place
            board[row][col] = 'Q';
            cols.insert(col); diag1.insert(row-col); diag2.insert(row+col);
            dfs(row + 1);
            // remove
            board[row][col] = '.';
            cols.erase(col); diag1.erase(row-col); diag2.erase(row+col);
        }
    };
    
    dfs(0);
    return res;
}

// ── Constraint check helper for Sudoku ───────────────────────────────────────
bool isValid(vector<vector<char>>& board, int r, int c, char num) {
    int box_r = (r / 3) * 3, box_c = (c / 3) * 3;
    for (int i = 0; i < 9; i++) {
        if (board[r][i] == num) return false;         // same row
        if (board[i][c] == num) return false;         // same col
        if (board[box_r + i/3][box_c + i%3] == num) return false; // same box
    }
    return true;
}
```

---

## 5. How to Present in Interview

**Verbal Script:**
> "For N-Queens, I'll go row by row. At each row, I try each column. Before placing, I check three constraints: the column isn't taken, and neither diagonal is taken. I use three hash sets tracking occupied columns, and the two diagonals (row-col is constant along \\ diagonal, row+col along / diagonal). If valid, I place the queen, mark the sets, recurse to the next row, then unmark and remove when backtracking."

**Checklist:**
- [ ] Row-by-row DFS (each row gets exactly one queen)
- [ ] Three constraint sets: cols, diag1 (r-c), diag2 (r+c)
- [ ] Backtrack: remove from all three sets + reset board cell
- [ ] Base case: row == n → record board
- [ ] For Sudoku: find next empty cell, try 1-9, validate against row/col/box

---

## 6. Problems

### Problem 1: N-Queens
**Difficulty:** Hard | **LC:** 51

**Approach:** Row-by-row backtracking with set-based conflict detection.

```cpp
vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> res;
    vector<string> board(n, string(n, '.'));
    unordered_set<int> cols, d1, d2;
    
    function<void(int)> dfs = [&](int row) {
        if (row == n) { res.push_back(board); return; }
        for (int col = 0; col < n; col++) {
            if (cols.count(col) || d1.count(row-col) || d2.count(row+col)) continue;
            board[row][col] = 'Q';
            cols.insert(col); d1.insert(row-col); d2.insert(row+col);
            dfs(row + 1);
            board[row][col] = '.';
            cols.erase(col); d1.erase(row-col); d2.erase(row+col);
        }
    };
    dfs(0);
    return res;
}
// Time: O(N!) | Space: O(N)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 2: N-Queens II (count only)
**Difficulty:** Hard | **LC:** 52

**Approach:** Same as N-Queens but count++ instead of recording the board.

```cpp
int totalNQueens(int n) {
    int count = 0;
    unordered_set<int> cols, d1, d2;
    function<void(int)> dfs = [&](int row) {
        if (row == n) { count++; return; }
        for (int col = 0; col < n; col++) {
            if (cols.count(col) || d1.count(row-col) || d2.count(row+col)) continue;
            cols.insert(col); d1.insert(row-col); d2.insert(row+col);
            dfs(row + 1);
            cols.erase(col); d1.erase(row-col); d2.erase(row+col);
        }
    };
    dfs(0);
    return count;
}
// Time: O(N!) | Space: O(N)
// Optimization: use bitmask instead of sets → 3× faster constant
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 3: Sudoku Solver
**Difficulty:** Hard | **LC:** 37

**Approach:** Find next empty cell, try digits 1-9, validate, recurse. Backtrack if stuck.

```cpp
void solveSudoku(vector<vector<char>>& board) {
    function<bool()> solve = [&]() -> bool {
        for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++) {
                if (board[r][c] != '.') continue;
                for (char d = '1'; d <= '9'; d++) {
                    if (!isValid(board, r, c, d)) continue;
                    board[r][c] = d;
                    if (solve()) return true;
                    board[r][c] = '.';
                }
                return false; // no digit works → backtrack
            }
        }
        return true; // all cells filled
    };
    solve();
}

bool isValid(vector<vector<char>>& board, int r, int c, char d) {
    int br = (r/3)*3, bc = (c/3)*3;
    for (int i = 0; i < 9; i++) {
        if (board[r][i] == d) return false;
        if (board[i][c] == d) return false;
        if (board[br+i/3][bc+i%3] == d) return false;
    }
    return true;
}
// Time: O(9^81) theoretical, heavily pruned in practice | Space: O(81)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 4: Word Search
**Difficulty:** Medium | **LC:** 79

**Approach:** DFS from each cell. Mark visited (overwrite with '#'), recurse in 4 directions, restore on backtrack.

```cpp
bool exist(vector<vector<char>>& board, string word) {
    int rows = board.size(), cols = board[0].size();
    
    function<bool(int,int,int)> dfs = [&](int r, int c, int idx) -> bool {
        if (idx == (int)word.size()) return true;
        if (r < 0 || r >= rows || c < 0 || c >= cols || board[r][c] != word[idx]) return false;
        char tmp = board[r][c];
        board[r][c] = '#'; // mark visited
        bool found = dfs(r+1,c,idx+1) || dfs(r-1,c,idx+1) ||
                     dfs(r,c+1,idx+1) || dfs(r,c-1,idx+1);
        board[r][c] = tmp; // restore
        return found;
    };
    
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            if (dfs(r, c, 0)) return true;
    return false;
}
// Time: O(rows*cols * 4^len) | Space: O(len) recursion stack
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 5: Restore IP Addresses
**Difficulty:** Medium | **LC:** 93

**Approach:** Backtracking: place 3 dots to create 4 segments. Each segment must be valid (0-255, no leading zeros).

```cpp
vector<string> restoreIpAddresses(string s) {
    vector<string> res;
    vector<string> parts;
    
    function<void(int)> dfs = [&](int start) {
        if ((int)parts.size() == 4 && start == (int)s.size()) {
            res.push_back(parts[0]+"."+parts[1]+"."+parts[2]+"."+parts[3]);
            return;
        }
        if (parts.size() == 4 || start == (int)s.size()) return;
        
        for (int len = 1; len <= 3 && start + len <= (int)s.size(); len++) {
            string seg = s.substr(start, len);
            if (len > 1 && seg[0] == '0') break; // no leading zeros
            if (stoi(seg) > 255) break;
            parts.push_back(seg);
            dfs(start + len);
            parts.pop_back();
        }
    };
    
    dfs(0);
    return res;
}
// Time: O(3^4) = O(1) — at most 3 lengths per of 4 segments | Space: O(1)
```

**My Solution:**
```
// Write your solution here
```

---

### Problem 6: Generate Parentheses
**Difficulty:** Medium | **LC:** 22

**Approach:** Constraint backtracking. At each step: add '(' if open < n; add ')' if close < open.

```cpp
vector<string> generateParenthesis(int n) {
    vector<string> res;
    string cur;
    function<void(int,int)> dfs = [&](int open, int close) {
        if ((int)cur.size() == 2 * n) { res.push_back(cur); return; }
        if (open < n) { cur += '('; dfs(open+1, close); cur.pop_back(); }
        if (close < open) { cur += ')'; dfs(open, close+1); cur.pop_back(); }
    };
    dfs(0, 0);
    return res;
}
// Time: O(C(2n,n)/n) — nth Catalan number | Space: O(n)
```

**My Solution:**
```
// Write your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:** N-Queens: why use `row-col` and `row+col` for diagonals?
<details><summary>Reveal</summary>
For '\' diagonal: all cells (r,c) where r-c is constant. For '/' diagonal: all cells where r+c is constant. These are invariants along each diagonal type, so storing them in a set detects conflicts in O(1).
</details>

**Drill 2:** Sudoku: why does returning `false` from the inner loop trigger backtracking?
<details><summary>Reveal</summary>
When no digit 1-9 works for a cell, there's no valid solution from the current board state. Returning false propagates up, causing the caller to undo the last placement and try the next digit. This is pure backtracking.
</details>

**Drill 3:** Word search: why overwrite with '#' instead of using a separate visited array?
<details><summary>Reveal</summary>
Space efficiency. The board already exists; overwriting temporarily is O(1) extra space. A separate visited array would be O(rows*cols) per call. Both work, but in-place is cleaner and common in interviews.
</details>

**Drill 4:** Generate parentheses: what's the constraint that prevents invalid strings?
<details><summary>Reveal</summary>
Two rules: (1) never exceed n open brackets; (2) never add ')' unless there's an unmatched '(' (i.e., close < open). These two constraints guarantee every complete string is valid.
</details>

**Drill 5:** Restore IP addresses: why break (not continue) when length > 3 or value > 255?
<details><summary>Reveal</summary>
Segments longer than 3 digits or values > 255 are always invalid. Longer segments only get larger, so we break (stop trying). A continue would skip to len+1 which is still invalid. Breaking is an optimization (pruning).
</details>

---

## 8. Complexity Cheatsheet

| Problem | Time | Space |
|---------|------|-------|
| N-Queens | O(N!) | O(N) |
| Sudoku | O(9^81) theoretical | O(81) |
| Word Search | O(R×C × 4^L) | O(L) |
| Generate Parentheses | O(C_n) Catalan | O(n) |
| Restore IP | O(3^4) = O(1) | O(1) |

---

## 9. Common Follow-up Questions

**Q: Can N-Queens be solved faster with bitmasks?**
A: Yes. Use three integers as bitmasks for cols, diag1, diag2. Bitwise AND/OR instead of hash set operations. Same O(N!) but faster constant.

**Q: Is Sudoku NP-complete?**
A: For standard 9×9, bounded search space makes it tractable. Generalized n²×n² Sudoku is NP-complete.

**Q: Word Search II (find all words from dictionary)?**
A: Build a Trie from dictionary. DFS on board; follow Trie branches. Prune when no Trie path exists. O(R×C × 4^L) but with much better pruning than checking each word separately.

**Q: How to optimize N-Queens for large N?**
A: Bitmask approach, constraint propagation (like arc consistency), or Dancing Links (Algorithm X) by Knuth for exact cover problems.

---

## 10. Cross-Pattern Connections

- **P46 (Subsets):** Same backtracking skeleton; constraint checking is the difference
- **P47 (Permutations):** N-Queens is a constrained permutation (each column exactly once → permutation of columns)
- **P18 (DFS):** Word search is DFS on a grid with backtracking
- **P36 (Bitmask DP):** Bitmask N-Queens uses integers for constraint sets; bitmask DP uses them for state
- **P86 (Strings/Trie):** Word Search II combines this pattern with Trie traversal
