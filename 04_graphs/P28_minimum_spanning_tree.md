# Pattern 28: Minimum Spanning Tree (MST)

## Category
Graphs

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 1135. Connecting Cities With Minimum Cost | Medium | https://leetcode.com/problems/connecting-cities-with-minimum-cost/ |
| 2 | 1168. Optimize Water Distribution in a Village | Hard | https://leetcode.com/problems/optimize-water-distribution-in-a-village/ |
| 3 | 1489. Find Critical and Pseudo-Critical Edges in MST | Hard | https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/ |
| 4 | 1584. Min Cost to Connect All Points | Medium | https://leetcode.com/problems/min-cost-to-connect-all-points/ |

---

## 1. First-Timer Explanation

### What is this pattern?
A **Minimum Spanning Tree** connects all nodes in a weighted undirected graph with minimum total edge weight, using exactly n-1 edges (no cycles).

**Two classic algorithms:**

**Kruskal's (sort edges + Union-Find):**
1. Sort all edges by weight
2. Greedily add each edge if it doesn't create a cycle (use Union-Find to check)
3. Stop when n-1 edges added

**Prim's (greedy node expansion):**
1. Start with any node; maintain a min-heap of edges crossing the cut
2. Always pick the cheapest edge to an unvisited node
3. Add that node to the MST; add all its edges to the heap

**Kruskal's** is simpler to code for sparse graphs. **Prim's** is better for dense graphs (similar to Dijkstra).

### Visual Walkthrough
```
Graph: nodes 1-4
Edges: (1,2,w=4), (1,3,w=2), (2,3,w=1), (2,4,w=5), (3,4,w=3)

Kruskal's:
  Sort edges: (2,3,1), (1,3,2), (3,4,3), (1,2,4), (2,4,5)

  Add (2,3,w=1): 2 and 3 different components → add. MST weight=1
  Add (1,3,w=2): 1 and {2,3} different → add. MST weight=3
  Add (3,4,w=3): 4 and {1,2,3} different → add. MST weight=6
  (1,2,w=4): 1 and 2 already connected → SKIP (would create cycle)
  (2,4,w=5): 2 and 4 already connected → SKIP

MST edges: {(2,3), (1,3), (3,4)}, total weight = 6
```

### When TO use this pattern
- Connect all nodes with minimum total cost
- "Minimum cost to connect all cities/points"
- Network design problems (cables, pipes, roads)
- Cluster analysis (cut MST to form clusters)
- Approximate TSP (MST + DFS ≈ 2× optimal tour)

### When NOT to use this pattern
- Need shortest path between two specific nodes → Dijkstra
- Directed graph → no MST concept (use minimum spanning arborescence)
- Network flow → different problem entirely

### Common Beginner Mistakes
- **Kruskal's edge list vs adjacency list**: Kruskal needs all edges as a list to sort
- **n-1 edges in MST**: stop as soon as you've added n-1 edges
- **Prim's visited array**: mark nodes visited when added to MST, not when pushed to heap
- **Disconnected graph**: MST doesn't exist; check if all nodes are connected

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | "connect all nodes/cities minimum cost", "minimum cable length", "minimum spanning" |
| Core Idea | Kruskal: sort edges + UF. Prim: Dijkstra-like greedy node expansion |
| Trigger Keywords | "minimum cost to connect", "wire all offices", "pipeline minimum cost" |
| Avoid When | Directed graph, shortest path (Dijkstra), disconnected graph |
| Time Complexity | Kruskal: O(E log E). Prim: O((V+E) log V) |
| Space Complexity | O(V + E) |

**Gotchas:**
- Kruskal: sort edges, not adjacency list
- Stop after n-1 edges (not n)
- UF for cycle detection in Kruskal
- Prim: use a min-heap of (weight, node) — same structure as Dijkstra

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"minimum cost to connect all"` + nodes → MST
- `"minimum spanning tree"` → direct signal
- `"connect all cities/points/offices"` + minimum → Kruskal or Prim
- `"critical edges in MST"` → MST with edge inclusion/exclusion analysis

---

## 4. C++ Template

```cpp
/*
 * Pattern: Minimum Spanning Tree
 * Kruskal: O(E log E) | Prim: O((V+E) log V)
 */

