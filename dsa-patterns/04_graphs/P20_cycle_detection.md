# Pattern 20: Cycle Detection in Graphs

## Category
Graphs

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 207. Course Schedule | Medium | https://leetcode.com/problems/course-schedule/ |
| 2 | 210. Course Schedule II | Medium | https://leetcode.com/problems/course-schedule-ii/ |
| 3 | 261. Graph Valid Tree | Medium | https://leetcode.com/problems/graph-valid-tree/ |
| 4 | 684. Redundant Connection | Medium | https://leetcode.com/problems/redundant-connection/ |
| 5 | 785. Is Graph Bipartite? | Medium | https://leetcode.com/problems/is-graph-bipartite/ |

---

## 1. First-Timer Explanation

### What is this pattern?
A **cycle** in a directed graph means there's a circular dependency: A → B → C → A. In undirected graphs, a cycle means more than one path between two nodes.

**Two main approaches:**

**Directed graph (DFS 3-color):**
- White (0) = unvisited
- Gray (1) = currently in DFS stack (being processed)
- Black (2) = fully processed
- Finding a gray neighbor while DFS-ing = back edge = cycle

**Undirected graph (DFS + parent tracking):**
- Track parent of each node
- If you reach an already-visited node that isn't your parent → cycle
- Alternative: Union-Find (if you union an edge where both endpoints are already in the same component → cycle)

**Bipartite check (BFS/DFS 2-coloring):**
- Color nodes with 2 colors, alternating
- If same-colored node is adjacent → not bipartite (odd cycle exists)

### Visual Walkthrough
```
Directed Graph — Cycle Detection (3-color):
  A → B → C → A  (cycle)

  DFS from A: color A gray
    DFS to B: color B gray
      DFS to C: color C gray
        DFS to A: A is GRAY → cycle found!

No cycle:
  A → B → C (no back edge — C has no outgoing edges)
  DFS from A: A gray → B gray → C gray → C black → B black → A black

Undirected — Bipartite Check:
  Color node 0 = RED
  Neighbor 1 = BLUE
  Neighbor of 1 is 2 = RED
  If neighbor of 2 is 0 (already RED) and we're trying to color it BLUE → contradiction → not bipartite
```

### When TO use this pattern
- "Can all courses be completed?" (detect cycle in prerequisite graph)
- "Is this graph a valid tree?" (connected + no cycle)
- "Find the redundant edge" (first edge that creates a cycle)
- "Is the graph bipartite?" (2-colorable = no odd cycles)
- "Detect deadlock" in dependency systems

### When NOT to use this pattern
- Just need to traverse (use regular DFS/BFS)
- Finding shortest cycle (different algorithm — BFS from each node)

### Common Beginner Mistakes
- **Directed vs undirected**: different algorithms — don't mix them up
- **Undirected cycle**: you must track the parent to avoid reporting the edge you came from as a cycle
- **Bipartite**: coloring must be done for each unvisited component (graph may be disconnected)
- **Gray vs Black**: cycle only when you reach a GRAY node (still on stack), not a black one

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | "cycle", "circular dependency", "valid tree", "redundant edge", "bipartite" |
| Core Idea | DFS 3-color for directed (gray = on stack = cycle); parent-tracking DFS for undirected; Union-Find for redundant edge |
| Trigger Keywords | "course schedule", "prerequisites", "cycle", "valid tree", "bipartite", "2-colorable" |
| Avoid When | Simple traversal (DFS/BFS), shortest path (BFS/Dijkstra) |
| Time Complexity | O(V + E) |
| Space Complexity | O(V) |

**Gotchas:**
- Directed: gray node during DFS = cycle (back edge)
- Undirected: visited neighbor ≠ parent → cycle
- Valid tree: n nodes, n-1 edges, connected, no cycle
- Bipartite: BFS 2-color; if same-color neighbor found → not bipartite

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"course schedule"`, `"can finish"` → directed cycle detection (DFS 3-color or Kahn's BFS)
- `"graph valid tree"` → undirected: connected + acyclic (n-1 edges + DFS/Union-Find)
- `"redundant connection"` → undirected: first edge connecting already-connected nodes (Union-Find)
- `"bipartite"` → 2-coloring DFS/BFS; cycle in odd length = not bipartite

---

## 4. C++ Template

```cpp
/*
 * Pattern: Cycle Detection
 * Time: O(V+E) | Space: O(V)
 */

// DIRECTED GRAPH — DFS 3-color (0=white, 1=gray, 2=black)
bool hasCycleDirected(int node, vector<vector<int>>& adj, vector<int>& color) {
    color[node] = 1;  // gray: on stack
    for (int nb : adj[node]) {
        if (color[nb] == 1) return true;   // back edge → cycle
        if (color[nb] == 0 && hasCycleDirected(nb, adj, color)) return true;
    }
    color[node] = 2;  // black: done
    return false;
}

