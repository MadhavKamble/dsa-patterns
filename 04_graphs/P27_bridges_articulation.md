# Pattern 27: Bridges and Articulation Points

## Category
Graphs

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 1192. Critical Connections in a Network | Hard | https://leetcode.com/problems/critical-connections-in-a-network/ |
| 2 | 1568. Minimum Number of Days to Disconnect Island | Hard | https://leetcode.com/problems/minimum-number-of-days-to-disconnect-island/ |

---

## 1. First-Timer Explanation

### What is this pattern?
**Bridge**: an edge whose removal disconnects the graph (increases number of connected components).
**Articulation Point**: a node whose removal disconnects the graph.

Both are found using Tarjan's DFS with **discovery time** and **low-link values**:
- `disc[u]` = time when u was first discovered in DFS
- `low[u]` = the smallest `disc` value reachable from u's subtree (via back edges)

**Bridge condition**: edge (u, v) is a bridge if `low[v] > disc[u]`
- Means: no back edge from v's subtree can reach u or above → removing (u,v) disconnects

**Articulation point condition**: node u is an articulation point if:
- u is root of DFS tree and has ≥ 2 children (removing it disconnects its subtrees), OR
- u is non-root and has a child v where `low[v] >= disc[u]` (no back edge from v's subtree bypasses u)

### Visual Walkthrough
```
Graph: 1-2-3-4-2 (4-2 edge creates cycle), 3-5

DFS from 1:
  disc[1]=0, disc[2]=1, disc[3]=2, disc[4]=3
  4→2 is back edge: low[4] = min(low[4], disc[2]) = 1
  low[3] = min(disc[3], low[4]) = min(2,1) = 1
  low[2] = min(disc[2], low[3]) = min(1,1) = 1

  disc[5]=4, low[5]=4 (no back edges from 5)
  Back at 3: low[3] = min(1, low[5]) = 1
  Check edge (3,5): low[5]=4 > disc[3]=2 → BRIDGE (removing 3-5 disconnects 5)
  Check edge (1,2): low[2]=1 > disc[1]=0? No (1>0 is true) → BRIDGE

Bridges: (1,2) and (3,5)

Articulation Points:
  Node 3: child 5 has low[5]=4 >= disc[3]=2 → YES, articulation point
  Node 1 (root): has 1 child (2) → NOT articulation point
```

### When TO use this pattern
- "Critical connections" / "critical servers" in a network
- "What single point of failure would disconnect the network?"
- Find edges/nodes that must not fail
- Network reliability analysis

### When NOT to use this pattern
- Simple connectivity check → DFS/UF
- Weighted shortest path → Dijkstra
- Need SCCs → Kosaraju/Tarjan SCC

### Common Beginner Mistakes
- **Parent edge vs back edge**: when computing low, skip the edge back to parent (otherwise every edge looks like a back edge in undirected graph). If there are multiple edges between same pair (multigraph), track edge ID, not node ID
- **Root special case**: DFS root is articulation point only if it has ≥ 2 DFS children
- **low update**: for unvisited neighbors → update from `low[v]`; for visited ancestors (back edges) → update from `disc[v]`

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | "critical connection", "bridge", "articulation point", "single point of failure" |
| Core Idea | Tarjan DFS: disc[u]=discovery time, low[u]=min disc reachable via back edges. Bridge: low[v] > disc[u] |
| Trigger Keywords | "critical server", "critical edge", "disconnects network", "remove one node/edge" |
| Avoid When | Simple connectivity (DFS), SCC (different Tarjan variant) |
| Time Complexity | O(V + E) |
| Space Complexity | O(V) |

**Gotchas:**
- Skip parent edge in low-link update (use parent node or edge ID)
- Root of DFS tree: count children — if ≥ 2 → articulation point
- Bridge: `low[v] > disc[u]`; articulation: `low[v] >= disc[u]` (note: >=, not >)
- Parallel edges: use edge index, not parent node, to skip the correct edge

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"critical connections"` → bridges
- `"if you remove this server/node, network splits"` → articulation points
- `"single point of failure"` → articulation points or bridges
- `"minimum removals to disconnect"` → may involve bridges/articulation points
- `"bridge edge"` → direct signal

---

## 4. C++ Template

```cpp
/*
 * Pattern: Bridges and Articulation Points
 * Time: O(V+E) | Space: O(V)
 */

// BRIDGES (critical edges)
vector<vector<int>> findBridges(int n, vector<vector<int>>& adj) {
    vector<int> disc(n, -1), low(n);
    int timer = 0;
    vector<vector<int>> bridges;

    function<void(int,int)> dfs = [&](int u, int parent) {
        disc[u] = low[u] = timer++;
        for (int v : adj[u]) {
            if (v == parent) continue;  // skip edge we came from
            if (disc[v] == -1) {
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] > disc[u]) bridges.push_back({u, v});
            } else {
                low[u] = min(low[u], disc[v]);
            }
        }
    };

    for (int i = 0; i < n; i++) if (disc[i] == -1) dfs(i, -1);
    return bridges;
}

