# Pattern 18: DFS — Connected Components / Island Counting

## Category
Graphs

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 200. Number of Islands | Medium | https://leetcode.com/problems/number-of-islands/ |
| 2 | 695. Max Area of Island | Medium | https://leetcode.com/problems/max-area-of-island/ |
| 3 | 733. Flood Fill | Easy | https://leetcode.com/problems/flood-fill/ |
| 4 | 547. Number of Provinces | Medium | https://leetcode.com/problems/number-of-provinces/ |
| 5 | 130. Surrounded Regions | Medium | https://leetcode.com/problems/surrounded-regions/ |
| 6 | 417. Pacific Atlantic Water Flow | Medium | https://leetcode.com/problems/pacific-atlantic-water-flow/ |
| 7 | 841. Keys and Rooms | Medium | https://leetcode.com/problems/keys-and-rooms/ |
| 8 | 1020. Number of Enclaves | Medium | https://leetcode.com/problems/number-of-enclaves/ |
| 9 | 1254. Number of Closed Islands | Medium | https://leetcode.com/problems/number-of-closed-islands/ |
| 10 | 1905. Count Sub Islands | Medium | https://leetcode.com/problems/count-sub-islands/ |
| 11 | 2101. Detonate the Maximum Bombs | Medium | https://leetcode.com/problems/detonate-the-maximum-bombs/ |

---

## 1. First-Timer Explanation

### What is this pattern?
A **connected component** is a maximal group of nodes where every node is reachable from every other. Island counting is the grid version: each group of adjacent `1`s is an island (= one component).

**The algorithm:**
1. Iterate over every unvisited node
2. When you find one, launch a DFS that **marks all reachable nodes as visited**
3. Each DFS launch = one new component; increment counter

The DFS itself: mark current as visited, then recurse on all valid unvisited neighbors.

**Grid variant**: neighbors are up/down/left/right (4-directional). Sometimes 8-directional.
**Graph variant**: adjacency list or matrix — iterate over all listed neighbors.

### Real-World Analogy
Counting separate landmasses on a map. Start on any unexplored land, walk until you've visited every connected piece, then count that as one island. Jump to the next unvisited land square and repeat.

### Visual Walkthrough
```
Grid:
1 1 0 0 0
1 1 0 0 0
0 0 1 0 0
0 0 0 1 1

Islands:
  Start at (0,0): DFS marks (0,0),(0,1),(1,0),(1,1) → island #1
  (2,2): DFS marks (2,2) → island #2
  (3,3): DFS marks (3,3),(3,4) → island #3
  Answer: 3

DFS from (0,0):
  Visit (0,0) → mark visited
    Visit (0,1) → mark visited (no unvisited neighbors)
    Visit (1,0) → mark visited
      Visit (1,1) → mark visited (no unvisited neighbors)
```

### When TO use this pattern
- Count distinct groups/regions
- Find size of largest group
- Flood fill / region marking
- Check if two nodes are connected
- "Surrounded" regions (DFS from border, then flip)
- Multi-source reachability (Pacific Atlantic)

### When NOT to use this pattern
- Shortest path needed → use BFS
- Weighted edges → Dijkstra/Bellman-Ford
- Need topological order → different DFS variant

### Common Beginner Mistakes
- **Not marking visited before recursing**: causes infinite loops on cycles or grids
- **Out-of-bounds check**: always validate row/col before accessing grid
- **Mutating input**: if you can't modify the grid, use a separate `visited` array
- **Diagonal neighbors**: standard island problems are 4-directional, not 8
- **Surrounded Regions**: mark safe cells (touching border) FIRST, then flip — don't try to detect "surrounded" directly

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | "number of islands", "connected components", "regions", "provinces" |
| Core Idea | Mark-and-count: DFS from unvisited node marks all reachable; each launch = 1 component |
| Trigger Keywords | "island", "province", "component", "region", "connected", "flood fill" |
| Avoid When | Shortest path needed (use BFS) |
| Time Complexity | O(m × n) for grid, O(V + E) for graph |
| Space Complexity | O(m × n) recursion stack worst case |