bool canFinish(int n, vector<vector<int>>& prerequisites) {
    vector<vector<int>> adj(n);
    for (auto& p : prerequisites) adj[p[1]].push_back(p[0]);
    vector<int> color(n, 0);
    for (int i = 0; i < n; i++)
        if (color[i] == 0 && hasCycleDirected(i, adj, color)) return false;
    return true;
}

// UNDIRECTED GRAPH — DFS with parent tracking
bool hasCycleUndirected(int node, int parent, vector<vector<int>>& adj, vector<bool>& vis) {
    vis[node] = true;
    for (int nb : adj[node]) {
        if (!vis[nb]) {
            if (hasCycleUndirected(nb, node, adj, vis)) return true;
        } else if (nb != parent) return true;  // visited non-parent = cycle
    }
    return false;
}

// BIPARTITE CHECK — BFS 2-coloring
bool isBipartite(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> color(n, -1);
    for (int start = 0; start < n; start++) {
        if (color[start] != -1) continue;
        queue<int> q;
        q.push(start); color[start] = 0;
        while (!q.empty()) {
            int node = q.front(); q.pop();
            for (int nb : graph[node]) {
                if (color[nb] == -1) { color[nb] = 1 - color[node]; q.push(nb); }
                else if (color[nb] == color[node]) return false;
            }
        }
    }
    return true;
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"For directed cycle detection, I use DFS with 3 states: unvisited (white), in-progress (gray), and done (black). A gray node is currently on the recursion stack — if I encounter a gray neighbor, I've found a back edge, which means a cycle.

For undirected, I track the parent. If I visit a node that's already visited and it's not where I came from, that's a cycle.

For Course Schedule specifically, I build a directed adjacency list from prerequisites and check if any cycle exists — if yes, we can't complete all courses."

### Interview Flow Checklist
- [ ] Identify: directed or undirected graph?
- [ ] For directed: build adj list, 3-color DFS per unvisited node
- [ ] For undirected: track parent in DFS, or use Union-Find
- [ ] Handle disconnected graphs (loop over all nodes as start)
- [ ] Return appropriate result (bool, order, etc.)

---

## 6. Problems

---

### Problem 1: 207. Course Schedule
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/course-schedule/
**Optimal C++ Solution:**
```cpp
bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> adj(numCourses);
    for (auto& p : prerequisites) adj[p[1]].push_back(p[0]);
    vector<int> state(numCourses, 0);  // 0=unvisited, 1=visiting, 2=done
    function<bool(int)> dfs = [&](int u) -> bool {
        if (state[u] == 1) return false;  // cycle
        if (state[u] == 2) return true;   // already processed safely
        state[u] = 1;
        for (int v : adj[u]) if (!dfs(v)) return false;
        state[u] = 2;
        return true;
    };
    for (int i = 0; i < numCourses; i++)
        if (!dfs(i)) return false;
    return true;
}
```
**Edge Cases:** [ ] No prerequisites (return true), [ ] Self-loop, [ ] Disconnected components

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 210. Course Schedule II
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/course-schedule-ii/
**Why this pattern fits:** Topological sort = cycle detection + order collection

**Optimal C++ Solution:**
```cpp
vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> adj(numCourses);
    for (auto& p : prerequisites) adj[p[1]].push_back(p[0]);
    vector<int> state(numCourses, 0), order;
    function<bool(int)> dfs = [&](int u) -> bool {
        if (state[u] == 1) return false;
        if (state[u] == 2) return true;
        state[u] = 1;
        for (int v : adj[u]) if (!dfs(v)) return false;
        state[u] = 2;
        order.push_back(u);  // postorder = reverse topological
        return true;
    };
    for (int i = 0; i < numCourses; i++)
        if (!dfs(i)) return {};
    reverse(order.begin(), order.end());
    return order;
}
```
**Edge Cases:** [ ] Cycle exists (return empty), [ ] All independent (any order works)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 3: 261. Graph Valid Tree
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/graph-valid-tree/
**Why this pattern fits:** Valid tree = n-1 edges + connected + no cycle

**Optimal C++ Solution:**
```cpp
bool validTree(int n, vector<vector<int>>& edges) {
    if ((int)edges.size() != n - 1) return false;  // tree has exactly n-1 edges
    vector<vector<int>> adj(n);
    for (auto& e : edges) { adj[e[0]].push_back(e[1]); adj[e[1]].push_back(e[0]); }
    vector<bool> vis(n, false);
    function<void(int,int)> dfs = [&](int u, int parent) {
        vis[u] = true;
        for (int v : adj[u]) if (!vis[v]) dfs(v, u);
    };
    dfs(0, -1);
    return all_of(vis.begin(), vis.end(), [](bool v){ return v; });
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 4: 684. Redundant Connection
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/redundant-connection/
**Why this pattern fits:** First edge that connects already-connected nodes creates a cycle → Union-Find

**Optimal C++ Solution:**
```cpp
vector<int> findRedundantConnection(vector<vector<int>>& edges) {
    int n = edges.size();
    vector<int> parent(n+1), rank(n+1, 0);
    iota(parent.begin(), parent.end(), 0);

    function<int(int)> find = [&](int x) -> int {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    };

    for (auto& e : edges) {
        int pu = find(e[0]), pv = find(e[1]);
        if (pu == pv) return e;  // same component → this edge creates cycle
        if (rank[pu] < rank[pv]) swap(pu, pv);
        parent[pv] = pu;
        if (rank[pu] == rank[pv]) rank[pu]++;
    }
    return {};
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 5: 785. Is Graph Bipartite?
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/is-graph-bipartite/
**Why this pattern fits:** 2-coloring BFS/DFS; conflict = not bipartite = odd cycle

**Optimal C++ Solution:**
```cpp
bool isBipartite(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> color(n, -1);
    for (int start = 0; start < n; start++) {
        if (color[start] != -1) continue;
        queue<int> q;
        q.push(start); color[start] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : graph[u]) {
                if (color[v] == -1) { color[v] = 1 - color[u]; q.push(v); }
                else if (color[v] == color[u]) return false;
            }
        }
    }
    return true;
}
```
**Edge Cases:** [ ] Disconnected graph (check all components), [ ] Self-loop (not bipartite)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> You have N tasks and a list of dependencies. Some dependencies form a cycle. Find all tasks involved in any cycle.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** DFS 3-color — collect nodes that are in gray→gray cycle path
**Reason:** During DFS, when you detect a back edge to a gray node, the cycle includes all nodes currently gray on the stack from the cycle start to the current node. Use a stack to track the current DFS path and extract cycle nodes.
</details>

---

**Drill 2:**
> Given a directed graph, determine if it's a DAG (directed acyclic graph).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** DFS 3-color cycle detection
**Reason:** A graph is a DAG if and only if it has no directed cycle. Run DFS 3-color on all nodes. If any back edge is found (gray neighbor), it's not a DAG. Otherwise it is. This is exactly what Course Schedule checks.
</details>

---

**Drill 3:**
> A social network has "friends" relationships. Some users claim to belong to team A and others to team B. A rule says no two members of the same team can be direct friends. Verify if these claims are consistent.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Bipartite check
**Reason:** Model friendships as an undirected graph. Try to 2-color: same team → same color, friend → different color. If any inconsistency (two friends have same color), the claims are impossible. This is exactly the bipartite check.
</details>

---

**Drill 4:**
> Given a directed graph, find all nodes from which you CANNOT reach node 0.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Reverse graph DFS/BFS from node 0
**Reason:** Reverse all edge directions. Then BFS/DFS from node 0 in the reversed graph. All nodes NOT reachable in the reversed graph are nodes that cannot reach 0 in the original.
</details>

---

**Drill 5:**
> You have a map of dependencies between modules. Find a valid build order, or report that none exists.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Topological sort (DFS or Kahn's BFS)
**Reason:** Build dependencies form a DAG if valid order exists. Topological sort gives the build order. If a cycle is detected, no valid build order exists. This is Course Schedule II generalized to module names.
</details>

---

## 8. Complexity Cheatsheet

| Variant | Time | Space | Notes |
|---------|------|-------|-------|
| Directed cycle (DFS 3-color) | O(V+E) | O(V) | State array |
| Undirected cycle (DFS+parent) | O(V+E) | O(V) | Parent tracking |
| Bipartite (BFS 2-color) | O(V+E) | O(V) | Color array |
| Redundant connection (UF) | O(E·α(V)) | O(V) | Near O(E) |
| Valid tree | O(V+E) | O(V) | Check edges + connectivity |

---

## 9. Common Follow-up Questions

1. Can Kahn's algorithm also detect cycles? (Yes — if the final topological order doesn't include all nodes, a cycle exists. Nodes not in the order are part of cycles)
2. Cycle in undirected graph: DFS vs Union-Find — which is better? (Same asymptotic O(V+E); UF is simpler to implement for edge-list input)
3. Find the actual cycle (not just detect it)? (DFS + track path stack; when back edge found, extract from current position back to the repeated node)
4. Directed graph: is any node part of a cycle? (Find all SCCs; any SCC with more than one node or a self-loop contains a cycle)

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| Topological Sort | DAG order after verifying no cycle | 210. Course Schedule II |
| Union-Find | Undirected cycle = same-component edge | 684. Redundant Connection |
| SCC (Kosaraju/Tarjan) | Find all cycles' members | P26. Strongly Connected Components |
| DFS postorder | Collect topological order alongside cycle check | 210. DFS topological sort |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
