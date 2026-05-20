# Pattern 40: DP on Graphs (DAG DP, Floyd-Warshall)

## Category
Dynamic Programming

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 329. Longest Increasing Path in Matrix | Hard | https://leetcode.com/problems/longest-increasing-path-in-a-matrix/ |
| 2 | 399. Evaluate Division | Medium | https://leetcode.com/problems/evaluate-division/ |
| 3 | 1334. Find the City With the Smallest Number of Neighbors | Medium | https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/ |

---

## 1. First-Timer Explanation

### What is this pattern?
**DP on Graphs** applies when the graph is a DAG (directed acyclic graph) or can be processed in a specific order. Since DAGs have no cycles, we can process nodes in topological order and guarantee dependencies are computed before dependents.

**DAG DP:**
- Process nodes in topological order
- `dp[u]` = optimal value for some property when starting/ending at u
- Transition: `dp[u] = combine(dp[v] for all v reachable from u)`
- Example: longest path in DAG = max(dp[v] + 1) for neighbors v of u

**Longest Increasing Path in Matrix:**
- Treat each cell as a node; edges go from smaller to larger value
- This implicit graph is a DAG (edges only go from smaller → larger)
- DFS with memoization = DP on DAG

**Floyd-Warshall (All-Pairs Shortest Path):**
- dp[i][j][k] = shortest path from i to j using only nodes 0..k as intermediaries
- `dp[i][j][k] = min(dp[i][j][k-1], dp[i][k][k-1] + dp[k][j][k-1])`
- Implemented in-place: for k in 0..n: for i: for j: `dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j])`

### Visual Walkthrough
```
Longest Increasing Path in Matrix:
1 2
4 3

Directed edges (smaller → larger):
1→2, 1→4, 2→3, 4→3

Implicit DAG — DFS with memo:
  LIP(0,0)=1: check right(1→2): LIP(0,1)=2, check down(1→4): LIP(1,0)=2
    LIP(0,1)=2: check right(none), down(2→3): LIP(1,1)=1... wait 3>2? Yes
      LIP(1,1)=1 (3 is biggest neighbor, no larger cells)
    LIP(0,1) = 1 + LIP(1,1) = 2? Wait 3>2 so: LIP(1,1)=1, LIP(0,1)=2
    LIP(1,0)=2: check right(4→3? No, 3<4), check down(none) → LIP(1,0)=1
  LIP(0,0) = 1 + max(LIP(0,1), LIP(1,0)) = 1 + max(2,1) = 3?

Actually: 1→2→3 has length 3, 1→4 has length 2 → answer = 3
```

### When TO use this pattern
- Longest/shortest path in DAG (or matrix with monotone direction)
- All-pairs shortest path (Floyd-Warshall)
- Reachability with optimal metric along path
- Any path problem on implicit DAG (increasing sequences, etc.)

### When NOT to use this pattern
- Graph has cycles (need to break cycles or use Bellman-Ford/Dijkstra)
- Only single-source shortest path (use Dijkstra/BFS instead)
- Grid shortest path with obstacles (BFS is simpler)

### Common Beginner Mistakes
- **LIP**: visiting in DFS order is safe because the implicit DAG (smaller→larger) has no cycles; memoize to avoid recomputation
- **Floyd-Warshall**: process k in outer loop, then i and j; using wrong order corrupts results
- **Detect negative cycles in Floyd-Warshall**: if dist[i][i] < 0 after running → negative cycle reachable from i
- **LIP vs LCS**: LIP is on a 2D matrix (not sequence); moves 4-directionally; no diagonal

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | "longest path in DAG", "all-pairs shortest", "increasing path in matrix" |
| Core Idea | DAG DP: process in topological order; Floyd-Warshall: try each intermediate node |
| Trigger Keywords | "longest increasing path", "city threshold distance", "evaluate division" |
| Avoid When | Graph has cycles (Floyd-Warshall handles negative weights but not negative cycles) |
| Time Complexity | O(V+E) DAG DP; O(V³) Floyd-Warshall |
| Space Complexity | O(V+E) or O(V²) |

**Gotchas:**
- Floyd-Warshall: initialize dist[i][i]=0, dist[i][j]=edge weight or INF, then triple loop
- LIP: DFS + memo; each cell's memoized value = longest path starting from that cell
- Negative cycle detection: dist[i][i] < 0 → negative cycle through i
- Floyd-Warshall with INT_MAX: `dist[i][k] + dist[k][j]` overflows if either is INT_MAX; use INF/2

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"longest increasing path in matrix"` → DAG DP via DFS + memoization
- `"all-pairs shortest path"` or `"threshold distance"` → Floyd-Warshall
- `"evaluate division"` → graph reachability with multiplicative weights (BFS/DFS or Floyd-Warshall)
- `"transitive closure"` → Floyd-Warshall with boolean (reachable/not)
- `"DAG"` + `"longest path"` → topological sort + DP

---

## 4. C++ Template

```cpp
/*
 * Pattern: DP on Graphs
 * DAG DP: O(V+E) | Floyd-Warshall: O(V^3)
 */

