# Prim's Algorithm — Minimum Spanning Tree

> **GFG Problem** · **Difficulty:** Medium · **Step 15 — Graphs · P38**

---

## Problem Understanding

**What is it asking?**
Given a connected undirected weighted graph with `V` vertices and `edges[][]`, find the **sum of weights of the Minimum Spanning Tree** using Prim's algorithm.

**Input:** `V`, `edges[][]` — each `[u, v, weight]`
**Output:** Total weight of MST

**Example:**
```
V=5, edges: 0-1(2), 0-3(6), 1-2(3), 1-3(8), 1-4(5), 2-4(7), 3-4(9)

MST edges: 0-1(2), 1-2(3), 1-4(5), 0-3(6)
MST weight = 2+3+5+6 = 16
```

**Key Observations:**
- Prim's is Dijkstra-like but pushes raw `edgeWeight` (not cumulative distance)
- `vis[]` replaces the stale-entry check — once a node is in MST, skip it
- Add weight to `sum` when node is **popped** (confirmed into MST), not when pushed
- Start from any node (here node 0) — MST weight is same regardless

---

## Prim's vs Dijkstra — The One Difference

```cpp
// Dijkstra: push cumulative distance
if(dis + edgeWt < dist[adjNode]){
    dist[adjNode] = dis + edgeWt;
    pq.push({dist[adjNode], adjNode});
}

// Prim's: push raw edge weight
if(!vis[adjNode]){
    pq.push({edgeWeight, adjNode});   // just the edge, not path sum
}
```

> In Dijkstra we want the shortest path from source — cumulative cost matters.
> In Prim's we want the cheapest edge to expand the tree — only edge weight matters.

---

## Optimal Approach — Prim's with Min-Heap

### Algorithm
1. Build adjacency list
2. `vis[V]=0`, push `{0, 0}` (weight=0, node=0) to min-heap
3. Pop `{wt, node}`: if already visited → skip
4. Mark visited, add `wt` to `sum`
5. Push all unvisited neighbors with their edge weights
6. Return `sum`

### Dry Run

**V=4, edges: 0-1(4), 0-2(1), 1-3(2), 2-3(5)**

```
Init: vis=[0,0,0,0], pq={(0,0)}, sum=0

Pop (0,0): vis[0]=0 → vis[0]=1, sum=0
  Push neighbors: (4,1), (1,2)
  pq={(1,2),(4,1)}

Pop (1,2): vis[2]=0 → vis[2]=1, sum=0+1=1
  Push neighbors: (4,0→skip vis),(5,3)
  pq={(4,1),(5,3)}

Pop (4,1): vis[1]=0 → vis[1]=1, sum=1+4=5
  Push neighbors: (4,0→skip),(2,3)
  pq={(2,3),(5,3)}

Pop (2,3): vis[3]=0 → vis[3]=1, sum=5+2=7
  Push neighbors: (2,1→skip),(5,2→skip)
  pq={(5,3)}

Pop (5,3): vis[3]=1 → skip

return 7 ✅  (MST: 0-2(1), 0-1(4), 1-3(2) = 7)
```

### Complexity
- **Time:** O((V+E) log V) — each edge pushed to heap at most once
- **Space:** O(V+E) — adjacency list + heap

---

## Clean C++ Interview Code

```cpp
class Solution {
  public:
    int spanningTree(int V, vector<vector<int>>& edges) {
        vector<pair<int,int>> adj[V];
        for(auto it: edges){
            adj[it[0]].push_back({it[1],it[2]});
            adj[it[1]].push_back({it[0],it[2]});
        }
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
        vector<int> vis(V,0);
        pq.push({0,0});
        int sum=0;
        while(!pq.empty()){
            auto it=pq.top();
            pq.pop();
            int node=it.second;
            int wt=it.first;
            if(vis[node]==1) continue;
            vis[node]=1;
            sum+=wt;
            for(auto it: adj[node]){
                int adjNode=it.first;
                int edgeWeight=it.second;
                if(!vis[adjNode]){
                    pq.push({edgeWeight,adjNode});
                }
            }
        }
        return sum;
    }
};
```

---

## Variant — Also Print MST Edges

Track the parent node when pushing to the heap. When a node is confirmed into MST, record the edge `{parent, node}`.

