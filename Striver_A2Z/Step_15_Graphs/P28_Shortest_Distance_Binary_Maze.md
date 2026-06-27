# Shortest Distance in Binary Maze

> **GFG Problem** · **Difficulty:** Medium · **Step 15 — Graphs · P28**

---

## Problem Understanding

**What is it asking?**
Given an `n × m` binary matrix where `1` = open cell and `0` = blocked, find the **shortest distance** from `src` to `dest` moving in 4 directions. Return `-1` if no path exists.

**Input:** `mat[][]`, `src=[r,c]`, `dest=[r,c]`
**Output:** Minimum steps from src to dest, or `-1`

**Example:**
```
mat = [[1,1,1,1],
       [1,1,0,1],
       [1,1,1,1],
       [1,1,0,0],
       [1,0,0,1]]
src=[0,0], dest=[4,3]

Shortest path: (0,0)→(1,0)→(2,0)→(3,0)→(4,0)... blocked at (4,1)
Better: (0,0)→(0,1)→(1,1)→(2,1)→(2,2)→(2,3)→(3,3)... → (4,3)? 
Check if (4,3)=1: yes. Path of length = ?

Output: shortest distance (BFS finds it)
```

**Key Observations:**
- Unit weights (each step = 1) → BFS gives shortest path (no Dijkstra needed)
- `mat[cell]==1` to enter, `mat[cell]==0` blocked
- Edge cases: src or dest is `0` → return `-1`; src == dest → return `0`
- Early return when dest is first reached — BFS guarantees it's via shortest path
- `dist[][]` array prevents re-visiting cells with worse distances

---

## Optimal Approach — BFS with Distance Array

### Key Observation

> All moves cost 1 → BFS level = distance. First time BFS reaches dest = shortest path. Use `dist[][]` initialized to `1e9`; only enqueue a cell if the new distance is strictly better — this acts as a visited check and prevents processing the same cell with a longer path.

### Algorithm
1. Handle edge cases: blocked src/dest → `-1`; src == dest → `0`
2. `dist[src]=0`, push `{0, {src_r, src_c}}` to queue
3. BFS: for each 4-direction neighbor:
   - In bounds, open (`mat==1`), and `dis+1 < dist[newRow][newCol]` → update dist, check if dest → return, else enqueue
4. Queue exhausted → return `-1`

### Dry Run

**mat=[[1,1,1],[1,0,1],[1,1,1]], src=[0,0], dest=[2,2]**

```
Init: dist[0][0]=0, queue={(0,{0,0})}

Pop (0,{0,0}): neighbors
  (−1,0): OOB
  (0,1): mat=1, 0+1=1<1e9 → dist[0][1]=1, push (1,{0,1})
  (1,0): mat=1, 0+1=1<1e9 → dist[1][0]=1, push (1,{1,0})
  (0,−1): OOB

Pop (1,{0,1}): neighbors
  (0,0): 1+1=2 > dist[0][0]=0 → skip
  (0,2): mat=1, 1+1=2<1e9 → dist[0][2]=2, push (2,{0,2})
  (1,1): mat=0 → skip
  (−1,1): OOB

Pop (1,{1,0}): neighbors
  (0,0): skip
  (1,1): mat=0 → skip
  (2,0): mat=1, 1+1=2<1e9 → dist[2][0]=2, push (2,{2,0})
  (1,−1): OOB

Pop (2,{0,2}): neighbors
  (0,1): skip
  (0,3): OOB
  (1,2): mat=1, 2+1=3<1e9 → dist[1][2]=3, push (3,{1,2})
  (−1,2): OOB

Pop (2,{2,0}): neighbors
  (1,0): skip
  (2,1): mat=1, 2+1=3<1e9 → dist[2][1]=3, push (3,{2,1})
  (3,0): OOB
  (2,−1): OOB

Pop (3,{1,2}): neighbors
  (0,2): skip
  (1,3): OOB
  (2,2): mat=1, 3+1=4<1e9 → dist[2][2]=4
         newRow==dest[0] && newCol==dest[1] → return 4 ✅
```