// LONGEST INCREASING PATH IN MATRIX (DAG DP via DFS + memo)
int longestIncreasingPath(vector<vector<int>>& matrix) {
    int rows = matrix.size(), cols = matrix[0].size(), best = 0;
    vector<vector<int>> memo(rows, vector<int>(cols, 0));
    int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

    function<int(int,int)> dfs = [&](int r, int c) -> int {
        if (memo[r][c]) return memo[r][c];
        memo[r][c] = 1;
        for (auto& d : dirs) {
            int nr = r+d[0], nc = c+d[1];
            if (nr<0||nr>=rows||nc<0||nc>=cols||matrix[nr][nc]<=matrix[r][c]) continue;
            memo[r][c] = max(memo[r][c], dfs(nr,nc) + 1);
        }
        return memo[r][c];
    };

    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            best = max(best, dfs(r, c));
    return best;
}

// FLOYD-WARSHALL (all-pairs shortest path)
vector<vector<int>> floydWarshall(int n, vector<tuple<int,int,int>>& edges) {
    const int INF = 1e9;
    vector<vector<int>> dist(n, vector<int>(n, INF));
    for (int i = 0; i < n; i++) dist[i][i] = 0;
    for (auto& [u, v, w] : edges) {
        dist[u][v] = min(dist[u][v], w);
        dist[v][u] = min(dist[v][u], w);  // undirected; remove for directed
    }
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    return dist;
}

// DAG LONGEST PATH (topological sort + DP)
int longestPathDAG(int n, vector<vector<int>>& adj) {
    vector<int> indegree(n, 0);
    for (int u = 0; u < n; u++) for (int v : adj[u]) indegree[v]++;
    queue<int> q;
    vector<int> dp(n, 0);
    for (int i = 0; i < n; i++) if (indegree[i] == 0) { q.push(i); }
    int best = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        best = max(best, dp[u]);
        for (int v : adj[u]) {
            dp[v] = max(dp[v], dp[u] + 1);
            if (--indegree[v] == 0) q.push(v);
        }
    }
    return best;
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"For the longest increasing path, I treat each cell as a node with directed edges to cells with strictly greater values. Since edges always go from smaller to larger values, this forms a DAG — no cycles possible. I use DFS with memoization: `memo[r][c]` = length of the longest increasing path starting at (r,c). Since the graph is acyclic, the DFS terminates and each cell is computed once."

"For all-pairs shortest path: Floyd-Warshall. For each intermediate node k, I check if routing through k improves any (i,j) path. After processing all k from 0 to n-1, dist[i][j] holds the shortest path between i and j."

### Interview Flow Checklist
- [ ] For LIP: write DFS, check bounds + increasing condition, return memoized or compute
- [ ] For Floyd-Warshall: init dist matrix, triple loop (k outer, i/j inner), handle overflow
- [ ] For DAG DP: topological sort first, then process in that order
- [ ] Return appropriate answer (max of all dp[] for LIP, specific dist for APSP)

---

## 6. Problems

---

