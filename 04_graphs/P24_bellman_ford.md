# Pattern 24: Bellman-Ford Algorithm

## Category
Graphs

## Problem List
| # | Problem | Difficulty | Leetcode Link |
|---|---------|------------|---------------|
| 1 | 743. Network Delay Time | Medium | https://leetcode.com/problems/network-delay-time/ |
| 2 | 787. Cheapest Flights Within K Stops | Medium | https://leetcode.com/problems/cheapest-flights-within-k-stops/ |
| 3 | 1334. Find the City With the Smallest Number of Neighbors | Medium | https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/ |

---

## 1. First-Timer Explanation

### What is this pattern?
**Bellman-Ford** finds shortest paths from a single source, even with **negative edge weights**. It can also detect **negative cycles** (cycles where total weight is negative — shortest path would be −∞ around the cycle).

**The algorithm:**
1. Initialize `dist[src] = 0`, all others = ∞
2. Repeat V-1 times: for every edge (u, v, w), relax: if `dist[u] + w < dist[v]`, update `dist[v]`
3. (Optional) Run one more iteration: if any edge can still be relaxed → negative cycle exists

**Why V-1 iterations?** A shortest path in a graph with V nodes has at most V-1 edges. Each iteration guarantees that paths using up to i edges are correctly computed after i iterations.

**Key advantage over Dijkstra:**
- Handles negative weights
- Detects negative cycles
- Simpler to implement (just iterate over all edges)

**K-stop variant (787):**
- Run only K+1 iterations of Bellman-Ford
- Use a copy of dist to prevent using edges from the SAME iteration (enforce "at most K stops")

### Visual Walkthrough
```
Graph: 1→2 (w=-1), 2→3 (w=4), 1→3 (w=5), 3→4 (w=-3)
Source = 1

Initial: dist = [∞, 0, ∞, ∞, ∞]

Iteration 1 (relax all edges):
  1→2: dist[2] = min(∞, 0+(-1)) = -1
  2→3: dist[3] = min(∞, -1+4) = 3
  1→3: dist[3] = min(3, 0+5) = 3 (no change)
  3→4: dist[4] = min(∞, 3+(-3)) = 0

Iteration 2 (no improvements, done early):
  All relaxations: no update

Final: dist = [∞, 0, -1, 3, 0]
```

### When TO use this pattern
- Graph has negative edge weights
- Need to detect negative cycles
- K-step shortest path (run K iterations only)
- Simpler implementation needed (no heap management)
- Currency arbitrage detection (negative cycle = profit cycle)

### When NOT to use this pattern
- All weights non-negative → Dijkstra is faster O((V+E) log V) vs O(VE)
- Very dense graphs → Floyd-Warshall for all-pairs
- Unweighted → BFS

### Common Beginner Mistakes
- **Copy dist before each iteration for K-stops**: without copying, you might use multiple edges in one "hop"
- **V-1 iterations**: not V, not V+1 — exactly V-1 for correctness
- **Negative cycle detection**: run a V-th iteration; if anything updates → cycle
- **Source unreachable**: dist stays ∞; don't mistake this for negative cycle

---

## 2. Revision Card
| Field | Detail |
|-------|--------|
| Recognition Signal | "negative weights", "K stops", "detect negative cycle", "currency arbitrage" |
| Core Idea | Relax ALL edges V-1 times; shortest path has at most V-1 edges |
| Trigger Keywords | "negative edge", "at most K hops", "cycle detection in weighted graph" |
| Avoid When | Non-negative weights and V large (use Dijkstra) |
| Time Complexity | O(V × E) |
| Space Complexity | O(V) |

**Gotchas:**
- K-stops: use COPY of dist per iteration to prevent chaining edges within one "step"
- Negative cycle: run iteration V, check if any dist updates
- Relax all edges (not just from current node) each pass

---

## 3. Interview Tell Signs

### Keywords in problem statement
- `"cheapest flights within K stops"` → Bellman-Ford K iterations
- `"negative weights"` + shortest path → Bellman-Ford
- `"detect negative cycle"` → extra iteration check
- `"currency arbitrage"` → find negative cycle in log-transformed weights

---

## 4. C++ Template

