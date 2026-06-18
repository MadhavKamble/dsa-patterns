# Surrounded Regions

> **LeetCode #130** · **Difficulty:** Medium · **Step 15 — Graphs · P13**

---

## Problem Understanding

**What is it asking?**
Given an `m x n` board of `'X'` and `'O'`, capture all regions of `'O'` that are **surrounded** by `'X'` on all 4 sides. A region is surrounded if none of its `'O'` cells touch the border.

**Input:** `board[][]` — matrix of `'X'` and `'O'`
**Output:** Modify `board` in-place — flip all surrounded `'O'` to `'X'`

**Example:**
```
Input:                Output:
X X X X              X X X X
X O O X    →         X X X X
X X O X              X X X X
X O X X              X O X X
```
The `'O'` at (3,1) touches the border → not surrounded → stays.
The `'O'` cluster at (1,1),(1,2),(2,2) is fully surrounded → flipped.

**Key Observations:**
- Any `'O'` connected (directly or indirectly) to a border `'O'` is **NOT** surrounded
- Instead of finding surrounded regions, find **safe** (border-connected) `'O'` cells — everything else gets flipped
- DFS/BFS from every `'O'` on the 4 borders marks all safe cells
- Unvisited `'O'` cells after that scan = surrounded → flip to `'X'`

---

## Optimal Approach — DFS from Border

### Key Observation

> Flip the problem: instead of finding surrounded cells, find the ones that are NOT surrounded. Run DFS from every `'O'` on the border — all cells visited in these DFS runs are safe. Then flip every unvisited `'O'` to `'X'`.

### Algorithm
1. DFS from every `'O'` on the top row, bottom row, left col, right col
2. Mark all reachable `'O'` cells as visited
3. Scan full board: any `'O'` with `vis==0` is surrounded → `board[i][j]='X'`

### Dry Run

```
Board:          vis after border DFS:
X X X X         0 0 0 0
X O O X    →    0 0 0 0
X X O X         0 0 0 0
X O X X         0 1 0 0

Unvisited O cells: (1,1),(1,2),(2,2) → flipped to X
Visited O cell: (3,1) → stays O
```

### Complexity
- **Time:** O(m × n) — each cell visited at most once
- **Space:** O(m × n) — vis array + recursion stack

---

## Clean C++ Interview Code

```cpp
class Solution {
public:
    void dfs(int row, int col,vector<vector<int>>& vis, vector<vector<char>>& board,int dRow[],int dCol[]){
        vis[row][col]=1;
        int n=board.size();
        int m=board[0].size();
        for(int i=0;i<4;i++){
            int nRow=row+dRow[i];
            int nCol=col+dCol[i];
            if(nRow>=0 && nRow<n &&
            nCol>=0 && nCol<m &&
            vis[nRow][nCol]==0 &&
            board[nRow][nCol]=='O'){
                dfs(nRow,nCol,vis, board, dRow,dCol);
            }
        }
    }
    void solve(vector<vector<char>>& board) {
        int n=board.size();
        int m=board[0].size();
        int dRow[]={-1,0,1,0};
        int dCol[]={0,1,0,-1};
        vector<vector<int>> vis(n,vector<int> (m,0));
        for(int j=0;j<m;j++){
            if(!vis[0][j] && board[0][j]=='O'){
                dfs(0,j,vis,board,dRow, dCol);
            }
            if(!vis[n-1][j] && board[n-1][j]=='O'){
                dfs(n-1,j,vis, board,dRow,dCol);
            }
        }
        for(int i=0;i<n;i++){
            if(!vis[i][0] && board[i][0]=='O'){
                dfs(i,0,vis, board,dRow,dCol);
            }
            if(!vis[i][m-1] && board[i][m-1]=='O'){
                dfs(i,m-1, vis, board, dRow, dCol);
            }
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(vis[i][j]==0 && board[i][j]=='O'){
                    board[i][j]='X';
                }
            }
        }
    }
};
```

### BFS Variant