// KRUSKAL'S (sort edges + UF)
struct DSU {
    vector<int> p, r;
    DSU(int n) : p(n), r(n, 0) { iota(p.begin(), p.end(), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool unite(int x, int y) {
        int px=find(x), py=find(y); if(px==py) return false;
        if(r[px]<r[py]) swap(px,py); p[py]=px; if(r[px]==r[py]) r[px]++;
        return true;
    }
};

int kruskalMST(int n, vector<tuple<int,int,int>>& edges) {
    // edges: (weight, u, v)
    sort(edges.begin(), edges.end());
    DSU dsu(n + 1);
    int cost = 0, count = 0;
    for (auto& [w, u, v] : edges) {
        if (dsu.unite(u, v)) {
            cost += w;
            if (++count == n - 1) break;
        }
    }
    return count == n - 1 ? cost : -1;  // -1 if disconnected
}

// PRIM'S (min-heap, Dijkstra-style)
int primMST(int n, vector<vector<pair<int,int>>>& adj) {
    // adj[u] = list of {weight, v}
    vector<bool> inMST(n + 1, false);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    pq.push({0, 1});  // start from node 1
    int cost = 0, count = 0;
    while (!pq.empty() && count < n) {
        auto [w, u] = pq.top(); pq.pop();
        if (inMST[u]) continue;
        inMST[u] = true; cost += w; count++;
        for (auto& [ew, v] : adj[u])
            if (!inMST[v]) pq.push({ew, v});
    }
    return count == n ? cost : -1;
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"I'll use Kruskal's algorithm. I collect all edges, sort them by weight, and greedily add each edge to the MST if it doesn't create a cycle — checking this with Union-Find. The MST is complete when I've added n-1 edges. This gives the minimum total connection cost.

Alternatively, Prim's is like Dijkstra: start from any node, always expand via the cheapest edge to an unvisited node. Both are O(E log E) or O((V+E) log V) respectively."

### Interview Flow Checklist
- [ ] Collect all edges as list (for Kruskal) or build adj list (for Prim)
- [ ] Kruskal: sort edges, UF for cycle detection, stop at n-1 edges
- [ ] Prim: min-heap of (cost, node), skip visited, stop at n nodes
- [ ] Handle disconnected graph (count edges/nodes reached)
- [ ] Return total MST cost

---

## 6. Problems

---

### Problem 1: 1584. Min Cost to Connect All Points
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/min-cost-to-connect-all-points/
**Why this pattern fits:** Complete graph of n points; MST gives minimum total Manhattan distance

**Optimal C++ Solution (Prim's — avoids storing O(n²) edges):**
```cpp
int minCostConnectPoints(vector<vector<int>>& points) {
    int n = points.size();
    vector<int> minDist(n, INT_MAX);
    vector<bool> inMST(n, false);
    minDist[0] = 0;
    int cost = 0;
    for (int i = 0; i < n; i++) {
        // find unvisited node with min dist
        int u = -1;
        for (int j = 0; j < n; j++)
            if (!inMST[j] && (u == -1 || minDist[j] < minDist[u])) u = j;
        inMST[u] = true;
        cost += minDist[u];
        // update distances
        for (int v = 0; v < n; v++) {
            if (inMST[v]) continue;
            int d = abs(points[u][0]-points[v][0]) + abs(points[u][1]-points[v][1]);
            minDist[v] = min(minDist[v], d);
        }
    }
    return cost;
}
```
**Complexity Analysis:**
- Time: O(n²) — no heap needed; all edges are computed on-the-fly
- Space: O(n)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 1135. Connecting Cities With Minimum Cost
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/connecting-cities-with-minimum-cost/
**Why this pattern fits:** Classic MST on given edge list

**Optimal C++ Solution (Kruskal's):**
```cpp
int minimumCost(int n, vector<vector<int>>& connections) {
    sort(connections.begin(), connections.end(),
         [](auto& a, auto& b){ return a[2] < b[2]; });
    DSU dsu(n + 1);
    int cost = 0, edges = 0;
    for (auto& c : connections) {
        if (dsu.unite(c[0], c[1])) {
            cost += c[2];
            if (++edges == n - 1) return cost;
        }
    }
    return -1;  // can't connect all cities
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 3: 1168. Optimize Water Distribution in a Village
**Difficulty:** Hard
**Leetcode:** https://leetcode.com/problems/optimize-water-distribution-in-a-village/
**Why this pattern fits:** Add virtual node 0 connected to each house with well cost; then find MST

**Approach:**
- Either build a well in house i (cost = wells[i]) OR connect via pipes
- Add a virtual node 0; add edge (0, i, wells[i-1]) for each house
- Run Kruskal's on all edges (virtual + pipe edges)
- MST of this extended graph = optimal water distribution

**Optimal C++ Solution:**
```cpp
int minCostToSupplyWater(int n, vector<int>& wells, vector<vector<int>>& pipes) {
    vector<tuple<int,int,int>> edges;
    for (int i = 0; i < n; i++) edges.push_back({wells[i], 0, i+1});
    for (auto& p : pipes) edges.push_back({p[2], p[0], p[1]});
    sort(edges.begin(), edges.end());
    DSU dsu(n + 1);
    int cost = 0;
    for (auto& [w, u, v] : edges)
        if (dsu.unite(u, v)) cost += w;
    return cost;
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> You want to divide a connected graph into exactly K clusters such that the maximum distance between any two nodes in the same cluster is minimized.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** MST + cut K-1 heaviest edges
**Reason:** Build the MST. To form K clusters, cut the K-1 heaviest MST edges. The resulting clusters minimize the maximum inter-cluster edge weight within each cluster. This is the k-clustering algorithm.
</details>

---

**Drill 2:**
> Find the maximum bottleneck spanning tree: a spanning tree where the maximum edge weight is minimized.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** MST = Maximum Bottleneck Spanning Tree
**Reason:** The MST IS the minimum bottleneck spanning tree — it minimizes the maximum edge weight among all spanning trees. This follows from the cycle property: MST never includes an unnecessarily heavy edge.
</details>

---

**Drill 3:**
> Given a spanning tree of a graph, determine if it's a valid MST.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** MST cycle property verification
**Reason:** A spanning tree T is an MST if and only if for every non-tree edge e=(u,v,w), the maximum edge weight on the path from u to v in T is ≤ w. Check this for all non-tree edges using LCA + path maximum queries. O(E log V).
</details>

---

**Drill 4:**
> You have n servers and m possible connections. Some connections are "mandatory" (must be in the spanning tree). Add minimum-cost optional connections to connect all servers.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** MST with mandatory edges (Kruskal variant)
**Reason:** First, add all mandatory edges (union them). This may create some components. Then run standard Kruskal's on optional edges — adding edges that connect different components. The mandatory edges are treated as pre-existing infrastructure.
</details>

---

**Drill 5:**
> Find all edges that appear in SOME MST of the graph (there may be multiple MSTs if edges have equal weights).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** MST critical/pseudo-critical edge analysis (LC 1489)
**Reason:** Critical edge: removing it increases MST cost → must appear in all MSTs. Pseudo-critical: can be in some MST but not all. For each edge: try MST without it (cost increases → critical); try MST with it forced (cost equals original MST → pseudo-critical). O(E² log E).
</details>

---

## 8. Complexity Cheatsheet

| Algorithm | Time | Space | Best For |
|-----------|------|-------|---------|
| Kruskal's | O(E log E) | O(V+E) | Sparse graphs, edge list input |
| Prim's (heap) | O((V+E) log V) | O(V+E) | Dense graphs with adj list |
| Prim's (O(n²)) | O(V²) | O(V) | Complete graphs (n points) |
| Borůvka's | O(E log V) | O(V+E) | Parallel MST computation |

---

## 9. Common Follow-up Questions

1. What if the graph is directed? (No MST — use minimum spanning arborescence: Edmonds'/Chu-Liu algorithm)
2. What's the difference between MST and shortest path? (MST minimizes total edge weight to connect all nodes. Shortest path minimizes path weight between two specific nodes)
3. Can there be multiple MSTs? (Yes — when multiple edges have the same weight, different choices may yield equal-cost MSTs. The total weight is unique though — all MSTs have the same total weight)
4. How to find the second minimum spanning tree? (Find MST, then for each MST edge e, find the minimum cost non-MST edge that can replace e while keeping the tree connected)

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| Union-Find | Kruskal's cycle detection | 1584. Min Cost Connect Points |
| Dijkstra | Prim's = Dijkstra variant on MST | Same structure, different semantics |
| Sorting | Kruskal must sort all edges | All Kruskal problems |
| LCA + path max | Verify MST property for each non-tree edge | 1489. Critical/Pseudo-critical edges |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