```cpp
/*
 * Pattern: Bellman-Ford
 * Time: O(V*E) | Space: O(V)
 */

// STANDARD BELLMAN-FORD
vector<int> bellmanFord(int n, int src, vector<tuple<int,int,int>>& edges) {
    vector<int> dist(n + 1, INT_MAX);
    dist[src] = 0;

    for (int i = 0; i < n - 1; i++) {
        bool updated = false;
        for (auto& [u, v, w] : edges) {
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                updated = true;
            }
        }
        if (!updated) break;  // early termination optimization
    }

    // negative cycle detection (optional)
    for (auto& [u, v, w] : edges) {
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            // negative cycle exists
            return {};
        }
    }

    return dist;
}

// K-STOPS VARIANT (copy dist per iteration)
int cheapestKStops(int n, vector<vector<int>>& flights, int src, int dst, int k) {
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;
    for (int i = 0; i <= k; i++) {
        vector<int> temp = dist;  // freeze: don't chain edges in same iteration
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

---

## 5. How to Present in Interview

### What to SAY (verbal script)
"Bellman-Ford works by repeatedly relaxing all edges. Since any shortest path in a graph of V nodes has at most V-1 edges, after V-1 iterations we're guaranteed to have the correct shortest distances.

For the K-stops problem specifically: I run K+1 iterations — each iteration finds cheapest paths using at most one more edge. The key is to use a copy of the distance array in each iteration; otherwise I could chain multiple edges within a single 'stop,' violating the constraint."

### Interview Flow Checklist
- [ ] Initialize dist array (INF everywhere, 0 at source)
- [ ] Run V-1 iterations (or K+1 for K-stops)
- [ ] For K-stops: copy dist before each iteration
- [ ] Each iteration: relax all edges
- [ ] Optional: V-th iteration to detect negative cycle
- [ ] Return dist[dst] or -1

---

## 6. Problems

---

### Problem 1: 787. Cheapest Flights Within K Stops
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/cheapest-flights-within-k-stops/
**Why this pattern fits:** K-limited relaxation iterations; copy array to enforce exactly K stops

**Optimal C++ Solution:**
```cpp
int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;
    for (int i = 0; i <= k; i++) {  // k+1 iterations = at most k+1 edges = k stops
        vector<int> temp = dist;
        for (auto& f : flights) {
            if (dist[f[0]] != INT_MAX && dist[f[0]] + f[2] < temp[f[1]])
                temp[f[1]] = dist[f[0]] + f[2];
        }
        dist = temp;
    }
    return dist[dst] == INT_MAX ? -1 : dist[dst];
}
```
**Edge Cases:** [ ] src == dst (0 cost), [ ] No path within K stops, [ ] K = 0 (direct flights only)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 2: 743. Network Delay Time (Bellman-Ford variant)
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/network-delay-time/
**Optimal C++ Solution:**
```cpp
int networkDelayTime(vector<vector<int>>& times, int n, int k) {
    vector<int> dist(n+1, INT_MAX);
    dist[k] = 0;
    for (int i = 0; i < n-1; i++) {
        bool updated = false;
        for (auto& t : times) {
            if (dist[t[0]] != INT_MAX && dist[t[0]] + t[2] < dist[t[1]]) {
                dist[t[1]] = dist[t[0]] + t[2];
                updated = true;
            }
        }
        if (!updated) break;
    }
    int ans = *max_element(dist.begin()+1, dist.end());
    return ans == INT_MAX ? -1 : ans;
}
```
**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

### Problem 3: 1334. Find the City With the Smallest Number of Neighbors at a Threshold Distance
**Difficulty:** Medium
**Leetcode:** https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/
**Why this pattern fits:** All-pairs shortest path → Floyd-Warshall (or Dijkstra/Bellman-Ford from each node)

**Optimal C++ Solution (Floyd-Warshall):**
```cpp
int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
    vector<vector<int>> dist(n, vector<int>(n, INT_MAX/2));
    for (int i = 0; i < n; i++) dist[i][i] = 0;
    for (auto& e : edges) {
        dist[e[0]][e[1]] = min(dist[e[0]][e[1]], e[2]);
        dist[e[1]][e[0]] = min(dist[e[1]][e[0]], e[2]);
    }
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    int ans = -1, minReachable = n;
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++)
            if (i != j && dist[i][j] <= distanceThreshold) count++;
        if (count <= minReachable) { minReachable = count; ans = i; }
    }
    return ans;
}
```
**Complexity Analysis:**
- Time: O(n³) for Floyd-Warshall
- Space: O(n²)

**My Solution:** *(fill this in after attempting)*
```cpp
// your solution here
```

---

## 7. Pattern Recognition Drill

**Drill 1:**
> You have a currency exchange network. Each edge has an exchange rate (multiplicative). Detect if there's an arbitrage opportunity (profit cycle).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Bellman-Ford negative cycle detection on log-transformed weights
**Reason:** Take -log of exchange rates (makes multiplicative problem additive; profit cycle → negative cycle). Run Bellman-Ford. If the V-th iteration still relaxes an edge → negative cycle → arbitrage exists. Note: maximize product = minimize negative log sum.
</details>

---

**Drill 2:**
> Find the shortest path in a graph where you can negate the weight of at most one edge (make it negative if positive, or positive if negative).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** DP with state (node, negate_used)
**Reason:** Run Dijkstra/Bellman-Ford on expanded graph: state = (node, 0/1). Two dist arrays: dist[node][0] (no negation used), dist[node][1] (negation used). Transition: normal edge updates both, negated edge transitions 0→1. LC 1368 variant.
</details>

---

**Drill 3:**
> Given a weighted directed graph, find if any negative cycle is reachable from the source.

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Bellman-Ford + reachability check
**Reason:** Run V-1 iterations of Bellman-Ford. In the V-th iteration, any edge (u,v,w) that can still be relaxed AND where dist[u] != INT_MAX indicates a negative cycle reachable from source. Mark all nodes reachable from such nodes as "in a negative cycle."
</details>

---

**Drill 4:**
> You have a flight network with prices. Find the cheapest way to visit all cities in any order (traveling salesman variant).

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Bitmask DP (not Bellman-Ford)
**Reason:** TSP is NP-hard; exact solution via bitmask DP: dp[mask][city] = cheapest cost to visit exactly the cities in mask ending at city. O(2^n * n^2). Bellman-Ford only finds single-source paths, not visit-all-cities routes.
</details>

---

**Drill 5:**
> After K time steps in a network, what is the maximum flow that has reached each node from a set of sources?

<details>
<summary>Click to reveal answer</summary>
**Pattern:** Multi-source BFS or DP propagation
**Reason:** At each time step, each source adds flow through edges. This is more like BFS-level propagation or a dynamic programming problem over time steps — not Bellman-Ford. Bellman-Ford computes minimum-cost paths, not maximum-flow propagation.
</details>

---

## 8. Complexity Cheatsheet

| Variant | Time | Space | Notes |
|---------|------|-------|-------|
| Standard Bellman-Ford | O(V×E) | O(V) | All edges relaxed V-1 times |
| K-stops variant | O(K×E) | O(V) | Only K+1 iterations |
| With early termination | O(V×E) best case O(E) | O(V) | Stop if no updates in iteration |
| Floyd-Warshall (all-pairs) | O(V³) | O(V²) | For dense small graphs |

---

## 9. Common Follow-up Questions

1. When to use Bellman-Ford vs Dijkstra? (Negative weights or K-hop constraint → Bellman-Ford. Non-negative and want speed → Dijkstra. All-pairs small graph → Floyd-Warshall)
2. Can Bellman-Ford handle negative cycles? (Yes — detects them, but can't compute shortest path THROUGH them since it'd be −∞)
3. What's SPFA (Shortest Path Faster Algorithm)? (Queue-based Bellman-Ford: only relax edges from nodes whose dist was recently updated. Same worst-case as BF but faster in practice)
4. Floyd-Warshall vs multiple Dijkstras for all-pairs? (Floyd-Warshall O(V³): simpler code. Multiple Dijkstras O(V(V+E)logV): better for sparse graphs)

---

## 10. Cross-Pattern Connections

| Combined With | When | Example Problem |
|---------------|------|-----------------|
| Dijkstra | Both solve SSSP; Dijkstra faster for non-negative | 743. Compare approaches |
| Floyd-Warshall | All-pairs version of Bellman-Ford | 1334. Smallest Neighbors |
| DP | K-stops = DP over edges | 787. Cheapest Flights |
| Negative Cycle Detection | Currency arbitrage, deadlock detection | Detect negative cycle variant |

---

## My Notes
*(add your personal notes, tricks, and observations here as you study)*
