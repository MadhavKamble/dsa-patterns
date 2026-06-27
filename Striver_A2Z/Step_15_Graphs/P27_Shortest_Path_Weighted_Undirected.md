# Shortest Path in Weighted Undirected Graph (with Path Reconstruction)

> **GFG Problem** · **Difficulty:** Medium · **Step 15 — Graphs · P27**

---

## Problem Understanding

**What is it asking?**
Given a weighted undirected graph with `n` nodes and `m` edges, find the **shortest path from node 1 to node n** and return the **actual path** (not just the distance). Return `{-1}` if no path exists.

**Input:** `n` (nodes), `m` (edges), `edges[][]` — each edge `[u, v, weight]`
**Output:** Vector of nodes forming the shortest path from 1 to n, or `{-1}`

**Example:**
```
n=5, edges: 1-2(2), 1-4(1), 4-2(3), 2-3(6), 3-5(2), 4-3(4), 3-5(2)

Shortest path 1→5:
1→4→3→5: cost = 1+4+2 = 7
1→2→3→5: cost = 2+6+2 = 10

Output: [1, 4, 3, 5]
```

**Key Observations:**
- Dijkstra gives shortest distances; add `parent[]` array to reconstruct the path
- `parent[node] = node` initially (self-loop marks source/unvisited)
- When relaxing: `parent[adjNode] = node` — track where we came from
- Path reconstruction: walk `parent[]` back from `n` to `1`, then reverse
- Nodes are 1-indexed (`n+1` sized arrays)

---

## Optimal Approach — Dijkstra + Parent Array

### Key Observation

> Standard Dijkstra finds shortest distances. To also find the path, maintain `parent[adjNode] = node` whenever we relax an edge. After BFS completes, trace back from `n` through parent pointers until we reach the source (where `parent[node]==node`).

### Algorithm
1. Build adjacency list (1-indexed)
2. `dist[]=1e9`, `dist[1]=0`, `parent[i]=i`, push `{0,1}` to min-heap
3. Dijkstra: relax edges, update `parent[adjNode]=node` on each relaxation
4. If `dist[n]==1e9` → return `{-1}`
5. Trace path: start at `n`, follow `parent[]` until `parent[node]==node`, push each node
6. Reverse and return

### Dry Run

**n=4, edges: 1-2(1), 2-3(2), 1-3(6), 3-4(1)**

```
Init: dist=[∞,0,∞,∞,∞], parent=[_,1,2,3,4], pq={(0,1)}

Pop (0,1): neighbors 2(1), 3(6)
  dist[2]=1, parent[2]=1, push (1,2)
  dist[3]=6, parent[3]=1, push (6,3)

Pop (1,2): neighbors 1(1), 3(2)
  1+1 > dist[1]=0 → skip
  1+2=3 < dist[3]=6 → dist[3]=3, parent[3]=2, push (3,3)

Pop (3,3): neighbors 2(2), 1(6), 4(1)
  3+2 > dist[2]=1 → skip
  3+6 > dist[1]=0 → skip
  3+1=4, dist[4]=4, parent[4]=3, push (4,4)

Pop (4,4): no neighbors updating
Pop (6,3): stale, relaxation won't improve anything

dist=[∞,0,1,3,4]
parent=[_,1,1,2,3]

Trace from 4: 4→parent[4]=3→parent[3]=2→parent[2]=1→parent[1]=1 (stop)
path=[4,3,2,1] → reverse → [1,2,3,4] ✅
```

### Complexity
- **Time:** O((V+E) log V) — Dijkstra with min-heap
- **Space:** O(V+E) — adjacency list + dist + parent arrays

---

## Clean C++ Interview Code

```cpp
class Solution {
    public:
        vector<int> shortestPath(int n, int m, vector<vector<int>>& edges){
            vector<pair<int,int>> adj[n+1];
            for(auto it: edges){
                adj[it[0]].push_back({it[1],it[2]});
                adj[it[1]].push_back({it[0],it[2]});
            }
            priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
            vector<int> dist(n+1,1e9);
            vector<int> parent(n+1);
            for(int i=1;i<=n;i++){
                parent[i]=i;
            }
            dist[1]=0;
            pq.push({0,1});
            while(!pq.empty()){
                auto it=pq.top();
                int node=it.second;
                int dis=it.first;
                pq.pop();
                for(auto it: adj[node]){
                    int adjNode=it.first;
                    int edgeWeight=it.second;
                    if(dis+edgeWeight<dist[adjNode]){
                        dist[adjNode]=dis+edgeWeight;
                        pq.push({dist[adjNode],adjNode});
                        parent[adjNode]=node;
                    }
                }
            }
            if(dist[n]==1e9) return {-1};
            vector<int> path;
            int node=n;
            while(parent[node]!=node){
                path.push_back(node);
                node=parent[node];
            }
            path.push_back(1);
            reverse(path.begin(),path.end());
            return path;
        }
};
```

