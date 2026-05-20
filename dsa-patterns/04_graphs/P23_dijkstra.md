# Pattern 23: Dijkstra's Algorithm — Shortest Path in Weighted Graph

## Category
Graphs

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 743. Network Delay Time | Medium | https://leetcode.com/problems/network-delay-time/ |
| 2 | 787. Cheapest Flights Within K Stops | Medium | https://leetcode.com/problems/cheapest-flights-within-k-stops/ |
| 3 | 1514. Path with Maximum Probability | Medium | https://leetcode.com/problems/path-with-maximum-probability/ |
| 4 | 1631. Path With Minimum Effort | Medium | https://leetcode.com/problems/path-with-minimum-effort/ |
| 5 | 2642. Design Graph With Shortest Path Calculator | Hard | https://leetcode.com/problems/design-graph-with-shortest-path-calculator/ |

---

## 1. First-Timer Explanation

### What is this pattern?
**Dijkstra's algorithm** finds the shortest path from a source to all other nodes in a graph with **non-negative edge weights**. It's a greedy algorithm: always expand the closest unvisited node.

**The algorithm (min-heap variant):**
1. `dist[source] = 0`, all others = ∞
2. Push `(0, source)` into a min-heap (priority queue sorted by distance)
3. While heap non-empty:
   - Pop the minimum-distance node `(d, u)`
   - If `d > dist[u]` → skip (stale entry)
   - For each neighbor `v` with edge weight `w`: if `dist[u] + w < dist[v]` → update `dist[v]` and push `(dist[v], v)` to heap
4. `dist[target]` = shortest distance

**Why min-heap?** We always want to process the node with the smallest current known distance first — min-heap gives O(log V) extraction.

### Visual Walkthrough
```
Graph: 1→2 (w=4), 1→3 (w=1), 3→2 (w=2), 2→4 (w=3)
Source = 1

Initial: dist = [∞,0,∞,∞,∞], heap = [(0,1)]

Pop (0,1):
  Neighbor 2: dist[2] = 0+4 = 4 → push (4,2)
  Neighbor 3: dist[3] = 0+1 = 1 → push (1,3)

Pop (1,3):
  Neighbor 2: dist[2] = min(4, 1+2) = 3 → update, push (3,2)

Pop (3,2):  [stale (4,2) still in heap but will be skipped]
  Neighbor 4: dist[4] = 3+3 = 6 → push (6,4)

Pop (4,2): dist[2] is already 3 < 4 → SKIP (stale)

Pop (6,4): no neighbors

Final: dist = [∞, 0, 3, 1, 6]
Shortest to node 4 = 6 (path: 1→3→2→4)
```

### When TO use this pattern
- Shortest path with non-negative edge weights
- "Minimum cost/time to reach destination"
- Network delay (time for signal to reach all nodes)
- "K stops" constraint → modified Dijkstra or Bellman-Ford
- Maximum probability path (negate: use max-heap)

### When NOT to use this pattern
- Negative edge weights → Bellman-Ford
- Unweighted graph → BFS (simpler, O(V+E))
- All-pairs shortest path → Floyd-Warshall

### Common Beginner Mistakes
- **Skip stale entries**: when popping `(d, u)`, check if `d > dist[u]` — if so, skip
- **Non-negative weights only**: Dijkstra fails with negative edges
- **Min-heap vs max-heap**: for minimum distance use min-heap; for maximum probability use max-heap with negation
- **K stops**: Dijkstra can be adapted but Bellman-Ford with K iterations is cleaner for this constraint

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | "shortest path", "minimum cost", "network delay", weighted graph |
| Core Idea | Greedy: always expand closest node; min-heap for efficient next-node selection |
| Trigger Keywords | "minimum cost", "shortest weighted path", "delay time", "probability path" |
| Avoid When | Negative weights (use Bellman-Ford), unweighted (use BFS) |
| Time Complexity | O((V + E) log V) with binary heap |
| Space Complexity | O(V + E) |

**Gotchas:**
- Skip stale heap entries (`d > dist[u]` → continue)
- Initialize dist[] to INT_MAX / infinity
- For maximum instead of minimum: negate weights or use max-heap
- K-stop constraint: add stops as part of state (u, stops_remaining)

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"minimum time"` / `"minimum cost"` + weighted graph → Dijkstra
- `"network delay time"` → Dijkstra from source; answer = max of all dist[]
- `"cheapest flights within K stops"` → Bellman-Ford K iterations, or Dijkstra with state
- `"maximum probability"` → Dijkstra with max-heap (or negate log probabilities)
- `"minimum effort"` → Dijkstra where edge weight = max height difference along path

---

## 4. C++ Template

```cpp
/*
 * Pattern: Dijkstra's Shortest Path
 * Time: O((V+E) log V) | Space: O(V+E)
 */

