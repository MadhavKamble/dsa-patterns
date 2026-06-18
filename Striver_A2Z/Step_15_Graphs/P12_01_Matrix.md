# 0/1 Matrix

> **LeetCode #542** · **Difficulty:** Medium · **Step 15 — Graphs · P12**

---

## Problem Understanding

**What is it asking?**
Given an `m x n` binary matrix `mat`, return a matrix of the same size where each cell contains the **distance to the nearest `0`**.

**Input:** `mat[][]` — binary matrix (values 0 or 1)
**Output:** `dist[][]` — same size, `dist[i][j]` = distance from `(i,j)` to nearest 0

**Example:**
```
mat = [[0,0,0],
       [0,1,0],
       [1,1,1]]

Output: [[0,0,0],
         [0,1,0],
         [1,2,1]]
```

**Key Observations:**
- Distance = number of steps (4-directional moves)
- Every `0` cell has distance `0` — they are the **sources**
- Multi-source BFS from all `0` cells simultaneously gives shortest distance to nearest 0 for every cell
- Same pattern as Rotten Oranges — all sources enqueued at time 0

---

## Optimal Approach — Multi-Source BFS

### Key Observation

> Enqueue all `0` cells at step 0. BFS spreads outward level by level — the first time BFS reaches a `1` cell, it's via the shortest path from the nearest `0`. This is the same multi-source BFS pattern as Rotten Oranges.
>
> Use a separate `vis[][]` array to avoid re-visiting cells. Store `{{row,col}, steps}` in the queue.

### Algorithm
1. Enqueue all `0` cells with `steps=0`, mark them visited
2. BFS: dequeue `{{row,col}, steps}`, set `dist[row][col]=steps`
3. For each 4-directional neighbor: if unvisited → mark visited, enqueue with `steps+1`
4. Return `dist`

### Dry Run

**Input:**
```
mat = [[0,0,0],
       [0,1,0],
       [1,1,1]]
```

Initial queue: `{(0,0),0}, {(0,1),0}, {(0,2),0}, {(1,0),0}, {(1,2),0}`

| Dequeued | steps | Newly enqueued |
|----------|-------|----------------|
| (0,0) | 0 | dist[0][0]=0 |
| (0,1) | 0 | dist[0][1]=0 |
| (0,2) | 0 | dist[0][2]=0 |
| (1,0) | 0 | dist[1][0]=0 |
| (1,2) | 0 | dist[1][2]=0 |
| (1,1) | 1 | dist[1][1]=1, enqueue (2,1) with steps=2 |
| (2,0) | 1 | dist[2][0]=1, enqueue (2,1) already vis |
| (2,2) | 1 | dist[2][2]=1 |
| (2,1) | 2 | dist[2][1]=2 |

**Output:**
```
[[0,0,0],
 [0,1,0],
 [1,2,1]]
```
✅

### Complexity
- **Time:** O(m × n) — each cell enqueued and processed once
- **Space:** O(m × n) — vis, dist arrays + queue

---

## Clean C++ Interview Code

```cpp
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int n=mat.size();
        int m=mat[0].size();
        vector<vector<int>> vis(n,vector<int> (m,0));
        vector<vector<int>> dist(n,vector<int>(m,0));
        queue<pair<pair<int,int>,int>> q;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(mat[i][j]==0){
                    q.push({{i,j},0});
                    vis[i][j]=1;
                }else{
                    vis[i][j]=0;
                }
            }
        }
        while(!q.empty()){
            int row=q.front().first.first;
            int col=q.front().first.second;
            int steps=q.front().second;
            q.pop();
            dist[row][col]=steps;
            int dRow[]={-1,0,1,0};
            int dCol[]={0,1,0,-1};
            for(int i=0;i<4;i++){
                int nRow=row+dRow[i];
                int nCol=col+dCol[i];
                if(nRow>=0 && nRow<n&&
                nCol>=0 && nCol<m&&
                vis[nRow][nCol]==0){
                    vis[nRow][nCol]=1;
                    q.push({{nRow,nCol},steps+1});
                }
            }
        }
        return dist;
    }
};
```

### DP Variant (two-pass, O(1) space)

