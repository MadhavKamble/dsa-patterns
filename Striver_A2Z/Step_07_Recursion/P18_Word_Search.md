# Word Search

> **LeetCode #79** · **Difficulty:** Medium · **Step 7 — Recursion · P18**

---

## 🧠 Problem Understanding

**What is it asking?**
Given an `m×n` grid of characters and a word, return true if the word exists in the grid. The word must be formed by sequentially adjacent cells (horizontally/vertically). Each cell may only be used once per path.

**Input:**
```
board = [["A","B","C","E"],
         ["S","F","C","S"],
         ["A","D","E","E"]]
word = "ABCCED"
```
**Output:** `true`

**Key Observations:**
- Multi-source start: try every cell as a potential starting point.
- DFS on 4 neighbors, checking character match at each step.
- Mark cell visited in-place (`'#'`), recurse, then restore — O(1) space vs a separate `visited` array.
- Base: `idx == word.size()` means all characters matched.

---

## 🥇 DFS with In-Place Marking

### Key Insight

> 💡 At each cell, check that `board[i][j] == word[idx]`. If yes, temporarily replace with `'#'` (visited marker), explore all 4 directions for `idx+1`, then restore. The restore step IS the backtracking.

### Why `'#'` Instead of a Visited Array?

Using `board[i][j] = '#'` avoids O(N×M) extra space. The check `board[i][j] != word[idx]` naturally fails for `'#'` since no word contains `'#'`. Restore at the end of each DFS call undoes the mark.

### Algorithm
1. Outer loop: try every `(i,j)` as start. If `board[i][j] == word[0]` and `dfs(i,j,0)` → return true.
2. `dfs(i, j, idx)`:
   - **Base:** `idx == word.size()` → return true (all matched).
   - **Guard:** out of bounds or `board[i][j] != word[idx]` → return false.
   - Mark: `board[i][j] = '#'`.
   - Try 4 directions: `OR` of dfs with `idx+1`.
   - Restore: `board[i][j] = temp`.
   - Return `found`.

### C++ Code

```cpp
class Solution {
public:
    int n,m;

    bool exist(vector<vector<char>>& board,string word){
        m=board.size();
        n=board[0].size();
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(board[i][j]==word[0] && dfs(board,word,i,j,0))
                    return true;
            }
        }
        return false;
    }

    bool dfs(vector<vector<char>>& board,string& word,int i,int j,int idx){
        if(idx==(int)word.size()) return true;
        if(i<0||j<0||i>=m||j>=n||board[i][j]!=word[idx])
            return false;
        char temp=board[i][j];
        board[i][j]='#';
        bool found=dfs(board,word,i+1,j,idx+1)||
                   dfs(board,word,i-1,j,idx+1)||
                   dfs(board,word,i,j+1,idx+1)||
                   dfs(board,word,i,j-1,idx+1);
        board[i][j]=temp;
        return found;
    }
};
```

**Time:** O(M × N × 4^L) — L = word length, at most 4 directions per step
**Space:** O(L) — recursion depth = word length

### Dry Run — Find "ABCCED" in board

```
Start at (0,0)='A', dfs(0,0,0):
  board[0][0]='A'==word[0] ✓, mark '#'
  → dfs(1,0,1): board[1][0]='S'≠'B' → false
  → dfs(-1,0,1): out of bounds → false
  → dfs(0,1,1): board[0][1]='B'==word[1] ✓, mark '#'
    → dfs(0,2,2): board[0][2]='C'==word[2] ✓, mark '#'
      → dfs(1,2,3): board[1][2]='C'==word[3] ✓, mark '#'
        → dfs(2,2,4): board[2][2]='E'==word[4] ✓, mark '#'
          → dfs(2,1,5): board[2][1]='D'==word[5] ✓, mark '#'
            → dfs(*,*,6): idx=6=word.size() → return true ✓
```

Path: (0,0)→(0,1)→(0,2)→(1,2)→(2,2)→(2,1) = "ABCCED" ✓

---

## 🔁 Key Backtracking Property

The `board[i][j] = temp` restore is what makes this backtracking:
```
Mark  (prevent revisit in this path)
 ↓
Recurse all 4 directions
 ↓
Restore  (allow other paths to use this cell)
```

Without restore, a cell used in one dead-end path would be permanently blocked from other paths.

---

## 🧾 Recall Line *(10-Second Revision)*

> "Try all start cells. DFS: base=`idx==size→true`, guard=OOB/mismatch. Mark `'#'`, explore 4 dirs with `idx+1`, restore. Backtrack = restore. O(M×N×4^L)."

---

## 📝 Short Revision Notes

- Outer loop `if(board[i][j]==word[0])` is an optimization — skip cells that don't match the first letter. Correctness is maintained by the check inside dfs anyway.
- `||` short-circuits: if any direction returns true, the rest aren't explored.
- `board[i][j]='#'` before the 4-directional OR is critical — without it, a cell can recursively visit itself.
- String `word` passed by reference in dfs — avoids copying on every recursive call.

---

## ⚠️ Common Mistakes

❌ Marking after the 4-directional search instead of before — cell can be revisited within the same path.
❌ Not restoring (`board[i][j] = temp`) — blocks future paths.
❌ Checking `board[i][j] == word[idx]` after marking with `'#'` — always fails.
❌ Bounds check after dereference — UB. Always: `i<0||i>=m||j<0||j>=n` before `board[i][j]`.

---

## 🧠 Pattern Recognition Trigger

**When I see:** "find a path in a grid matching a sequence" → **multi-source DFS, in-place mark + restore (backtrack)**.

---

## 🏆 Pattern Category

`Recursion` · `Backtracking` · `DFS` · `Grid`

---

## ⏱️ 30-Second Last-Minute Revision

> Each cell: if matches `word[idx]`, mark `'#'`, DFS 4 dirs for `idx+1`, restore. Base: `idx==len→true`. Guard: OOB or mismatch → false. **Time:** O(M×N×4^L) | **Space:** O(L).