**Gotchas:**
- Mark visited at entry of DFS (before recursing into neighbors)
- Grid bounds check: `r >= 0 && r < rows && c >= 0 && c < cols`
- Surrounded Regions: reverse-think — mark anything touching border as safe, then flip remaining
- Pacific Atlantic: run two separate DFS/BFS from each ocean, find intersection

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"number of islands"` → count DFS launches on `1` cells
- `"max area of island"` → DFS returns component size; track max
- `"flood fill"` → DFS marks connected region with new color
- `"provinces"` → graph (adjacency matrix), count DFS launches
- `"surrounded regions"` → DFS from border to find safe cells; flip rest
- `"pacific atlantic"` → two DFS/BFS from border edges; find cells reachable by both

---

## 4. C++ Template

```cpp
/*
 * Pattern: DFS Connected Components
 * Time: O(m*n) grid / O(V+E) graph | Space: O(m*n) / O(V)
 */

// GRID: Number of Islands
int numIslands(vector<vector<char>>& grid) {
    int rows = grid.size(), cols = grid[0].size(), count = 0;

    function<void(int,int)> dfs = [&](int r, int c) {
        if (r < 0 || r >= rows || c < 0 || c >= cols) return;
        if (grid[r][c] != '1') return;
        grid[r][c] = '0';  // mark visited by sinking
        dfs(r+1,c); dfs(r-1,c); dfs(r,c+1); dfs(r,c-1);
    };

    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            if (grid[r][c] == '1') { dfs(r, c); count++; }

    return count;
}

// GRAPH: Number of Provinces (adjacency matrix)
int findCircleNum(vector<vector<int>>& isConnected) {
    int n = isConnected.size(), provinces = 0;
    vector<bool> visited(n, false);

    function<void(int)> dfs = [&](int node) {
        visited[node] = true;
        for (int j = 0; j < n; j++)
            if (isConnected[node][j] == 1 && !visited[j])
                dfs(j);
    };

    for (int i = 0; i < n; i++)
        if (!visited[i]) { dfs(i); provinces++; }

    return provinces;
}

// GRID: Max Area (DFS returns size)
int maxAreaOfIsland(vector<vector<int>>& grid) {
    int rows = grid.size(), cols = grid[0].size(), maxArea = 0;

    function<int(int,int)> dfs = [&](int r, int c) -> int {
        if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] == 0) return 0;
        grid[r][c] = 0;
        return 1 + dfs(r+1,c) + dfs(r-1,c) + dfs(r,c+1) + dfs(r,c-1);
    };

    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            maxArea = max(maxArea, dfs(r, c));

    return maxArea;
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"This is a connected components problem on a grid. I'll iterate over every cell; when I find an unvisited land cell, I launch a DFS that marks the entire island as visited. Each DFS launch increments the island count. The DFS itself just checks bounds, whether the cell is land, marks it visited, and recurses in 4 directions."

### Interview Flow Checklist
- [ ] Confirm grid dimensions and valid cell values
- [ ] Decide: modify input vs. separate visited array
- [ ] Write DFS with bounds check, type check, mark-visited, 4-directional recurse
- [ ] Outer loop: count DFS launches
- [ ] Test with disconnected islands and edge cases (empty grid, all water)

---

## 6. Problems

---