### Complexity
- **Time:** O(n × m) — each cell processed at most once
- **Space:** O(n × m) — dist array + queue

---

## Clean C++ Interview Code

```cpp
class Solution {
  public:
    int shortestPath(vector<vector<int>> &mat, vector<int> &src, vector<int> &dest) {
        int n=mat.size();
        int m=mat[0].size();
        if(mat[src[0]][src[1]]==0 || mat[dest[0]][dest[1]]==0){
            return -1;
        }
        if(src[0]==dest[0] && src[1]==dest[1]){
            return 0;
        }
        queue<pair<int,pair<int,int>>> q;
        vector<vector<int>> dist(n,vector<int>(m,1e9));
        dist[src[0]][src[1]]=0;
        q.push({0,{src[0],src[1]}});
        int delRow[]={-1,0,1,0};
        int delCol[]={0,1,0,-1};
        while(!q.empty()){
            auto it=q.front();
            q.pop();
            int dis=it.first;
            int row=it.second.first;
            int col=it.second.second;
            for(int i=0;i<4;i++){
                int newRow=row+delRow[i];
                int newCol=col+delCol[i];
                if(newRow>=0 && newRow<n &&
                newCol>=0 && newCol<m &&
                mat[newRow][newCol]==1 &&
                dis+1<dist[newRow][newCol]){
                    dist[newRow][newCol]=dis+1;
                    if(newRow==dest[0] && newCol==dest[1]){
                        return dis+1;
                    }
                    q.push({dis+1,{newRow,newCol}});
                }
            }
        }
        return -1;
    }
};
```

### LeetCode #1091 — Shortest Path in Binary Matrix (8-directional)

> Key differences from GFG version:
> - `0` = open, `1` = blocked (inverted)
> - 8-directional movement (diagonals allowed)
> - `dist[0][0]=1` — path length counts the start cell itself
> - Fixed src=(0,0), dest=(n-1,n-1), square grid

```cpp
class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n=grid.size();
        if(grid[0][0]==1 || grid[n-1][n-1]==1)
            return -1;
        queue<pair<int,pair<int,int>>> q;
        vector<vector<int>> dist(n,vector<int>(n,1e9));
        dist[0][0]=1;
        q.push({1,{0,0}});
        int delRow[]={-1,-1,-1,0,0,1,1,1};
        int delCol[]={-1,0,1,-1,1,-1,0,1};
        while(!q.empty()){
            auto it=q.front();
            q.pop();
            int dis=it.first;
            int row=it.second.first;
            int col=it.second.second;
            if(row==n-1 && col==n-1)
                return dis;
            for(int i=0;i<8;i++){
                int nRow=row+delRow[i];
                int nCol=col+delCol[i];
                if(nRow>=0 && nRow<n &&
                nCol>=0 && nCol<n &&
                grid[nRow][nCol]==0 &&
                dis+1<dist[nRow][nCol]){
                    dist[nRow][nCol]=dis+1;
                    q.push({dis+1,{nRow,nCol}});
                }
            }
        }
        return -1;
    }
};
```

### Dijkstra Variant (if weights were non-uniform)

```cpp
// If different cells had different traversal costs, use priority_queue instead:
class Solution {
  public:
    int shortestPath(vector<vector<int>> &mat, vector<int> &src, vector<int> &dest) {
        int n=mat.size();
        int m=mat[0].size();
        if(mat[src[0]][src[1]]==0 || mat[dest[0]][dest[1]]==0) return -1;
        if(src[0]==dest[0] && src[1]==dest[1]) return 0;
        priority_queue<pair<int,pair<int,int>>,
                       vector<pair<int,pair<int,int>>>,
                       greater<pair<int,pair<int,int>>>> pq;
        vector<vector<int>> dist(n,vector<int>(m,1e9));
        dist[src[0]][src[1]]=0;
        pq.push({0,{src[0],src[1]}});
        int delRow[]={-1,0,1,0};
        int delCol[]={0,1,0,-1};
        while(!pq.empty()){
            auto it=pq.top(); pq.pop();
            int dis=it.first;
            int row=it.second.first;
            int col=it.second.second;
            for(int i=0;i<4;i++){
                int newRow=row+delRow[i];
                int newCol=col+delCol[i];
                if(newRow>=0 && newRow<n &&
                newCol>=0 && newCol<m &&
                mat[newRow][newCol]==1 &&
                dis+1<dist[newRow][newCol]){
                    dist[newRow][newCol]=dis+1;
                    if(newRow==dest[0] && newCol==dest[1]) return dis+1;
                    pq.push({dis+1,{newRow,newCol}});
                }
            }
        }
        return -1;
    }
};
```

