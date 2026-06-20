# Shortest Path in Directed Acyclic Graph

> **GFG Problem** · **Difficulty:** Medium · **Step 15 — Graphs · P23**

---

## Problem Understanding

**What is it asking?**
Given a DAG with `V` vertices, `E` edges (weighted), find the shortest distance from **vertex 0** to all other vertices. Return `-1` for unreachable vertices.

**Input:** `V`, `E`, `edges[][]` — each edge is `[u, v, weight]` (directed, weighted)
**Output:** `dist[]` — shortest distance from 0 to each vertex, `-1` if unreachable

**Example:**
```
V=6, edges: 0→1(2), 0→4(1), 1→2(3), 4→2(2), 4→5(4), 2→3(6), 5→3(1)

Topo order: 0,1,4,2,5,3 (one valid order)

Relax in topo order:
Node 0 (dist=0): dist[1]=2, dist[4]=1
Node 1 (dist=2): dist[2]=min(∞,2+3)=5
Node 4 (dist=1): dist[2]=min(5,1+2)=3, dist[5]=1+4=5
Node 2 (dist=3): dist[3]=min(∞,3+6)=9
Node 5 (dist=5): dist[3]=min(9,5+1)=6
Node 3 (dist=6): no outgoing edges

dist = [0,2,3,6,1,5]
```

**Key Observations:**
- In a DAG, topological order guarantees: when we process node `u`, all shortest paths TO `u` are already finalized
- Relaxing edges in topo order = one pass is enough (no cycles to loop back)
- Dijkstra runs O((V+E)logV); DAG shortest path runs O(V+E) — strictly better when graph is a DAG
- Source is always vertex 0 in this problem

---

## Optimal Approach — Topo Sort + Edge Relaxation

### Key Observation

> In a DAG, if we process nodes in topological order, every predecessor of a node is processed before it. So when we reach node `u` in topo order, `dist[u]` is already optimal — we can safely relax all outgoing edges from `u`. One linear pass through the topo order is sufficient.
>
> Skip nodes with `dist[node]==1e9` — they are unreachable and can't contribute to any shortest path.

### Algorithm
1. Build weighted adjacency list from edges
2. DFS topological sort → push nodes to stack after all neighbors
3. `dist[0..V-1] = 1e9`, `dist[0] = 0`
4. Process stack (topo order): for each `node`, if reachable, relax all outgoing edges
5. Replace `1e9` with `-1`

### Dry Run

**V=4, edges: 0→1(2), 0→2(4), 1→2(1), 1→3(7), 2→3(1)**

```
Topo order (stack top to bottom): 0, 1, 2, 3

Init: dist=[0, 1e9, 1e9, 1e9]

Process 0 (dist=0):
  dist[1]=min(1e9,0+2)=2
  dist[2]=min(1e9,0+4)=4

Process 1 (dist=2):
  dist[2]=min(4,2+1)=3
  dist[3]=min(1e9,2+7)=9

Process 2 (dist=3):
  dist[3]=min(9,3+1)=4

Process 3 (dist=4): no outgoing edges

dist=[0,2,3,4] ✅
```

### Complexity
- **Time:** O(V + E) — topo sort O(V+E) + single relaxation pass O(V+E)
- **Space:** O(V + E) — adjacency list + dist array + stack

---

## Clean C++ Interview Code

```cpp
class Solution {
public:
    void topoSort(int node, vector<pair<int,int>> adj[],
                  vector<int>& vis, stack<int>& st){
        vis[node]=1;
        for(auto it: adj[node]){
            int v=it.first;
            if(!vis[v]){
                topoSort(v,adj,vis,st);
            }
        }
        st.push(node);
    }
    vector<int> shortestPath(int V, int E, vector<vector<int>>& edges) {
        vector<pair<int,int>> adj[V];
        for(int i=0;i<edges.size();i++){
            int u=edges[i][0];
            int v=edges[i][1];
            int wt=edges[i][2];
            adj[u].push_back({v,wt});
        }
        vector<int> vis(V,0);
        stack<int> st;
        for(int i=0;i<V;i++){
            if(!vis[i])
                topoSort(i,adj,vis,st);
        }
        vector<int> dist(V,1e9);
        dist[0]=0;
        while(!st.empty()){
            int node=st.top();
            st.pop();
            if(dist[node]!=1e9){
                for(auto it:adj[node]){
                    int v=it.first;
                    int wt=it.second;
                    if(dist[node]+wt<dist[v]){
                        dist[v]=dist[node]+wt;
                    }
                }
            }
        }
        for(int i=0;i<V;i++){
            if(dist[i]==1e9)
                dist[i]=-1;
        }
        return dist;
    }
};
```

