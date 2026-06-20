# Shortest Path in Undirected Graph (Unit Weights)

> **GFG Problem** · **Difficulty:** Medium · **Step 15 — Graphs · P22**

---

## Problem Understanding

**What is it asking?**
Given an undirected graph with `V` vertices and a list of edges (all weight = 1), and a source `src`, return the shortest distance from `src` to every other vertex. Return `-1` for unreachable vertices.

**Input:** `V` (vertices), `edges[][]` (undirected edge list), `src` (source)
**Output:** `dist[]` where `dist[i]` = shortest distance from `src` to `i`, or `-1` if unreachable

**Example:**
```
V=9, src=0
Edges: 0-1, 0-3, 3-4, 4-5, 5-6, 1-2, 2-6, 6-7, 7-8

Shortest distances from 0:
0→0: 0
0→1: 1
0→3: 1
0→2: 2
0→4: 2
0→5: 3
0→6: 3
0→7: 4
0→8: 5
```

**Key Observations:**
- All edges have weight 1 → BFS gives shortest path (each level = 1 hop)
- No need for Dijkstra — BFS is optimal for unit weights (O(V+E) vs O((V+E)logV))
- Unreachable nodes: `dist[i]` stays `1e9` → output `-1`
- Build adjacency list from edge list inside the function

---

## Optimal Approach — BFS from Source

### Key Observation

> BFS explores nodes level by level. In a unit-weight graph, each BFS level = distance 1 from the previous level. The first time BFS reaches any node, it's via the shortest path — so `dist[node]+1 < dist[neighbor]` is the relaxation condition.

### Algorithm
1. Build adjacency list from edge list
2. `dist[0..V-1] = 1e9`, `dist[src] = 0`
3. BFS from `src`: for each neighbor `it` of `node`, if `dist[node]+1 < dist[it]` → update and enqueue
4. Final: `dist[i] == 1e9 → ans[i] = -1`, else `ans[i] = dist[i]`

### Dry Run

**V=5, edges: 0-1, 0-2, 1-3, 2-3, 3-4, src=0**

```
Init: dist=[0,1e9,1e9,1e9,1e9], queue=[0]

Dequeue 0: neighbors 1,2
  dist[1]=0+1=1, enqueue 1
  dist[2]=0+1=1, enqueue 2
  queue=[1,2]

Dequeue 1: neighbors 0,3
  dist[0]=0, 0+1=1 > 0 → skip
  dist[3]=1+1=2, enqueue 3
  queue=[2,3]

Dequeue 2: neighbors 0,3
  dist[3]=2, 1+1=2 not < 2 → skip
  queue=[3]

Dequeue 3: neighbors 1,2,4
  dist[4]=2+1=3, enqueue 4
  queue=[4]

Dequeue 4: no unvisited neighbors

dist=[0,1,1,2,3] → ans=[0,1,1,2,3] ✅
```

### Complexity
- **Time:** O(V + E) — BFS processes each node and edge once
- **Space:** O(V + E) — adjacency list + dist array + queue

---

## Clean C++ Interview Code

```cpp
class Solution {
  public:
    vector<int> shortestPath(int V, vector<vector<int>> &edges, int src) {
        vector<int> adj[V];
        for(auto it:edges){
            adj[it[0]].push_back(it[1]);
            adj[it[1]].push_back(it[0]);
        }
        int dist[V];
        for(int i=0;i<V;i++){
            dist[i]=1e9;
        }
        dist[src]=0;
        queue<int> q;
        q.push(src);
        while(!q.empty()){
            int node=q.front();
            q.pop();
            for(auto it: adj[node]){
                if(dist[node]+1<dist[it]){
                    dist[it]=dist[node]+1;
                    q.push(it);
                }
            }
        }
        vector<int> ans(V,-1);
        for(int i=0;i<V;i++){
            if(dist[i]!=1e9){
                ans[i]=dist[i];
            }
        }
        return ans;
    }
};
```

### Variant — with visited array (avoids re-enqueuing)

