# Find Eventual Safe States

> **LeetCode #802** · **Difficulty:** Medium · **Step 15 — Graphs · P19**

---

## Problem Understanding

**What is it asking?**
In a directed graph, a node is **safe** if every path starting from it leads to a terminal node (a node with no outgoing edges). Return all safe nodes in sorted order.

**Input:** `graph[][]` — adjacency list of directed graph
**Output:** Sorted list of safe node indices

**Example:**
```
graph = [[1,2],[2,3],[5],[0],[5],[],[]]

Terminal nodes: 5, 6 (no outgoing edges)
Node 4 → 5 (safe)
Node 2 → 5 (safe)
Node 0 → 1 → 2 → 5 ✓, but also 0 → 2 → 5 ✓ (safe)
Node 1 → 3 → 0 → ... (cycle! unsafe)

Safe nodes: [2, 4, 5, 6]
```

**Key Observations:**
- A node is **unsafe** if it lies on a cycle or can reach a cycle
- A node is **safe** if ALL paths from it eventually reach a terminal (no cycle reachable)
- Safe nodes = nodes NOT involved in any cycle and not leading to any cycle
- Equivalent to: nodes whose DFS completes without finding a back edge

---

## Approach 1 — DFS with vis + pathVis + check

### Key Observation

> Extension of directed cycle detection (P18). Add a `check[]` array: `check[node]=1` only when DFS from `node` completes without finding a cycle. A node is safe iff its entire DFS subtree is cycle-free.

### Algorithm
1. Same DFS as cycle detection with `vis[]` and `pathVis[]`
2. At entry: `check[node]=0` (assume unsafe)
3. If cycle found from any neighbor: `check[node]=0`, return `true`
4. If DFS completes with no cycle: `check[node]=1`, `pathVis[node]=0`, return `false`
5. Collect all nodes where `check[i]==1`

```cpp
class Solution {
private:
    bool dfsCheck(int node, vector<vector<int>>& graph,vector<int>& vis,vector<int>& pathVis,vector<int>& check) {
        vis[node]=1;
        pathVis[node]=1;
        check[node]=0;
        for(auto it : graph[node]) {
            if(!vis[it]) {
                if(dfsCheck(it,graph,vis,pathVis,check)) {
                    check[node]=0;
                    return true;
                }
            }
            else if(pathVis[it]) {
                check[node]=0;
                return true;
            }
        }
        check[node]=1;
        pathVis[node]=0;
        return false;
    }
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int V=graph.size();
        vector<int> vis(V,0);
        vector<int> pathVis(V,0);
        vector<int> check(V,0);
        vector<int> safeNodes;
        for(int i=0;i<V;i++) {
            if(!vis[i]) {
                dfsCheck(i,graph,vis,pathVis,check);
            }
        }
        for(int i=0;i<V;i++) {
            if(check[i]==1)
                safeNodes.push_back(i);
        }
        return safeNodes;
    }
};
```

---

## Approach 2 — 3-State DFS (Cleaner)

### Key Observation

> Use a single `state[]` array with 3 values instead of two boolean arrays:
> - `0` = unvisited
> - `1` = visiting (currently on DFS path)
> - `2` = safe (DFS completed, no cycle)
>
> `dfsCheck` returns `true` if node is safe. If we hit a `state==1` node, we found a cycle → unsafe. If we hit a `state==2` node, it's already confirmed safe → return `true`. No need for a separate `pathVis` or `check` array.

```cpp
class Solution {
public:
    bool dfsCheck(int node, vector<vector<int>>& graph, vector<int>& state){
        if(state[node]==2) return true;
        if(state[node]==1) return false;
        state[node]=1;
        for(auto neighbour : graph[node]) {
            if(!dfsCheck(neighbour,graph,state))
                return false;
        }
        state[node]=2;
        return true;
    }
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n=graph.size();
        vector<int> state(n,0);
        vector<int> ans;
        for(int i=0;i<n;i++){
            if(dfsCheck(i,graph,state)){
                ans.push_back(i);
            }
        }
        return ans;
    }
};
```

### State Transition

```
state[node]: 0 → 1 (on entry)
             1 → 2 (on safe exit, all neighbors safe)
             1 → stays 1 if cycle found (never marked 2)

state==1 when revisited → cycle → unsafe → return false
state==2 when revisited → already confirmed safe → return true
```