---

## Why Topo Order Works — Intuition

```
In topo order, for any edge u→v, u always appears before v.

So when we relax edges from u:
- dist[u] is already final (all paths to u processed before u in topo order)
- We can safely update dist[v] = dist[u] + wt

No node needs to be revisited → single pass = O(V+E)

This ONLY works for DAGs. Cycles break this guarantee → need Dijkstra/Bellman-Ford.
```

---

## Interview Explanation Script

> "For a DAG, I can find shortest paths in O(V+E) — better than Dijkstra's O((V+E)logV). First I get the topological order via DFS. Then I relax edges in that order: for each node processed, all paths leading TO it are already finalized (because all predecessors come earlier in topo order). So one linear pass through the topo order is enough."

> "The `dist[node]!=1e9` check is important — if a node is unreachable from source, relaxing its edges would set neighbors to bogus values like `1e9+wt`."

---

## Recall Line *(10-Second Revision)*

> "DAG shortest path: topo sort → relax edges in topo order → O(V+E). Skip unreachable nodes (dist==1e9)."

---

## Short Revision Notes

- Topo sort first, then single relaxation pass — total O(V+E)
- `dist[node]!=1e9` guard — unreachable node shouldn't relax its neighbors
- Source = vertex 0 (hardcoded in this problem, not passed as parameter)
- Directed edges only: `adj[u].push_back({v,wt})` — no reverse edge
- Works for negative weights too (unlike Dijkstra) — DAGs can have negative edges, no cycles to cause issues

---

## Comparison: DAG vs General Shortest Path

| Approach | Graph type | Negative edges | Time |
|----------|-----------|----------------|------|
| BFS | Unweighted | N/A | O(V+E) |
| DAG (topo + relax) | DAG only | ✅ Yes | O(V+E) |
| Dijkstra | General (no neg) | ❌ No | O((V+E)logV) |
| Bellman-Ford | General | ✅ Yes | O(VE) |

---

## Pattern Recognition Trigger

**When I see:**
- "Shortest path in DAG"
- "Weighted DAG, find distances from source"
- "Graph with no cycles, find shortest/longest path"

**I should think of:** Topo sort → relax in topo order

---

## Common Mistakes

❌ Missing `dist[node]!=1e9` check → unreachable nodes propagate garbage values
❌ Using Dijkstra for a DAG — correct but suboptimal
❌ Adding reverse edge (this is a directed graph — one direction only)
❌ Not handling the case where some nodes have no path from source (keep as -1)

---

## What Interviewer Is Testing

- **Why topo sort enables O(V+E) shortest path** on DAGs
- **DAG = can have negative edges** (unlike Dijkstra)
- **Unreachable node guard** (`dist[node]!=1e9`)
- Knowing when to use which shortest path algorithm

---

## Related Problems

- [ ] Striver Step 15 P22 — Shortest Path Undirected Unit Weight (BFS)
- [ ] Striver Step 15 P24 — Dijkstra's Algorithm
- [ ] Striver Step 15 P20 — Topological Sort
- [ ] LeetCode #1514 — Path with Maximum Probability (Dijkstra variant)

---

## Pattern Category

`Graphs` · `DAG` · `Topological Sort` · `Shortest Path` · `Edge Relaxation`

---

## 30-Second Last-Minute Revision

> **DAG Shortest Path:** DFS topo sort → stack. Init `dist[]=1e9`, `dist[0]=0`.
> Pop stack → if `dist[node]!=1e9` → relax all outgoing edges.
> `dist[i]==1e9` → output `-1`.
> **Time:** O(V+E) | Works with negative edges | Only for DAGs.
