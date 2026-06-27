# Path with Minimum Effort

> **LeetCode #1631** · **Difficulty:** Medium · **Step 15 — Graphs · P29**

---

## Problem Understanding

**What is it asking?**
Given an `n × m` grid of heights, find a path from top-left `(0,0)` to bottom-right `(n-1,m-1)` that **minimizes the maximum absolute difference** between adjacent cells on the path. This maximum difference is called the "effort."

**Input:** `heights[][]` — integer matrix of heights
**Output:** Minimum effort (minimum possible maximum height difference along any path)

**Example:**
```
heights = [[1,2,2],
           [3,8,2],
           [5,3,5]]

Path 1: (0,0)→(0,1)→(0,2)→(1,2)→(2,2) — diffs: 1,0,6,3 → max = 6
Path 2: (0,0)→(1,0)→(2,0)→(2,1)→(2,2) — diffs: 2,2,2,2 → max = 2
Path 3: (0,0)→(1,0)→(1,1)→(1,2)→(2,2) — diffs: 2,5,6,3 → max = 6

Output: 2 (Path 2)
```

**Key Observations:**
- Not minimizing SUM of differences — minimizing the **MAX** difference along the path
- Classic Dijkstra but edge weight = `max(current_max_diff, |h[r][c] - h[nr][nc]|)`
- `dist[r][c]` = minimum effort to reach `(r,c)` from `(0,0)`
- Min-heap ordered by effort — always process the cell reachable with least effort first
- Early return when `(n-1, m-1)` is popped from the heap

---

## Why Modified Dijkstra (Not BFS)?

```
BFS works for unit weights. Here, each move has a variable cost:
  cost of move = max(path_so_far_max, |h[curr] - h[next]|)

This is a non-uniform "edge weight" problem → need Dijkstra (min-heap).

The "distance" here is not sum but max — Dijkstra still works because:
  - max() is monotonically non-decreasing along any path
  - min-heap always gives the path with the smallest current max effort
  - First time we pop (n-1,m-1), it's via the minimum effort path
```

---

## Optimal Approach — Modified Dijkstra

### Key Observation

> `dist[r][c]` = minimum effort to reach `(r,c)`. When relaxing a neighbor, the new effort is `max(diff_so_far, |h[curr] - h[neighbor]|)`. If this is less than the currently known `dist[neighbor]`, update and push. The min-heap ensures we always explore the path with least current effort first.

### Algorithm
1. `dist[]=1e9`, `dist[0][0]=0`, push `{0, {0,0}}` to min-heap
2. Pop `{diff, {row, col}}` — if it's the destination, return `diff`
3. For each 4-direction neighbor `(nr, nc)`:
   - `newEffort = max(diff, |heights[row][col] - heights[nr][nc]|)`
   - If `newEffort < dist[nr][nc]`: update, push to heap

### Dry Run

**heights=[[1,2,2],[3,8,2],[5,3,5]]**

```
Init: dist[0][0]=0, pq={(0,{0,0})}

Pop (0,{0,0}): neighbors
  (0,1): effort=max(0,|1-2|)=1 < 1e9 → dist[0][1]=1, push (1,{0,1})
  (1,0): effort=max(0,|1-3|)=2 < 1e9 → dist[1][0]=2, push (2,{1,0})

Pop (1,{0,1}): neighbors
  (0,0): max(1,1)=1 > dist[0][0]=0 → skip
  (0,2): max(1,|2-2|)=1 < 1e9 → dist[0][2]=1, push (1,{0,2})
  (1,1): max(1,|2-8|)=6 < 1e9 → dist[1][1]=6, push (6,{1,1})

Pop (1,{0,2}): neighbors
  (0,1): skip
  (1,2): max(1,|2-2|)=1 < 1e9 → dist[1][2]=1, push (1,{1,2})

Pop (1,{1,2}): neighbors
  (0,2): skip
  (1,1): max(1,|2-8|)=6, not < dist[1][1]=6 → skip
  (2,2): max(1,|2-5|)=3 < 1e9 → dist[2][2]=3, push (3,{2,2})

Pop (2,{1,0}): neighbors
  (0,0): skip
  (1,1): max(2,|3-8|)=5 < dist[1][1]=6 → dist[1][1]=5, push (5,{1,1})
  (2,0): max(2,|3-5|)=2 < 1e9 → dist[2][0]=2, push (2,{2,0})

Pop (2,{2,0}): neighbors
  (1,0): skip
  (2,1): max(2,|5-3|)=2 < 1e9 → dist[2][1]=2, push (2,{2,1})

Pop (2,{2,1}): neighbors
  (2,0): skip
  (2,2): max(2,|3-5|)=2 < dist[2][2]=3 → dist[2][2]=2, push (2,{2,2})
  (1,1): max(2,|3-8|)=5, not < dist[1][1]=5 → skip

Pop (2,{2,2}): row==n-1 && col==m-1 → return 2 ✅
```

