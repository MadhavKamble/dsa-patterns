# Minimum Spanning Tree — Theory

> **Concept Note** · **Step 15 — Graphs · P37**

---

## What is a Spanning Tree?

A **spanning tree** of a connected undirected graph is a subgraph that:
- Includes **all V vertices**
- Contains exactly **V-1 edges**
- Has **no cycles**
- Is **connected**

```
Graph:               One Spanning Tree:
0 -1- 1              0 -1- 1
|     |              |
4     2              4     2
 \   /                \   /
  \ /                  \ /
   3 -3- 4              3
```

A graph with V vertices can have many spanning trees. The number of possible spanning trees of a complete graph K_n = n^(n-2) (Cayley's formula).

---

## What is a Minimum Spanning Tree (MST)?

A **Minimum Spanning Tree** is a spanning tree with the **minimum total edge weight** among all spanning trees of a graph.

```
Graph:                    MST (total weight = 10):
0 --4-- 1                 0 --4-- 1
|  \    |                 |
2   3   5        →        2       5
|    \  |                 |
3 --1-- 2                 3 --1-- 2
```

**Properties:**
- A graph can have **multiple MSTs** if there are edges with equal weights
- MST is unique if all edge weights are distinct
- MST always has exactly **V-1 edges**
- **Cut property:** The minimum weight edge crossing any cut of the graph is always in some MST
- **Cycle property:** The maximum weight edge in any cycle is never in any MST

---

## Two Algorithms to Find MST

### 1. Prim's Algorithm (Greedy — grow tree from a node)

**Idea:** Start from any node. Greedily pick the minimum weight edge that connects a visited node to an unvisited node. Repeat until all nodes are included.

```
Think of it as: "grow the MST one vertex at a time"

Data structure: Min-heap (priority queue)
  State: {weight, node}
  Mark node visited when popped

Key: process an edge only if the destination is NOT yet in MST
```

**Pseudocode:**
```
dist[V] = 1e9, dist[src] = 0
vis[V] = false
pq = min-heap, push {0, src}
mstWeight = 0

while pq not empty:
    {wt, node} = pq.pop()
    if vis[node]: continue
    vis[node] = true
    mstWeight += wt
    for each (adjNode, edgeWt) in adj[node]:
        if not vis[adjNode]:
            pq.push({edgeWt, adjNode})

return mstWeight
```

**Time:** O((V+E) log V) — same as Dijkstra
**Space:** O(V+E)

**Difference from Dijkstra:**
```
Dijkstra:  push {dist[node] + edgeWt, adjNode}   ← cumulative distance
Prim's:    push {edgeWt, adjNode}                 ← just the edge weight
```

---

### 2. Kruskal's Algorithm (Greedy — sort edges, use DSU)

**Idea:** Sort all edges by weight. For each edge (cheapest first), add it to MST if it doesn't form a cycle. Use **Disjoint Set Union (DSU)** to detect cycles in O(α(V)) ≈ O(1).

```
Think of it as: "pick the cheapest safe edge globally"

Data structure: Sort edges + DSU (Union-Find)
  An edge is "safe" if its two endpoints are in different components
```

**Pseudocode:**
```
Sort edges by weight
DSU: parent[i]=i, rank[i]=0
mstWeight = 0, edgesAdded = 0

for each (u, v, wt) in sorted edges:
    if find(u) != find(v):    ← different components (no cycle)
        union(u, v)
        mstWeight += wt
        edgesAdded++
        if edgesAdded == V-1: break   ← MST complete

if edgesAdded < V-1: graph is disconnected
return mstWeight
```

**Time:** O(E log E) — dominated by sorting
**Space:** O(V) — DSU arrays

---

## Prim's vs Kruskal's

| | Prim's | Kruskal's |
|--|--------|-----------|
| **Approach** | Grow tree from a node | Pick globally cheapest safe edge |
| **Data structure** | Min-heap (priority queue) | Sort + DSU |
| **Time** | O((V+E) log V) | O(E log E) |
| **Better for** | Dense graphs (E ≈ V²) | Sparse graphs (E ≈ V) |
| **Starting point** | Any single node | All edges globally |
| **Cycle avoidance** | `vis[]` array | DSU find() |
| **Similarity** | Very similar to Dijkstra | Requires DSU knowledge |

```
Dense graph (E ≈ V²):
  Prim's:    O(V² log V)
  Kruskal's: O(V² log V²) = O(V² log V)  — same asymptotically

Sparse graph (E ≈ V):
  Prim's:    O(V log V)
  Kruskal's: O(V log V)   — similar

In practice: Kruskal's often preferred for its simplicity when E is manageable.
```

---

## Key Properties (Interview Gold)

```
1. V-1 edges: MST always has exactly V-1 edges for V nodes.

2. Cut property: For any cut (partition of nodes into two sets S and V-S),
   the minimum weight edge crossing the cut is in SOME MST.
   → This is WHY Prim's works: we always pick min edge crossing the cut
     between visited and unvisited nodes.

3. Cycle property: The maximum weight edge in any cycle is NOT in any MST.
   → This is WHY Kruskal's works: we skip edges that form cycles.

4. Uniqueness: MST is unique if all edge weights are distinct.
   Multiple MSTs possible when equal-weight edges exist.

5. MST is not unique for the shortest path: MST minimizes total tree weight,
   NOT the shortest path between specific nodes.
```

---

## Common Interview Questions on MST

**Q: What's the difference between MST and shortest path?**
> MST minimizes the total weight of edges used to connect ALL nodes.
> Shortest path minimizes cost between a specific source and destination.
> They are different: the MST path between two nodes is NOT necessarily the shortest path.

**Q: Can Prim's or Kruskal's handle negative weights?**
> Yes — both algorithms work correctly with negative edge weights.
> Unlike Dijkstra (which fails with negatives), MST algorithms don't accumulate path costs.

**Q: What if the graph is disconnected?**
> There's no spanning tree (can't connect all nodes).
> Result is a Minimum Spanning Forest (MST for each connected component).
> Kruskal's handles this naturally; Prim's needs to be run from each unvisited node.