```cpp
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int n=mat.size();
        int m=mat[0].size();
        vector<vector<int>> dist(n,vector<int>(m,INT_MAX-1));
        // top-left pass: propagate from top and left
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(mat[i][j]==0){
                    dist[i][j]=0;
                } else {
                    if(i>0) dist[i][j]=min(dist[i][j],dist[i-1][j]+1);
                    if(j>0) dist[i][j]=min(dist[i][j],dist[i][j-1]+1);
                }
            }
        }
        // bottom-right pass: propagate from bottom and right
        for(int i=n-1;i>=0;i--){
            for(int j=m-1;j>=0;j--){
                if(i<n-1) dist[i][j]=min(dist[i][j],dist[i+1][j]+1);
                if(j<m-1) dist[i][j]=min(dist[i][j],dist[i][j+1]+1);
            }
        }
        return dist;
    }
};
```

> Two passes cover all 4 directions: top+left in pass 1, bottom+right in pass 2. No queue needed — O(1) extra space (excluding output).

---

## Interview Explanation Script

> "This is multi-source BFS. All 0 cells are sources — I enqueue all of them at step 0 and mark them visited. BFS spreads outward; the first time any cell is reached, it's via the shortest path from the nearest 0. I store `{{row,col}, steps}` in the queue and write the steps into `dist` as I dequeue."

> "The separate `vis` array prevents re-visiting. Once a cell is marked visited on enqueue, it won't be enqueued again — so each cell gets the correct minimum distance."

---

## Recall Line *(10-Second Revision)*

> "0/1 Matrix: multi-source BFS from all 0s. Queue = {{row,col},steps}. dist[row][col]=steps on dequeue. O(m*n)."

---

## Short Revision Notes

- Multi-source BFS: enqueue **all** 0 cells at step 0 before BFS starts
- `vis[][]` separate from `mat` and `dist` — marks cells already in queue
- Mark visited on **enqueue** (not dequeue) — prevents duplicates
- Same pattern as Rotten Oranges — sources spread simultaneously
- `dist` initialized to 0; only cells actually dequeued get their value set

---

## Pattern Recognition Trigger

**When I see:**
- "Distance from each cell to nearest X"
- "Minimum steps to reach nearest target"
- "Multiple starting points, find distance to closest"

**I should think of:** Multi-source BFS — enqueue all targets at time 0

---

## Common Mistakes

❌ Running separate BFS from each 0 cell → O(m²n²), TLE
❌ Not using a `vis` array — same 1 cell gets enqueued multiple times via different 0 neighbors
❌ Marking visited on dequeue instead of enqueue → duplicates in queue
❌ Forgetting to enqueue 0 cells themselves (they need `dist=0` too)

---

## What Interviewer Is Testing

- **Multi-source BFS recognition** — multiple sources spreading simultaneously
- **vis array timing** — mark on enqueue, not dequeue
- **Connection to Rotten Oranges** — same underlying pattern

---

## Rotten Oranges vs 0/1 Matrix

| Property | Rotten Oranges | 0/1 Matrix |
|----------|---------------|------------|
| Sources | Rotten cells (value 2) | Zero cells (value 0) |
| Answer | Max time (last cell rotted) | Per-cell distance array |
| Unreachable check | freshCount > 0 after BFS | Not needed (all 1s reachable from some 0) |
| Queue stores | `{{row,col}, time}` | `{{row,col}, steps}` |

---

## Related Problems

- [ ] LeetCode #994 — Rotten Oranges (same multi-source BFS pattern)
- [ ] LeetCode #286 — Walls and Gates (multi-source BFS from gates)
- [ ] LeetCode #1162 — As Far from Land as Possible
- [ ] Striver Step 15 P09 — Rotten Oranges

---

## Pattern Category

`Graphs` · `BFS` · `Multi-Source BFS` · `Grid` · `Shortest Path`

---

## Difficulty Analysis

**Rating:** Medium (easy once you see it as multi-source BFS; the trap is trying single-source BFS per cell)

**Why challenging:** Realizing that BFS from each 1-cell separately is TLE, and that reversing the direction (BFS from all 0s) solves it in O(m×n).

---

## 30-Second Last-Minute Revision

> **0/1 Matrix:** Multi-source BFS from all 0 cells at step 0.
> Queue = `{{row,col},steps}`. Mark vis on enqueue.
> Dequeue → `dist[row][col]=steps` → enqueue unvisited neighbors with `steps+1`.
> **Time:** O(m×n) | **Space:** O(m×n)
