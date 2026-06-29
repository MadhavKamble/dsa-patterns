# Bellman-Ford Algorithm

> **GFG Problem** · **Difficulty:** Medium · **Step 15 — Graphs · P34**

---

## Problem Understanding

**What is it asking?**
Given a directed weighted graph with `V` vertices and `edges[][]` (each `[u, v, weight]`), find the **shortest distance from `src` to all nodes**. Unlike Dijkstra, handles **negative weights**. Return `{-1}` if a **negative cycle** is reachable from `src`.

**Input:** `V`, `edges[][]`, `src`
**Output:** `dist[]` — shortest distance from `src` to every node, or `{-1}` if negative cycle

**Example:**
```
V=5, src=0
edges: 0→1(5), 0→2(4), 1→3(-3), 2→1(−2), 3→4(4)

After relaxation:
dist[0]=0, dist[1]=2(via 0→2→1), dist[2]=4, dist[3]=-1, dist[4]=3

No negative cycle → return [0,2,4,-1,3]
```

**Key Observations:**
- Relax ALL edges exactly `V-1` times (not just neighbors)
- After V-1 relaxations, all shortest paths (without negative cycles) are finalized
- One more (Nth) relaxation: if any edge still relaxes → negative cycle exists
- `dist[u] != 1e8` guard: don't propagate from unreachable nodes
- Works on directed graphs; edges given directly (no adjacency list needed)

---

## Why V-1 Relaxations?

```
A shortest path in a graph with V nodes has at most V-1 edges
(visiting each node at most once on a simple path).

After 1 relaxation: shortest paths using ≤ 1 edge are correct
After 2 relaxations: shortest paths using ≤ 2 edges are correct
...
After V-1 relaxations: all shortest paths are correct

If on the Nth pass we can STILL relax an edge:
  → there's a cycle that keeps reducing cost → negative cycle
```

---

## Optimal Approach — Edge Relaxation V-1 Times

### Algorithm
1. `dist[V]=1e8`, `dist[src]=0`
2. Repeat `V-1` times: for every edge `(u,v,wt)`:
   - If `dist[u] != 1e8` and `dist[u]+wt < dist[v]` → `dist[v] = dist[u]+wt`
3. One more pass (Nth): if any edge still relaxes → return `{-1}` (negative cycle)
4. Return `dist[]`

### Dry Run

**V=4, src=0, edges: 0→1(4), 0→2(5), 1→2(-3), 2→3(2)**

```
Init: dist=[0,1e8,1e8,1e8]

Pass 1 (i=0):
  0→1(4):  dist[0]=0 ≠ 1e8, 0+4=4 < 1e8  → dist[1]=4
  0→2(5):  0+5=5 < 1e8                    → dist[2]=5
  1→2(-3): dist[1]=4, 4-3=1 < 5           → dist[2]=1
  2→3(2):  dist[2]=1, 1+2=3 < 1e8         → dist[3]=3

dist=[0,4,1,3]

Pass 2 (i=1):
  0→1(4):  0+4=4, not < dist[1]=4 → skip
  0→2(5):  0+5=5, not < dist[2]=1 → skip
  1→2(-3): 4-3=1, not < dist[2]=1 → skip
  2→3(2):  1+2=3, not < dist[3]=3 → skip

(no changes — already converged)

Pass 3 (V-1=3): same, no changes

Nth relaxation check:
  No edge relaxes → no negative cycle

return [0,4,1,3] ✅
```

**Negative Cycle Detection:**
```
If edges contained: 1→2(-3), 2→1(-3)
  dist[1] and dist[2] would keep decreasing forever
  Nth pass: 1→2 still relaxes → return {-1}
```

### Complexity
- **Time:** O(V × E) — V-1 passes over all E edges
- **Space:** O(V) — dist array only (no adjacency list)

---

## Clean C++ Interview Code

```cpp
class Solution {
  public:
    vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) {
        vector<int> dist(V,1e8);
        dist[src]=0;
        for(int i=0;i<V-1;i++){
            for(auto it: edges){
                int u=it[0];
                int v=it[1];
                int wt=it[2];
                if(dist[u]!=1e8 && dist[u]+wt<dist[v]){
                    dist[v]=dist[u]+wt;
                }
            }
        }
        for(auto it: edges){
            int u=it[0];
            int v=it[1];
            int wt=it[2];
            if(dist[u]!=1e8 && dist[u]+wt<dist[v]){
                return {-1};
            }
        }
        return dist;
    }
};
```

---

## Why `1e8` and Not `1e9`?

