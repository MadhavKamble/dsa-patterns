# Sudoku Solver

> **LeetCode #37** · **Difficulty:** Hard · **Step 7 — Recursion · P23**

---

## 🧠 Problem Understanding

**What is it asking?**
Fill a 9×9 Sudoku board such that every row, column, and 3×3 box contains digits 1–9 exactly once. Given board has some pre-filled cells.

**Key Observations:**
- Find first empty cell (`'.'`), try digits `'1'` to `'9'`.
- For each digit, validate against its row, column, and 3×3 box.
- If valid: place it, recurse. If recursion fails: backtrack (reset to `'.'`).
- When no empty cell is found: board is complete → return true.

---

## 🥇 Recursive Backtracking

### Key Insight

> 💡 Scan row by row for the first empty cell. Try `'1'` to `'9'`. If `isValid`, place and recurse. If recursion returns false, undo (backtrack). If no digit works at a cell, return false to trigger parent backtrack. If no empty cell found, return true.

### 3×3 Box Index Formula

```cpp
int boxRowStart = 3 * (row / 3);
int boxColStart = 3 * (col / 3);
```

Integer division maps each row/col into its box:
```
row 0,1,2 → boxRowStart = 0
row 3,4,5 → boxRowStart = 3
row 6,7,8 → boxRowStart = 6
```

### isValid Check (3 Parts)

```
1. Column check: scan all rows in col `c`, look for duplicate
2. Row check:    scan all cols in row `r`, look for duplicate
3. Box check:    scan 3×3 sub-grid at (boxRowStart, boxColStart) for duplicate
```

Each check is O(9) = O(1) for fixed 9×9 board.

### Algorithm
1. `solveSudoku()`:
   - Find first `'.'` cell at `(i,j)`.
   - Try `'1'` to `'9'`: if `isValid(i,j,c)` → place `c`, recurse.
     - If recursion returns true → return true.
     - Else: `board[i][j] = '.'` (backtrack).
   - If no digit works → return false.
   - If no `'.'` found in any cell → return true (done).

### C++ Code

```cpp
class Solution {
public:
    bool isValid(vector<vector<char>>& board,int row,int col,char c){
        for(int i=0;i<9;i++){
            if(board[i][col]==c) return false;
        }
        for(int j=0;j<9;j++){
            if(board[row][j]==c) return false;
        }
        int boxRowStart=3*(row/3);
        int boxColStart=3*(col/3);
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                if(board[boxRowStart+i][boxColStart+j]==c) return false;
            }
        }
        return true;
    }

    bool solveSudoku(vector<vector<char>>& board){
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                if(board[i][j]=='.'){
                    for(char c='1';c<='9';c++){
                        if(isValid(board,i,j,c)){
                            board[i][j]=c;
                            if(solveSudoku(board)) return true;
                            board[i][j]='.';
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }
};
```

**Time:** O(9^(empty cells)) · **Space:** O(81) = O(1) — fixed 9×9 board, recursion depth ≤ 81

### Flow for One Empty Cell

```
Find (i,j) = first '.'
Try '1':
  isValid? 
    if yes: board[i][j]='1', solveSudoku() → recurse
      find next '.'...
        if no more '.' → return true (board complete)
        if stuck → return false
    backtrack: board[i][j]='.'
Try '2': ... (same)
...
Try '9': all fail → return false (parent must backtrack)
```

---

## 🔁 Contrast with M-Coloring (P22) and N-Queens (P19)

| | N-Queens (P19) | M-Coloring (P22) | Sudoku (P23) |
|---|---|---|---|
| Fill order | column by column | node by node | cell by cell (row-major) |
| Options per step | N rows | M colors | 9 digits |
| Validity check | row + 2 diagonals | adjacent node color | row + col + 3×3 box |
| Backtrack value | '.' | 0 | '.' |
| Return type | collect all | bool (exists?) | bool (modifies in-place) |

All three: **assign → recurse → backtrack if fail**.

---

## 🧾 Recall Line *(10-Second Revision)*

> "Find first '.'. Try '1'→'9'. isValid checks row + col + 3×3 box. Place, recurse, backtrack if false. No '.' found → return true. Box index: `3*(row/3)`, `3*(col/3)`."

---

## 📝 Short Revision Notes

- `return false` immediately when a cell has no valid digit — triggers parent's backtrack without scanning the rest of the board.
- `return true` at the bottom of the nested loop (after scanning all 81 cells with no `'.'` found) — this is the success condition.
- The cell scan always restarts from `(0,0)` per recursive call — O(81) scan, but with short-circuit on first `'.'`. This is a fixed cost for a 9×9 board.
- Column check can also be done with 3 hash sets (row/col/box) prebuilt in O(81) — same asymptotic but faster in practice.

---

## ⚠️ Common Mistakes

❌ Putting `return true` inside the `for(c='1';c<='9')` loop (after place+recurse) — only correct if already checked recursion success.
❌ Forgetting `board[i][j]='.'` backtrack — board stays corrupted for sibling paths.
❌ Off-by-one in box formula: `row/3*3` vs `3*(row/3)` — same result, but `3*(row/3)` is clearer.
❌ Checking validity of pre-filled cells — only check when placing into `'.'`.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "fill a grid cell-by-cell with digit constraints across row/col/box" → **find first empty, try all digits, isValid (row+col+box), recurse, backtrack**.

---

## 🏆 Pattern Category

`Recursion` · `Backtracking` · `Constraint Satisfaction` · `Grid`

---

## ⏱️ 30-Second Last-Minute Revision

> Find `'.'`, try `'1'`→`'9'`, check row/col/box validity. Place, recurse, backtrack if fail. No `'.'` left → true. Box: `3*(row/3)`, `3*(col/3)`. **Time:** O(9^N) where N=empty cells.
