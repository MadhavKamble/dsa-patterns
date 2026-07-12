# N-Queens

> **LeetCode #51** · **Difficulty:** Hard · **Step 7 — Recursion · P19**

---

## 🧠 Problem Understanding

**What is it asking?**
Place `n` queens on an `n×n` chessboard such that no two queens attack each other (no shared row, column, or diagonal). Return all distinct solutions.

**Input:** `n = 4` → **Output:** two valid board configurations.

**Key Observations:**
- Place exactly one queen per column (or row) — reduces search space to n! instead of n^n.
- Work column by column: for each column, try every row.
- A queen attacks on: same row, upper-left diagonal, lower-left diagonal.
- Brute force checks these three threats in O(N) each. Optimal uses hash arrays for O(1).

---

## 🥉 Brute Force — O(N) Safety Check

### isSafe checks 3 directions (looking left since we fill left→right):
1. Same row leftward.
2. Upper-left diagonal.
3. Lower-left diagonal.

```cpp
bool isSafe(int row,int col,vector<vector<char>>& board,int n){
    for(int j=0;j<col;j++)
        if(board[row][j]=='Q') return false;
    for(int i=row,j=col;i>=0&&j>=0;i--,j--)
        if(board[i][j]=='Q') return false;
    for(int i=row,j=col;i<n&&j>=0;i++,j--)
        if(board[i][j]=='Q') return false;
    return true;
}

void solve(int col,vector<vector<char>>& board,vector<vector<string>>& ans,int n){
    if(col==n){
        vector<string> temp;
        for(int i=0;i<n;i++)
            temp.push_back(string(board[i].begin(),board[i].end()));
        ans.push_back(temp);
        return;
    }
    for(int row=0;row<n;row++){
        if(isSafe(row,col,board,n)){
            board[row][col]='Q';
            solve(col+1,board,ans,n);
            board[row][col]='.';
        }
    }
}
```

**Time:** O(N! × N) · **Space:** O(N²) for board

---

## 🥇 Optimal — O(1) Safety Check with Hash Arrays

### Key Insight

> 💡 Precompute three arrays that track which rows and diagonals are occupied. Any conflict is a O(1) lookup. No scanning the board.

### The Three Hash Arrays

```
leftRow[row]              = 1 if some column in this row already has a queen
lowerDiagonal[row + col]  = 1 if the lower-left diagonal through (row,col) is occupied
upperDiagonal[n-1+col-row]= 1 if the upper-left diagonal through (row,col) is occupied
```

**Why `row + col` for lower diagonal?**
All cells on the same lower-left diagonal share the same value of `row + col`.
```
(0,2)→2  (1,1)→2  (2,0)→2   all on same diagonal → row+col=2
(0,3)→3  (1,2)→3  (2,1)→3   (3,0)→3
```

**Why `n-1+col-row` for upper diagonal?**
All cells on the same upper-left diagonal share the same `col - row`.
`col - row` can be negative (range: `-(n-1)` to `+(n-1)`), so offset by `n-1` to make it 0-indexed.
```
Range of col-row: [-(n-1), n-1] → shifted: [0, 2(n-1)]
Size of upperDiagonal array: 2n-1
```

### C++ Code (Optimal)

```cpp
class Solution {
public:
    void solve(int col,vector<string>& board,int n,
               vector<int>& leftRow,vector<int>& upperDiagonal,vector<int>& lowerDiagonal,
               vector<vector<string>>& ans){
        if(col==n){
            ans.push_back(board);
            return;
        }
        for(int row=0;row<n;row++){
            if(leftRow[row]==0 && lowerDiagonal[row+col]==0 &&
               upperDiagonal[n-1+col-row]==0){
                board[row][col]='Q';
                leftRow[row]=1;
                lowerDiagonal[row+col]=1;
                upperDiagonal[n-1+col-row]=1;
                solve(col+1,board,n,leftRow,upperDiagonal,lowerDiagonal,ans);
                board[row][col]='.';
                leftRow[row]=0;
                lowerDiagonal[row+col]=0;
                upperDiagonal[n-1+col-row]=0;
            }
        }
    }

    vector<vector<string>> solveNQueens(int n){
        vector<vector<string>> ans;
        vector<string> board(n,string(n,'.'));
        vector<int> leftRow(n,0),upperDiagonal(2*n-1,0),lowerDiagonal(2*n-1,0);
        solve(0,board,n,leftRow,upperDiagonal,lowerDiagonal,ans);
        return ans;
    }
};
```