```cpp
class Solution {
  public:
    pair<int, vector<pair<int,int>>> spanningTreeWithEdges(int V, vector<vector<int>>& edges) {
        vector<pair<int,int>> adj[V];
        for(auto it: edges){
            adj[it[0]].push_back({it[1],it[2]});
            adj[it[1]].push_back({it[0],it[2]});
        }
        // {weight, {node, parent}}
        priority_queue<pair<int,pair<int,int>>,
                       vector<pair<int,pair<int,int>>>,
                       greater<pair<int,pair<int,int>>>> pq;
        vector<int> vis(V,0);
        pq.push({0,{0,-1}});
        int sum=0;
        vector<pair<int,int>> mstEdges;
        while(!pq.empty()){
            auto it=pq.top();
            pq.pop();
            int wt=it.first;
            int node=it.second.first;
            int parent=it.second.second;
            if(vis[node]==1) continue;
            vis[node]=1;
            sum+=wt;
            if(parent!=-1) mstEdges.push_back({parent,node});
            for(auto it: adj[node]){
                int adjNode=it.first;
                int edgeWeight=it.second;
                if(!vis[adjNode]){
                    pq.push({edgeWeight,{adjNode,node}});
                }
            }
        }
        return {sum, mstEdges};
    }
};
```

**What changes:**
- Queue stores `{weight, {node, parent}}` instead of `{weight, node}`
- Source node pushed with parent `-1`
- On pop (MST confirmation): if `parent != -1` → record `{parent, node}` as MST edge
- Returns both the MST weight and the V-1 edges

**Dry Run on same graph (V=4):**
```
Pop (0,{0,-1}): parent=-1, no edge recorded. Push (4,{1,0}),(1,{2,0})
Pop (1,{2,0}): parent=0 → mstEdges={(0,2)}. Push (5,{3,2})
Pop (4,{1,0}): parent=0 → mstEdges={(0,2),(0,1)}. Push (2,{3,1})
Pop (2,{3,1}): parent=1 → mstEdges={(0,2),(0,1),(1,3)}

MST edges: 0-2, 0-1, 1-3  ✅
```

---

## Interview Explanation Script

> "Prim's algorithm grows the MST one vertex at a time. I start from node 0 and use a min-heap to always pick the cheapest edge connecting the current MST to an unvisited node."

> "The key difference from Dijkstra: I push raw edge weights to the heap, not cumulative distances. I use `vis[]` to avoid re-adding nodes already in the MST."

> "To also track the MST edges, I store the parent node in the heap as `{weight, {node, parent}}`. When a node is confirmed into the MST (popped from heap), I record `{parent, node}` as an MST edge."

---

## Recall Line *(10-Second Revision)*

> "Prim's: min-heap {wt,node}. vis[] skip. Pop → mark vis, sum+=wt. Push unvisited neighbors with edge weight (not cumulative). O((V+E)logV)."

---

## Short Revision Notes

- Push `{0, 0}` to start — zero cost to include the source itself
- `vis[node]==1` check on pop (not on push) — multiple entries for same node can exist in heap
- Only push neighbors where `!vis[adjNode]` — small optimization, doesn't affect correctness
- `sum += wt` happens on pop, not push — ensures we only count confirmed MST edges
- For MST edges variant: push `{wt, {adjNode, node}}` — node becomes parent of adjNode

---

## Prim's vs Kruskal's (Application)

| | Prim's | Kruskal's |
|--|--------|-----------|
| Start | Single node, expand | All edges globally |
| Cycle avoidance | `vis[]` array | DSU |
| Better for | Dense graphs | Sparse graphs |
| Prints MST edges | Via parent tracking | Directly (each union = one MST edge) |

---

## Pattern Recognition Trigger

**When I see:**
- "Minimum Spanning Tree weight"
- "Connect all nodes at minimum cost"
- "Dijkstra-like but for MST"

**I should think of:** Prim's — min-heap `{edgeWt, node}` + `vis[]` (not dist[])

---

## Common Mistakes

❌ Pushing `dis + edgeWeight` like Dijkstra — should push just `edgeWeight`
❌ Using `dist[]` relaxation instead of `vis[]` — different check for MST
❌ Adding weight on push instead of pop — may count edges before they're confirmed
❌ Not starting with `{0, 0}` — source must be included with zero weight

---

## What Interviewer Is Testing

- **Prim's vs Dijkstra difference** — edge weight vs cumulative distance
- **`vis[]` instead of `dist[]`** — MST inclusion vs shortest path
- **Why add weight on pop** — only confirmed MST nodes count
- **Parent tracking** for printing actual MST edges

---

## Related Problems

- [ ] Striver Step 15 P37 — MST Theory
- [ ] Striver Step 15 P39 — Kruskal's Algorithm
- [ ] LeetCode #1584 — Min Cost to Connect All Points (Prim's on coordinate graph)

---

## Pattern Category

`Graphs` · `MST` · `Prim's` · `Greedy` · `Priority Queue`

---

## 30-Second Last-Minute Revision

> **Prim's MST:** Min-heap `{wt, node}`. `vis[V]=0`. Push `{0,0}`.
> Pop → `vis[node]` → skip. Else: `vis[node]=1`, `sum+=wt`.
> Push unvisited neighbors with raw `edgeWeight` (NOT cumulative).
> **For MST edges:** heap stores `{wt,{node,parent}}`. On pop: record `{parent,node}`.
> **Time:** O((V+E)logV) | **Key:** edge weight not cumulative; vis[] not dist[].