---

## Approach 3 — BFS (Reverse Graph + Kahn's Algorithm)

### Key Observation

> Terminal nodes (out-degree 0) are always safe. Reverse all edges: nodes that can reach terminals in the original graph become nodes reachable FROM terminals in the reversed graph. Run Kahn's BFS on the reversed graph starting from terminal nodes — all nodes processed are safe.

```cpp
class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n=graph.size();
        vector<vector<int>> revGraph(n);
        vector<int> inDegree(n,0);
        for(int i=0;i<n;i++){
            for(auto it : graph[i]){
                revGraph[it].push_back(i);
                inDegree[i]++;
            }
        }
        queue<int> q;
        for(int i=0;i<n;i++)
            if(inDegree[i]==0) q.push(i);

        vector<int> safeNodes;
        while(!q.empty()){
            int node=q.front(); q.pop();
            safeNodes.push_back(node);
            for(auto it : revGraph[node]){
                inDegree[it]--;
                if(inDegree[it]==0) q.push(it);
            }
        }
        sort(safeNodes.begin(),safeNodes.end());
        return safeNodes;
    }
};
```

---

## Approach Comparison

| | Approach 1 | Approach 2 | Approach 3 |
|--|-----------|-----------|-----------|
| Method | DFS + vis/pathVis/check | DFS + 3-state | BFS on reversed graph |
| Arrays needed | 3 | 1 | inDegree + revGraph |
| Code clarity | Verbose | Cleanest | Moderate |
| Time | O(V+E) | O(V+E) | O(V+E) |
| Space | O(V) | O(V) | O(V+E) |

---

## Interview Explanation Script

> "A node is safe if no cycle is reachable from it. I use the same `vis`+`pathVis` arrays from directed cycle detection, but add a `check[]` array — `check[node]=1` only when DFS completes from that node without finding any cycle."

> "Approach 2 is cleaner: one `state[]` array with 3 values — 0 unvisited, 1 on current path, 2 confirmed safe. If DFS hits state=1, cycle found. If it hits state=2, already safe. After DFS completes without hitting a cycle, mark state=2."

---

## Recall Line *(10-Second Revision)*

> "Safe states: nodes not on/leading to a cycle. DFS with check[]=1 on clean exit. Or 3-state: 0/1/2. O(V+E)."

---

## Short Revision Notes

- Approach 1: `check[node]=1` set at the same point where `pathVis[node]=0` (clean backtrack)
- Approach 2: `state=2` = memoized "safe" result — avoids recomputing for shared nodes
- Approach 2 has no outer `vis` check — `state==0` handles unvisited, `state==1/2` handle revisits
- Result is naturally sorted (outer loop is `i=0` to `n-1`)
- Terminal nodes (out-degree 0): DFS loop doesn't execute → immediately marked safe

---

## Pattern Recognition Trigger

**When I see:**
- "Find all nodes from which every path leads to a terminal"
- "Nodes not part of / not leading to a cycle"
- "Safe nodes in a directed graph"

**I should think of:** DFS cycle detection + check[], or 3-state DFS, or reverse graph + Kahn's

---

## Common Mistakes

❌ Approach 1: forgetting `check[node]=0` when cycle propagates up from a neighbor
❌ Approach 2: returning `true` for `state==1` (should be `false` — state=1 means cycle)
❌ Not sorting the result (problem requires sorted output)
❌ Using undirected cycle detection technique (parent tracking) — wrong for directed graphs

---

## Related Problems

- [ ] LeetCode #207 — Course Schedule (cycle detection, same DFS)
- [ ] Striver Step 15 P18 — Detect Cycle in Directed Graph
- [ ] Striver Step 15 P20 — Topological Sort (Kahn's algorithm)

---

## Pattern Category

`Graphs` · `DFS` · `Cycle Detection` · `Directed Graph` · `Topological Sort`

---

## 30-Second Last-Minute Revision

> **Safe States:** Nodes not on/leading to a cycle.
> **Approach 1:** Same as directed cycle DFS. `check[node]=1` on clean exit (no cycle), `pathVis[node]=0`.
> **Approach 2:** `state`: 0→unvisited, 1→visiting, 2→safe. Hit state=1 → cycle (false). Hit state=2 → safe (true). Clean exit → state=2.
> **Time:** O(V+E) | **Space:** O(V)