---

## Interview Explanation Script

> "Unit weights on a grid → BFS gives shortest path in O(n×m). I use a dist array initialized to infinity to prevent re-processing cells with worse distances — it acts as a combined visited check and distance tracker."

> "I check `dis+1 < dist[newRow][newCol]` before enqueuing. For unit weight BFS, this simplifies to checking if the cell is unvisited (dist==1e9), but the explicit check is correct for any variant."

> "Early return when dest is first reached — BFS guarantees first reach = shortest path for unit weights."

---

## Recall Line *(10-Second Revision)*

> "Binary maze BFS: queue={dis,{row,col}}. dis+1<dist[nr][nc] → update+enqueue. dest reached → return dis+1. O(n×m)."

---

## Short Revision Notes

- Unit weight grid → BFS, not Dijkstra (O(nm) vs O(nm log nm))
- Three conditions to enqueue: in bounds + `mat==1` + `dis+1 < dist[new]`
- Early exit on reaching dest — avoids processing the entire grid
- Edge cases before BFS: blocked src/dest, src==dest
- `queue<pair<int,pair<int,int>>>` — same pattern as Rotten Oranges, 0/1 Matrix
- `dist[][]` = visited + distance in one array

---

## Comparison: BFS vs Dijkstra on Grid

| | BFS (unit weight) | Dijkstra (variable weight) |
|--|------------------|---------------------------|
| Queue | `queue` (FIFO) | `priority_queue` (min-heap) |
| Time | O(n×m) | O(n×m × log(n×m)) |
| Use when | All moves cost 1 | Moves have different costs |
| Example | Binary maze, 0/1 matrix | Path with minimum effort |

---

## Pattern Recognition Trigger

**When I see:**
- "Shortest path in binary grid (0/1)"
- "Minimum steps to reach destination"
- "BFS on grid from source to destination"

**I should think of:** BFS with `dist[][]` array, `queue<{dis,{r,c}}>`

---

## Common Mistakes

❌ Not checking if src or dest is blocked (`mat==0`)
❌ Not checking src == dest (returns 0 immediately, not 1)
❌ Missing `mat[newRow][newCol]==1` check → traverses through blocked cells
❌ Using Dijkstra for unit weights — correct but unnecessarily slow

---

## What Interviewer Is Testing

- **BFS for unit-weight grid shortest path**
- **dist[][] as combined visited + distance tracker**
- **Edge case handling** before BFS starts
- **Early termination** on reaching dest

---

## Related Problems

- [ ] LeetCode #542 — 0/1 Matrix (multi-source BFS, same grid pattern)
- [ ] LeetCode #1091 — Shortest Path in Binary Matrix (8-directional variant)
- [ ] LeetCode #1631 — Path with Minimum Effort (Dijkstra on grid)
- [ ] Striver Step 15 P22 — Shortest Path Undirected Unit Weight

---

## Pattern Category

`Graphs` · `BFS` · `Grid` · `Shortest Path` · `Unit Weight`

---

## 30-Second Last-Minute Revision

> **Binary Maze:** Edge cases first (blocked src/dest → -1, src==dest → 0).
> BFS with `queue<{dis,{r,c}}>`. `dist[][]=1e9`, `dist[src]=0`.
> Dequeue → 4 neighbors: in bounds + open + `dis+1<dist[nr][nc]` → update + early return if dest + enqueue.
> **Time:** O(n×m) | BFS not Dijkstra for unit weights.
