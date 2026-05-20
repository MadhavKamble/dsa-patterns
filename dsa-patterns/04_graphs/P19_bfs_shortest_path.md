# Pattern 19: BFS — Shortest Path in Unweighted Graph

## Category
Graphs

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 127. Word Ladder | Hard | https://leetcode.com/problems/word-ladder/ |
| 2 | 200. Number of Islands (BFS variant) | Medium | https://leetcode.com/problems/number-of-islands/ |
| 3 | 286. Walls and Gates | Medium | https://leetcode.com/problems/walls-and-gates/ |
| 4 | 542. 01 Matrix | Medium | https://leetcode.com/problems/01-matrix/ |
| 5 | 752. Open the Lock | Medium | https://leetcode.com/problems/open-the-lock/ |
| 6 | 994. Rotting Oranges | Medium | https://leetcode.com/problems/rotting-oranges/ |
| 7 | 1091. Shortest Path in Binary Matrix | Medium | https://leetcode.com/problems/shortest-path-in-binary-matrix/ |
| 8 | 1162. As Far from Land as Possible | Medium | https://leetcode.com/problems/as-far-from-land-as-possible/ |
| 9 | 1293. Shortest Path in a Grid with Obstacles Elimination | Hard | https://leetcode.com/problems/shortest-path-in-a-grid-with-obstacles-elimination/ |

---

## 1. First-Timer Explanation

### What is this pattern?
BFS explores nodes **level by level** — all nodes at distance 1, then distance 2, etc. This property makes BFS guarantee the **shortest path in unweighted graphs**: the first time you reach a node, it's via the shortest route.

**The algorithm:**
1. Enqueue the source(s) with distance 0
2. Mark source(s) as visited immediately when enqueued
3. While queue non-empty: dequeue, process, enqueue all unvisited neighbors (with distance + 1)
4. First time you reach the target = shortest distance

**Multi-source BFS**: start with multiple sources in the queue simultaneously. Useful when asking "minimum distance from ANY source to each cell" (Rotting Oranges, 01 Matrix, Walls and Gates).

### Real-World Analogy
Water spreading from a tap: in the first second it fills all adjacent cells, then cells adjacent to those, etc. The number of seconds to fill a cell = shortest path distance.

### Visual Walkthrough
```
Grid (0=open, 1=blocked):
0 0 0
0 1 0
0 0 0

BFS from (0,0) to (2,2):
Level 0: enqueue (0,0)
Level 1: enqueue (0,1),(1,0)
Level 2: enqueue (0,2),(2,0)   [(1,1) blocked]
Level 3: enqueue (1,2),(2,1)  [from (0,2) and (2,0)]  (also (2,1) from (2,0))
Level 4: enqueue (2,2) from (1,2) or (2,1) → distance = 4

Rotting Oranges (multi-source):
  Start: all rotten oranges in queue at time 0
  Each step: spread rot to adjacent fresh oranges
  Answer: time when last fresh orange rots
```

### When TO use this pattern
- Shortest path in unweighted graph/grid
- Minimum steps/moves to reach target
- Spreading simulation (fire, rot, infection)
- "Minimum distance from any source" (multi-source BFS)
- BFS with state when state space is the "graph"

### When NOT to use this pattern
- Weighted edges → Dijkstra
- Negative edges → Bellman-Ford
- Only need connectivity (not distance) → DFS is simpler
- All pairs shortest path → Floyd-Warshall

### Common Beginner Mistakes
- **Mark visited WHEN ENQUEUING, not when dequeuing**: avoids adding the same node multiple times to the queue (causes TLE)
- **Multi-source**: put ALL sources in queue before starting — don't do separate BFS for each
- **State BFS**: include all state components in the visited set (e.g., position + keys bitmask)
- **01 Matrix**: multi-source from all 0s simultaneously — don't BFS from each 1 separately (O(m²n²) vs O(mn))

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | "shortest path", "minimum steps", "minimum distance", spread simulation |
| Core Idea | BFS = level-by-level expansion; first arrival = shortest path |
| Trigger Keywords | "minimum steps", "shortest", "nearest", "minimum moves", "spread" |
| Avoid When | Weighted edges (use Dijkstra) or need all paths (use DFS/backtracking) |
| Time Complexity | O(V + E) or O(m × n) for grids |
| Space Complexity | O(V) or O(m × n) |

