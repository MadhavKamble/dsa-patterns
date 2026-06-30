# Kruskal's Algorithm — MST using Disjoint Set

> **GFG Problem** · **Difficulty:** Medium · **Step 15 — Graphs · P40**

---

## Problem Understanding

**What is it asking?**
Given a connected undirected weighted graph with `V` vertices and `edges[][]`, find the **sum of weights of the Minimum Spanning Tree** using Kruskal's algorithm with DSU.

**Input:** `V`, `edges[][]` — each `[u, v, weight]`
**Output:** Total weight of MST

**Example:**
```
V=5, edges: 0-1(2), 0-3(6), 1-2(3), 1-3(8), 1-4(5), 2-4(7), 3-4(9)

Sorted edges: (0-1,2),(1-2,3),(1-4,5),(0-3,6),(2-4,7),(1-3,8),(3-4,9)

Pick 0-1(2): find(0)=0 ≠ find(1)=1 → add. MST={0-1}
Pick 1-2(3): find(1)=0 ≠ find(2)=2 → add. MST={0-1,1-2}
Pick 1-4(5): find(1)=0 ≠ find(4)=4 → add. MST={0-1,1-2,1-4}
Pick 0-3(6): find(0)=0 ≠ find(3)=3 → add. MST={0-1,1-2,1-4,0-3}
(V-1=4 edges added → stop)

MST weight = 2+3+5+6 = 16
```

**Key Observations:**
- Sort edges by weight → greedy pick cheapest safe edge
- "Safe" = doesn't form a cycle = the two endpoints have different roots in DSU
- Each successful union adds exactly one edge to MST
- Stop after V-1 edges are added (MST is complete)

---

## Kruskal's Core Idea

```
Sort all edges by weight (ascending).
For each edge (u, v, wt):
  if findUPar(u) != findUPar(v):   ← different components → no cycle
    add edge to MST
    union(u, v)                     ← merge their components
  else:
    skip                            ← same component → would form cycle

MST is complete when V-1 edges are added.
```

---

## DSU + Kruskal — Why It Works

```
After sorting, we always pick the globally cheapest remaining safe edge.

"Safe" is proven by the Cut Property:
  The minimum-weight edge crossing any cut (partition of nodes)
  is always in some MST.

When we pick the cheapest edge between two different components,
we're picking the min-weight edge crossing the cut
{component of u} vs {everything else} → it belongs in the MST.

DSU makes the "does this create a cycle?" check O(α(N)) ≈ O(1).
Without DSU: O(V) per check via BFS/DFS → O(EV) total.
With DSU:    O(α(N)) per check → O(E log E) total (sort dominates).
```

---

## Algorithm

1. Sort `edges` by weight (ascending)
2. Initialize DSU with `V` nodes
3. For each edge `(u, v, wt)`:
   - `if findUPar(u) != findUPar(v)` → `mstWt += wt`, `union(u, v)`
4. Return `mstWt`

---

## Dry Run

**V=4, edges: 0-1(4), 0-2(1), 1-3(2), 2-3(5)**

```
Sorted: 0-2(1), 1-3(2), 0-1(4), 2-3(5)

DSU init: parent=[0,1,2,3], size=[1,1,1,1]

Edge 0-2(1): find(0)=0, find(2)=2. Different → mstWt=1, union(0,2)
  size[0]=1 < size[2]=1? No (equal) → parent[2]=0, size[0]=2
  parent=[0,1,0,3]

Edge 1-3(2): find(1)=1, find(3)=3. Different → mstWt=3, union(1,3)
  equal size → parent[3]=1, size[1]=2
  parent=[0,1,0,1]

Edge 0-1(4): find(0)=0, find(1)=1. Different → mstWt=7, union(0,1)
  size[0]=2 == size[1]=2 → parent[1]=0, size[0]=4
  parent=[0,0,0,1]

(3 edges added = V-1 = 3 → MST complete, skip remaining)

Edge 2-3(5): find(2)=0, find(3)=0. Same → skip

MST weight = 7 ✅  (edges: 0-2, 1-3, 0-1)
```

### Complexity
- **Time:** O(E log E) — sorting dominates; DSU operations O(α(N)) ≈ O(1)
- **Space:** O(V) — DSU arrays

---

## Clean C++ Interview Code

```cpp
class DisjointSet {
    vector<int> parent, size;
public:
    DisjointSet(int n) {
        parent.resize(n+1);
        size.resize(n+1);
        for(int i=0;i<=n;i++){
            parent[i]=i;
            size[i]=1;
        }
    }

    int findUPar(int node) {
        if(node==parent[node])
            return node;
        return parent[node]=findUPar(parent[node]);
    }

    void unionBySize(int u, int v) {
        int ulp_u=findUPar(u);
        int ulp_v=findUPar(v);
        if(ulp_u==ulp_v) return;
        if(size[ulp_u]<size[ulp_v]){
            parent[ulp_u]=ulp_v;
            size[ulp_v]+=size[ulp_u];
        }else{
            parent[ulp_v]=ulp_u;
            size[ulp_u]+=size[ulp_v];
        }
    }
};

class Solution {
public:
    int spanningTree(int V, vector<vector<int>>& edges) {
        sort(edges.begin(),edges.end(),[](auto& a, auto& b){
            return a[2]<b[2];
        });
        DisjointSet ds(V);
        int mstWt=0;
        for(auto it: edges){
            int u=it[0];
            int v=it[1];
            int wt=it[2];
            if(ds.findUPar(u)!=ds.findUPar(v)){
                mstWt+=wt;
                ds.unionBySize(u,v);
            }
        }
        return mstWt;
    }
};
```