> **Bug fix from original:** `pq.push({0,1})` added after `dist[1]=0` — without this, the priority queue starts empty and the while loop never executes.
> Also fixed: `parent` loop changed to `i=1;i<=n` (1-indexed nodes).

---

## Path Reconstruction — How `parent[]` Works

```
parent[i] = i      → node i is the source (or unvisited — hasn't been relaxed)
parent[i] = j      → shortest path to i goes through j

Trace: n → parent[n] → parent[parent[n]] → ... → 1
Stop condition: parent[node] == node (reached source)

Why reverse at the end:
  We trace backwards (n→...→1), push in that order → path is reversed
  reverse() fixes it to get [1→...→n]
```

---

## Interview Explanation Script

> "I run Dijkstra from node 1 and additionally maintain a `parent[]` array. Whenever I relax an edge to `adjNode`, I set `parent[adjNode]=node` — tracking the predecessor on the shortest path. After Dijkstra completes, I trace back from `n` through parent pointers until I reach the source (where `parent[node]==node`), collect nodes, then reverse."

> "If `dist[n]` is still infinity after Dijkstra, node `n` is unreachable — return `{-1}`."

---

## Recall Line *(10-Second Revision)*

> "Shortest path + trace: Dijkstra + parent[adjNode]=node on relax. Trace n→1 via parent[], reverse. O((V+E)logV)."

---

## Short Revision Notes

- Add `pq.push({0, src})` before the while loop — easy to forget, breaks everything
- `parent[i]=i` init — self-loop signals "source" or "unvisited"
- Update `parent[adjNode]=node` inside the relaxation condition only
- Trace stops when `parent[node]==node` (reached source)
- 1-indexed nodes → arrays of size `n+1`
- `dist[n]==1e9` → unreachable → return `{-1}`

---

## Dijkstra vs Dijkstra + Path

| | Distance only | Distance + Path |
|--|--------------|-----------------|
| Extra array | None | `parent[]` |
| Extra step | None | Trace back + reverse |
| Update | `dist[adj]=dis+w` | + `parent[adj]=node` |
| Output | `dist[]` array | Path vector |

---

## Pattern Recognition Trigger

**When I see:**
- "Find shortest path AND return the actual route"
- "Print the path, not just the cost"
- "Reconstruct the shortest path"

**I should think of:** Dijkstra + `parent[]` array → trace back → reverse

---

## Common Mistakes

❌ Forgetting `pq.push({0, src})` — queue starts empty, loop never runs
❌ `parent` loop `i=0` to `n-1` when nodes are 1-indexed → off by one
❌ Setting `parent[adjNode]=node` outside the relaxation if-block → wrong parent
❌ Tracing with `parent[node]!=1` instead of `parent[node]!=node` → misses source push
❌ Forgetting `reverse()` at the end

---

## What Interviewer Is Testing

- **Dijkstra correctness** — min-heap, relaxation
- **Path reconstruction** via parent array — the add-on to standard Dijkstra
- **Trace-back pattern** — follow parent until self-loop, then reverse
- **Edge case:** unreachable destination

---

## Related Problems

- [ ] Striver Step 15 P26 — Dijkstra (distance only)
- [ ] LeetCode #743 — Network Delay Time
- [ ] LeetCode #1631 — Path with Minimum Effort

---

## Pattern Category

`Graphs` · `Dijkstra` · `Shortest Path` · `Path Reconstruction` · `Priority Queue`

---

## 30-Second Last-Minute Revision

> **Shortest Path + Trace:** Dijkstra + `parent[adjNode]=node` on each relaxation.
> Init: `parent[i]=i`, `dist[1]=0`, `pq.push({0,1})`.
> After Dijkstra: trace `n→parent[n]→...→1` (stop when `parent[node]==node`).
> Push each, reverse. `dist[n]==1e9` → return `{-1}`.
> **Time:** O((V+E)logV) | **Space:** O(V+E)