**Gotchas:**
- Mark visited on enqueue, not dequeue
- Multi-source BFS: all sources in queue at level 0
- State BFS (Word Ladder, Lock): the "graph" is implicit; visited = set of states
- Word Ladder: generate all one-edit-away words; check if in wordSet

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"minimum number of steps/moves"` + grid → BFS
- `"shortest path"` + unweighted → BFS
- `"rotting oranges"`, `"walls and gates"` → multi-source BFS
- `"01 Matrix"` → multi-source BFS from all 0s
- `"word ladder"` → BFS on implicit word graph
- `"open the lock"` → BFS on state space (4-digit combination)

---

## 4. C++ Template

```cpp
/*
 * Pattern: BFS Shortest Path
 * Time: O(V+E) / O(m*n) | Space: O(V) / O(m*n)
 */

// SINGLE-SOURCE BFS (grid)
int bfsShortestPath(vector<vector<int>>& grid, pair<int,int> src, pair<int,int> dst) {
    int rows = grid.size(), cols = grid[0].size();
    vector<vector<bool>> vis(rows, vector<bool>(cols, false));
    queue<pair<int,int>> q;
    q.push(src); vis[src.first][src.second] = true;
    int steps = 0;
    int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    while (!q.empty()) {
        int sz = q.size();
        while (sz--) {
            auto [r, c] = q.front(); q.pop();
            if (make_pair(r,c) == dst) return steps;
            for (auto& d : dirs) {
                int nr = r+d[0], nc = c+d[1];
                if (nr<0||nr>=rows||nc<0||nc>=cols||vis[nr][nc]||grid[nr][nc]==1) continue;
                vis[nr][nc] = true;
                q.push({nr, nc});
            }
        }
        steps++;
    }
    return -1;
}

// MULTI-SOURCE BFS
void multiSourceBFS(vector<vector<int>>& grid) {
    int rows = grid.size(), cols = grid[0].size();
    queue<pair<int,int>> q;
    // seed all sources
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            if (grid[r][c] == 0) q.push({r, c});  // source condition
    int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        for (auto& d : dirs) {
            int nr = r+d[0], nc = c+d[1];
            if (nr<0||nr>=rows||nc<0||nc>=cols||grid[nr][nc]!=TARGET) continue;
            grid[nr][nc] = grid[r][c] + 1;  // distance from nearest source
            q.push({nr, nc});
        }
    }
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"Since all edges have equal weight (or the grid has uniform step cost), BFS gives the shortest path. I'll use a queue, seed it with the source(s), mark them visited immediately on enqueue, and expand level by level. The first time I reach the destination is the minimum distance.

For multi-source BFS like Rotting Oranges: I put all initial rotten oranges in the queue at time 0. Each BFS level represents one minute — fresh oranges adjacent to rotten ones get infected and join the queue."

### Interview Flow Checklist
- [ ] Identify: single source or multi-source?
- [ ] Decide state representation (just position, or position + extra state)
- [ ] Mark visited ON ENQUEUE
- [ ] Process level by level if tracking distance
- [ ] Handle unreachable case

---

## 6. Problems

---

### Problem 1: 994. Rotting Oranges
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/rotting-oranges/
**Why this pattern fits:** Multi-source BFS; all rotten oranges spread simultaneously

**Optimal C++ Solution:**
```cpp
int orangesRotting(vector<vector<int>>& grid) {
    int rows = grid.size(), cols = grid[0].size();
    queue<pair<int,int>> q;
    int fresh = 0;
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 2) q.push({r, c});
            else if (grid[r][c] == 1) fresh++;
        }
    if (fresh == 0) return 0;
    int minutes = 0;
    int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    while (!q.empty()) {
        int sz = q.size();
        bool spread = false;
        while (sz--) {
            auto [r, c] = q.front(); q.pop();
            for (auto& d : dirs) {
                int nr = r+d[0], nc = c+d[1];
                if (nr<0||nr>=rows||nc<0||nc>=cols||grid[nr][nc]!=1) continue;
                grid[nr][nc] = 2;
                fresh--;
                spread = true;
                q.push({nr, nc});
            }
        }
        if (spread) minutes++;
    }
    return fresh == 0 ? minutes : -1;
}
```
**Edge Cases:** [ ] No fresh oranges (return 0), [ ] Fresh oranges isolated from rotten ones (return -1)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 542. 01 Matrix
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/01-matrix/
**Why this pattern fits:** Multi-source BFS from all 0s simultaneously

