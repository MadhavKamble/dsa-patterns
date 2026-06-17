# Detect Cycle in Undirected Graph (DFS)

> **GFG / Concept Problem** · **Difficulty:** Medium · **Step 15 — Graphs · P11**

---

## Problem Understanding

**What is it asking?**
Given an undirected graph with `V` vertices and `E` edges (as adjacency list), determine whether the graph contains a **cycle** — using DFS.

**Input:** `V` (vertices), `adj[][]` (adjacency list)
**Output:** `true` if cycle exists, `false` otherwise

**Example:**
```
Graph 1 (cycle exists):
0 — 1 — 2
|       |
+-------+
adj: 0:[1,2], 1:[0,2], 2:[1,0]
→ true

Graph 2 (no cycle):
0 — 1 — 2
adj: 0:[1], 1:[0,2], 2:[1]
→ false
```

**Key Observations:**
- In DFS, a cycle exists if we reach an **already-visited node** that is **not the parent** of the current node
- Same logic as BFS but implemented recursively
- Must pass `parent` through the recursion to avoid false cycle detection on the reverse edge

---

## Optimal Approach — DFS with Parent Tracking

### Key Observation

> During DFS, when we visit a neighbor that is already visited, it means we've reached a node currently on (or already finished in) our DFS path. In an undirected graph, the only already-visited neighbor we should see is the parent (via the same edge). Any other already-visited neighbor = back edge = cycle.

### Algorithm
1. `visited[0..V-1] = false`
2. For each unvisited node `i`:
   - DFS from `i` with `parent = -1`
   - At each node, mark visited, then for each neighbor `nb`:
     - If not visited: recurse `dfs(nb, curr)`; if returns true → propagate `true`
     - If visited AND `nb != parent`: **cycle** → return `true`
3. Return `false`

### Dry Run

**Graph with cycle:** `adj: 0:[1,2], 1:[0,2], 2:[1,0]`

```
dfs(0, -1): visited={0}
  neighbor 1: not visited
  dfs(1, 0): visited={0,1}
    neighbor 0: visited & 0==par(0) → skip
    neighbor 2: not visited
    dfs(2, 1): visited={0,1,2}
      neighbor 1: visited & 1==par(1) → skip
      neighbor 0: visited & 0≠par(1) → CYCLE! return true
    ← true propagates up
```

Return `true` ✅

**Graph without cycle:** `adj: 0:[1], 1:[0,2], 2:[1]`

```
dfs(0, -1): visited={0}
  dfs(1, 0): visited={0,1}
    neighbor 0: visited & 0==par → skip
    dfs(2, 1): visited={0,1,2}
      neighbor 1: visited & 1==par → skip
      return false
    return false
  return false
return false
```

Return `false` ✅

### Complexity
- **Time:** O(V + E) — each node and edge visited once
- **Space:** O(V) — visited array + recursion stack depth

---

## Clean C++ Interview Code

```cpp
class Solution {
  public:
    bool dfs(int node, int parent,vector<int> adj[], int vis[]){
        vis[node]=1;
        for(auto adjacentNode:adj[node]){
            if(!vis[adjacentNode]){
                if(dfs(adjacentNode,node,adj,vis)==true){
                    return true;
                }
            }else if(adjacentNode!=parent) return true;
        }
        return false;
    }
    bool isCycle(int V, vector<vector<int>>& edges) {
        vector<int> adj[V];
        for(auto edge:edges){
            int u=edge[0];
            int v=edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        int vis[V]={0};
        for(int i=0;i<V;i++){
            if(!vis[i]){
                if(dfs(i,-1,adj,vis))
                    return true;
            }
        }
        return false;
    }
};
```

---

## BFS vs DFS Side-by-Side

