# Rotten Oranges

> **LeetCode #994** · **Difficulty:** Medium · **Step 15 — Graphs · P09**

---

## Problem Understanding

**What is it asking?**
Given an `m x n` grid where:
- `0` = empty cell
- `1` = fresh orange
- `2` = rotten orange

Every minute, a rotten orange makes all 4-directionally adjacent fresh oranges rotten. Return the **minimum number of minutes** until no fresh orange remains, or `-1` if impossible.

**Input:** `grid[][]`
**Output:** Minimum minutes, or `-1`

**Example:**
```
grid = [[2,1,1],
        [1,1,0],
        [0,1,1]]

Minute 0: rotten = {(0,0)}
Minute 1: (0,1) and (1,0) rot
Minute 2: (0,2), (1,1) rot
Minute 3: (2,1) rots
Minute 4: (2,2) rots

Answer: 4
```

**Key Observations:**
- Multiple rotten oranges spread simultaneously → **Multi-source BFS**
- BFS gives minimum time (level = minute)
- If any fresh orange remains after BFS → return `-1`
- Cells with `0` are never oranges — skip them

---

## Optimal Approach — Multi-Source BFS

### Key Observation

> All rotten oranges rot their neighbors simultaneously. This is exactly multi-source BFS — enqueue ALL rotten oranges at minute 0, then process level by level. Each BFS level = 1 minute elapsed.
>
> We do NOT run separate BFS from each rotten orange — that would give the wrong (non-simultaneous) spreading.

### Algorithm
1. Find all rotten oranges → enqueue them all, count `freshCount`
2. If `freshCount == 0`, return `0`
3. BFS level by level (each level = 1 minute):
   - For each rotten orange in the current level, rot its 4 fresh neighbors
   - For each newly rotted orange: decrement `freshCount`, enqueue
4. After BFS: if `freshCount > 0` → return `-1`, else return `minutes`

### Dry Run

**Input:**
```
[[2,1,1],
 [1,1,0],
 [0,1,1]]
```

| Minute | Queue (before processing) | Newly Rotted | freshCount |
|--------|---------------------------|--------------|------------|
| Start | [(0,0)] | — | 6 |
| 1 | [(0,0)] → process | (0,1),(1,0) | 4 |
| 2 | [(0,1),(1,0)] → process | (0,2),(1,1) | 2 |
| 3 | [(0,2),(1,1)] → process | (2,1) | 1 |
| 4 | [(2,1)] → process | (2,2) | 0 |

`freshCount == 0` → return `4` ✅

**Impossible case:**
```
[[2,1,1],
 [0,1,1],
 [1,0,1]]
→ freshCount > 0 after BFS → return -1
```

### Complexity
- **Time:** O(m × n) — each cell enqueued/processed at most once
- **Space:** O(m × n) — queue can hold all cells

---

## Clean C++ Interview Code

```cpp
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int n=grid.size();
        int m=grid[0].size();
        queue<pair<int,int>> q;
        int freshCount=0;

        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                if(grid[i][j]==2) q.push({i,j});
                else if(grid[i][j]==1) freshCount++;

        if(freshCount==0) return 0;

        int minutes=0;
        int dRow[]={-1,0,1,0};
        int dCol[]={0,1,0,-1};

        while(!q.empty()){
            int sz=q.size();
            bool rotted=false;
            for(int k=0;k<sz;k++){
                auto it=q.front();
                q.pop();
                int row=it.first;
                int col=it.second;
                for(int i=0;i<4;i++){
                    int newRow=row+dRow[i];
                    int newCol=col+dCol[i];
                    if(newRow>=0 && newRow<n &&
                    newCol>=0 && newCol<m &&
                    grid[newRow][newCol]==1){
                        grid[newRow][newCol]=2;
                        freshCount--;
                        q.push({newRow,newCol});
                        rotted=true;
                    }
                }
            }
            if(rotted) minutes++;
        }

        return freshCount==0 ? minutes : -1;
    }
};
```

### Variant (time stored in queue)

