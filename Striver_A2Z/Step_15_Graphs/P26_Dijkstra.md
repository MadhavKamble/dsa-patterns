# Dijkstra's Algorithm

> **GFG / LeetCode #743** · **Difficulty:** Medium · **Step 15 — Graphs · P26**

---

## Problem Understanding

**What is it asking?**
Given a weighted undirected graph with `V` vertices and `edges[][]` (each edge = `[u, v, weight]`), find the shortest distance from source `src` to all other vertices.

**Input:** `V`, `edges[][]`, `src`
**Output:** `dist[]` — shortest distance from `src` to every vertex

**Example:**
```
V=5, src=0
Edges: 0-1(4), 0-2(1), 2-1(2), 1-3(1), 2-3(5), 3-4(3)

Shortest paths from 0:
0→0: 0
0→1: 3  (0→2→1)
0→2: 1  (0→2)
0→3: 4  (0→2→1→3)
0→4: 7  (0→2→1→3→4)
```

**Key Observations:**
- Greedy: always process the unvisited node with the current minimum distance
- Works for non-negative weights only (negative edges → Bellman-Ford)
- Two implementations: **min-heap (priority queue)** or **set**
- `dist[src]=0`, all others `1e9` (infinity)
- Relaxation: if `dist[node] + weight < dist[adjNode]` → update

---

## Approach 1 — Priority Queue (Min-Heap)

### Key Observation

> Use a min-heap keyed by distance. Always pop the node with the smallest current distance. If a shorter path is found to a neighbor, push the new `{dist, node}` to the heap. Stale entries (with outdated larger distances) are naturally skipped because `dis > dist[node]` when popped.

### Algorithm
1. `dist[]=1e9`, `dist[src]=0`, push `{0, src}` to min-heap
2. Pop `{dis, node}` — process its neighbors
3. If `dis + weight < dist[adjNode]`: update `dist[adjNode]`, push `{dist[adjNode], adjNode}`
4. Stale entries: automatically ignored (their `dis` > current `dist[node]`)

### Dry Run

**V=3, edges: 0-1(5), 0-2(1), 2-1(2), src=0**

```
Init: dist=[0,1e9,1e9], pq={(0,0)}

Pop (0,0): neighbors 1(5), 2(1)
  dist[1]=5, push (5,1)
  dist[2]=1, push (1,2)

Pop (1,2): neighbors 0(1), 1(2)
  0+1=1 not < dist[0]=0 → skip
  1+2=3 < dist[1]=5 → dist[1]=3, push (3,1)

Pop (3,1): neighbors 0(5), 2(2)
  3+5 > 0 → skip
  3+2 > 1 → skip

Pop (5,1): dis=5 > dist[1]=3 → stale, skip (implicitly — no check needed,
           relaxation just won't trigger)

dist=[0,3,1] ✅
```

```cpp
class Solution {
public:
    vector<int> dijkstra(int V, vector<vector<int>>& edges, int src) {
        vector<vector<pair<int,int>>> adj(V);
        for(auto edge: edges){
            int u=edge[0];
            int v=edge[1];
            int w=edge[2];
            adj[u].push_back({v,w});
            adj[v].push_back({u,w});
        }
        priority_queue<pair<int,int>,
                       vector<pair<int,int>>,
                       greater<pair<int,int>>> pq;
        vector<int> dist(V,1e9);
        dist[src]=0;
        pq.push({0,src});
        while(!pq.empty()){
            int dis=pq.top().first;
            int node=pq.top().second;
            pq.pop();
            for(auto it: adj[node]){
                int adjNode=it.first;
                int weight=it.second;
                if(dis+weight<dist[adjNode]){
                    dist[adjNode]=dis+weight;
                    pq.push({dist[adjNode],adjNode});
                }
            }
        }
        return dist;
    }
};
```

---

## Approach 2 — Set (Ordered by Distance)

### Key Observation

> Use an ordered `set<{dist, node}>` instead of a priority queue. Advantage: when a shorter path is found, we can **explicitly erase** the outdated entry before inserting the updated one — no stale entries accumulate. `set.begin()` always gives the minimum-distance node.

### Algorithm
1. `dist[]=1e9`, `dist[src]=0`, insert `{0,src}` into set
2. Extract `*st.begin()` (min-dist node), erase it
3. For each neighbor: if relaxed → erase old `{dist[adjNode],adjNode}` from set (if not 1e9), update `dist[adjNode]`, insert new `{dist[adjNode],adjNode}`

