# Topological Sort

> **GFG Problem** · **Difficulty:** Medium · **Step 15 — Graphs · P20**

---

## Problem Understanding

**What is it asking?**
Given a **Directed Acyclic Graph (DAG)** with `V` vertices and adjacency list `adj[]`, return a **topological ordering** — a linear ordering of vertices such that for every directed edge `u → v`, `u` appears before `v` in the ordering.

**Input:** `V` (vertices), `adj[]` — directed adjacency list (DAG, no cycles)
**Output:** A valid topological order (multiple valid orderings may exist)

**Example:**
```
Graph: 5→0, 5→2, 4→0, 4→1, 2→3, 3→1

One valid topo order: [5, 4, 2, 3, 1, 0]
Another valid:        [4, 5, 2, 3, 0, 1]

Rule: for every edge u→v, u must come before v
```

**Key Observations:**
- Only possible on **DAGs** (cycles make ordering impossible)
- Terminal nodes (out-degree 0) always appear at the end
- Source nodes (in-degree 0) always appear at the start
- DFS: push node to stack **after** all neighbors are processed (post-order)
- BFS (Kahn's): process nodes with in-degree 0 first, reduce neighbors' in-degrees

---

## Approach 1 — DFS + Stack

### Key Observation

> In DFS, we push a node to the stack **after** all its neighbors have been fully processed. When we pop the stack, nodes come out in reverse post-order = topological order. A node only goes on the stack once all nodes it must precede have been visited.

### Algorithm
1. `vis[0..V-1] = 0`, empty `stack`
2. For each unvisited node: DFS
3. DFS: mark visited → recurse all unvisited neighbors → **push to stack**
4. Pop stack into result array

### Dry Run

**Graph: 5→0, 5→2, 4→0, 4→1, 2→3, 3→1**

```
DFS(5): vis[5]=1
  DFS(0): vis[0]=1, no unvisited neighbors → st.push(0)
  DFS(2): vis[2]=1
    DFS(3): vis[3]=1
      DFS(1): vis[1]=1, no unvisited neighbors → st.push(1)
      st.push(3)
    st.push(2)
  st.push(5)
DFS(4): vis[4]=1
  0 already visited, 1 already visited
  st.push(4)

Stack (top→bottom): 4, 5, 2, 3, 1, 0
Pop → result: [4, 5, 2, 3, 1, 0] ✅
```

### Complexity
- **Time:** O(V + E) — each node and edge visited once
- **Space:** O(V) — vis array + stack

```cpp
class Solution {
public:
    void dfs(int node, vector<int> adj[], vector<int>& vis, stack<int>& st) {
        vis[node]=1;
        for(auto it : adj[node]) {
            if(!vis[it]) {
                dfs(it,adj,vis,st);
            }
        }
        st.push(node);
    }
    vector<int> topoSort(int V, vector<int> adj[]) {
        vector<int> vis(V,0);
        stack<int> st;
        for(int i=0;i<V;i++) {
            if(!vis[i]) {
                dfs(i,adj,vis,st);
            }
        }
        vector<int> ans;
        while(!st.empty()) {
            ans.push_back(st.top());
            st.pop();
        }
        return ans;
    }
};
```

---

## Approach 2 — BFS / Kahn's Algorithm

### Key Observation

> Start with all nodes that have in-degree 0 (no prerequisites). Process them, reduce neighbors' in-degrees. When a neighbor's in-degree drops to 0, it has no more unprocessed prerequisites — add it to the queue. Order of processing = topological order.
>
> Bonus: if the result doesn't contain all `V` nodes, the graph has a cycle.

### Algorithm
1. Compute `inDegree[i]` for all nodes
2. Enqueue all nodes with `inDegree[i]==0`
3. BFS: dequeue node, add to result, decrement in-degree of all neighbors
4. If neighbor's in-degree hits 0: enqueue it
5. Return result (`result.size() != V` → cycle exists)

### Dry Run

**Graph: 5→0, 5→2, 4→0, 4→1, 2→3, 3→1**

```
inDegree: 0→2, 1→2, 2→1, 3→1, 4→0, 5→0
Queue: [4, 5]

Dequeue 4: topo=[4], inDegree[0]→1, inDegree[1]→1
Dequeue 5: topo=[4,5], inDegree[0]→0(enqueue), inDegree[2]→0(enqueue)
Dequeue 0: topo=[4,5,0]
Dequeue 2: topo=[4,5,0,2], inDegree[3]→0(enqueue)
Dequeue 3: topo=[4,5,0,2,3], inDegree[1]→0(enqueue)
Dequeue 1: topo=[4,5,0,2,3,1]
```

Result: `[4,5,0,2,3,1]` ✅ (valid topo order)

### Complexity
- **Time:** O(V + E) — each node dequeued once, each edge processed once
- **Space:** O(V) — inDegree array + queue

```cpp
class Solution {
public:
    vector<int> topologicalSort(int V, vector<int> adj[]) {
        vector<int> indegree(V,0);
        for(int i=0;i<V;i++) {
            for(auto it : adj[i]) {
                indegree[it]++;
            }
        }
        queue<int> q;
        for(int i=0;i<V;i++) {
            if(indegree[i]==0) {
                q.push(i);
            }
        }
        vector<int> topo;
        while(!q.empty()) {
            int node=q.front();
            q.pop();
            topo.push_back(node);
            for(auto it : adj[node]) {
                indegree[it]--;
                if(indegree[it]==0) {
                    q.push(it);
                }
            }
        }
        return topo;
    }
};
```

---

## DFS vs BFS (Kahn's) Comparison

| Property | DFS + Stack | BFS / Kahn's |
|----------|------------|--------------|
| Data structure | Stack | Queue + inDegree array |
| Order produced | Reverse post-order | Source-first order |
| Cycle detection | Separate pass needed | Built-in: `topo.size() != V` |
| Code simplicity | Simple | Slightly more setup |
| Use when | Pure topo sort | Also need cycle detection |

---

## Interview Explanation Script

> **DFS:** "I run DFS and push each node to a stack only after all its successors are fully processed. Popping the stack gives topological order — every node appears before all nodes it has edges to."

> **Kahn's:** "I compute in-degrees and start BFS from nodes with no prerequisites (in-degree 0). As I process each node, I remove its edges by decrementing neighbors' in-degrees. When a neighbor hits 0, all its prerequisites are done — enqueue it. If not all nodes are processed, a cycle exists."

---

## Recall Line *(10-Second Revision)*

> "Topo DFS: push to stack AFTER recursing neighbors. Pop stack = topo order."
> "Kahn's BFS: in-degree 0 → queue. Dequeue → decrement neighbors. 0 in-degree → enqueue."

---

## Short Revision Notes

- DFS: push node to stack **after** (not before) processing all neighbors
- Kahn's: `topo.size() != V` after BFS → cycle detected (used in P18 BFS variant)
- Both run O(V+E) — same time complexity
- Topological sort is only defined for DAGs
- Multiple valid topological orderings exist for most graphs
- DFS topo order and Kahn's topo order may differ — both are valid

---

## Pattern Recognition Trigger

**When I see:**
- "Order tasks given prerequisites"
- "Scheduling with dependencies"
- "Is this graph a DAG?" (Kahn's: `topo.size() != V` → cycle)
- Course Schedule II, build order, compile order

**I should think of:** Topological sort (DFS stack or Kahn's BFS)

---

## Common Mistakes

❌ DFS: pushing node to stack **before** recursing neighbors → wrong order
❌ Kahn's: not computing in-degrees for ALL nodes before starting BFS
❌ Using topo sort on a graph with cycles (undefined — Kahn's detects this, DFS doesn't)
❌ Confusing topo sort (DAG ordering) with BFS/DFS traversal order

---

## What Interviewer Is Testing

- **DFS:** post-order push to stack
- **Kahn's:** in-degree array, queue seeded with 0-in-degree nodes
- **Cycle detection via Kahn's:** `topo.size() != V`
- Connection to real problems: Course Schedule, build systems

---

## Real Problem Applications

| Problem | How topo sort applies |
|---------|----------------------|
| LC #207 Course Schedule | Detect cycle via Kahn's |
| LC #210 Course Schedule II | Return Kahn's topo order |
| LC #269 Alien Dictionary | Build graph from word order, return topo sort |
| LC #310 Minimum Height Trees | Related — find roots via in-degree |

---

## Related Problems

- [ ] LeetCode #207 — Course Schedule (Kahn's cycle detection)
- [ ] LeetCode #210 — Course Schedule II (return topo order)
- [ ] Striver Step 15 P18 — Detect Cycle in Directed Graph
- [ ] Striver Step 15 P19 — Eventual Safe States

---

## Pattern Category

`Graphs` · `DFS` · `BFS` · `Topological Sort` · `DAG` · `Kahn's Algorithm`

---

## 30-Second Last-Minute Revision

> **Topo Sort DFS:** DFS → push to stack AFTER all neighbors done → pop stack = answer.
> **Kahn's BFS:** Compute inDegree. Queue all inDegree==0. Dequeue → add to result → decrement neighbors → enqueue if inDegree hits 0.
> Kahn's bonus: `result.size() != V` → cycle.
> **Time:** O(V+E) | **Space:** O(V)
