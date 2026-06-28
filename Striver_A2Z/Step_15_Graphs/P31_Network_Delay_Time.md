# Network Delay Time

> **LeetCode #743** · **Difficulty:** Medium · **Step 15 — Graphs · P31**

---

## Problem Understanding

**What is it asking?**
Given a directed weighted graph of `n` nodes and travel times `times[][]` (each `[u, v, w]` = directed edge), and a source node `k`, find the **minimum time for a signal to reach ALL nodes**. Return `-1` if any node is unreachable.

**Input:** `times[][]`, `n` (nodes), `k` (source)
**Output:** Minimum time for signal to reach every node, or `-1`

**Example:**
```
n=4, k=2
times: [[2,1,1],[2,3,1],[3,4,1]]

Shortest paths from 2:
  2→1: 1
  2→3: 1
  2→3→4: 2
  (node 2 itself: 0)

Max = 2  →  Output: 2
```

**Key Observations:**
- Dijkstra from source `k` gives shortest dist to all nodes
- Answer = max of all shortest distances (all nodes must be reached)
- If any `dist[i] == 1e9` → node unreachable → return `-1`
- Directed graph → one-way edges
- Nodes are 1-indexed (`adj[n+1]`, `dist[n+1]`)

---

## Optimal Approach — Dijkstra + Max of All Distances

### Key Observation

> Run Dijkstra from `k`. The signal reaches all nodes simultaneously; the time for all nodes to receive it = the slowest (maximum shortest-path) time. If any node has dist = infinity, the signal never reaches it.

### Algorithm
1. Build directed adjacency list (1-indexed)
2. `dist[]=1e9`, `dist[k]=0`, push `{0,k}` to min-heap
3. Dijkstra with stale-entry skip: `if(dis > dist[node]) continue`
4. After Dijkstra: scan `dist[1..n]`
   - Any `1e9` → return `-1`
   - Track `max(dist[i])` → return it

### Dry Run

**n=4, k=2, times: [[2,1,1],[2,3,1],[3,4,1]]**

```
Init: dist=[1e9,1e9,0,1e9,1e9], pq={(0,2)}

Pop (0,2): dis=0 == dist[2]=0, not stale
  →1(w=1): 0+1=1 < 1e9 → dist[1]=1, push (1,1)
  →3(w=1): 0+1=1 < 1e9 → dist[3]=1, push (1,3)

Pop (1,1): dis=1 == dist[1]=1, not stale
  (no outgoing edges from node 1)

Pop (1,3): dis=1 == dist[3]=1, not stale
  →4(w=1): 1+1=2 < 1e9 → dist[4]=2, push (2,4)

Pop (2,4): dis=2 == dist[4]=2, not stale
  (no outgoing edges from node 4)

dist=[1e9,1,0,1,2]

Scan i=1..4: all ≠ 1e9
ans = max(1,0,1,2) = 2 ✅
```

### Complexity
- **Time:** O((V+E) log V) — Dijkstra with min-heap
- **Space:** O(V+E) — adjacency list + dist array

---

## Clean C++ Interview Code

```cpp
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<pair<int,int>>> adj(n+1);
        for(auto it: times){
            adj[it[0]].push_back({it[1],it[2]});
        }
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
        vector<int> dist(n+1,1e9);
        dist[k]=0;
        pq.push({0,k});
        while(!pq.empty()){
            auto it=pq.top();
            int dis=it.first;
            int node=it.second;
            pq.pop();
            if(dis>dist[node]) continue;
            for(auto iter: adj[node]){
                int adjNode=iter.first;
                int edgeWeight=iter.second;
                if(edgeWeight+dis<dist[adjNode]){
                    dist[adjNode]=edgeWeight+dis;
                    pq.push({dist[adjNode],adjNode});
                }
            }
        }
        int ans=0;
        for(int i=1;i<=n;i++){
            if(dist[i]==(int)1e9) return -1;
            ans=max(ans,dist[i]);
        }
        return ans;
    }
};
```

---

## Stale Entry Skip — `if(dis > dist[node]) continue`