```cpp
class Solution {
public:
    void solve(vector<vector<char>>& board) {
        int n=board.size();
        int m=board[0].size();
        vector<vector<int>> vis(n,vector<int>(m,0));
        queue<pair<int,int>> q;
        int dRow[]={-1,0,1,0};
        int dCol[]={0,1,0,-1};
        for(int j=0;j<m;j++){
            if(board[0][j]=='O'){ vis[0][j]=1; q.push({0,j}); }
            if(board[n-1][j]=='O'){ vis[n-1][j]=1; q.push({n-1,j}); }
        }
        for(int i=0;i<n;i++){
            if(board[i][0]=='O'){ vis[i][0]=1; q.push({i,0}); }
            if(board[i][m-1]=='O'){ vis[i][m-1]=1; q.push({i,m-1}); }
        }
        while(!q.empty()){
            auto it=q.front(); q.pop();
            int row=it.first;
            int col=it.second;
            for(int i=0;i<4;i++){
                int nRow=row+dRow[i];
                int nCol=col+dCol[i];
                if(nRow>=0 && nRow<n &&
                nCol>=0 && nCol<m &&
                vis[nRow][nCol]==0 &&
                board[nRow][nCol]=='O'){
                    vis[nRow][nCol]=1;
                    q.push({nRow,nCol});
                }
            }
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(vis[i][j]==0 && board[i][j]=='O'){
                    board[i][j]='X';
                }
            }
        }
    }
};
```

---

## Interview Explanation Script

> "Instead of finding surrounded regions directly, I find the ones that are NOT surrounded. Any `'O'` connected to a border `'O'` is safe — so I run DFS from every `'O'` on all 4 borders and mark them visited. After that, any `'O'` that's still unvisited must be surrounded — I flip it to `'X'`."

> "The key insight is inverting the problem. Trying to identify surrounded regions directly is hard. But identifying safe ones — those touching the border — is straightforward with DFS."

---

## Recall Line *(10-Second Revision)*

> "Surrounded Regions: DFS from all border O cells. Mark safe. Unvisited O → flip to X. O(m*n)."

---

## Short Revision Notes

- DFS from **borders only** — not from every `'O'`
- Four border traversals: top row, bottom row, left col, right col
- `vis[i][j]==0 && board[i][j]=='O'` → surrounded → flip
- Safe cells: border-connected `'O'` cells (vis==1), never flipped
- Works with BFS or DFS — same logic, different traversal

---

## Pattern Recognition Trigger

**When I see:**
- "Capture surrounded regions"
- "Islands not connected to border"
- "Flip interior cells of some type"

**I should think of:** DFS/BFS from the border, mark reachable cells, flip the rest

---

## Common Mistakes

❌ DFS from every `'O'` instead of only border `'O'` → marks everything as safe
❌ Modifying the board directly during DFS → corrupts traversal
❌ Missing one of the 4 borders (e.g., forgetting left/right columns)
❌ Flipping `vis==1` cells instead of `vis==0` cells at the end

---

## What Interviewer Is Testing

- **Problem inversion:** Recognizing that "find surrounded" is easier as "find NOT surrounded"
- **Border seeding:** DFS/BFS starting from all 4 edges
- **vis array usage:** Distinguishing safe vs surrounded cells cleanly

---

## Related Problems

- [ ] LeetCode #200 — Number of Islands
- [ ] LeetCode #417 — Pacific Atlantic Water Flow (DFS from two borders)
- [ ] LeetCode #1020 — Number of Enclaves (same pattern, count instead of flip)
- [ ] Striver Step 15 P08 — Flood Fill

---

## Pattern Category

`Graphs` · `DFS` · `BFS` · `Grid` · `Border Seeding`

---

## Difficulty Analysis

**Rating:** Medium (the inversion insight is the key — once you see it, implementation is straightforward)

**Why challenging:** Instinct is to DFS from every `'O'`, which is wrong. The trick is seeding from the border and working inward.

---

## 30-Second Last-Minute Revision

> **Surrounded Regions:** DFS from every `'O'` on all 4 borders → mark vis=1.
> Final scan: `vis==0 && board=='O'` → flip to `'X'`.
> **Time:** O(m×n) | **Space:** O(m×n)
> **Key insight:** Find safe cells (border-connected), not surrounded cells directly.
