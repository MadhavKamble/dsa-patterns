# Number of Islands

> **LeetCode #200** · **Difficulty:** Medium · **Step 15 — Graphs · P15**

---

## Problem Understanding

**What is it asking?**
Given an `m x n` grid of `'1'` (land) and `'0'` (water), return the number of islands. An island is surrounded by water and formed by connecting adjacent land cells horizontally or vertically.

**Input:** `grid[][]` — matrix of `'1'` and `'0'`
**Output:** Integer — number of islands

**Example:**
```
grid = [["1","1","0","0","0"],
        ["1","1","0","0","0"],
        ["0","0","1","0","0"],
        ["0","0","0","1","1"]]

Islands: {(0,0),(0,1),(1,0),(1,1)}, {(2,2)}, {(3,3),(3,4)}
Output: 3
```

**Key Observations:**
- Each unvisited `'1'` cell starts a new island
- DFS/BFS from that cell marks the entire island as visited
- Count how many times we trigger a DFS/BFS from the outer loop
- Modifying grid in-place (`'1'→'0'`) avoids a separate vis array

---

## Optimal Approach — DFS (in-place marking)

### Key Observation

> Each time we find an unvisited `'1'`, we found a new island. DFS floods the entire island, marking every cell `'0'` so it's never counted again. The base case handles all bounds and water checks in one return statement.

### Algorithm
1. Scan every cell; if `grid[i][j]=='1'`: `count++`, DFS from `(i,j)`
2. DFS: base case returns if out of bounds or `'0'`; marks current cell `'0'`; recurses all 4 directions

### Dry Run

```
Start: count=0
(0,0)=='1' → count=1, DFS floods {(0,0),(0,1),(1,0),(1,1)} → all become '0'
(2,2)=='1' → count=2, DFS floods {(2,2)}
(3,3)=='1' → count=3, DFS floods {(3,3),(3,4)}
Output: 3 ✅
```

### Complexity
- **Time:** O(m × n) — each cell visited at most once
- **Space:** O(m × n) — recursion stack depth in worst case (all land)

---

## Clean C++ Interview Code

```cpp
class Solution {
public:
    void dfs(vector<vector<char>>& grid,int i,int j){
        int m=grid.size();
        int n=grid[0].size();
        if(i<0||j<0||i>=m||j>=n||grid[i][j]=='0') return;
        grid[i][j]='0';
        dfs(grid,i+1,j);
        dfs(grid,i-1,j);
        dfs(grid,i,j+1);
        dfs(grid,i,j-1);
    }
    int numIslands(vector<vector<char>>& grid) {
        int m=grid.size();
        int n=grid[0].size();
        int count=0;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]=='1'){
                    count++;
                    dfs(grid,i,j);
                }
            }
        }
        return count;
    }
};
```

### BFS Variant (separate vis array, grid unchanged)

```cpp
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int m=grid.size();
        int n=grid[0].size();
        vector<vector<int>> vis(m,vector<int>(n,0));
        int count=0;
        int dRow[]={-1,0,1,0};
        int dCol[]={0,1,0,-1};
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(!vis[i][j] && grid[i][j]=='1'){
                    count++;
                    queue<pair<int,int>> q;
                    vis[i][j]=1;
                    q.push({i,j});
                    while(!q.empty()){
                        int row=q.front().first;
                        int col=q.front().second;
                        q.pop();
                        for(int k=0;k<4;k++){
                            int nRow=row+dRow[k];
                            int nCol=col+dCol[k];
                            if(nRow>=0 && nRow<m &&
                            nCol>=0 && nCol<n &&
                            vis[nRow][nCol]==0 &&
                            grid[nRow][nCol]=='1'){
                                vis[nRow][nCol]=1;
                                q.push({nRow,nCol});
                            }
                        }
                    }
                }
            }
        }
        return count;
    }
};
```

---

## Interview Explanation Script

> "I scan the grid; whenever I find a `'1'` I haven't visited, it's a new island — increment count, then DFS to sink the entire island by marking every connected `'1'` as `'0'`. The base case of the DFS handles out-of-bounds and water in one check, making the code very clean."

> "Modifying the grid avoids a separate visited array. If the problem requires preserving input, switch to BFS with a separate `vis` array."

---

## Recall Line *(10-Second Revision)*

> "Islands: DFS, mark '1'→'0'. Count DFS launches. O(m*n)."

---

## Short Revision Notes

- In-place DFS: base case `i<0||j<0||i>=m||j>=n||grid[i][j]=='0'` — all guards in one line
- Mark `'0'` before recursing (effectively marks visited)
- BFS variant needed if grid must not be modified
- Count = number of DFS/BFS launches from the outer loop
- Works for 8-directional islands too — just add 4 diagonal directions

---

## Pattern Recognition Trigger

**When I see:**
- "Count connected components on a grid"
- "Number of groups/clusters of 1s"
- "Islands, provinces, regions"

**I should think of:** DFS/BFS from each unvisited source cell, count launches

---

## Common Mistakes

❌ Not marking visited before recursing → infinite loop on cycles
❌ Counting cells instead of DFS launches (counts cells not islands)
❌ Forgetting to check bounds before accessing `grid[i][j]`
❌ Using 8-directional when problem says 4-directional

---

## What Interviewer Is Testing

- **Connected component counting** on a grid
- **In-place visited marking** vs separate vis array trade-off
- **Clean base case** for recursive grid DFS

---

## Related Problems

- [ ] LeetCode #695 — Max Area of Island (same DFS, return size)
- [ ] LeetCode #130 — Surrounded Regions (border seeding variant)
- [ ] LeetCode #1020 — Number of Enclaves
- [ ] GFG — Number of Distinct Islands (same DFS + shape tracking)
- [ ] Striver Step 15 P16 — Number of Distinct Islands

---

## Pattern Category

`Graphs` · `DFS` · `BFS` · `Grid` · `Connected Components`

---

## Difficulty Analysis

**Rating:** Medium (classic — every interviewer knows it; clean base case and in-place marking are what they watch for)

**Why challenging:** Handling bounds cleanly, choosing in-place vs vis array, and knowing when to use BFS vs DFS.

---

## 30-Second Last-Minute Revision

> **Number of Islands:** Scan grid. `grid[i][j]=='1'` → `count++` → DFS.
> DFS base case: out of bounds or `'0'` → return. Mark `'0'`, recurse 4 directions.
> **Time:** O(m×n) | **Space:** O(m×n) recursion stack