### Problem 1: 329. Longest Increasing Path in Matrix
**Difficulty:** Hard
**Leetcode:** https://leetcode.com/problems/longest-increasing-path-in-a-matrix/
**Optimal C++ Solution:**
```cpp
int longestIncreasingPath(vector<vector<int>>& matrix) {
    int rows = matrix.size(), cols = matrix[0].size(), best = 0;
    vector<vector<int>> memo(rows, vector<int>(cols, 0));
    int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    function<int(int,int)> dfs = [&](int r, int c) -> int {
        if (memo[r][c]) return memo[r][c];
        memo[r][c] = 1;
        for (auto& d : dirs) {
            int nr = r+d[0], nc = c+d[1];
            if (nr<0||nr>=rows||nc<0||nc>=cols||matrix[nr][nc]<=matrix[r][c]) continue;
            memo[r][c] = max(memo[r][c], 1 + dfs(nr, nc));
        }
        return memo[r][c];
    };
    for (int r = 0; r < rows; r++)
        for (int c = 0; c < cols; c++)
            best = max(best, dfs(r, c));
    return best;
}
```
**Edge Cases:** [ ] Single cell, [ ] All same values (length 1), [ ] Decreasing matrix

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 1334. Find the City With Smallest Number of Neighbors at Threshold Distance
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/
**Optimal C++ Solution:**
```cpp
int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
    const int INF = 1e8;
    vector<vector<int>> dist(n, vector<int>(n, INF));
    for (int i = 0; i < n; i++) dist[i][i] = 0;
    for (auto& e : edges) { dist[e[0]][e[1]] = e[2]; dist[e[1]][e[0]] = e[2]; }
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
    int ans = -1, minReach = n+1;
    for (int i = 0; i < n; i++) {
        int reach = 0;
        for (int j = 0; j < n; j++) if (i != j && dist[i][j] <= distanceThreshold) reach++;
        if (reach <= minReach) { minReach = reach; ans = i; }
    }
    return ans;
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 3: 399. Evaluate Division
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/evaluate-division/
**Why this pattern fits:** Weighted graph; queries = product of edge weights along path (Floyd-Warshall with multiplication)

**Optimal C++ Solution:**
```cpp
vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values,
                             vector<vector<string>>& queries) {
    unordered_map<string, unordered_map<string, double>> graph;
    for (int i = 0; i < (int)equations.size(); i++) {
        string a = equations[i][0], b = equations[i][1];
        graph[a][b] = values[i];
        graph[b][a] = 1.0 / values[i];
        graph[a][a] = graph[b][b] = 1.0;
    }
    // Floyd-Warshall: if a/b = x and b/c = y, then a/c = x*y
    for (auto& [k, _] : graph)
        for (auto& [i, _2] : graph)
            for (auto& [j, _3] : graph)
                if (graph[i].count(k) && graph[k].count(j))
                    graph[i][j] = graph[i][k] * graph[k][j];
    vector<double> ans;
    for (auto& q : queries) {
        if (!graph.count(q[0]) || !graph[q[0]].count(q[1])) ans.push_back(-1.0);
        else ans.push_back(graph[q[0]][q[1]]);
    }
    return ans;
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> In a city map (directed graph), find the number of paths from A to B that visit at most K distinct cities.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** DAG DP or BFS with depth constraint
**Reason:** If the graph is a DAG: dp[v][k] = number of paths from A to v using at most k edges. Process in topological order. If general graph: BFS/DFS tracking (current node, hops_used). K-hop shortest path = Bellman-Ford with K iterations.
</details>

---

**Drill 2:**
> Find the minimum cost path in a grid where you can move in any direction but can only move to cells with strictly decreasing values (no cycles guaranteed).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** DAG DP via DFS + memoization (same as LIP)
**Reason:** Moving only to strictly decreasing cells makes this a DAG (edges from larger → smaller). DFS with memo: `cost[r][c]` = minimum cost path starting at (r,c). Cost at each cell = cell cost + min(cost of reachable neighbors). No cycle issues since values strictly decrease.
</details>

---

**Drill 3:**
> Given a social network, find for each person the minimum "influence chain length" to reach everyone in the network.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** All-Pairs Shortest Path (Floyd-Warshall or BFS from each node)
**Reason:** Each person = source. BFS from each person gives shortest path to all others. Floyd-Warshall works for small n. The "influence chain" for person i = max(dist[i][j]) for all j reachable from i (eccentricity of the graph).
</details>

---

**Drill 4:**
> You have a sequence of events, each with a time. Event B can only happen after event A if there's a dependency. Find the earliest time all events can complete (critical path).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** DAG DP — critical path method
**Reason:** Build DAG where edge A→B with weight = duration of B. dp[v] = earliest start time of event v = max(dp[u] + weight(u,v)) over all predecessors u. Process in topological order (Kahn's algorithm). Critical path = the longest path from start to end.
</details>

---

**Drill 5:**
> Given a directed graph, determine if a specific node can reach all other nodes, and find the minimum number of edges to add if it can't.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** DFS/BFS reachability + SCC condensation
**Reason:** DFS/BFS from the node; check if all nodes visited. If not, condense SCCs. The condensed DAG shows which "super-nodes" are unreachable. Adding edges to connect them = number of super-nodes with in-degree 0 in the condensed DAG (excluding the source SCC).
</details>

---

## 8. Complexity Cheatsheet

| Variant | Time | Space | Notes |
|---------|------|-------|-------|
| LIP (DFS + memo) | O(m×n) | O(m×n) | Each cell visited once |
| DAG DP (topo + DP) | O(V+E) | O(V) | Linear in graph size |
| Floyd-Warshall | O(V³) | O(V²) | All-pairs, handles negative weights |
| BFS all-pairs | O(V(V+E)) | O(V+E) | Better for sparse graphs |
| Dijkstra all-pairs | O(V(V+E)logV) | O(V+E) | Best for sparse non-negative |

---

## 9. Common Follow-up Questions

1. What's the difference between LIP and standard grid shortest path? (LIP: must go strictly increasing → DAG, DFS + memo. Grid shortest path: BFS/Dijkstra depending on weights — no DAG guarantee)
2. Floyd-Warshall vs all-pairs Dijkstra? (Floyd-Warshall: O(V³), handles negative weights (not negative cycles), simple code. All-pairs Dijkstra: O(V(V+E)log V), faster for sparse graphs, requires non-negative weights)
3. Can Floyd-Warshall detect negative cycles? (Yes: if dist[i][i] < 0 after running, there's a negative cycle through i)
4. How to reconstruct the actual path in Floyd-Warshall? (Maintain next[i][j] = first node after i on the shortest i→j path. Update: if dist[i][k]+dist[k][j] < dist[i][j]: next[i][j] = next[i][k]. Trace: i → next[i][j] → ... → j)

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| Topological Sort | DAG DP processes in topo order | Longest path in DAG |
| DFS + Memoization | Top-down DAG DP | 329. LIP in Matrix |
| Dijkstra | Single-source weighted shortest path | P23. Dijkstra |
| Bellman-Ford | K-hop shortest path | P24. Bellman-Ford |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
