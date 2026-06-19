# Detect Cycle in Directed Graph

> **GFG Problem** · **Difficulty:** Medium · **Step 15 — Graphs · P18**

---

## Problem Understanding

**What is it asking?**
Given a directed graph with `V` vertices and adjacency list `adj[]`, determine whether the graph contains a **cycle**.

**Input:** `V` (vertices), `adj[]` — array of adjacency lists
**Output:** `true` if cycle exists, `false` otherwise

**Example:**
```
Graph 1 (cycle):
0 → 1 → 2 → 3 → 1  (back edge 3→1 creates cycle)
→ true

Graph 2 (no cycle — DAG):
0 → 1 → 3
0 → 2 → 3
→ false
```

**Key Observations:**
- Undirected cycle detection uses `parent` tracking — that doesn't work for directed graphs
- In a directed graph, a cycle exists iff there is a **back edge** — an edge to a node currently on the DFS recursion stack
- Need two arrays: `vis[]` (ever visited) and `pathVis[]` (on current DFS path)
- `pathVis[node] = 0` on backtrack — this is the critical step that makes it work for directed graphs

---

## Why Two Arrays?

```
Graph: 1 → 2 → 3, 4 → 2

DFS from 4: visits 4 → 2 → 3
pathVis after: {2:0, 3:0, 4:0} (backtracked)

DFS from 1: visits 1 → 2
vis[2] = 1 (already visited) BUT pathVis[2] = 0 (not on current path)
→ NOT a cycle — this is just a shared node, not a back edge
```

Without `pathVis`, checking only `vis` would give false positives on shared nodes.

---

## Optimal Approach — DFS with Path Visited Array

### Key Observation

> A back edge in a directed graph is an edge `u → v` where `v` is an ancestor of `u` in the **current DFS path**. `pathVis[v] == 1` means `v` is on the current recursion stack. If a neighbor is already on the current path, we found a cycle.
>
> After returning from DFS, reset `pathVis[node] = 0` — the node is no longer on the active path.

### Algorithm
1. `vis[0..V-1] = 0`, `pathVis[0..V-1] = 0`
2. For each unvisited node `i`: run `dfsCheck(i)`
3. `dfsCheck(node)`: mark `vis[node]=1`, `pathVis[node]=1`
4. For each neighbor `it`:
   - Not visited: recurse; if returns true → propagate
   - Visited AND `pathVis[it]==1`: **cycle** → return true
5. **Backtrack:** `pathVis[node]=0`, return false

### Dry Run

**Graph: 0→1, 1→2, 2→0 (cycle)**

```
dfsCheck(0): vis[0]=1, pathVis[0]=1
  dfsCheck(1): vis[1]=1, pathVis[1]=1
    dfsCheck(2): vis[2]=1, pathVis[2]=1
      neighbor 0: vis[0]=1 & pathVis[0]=1 → CYCLE → return true
```
Return `true` ✅

**Graph: 0→1, 2→1 (shared node, no cycle)**

```
dfsCheck(0): vis[0]=1, pathVis[0]=1
  dfsCheck(1): vis[1]=1, pathVis[1]=1
    no neighbors
    pathVis[1]=0 ← backtrack
  pathVis[0]=0 ← backtrack

dfsCheck(2): vis[2]=1, pathVis[2]=1
  neighbor 1: vis[1]=1 but pathVis[1]=0 → NOT a cycle, skip
  pathVis[2]=0 ← backtrack

return false
```
Return `false` ✅

### Complexity
- **Time:** O(V + E) — each node and edge visited once
- **Space:** O(V) — vis, pathVis arrays + recursion stack

---

## Clean C++ Interview Code

```cpp
class Solution {
private:
    bool dfsCheck(int node, vector<int> adj[], int vis[], int pathVis[]) {
        vis[node]=1;
        pathVis[node]=1;
        for(auto it : adj[node]) {
            if(!vis[it]) {
                if(dfsCheck(it,adj,vis,pathVis)==true)
                    return true;
            }
            else if(pathVis[it]) {
                return true;
            }
        }
        pathVis[node]=0;
        return false;
    }
public:
    bool isCyclic(int V, vector<int> adj[]) {
        int vis[V]={0};
        int pathVis[V]={0};
        for(int i=0;i<V;i++) {
            if(!vis[i]) {
                if(dfsCheck(i,adj,vis,pathVis)==true) return true;
            }
        }
        return false;
    }
};
```

### BFS Variant — Kahn's Algorithm (Topological Sort)