**Time:** O(N!) · **Space:** O(N) for hash arrays + O(N²) for board

### Diagonal Index Visualization for n=4

```
Board (row, col):       row+col (lower diag):   n-1+col-row (upper diag, n=4):
(0,0)(0,1)(0,2)(0,3)    0  1  2  3              3  4  5  6
(1,0)(1,1)(1,2)(1,3)    1  2  3  4              2  3  4  5
(2,0)(2,1)(2,2)(2,3)    2  3  4  5              1  2  3  4
(3,0)(3,1)(3,2)(3,3)    3  4  5  6              0  1  2  3
```

Same diagonal → same index. The arrays are sized `2n-1 = 7` for n=4.

### Dry Run — n=4, col=0

```
solve(col=0):
  row=0: all zeros → place Q at (0,0)
    leftRow[0]=1, lowerDiag[0]=1, upperDiag[3]=1
    solve(col=1):
      row=0: leftRow[0]=1 → skip
      row=1: lowerDiag[1+1=2]=0, upperDiag[3+1-1=3]=1 → skip (upper diag conflict)
      row=2: lowerDiag[2+1=3]=0, upperDiag[3+1-2=2]=0, leftRow[2]=0 → place Q at (2,1)
        solve(col=2): ... (continues)
      row=3: lowerDiag[3+1=4]=0, upperDiag[3+1-3=1]=0, leftRow[3]=0 → place Q at (3,1)
        solve(col=2): ...
```

---

## 🆚 Brute Force vs Optimal

| | Brute Force | Optimal |
|---|---|---|
| Safety check | O(N) — scan board | O(1) — hash arrays |
| Space for tracking | board scan | 3 arrays of size N / 2N-1 |
| Total time | O(N! × N) | O(N!) |
| Diagonal key | computed by scan | `row+col` / `n-1+col-row` |

---

## 🧾 Recall Line *(10-Second Revision)*

> "One queen per column. Optimal: 3 hash arrays — `leftRow[row]`, `lowerDiag[row+col]`, `upperDiag[n-1+col-row]`. Set on place, clear on backtrack. O(N!)."

---

## 📝 Short Revision Notes

- Column-by-column placement: since exactly one queen per column, no `colArray` needed.
- `row + col` is invariant along lower-left diagonals (↙).
- `col - row` is invariant along upper-left diagonals (↖); shift by `n-1` to keep non-negative.
- Array size `2n-1`: valid range of `row+col` is `[0, 2(n-1)]` → `2n-1` values.

---

## ⚠️ Common Mistakes

❌ Forgetting to reset hash arrays after backtracking — queens from dead-end paths persist.
❌ Wrong upper diagonal formula: using `col + row` (which is for lower) instead of `col - row`.
❌ Wrong array size: `n` instead of `2n-1` for diagonal arrays — index out of bounds.
❌ Scanning right side (cols > current) in brute force `isSafe` — queens are only placed to the left.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "place N non-attacking queens" → **column-by-column backtracking, 3 hash arrays for O(1) conflict check**.

---

## 🏆 Pattern Category

`Recursion` · `Backtracking` · `Constraint Satisfaction` · `N-Queens`

---

## ⏱️ 30-Second Last-Minute Revision

> One queen per col. Hash arrays: `leftRow[r]`, `lowerDiag[r+c]`, `upperDiag[n-1+c-r]`. All 0 → place, set to 1, recurse col+1, reset to 0 (backtrack). **Time:** O(N!) | **Space:** O(N).