```
When we find a shorter path to a node, we push a new entry to the heap.
The old entry (with higher dist) remains in the heap — it's "stale."

When stale entry is popped:
  dis  = old (higher) distance
  dist[node] = already updated to lower distance

  → dis > dist[node] → skip this node entirely
  → No incorrect relaxation happens
  → Equivalent to the implicit skip in standard Dijkstra
    (where relaxation just wouldn't trigger anyway)

Benefit: avoids iterating over all neighbors unnecessarily.
```

---

## Interview Explanation Script

> "I run Dijkstra from source `k` to get the shortest time to reach every node. The answer is the maximum of all shortest distances — the signal reaches all nodes simultaneously, so we wait for the last one."

> "I use `if(dis > dist[node]) continue` to explicitly skip stale heap entries — when a shorter path to a node was already found, any older entry in the heap has `dis > dist[node]` and can be safely ignored."

> "After Dijkstra, I scan all nodes. If any node has distance infinity, it's unreachable — return `-1`. Otherwise return the max."

---

## Recall Line *(10-Second Revision)*

> "Network delay: Dijkstra from k. Skip stale: if(dis>dist[node]) continue. Answer = max(dist[1..n]). Any 1e9 → -1."

---

## Short Revision Notes

- Directed graph → `adj[it[0]].push_back({it[1],it[2]})` one-way only
- `dist[n+1]` and `adj[n+1]` — 1-indexed (nodes 1 to n)
- Stale skip: `if(dis > dist[node]) continue` — explicit optimization
- After Dijkstra: two-pass over `dist[]` — check reachability AND find max
- Cast `(int)1e9` for comparison — avoids float comparison issues
- Source `k` itself: `dist[k]=0` → contributes 0 to max answer

---

## Two Ways to Handle Stale Entries

```cpp
// Method 1: Explicit skip (user's approach — cleaner)
if(dis > dist[node]) continue;

// Method 2: Implicit (let relaxation handle it)
// No skip needed — relaxation condition won't trigger for stale entries
// because: dis > dist[node] → dis+w > dist[node]+w ≥ dist[adj]

// Both are correct. Method 1 avoids iterating over adj[node] unnecessarily.
```

---

## Pattern Recognition Trigger

**When I see:**
- "Minimum time/cost to reach ALL nodes from a source"
- "Signal propagation delay"
- "When does the last node receive X?"

**I should think of:** Dijkstra from source → max of all shortest distances

---

## Common Mistakes

❌ Returning `max(dist[])` without checking for unreachable nodes first
❌ Building undirected adjacency list — edges in `times` are directed
❌ 0-indexed when nodes are 1-indexed → off-by-one on `dist[]` scan
❌ Comparing `dist[i] == 1e9` with float (use cast `(int)1e9` or use `INT_MAX`)

---

## Dijkstra Problems Comparison

| Problem | What dist[] means | Answer |
|---------|------------------|--------|
| Standard shortest path (P26) | Min cost to reach each node | `dist[target]` |
| Shortest path + trace (P27) | Min cost + parent tracking | Path vector |
| Path min effort (P29) | Min max-diff to reach cell | `dist[n-1][m-1]` |
| Cheapest K stops (P30) | Min cost within k stops | `dist[dst]` |
| **Network delay (P31)** | Min time for signal to each node | `max(dist[1..n])` |

---

## Related Problems

- [ ] Striver Step 15 P26 — Dijkstra (return dist[] array)
- [ ] Striver Step 15 P30 — Cheapest Flights K Stops (BFS, stop constraint)
- [ ] LeetCode #1514 — Path with Maximum Probability

---

## Pattern Category

`Graphs` · `Dijkstra` · `Shortest Path` · `Directed Graph` · `All-Nodes Reachability`

---

## 30-Second Last-Minute Revision

> **Network Delay:** Dijkstra from `k`. Directed graph.
> `dist[]=1e9`, `dist[k]=0`. Min-heap `{dist,node}`.
> Pop → `if(dis>dist[node]) continue` (stale skip). Relax neighbors.
> Scan `dist[1..n]`: any `1e9` → `-1`. Return `max(dist[i])`.
> **Time:** O((V+E)logV) | **Key:** answer = max of all shortest paths.