### Complexity
- **Time:** O(n × m × log(n×m)) — Dijkstra with min-heap
- **Space:** O(n × m) — dist array + heap

---

## Clean C++ Interview Code

```cpp
class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        priority_queue<pair<int,pair<int,int>>,
        vector<pair<int,pair<int,int>>>,
        greater<pair<int,pair<int,int>>>> pq;
        int n=heights.size();
        int m=heights[0].size();
        vector<vector<int>> dist(n,vector<int>(m,1e9));
        dist[0][0]=0;
        pq.push({0,{0,0}});
        int delRow[]={-1,0,1,0};
        int delCol[]={0,1,0,-1};
        while(!pq.empty()){
            auto it=pq.top();
            pq.pop();
            int diff=it.first;
            int row=it.second.first;
            int col=it.second.second;
            if(row==n-1 && col==m-1) return diff;
            for(int i=0;i<4;i++){
                int newRow=row+delRow[i];
                int newCol=col+delCol[i];
                if(newRow>=0 && newRow<n &&
                newCol>=0 && newCol<m){
                    int newEffort=max(abs(heights[row][col]-heights[newRow][newCol]),diff);
                    if(newEffort<dist[newRow][newCol]){
                        dist[newRow][newCol]=newEffort;
                        pq.push({newEffort,{newRow,newCol}});
                    }
                }
            }
        }
        return 0;
    }
};
```

---

## Key Difference from Standard Dijkstra

```
Standard Dijkstra:
  newDist = dist[node] + edgeWeight      (SUM along path)

Path with Minimum Effort:
  newEffort = max(diff, |h[curr]-h[next]|)   (MAX along path)

Both use min-heap. Both use relaxation condition (new < current dist).
The only change: + → max()
```

---

## Interview Explanation Script

> "This is modified Dijkstra where the 'distance' to a cell is the minimum possible maximum height difference along any path to it. When relaxing a neighbor, the effort is `max(current_path_max, |h[curr]-h[next]|)`. I use a min-heap so I always explore the path with the smallest effort first."

> "Early return when `(n-1,m-1)` is popped — the first time Dijkstra reaches the destination guarantees it's via the minimum effort path, same as standard Dijkstra."

> "The only difference from standard Dijkstra: edge weight accumulation uses `max` instead of `+`."

---

## Recall Line *(10-Second Revision)*

> "Min effort: Dijkstra. newEffort=max(diff,|h[r][c]-h[nr][nc]|). Min-heap by effort. Pop dest → return. O(nm log nm)."

---

## Short Revision Notes

- `dist[r][c]` = min possible max-diff to reach `(r,c)`, not sum
- Relaxation: `newEffort = max(diff, abs_height_diff)` — always non-decreasing
- Early return on pop of destination (not on push)
- `dist[0][0]=0` — zero effort at source
- Return `0` at end (unreachable, though for a connected grid this shouldn't happen)
- This is a "minimax path" problem — minimize the maximum edge weight

---

## Pattern Recognition Trigger

**When I see:**
- "Minimize the maximum difference/weight along a path"
- "Minimax path problem"
- "Minimum effort / bottleneck path"

**I should think of:** Modified Dijkstra with `max()` instead of `+` for path cost

---

## Common Mistakes

❌ Using `+` instead of `max()` for effort accumulation
❌ Checking destination on enqueue (not pop) — may return non-optimal result
❌ Using BFS — non-uniform effort requires priority queue
❌ Missing bounds check before accessing `heights[newRow][newCol]`

---

## Dijkstra Variants Summary

| Problem | Edge cost formula | What we minimize |
|---------|------------------|-----------------|
| Standard shortest path | `dist + weight` | Sum of weights |
| Path with min effort | `max(diff, \|h1-h2\|)` | Max edge weight |
| Network delay time | `dist + weight` | Sum (directed) |
| Swim in rising water | `max(diff, grid[nr][nc])` | Max cell value |

---

## Related Problems

- [ ] LeetCode #778 — Swim in Rising Water (same pattern, `max(diff, grid[nr][nc])`)
- [ ] LeetCode #743 — Network Delay Time (standard Dijkstra)
- [ ] Striver Step 15 P26 — Dijkstra's Algorithm
- [ ] Striver Step 15 P28 — Shortest Distance Binary Maze (BFS, unit weight)

---

## Pattern Category

`Graphs` · `Dijkstra` · `Grid` · `Minimax Path` · `Priority Queue`

---

## 30-Second Last-Minute Revision

> **Min Effort Path:** Modified Dijkstra on grid.
> `newEffort = max(diff, |heights[r][c] - heights[nr][nc]|)`
> Min-heap by effort. Pop → if dest → return diff.
> Relax: `newEffort < dist[nr][nc]` → update + push.
> **Time:** O(nm log nm) | **Key:** `max()` not `+` for path cost