```cpp
// A directed graph has a cycle ↔ topological sort is impossible
// (not all nodes can be added to the order)
class Solution {
public:
    bool isCyclic(int V, vector<int> adj[]) {
        vector<int> inDegree(V,0);
        for(int i=0;i<V;i++)
            for(auto it : adj[i])
                inDegree[it]++;

        queue<int> q;
        for(int i=0;i<V;i++)
            if(inDegree[i]==0) q.push(i);

        int count=0;
        while(!q.empty()) {
            int node=q.front(); q.pop();
            count++;
            for(auto it : adj[node]) {
                inDegree[it]--;
                if(inDegree[it]==0) q.push(it);
            }
        }
        return count != V;    // if not all nodes processed → cycle exists
    }
};
```

---

## Interview Explanation Script

> "I use DFS with two boolean arrays: `vis[]` tracks globally visited nodes, `pathVis[]` tracks nodes on the current DFS recursion stack. If I reach a neighbor that's already visited AND on the current path (`pathVis[it]==1`), I've found a back edge — a cycle."

> "The critical step is resetting `pathVis[node]=0` when backtracking. This is what makes it work for directed graphs. Without it, a shared node visited in one DFS branch would falsely look like a cycle when encountered in another branch."

> "Alternative: Kahn's algorithm — if topological sort can't process all V nodes (cycle prevents some from ever reaching in-degree 0), the graph has a cycle."

---

## Recall Line *(10-Second Revision)*

> "Cycle (directed, DFS): vis[] + pathVis[]. pathVis[it]==1 → cycle. Reset pathVis on backtrack. O(V+E)."

---

## Short Revision Notes

- `vis[]`: globally visited — prevents re-processing nodes
- `pathVis[]`: on current DFS stack — detects back edges
- Reset `pathVis[node]=0` after recursion returns (backtrack step)
- Neighbor `vis[it]=1` alone is NOT a cycle — could be a cross edge or forward edge
- Need BOTH: `vis[it]=1 AND pathVis[it]=1` → back edge → cycle
- Kahn's BFS approach: cycle ↔ `count != V` after topological sort

---

## Undirected vs Directed Cycle Detection

| Property | Undirected | Directed |
|----------|-----------|---------|
| Extra tracking | `parent` param | `pathVis[]` array |
| Cycle condition | `vis[nb] && nb!=parent` | `vis[nb] && pathVis[nb]` |
| Backtrack reset | Not needed | `pathVis[node]=0` |
| BFS alternative | Parent in queue | Kahn's algorithm |

---

## Pattern Recognition Trigger

**When I see:**
- "Detect cycle in directed graph"
- "Is this directed graph a DAG?"
- "Can we complete all courses?" (Course Schedule)

**I should think of:** DFS + pathVis[], OR Kahn's topological sort

---

## Common Mistakes

❌ Using parent tracking (undirected technique) on directed graph → wrong
❌ Only checking `vis[it]` without `pathVis[it]` → false positives on shared/cross edges
❌ Forgetting `pathVis[node]=0` on backtrack → treats finished nodes as still on path
❌ Not using outer loop → misses disconnected components

---

## What Interviewer Is Testing

- **Why `pathVis[]` is needed** (vs just `vis[]`)
- **Backtrack reset** — the most commonly forgotten step
- **Directed vs undirected** cycle detection difference
- **Kahn's alternative** — shows understanding of the connection to topological sort

---

## Related Problems

- [ ] LeetCode #207 — Course Schedule (cycle in directed graph)
- [ ] LeetCode #210 — Course Schedule II (topological sort)
- [ ] Striver Step 15 P11 — Cycle Detection Undirected (DFS)
- [ ] Striver Step 15 P19 — Topological Sort (DFS)
- [ ] Striver Step 15 P20 — Kahn's Algorithm (BFS Topo Sort)

---

## Pattern Category

`Graphs` · `DFS` · `Cycle Detection` · `Directed Graph` · `Topological Sort`

---

## Difficulty Analysis

**Rating:** Medium (concept clear once you understand why `pathVis` is needed; the backtrack reset is the key detail)

**Why challenging:** Understanding why `vis[]` alone isn't enough, and why the backtrack `pathVis[node]=0` is critical.

---

## 30-Second Last-Minute Revision

> **Cycle in Directed (DFS):** Two arrays — `vis[]` (ever seen) + `pathVis[]` (current stack).
> Mark both on entry. If neighbor is `vis && pathVis` → cycle.
> **Backtrack: `pathVis[node]=0`** before returning false.
> Outer loop for disconnected components.
> **Time:** O(V+E) | **Space:** O(V)