```cpp
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int n=grid.size();
        int m=grid[0].size();
        queue<tuple<int,int,int>> q;
        int freshCount=0;

        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++){
                if(grid[i][j]==2) q.push({i,j,0});
                else if(grid[i][j]==1) freshCount++;
            }

        int maxTime=0;
        int dRow[]={-1,0,1,0};
        int dCol[]={0,1,0,-1};

        while(!q.empty()){
            auto [row,col,t]=q.front(); q.pop();
            for(int i=0;i<4;i++){
                int newRow=row+dRow[i];
                int newCol=col+dCol[i];
                if(newRow>=0 && newRow<n &&
                newCol>=0 && newCol<m &&
                grid[newRow][newCol]==1){
                    grid[newRow][newCol]=2;
                    freshCount--;
                    maxTime=max(maxTime,t+1);
                    q.push({newRow,newCol,t+1});
                }
            }
        }

        return freshCount==0 ? maxTime : -1;
    }
};
```

---

## Interview Explanation Script

> "This is multi-source BFS. All rotten oranges spread simultaneously, so I enqueue all of them at minute 0 and process BFS level by level — each level is one minute."

> "I count fresh oranges upfront. Every time I rot a fresh one, I decrement the count. After BFS, if any fresh orange remains, it was unreachable — return -1. Otherwise return the number of BFS levels processed."

> "The key mistake to avoid: running separate BFS from each rotten orange. That simulates sequential spreading, not simultaneous. Multi-source BFS is the right model."

---

## Recall Line *(10-Second Revision)*

> "Rotten Oranges: multi-source BFS. Enqueue all rotten at t=0. Level = 1 min. freshCount > 0 after BFS → -1."

---

## Short Revision Notes

- Multi-source BFS: enqueue **all** starting sources before BFS begins
- Track `freshCount` — decrement when rotting, check at end for `-1`
- `freshCount == 0` at start → return `0` immediately
- Each BFS level = simultaneous spread = 1 minute
- Modifying grid in-place (2) serves as visited marker for fresh oranges

---

## Pattern Recognition Trigger

**When I see:**
- "Minimum time for something to spread from multiple sources"
- "All sources spread simultaneously each step"
- "Find how long until all cells are affected"

**I should think of:** Multi-source BFS (enqueue all sources at time 0)

---

## Common Mistakes

❌ Running BFS separately from each rotten orange → simulates sequential spread, wrong answer
❌ Not handling `freshCount == 0` at start → returns non-zero for already solved grid
❌ Counting `minutes++` even when nothing rotted in a level → overcounts
❌ Forgetting `-1` case — not all grids are solvable

---

## What Interviewer Is Testing

- **Multi-source BFS:** Recognizing that simultaneous spread = all sources enqueued at once
- **Level-by-level BFS:** Tracking time via BFS levels
- **Edge cases:** No fresh oranges, unreachable fresh oranges

---

## Multi-Source BFS Pattern

```
Enqueue all sources with time 0
While queue not empty:
    Dequeue (cell, time)
    For each valid neighbor not yet visited:
        Mark visited
        Enqueue (neighbor, time+1)
        Update answer = max(answer, time+1)
Return answer (or -1 if some cells unreached)
```

**Other problems using this pattern:**
- 0/1 Matrix (LC #542) — distance from nearest 0
- Walls and Gates (LC #286) — distance from nearest gate
- Pacific Atlantic Water Flow (LC #417)

---

## Related Problems

- [ ] LeetCode #542 — 0/1 Matrix (multi-source BFS from all 0s)
- [ ] LeetCode #286 — Walls and Gates (multi-source BFS from gates)
- [ ] LeetCode #733 — Flood Fill (single-source BFS/DFS on grid)
- [ ] LeetCode #200 — Number of Islands
- [ ] Striver Step 15 P08 — Flood Fill

---

## Pattern Category

`Graphs` · `BFS` · `Multi-Source BFS` · `Grid` · `Shortest Path`

---

## Difficulty Analysis

**Rating:** Medium (easy to code BFS; the challenge is recognizing multi-source and handling edge cases)

**Why challenging:** Multi-source BFS insight, correct minute counting, and the `-1` edge case all need to be handled together.

---

## 30-Second Last-Minute Revision

> **Rotten Oranges:** Multi-source BFS. Enqueue ALL rotten at t=0. Count fresh oranges.
> BFS level by level → each level = 1 minute → rot neighbors → decrement freshCount.
> After BFS: freshCount > 0 → -1, else → minutes elapsed.
> **Time:** O(m×n) | **Space:** O(m×n)
