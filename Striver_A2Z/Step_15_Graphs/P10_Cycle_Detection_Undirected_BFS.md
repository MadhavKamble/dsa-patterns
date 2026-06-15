# Detect Cycle in Undirected Graph (BFS)

> **GFG / Concept Problem** · **Difficulty:** Medium · **Step 15 — Graphs · P10**

---

## Problem Understanding

**What is it asking?**
Given an undirected graph with `V` vertices and `E` edges (as adjacency list), determine whether the graph contains a **cycle**.

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
- In BFS, a cycle exists if we reach an **already-visited node** that is **not the parent** of the current node
- We need to track the **parent** of each node to avoid false positives (the edge we came from always points back to the parent — that's not a cycle)
- For disconnected graphs: run BFS from every unvisited node; if any component has a cycle → return `true`

---

## Optimal Approach — BFS with Parent Tracking

### Key Observation

> In an undirected graph, BFS from a node will naturally see all adjacent nodes. The edge back to the parent is expected — it's the same edge we traversed to arrive. But if we see a neighbor that is already visited AND is NOT the parent, we found a back edge → cycle.
>
> Store `{node, parent}` in the queue.

### Algorithm
1. `visited[0..V-1] = false`
2. For each unvisited node `i` (handles disconnected graphs):
   - BFS from `i` with parent = `-1`
   - Queue stores `{node, parent}`
   - Dequeue `{curr, par}`, mark visited
   - For each neighbor `nb`:
     - If not visited: enqueue `{nb, curr}`
     - If visited AND `nb != par`: **cycle found** → return `true`
3. Return `false`

### Dry Run

**Graph with cycle:** `adj: 0:[1,2], 1:[0,2], 2:[1,0]`

| Dequeued | Parent | Neighbors | Action |
|----------|--------|-----------|--------|
| 0 | -1 | 1, 2 | enqueue {1,0}, {2,0} |
| 1 | 0 | 0, 2 | 0 visited & 0==par → skip; 2 not visited → enqueue {2,1} |
| 2 | 0 | 1, 0 | 1 visited & 1≠par(0) → **CYCLE!** |

Return `true` ✅

**Graph without cycle:** `adj: 0:[1], 1:[0,2], 2:[1]`

| Dequeued | Parent | Neighbors | Action |
|----------|--------|-----------|--------|
| 0 | -1 | 1 | enqueue {1,0} |
| 1 | 0 | 0, 2 | 0 visited & 0==par → skip; 2 not visited → enqueue {2,1} |
| 2 | 1 | 1 | 1 visited & 1==par → skip |

Queue empty → return `false` ✅

### Complexity
- **Time:** O(V + E) — each node and edge processed once
- **Space:** O(V) — visited array + queue

---

## Clean C++ Interview Code

```cpp
class Solution {
public:
    bool isCycle(int V, vector<vector<int>>& adj) {
        vector<bool> visited(V,false);
        for(int i=0;i<V;i++){
            if(!visited[i]){
                queue<pair<int,int>> q;
                visited[i]=true;
                q.push({i,-1});
                while(!q.empty()){
                    auto it=q.front();
                    q.pop();
                    int curr=it.first;
                    int par=it.second;
                    for(int nb : adj[curr]){
                        if(!visited[nb]){
                            visited[nb]=true;
                            q.push({nb,curr});
                        } else if(nb!=par){
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }
};
```

---

## Interview Explanation Script

> "For cycle detection in an undirected graph using BFS, I store the parent alongside each node in the queue. When I dequeue a node and check its neighbors: if a neighbor is already visited and is NOT the node I came from, that's a back edge — a cycle exists."

> "The parent check is essential. In an undirected graph, every edge appears in both directions in the adjacency list. Without tracking the parent, the edge back to where we came from would always look like a cycle."

> "I wrap BFS in an outer loop to handle disconnected graphs."

---

## Recall Line *(10-Second Revision)*

> "Cycle (undirected, BFS): Queue stores {node, parent}. Visited neighbor ≠ parent → cycle. O(V+E)."

---

## Short Revision Notes

- Parent tracking is what distinguishes cycle detection from plain BFS
- `nb != par` is the cycle condition — visited neighbor that isn't the direct predecessor
- Outer for-loop handles disconnected components
- BFS and DFS approaches give the same result — just different traversal styles
- This only works for **undirected** graphs; directed graphs need a different approach (color-based DFS)

---

## Pattern Recognition Trigger

**When I see:**
- "Does this undirected graph have a cycle?"
- "Can we form a tree from these edges?" (no cycle = tree)
- "Is this graph acyclic?"

**I should think of:** BFS/DFS with parent tracking (undirected), or Union-Find

---

## Common Mistakes

❌ Not tracking parent → always detects a false cycle (every undirected edge looks like a cycle)
❌ Marking visited after dequeue instead of before enqueue → same node enqueued multiple times
❌ Not using outer loop → misses disconnected components
❌ Using this approach for directed graphs → wrong (directed needs DFS with recursion stack)

---

## What Interviewer Is Testing

- **Why parent tracking is needed** in undirected graphs
- **Disconnected graph handling** with outer loop
- **Difference between undirected and directed** cycle detection

---

## Approach Comparison for Cycle Detection

| Approach | Graph Type | Key Idea |
|----------|-----------|----------|
| BFS + parent | Undirected | Visited neighbor ≠ parent → cycle |
| DFS + parent | Undirected | Visited neighbor ≠ parent → cycle |
| DFS + rec stack | Directed | Neighbor in current DFS path → cycle |
| Union-Find | Undirected | Adding edge to same component → cycle |

---

## Related Problems

- [ ] Striver Step 15 P11 — Detect Cycle Undirected (DFS)
- [ ] LeetCode #684 — Redundant Connection (Union-Find cycle detection)
- [ ] LeetCode #207 — Course Schedule (cycle in directed graph)
- [ ] LeetCode #261 — Graph Valid Tree (undirected acyclic + connected)

---

## Pattern Category

`Graphs` · `BFS` · `Cycle Detection` · `Undirected Graph`

---

## Difficulty Analysis

**Rating:** Medium (BFS is straightforward; the parent-tracking detail is what trips people up)

**Why challenging:** Understanding why parent tracking is necessary, and knowing this approach doesn't extend to directed graphs.

---

## 30-Second Last-Minute Revision

> **Cycle in Undirected (BFS):** Queue = {node, parent}. Mark visited on enqueue.
> Dequeue → check neighbors: visited & ≠ parent → cycle found.
> Outer loop for disconnected components.
> **Time:** O(V+E) | **Space:** O(V)
