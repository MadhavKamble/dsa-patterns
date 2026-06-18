# Number of Enclaves

> **LeetCode #1020** · **Difficulty:** Medium · **Step 15 — Graphs · P14**

---

## Problem Understanding

**What is it asking?**
Given a binary matrix `grid` where `0` = sea and `1` = land, return the number of land cells from which you **cannot** walk off the boundary of the grid in any number of moves (4-directional).

**Input:** `grid[][]` — binary matrix
**Output:** Count of enclosed land cells (enclaves)

**Example:**
```
grid = [[0,0,0,0],
        [1,0,1,0],
        [0,1,1,0],
        [0,0,0,0]]

Border-connected land: (1,0) touches left border → not enclave
Enclosed land: (1,2),(2,1),(2,2) → no path to border → count = 3
```

**Key Observations:**
- Same pattern as Surrounded Regions (P13) — find border-connected cells, count the rest
- BFS/DFS from all border land cells marks every reachable land cell as "safe"
- Unvisited land cells are enclaves → count them

---

## Optimal Approach — BFS from Border

### Key Observation

> Seed BFS with all land cells on the 4 borders simultaneously. BFS marks every land cell connected to the border. Any remaining unvisited land cell is an enclave.
>
> Compact border check: `i==0 || j==0 || i==n-1 || j==m-1`

### Algorithm
1. Enqueue all border land cells (`grid[i][j]==1`), mark visited
2. BFS: spread to all 4-connected unvisited land neighbors
3. Count cells where `grid[i][j]==1 && vis[i][j]==0`

### Dry Run

```
grid = [[0,0,0,0],
        [1,0,1,0],
        [0,1,1,0],
        [0,0,0,0]]

Border land cells: (1,0) → enqueue, vis[1][0]=1
BFS from (1,0): no unvisited land neighbors reachable

vis after BFS:
0 0 0 0
1 0 0 0
0 0 0 0
0 0 0 0

Count vis==0 && grid==1: (1,2),(2,1),(2,2) → return 3
```
✅

### Complexity
- **Time:** O(m × n) — each cell visited at most once
- **Space:** O(m × n) — vis array + queue

---

## Clean C++ Interview Code

```cpp
class Solution {
public:
    int numEnclaves(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        queue<pair<int,int>> q;
        vector<vector<int>> vis(n,vector<int> (m,0));
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(i==0 || j==0 || i==n-1 || j==m-1){
                    if(grid[i][j]==1){
                        q.push({i,j});
                        vis[i][j]=1;
                    }
                }
            }
        }
        while(!q.empty()){
            int row=q.front().first;
            int col=q.front().second;
            q.pop();
            int dRow[]={-1,0,1,0};
            int dCol[]={0,1,0,-1};
            for(int i=0;i<4;i++){
                int nRow=row+dRow[i];
                int nCol=col+dCol[i];
                if(nRow>=0 && nRow<n &&
                nCol>=0 && nCol<m &&
                vis[nRow][nCol]==0 &&
                grid[nRow][nCol]==1){
                    q.push({nRow,nCol});
                    vis[nRow][nCol]=1;
                }
            }
        }
        int count=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(grid[i][j]==1 && vis[i][j]==0){
                    count++;
                }
            }
        }
        return count;
    }
};
```

### DFS Variant

```cpp
class Solution {
    void dfs(int row, int col, vector<vector<int>>& grid,
             vector<vector<int>>& vis, int dRow[], int dCol[]){
        vis[row][col]=1;
        int n=grid.size();
        int m=grid[0].size();
        for(int i=0;i<4;i++){
            int nRow=row+dRow[i];
            int nCol=col+dCol[i];
            if(nRow>=0 && nRow<n &&
            nCol>=0 && nCol<m &&
            vis[nRow][nCol]==0 &&
            grid[nRow][nCol]==1){
                dfs(nRow,nCol,grid,vis,dRow,dCol);
            }
        }
    }
public:
    int numEnclaves(vector<vector<int>>& grid) {
        int n=grid.size();
        int m=grid[0].size();
        int dRow[]={-1,0,1,0};
        int dCol[]={0,1,0,-1};
        vector<vector<int>> vis(n,vector<int>(m,0));
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(i==0 || j==0 || i==n-1 || j==m-1){
                    if(!vis[i][j] && grid[i][j]==1){
                        dfs(i,j,grid,vis,dRow,dCol);
                    }
                }
            }
        }
        int count=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(grid[i][j]==1 && vis[i][j]==0) count++;
            }
        }
        return count;
    }
};
```

---

## Interview Explanation Script

> "Same idea as Surrounded Regions — find land cells that are NOT enclaves (i.e., border-connected), then count the rest. I BFS from all border land cells, marking every reachable land cell as visited. Any unvisited land cell after BFS is an enclave."

> "The border check `i==0 || j==0 || i==n-1 || j==m-1` in one condition is cleaner than four separate loops."

---

## Recall Line *(10-Second Revision)*

> "Enclaves: BFS from all border land cells. Count unvisited land cells after BFS. O(m*n)."

---

## Short Revision Notes

- Same pattern as Surrounded Regions — border seeding + count instead of flip
- `i==0 || j==0 || i==n-1 || j==m-1` covers all 4 borders in one pass
- Mark vis on **enqueue** — prevents duplicate entries
- BFS and DFS give identical results — BFS is iterative (safer for large grids)
- No modification to `grid` needed — separate `vis` array

---

## Pattern Recognition Trigger

**When I see:**
- "Count land cells that can't reach the boundary"
- "Enclosed regions"
- "Islands completely surrounded by water/border"

**I should think of:** BFS/DFS from all border cells → count unreached cells

---

## Common Mistakes

❌ BFS from interior cells instead of border cells → wrong seeding
❌ Counting visited cells instead of unvisited ones
❌ Marking visited on dequeue instead of enqueue → duplicates in queue
❌ Missing corners (handled automatically by the `i==0||j==0||...` check)

---

## What Interviewer Is Testing

- **Border seeding pattern** — same as Surrounded Regions
- **Compact border check** vs four separate loops
- **vis timing** — mark on enqueue

---

## Surrounded Regions vs Number of Enclaves

| Property | Surrounded Regions | Number of Enclaves |
|----------|-------------------|--------------------|
| Cell type | `'O'` / `'X'` chars | `0`/`1` integers |
| Output | Modify board in-place | Return count |
| Post-BFS action | Flip unvisited `'O'` → `'X'` | Count unvisited `1` cells |
| Border seeding | Same | Same |

---

## Related Problems

- [ ] LeetCode #130 — Surrounded Regions (flip instead of count)
- [ ] LeetCode #200 — Number of Islands
- [ ] LeetCode #417 — Pacific Atlantic Water Flow
- [ ] Striver Step 15 P13 — Surrounded Regions

---

## Pattern Category

`Graphs` · `BFS` · `DFS` · `Grid` · `Border Seeding`

---

## Difficulty Analysis

**Rating:** Medium (easy once you recognize the Surrounded Regions pattern)

**Why challenging:** Recognizing that counting enclaves = count of non-border-connected land, not finding enclosed regions directly.

---

## 30-Second Last-Minute Revision

> **Number of Enclaves:** BFS/DFS from all border `1` cells → mark safe.
> Count `grid[i][j]==1 && vis[i][j]==0` → those are enclaves.
> Border check: `i==0 || j==0 || i==n-1 || j==m-1`
> **Time:** O(m×n) | **Space:** O(m×n)