```cpp
class Solution {
  public:
    vector<int> shortestPath(int V, vector<vector<int>>& edges, int src) {
        vector<int> adj[V];
        for(auto it:edges){
            adj[it[0]].push_back(it[1]);
            adj[it[1]].push_back(it[0]);
        }
        vector<int> dist(V,INT_MAX);
        dist[src]=0;
        queue<int> q;
        q.push(src);
        while(!q.empty()){
            int node=q.front(); q.pop();
            for(auto it: adj[node]){
                if(dist[it]==INT_MAX){
                    dist[it]=dist[node]+1;
                    q.push(it);
                }
            }
        }
        for(int i=0;i<V;i++)
            if(dist[i]==INT_MAX) dist[i]=-1;
        return dist;
    }
};
```

> In unit-weight BFS, the first time a node is reached IS the shortest path — so `dist[it]==INT_MAX` (unvisited) is equivalent to `dist[node]+1 < dist[it]`. This avoids redundant re-enqueuing.

---

## Interview Explanation Script

> "For unit-weight graphs, BFS gives shortest paths because each level of BFS represents exactly one more hop. I initialize all distances to infinity and the source to 0. During BFS, when I find a shorter path to a neighbor (`dist[node]+1 < dist[it]`), I update and enqueue it. Unreachable nodes stay at infinity — I output -1 for those."

> "Why BFS and not Dijkstra? Dijkstra uses a priority queue and runs O((V+E)logV). BFS is O(V+E) — strictly better for unit weights. Dijkstra is needed only when edge weights vary."

---

## Recall Line *(10-Second Revision)*

> "Shortest path unit weight: BFS from src. dist[]=1e9. Relax: dist[node]+1 < dist[it] → update, enqueue. 1e9 → -1. O(V+E)."

---

## Short Revision Notes

- Unit weight → BFS, not Dijkstra (BFS is O(V+E), Dijkstra is O((V+E)logV))
- `dist[src]=0` before BFS, all others `1e9`
- Relaxation: `dist[node]+1 < dist[it]` — same as Dijkstra but with +1 always
- First reach in BFS = shortest path (no need to re-process in unit weight graphs)
- `dist[i]==1e9` → node unreachable → output `-1`
- Build adj list inside function from edge list (edges given as pairs)

---

## BFS vs Dijkstra for Shortest Path

| | BFS (unit weight) | Dijkstra (weighted) |
|--|------------------|---------------------|
| Edge weights | All = 1 | Any non-negative |
| Time | O(V + E) | O((V+E) log V) |
| Data structure | Queue | Min-heap (priority queue) |
| Relaxation | `dist+1 < dist[nb]` | `dist+w < dist[nb]` |
| When to use | Unweighted / unit weight | General weighted graphs |

---

## Pattern Recognition Trigger

**When I see:**
- "Shortest path in unweighted graph"
- "Minimum hops/steps to reach a node"
- "Minimum moves in a grid" (unit weight BFS on grid)

**I should think of:** BFS with distance array (not Dijkstra)

---

## Common Mistakes

❌ Using Dijkstra for unit weights — correct but unnecessarily O((V+E)logV)
❌ Not initializing `dist[src]=0` before pushing to queue
❌ Outputting `1e9` instead of `-1` for unreachable nodes
❌ Directed graph vs undirected — this problem adds both `adj[u]→v` and `adj[v]→u`

---

## What Interviewer Is Testing

- **BFS = shortest path for unit weights** — why and when
- **BFS vs Dijkstra** distinction
- **Unreachable node handling** (`1e9 → -1`)
- **Adjacency list construction** from edge list

---

## Related Problems

- [ ] LeetCode #994 — Rotten Oranges (unit weight BFS on grid)
- [ ] LeetCode #542 — 0/1 Matrix (multi-source unit weight BFS)
- [ ] LeetCode #127 — Word Ladder (unit weight BFS on state graph)
- [ ] Striver Step 15 P23 — Shortest Path in DAG (weighted, use topo sort)
- [ ] Striver Step 15 P24 — Dijkstra's Algorithm (general weighted)

---

## Pattern Category

`Graphs` · `BFS` · `Shortest Path` · `Unit Weight`

---

## 30-Second Last-Minute Revision

> **Shortest Path (Unit Weight):** Build adj list. Init `dist[]=1e9`, `dist[src]=0`. BFS.
> Relax: `dist[node]+1 < dist[it]` → update + enqueue.
> Final: `dist[i]==1e9` → `-1`.
> **Time:** O(V+E) | Use BFS not Dijkstra for unit weights.