**Q: When would you use MST in practice?**
> - Network design: laying cables/pipes connecting all cities at minimum cost
> - Cluster analysis: build MST, remove k-1 heaviest edges → k clusters
> - Approximation algorithms: TSP 2-approximation uses MST

---

## Prim's vs Dijkstra — Side by Side

```cpp
// Dijkstra
if(dis + edgeWt < dist[adjNode]){
    dist[adjNode] = dis + edgeWt;   // cumulative distance from source
    pq.push({dist[adjNode], adjNode});
}

// Prim's
if(!vis[adjNode]){
    pq.push({edgeWt, adjNode});     // just the edge weight, not cumulative
}
```

> The single key difference: Prim's pushes raw edge weight; Dijkstra pushes accumulated distance. Prim's uses `vis[]` to skip already-included MST nodes; Dijkstra has no such skip (stale entries handled by relaxation).

---

## Recall Line *(10-Second Revision)*

> "MST: V-1 edges, min total weight, connects all nodes, no cycles. Prim's = Dijkstra-like with edge weight (not cumulative). Kruskal's = sort edges + DSU."

---

## Short Revision Notes

- Spanning tree: V vertices, V-1 edges, connected, acyclic
- MST: spanning tree with minimum sum of edge weights
- Both Prim's and Kruskal's are greedy and provably optimal via cut/cycle properties
- Prim's: start anywhere, use min-heap, skip visited nodes
- Kruskal's: sort edges, skip edges forming cycles (DSU)
- Both handle negative weights correctly
- Disconnected graph → no MST (only spanning forest)

---

## Pattern Category

`Graphs` · `MST` · `Greedy` · `Prim's` · `Kruskal's` · `DSU`

---

## Coming Up

- **P38** — Prim's Algorithm (code)
- **P39** — Kruskal's Algorithm + DSU (code)