using pii = pair<int,int>;  // (dist, node)

int dijkstra(int n, int src, int dst, vector<vector<pii>>& adj) {
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;
    priority_queue<pii, vector<pii>, greater<pii>> pq;  // min-heap
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;  // stale entry
        if (u == dst) return d;     // early exit if only need dst
        for (auto [w, v] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist[dst] == INT_MAX ? -1 : dist[dst];
}

// Build adjacency list from edge list
// edges[i] = {u, v, w}
vector<vector<pii>> buildAdj(int n, vector<vector<int>>& edges) {
    vector<vector<pii>> adj(n + 1);
    for (auto& e : edges)
        adj[e[0]].push_back({e[2], e[1]});  // {weight, neighbor}
    return adj;
}
```

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"This is a shortest path problem with weighted edges, so I'll use Dijkstra's algorithm. I'll maintain a distance array initialized to infinity (0 for source) and a min-heap to always process the cheapest-to-reach node next. For each extracted node, I relax all its outgoing edges. I skip stale heap entries — when I pop a node with a distance larger than the current best known, that entry is outdated and I continue. The answer is dist[destination]."

### Interview Flow Checklist
- [ ] Build adjacency list (node → list of (weight, neighbor))
- [ ] Initialize dist[] = INF, dist[src] = 0
- [ ] Push (0, src) to min-heap
- [ ] While heap: pop (d, u); skip if d > dist[u]; relax edges
- [ ] Return dist[dst] or -1 if unreachable

---

## 6. Problems

---

### Problem 1: 743. Network Delay Time
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/network-delay-time/
**Why this pattern fits:** Shortest path from source to all nodes; answer = max distance

**Optimal C++ Solution:**
```cpp
int networkDelayTime(vector<vector<int>>& times, int n, int k) {
    vector<vector<pair<int,int>>> adj(n+1);
    for (auto& t : times) adj[t[0]].push_back({t[2], t[1]});

    vector<int> dist(n+1, INT_MAX);
    dist[k] = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    pq.push({0, k});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto [w, v] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    int ans = *max_element(dist.begin()+1, dist.end());
    return ans == INT_MAX ? -1 : ans;
}
```
**Edge Cases:** [ ] Unreachable node (return -1), [ ] Single node

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 1631. Path With Minimum Effort
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/path-with-minimum-effort/
**Why this pattern fits:** Dijkstra where "cost" = max absolute height difference on path (not sum)

**Optimal C++ Solution:**
```cpp
int minimumEffortPath(vector<vector<int>>& heights) {
    int rows = heights.size(), cols = heights[0].size();
    vector<vector<int>> effort(rows, vector<int>(cols, INT_MAX));
    effort[0][0] = 0;
    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> pq;
    pq.push({0, 0, 0});  // (effort, row, col)
    int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    while (!pq.empty()) {
        auto [e, r, c] = pq.top(); pq.pop();
        if (r == rows-1 && c == cols-1) return e;
        if (e > effort[r][c]) continue;
        for (auto& d : dirs) {
            int nr = r+d[0], nc = c+d[1];
            if (nr<0||nr>=rows||nc<0||nc>=cols) continue;
            int newEff = max(e, abs(heights[nr][nc] - heights[r][c]));
            if (newEff < effort[nr][nc]) {
                effort[nr][nc] = newEff;
                pq.push({newEff, nr, nc});
            }
        }
    }
    return 0;
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 3: 1514. Path with Maximum Probability
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/path-with-maximum-probability/
**Why this pattern fits:** Maximum probability = Dijkstra with max-heap (maximize instead of minimize)

**Optimal C++ Solution:**
```cpp
double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb,
                      int start, int end) {
    vector<vector<pair<int,double>>> adj(n);
    for (int i = 0; i < (int)edges.size(); i++) {
        adj[edges[i][0]].push_back({edges[i][1], succProb[i]});
        adj[edges[i][1]].push_back({edges[i][0], succProb[i]});
    }
    vector<double> prob(n, 0.0);
    prob[start] = 1.0;
    priority_queue<pair<double,int>> pq;  // max-heap
    pq.push({1.0, start});
    while (!pq.empty()) {
        auto [p, u] = pq.top(); pq.pop();
        if (p < prob[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (prob[u] * w > prob[v]) {
                prob[v] = prob[u] * w;
                pq.push({prob[v], v});
            }
        }
    }
    return prob[end];
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 4: 787. Cheapest Flights Within K Stops
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/cheapest-flights-within-k-stops/
**Why this pattern fits:** Dijkstra with state (node, stops_used); or Bellman-Ford K iterations

**Optimal C++ Solution (Bellman-Ford, K iterations):**
```cpp
int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;
    for (int i = 0; i <= k; i++) {
        vector<int> temp = dist;  // copy: only update via edges from PREVIOUS state
        for (auto& f : flights) {
            int u = f[0], v = f[1], w = f[2];
            if (dist[u] != INT_MAX && dist[u] + w < temp[v])
                temp[v] = dist[u] + w;
        }
        dist = temp;
    }
    return dist[dst] == INT_MAX ? -1 : dist[dst];
}
```
**Complexity Analysis:**
- Time: O(K × E)
- Space: O(n)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> You have a map with roads where each road has a travel time AND a toll. Minimize total toll, but among paths with the same toll, prefer the fastest one.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Dijkstra with composite cost
**Reason:** State = (toll, time, node). Push (toll, time, node) to min-heap sorted by (toll, then time). When relaxing edges: new_toll = toll + edge_toll, new_time = time + edge_time. Compare lexicographically (toll first, then time).
</details>

---

**Drill 2:**
> Find the path between two cities that maximizes the minimum road capacity (bottleneck path).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Modified Dijkstra (maximize minimum) or Binary Search + BFS
**Reason:** Dijkstra variant: dist[v] = max bottleneck reaching v. Use max-heap. When relaxing: new_bottleneck = min(current_bottleneck, edge_capacity). Update if new_bottleneck > dist[v]. Alternatively, binary search on answer + BFS/DFS to check feasibility. LC 1631 variant.
</details>

---

**Drill 3:**
> You can use at most one "speed boost" to halve the travel time of one road segment. Find the fastest path.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Dijkstra with state (node, boost_used)
**Reason:** State = (node, 0/1 boost_used). Two copies of the distance array: dist[node][0] (no boost) and dist[node][1] (boost used). When traversing edge, try both: normal cost and halved cost (if boost not yet used). Standard Dijkstra on this expanded state graph.
</details>

---

**Drill 4:**
> A package delivery system has time windows: some roads are only passable between time A and time B. Find the fastest delivery route.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Dijkstra with time-dependent edges
**Reason:** State = (current_time, node). When relaxing edge u→v: check if current_time falls within the road's time window; if not, you must wait until window opens. Push (max(current_time, window_start) + travel_time, v) to heap. Dijkstra handles this naturally.
</details>

---

**Drill 5:**
> In a weighted graph, find the shortest path that passes through a specific intermediate node M (must visit M on the way from src to dst).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Two Dijkstra runs
**Reason:** Run Dijkstra from src to get dist_from_src[]. Run Dijkstra from dst on reversed graph (or undirected) to get dist_from_dst[]. Answer = dist_from_src[M] + dist_from_dst[M]. For multiple intermediate nodes, run Dijkstra from each and take minimum total.
</details>

---

## 8. Complexity Cheatsheet

| Variant | Time | Space | Notes |
|---------|------|-------|-------|
| Standard Dijkstra | O((V+E) log V) | O(V+E) | Binary heap |
| Dijkstra with state | O(S × (V+E) log(S×V)) | O(S×V) | S = state space size |
| Bellman-Ford (K stops) | O(K × E) | O(V) | Good for K-constraint |
| Dijkstra on grid | O(m×n × log(m×n)) | O(m×n) | Grid as graph |

---

## 9. Common Follow-up Questions

1. Why does Dijkstra fail with negative edges? (A later-discovered shorter path could improve already-settled nodes — the greedy "settled = optimal" assumption breaks)
2. Can you reconstruct the actual path? (Yes — maintain a `parent[]` array; when dist[v] is updated, set parent[v] = u; then trace back from dst to src)
3. What's the difference between Dijkstra and BFS? (BFS = unweighted / unit weights; Dijkstra = non-negative weights. BFS is O(V+E), Dijkstra is O((V+E) log V))
4. What if the graph is dense? (Use adjacency matrix + simple O(V²) Dijkstra instead of heap — faster for E = O(V²))

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| BFS | Unweighted = Dijkstra with unit weights | 1091. Shortest Path Binary Matrix |
| Bellman-Ford | K-stop constraint / negative edges | 787. Cheapest Flights K Stops |
| State Machine | Extra constraints (stops, boosts, fuel) | 787, 1293 |
| Binary Search | Alternative: binary search on answer + BFS | 1631 alternative |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