// ARTICULATION POINTS
vector<int> findArticulationPoints(int n, vector<vector<int>>& adj) {
    vector<int> disc(n, -1), low(n), parent(n, -1);
    vector<bool> isAP(n, false);
    int timer = 0;

    function<void(int)> dfs = [&](int u) {
        disc[u] = low[u] = timer++;
        int children = 0;
        for (int v : adj[u]) {
            if (disc[v] == -1) {
                children++;
                parent[v] = u;
                dfs(v);
                low[u] = min(low[u], low[v]);
                // non-root: v can't bypass u → u is AP
                if (parent[u] != -1 && low[v] >= disc[u]) isAP[u] = true;
                // root: multiple DFS children → AP
                if (parent[u] == -1 && children > 1) isAP[u] = true;
            } else if (v != parent[u]) {
                low[u] = min(low[u], disc[v]);
            }
        }
    };

    for (int i = 0; i < n; i++) if (disc[i] == -1) dfs(i);
    vector<int> result;
    for (int i = 0; i < n; i++) if (isAP[i]) result.push_back(i);
    return result;
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"I'll use Tarjan's bridge-finding algorithm. During DFS, I track two values per node: `disc` (discovery time) and `low` (the minimum discovery time reachable from the subtree). For each edge u→v: if v is unvisited, recurse and update `low[u] = min(low[u], low[v])`. If low[v] > disc[u], then edge (u,v) is a bridge — no back edge from v's subtree reaches u or above, so removing (u,v) disconnects the graph."

### Interview Flow Checklist
- [ ] Build adjacency list
- [ ] DFS with disc[] and low[] arrays, timer
- [ ] For unvisited neighbor: recurse, update low[u] from low[v], check bridge/AP condition
- [ ] For visited ancestor: update low[u] from disc[v]
- [ ] Skip parent edge (use parent node or edge index)
- [ ] Handle root special case for APs

---

## 6. Problems

---

### Problem 1: 1192. Critical Connections in a Network
**Difficulty:** Hard
**Leetcode:** https://leetcode.com/problems/critical-connections-in-a-network/
**Optimal C++ Solution:**
```cpp
vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
    vector<vector<int>> adj(n);
    for (auto& c : connections) {
        adj[c[0]].push_back(c[1]);
        adj[c[1]].push_back(c[0]);
    }
    vector<int> disc(n, -1), low(n);
    int timer = 0;
    vector<vector<int>> bridges;

    function<void(int,int)> dfs = [&](int u, int par) {
        disc[u] = low[u] = timer++;
        for (int v : adj[u]) {
            if (v == par) continue;
            if (disc[v] == -1) {
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] > disc[u]) bridges.push_back({u, v});
            } else {
                low[u] = min(low[u], disc[v]);
            }
        }
    };

    dfs(0, -1);
    return bridges;
}
```
**Edge Cases:** [ ] Graph already disconnected, [ ] Parallel edges (use edge index to skip correctly)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 1568. Minimum Number of Days to Disconnect Island
**Difficulty:** Hard
**Leetcode:** https://leetcode.com/problems/minimum-number-of-days-to-disconnect-island/
**Why this pattern fits:** Check if already disconnected (0 days), if one cell removal disconnects (articulation point = 1 day), else 2 days

**Optimal C++ Solution:**
```cpp
int minDays(vector<vector<int>>& grid) {
    int rows = grid.size(), cols = grid[0].size();

    auto countIslands = [&]() {
        vector<vector<bool>> vis(rows, vector<bool>(cols, false));
        int count = 0;
        function<void(int,int)> dfs = [&](int r, int c) {
            if (r<0||r>=rows||c<0||c>=cols||vis[r][c]||grid[r][c]==0) return;
            vis[r][c] = true;
            dfs(r+1,c); dfs(r-1,c); dfs(r,c+1); dfs(r,c-1);
        };
        for (int r = 0; r < rows; r++)
            for (int c = 0; c < cols; c++)
                if (!vis[r][c] && grid[r][c]==1) { dfs(r,c); count++; }
        return count;
    };

    if (countIslands() != 1) return 0;

    // Try removing each land cell
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 0) continue;
            grid[r][c] = 0;
            if (countIslands() != 1) return 1;
            grid[r][c] = 1;
        }
    }
    return 2;  // always achievable in 2 days for any island with > 1 cell
}
```
**Complexity Analysis:**
- Time: O(m² × n²) — trying each cell × DFS
- Space: O(m × n)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> In a computer network, find all servers that, if taken offline, would split the network into two or more parts.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Articulation Points
**Reason:** Model servers as nodes, connections as edges. Run Tarjan's articulation point algorithm. Each articulation point = a server whose removal disconnects the network. O(V+E) solution.
</details>

---

**Drill 2:**
> Find the minimum number of edges to add to a graph to eliminate all bridges.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Bridge finding + condensation
**Reason:** Find all bridges, condense SCCs (each SCC has no bridges internally). The condensed graph is a tree. A tree with L leaves needs ceil(L/2) edges to make it bridgeless (connect pairs of leaves). Answer = ceil(leaves_in_condensed_tree / 2).
</details>

---

**Drill 3:**
> A road network has some one-way roads. Find all two-way roads (bidirectional edges) that are bridges.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Bridge finding on undirected subgraph
**Reason:** Extract only bidirectional roads as undirected edges. Run bridge-finding algorithm on this subgraph. Bridges in this undirected graph are the critical bidirectional roads. One-way roads can't be bridges in the undirected sense.
</details>

---

**Drill 4:**
> In a city's subway system, find the minimum number of stations to close to isolate a specific zone (remove all paths from the zone to the rest).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Min vertex cut / Network flow (not just bridges)
**Reason:** This is a minimum vertex cut problem: find the minimum number of nodes to remove to disconnect source from sink. Max-flow/min-cut via node splitting (each node → edge of capacity 1). Bridge/articulation point gives the single-node/edge answer, but minimum cut may require removing multiple nodes.
</details>

---

**Drill 5:**
> A ship's hull is a grid. Some cells are already holes. Find the minimum additional holes to punch to sink the ship (disconnect top from bottom).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** BFS connectivity check + answer is 0, 1, or 2
**Reason:** If already disconnected → 0. If one cell removal disconnects (check each cell) → 1. Otherwise, 2 cells always suffice (punch one corner cell to isolate it, or cut a bridge). Similar to LC 1568 approach: check 0, try 1, return 2.
</details>

---

## 8. Complexity Cheatsheet

| Variant | Time | Space | Notes |
|---------|------|-------|-------|
| Bridge finding | O(V+E) | O(V) | Single DFS, Tarjan's |
| Articulation points | O(V+E) | O(V) | Single DFS, root special case |
| Min days disconnect island | O(m²×n²) | O(m×n) | Brute force tries each cell |

---

## 9. Common Follow-up Questions

1. What if the graph has parallel (multiple) edges? (Use edge index to skip, not parent node — otherwise you'd skip BOTH parallel edges)
2. What's the relation between bridges and SCCs? (An edge is a bridge if and only if it's not part of any cycle, i.e., it's its own "SCC" in a directed sense — not in any cycle)
3. How to find biconnected components? (Similar to bridge finding: every maximal set of edges where no bridge exists = one biconnected component. Track edges in a stack during DFS)
4. Can you find bridges without DFS? (Not efficiently — bridge finding inherently relies on DFS tree structure and back edges)

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| SCC (Tarjan) | Both use disc/low arrays; bridges = edges between SCCs | 1192. Critical Connections |
| DFS | Core traversal for both bridge and AP finding | Both problems |
| Graph Condensation | After finding bridges, condense bridgeless components | Min edges to eliminate bridges |
| Network Flow | Min vertex cut (generalization of APs) | Complex network reliability |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