```cpp
// BFS approach — queue stores {node, parent}
bool bfsCheck(int src, vector<vector<int>>& adj, vector<bool>& visited) {
    queue<pair<int,int>> q;
    visited[src]=true;
    q.push({src,-1});
    while(!q.empty()){
        auto it=q.front(); q.pop();
        int curr=it.first; int par=it.second;
        for(int nb : adj[curr]){
            if(!visited[nb]){ visited[nb]=true; q.push({nb,curr}); }
            else if(nb!=par) return true;
        }
    }
    return false;
}

// DFS approach — parent passed through recursion
bool dfs(int node, int parent, vector<int> adj[], int vis[]) {
    vis[node]=1;
    for(auto adjacentNode:adj[node]){
        if(!vis[adjacentNode]){ if(dfs(adjacentNode,node,adj,vis)) return true; }
        else if(adjacentNode!=parent) return true;
    }
    return false;
}
```

Both detect the same condition: **visited neighbor ≠ parent**.

---

## Interview Explanation Script

> "For cycle detection in an undirected graph using DFS, I pass the parent node through the recursion. At each node, I visit unvisited neighbors recursively. If I encounter an already-visited neighbor that isn't the parent, that's a back edge — proof of a cycle."

> "The parent check prevents false positives. In an undirected graph, adjacency lists have both directions of each edge. Without the parent check, the reverse edge back to the parent would always look like a cycle."

> "DFS and BFS give the same result here. The difference is just implementation style: DFS uses the call stack (parent passed as parameter), BFS uses an explicit queue storing {node, parent}."

---

## Recall Line *(10-Second Revision)*

> "Cycle (undirected, DFS): Pass parent in recursion. Visited neighbor ≠ parent → cycle. O(V+E)."

---

## Short Revision Notes

- Same cycle condition as BFS: `visited[nb] && nb != parent`
- Parent passed as function argument — not a global/visited-array concept
- Return `true` immediately when cycle found (early exit through recursion)
- Outer for-loop mandatory for disconnected graphs
- **Does NOT work for directed graphs** — directed cycle detection needs `inStack[]` (recursion stack tracking)

---

## DFS Cycle Detection: Undirected vs Directed

| Property | Undirected | Directed |
|----------|-----------|----------|
| Check | `visited[nb] && nb != parent` | `visited[nb] && inStack[nb]` |
| Why different | Reverse edge is always present | No reverse edges; need to track current path |
| Data needed | `parent` param | `inStack[]` boolean array |

---

## Pattern Recognition Trigger

**When I see:**
- "Does this undirected graph have a cycle?"
- "Can these edges form a tree?" (tree = connected + no cycle)
- "Redundant connection in undirected graph"

**I should think of:** DFS/BFS with parent tracking, or Union-Find

---

## Common Mistakes

❌ Not passing parent → `nb != parent` check missing → always returns `true` on the reverse edge
❌ Using `inStack[]` (directed graph technique) on undirected graph → incorrect
❌ Not handling disconnected graphs with outer loop
❌ Returning `false` inside the loop instead of after all neighbors checked

---

## What Interviewer Is Testing

- **Why parent parameter is needed** for undirected (vs directed)
- **Difference between undirected and directed** cycle detection
- **Disconnected graph handling**

---

## Related Problems

- [ ] Striver Step 15 P10 — Detect Cycle Undirected (BFS)
- [ ] LeetCode #684 — Redundant Connection
- [ ] LeetCode #207 — Course Schedule (directed cycle)
- [ ] LeetCode #261 — Graph Valid Tree
- [ ] Striver Step 15 P15 — Detect Cycle in Directed Graph (DFS)

---

## Pattern Category

`Graphs` · `DFS` · `Cycle Detection` · `Undirected Graph`

---

## Difficulty Analysis

**Rating:** Medium (DFS is natural; parent parameter and directed vs undirected distinction are the key concepts)

**Why challenging:** Understanding why the parent check is needed, and knowing that this approach doesn't work for directed graphs.

---

## 30-Second Last-Minute Revision

> **Cycle in Undirected (DFS):** Pass parent through recursion. Mark visited on entry.
> For each neighbor: unvisited → recurse; visited & ≠ parent → cycle.
> Outer loop for disconnected components.
> **Time:** O(V+E) | **Space:** O(V)
> **Key distinction:** Directed graph needs `inStack[]`, not parent param.