### Problem 1: 200. Number of Islands
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/number-of-islands/
**Optimal C++ Solution:**
```cpp
int numIslands(vector<vector<char>>& grid) {
    int rows = grid.size(), cols = grid[0].size(), count = 0;
    function<void(int,int)> dfs = [&](int r, int c) {
        if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] != '1') return;
        grid[r][c] = '0';
        dfs(r+1,c); dfs(r-1,c); dfs(r,c+1); dfs(r,c-1);
    };
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            if (grid[r][c] == '1') { dfs(r, c); count++; }
    return count;
}
```
**Edge Cases:** [ ] All water, [ ] All land (one island), [ ] Single cell

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 695. Max Area of Island
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/max-area-of-island/
**Optimal C++ Solution:**
```cpp
int maxAreaOfIsland(vector<vector<int>>& grid) {
    int rows = grid.size(), cols = grid[0].size(), best = 0;
    function<int(int,int)> dfs = [&](int r, int c) -> int {
        if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] == 0) return 0;
        grid[r][c] = 0;
        return 1 + dfs(r+1,c) + dfs(r-1,c) + dfs(r,c+1) + dfs(r,c-1);
    };
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            best = max(best, dfs(r, c));
    return best;
}
```
**Edge Cases:** [ ] No island (return 0), [ ] Single cell island

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 3: 733. Flood Fill
**Difficulty:** Easy
**Leetcode:** https://leetcode.com/problems/flood-fill/
**Optimal C++ Solution:**
```cpp
vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
    int oldColor = image[sr][sc];
    if (oldColor == color) return image;
    int rows = image.size(), cols = image[0].size();
    function<void(int,int)> dfs = [&](int r, int c) {
        if (r < 0 || r >= rows || c < 0 || c >= cols || image[r][c] != oldColor) return;
        image[r][c] = color;
        dfs(r+1,c); dfs(r-1,c); dfs(r,c+1); dfs(r,c-1);
    };
    dfs(sr, sc);
    return image;
}
```
**Edge Cases:** [ ] New color equals old color (early return to avoid infinite loop)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 4: 547. Number of Provinces
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/number-of-provinces/
**Optimal C++ Solution:**
```cpp
int findCircleNum(vector<vector<int>>& isConnected) {
    int n = isConnected.size(), count = 0;
    vector<bool> visited(n, false);
    function<void(int)> dfs = [&](int i) {
        visited[i] = true;
        for (int j = 0; j < n; j++)
            if (isConnected[i][j] && !visited[j]) dfs(j);
    };
    for (int i = 0; i < n; i++)
        if (!visited[i]) { dfs(i); count++; }
    return count;
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 5: 130. Surrounded Regions
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/surrounded-regions/
**Why this pattern fits:** DFS from border cells to mark safe 'O's; flip remaining 'O' to 'X'

**Approach:**
1. Run DFS from every 'O' on the border — mark all reachable 'O' as 'S' (safe)
2. Flip all remaining 'O' to 'X' (surrounded)
3. Flip all 'S' back to 'O'

**Optimal C++ Solution:**
```cpp
void solve(vector<vector<char>>& board) {
    int rows = board.size(), cols = board[0].size();
    function<void(int,int)> dfs = [&](int r, int c) {
        if (r < 0 || r >= rows || c < 0 || c >= cols || board[r][c] != 'O') return;
        board[r][c] = 'S';
        dfs(r+1,c); dfs(r-1,c); dfs(r,c+1); dfs(r,c-1);
    };
    // mark border-connected O's as safe
    for (int r = 0; r < rows; r++) { dfs(r, 0); dfs(r, cols-1); }
    for (int c = 0; c < cols; c++) { dfs(0, c); dfs(rows-1, c); }
    // flip
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++) {
            if (board[r][c] == 'O') board[r][c] = 'X';
            else if (board[r][c] == 'S') board[r][c] = 'O';
        }
}
```
**Edge Cases:** [ ] Board with no 'O', [ ] All cells are 'O' (none surrounded)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 6: 417. Pacific Atlantic Water Flow
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/pacific-atlantic-water-flow/
**Why this pattern fits:** Two DFS from ocean borders; find cells reachable by both

**Optimal C++ Solution:**
```cpp
vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
    int rows = heights.size(), cols = heights[0].size();
    vector<vector<bool>> pac(rows, vector<bool>(cols, false));
    vector<vector<bool>> atl(rows, vector<bool>(cols, false));

    function<void(int,int,vector<vector<bool>>&)> dfs = [&](int r, int c, vector<vector<bool>>& reach) {
        reach[r][c] = true;
        int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
        for (auto& d : dirs) {
            int nr = r + d[0], nc = c + d[1];
            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;
            if (reach[nr][nc]) continue;
            if (heights[nr][nc] < heights[r][c]) continue;  // water flows downhill
            dfs(nr, nc, reach);
        }
    };

    for (int r = 0; r < rows; r++) { dfs(r, 0, pac); dfs(r, cols-1, atl); }
    for (int c = 0; c < cols; c++) { dfs(0, c, pac); dfs(rows-1, c, atl); }

    vector<vector<int>> result;
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            if (pac[r][c] && atl[r][c]) result.push_back({r, c});
    return result;
}
```
**Complexity Analysis:**
- Time: O(m × n) — each cell visited twice at most
- Space: O(m × n) for two reachability arrays

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 7: 841. Keys and Rooms
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/keys-and-rooms/
**Optimal C++ Solution:**
```cpp
bool canVisitAllRooms(vector<vector<int>>& rooms) {
    int n = rooms.size();
    vector<bool> visited(n, false);
    function<void(int)> dfs = [&](int room) {
        visited[room] = true;
        for (int key : rooms[room])
            if (!visited[key]) dfs(key);
    };
    dfs(0);
    return all_of(visited.begin(), visited.end(), [](bool v){ return v; });
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 8: 1020. Number of Enclaves
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/number-of-enclaves/
**Why this pattern fits:** DFS from border land cells; count remaining unreachable land

**Optimal C++ Solution:**
```cpp
int numEnclaves(vector<vector<int>>& grid) {
    int rows = grid.size(), cols = grid[0].size();
    function<void(int,int)> dfs = [&](int r, int c) {
        if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] != 1) return;
        grid[r][c] = 0;
        dfs(r+1,c); dfs(r-1,c); dfs(r,c+1); dfs(r,c-1);
    };
    for (int r = 0; r < rows; r++) { dfs(r, 0); dfs(r, cols-1); }
    for (int c = 0; c < cols; c++) { dfs(0, c); dfs(rows-1, c); }
    int count = 0;
    for (auto& row : grid)
        for (int v : row) count += v;
    return count;
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 9: 1254. Number of Closed Islands
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/number-of-closed-islands/
**Optimal C++ Solution:**
```cpp
int closedIsland(vector<vector<int>>& grid) {
    int rows = grid.size(), cols = grid[0].size(), count = 0;
    function<bool(int,int)> dfs = [&](int r, int c) -> bool {
        if (r < 0 || r >= rows || c < 0 || c >= cols) return false;  // touches border
        if (grid[r][c] == 1) return true;  // water cell
        grid[r][c] = 1;  // mark visited
        bool top   = dfs(r-1, c);
        bool bot   = dfs(r+1, c);
        bool left  = dfs(r, c-1);
        bool right = dfs(r, c+1);
        return top && bot && left && right;
    };
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            if (grid[r][c] == 0 && dfs(r, c)) count++;
    return count;
}
```
**Edge Cases:** [ ] Island touching corner, [ ] No closed island

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 10: 1905. Count Sub Islands
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/count-sub-islands/
**Why this pattern fits:** DFS on grid2 islands; check if every cell is also land in grid1

**Optimal C++ Solution:**
```cpp
int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
    int rows = grid2.size(), cols = grid2[0].size(), count = 0;
    function<bool(int,int)> dfs = [&](int r, int c) -> bool {
        if (r < 0 || r >= rows || c < 0 || c >= cols || grid2[r][c] == 0) return true;
        grid2[r][c] = 0;
        bool isSub = (grid1[r][c] == 1);  // must be land in grid1
        // use & not && to ensure full DFS (don't short-circuit)
        isSub &= dfs(r+1,c); isSub &= dfs(r-1,c);
        isSub &= dfs(r,c+1); isSub &= dfs(r,c-1);
        return isSub;
    };
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            if (grid2[r][c] == 1 && dfs(r, c)) count++;
    return count;
}
```
**Gotcha:** Use `&=` not `&&=` — must visit ALL cells in the island even if one fails

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 11: 2101. Detonate the Maximum Bombs
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/detonate-the-maximum-bombs/
**Why this pattern fits:** Build directed graph of which bomb can trigger which; count reachable from each source

**Optimal C++ Solution:**
```cpp
int maximumDetonation(vector<vector<int>>& bombs) {
    int n = bombs.size();
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; i++) {
        long long x1 = bombs[i][0], y1 = bombs[i][1], r = bombs[i][2];
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            long long dx = x1 - bombs[j][0], dy = y1 - bombs[j][1];
            if (dx*dx + dy*dy <= r*r) adj[i].push_back(j);
        }
    }
    int best = 0;
    function<int(int, vector<bool>&)> dfs = [&](int node, vector<bool>& vis) -> int {
        vis[node] = true;
        int cnt = 1;
        for (int nb : adj[node])
            if (!vis[nb]) cnt += dfs(nb, vis);
        return cnt;
    };
    for (int i = 0; i < n; i++) {
        vector<bool> vis(n, false);
        best = max(best, dfs(i, vis));
    }
    return best;
}
```
**Complexity Analysis:**
- Time: O(n² + n(V+E)) — graph build O(n²), DFS from each node
- Space: O(n²)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> Given a grid where `1` = infected cell and `0` = healthy cell, count how many infected regions exist. Then determine the minimum number of healthy cells adjacent to exactly one infected region.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** DFS Connected Components + BFS boundary
**Reason:** First, count infected regions using DFS (each DFS launch = one region). Then for each region, BFS outward one step to count distinct healthy border cells. Classic "count components + analyze perimeter."
</details>

---

**Drill 2:**
> You have a grid where some cells are "fires" (`F`) and some are "empty" (`E`). Fire spreads to adjacent cells every second. Given your starting position, find the latest second you can leave to reach the exit while never entering a fire cell.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Multi-source BFS (fires) + BFS (player) + binary search on time
**Reason:** First multi-source BFS from all fires gives fire arrival time per cell. Then binary search on wait time: can the player still reach exit if waiting t seconds? Player BFS avoids cells where fire arrives ≤ player's arrival time. LC 2258.
</details>

---

**Drill 3:**
> In a grid of rooms and walls, you can unlock doors by collecting keys. Each door has a color matching a key. Count the minimum steps to collect all keys.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** BFS with state (position + keys bitmask)
**Reason:** Standard BFS won't work because visiting the same cell with different key sets is different. State = (row, col, keys_bitmask). BFS over this state space. LC 864.
</details>

---

**Drill 4:**
> Given a boolean matrix, find the largest square of all 1s.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Dynamic Programming (not DFS)
**Reason:** DFS would count cells but not detect square shape efficiently. DP: dp[r][c] = side length of largest all-1 square with bottom-right at (r,c). dp[r][c] = min(dp[r-1][c], dp[r][c-1], dp[r-1][c-1]) + 1 if grid[r][c] == 1. LC 221.
</details>

---

**Drill 5:**
> You have a graph of servers where server A is connected to server B if they share a user. Find the number of isolated server clusters.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** DFS Connected Components on graph
**Reason:** Build adjacency list from shared-user relationship. Then count DFS launches (each = one cluster). Alternatively, Union-Find if relationships are given incrementally. Same as Number of Provinces but with adjacency list instead of matrix.
</details>

---

## 8. Complexity Cheatsheet

| Variant | Time | Space | Notes |
|---------|------|-------|-------|
| Number of Islands (grid) | O(m×n) | O(m×n) | Each cell visited once |
| Max Area | O(m×n) | O(m×n) | Returns component size |
| Number of Provinces (matrix) | O(n²) | O(n) | Adjacency matrix = O(n²) |
| Surrounded Regions | O(m×n) | O(m×n) | 2-pass: mark safe, flip rest |
| Pacific Atlantic | O(m×n) | O(m×n) | Two separate DFS from borders |
| Detonate Bombs | O(n² + n(V+E)) | O(n²) | Graph build + DFS per node |

---

## 9. Common Follow-up Questions

1. Can you solve Number of Islands iteratively? (Yes — use explicit stack instead of recursion; same logic)
2. What if the grid is very large and recursion depth is an issue? (Iterative DFS with explicit stack, or BFS)
3. How to restore the grid after counting? (Use a separate `visited` boolean array instead of mutating input)
4. What about 8-directional connectivity? (Add 4 diagonal directions to the neighbor loop)
5. What if you need to count the perimeter of each island? (For each land cell, count neighbors that are water or out-of-bounds; each = 1 perimeter unit)

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| BFS | Shortest path within a component | 1162. As Far from Land as Possible |
| Union-Find | Dynamic connectivity, merge components | P25 Union-Find |
| Multi-source BFS | Fire spread, distance from all sources | 994. Rotting Oranges |
| Bitmask BFS | State includes collected items | 864. Shortest Path with All Keys |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