```cpp
class Solution {
public:
    vector<int> dijkstra(int V, vector<vector<int>>& edges, int src) {
        vector<vector<pair<int,int>>> adj(V);
        for(auto edge: edges){
            int u=edge[0];
            int v=edge[1];
            int w=edge[2];
            adj[u].push_back({v,w});
            adj[v].push_back({u,w});
        }
        set<pair<int,int>> st;
        vector<int> dist(V,1e9);
        st.insert({0,src});
        dist[src]=0;
        while(!st.empty()){
            auto it=*(st.begin());
            int node=it.second;
            int dis=it.first;
            st.erase(it);
            for(auto it: adj[node]){
                int adjNode=it.first;
                int edgeWeight=it.second;
                if(dis+edgeWeight<dist[adjNode]){
                    if(dist[adjNode]!=1e9){
                        st.erase({dist[adjNode],adjNode});
                    }
                    dist[adjNode]=dis+edgeWeight;
                    st.insert({dist[adjNode],adjNode});
                }
            }
        }
        return dist;
    }
};
```

---

## Approach Comparison

| | Priority Queue | Set |
|--|---------------|-----|
| Data structure | Min-heap | Ordered set (BST) |
| Stale entries | Accumulate — skipped implicitly | Explicitly erased on update |
| Extract min | O(log N) | O(log N) |
| Update key | Not supported — push duplicate | O(log N) erase + insert |
| Memory | O(E) worst case (duplicates) | O(V) — at most V entries |
| Preferred | Most competitive programming | When memory matters |

---

## Interview Explanation Script

> **PQ approach:** "I use a min-heap keyed by `{dist, node}`. I always process the node with the smallest known distance. When relaxing a neighbor, I push the new distance to the heap. Old entries with outdated distances remain but are harmless — when popped, their relaxation condition `dis+w < dist[adj]` won't trigger since `dist[adj]` is already better."

> **Set approach:** "Same logic but with an ordered set. The advantage: when I find a shorter path to a node already in the set, I explicitly erase the old entry and insert the updated one — no stale duplicates. `*st.begin()` always gives the minimum."

---

## Recall Line *(10-Second Revision)*

> "Dijkstra: min-heap {dist,node}. Pop min. Relax: dis+w < dist[adj] → update + push. O((V+E)logV)."

---

## Short Revision Notes

- Pair order matters: `{dist, node}` not `{node, dist}` — heap/set orders by first element
- `greater<pair<int,int>>` makes priority_queue a min-heap (default is max-heap)
- PQ: stale entries handled implicitly by relaxation condition
- Set: must erase `{dist[adjNode], adjNode}` (not just `adjNode`) — set is ordered by pair
- Only works for **non-negative weights** — negative edges break the greedy assumption
- `dist[src]=0`, push/insert `{0,src}` before loop

---

## When to Use Which Shortest Path Algorithm

| Situation | Algorithm |
|-----------|-----------|
| Unweighted graph | BFS — O(V+E) |
| DAG (any weights) | Topo sort + relax — O(V+E) |
| Non-negative weights | Dijkstra — O((V+E)logV) |
| Negative weights, no neg cycle | Bellman-Ford — O(VE) |
| All-pairs shortest path | Floyd-Warshall — O(V³) |

---

## Pattern Recognition Trigger

**When I see:**
- "Shortest path in weighted graph (non-negative)"
- "Minimum cost to reach destination"
- "Network delay time", "path with minimum effort"

**I should think of:** Dijkstra with min-heap

---

## Common Mistakes

❌ Using max-heap instead of min-heap (forget `greater<>`)
❌ Putting `{node, dist}` in heap — heap sorts by first element, must be `{dist, node}`
❌ Using Dijkstra with negative weights → incorrect results
❌ Set approach: erasing just `adjNode` instead of `{dist[adjNode], adjNode}`
❌ Not initializing `dist[src]=0` before pushing to heap

---

## What Interviewer Is Testing

- **Min-heap setup:** `greater<pair<int,int>>`, `{dist,node}` ordering
- **Relaxation condition:** `dis + weight < dist[adjNode]`
- **Stale entry handling** (PQ) vs explicit erasure (set)
- **Algorithm selection:** why not BFS, why not Bellman-Ford

---

## Related Problems

- [ ] LeetCode #743 — Network Delay Time (Dijkstra, directed)
- [ ] LeetCode #1631 — Path with Minimum Effort (Dijkstra on grid)
- [ ] LeetCode #778 — Swim in Rising Water (binary search + BFS or Dijkstra)
- [ ] Striver Step 15 P23 — Shortest Path DAG (O(V+E), DAG only)
- [ ] Striver Step 15 P27 — Shortest Path with K Stops (modified Dijkstra)

---

## Pattern Category

`Graphs` · `Dijkstra` · `Shortest Path` · `Greedy` · `Priority Queue`

---

## 30-Second Last-Minute Revision

> **Dijkstra:** `dist[]=1e9`, `dist[src]=0`. Min-heap `{dist,node}`.
> Pop `{dis,node}` → for each neighbor: `dis+w < dist[adj]` → update + push.
> **`greater<pair<int,int>>`** for min-heap. `{dist,node}` not `{node,dist}`.
> Non-negative weights only. **Time:** O((V+E)logV) | **Space:** O(V+E)