```
If dist[u] = 1e9 (INT_MAX territory) and wt is negative:
  dist[u] + wt could still be a large positive — or overflow int.

1e8 as infinity:
  Safely fits in int (max ~2×10^9)
  dist[u]+wt won't overflow int even for large negative weights
  Guard: dist[u] != 1e8 prevents relaxing from unreachable nodes

Using INT_MAX would overflow: INT_MAX + (-1) = INT_MIN → wrong relaxation
```

---

## Dijkstra vs Bellman-Ford

| | Dijkstra | Bellman-Ford |
|--|----------|--------------|
| Negative weights | ❌ (wrong results) | ✅ |
| Negative cycle detection | ❌ | ✅ (Nth relaxation) |
| Time complexity | O((V+E) log V) | O(V×E) |
| Algorithm type | Greedy (min-heap) | Dynamic programming |
| Data structure | Priority queue | Just the edge list |
| Graph type | Directed/undirected | Directed (undirected: list each edge twice) |

---

## Interview Explanation Script

> "Bellman-Ford relaxes all edges V-1 times. After k relaxations, all shortest paths using ≤ k edges are correctly computed. Since a simple path has at most V-1 edges, V-1 passes guarantee all shortest paths."

> "To detect negative cycles: run one more (Nth) relaxation. If any edge still improves a distance, there's a cycle that keeps reducing cost — a negative cycle. Return -1."

> "I use 1e8 as infinity instead of INT_MAX to avoid overflow when adding negative weights. The guard `dist[u] != 1e8` prevents relaxing from unreachable nodes."

---

## Recall Line *(10-Second Revision)*

> "Bellman-Ford: V-1 passes over all edges, relax if dist[u]+wt<dist[v]. Nth pass: if relaxes → neg cycle → {-1}. O(VE)."

---

## Short Revision Notes

- No adjacency list needed — iterate over raw edge list directly
- Loop runs `V-1` times (not V) — paths have at most V-1 edges
- `dist[u] != 1e8` guard — don't propagate infinity
- Nth relaxation is a single pass (not V-1 again) — just checking
- `1e8` not `1e9` or `INT_MAX` — avoids overflow with negative weights
- Directed graph — don't add reverse edges (unlike Dijkstra on undirected)
- Order of edge processing doesn't matter for correctness (unlike Dijkstra)

---

## When to Use Bellman-Ford

```
Use Dijkstra when:  non-negative weights, need O((V+E)logV)
Use Bellman-Ford when:
  1. Negative edge weights exist
  2. Need to detect negative cycles
  3. Simpler implementation acceptable (no priority queue)
  4. Distributed systems (each node can run independently)
```

---

## Pattern Recognition Trigger

**When I see:**
- "Graph with negative weights — find shortest path"
- "Detect negative cycle"
- "Relax edges repeatedly"

**I should think of:** Bellman-Ford — V-1 relaxation passes + Nth pass for cycle detection

---

## Common Mistakes

❌ Using `INT_MAX` as infinity — `INT_MAX + negative_weight` overflows
❌ Running exactly V passes instead of V-1 (off-by-one, though functional)
❌ Not guarding `dist[u] != 1e8` — propagates infinity as if it's a valid distance
❌ Adding reverse edges for directed graph — Bellman-Ford is for directed (add reverse only if undirected)
❌ Checking Nth relaxation with `>= 0` instead of `< dist[v]` — wrong condition

---

## What Interviewer Is Testing

- **Why V-1 passes** — longest simple path has V-1 edges
- **Negative cycle detection** — Nth pass trick
- **`1e8` vs `INT_MAX`** — overflow awareness with negative weights
- **Dijkstra vs Bellman-Ford** tradeoff: speed vs negative-weight support

---

## Related Problems

- [ ] Striver Step 15 P26 — Dijkstra (non-negative weights only)
- [ ] Striver Step 15 P35 — Floyd-Warshall (all-pairs shortest path)
- [ ] LeetCode #787 — Cheapest Flights K Stops (K-limited Bellman-Ford variant)

---

## Pattern Category

`Graphs` · `Shortest Path` · `Dynamic Programming` · `Negative Weights` · `Cycle Detection`

---

## 30-Second Last-Minute Revision

> **Bellman-Ford:** `dist[V]=1e8`, `dist[src]=0`.
> V-1 passes over ALL edges: `dist[u]!=1e8 && dist[u]+wt<dist[v]` → relax.
> Nth pass: any relaxation → return `{-1}` (negative cycle).
> **Time:** O(V×E) | **Use when:** negative weights or need cycle detection.
> `1e8` not `INT_MAX` — avoid overflow with negative weights.