---

## Variant — Also Print MST Edges

Every edge where `findUPar(u) != findUPar(v)` is an MST edge — collect them directly.

```cpp
class Solution {
public:
    pair<int,vector<pair<int,int>>> spanningTreeWithEdges(int V, vector<vector<int>>& edges) {
        sort(edges.begin(),edges.end(),[](auto& a, auto& b){
            return a[2]<b[2];
        });
        DisjointSet ds(V);
        int mstWt=0;
        vector<pair<int,int>> mstEdges;
        for(auto it: edges){
            int u=it[0];
            int v=it[1];
            int wt=it[2];
            if(ds.findUPar(u)!=ds.findUPar(v)){
                mstWt+=wt;
                ds.unionBySize(u,v);
                mstEdges.push_back({u,v});   // ← this edge is in MST
            }
        }
        return {mstWt,mstEdges};
    }
};
```

> Kruskal's prints MST edges naturally — each accepted edge is an MST edge.
> Compare with Prim's (P38) where we needed parent tracking in the heap.

---

## Kruskal's vs Prim's

| | Kruskal's | Prim's |
|--|-----------|--------|
| **Approach** | Global edge sort + DSU | Grow tree from node using heap |
| **Cycle avoidance** | DSU `findUPar` check | `vis[]` array |
| **Sort** | Sort all edges once O(E log E) | No pre-sort; heap handles order |
| **Data structure** | Sorted edge list + DSU | Min-heap |
| **MST edges** | Direct — each accepted edge | Via parent tracking in heap |
| **Better for** | Sparse graphs (E ≈ V) | Dense graphs (E ≈ V²) |
| **Handles disconnected** | Yes (spanning forest) | Needs restart per component |

---

## Cycle Detection Reminder

```
DSU detects cycle in O(α(N)):
  Before adding edge (u,v):
    if findUPar(u) == findUPar(v) → same component → adding creates cycle → skip
    else → safe → add + union

This is more efficient than DFS cycle detection O(V+E) per edge.
For Kruskal's across E edges: O(E × α(N)) vs O(E × (V+E)) without DSU.
```

---

## Interview Explanation Script

> "Kruskal's sorts all edges by weight, then greedily picks the cheapest edge that doesn't form a cycle. I use DSU to check cycles in O(α(N)) — two nodes are in a cycle if they already share the same DSU root before the edge is added."

> "Each accepted edge is a confirmed MST edge. We stop when V-1 edges are added. The sort is O(E log E) which dominates the overall complexity."

> "Kruskal's naturally gives the MST edges — unlike Prim's where you need parent tracking. The tradeoff: Kruskal's needs a DSU, Prim's needs a min-heap."

---

## Recall Line *(10-Second Revision)*

> "Kruskal's: sort edges by wt. For each: findUPar(u)!=findUPar(v) → add wt, union. O(E log E) + DSU."

---

## Short Revision Notes

- Sort by `edge[2]` (weight) not by node
- Lambda comparator: `[](auto& a, auto& b){ return a[2]<b[2]; }`
- DSU check: `findUPar(u) != findUPar(v)` — do this BEFORE union
- Union after adding to MST — order matters
- No explicit V-1 break needed (correct, but can optimize early exit)
- DSU initialized with `V` nodes (0 to V-1 or 1 to V depending on input)

---

## Pattern Recognition Trigger

**When I see:**
- "MST using Kruskal's"
- "Connect nodes at minimum cost — sort edges approach"
- "Cycle detection while building spanning tree"

**I should think of:** Sort edges + DSU `findUPar` check

---

## Common Mistakes

❌ Sorting by node index instead of weight
❌ Calling `union` before the `findUPar` check — then check is useless
❌ `findUPar(u) == findUPar(v)` (adding cycle edges) instead of `!=` (safe edges)
❌ DSU initialized with wrong size — must cover all node indices used

---

## What Interviewer Is Testing

- **Why sort edges** — greedy proof via cut property
- **DSU for cycle detection** — O(α(N)) vs O(V+E) DFS
- **findUPar before union, not after** — logical order
- **Kruskal's vs Prim's** tradeoff

---

## Related Problems

- [ ] Striver Step 15 P38 — Prim's MST (heap-based approach)
- [ ] Striver Step 15 P39 — DSU Theory and Implementation
- [ ] LeetCode #1584 — Min Cost to Connect All Points (Kruskal's on coordinate plane)
- [ ] LeetCode #684 — Redundant Connection (DSU cycle detection — same pattern)

---

## Pattern Category

`Graphs` · `MST` · `Kruskal's` · `DSU` · `Greedy` · `Sort`

---

## 30-Second Last-Minute Revision

> **Kruskal's MST:** Sort edges by weight. Init DSU.
> For each edge `(u,v,wt)`: `findUPar(u) != findUPar(v)` → `mstWt+=wt`, `unionBySize(u,v)`.
> Skip if same root (cycle). Each accepted edge = MST edge (print directly).
> **Time:** O(E log E) | **Key:** sort + DSU. Cycle check = same root = skip.