**Optimal C++ Solution:**
```cpp
vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
    int rows = mat.size(), cols = mat[0].size();
    vector<vector<int>> dist(rows, vector<int>(cols, INT_MAX));
    queue<pair<int,int>> q;
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            if (mat[r][c] == 0) { dist[r][c] = 0; q.push({r, c}); }
    int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        for (auto& d : dirs) {
            int nr = r+d[0], nc = c+d[1];
            if (nr<0||nr>=rows||nc<0||nc>=cols) continue;
            if (dist[nr][nc] > dist[r][c] + 1) {
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }
    return dist;
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 3: 1091. Shortest Path in Binary Matrix
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/shortest-path-in-binary-matrix/
**Why this pattern fits:** 8-directional BFS from (0,0) to (n-1,n-1)

**Optimal C++ Solution:**
```cpp
int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
    int n = grid.size();
    if (grid[0][0] == 1 || grid[n-1][n-1] == 1) return -1;
    queue<tuple<int,int,int>> q;  // (row, col, dist)
    q.push({0, 0, 1});
    grid[0][0] = 1;  // mark visited
    int dirs[8][2] = {{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};
    while (!q.empty()) {
        auto [r, c, d] = q.front(); q.pop();
        if (r == n-1 && c == n-1) return d;
        for (auto& dir : dirs) {
            int nr = r+dir[0], nc = c+dir[1];
            if (nr<0||nr>=n||nc<0||nc>=n||grid[nr][nc]!=0) continue;
            grid[nr][nc] = 1;
            q.push({nr, nc, d+1});
        }
    }
    return -1;
}
```
**Edge Cases:** [ ] Start or end cell is blocked, [ ] 1x1 grid with 0

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 4: 127. Word Ladder
**Difficulty:** Hard
**Leetcode:** https://leetcode.com/problems/word-ladder/
**Why this pattern fits:** BFS on implicit graph where nodes = words, edges = one-character changes

**Optimal C++ Solution:**
```cpp
int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    unordered_set<string> wordSet(wordList.begin(), wordList.end());
    if (!wordSet.count(endWord)) return 0;
    queue<string> q;
    q.push(beginWord);
    wordSet.erase(beginWord);
    int steps = 1;
    while (!q.empty()) {
        int sz = q.size();
        while (sz--) {
            string word = q.front(); q.pop();
            if (word == endWord) return steps;
            for (int i = 0; i < (int)word.size(); i++) {
                char orig = word[i];
                for (char ch = 'a'; ch <= 'z'; ch++) {
                    if (ch == orig) continue;
                    word[i] = ch;
                    if (wordSet.count(word)) {
                        wordSet.erase(word);
                        q.push(word);
                    }
                    word[i] = orig;
                }
            }
        }
        steps++;
    }
    return 0;
}
```
**Complexity Analysis:**
- Time: O(M² × N) — M = word length, N = wordList size
- Space: O(M × N)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 5: 752. Open the Lock
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/open-the-lock/
**Why this pattern fits:** BFS on state space (4-digit combination strings)

**Optimal C++ Solution:**
```cpp
int openLock(vector<string>& deadends, string target) {
    unordered_set<string> dead(deadends.begin(), deadends.end());
    if (dead.count("0000")) return -1;
    queue<string> q;
    unordered_set<string> vis;
    q.push("0000"); vis.insert("0000");
    int steps = 0;
    while (!q.empty()) {
        int sz = q.size();
        while (sz--) {
            string cur = q.front(); q.pop();
            if (cur == target) return steps;
            for (int i = 0; i < 4; i++) {
                for (int d : {1, -1}) {
                    string next = cur;
                    next[i] = (next[i] - '0' + d + 10) % 10 + '0';
                    if (!vis.count(next) && !dead.count(next)) {
                        vis.insert(next);
                        q.push(next);
                    }
                }
            }
        }
        steps++;
    }
    return -1;
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 6: 1293. Shortest Path with Obstacles Elimination
**Difficulty:** Hard
**Leetcode:** https://leetcode.com/problems/shortest-path-in-a-grid-with-obstacles-elimination/
**Why this pattern fits:** BFS with state (row, col, remaining eliminations)

**Optimal C++ Solution:**
```cpp
int shortestPath(vector<vector<int>>& grid, int k) {
    int rows = grid.size(), cols = grid[0].size();
    // state: (row, col, eliminations_remaining)
    vector<vector<vector<bool>>> vis(rows, vector<vector<bool>>(cols, vector<bool>(k+1, false)));
    queue<tuple<int,int,int,int>> q;  // row, col, elim, steps
    q.push({0, 0, k, 0});
    vis[0][0][k] = true;
    int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    while (!q.empty()) {
        auto [r, c, elim, steps] = q.front(); q.pop();
        if (r == rows-1 && c == cols-1) return steps;
        for (auto& d : dirs) {
            int nr = r+d[0], nc = c+d[1];
            if (nr<0||nr>=rows||nc<0||nc>=cols) continue;
            int newElim = elim - grid[nr][nc];
            if (newElim < 0 || vis[nr][nc][newElim]) continue;
            vis[nr][nc][newElim] = true;
            q.push({nr, nc, newElim, steps+1});
        }
    }
    return -1;
}
```
**Complexity Analysis:**
- Time: O(m × n × k)
- Space: O(m × n × k)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 7: 1162. As Far from Land as Possible
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/as-far-from-land-as-possible/
**Why this pattern fits:** Multi-source BFS from all land cells; find max distance water cell

**Optimal C++ Solution:**
```cpp
int maxDistance(vector<vector<int>>& grid) {
    int n = grid.size();
    queue<pair<int,int>> q;
    for (int r = 0; r < n; r++)
        for (int c = 0; c < n; c++)
            if (grid[r][c] == 1) q.push({r, c});
    if (q.size() == 0 || q.size() == (size_t)(n*n)) return -1;
    int dist = -1;
    int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        for (auto& d : dirs) {
            int nr = r+d[0], nc = c+d[1];
            if (nr<0||nr>=n||nc<0||nc>=n||grid[nr][nc]!=0) continue;
            grid[nr][nc] = grid[r][c] + 1;
            dist = max(dist, grid[nr][nc] - 1);
            q.push({nr, nc});
        }
    }
    return dist;
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> You have a grid of 0s and 1s. Find the minimum number of 0s you must flip to 1 to create a path from top-left to bottom-right (moving 4-directionally through 1s only).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** 0-1 BFS (deque-based) or Dijkstra on grid
**Reason:** Cost of traversal: 0 if cell is already 1, 1 if you must flip a 0. This is a shortest-path problem with edge weights 0 and 1. Use 0-1 BFS: push to front if cost 0, push to back if cost 1. LC 1368.
</details>

---

**Drill 2:**
> Given a snake and ladder board, find the minimum dice rolls to reach square n².

<details>
<summary>Click to reveal answer</summary>
**Pattern:** BFS on state (current square)
**Reason:** Each "edge" from square i goes to squares i+1 through i+6 (then applies snake/ladder). BFS guarantees minimum rolls. State = current square position. LC 909.
</details>

---

**Drill 3:**
> Given a grid with start, end, and "portals" (stepping on one teleports you to the other), find shortest path.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** BFS with teleport edges
**Reason:** Standard BFS but when you step on a portal cell, also enqueue the destination portal as a free move (distance unchanged). Treat portals as 0-cost edges.
</details>

---

**Drill 4:**
> Given a binary tree, find the minimum number of edges to flip to make it a valid BST.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Not BFS — Tree DP or greedy
**Reason:** This is a tree structure problem, not a graph traversal. Analyze the subtree violations and fix greedily or with DP. BFS doesn't naturally apply here without reformulating as a graph problem.
</details>

---

**Drill 5:**
> You have a map with cities and roads. Some roads are toll roads (cost 1). Find the path with minimum tolls between two cities.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** 0-1 BFS (deque)
**Reason:** Free roads = cost 0, toll roads = cost 1. Use deque-based BFS: push_front for 0-cost, push_back for 1-cost. Finds minimum-toll path in O(V+E). More efficient than Dijkstra for binary edge weights.
</details>

---

## 8. Complexity Cheatsheet

| Variant | Time | Space | Notes |
|---------|------|-------|-------|
| BFS shortest path (grid) | O(m×n) | O(m×n) | Each cell visited once |
| Multi-source BFS | O(m×n) | O(m×n) | All sources in queue at start |
| Word Ladder | O(M²×N) | O(M×N) | M=word len, N=dict size |
| State BFS (lock, keys) | O(states × branching) | O(states) | State must include all relevant info |
| BFS with k eliminations | O(m×n×k) | O(m×n×k) | Add k to state |

---

## 9. Common Follow-up Questions

1. What if the graph is weighted? (Use Dijkstra — BFS no longer guarantees shortest path)
2. Bidirectional BFS? (Start from both source and destination; much faster in practice — see P29)
3. Can you do BFS iteratively without level tracking? (Yes — use `(node, dist)` tuple in queue instead of counting level sizes)
4. How does 0-1 BFS differ from standard? (Use deque: push_front for 0-cost edges, push_back for 1-cost. O(V+E) like BFS but handles binary weights)

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| Multi-source | Start from all sources simultaneously | 994. Rotting Oranges, 542. 01 Matrix |
| State machine | Track position + extra state | 752. Open Lock, 1293. Obstacles |
| Bidirectional BFS | Source and target both known; prune search | 127. Word Ladder optimization |
| Dijkstra | BFS + weighted edges | P23. Dijkstra |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
